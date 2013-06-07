// Testprogramm fuer kooperative Threads

#include "device/CgaChannel.h"
#include "device/CPU.h"
#include "io/PrintStream.h"
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"
#include "device/PIC.h"
#include "device/Clock.h"
#include "interrupts/InterruptGuardian.h"
#include "interrupts/IntLock.h"

// Hello: Eine kooperative Aktivitaet
//
// Anmerkung: Diese Klasse dient
// zu Testzwecken und der Einfacheit halber sind
// alle Methoden dieser Klasse ausnahmsweise inline deklariert
// Das sollte normalerweise *nicht* der Fall sein!
class HelloPre: public Activity {
public:
	HelloPre(const char* name, PrintStream& out, int time)
		: Activity(time), cout(out)
	{
		this->name = name;
	}

	HelloPre(const char* name, PrintStream& out, void* sp, int time)
		: Activity(sp, time), cout(out)
	{
		this->name = name;
		wakeup();
	}

	~HelloPre()
	{
		join();
	}

	void body()
	{
		for(int i = 0; i < 101; i++) {
			{
				IntLock lock;
				cout.print(name);
				cout.print(" ");
				cout.print(i);
				cout.println();
			}
            for(int j = 0; j < 100000; j++);
		}
//	  while(0) {
//	    yield();
//	  }
	}

private:
	const char* name;
	PrintStream& cout;
};

//////////////////////////////////////////////////////////////////////////
// Die Systemobjekte von Co-Stubs

CPU cpu;

InterruptGuardian interruptGuardian;
PIC pic;
Clock clock(2500);

// globale Ein-/Ausgabeobjekte
CgaChannel cga;         // unser CGA-Ausgabekanal
PrintStream out(cga);   // unseren PrintStream mit Ausgabekanal verknuepfen

// Objekte der Prozessverwaltung
ActivityScheduler scheduler;   // der Scheduler

// die Stacks fuer unsere Prozesse/Coroutinen
unsigned stack0[1024];
unsigned stack1[1024];

int main()
{
	HelloPre anton("Anton", out, 10); // anton benutzt den Stack von main
	HelloPre berta("Berta", out, &stack0[1023], 15);
	HelloPre caesar("Caesar", out, &stack1[1023], 20);

	cpu.enableInterrupts();
	anton.body();
}
