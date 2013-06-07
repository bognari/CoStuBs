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

#ifndef Background_h
#define Background_h

#include "system/Thread.h"
#include "system/Environment.h"

// Ein Hintergrundprozess, der einfach mitlaeuft ...

class Background: public Thread {
public:
	Background(void* sp, int show): Thread(sp), show(show)
	{
		start();
	}

	~Background()
	{
		out.println("Background should be killed now!");
	}

private:
	void run()
	{
		out.println("Background is running!");
		for(int i=0;;i++) {
			if (i % show == 0) {
				out.print("*");
			}
			yield();
		}

	}

	int show;
};

#endif
