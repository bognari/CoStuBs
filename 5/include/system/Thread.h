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

#ifndef Thread_h
#define Thread_h

#include "thread/Activity.h"
#include "sync/KernelLock.h"
#include "thread/ActivityScheduler.h"

/** 	Diese Klasse implementiert die Systemschnittstelle fuer leichtgewichtige
 *	Prozesse in Co-Stubs. Die run-Methode entspricht der main eines Threads.
 *
 *	Beachte, das Thread private von Activity erbt, in abgeleiteten Klassen
 *	kann also nicht direkt auf Methoden von Activity zugegriffen werden.
 *
 *	In abgeleiteten Klassen nicht vergessen den virtuellen Destruktor
 *	zu definieren, wenn eine Synchronisation aufs Ende erforderlich ist.
 *	Nutze dazu die Methoden join oder kill.
 *
 *	Da die Methoden hier sehr kurz sind, koennen sie alle inline implementiert
 *	werden.
 */

#include "sync/KernelLock.h"

class Thread: private Activity {
public:
	Thread(int slice=1) : Activity(slice)
	{}

	Thread(void* tos, int slice=1) : Activity(tos, slice)
	{}

	/** Die Implementierung der body-Methode geerbt von Coroutine.
	 */
	virtual void body()
	{
	  this -> run();
	}

	/** Die Methode fuer den Anwendungscode eines Threads.
	 */
	virtual void run()=0;

	/** Den gerade laufenden Thread ermitteln.
	 */
	static Thread* self()
	{
	  return ((Thread*)(scheduler.active()));
	}

	/** Synchronisation auf das Ende eines Threads
	 */
	void join()
	{
	  KernelLock lock;

	  Activity::join();
	}

	/** Ein Thread wird explizit gestartet.
	 */
	void start()
	{
	  KernelLock lock;

	  Activity::wakeup();
	}

	/** Explizites beenden eines Threads.
	 */
	void exit()
	{
	  KernelLock lock;

	  Activity::exit();
	}

	/** Abgabe der CPU.
	 */
	void yield()
	{
	  KernelLock lock;

	  Activity::yield();
	}


};

#endif

