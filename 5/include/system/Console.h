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

#ifndef Console_h
#define Console_h

#include "io/InputChannel.h"
#include "io/OutputChannel.h"
#include "system/Semaphore.h"
#include "system/Thread.h"

//#include "io/PrintStream.h"
// extern PrintStream out;
/**
 *  Console:	Die Systemkonsole
 */
class Console: 	public InputChannel, public OutputChannel{
public:
	Console(InputChannel& input, OutputChannel& output) : input(input), output(output), sema(Semaphore(1))
	{}

	/** 	Konsole reservieren
	 */
	void attach();

	/** 	Konsole wieder freigeben
	 */
	void detach();

	/** 	Daten auf der Console ausgeben
	 */
	virtual int write(const char* data, int size);

	/** 	Jedes von der Tastatur eingelesene Zeichen
	 * 	soll auf dem Bildschirm dargestellt werden (Echo Funktion!)
	 * 	Wenn ein '\n' erkannt wurde oder bereits "size" Zeichen
	 *	gelesen wurden, ist eine Zeile zuende und read() kehrt zurueck.
	 *	Alle gelesenen Ascii-zeichen sind in den Puffer einzutragen
	 *	und zaehlen als gueltiges Zeichen!
	 */
	virtual int read(char* data, int size);


private:

  /**   Liefert das naechste Zeichen aus dem Eingabepuffer zurueck.
   */
  char read();

	InputChannel &input;
	OutputChannel &output;
  Semaphore sema;
};

#endif
