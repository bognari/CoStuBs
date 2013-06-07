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

#include "sync/KernelSemaphore.h"

  void KernelSemaphore::wait()
  {
    if (this -> counter > 0) {
      this -> counter--;
    } else {
      Activity* act = (Activity*)(scheduler.active());
      this -> waitlist.enqueue(act);
      act -> sleep();
    }
  }

  void KernelSemaphore::signal()
  {
    if (this -> waitlist.getItem(0)) {
      Activity* phoenix = (Activity*)(this -> waitlist.dequeue());
      phoenix -> wakeup();
    } else {
      this -> counter++;
    }
  }
