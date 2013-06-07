#include "device/CgaChannel.h"
#include "device/CPU.h"
#include "io/PrintStream.h"
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"
#include "device/PIC.h"
#include "device/Clock.h"
#include "interrupts/InterruptGuardian.h"
#include "interrupts/IntLock.h"
#include "device/Keyboard.h"
#include "software/Editor.h"

//////////////////////////////////////////////////////////////////////////
// Die Systemobjekte von Co-Stubs

CPU cpu;

InterruptGuardian interruptGuardian;
PIC pic;
Clock clock(2500);

Keyboard keyboard;

// Objekte der Prozessverwaltung
ActivityScheduler scheduler;   // der Scheduler

// globale Ein-/Ausgabeobjekte
Editor editor;         // unser CGA-Ausgabekanal
PrintStream out(editor);   // unseren PrintStream mit Ausgabekanal verknuepfen


int main()
{
	cpu.enableInterrupts();
  editor.body();
  scheduler.kill(&editor);
}

