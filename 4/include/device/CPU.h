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

#ifndef CPU_h
#define CPU_h

/*!
 * CPU:	Diese Klasse ist der Softwareprototyp fuer die CPU
 *	Wir benoetigen sie in erster Linie zum Sperren/Zulassen der
 *	Interrupts
 */


//! Assemblerroutinen uebernehmen die eigentliche Arbeit...

extern "C" {
	void int_enable ();
	unsigned int_disable ();
	void cpu_halt ();
  void* get_cr2 ();
}

class CPU {
public:
	/*! Anhalten der CPU bis zum naechsten Interrupt (falls die
  *   Interrupts aktiviert sind sonst fuer immer)
  */
	static void halt () { cpu_halt(); }

	//! Zulassen der Interrupts
	static void enableInterrupts () { int_enable(); }

	/*! Sperren der Interrupts.
	*   Liefert den letzten Interruptstatus zurueck
	*/
	static bool disableInterrupts () { return int_disable(); }

  //! liefert den Wert des CR2 Registers
  static void* getCR2 () { return get_cr2(); }
};
#endif

