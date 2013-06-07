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

#ifndef Schedulable_h
#define Schedulable_h

/*!
 * Schedulable: Diese Klasse implementiert ein Element
 *		          der Ready-Liste des Schedulers
 *
 *	Anmerkung: Die Klasse ist von Chain abgeleitet,
 *	damit Instanzen dieser Klasse verkettet werden koennen.
 *	Hier wuerden typischerweise Informationen
 *	wie prozesspezifische Laufzeitstatistiken,
 *	Prioritaeten etc. verwaltet werden.
 *
 */

#include "lib/Chain.h"

class Schedulable: public Chain {
public:
	Schedulable(int slice = 1) : Chain(), ticks(0)
	{ 
		quantum(slice); 
	}

//! setzt die zeit die ihm zusteht
	void quantum(int slice)
	{ 
		this -> slice = slice;
	}

//! gibt die zeit die ihm zusteht aus
	int quantum()
	{ 
		return slice;
	}

//! ticks + 1
	void tickUp()
	{
	  (this -> ticks)++;
	}

//! ticks = 0
	void tickNull()
	{
	  this -> ticks = 0;
	}

//! gibt ticks aus
	int getTick()
	{
	  return this -> ticks;
	}

private:
	//! wie viel zeit er bekommt
	int slice;
	//! wie viel zeit er schon hatte
	int ticks;
};

#endif
