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

#ifndef IntLock_h
#define IntLock_h

/*!
 * IntLock: 	Diese Klasse dient dazu,
 *		        innerhalb eines Blockes die Interrupts zu sperren
 *		        und bei Verlassen des Blockes den alten Interruptstatus
 *		        automatisch wiederherzustellen.
 */

#include "device/CPU.h"

class IntLock {
public:
	//! Sperren!
	IntLock()
	{
	  lock();
	}

	//! Restaurieren
	~IntLock()
	{
	  restore();
	}

	//! Sperren!
	void lock()
	{
	  previousState = CPU::disableInterrupts();
	}

	//! Restaurieren
	void restore()
	{
		if(this -> previousState){
			CPU::enableInterrupts();
		}
	}
private:
	//! der alte zustand des interrupt-flags
	unsigned previousState;
};

#endif
