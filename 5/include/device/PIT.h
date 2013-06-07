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

#ifndef PIT_h
#define PIT_h

/*!
 * PIT: Der Treiber fuer den Programmable Interrupt Timer
 *
 *	Wenn der PIT richtig programmiert wurde,
 *	liefert er alle "us" Mikrosekunden einen Interrupt
 */

#include "io/IOPort.h"

class PIT {
public:
	/*! Initialisiert den Timers, sodass alle "us" Mikrosekunden ein Interrupt
	  * ausgeloest wird
	  */
	PIT (unsigned short int us);

	/*! Default-Konstruktor. Das Interval wird spaeter
	  * mit der interval-Methode initialisiert
	  */
	PIT ();

	/*! Setzt das Timer-Intervall, sodass alle "us" Mikrosekunden ein Interrupt
	  * ausgeloest wird.
	  *
	  * BEACHTE: Hier muss die Hardware korrekt programmiert werden.
	  * Naeheres steht in der Web-Dokumentation.
	  */
	void interval (unsigned short int us);

	/*! Gibt den Timer-Intervall zurueck.
	  * Hier wird der zuletzt gesetzte Intervallwert zurueckgeliefert. Dies kann
	  * kann ohne Hardware-Programmierung geschehen.
	  */
	int interval ();

private:
	enum Values
	{
	  /*! Dauer eines Zaehlticks in ns = 1000000 / (ca 1,2MHz)*/
	  TIME_BASE = 838,
		//! = 00|11|010|0 = timer 1 | werte nach einander | modus 2 | binaer
		TIMER_CONF = 0x34
	};

	// Die I/O Ports des PIC
	enum Ports
	{
	  CONTROL_PORT 	= 0x43,
	  DATA_PORT 	= 0x40
	};

	IOPort8 control;
	IOPort8 data;

	//! das intervall der ticks
	unsigned short int interv;
};

extern PIT pit;
#endif
