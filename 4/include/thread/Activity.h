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

#ifndef Activity_h
#define Activity_h

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

#include "thread/Schedulable.h"
#include "thread/Coroutine.h"
#include "lib/Queue.h"

#include "io/PrintStream.h"

extern PrintStream out; // debug

class Activity: public Schedulable, public Coroutine {
public:
	/*! Die logischen Ausfuehrungszustaende
	 *  fuer diese Aktivitaet
	 */
	enum State
	{
		BLOCKED,	//Prozesse die auf etwas warten
		READY,      	//Prozesse die aktiviert werden kodnnen
		RUNNING,	//Status des aktiven Prozesses
		ZOMBIE		//Kindprozesse die vor den Eltern beendet werden
	};

	/*! Aufsetzen eines Threads, der initiale Zustand ist "Blocked",
	 *  da der Thread erst laufen darf, wenn der spezielle Konstruktor
	 *  der abgeleiteten Klasse abgearbeitet ist. Die Aktivierung
	 *  erfolgt von der abgeleiteten Klasse mittels "wakeup".
	*/
	Activity(void*, int time = 1);

	/*! Verpacken des aktuellen Kontrollflusses als Thread.
	 *  Wird nur fuer den Hauptkontrollfluss "main" benoetigt.
	 *  Es wird hier kein Stack initialisiert.
	 *  Beachte das Activity wegen der Vererbungsbeziehung von
	 *  Coroutine abstrakt ist. Bei Bedarf muss "body" direkt
	 *  aufgerufen werden.
	 */
	Activity(int time = 1);

	/*! Im Destruktor muss ein explizites Terminieren dieser Aktivitaet erfolgen.
	 *  Das muss geschehen, da aufgrund der Aufrufreihenfolge von
	 *  Destruktoren bereits der abgeleitete Teil des Activity-Objekts zerstoert
	 *  wurde und diese Aktivitaet daher keine Laufzeit mehr erhalten darf.
	 *  Das Warten auf die Beendigung (mittels join()) muss im Destruktor der
	 *  von Activity am weitesten abgeleiteten Klasse erfolgen.
	 */
	virtual ~Activity();

	/*! Veranlasst den Scheduler, diese Aktivitaet zu suspendieren.
	 */
	void sleep();

	/*! Veranlasst den Scheduler, diese Aktivitaet aufzuwecken.
	 */
	void wakeup();

	/*! Diese Aktivitaet gibt die CPU vorruebergehend ab.
	 */
	void yield();

	/*! Diese Aktivitaet wird terminiert. Hier muss eine eventuell
	 *  auf die Beendigung wartende Aktivitaet geweckt werden.
	 */
	void exit();

	/*! Der aktuelle Prozess wird solange schlafen gelegt, bis der
	 *  Prozess auf dem join aufgerufen wird beendet ist. Das
	 *  Wecken des wartenden Prozesses uebernimmt exit.
	 */
	void join();

	// Folgende Methoden duerfen "inline" implementiert werden

	/*! Aendern des Ausfuehrungszustandes. Diese Methode sollte nur vom
	 *  Scheduler verwendet werden.
	 */
	void changeTo(State state)
  {
    this -> state = state;
  }

	//! Ausfuehrungszustand abfragen.
	bool isBlocked()
	{
    return (this -> state == BLOCKED);
	}

  //! Ausfuehrungszustand abfragen.
	bool isReady()
	{
    return (this -> state == READY);
	}

  //! Ausfuehrungszustand abfragen.
	bool isRunning()
	{
    return (this -> state == RUNNING);
	}

  //! Ausfuehrungszustand abfragen.
	bool isZombie()
	{
    return (this -> state == ZOMBIE);
	}

  //! gibt den Parent aus
  Activity* getParent()
  {
    return this -> parent;
  }
  
  Queue* getChildren()
  {
    return &(this -> children);
  }

private:
  //! Status der Aktivitaet
  State state;
  //! Parent der Aktivitaet
  Activity* parent;
  //! Children der Aktivitaet
  Queue children;
};

#endif
