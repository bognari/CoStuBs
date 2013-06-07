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

#ifndef CodeTable_h
#define CodeTable_h

/** Die Code Tabelle beschreibt die Umsetzung von Scancodes der Tastatur
 *  auf ASCII-Zeichen. Weiterhin wird festgelegt welche Scancodes als
 *  Steuerzeichen betrachtet werden, und nicht in ein ASCII-Zeichen
 *  umgesetzt werden.
 */
struct CodeTable {
public:

	/** Hier werden Zeichen definiert, welche nicht zu einem AsciiZeichen
	 *  umgewandelt werden sollen, da sie als Steuerzeichen dienen.
	 */
	enum {
		CTRL 		    = 29,
		SHIFT_LEFT 	= 42,
		SHIFT_RIGHT = 54,
		ALT 		    = 56,
		CAPS_LOCK 	= 58,
		NUM_LOCK 	  = 69,
		SCROLL_LOCK = 70,
		POS1 		    = 71,
		UP 		      = 72,
		PAGE_UP 	  = 73,
		LEFT 		    = 75,
		RIGHT 		  = 77,
		END 		    = 79,
		DOWN 		    = 80,
		PAGE_DOWN 	= 81,
		INS 		    = 82,
		DEL 		    = 83
	};

	CodeTable()
	{
		lookup[CTRL] = true;
		lookup[SHIFT_LEFT] = true;
		lookup[SHIFT_RIGHT] = true;
		lookup[ALT] = true;
		lookup[CAPS_LOCK] = true;
		lookup[NUM_LOCK] = true;
		lookup[SCROLL_LOCK] = true;
		lookup[POS1] = true;
		lookup[UP] = true;
		lookup[PAGE_UP] = true;
		lookup[LEFT] = true;
		lookup[RIGHT] = true;
		lookup[END] = true;
		lookup[DOWN] = true;
		lookup[PAGE_DOWN] = true;
		lookup[INS] = true;
		lookup[DEL] = true;
	}

	static bool isControl(unsigned char scanCode)
	{
		return (lookup[scanCode]);
	}

	static const unsigned char normalAscii[];
	static const unsigned char shiftAscii[];
	static const unsigned char strgAscii[];
	static const unsigned char altAscii[];
	static const unsigned char numblockAscii[];

private:
	static bool lookup[];
};

#endif

