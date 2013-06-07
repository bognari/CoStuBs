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

#ifndef Dispatcher_h
#define Dispatcher_h

/*
 * Dispatcher: 	Diese Klasse verwaltet den Zeiger auf den aktuell
 *		laufenden Prozess.
 *
 *	Anmerkung: Hier wird der Mechanismus der CPU-Zuteilung
 *	implementiert, daher ist dies eine Basisklasse
 *	des ActivitySchedulers, der wiederum fuer die strategischen
 *	Zuteilungsentscheidungen zustaendig ist.
 */

#include "thread/Coroutine.h"

class Dispatcher {
public:
  //! Konstruktor der nichts ausfuehrt
	Dispatcher() : running(0)
	{}

	/*! Definieren des ersten Prozesses.
	 *  Wird nur einmal zur Initialisierung aufgerufen!!
	 */
	void init(Coroutine* act) 
	{ 
		running = act; 
	}

	/*! "active" liefert den Zeiger auf den aktiven Prozess.
	*/
	Coroutine* active() 
	{ 
		return running; 
	}

	/*! "dispatch" wird vom ActivityScheduler aufgerufen,
	 *  um vom aktiven zum neu ausgewaehlten Prozess zu wechseln.
	 *  Man beachte die Reihenfolge der Anweisungen, die daraus
	 *  resultiert, dass hier der Kontrollfluss gewechselt wird
	 */
	void dispatch(Coroutine* next)
	{
		Coroutine* curr = running;

		running = next;
		curr -> resume(next);
	}

protected:
  //! die momentan laufene Coroutine
	Coroutine* running;
};

#endif
