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

#ifndef ActivityScheduler_h
#define ActivityScheduler_h

#include "io/PrintStream.h"
extern PrintStream out; // debug

/*
 * ActivityScheduler: 	Diese Klasse implementiert die Zustandsverwaltung
 * 			fuer Activities
 *
 */

#include "lib/Queue.h"
#include "thread/Scheduler.h"
#include "thread/Activity.h"
#include "thread/Dispatcher.h"
#include "interrupts/IntLock.h"

class ActivityScheduler: public Dispatcher, public Scheduler {
public:
	ActivityScheduler() : idle(false) {};

	/*! Initialisieren der ersten Aktivitaet, des Schedulers
	 *  und des Dispatchers.
	 *  Wird nur einmal aufgerufen.
	 */
	void start(Activity* act)
	{
    act -> changeTo(Activity::RUNNING);
    this -> init(act);
	};

	/*! Suspendieren des aktiven Prozesses
	 *  Der korrekte Ausfuehrungszustand ist zu setzen
	 *  und danach der naechste lauffaehige Prozess zu aktivieren.
	 */
	void suspend();

	/*! Explizites Terminieren des angegebenen Prozesses
	 *  Der Prozesszustand ist korrekt zu setzen
	 *  und der Prozess aus der Ready-Liste des Schedulers
	 *  zu entfernen. Falls der aktive Prozess zerstoert wird,
	 *  ist dem naechsten lauffaehigen Prozess die CPU
	 *  zuzuteilen.
	 */
	void kill(Activity*);

	/*! Terminieren des aktiven Prozesses,
	 *  und Wechsel zum naechsten lauffaehigen Prozess
	 */
	void exit();


  //! guckt ob der Prozess schon seine Zeit hatte und zwingt ihn wenn noetig zur Abgabe
  void checkSlice();

  //! gibt idle aus
  bool isIdle()
  {
    return this -> idle;
  }


protected:
	/*! Der aktive Prozess ist, sofern er sich nicht im Zustand
	 *  Blocked oder Zombie befindet, wieder auf die Ready-Liste
	 *  zu setzen. Danach ist "to" mittels dispatch die Kontrolle
	 *  zu uebergeben.
	 */
	virtual void activate(Schedulable*);

private:
  volatile bool idle;
};

extern ActivityScheduler scheduler;

#endif
