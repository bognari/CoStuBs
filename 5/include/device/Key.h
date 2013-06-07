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

#ifndef Key_h
#define Key_h

/** Die Klasse Key beschreibt ein logisches Zeichen,
 *  das heisst ein ASCII-Zeichen oder ein Steuerzeichen.
 */
class Key {
public:
	enum Type {
		CTRL,
		ASCII
	};

	/** Diese Methode initialisiert das Zeichen als Ascii-Zeichen.
	 */
	void setAscii(unsigned char ascii)
	{
		type = ASCII;
		value = ascii;
	}

	/** Diese Methode initialisiert das Zeichen als Steuerzeichen.
	 */
	void setControl(unsigned char control)
	{
		type = CTRL;
		value = (unsigned char)control;
	}

	char getValue()
	{
		return (this -> value);
	}

	bool isAscii()
	{
		return ((this -> type) == ASCII);
	}

private:
	Type type;
	unsigned char value;
};

#endif

