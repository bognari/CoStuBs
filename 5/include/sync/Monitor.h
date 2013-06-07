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

#ifndef Monitor_h
#define Monitor_h

#include "lib/Queue.h"
#include "interrupts/Gate.h"

/** 	Die Monitorimplementierung fuer den Kern.
 *	Beachte das der Monitor synchron (Anwendung) als auch asynchron
 * 	(Interrupt) betreten werden kann.
 */
class Monitor {
public:
	/** 	Initial ist der Monitor gesperrt. Erst nach der Initialisierung des Systems
	 *	darf er freigeschaltet werden.
	 */
	Monitor() : free(false)
	{}

	/** 	Die Methode zum betreten, sperren des Monitors, aus der Anwendung heraus.
	 */
	void enter()
	{
	  free = false;
	}

	/** 	Wenn der Monitor verlassen wird, muessen alle ausstehenden Epiloge sofort
	 *	abgearbeitet werden.
	 */
	void leave();

	bool isFree()
	{
		return (this -> free);
	}

	/** 	Diese Methode wird waehrend der Interruptbehandlung aufgerufen, wenn ein
	 *	Epilog abgearbeitet werden muss. Ist der Monitor besetzt muss der Epilog
	 *	in die Warteschlange eingereiht werden, darf aber maximal einmal in der
	 *	Warteschlange sein.
	 */
	void runEpilogue(Gate *gate);

private:
	bool free;	// Monitor-Sperre
	Queue deferred; // Liste der vermerkten Epiloge
};

extern Monitor monitor;

#endif
