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

#ifndef PrintStream_h
#define PrintStream_h

#include "io/OutputChannel.h"

/*
 * PrintStream: Diese Klasse ist aehnlich der Java-PrintStream Klasse
 *    Sie konvertiert u.A. numerische Werte in sichtbare Zeichen
 *    und gibt Sie auf dem im Konstruktor spezifizierten
 *    Ausgabekanal aus.
 *    Daraus ergeben sich 2 Teilaufgaben:
 *
 *    1. Die Feststellung der Ziffern einer Zahl
 *    2. Die Umwandlung der Ziffern in darstellbare Zeichen
 *
 *    Man beachte, dass diese Klasse unabhaengig
 *    von dem tatsaechlich verwendeten Ausgabekanal arbeitet.
 *
 *    Anmerkung: Diese Klasse werden wir spaeter noch in
 *    C++ konforme Ausgabe umwandeln.
 */

class PrintStream {
private:
  //! Basen fuer die Zahlensysteme
  enum Base {
    BINARY = 2,
    DECIMAL = 10,
    HEX = 16
  };
  
public:
  PrintStream(OutputChannel* chan): channel(*chan){ };
  PrintStream(OutputChannel& chan): channel(chan){ };
  
  //! Ausgabe eines mit einem NULL-Byte terminierten Strings
  void print(const char* str);
  //! Ausgabe eines Char
  void print(char ch);
  //! Ausgabe eines Char und NL
  void println(char c);
  
  //! Ausgabe eines Strings mit anschliessendem Zeilenvorschub
  void println(const char* str);
  
  //! Zeilenvorschub
  void println();
  
  /*! numerische Werte werden zur Basis 'base' Ausgegeben
  *   implementiere die Basen 2, 10 und 16
  */
  void print(int x, int base = DECIMAL);
  void print(unsigned x, int base = DECIMAL);
  
  //! Zeigertypen werden immer zur Basis 16 ausgegeben!
  void print(void* p);
  
private:
  //! Ausgabechannel
  OutputChannel& channel;
};

#endif
