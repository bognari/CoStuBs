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

#ifndef Keyboard_h
#define Keyboard_h

#include "interrupts/Gate.h"
#include "device/CodeTable.h"
#include "device/Key.h"
#include "io/IOPort.h"
#include "io/InputChannel.h"
#include "lib/BoundedBuffer.h"

/*
 * Keyboard: Der Treiber fuer eine MF-II Tastatur
 *
 *
 */
class Keyboard: public Gate, public InputChannel {
private:
	enum Ports{
		DATA = 0x60,
		CTRL = 0x64
	};

	enum KeyboardControls{
		OUTPUT_BIT 	= 0x01,
		INPUT_BIT 	= 0x02,
		AUX_BIT 	= 0x20,
		BREAK_BIT 	= 0x80,
		PREFIX1 	= 0xe0,
		PREFIX2 	= 0xe1,
		SET_LED 	= 0xed,
		SET_SPEED 	= 0xf3,
		ACKNOWLEDGE 	= 0xfa,
		RESET_CODE 	= 0xfc
	};

	enum Mode{
		SHIFT_LEFT 	= 0x0001,
		SHIFT_RIGHT 	= 0x0002,
		ALT_LEFT 	= 0x0004,
		ALT_RIGHT 	= 0x0008,
		CTRL_LEFT 	= 0x0010,
		CTRL_RIGHT 	= 0x0020,
		CAPS_LOCK 	= 0x0040,
		NUM_LOCK 	= 0x0080,
		SCROLL_LOCK 	= 0x0100
	};

	enum Leds{
		SCROLL_LOCK_LED = 0x1,
		NUM_LOCK_LED 	= 0x2,
		CAPS_LOCK_LED 	= 0x4
	};

	enum {
		BUFFER_SIZE = 10
	};


public:
	/**	Setzt den initialen Zustand und meldet die Tastatur als
	 *	Interruptquelle an.
	 */
	Keyboard();

	/**	Die Interruptbehandlungsfunktion.
	 */
	bool prologue();
	void epilogue();

	/**	Diese Methode liefert ein Zeichen aus dem Tastaturpuffer
	 *	zurueck. Diese Methode blockiert, wenn der Puffer leer ist.
	 */
	Key read();

	/**	Diese Methode ist die Implementierung von InputChannel.
	 *	Es werden nur Ascii-zeichen zurueckgegeben.
	 */
	virtual int read(char* data, int size);

private:
	BoundedBuffer<Key,BUFFER_SIZE> buffer;   //Der Tastaturpuffer
	BoundedBuffer<unsigned char, BUFFER_SIZE> key_codes; // key codes fuer den epilogue
	CodeTable codeTable;                    //Abbildung von Scancode -> Zeichen
	unsigned char scanCode;                 //Der letzte von der Tastatur gelesen code
	unsigned mode;                          //Eingabemodus (Shift, Alt, Ctrl)
	unsigned char prefix;                   //von Tastatur gesendeter Prefix, falls gesendet sonst 0
	char leds;                              //Zustand der Tastaturleds

	IOPort8 dataPort; // Ausgabe- (R) u. Eingabepuffer (W)
	IOPort8 ctrlPort; // Status- (R) u. Steuerregister (W)

	/**	Diese Methode bestimmt was getan werden muss,
	 *	wenn Strg-Alt-Entf gedrueckt wurde, ein Prefixcode von
	 *	der Tastatur gelesen wurde, oder eine Taste gedrueckt
	 *	bzw. losgelassen wurde.
	 */
	void analyzeScanCode();

	/**	Behandelt das Loslassen einer Taste.
	 */
	void keyReleased();

	/**	Behandelt das Druecken einer Taste.
	 */
	void keyHit();

	/**	Bestimmt das Zeichen, gemaess der Codetabelle.
	 */
	void determineAsciiCode();

	/**	Fuehrt den software reboot aus.
	 */
	void reboot();

	/**	Stellt die Tastenwiederholrate ein.
	 */
	void setRepeatRate(int speed, int delay);

	/**	Steuert die Leds der Tastatur.
	 */
	void setLed(char led, bool on);


	/**	Hilfsfunktionen fuer den Zugriff auf den Tastaturcontroller
	 */
	void waitForRead();
	void waitForWrite();
};

extern Keyboard keyboard;

#endif
