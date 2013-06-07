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

#include "interrupts/InterruptGuardian.h"
#include "sync/Monitor.h"

#include "interrupts/PanicGate.h"
extern PanicGate panicGate;

static bool initialized = false;
Gate* InterruptGuardian::vectorTable[NrOfInterrupts];

extern "C" void guardian(int num);

void guardian(int num)
{
	InterruptGuardian::handle(num);
}

InterruptGuardian::InterruptGuardian()
{
	if(!initialized){
		for(int i = 0; i < NrOfInterrupts; i++){
			vectorTable[i] = &panicGate;
		}
		initialized = true;
	}
}

void InterruptGuardian::handle(int num)
{
	Gate* gate = vectorTable[num];
	if(gate -> prologue()) {
		monitor.runEpilogue(gate);
	}
}

void InterruptGuardian::registerGate(Gate* gate,int num)
{
	if(!initialized) {
		for(int i = 0; i < NrOfInterrupts; i++){
			vectorTable[i] = &panicGate;
		}
		initialized = true;
	}
	if((num >= -1) && (num < NrOfInterrupts)){
		vectorTable[num] = gate;
	}
}

