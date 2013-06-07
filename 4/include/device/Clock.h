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

#ifndef Clock_h
#define Clock_h

/*
 * Clock: Der Treiber fuer die Systemuhr
 *
 *
 * Alle "us" Mikrosekunden wird durch einen Interrupt
 * ein Ticken der Uhr ausgeloest
 */

#include "interrupts/Gate.h"
#include "device/PIT.h"

#include "device/PIC.h"

struct Time
{
  int d;
  int h;
  int m;
  int s;
};

class Clock: public Gate, public PIT {
public:

	/*!	Initialisierung des "Ticks" der Uhr
	 *	Standardmaessig setzen wir das
	 *	Uhrenintervall auf 20 Millisekunden
	 *	und wir bekommen damit 50 Interrupts pro Sekunde
	 *
	 *	Zum Testen koennt Ihr bei Bedarf einen hoeheren Wert einstellen
	 *	Weitere Hinweise zur Implementierung siehe "windup"
	 */
	Clock (int us);


	/*!	Spaetere Initialisierung...
	 *	Hier ist nur im Konstruktor dafuer zu sorgen,
	 *	dass sich Gate korrekt initialisieren kann
	 */
	Clock ();


	/*!	Initialisierung des "Ticks" der Uhr
	 * 	Die Einheit sind Mikrosekunden.
	 * 	Hier ist der PIT geeignet zu initialisieren
	 * 	und der PIT beim PIC anzustellen.
	 */
	void windup(int us);

	/*! Der Interrupt-Handler fuer die Uhr.
	 *	Hier ist der Interrupt am PIC zu bestaetigen
	 *	und die Systemzeit zu aktualisieren.
	 *	Die Systemzeit wird in Uhrenticks gemessen,
	 *	Ihr muesst hier also nur mitzaehlen,
	 *	wie oft die Uhr getickt hat.
	 *
	 *	Ueberpruefe zunaechst die Funktion des Timers
	 *	indem Du jede Sekunde eine Ausgabe an der Bildschirmstelle (0,0)
	 *	in Form eines rotierenden Propellers machst, der sich pro Sekunde
	 *	ein kleines Stueck weiterdreht, wie der Sekundenzeiger einer Uhr.
	 *	Der Propeller besteht aus der Zeichenfolge '/', '-', '\\', '|',
	 *	d.h. nach 4 Sekunden ist eine komplette Umdrehung geschafft.
	 *
	 *	Achtung: Kommentiert alle anderen Ausgaben Eures Testprogrammes
	 *	aus, sonst seht Ihr nichts!
	 *
	 *	Wenn der Uhrentest erfolgreich verlaufen ist, kommentiert
	 *	den Propeller wieder aus und ruft stattdessen
	 *	die "checkSlice" Methode des Schedulers auf,
	 *	um diesen ggf. zum praeemptiven Rescheduling zu veranlassen.
	 */
	void handle();

	/*! Liefert die Systemzeit in Ticks zurueck
	 *	Kann hier "inline" implementiert werden
	 */
	int ticks()
	{
	  return this -> tick;
	}

	/*! gibt ein Zeit Objekt zurueck
	 *
	 */
	void getTime(Time*);

private:
	//! system ticks
	int tick;
};

extern Clock clock;

#endif
