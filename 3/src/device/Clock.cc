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
extern PrintStream out; // debug

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

/*! Der Interrupt-Handler fuer die Uhr.
 *  Hier ist der Interrupt am PIC zu bestaetigen
 *  und die Systemzeit zu aktualisieren.
 *  Die Systemzeit wird in Uhrenticks gemessen,
 *  Ihr muesst hier also nur mitzaehlen,
 *  wie oft die Uhr getickt hat.
 *
 *  Ueberpruefe zunaechst die Funktion des Timers
 *  indem Du jede Sekunde eine Ausgabe an der Bildschirmstelle (0,0)
 *  in Form eines rotierenden Propellers machst, der sich pro Sekunde
 *  ein kleines Stueck weiterdreht, wie der Sekundenzeiger einer Uhr.
 *  Der Propeller besteht aus der Zeichenfolge '/', '-', '\\', '|',
 *  d.h. nach 4 Sekunden ist eine komplette Umdrehung geschafft.
 *
 *  Achtung: Kommentiert alle anderen Ausgaben Eures Testprogrammes
 *  aus, sonst seht Ihr nichts!
 *
 *  Wenn der Uhrentest erfolgreich verlaufen ist, kommentiert
 *  den Propeller wieder aus und ruft stattdessen
 *  die "checkSlice" Methode des Schedulers auf,
 *  um diesen ggf. zum praeemptiven Rescheduling zu veranlassen.
 */
void Clock::handle()
{
  pic.ack();

  this -> tick++;
// test von oben
//  if (((this -> ticks()) % (1000000 / (this -> interval()))) == 0) { // damit er nicht "flackert"
//    switch((this -> ticks() / (1000000 / (this -> interval()))) % 4) {
//      case 0: out.print("\r/"); break;
//      case 1: out.print("\r-"); break;
//      case 2: out.print("\r\\"); break;
//      case 3: out.print("\r|"); break;
//    }
//    Time time;
//    this -> getTime(&time);
//    out.print("   ");
//    out.print(time.d);
//    out.print(" : ");
//    if (time.h < 10) {
//      out.print(0);
//    }
//    out.print(time.h);
//    out.print(" : ");
//    if (time.m < 10) {
//      out.print(0);
//    }
//    out.print(time.m);
//    out.print(" : ");
//    if (time.s < 10) {
//      out.print(0);
//    }
//    out.print(time.s);
//    out.print("       ");
//    if((time.s % 2) == 0) {
//      out.print("TICK");
//    } else {
//      out.print("TACK");
//    }
//  }
//  out.print("INTERRUPT-CLOCK ");
//  out.print(this -> ticks());
//  out.println();
  scheduler.checkSlice();
}

void Clock::getTime(Time* time)
{
  int tick = (this -> ticks()) / (1000000 / (this -> interval()));
  time -> d = tick / 86400;
  time -> h = (tick % 86400) / 3600;
  time -> m = (tick % 3600) / 60;
  time -> s = tick % 60;
}
