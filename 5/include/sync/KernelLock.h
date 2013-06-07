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

#ifndef KernelLock_h
#define KernelLock_h

#include "sync/Monitor.h"

/**	Diese Klasse dient dazu	innerhalb eines Blockes den Kernel-Monitor
 *	zu sperren. Dabei kann KernelLock auch verschachtelt verwendet
 *	werden.
 */
class KernelLock {
public:
	KernelLock()
	{
	  this -> lock();
	}

	~KernelLock()
	{
	  this -> unlock();
	}

	void lock()
	{
		this -> wasFree = monitor.isFree();
		monitor.enter();
	}

	void unlock()
	{
		if (this -> wasFree) {
		  monitor.leave();
		}
	}
private:
	bool wasFree; // vorheriger Zustand des Monitors
};

#endif
