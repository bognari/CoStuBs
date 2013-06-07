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

#include "interrupts/PanicGate.h"
#include "interrupts/InterruptVector.h"
#include "io/PrintStream.h"
#include "device/CPU.h"

extern CPU cpu;
extern PrintStream out;

PanicGate::PanicGate(): Gate(Panic) { }

void PanicGate::handle()
{
	out.print("Panic: Illegal Trap/Interrupt!");
	cpu.halt();
}
