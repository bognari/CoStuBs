// This file is part of CoStuBS.
//
// CoStuBS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CoStuBS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CoStuBS.  If not, see <http://www.gnu.org/licenses/>.

#include "thread/ActivityScheduler.h"

#include "sync/Monitor.h"
#include "sync/KernelLock.h"

/*
 * ActivityScheduler:   Diese Klasse implementiert die Zustandsverwaltung
 *      für Activities
 *
 */

/* Suspendieren des aktiven Prozesses
 * Der korrekte Ausfuehrungszustand ist zu setzen
 * und danach der naechste lauffaehige Prozess zu aktivieren.
 */
void ActivityScheduler::suspend()
{
  KernelLock lock;
  ((Activity*)(this -> active())) -> changeTo(Activity::BLOCKED);
  scheduler.reschedule();
}

/* Explizites Terminieren des angegebenen Prozesses
 * Der Prozesszustand ist korrekt zu setzen
 * und der Prozess aus der Ready-Liste des Schedulers
 * zu entfernen. Falls der aktive Prozess zerstoert wird,
 * ist dem naechsten lauffaehigen Prozess die CPU
 * zuzuteilen.
 */
void ActivityScheduler::kill(Activity* act)
{
  KernelLock lock;

  bool isRunning = act -> isRunning();
  act -> changeTo(Activity::ZOMBIE);

  // suchen aller children und .kill
  Activity* child = (Activity*)(act -> getChildren() -> dequeue());
  while(child) {  // geht rekursiv alle children durch und killt diese
    scheduler.kill(child);
    child = (Activity*)(act -> getChildren() -> dequeue());
  }

  // sollte sich auch bei seinem parent abmelden wenn er im sterben liegt, koennte sonst unschoene ereigneisse passieren lassen
  if (act -> getParent()) {
    act -> getParent() -> getChildren() -> remove(act);
  }

  if (isRunning) { // wenn running reicht ein reschedule
    scheduler.reschedule();
  } else { // sonst loeschen aus der readylist
    scheduler.remove(act);
  }
};

/* Terminieren des aktiven Prozesses,
 * und Wechsel zum naechsten lauffaehigen Prozess
 */
void ActivityScheduler::exit()
{
  // macht das selbe wie kill nur das hier die unterscheidung auf running ueberfluessig waere
  scheduler.kill(((Activity*)scheduler.active()));
};

/* Der aktive Prozess ist, sofern er sich nicht im Zustand
 * Blocked oder Zombie befindet, wieder auf die Ready-Liste
 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle
 * zu übergeben.
 */
void ActivityScheduler::activate(Schedulable* to)
{

  Activity* curr = (Activity*) this -> active();
  Activity* next = (Activity*) to;

  if (next != 0) { // wenn es EIN next gibt
    if(!(curr -> isBlocked()) && !(curr -> isZombie())) {
      // wieder auf ready und ab ist die queue
      curr -> changeTo(Activity::READY);
      curr -> rebirth();
      scheduler.schedule(curr);
    }
    next -> changeTo(Activity::RUNNING);
    dispatch(next);
  } else { // wenn es KEIN next gibt
    if((curr -> isBlocked()) || (curr -> isZombie())) { // gucken ob curr nicht mehr lauffaehig ist
      this -> idle = true;
      while (next == 0) { // nach jedem interrupt gucken ob evtl wieder etwas lauffaehiges in der readyliste steht
        monitor.leave();
        // hier sind die interrupts wieder aktiv und alle wurden abgearbeitet
        CPU::halt();
        monitor.enter();

        next = (Activity*)readylist.getItem(0); // gucken ob nun doch was drinnen ist.
      } // ab hier gibt es ein next
      this -> idle = false;
      next -> changeTo(Activity::RUNNING);
      readylist.dequeue(); // wegwerfen
      dispatch(next);
    } else {
      curr -> rebirth();
      // es gibt kein next aber curr ist noch lauffaehig.
      // somit gibt es hier nichts zu tun
    }
  }
}


//! guckt ob der Prozess schon seine Zeit hatte und zwingt ihn wenn noetig zur Abgabe
void ActivityScheduler::checkSlice() {
  if (!this -> idle) { // gucken ob er einen laufene act hat
    Activity* curr = (Activity*) this -> active();
    curr -> grow(); // da tick = 0 ja auch ein tick ist sollte man ihn auch mitzaehlen

    if (!((curr -> getAge()) < (curr -> quantum()))) { // pruefen ob die zeit schon um ist
      this -> activate((Schedulable*)readylist.dequeue());
    }
  } else { // er hat keine laufene act
    // da activate noch in der while schleife ist muss man hier nichts machen, weil cpu::halt() nach dem clock interrupt wieder aufgehoben wurde
  }
}
