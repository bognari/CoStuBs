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

#ifndef Scheduler_h
#define Scheduler_h

/*
 * Scheduler: 	Diese Klasse implementiert die Zuteilungsstrategie
 *		fuer die CPU.
 *
 *	Anmerkung: Hier wird ein einfacher First-Come-First-Served
 *	Algorithmus implementiert, der sich auf eine
 *	ready-liste stuetzt, in dem alle lauffaehigen Prozesse
 *	miteinander verkettet sind.
 */

#include "lib/Queue.h"
#include "thread/Schedulable.h"

class Scheduler {
public:

	//! Einfuegen eines neuen Elements in die Ready-Liste.
	void schedule(Schedulable* sched);

	//! Entfernen eines Elements von der Ready-Liste.
	void remove(Schedulable* sched);

	//! Aktiviert das vorderste der Liste mittels activate.
	void reschedule();

protected:
	/*! Diese pur-virtuelle Methode stellt die Schnittstelle zum
	 *  ActivityScheduler dar, der diese Klasse erweitert. Siehe
	 *  die Beschreibung dort.
	 */
	virtual void activate(Schedulable* to) = 0;

	//! Die Ready-Liste
	Queue readylist;

};

#endif
