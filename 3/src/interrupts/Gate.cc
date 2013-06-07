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

#include "interrupts/Gate.h"
#include "interrupts/PanicGate.h"
#include "interrupts/PageFaultGate.h"

PanicGate panicGate;
PageFaultGate pageFaultGate;

#include "interrupts/InterruptGuardian.h"
extern InterruptGuardian interruptGuardian;

/*!
 * Gate: Ein Trap/Interrupt Tor
 *
 *  Alle Treiber, die Geraete mit Interrupts steuern
 *  muessen fuer jeden Interrupt ein Gate-Objekt anlegen.
 *  Die Gate-Objekte tragen sich selber in die logische
 *  Interrupt-Tabelle ein.
 *  Sobald dies geschehen ist, werden alle an diesem Gate
 *  auftretenden Interrupts ueber die handle()-Methode
 *  dem Treiber mitgeteilt.
 *
 *  Achtung: Gates muessen definiert sein,
 *  *bevor* der zugehoerige Interrupt zugelassen wird!!!!
 */

//! Definition eines Gates fuer Vektornummer "num"
Gate::Gate(int num)
{
	this -> num = num;
	if (num > 0) {
		interruptGuardian.registerGate(this, num);
	}
}

//!  Automatisches Abmelden des Gates
Gate::~Gate()
{
	if (num > 0) {
		interruptGuardian.registerGate(&panicGate, num);
	}
}
