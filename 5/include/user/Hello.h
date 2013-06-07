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

#ifndef Hello_h
#define Hello_h

#include "system/Thread.h"
#include "system/Console.h"

class Hello: public Thread {
public:
	enum Config
	{
	  LINE_SIZE = 512
	};

	/** Konstruktor mit den bekannten Argumenten..
	 */
	Hello(const char* name, int runs, int slice, void* sp,Console& console);

	/* Im Destruktor muss auf die Beendigung von "body()"
	 * gewartet werden!
	 */
	~Hello();

	virtual void run();

private:

	int runs;		// Anzahl der Durchlaeufe
	const char* name; 	// Name dieses Threads

	char line[LINE_SIZE];  	// Zeilenpuffer
	Console& console;
};

#endif
