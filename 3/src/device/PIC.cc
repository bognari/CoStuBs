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

#include "device/PIC.h"

void PIC::enable (int num)
{
	if (num < 8) // PIC 1
		imr1.write (imr1.read () & (~(1 << num)));
	else         // PIC 2
		imr2.write (imr2.read () & (~(1 << (num-8))));
}


void PIC::disable (int num)
{
	if (num < 8) // PIC 1
		imr1.write (imr1.read () | (1 << num));
	else         // PIC 2
		imr2.write (imr2.read () | (1 << (num-8)));
}

void PIC::ack (int num)
{
	ack();
}

void PIC::ack ()
{
	ctrl1.write (ACK); // Unspez. EOI-Befehl an PIC 1
	ctrl2.write (ACK); // Unspez. EOI-Befehl an PIC 2
}
