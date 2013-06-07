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

#include "device/PIT.h"

  /*! Initialisiert den Timers, sodass alle "us" Mikrosekunden ein Interrupt
    * ausgeloest wird
    */
  PIT::PIT (int us): control(CONTROL_PORT), data(DATA_PORT)
  {
    this -> interval(us);
  }

  /*! Default-Konstruktor. Das Interval wird spaeter
    * mit der interval-Methode initialisiert
    */
  PIT::PIT (): control(CONTROL_PORT), data(DATA_PORT) {}

  /*! Setzt das Timer-Intervall, sodass alle "us" Mikrosekunden ein Interrupt
    * ausgeloest wird.
    *
    * BEACHTE: Hier muss die Hardware korrekt programmiert werden.
    * Naeheres steht in der Web-Dokumentation.
    */
  void PIT::interval (int us)
  {
    this -> interv = us;
    this -> control.write(TIMER_CONF);
    unsigned short int _us = (unsigned) us;
    _us = _us * TIME_BASE;
    this -> data.write((unsigned char)_us); // unteres byte
    this -> data.write(((unsigned char)(_us >> 8))); // oberes byte
  }

  /*! Gibt den Timer-Intervall zurueck.
    * Hier wird der zuletzt gesetzte Intervallwert zurueckgeliefert. Dies kann
    * kann ohne Hardware-Programmierung geschehen.
    */
  int PIT::interval ()
  {
    return this -> interv;
  }
