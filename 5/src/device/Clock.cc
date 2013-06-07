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

#include "device/Clock.h"
#include "interrupts/InterruptVector.h"

#include "io/PrintStream.h"
//extern PrintStream out; // debug

extern PIC pic;

#include "thread/ActivityScheduler.h"
extern ActivityScheduler scheduler;

/*! Initialisierung des "Ticks" der Uhr
 *  Standardmaessig setzen wir das
 *  Uhrenintervall auf 20 Millisekunden
 *  und wir bekommen damit 50 Interrupts pro Sekunde
 *
 *  Zum Testen koennt Ihr bei Bedarf einen hoeheren Wert einstellen
 *  Weitere Hinweise zur Implementierung siehe "windup"
 */
Clock::Clock (int us): Gate(Timer), PIT(us)
{
  this -> windup(us);
}


/*! Spaetere Initialisierung...
 *  Hier ist nur im Konstruktor dafuer zu sorgen,
 *  dass sich Gate korrekt initialisieren kann
 */
Clock::Clock (): Gate(Timer), PIT()
{
  this -> tick = 0;
}


/*! Initialisierung des "Ticks" der Uhr
 *  Die Einheit sind Mikrosekunden.
 *  Hier ist der PIT geeignet zu initialisieren
 *  und der PIT beim PIC anzustellen.
 */
void Clock::windup(int us)
{
  this -> interval(us);
  this -> tick = 0;

  pic.enable(PIC::PIT);
}

bool Clock::prologue()
{
  (this -> tick)++;
  pic.ack(this -> getNumber());
  return (true);
}

void Clock::epilogue()
{
  scheduler.checkSlice();
}
