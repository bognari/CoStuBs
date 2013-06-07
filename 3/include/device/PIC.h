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

#ifndef PIC_h
#define PIC_h

/*!
 * PIC: Diese Klasse ist der Treiber fuer den
 *	    Programmable Interrupt Controler (PIC)
 *
 *	Genaugenommen werden hier zwei kaskadierte PICs behandelt
 */


#include "io/IOPort.h"

class PIC {
public:

	//! die Interrupt-Quellen von Co-Stubs
  enum Interrupts
	{
    PIT	 = 0,	// Programmable Interrupt Timer (PIT)
		KEYBOARD = 1	// Tastatur
	};

	PIC(): 	imr1(IMR1), imr2(IMR2), ctrl1(CTRL1), ctrl2(CTRL2) {}

	//! Anstellen von Interrupt "num"
	void enable (int num);

	//! Abstellen von Interrupt "num"
	void disable (int num);

	//! Die Behandlung von Interrupt "num" bestaetigen
	void ack (int num);

	//! Unspezifische Bestaetigung des aktuellen Interrupts
	void ack ();

private:
	enum Ports
	{
	  IMR1 	= 0x21,	//! Interrupt Mask Register von PIC 1
	  IMR2 	= 0xa1,	//! " PIC2
	  CTRL1 	= 0x20,	//! Interrupt Control Register von PIC 1
	  CTRL2 	= 0xa0	//! " PIC 2
	};

	enum Commands
	{
		ACK	= 0x20	//! Bestaetigung fuer alle Interr.
	};

	IOPort8 imr1;
	IOPort8 imr2;
	IOPort8 ctrl1;
	IOPort8 ctrl2;
};

extern PIC pic;

#endif
