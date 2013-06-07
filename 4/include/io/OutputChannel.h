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

#ifndef OutputChannel_h
#define OutputChannel_h

/**
 * OutputChannel:
 * Diese Klasse ist die Abstraktion eines Ausgabekanals.
 *
 * Beachte, dass die 'write'- Methode
 * eine so genannte pure virtuelle Methode ist,
 * fuer die hier keine Implementierung
 * angegeben wird. Daher ist OutputChannel
 * eine sogenannte abstrakte Klasse.
 *
 * Man beachte:
 * Unter den auszugebenden Zeichen befinden
 * sich sogenannte Steuerzeichen, die geeignet
 * zu interpretieren sind.
 * Z.B. newline, carriage return, backspace usw.
 *
 */

class OutputChannel {
public:
	/*! write ist hier nicht definiert
	*   erst abgeleitete Klassen implementieren diese Methode
  */
  virtual int write(const char* data, int size) = 0;

	/*! Methode zur Ausgabe einzelner Zeichen
	*   ... aus reiner Bequemlichkeit
  */
  int write(char c)
	{
		return write(&c, sizeof(c));
	}
};

#endif
