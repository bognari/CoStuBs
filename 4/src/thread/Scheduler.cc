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

#include "thread/Scheduler.h"

// extern Printstream out

/*
 * Scheduler:   Diese Klasse implementiert die Zuteilungsstrategie
 *    fuer die CPU.
 *
 *  Anmerkung: Hier wird ein einfacher First-Come-First-Served
 *  Algorithmus implementiert, der sich auf eine
 *  ready-liste stuetzt, in dem alle lauffaehigen Prozesse
 *  miteinander verkettet sind.
 */

#include "interrupts/IntLock.h"

// Einfuegen eines neuen Elements in die Ready-Liste.
void Scheduler::schedule(Schedulable* sched)
{
  IntLock lock;

  this -> readylist.enqueue(sched);
}

// Entfernen eines Elements von der Ready-Liste.
void Scheduler::remove(Schedulable* sched)
{
  IntLock lock;

  this -> readylist.remove(sched);
}


// Aktiviert das vorderste der Liste mittels activate.
void Scheduler::reschedule()
{
  IntLock lock;

  this -> activate((Schedulable*)readylist.dequeue());
}
