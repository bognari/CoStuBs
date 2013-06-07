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

#ifndef Environment_h
#define Environment_h

#include "device/CgaChannel.h"
#include "device/Clock.h"
#include "device/CPU.h"
#include "device/PIC.h"
#include "device/PIT.h"
#include "device/Keyboard.h"
#include "io/PrintStream.h"
#include "sync/Monitor.h"
#include "thread/ActivityScheduler.h"
#include "system/Console.h"

extern CPU cpu;
extern Console console;
extern Monitor monitor;
extern PIC pic;
extern PIT pit;
extern Clock clock;
extern Keyboard keyboard;
extern CgaChannel screen;
extern PrintStream out;
extern ActivityScheduler scheduler;

#endif

