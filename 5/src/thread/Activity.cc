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

#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"
#include "sync/KernelLock.h"

/*
 * Activity:
 * Diese Klasse implementiert kooperative aktive Objekte
 * fuer Co-Stubs.
 *
 * Anmerkung:
 * Im Gegensatz zur Coroutine wird eine
 * Instanz der Klasse Activity von einem Scheduler verwaltet.
 * Ein explizites Umschalten zu einer anderen Coroutine
 * wird damit hinfaellig.
 */

/* Aufsetzen eines Threads, der initiale Zustand ist "Blocked",
 * da der Thread erst laufen darf, wenn der spezielle Konstruktor
 * der abgeleiteten Klasse abgearbeitet ist.
 * Die Aktivierung
 * erfolgt von der abgeleiteten Klasse mittels "wakeup".
 */

Activity::Activity(void* tos, int time, bool isChild): Schedulable(time), Coroutine(tos), state(BLOCKED), parent(0), children(), blocked(0)
{ // da er eien eigenen stack hat ist er child des grade laufenden
  if (isChild) {
    this -> parent = (Activity*)scheduler.active();
    this -> parent -> children.enqueue(this); // fuegt den Children zum Parent hin zu
  }
}

/* Verpacken des aktuellen Kontrollflusses als Thread.
 * Wird nur für den Hauptkontrollfluss "main" benötigt.
 * Es wird hier kein Stack initialisiert.
 * Beachte das Activity wegen der Vererbungsbeziehung von
 * Coroutine abstrakt ist. Bei Bedarf muss "body" direkt
 * aufgerufen werden.
 */
Activity::Activity(int time, bool isChild): Schedulable(time), Coroutine(), state(BLOCKED), parent(0), children(), blocked(0) // arbeitet auf dem mainstack also ist er cheffe
{
  if (isChild) {
      this -> parent = (Activity*)scheduler.active();
      this -> parent -> children.enqueue(this); // fuegt den Children zum Parent hin zu
  }
  this -> state = READY;
  scheduler.start(this);
}
/* Im Destruktor muss ein explizites Terminieren dieser Aktivitaet erfolgen.
 * Das muss geschehen, da aufgrund der Aufrufreihenfolge von
 * Destruktoren bereits der abgeleitete Teil des Activity-Objekts zerstoert
 * wurde und diese Aktivitaet daher keine Laufzeit mehr erhalten darf.
 * Das Warten auf die Beendigung (mittels join()) muss im Destruktor der
 * von Activity am weitesten abgeleiteten Klasse erfolgen.
 */
Activity::~Activity()
{
  //wenn er hier ist ist der prozess eh nur noch muell deswegen .kill
  scheduler.kill(this);
}

/* Veranlasst den Scheduler, diese Aktivitaet zu suspendieren.
 */
void Activity::sleep()
{
  // wenn er laeuft dann auf blocked und reschedule
  switch (this -> state) {
    case RUNNING  : scheduler.suspend(); break;
    case READY    : {
      this -> state = BLOCKED;
      scheduler.remove(this);
    }; break;
    default : { }; break;
  }
}

/* Veranlasst den Scheduler, diese Aktivitaet aufzuwecken.
 */
void Activity::wakeup()
{
  if(this -> isBlocked()) { // kann ja nur wakeup auf einen blocked machen
    this -> state = READY;
    scheduler.schedule(this);
  }
}

/* Diese Aktivitaet gibt die CPU vorruebergehend ab.
 */
void Activity::yield()
{
  scheduler.reschedule();
}

/* Diese Aktivitaet wird terminiert. Hier muss eine eventuell
 * auf die Beendigung wartende Aktivität geweckt werden.
 */
void Activity::exit()
{
  int i = 0;
  Activity* child = (Activity*)(this -> children.getItem(i));
  while (child){ // wenn er Children hat dann soll er waren bis diese fertig sind
    if (!child -> isZombie()) {
      this -> sleep();
    }
    i++;
    child = (Activity*)(this -> children.getItem(i));
  }

  // wenn er einen anderen geblockt hatte da er ihm ans leder wollte darf er nun wieder
  if (this -> blocked) {
    if (this -> blocked -> isBlocked()) { // nicht das er selber schonmal gekillt wurde
      this -> blocked -> wakeup();
    }
    this -> blocked = 0;
  }

  // Testet ob er selber das letzte laufene Child seines Parents war, wenn ja dann starte ihn wieder
  if (this -> parent) {
    if (this -> parent -> isBlocked()) {
      i = 0;
      bool islast = true;
      child = (Activity*)(this -> parent -> children.getItem(i));
      while (child && islast) { // sucht alle Geschwister und guckt ob einer davon kein Zombie ist
        if ((!(child -> isZombie())) && (child != this)) {
          islast = false;
        }
        i++;
        child = (Activity*)(this -> parent -> children.getItem(i));
      }
      if (islast) { // wenn er der letzte war dann wakeup den Parent
        this -> parent -> getChildren() -> remove(this);
        this -> parent -> wakeup();
      }
    }
  }
  // nun wird er zum Zombie und bekommt nie wieder die CPU
  scheduler.exit();
}

/* Der aktuelle Prozess wird solange schlafen gelegt, bis der
 * Prozess auf dem join aufgerufen wird beendet ist. Das
 * Wecken des wartenden Prozesses übernimmt exit.
 */
void Activity::join()
{
  // testen ob der Prozess schon Zombie war, wenn ja war er schon fertig
  if (!(this -> isZombie())) {
    this -> blocked = (Activity*)scheduler.active();
    this -> blocked -> sleep();
  }
  // wenn er schon fertig war darf er auch sterben.
  // also wird dann der destruktor weiter ausgefuehrt und der prozess ist nur noch muell
}

