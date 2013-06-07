// Testprogramm fuer Coroutinen

#include "device/CgaChannel.h"
#include "io/PrintStream.h"
#include "thread/Coroutine.h"

// Eine Coroutinen-Klasse
//
// Anmerkung: Diese Klasse dient
// zu Testzwecken und der Einfacheit halber sind
// alle Methoden dieser Klasse ausnahmsweise inline deklariert
// Das sollte normalerweise *nicht* der Fall sein!

class HelloCo: public Coroutine {
public:
	HelloCo(const char* name, PrintStream& out)
		: cout(out)
	{
		this->name = name;
	}

	HelloCo(const char* name, PrintStream& out, void* sp)
		: Coroutine(sp), cout(out)
	{
		this->name = name;
	}

	void link(Coroutine& next)
	{
		this->next = &next;
	}

	void body()
	{
		for(int i=0; i<100; i++) {
			cout.print(name);
			cout.print(" ");
			cout.print(i);
			cout.println();

			resume(next);
		}
	}

	void exit()
	{
		cout.print("Panic!!!!");
		cout.println();
	}

	const char* name;
	Coroutine* next;

	PrintStream& cout;
};

//////////////////////////////////////////////////////////////////////////
// Die Systemobjekte von Co-Stubs

// globale Ein-/Ausgabeobjekte

CgaChannel cga;         // unser CGA-Ausgabekanal
PrintStream out(cga);   // unseren PrintStream mit Ausgabekanal verknuepfen

// die Stacks fuer unsere Prozesse/Coroutinen

unsigned stack0[1024];
unsigned stack1[1024];

int main()
{
	HelloCo anton("Anton", out); // anton benutzt den Stack von main
  out.println("anton fertig");
	HelloCo berta("Berta", out, &stack0[1023]);
  out.println("berta fertig");
	HelloCo caesar("Caesar", out, &stack1[1023]);
  out.println("caesar fertig");
	// alle Coroutinen zyklisch verketten
	anton.link(berta);
	berta.link(caesar);
	caesar.link(anton);

	// los geht's
	anton.body();
  out.println();
  out.print("mainCo done");
}
