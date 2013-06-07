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

#ifndef InputChannel_h
#define InputChannel_h

/**	InputChannel:
 * 	Diese Klasse ist die Abstraktion fuer einen Eingabekanal.
 *
 *	Beachte, dass die 'read'- Methode
 *	eine so genannte pure virtuelle Methode ist,
 *	fuer die hier keine Implementierung
 *	angegeben wird. Daher ist InputChannel
 *	eine sogenannte abstrakte Klasse.
 */

class InputChannel {
public:
	/** Diese Methode kehrt zurueck, wenn die Anzahl der mit size angegebenen
	 *  Zeichen erreicht ist oder ein '\n' vorliegt. Es werden alle
	 *  Ascii-zeichen in den Datenbereich geschrieben.
	 */
	virtual int read(char* data, int size) = 0;
};

#endif
