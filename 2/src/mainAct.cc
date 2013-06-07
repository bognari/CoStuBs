// Testprogramm fuer kooperative Threads

#include "device/CgaChannel.h"
#include "io/PrintStream.h"
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"

// Hello: Eine kooperative Aktivitaet
//
// Anmerkung: Diese Klasse dient
// zu Testzwecken und der Einfacheit halber sind
// alle Methoden dieser Klasse ausnahmsweise inline deklariert
// Das sollte normalerweise *nicht* der Fall sein!
class HelloAct: public Activity {
public:
  HelloAct(const char* name, PrintStream& out, int count=10)
  : cout(out)
  {
    this->name = name;
    this->count = count;
    this -> wakeup();
  }
  
  HelloAct(const char* name, PrintStream& out, void* sp, int count=10)
  : Activity(sp), cout(out)
  {
    this->name = name;
    this->count = count;
    this -> wakeup();
  }
  
  ~HelloAct()
  {
//     ok dann halt hier. um zu sehen wann anton fertig ist
//    cout.print(name);
//    cout.println(" destruktor");
    this -> join();
//    cout.print(name);
//    cout.println(" destruktor finish");
  }
  
  void body()
  {
    for(int i=0; i<=count; i++) {
      cout.print(name);
      cout.print(" ");
      cout.print(i);
      cout.println();
      
      yield();
    }
  }
  
private:
  const char* name;
  PrintStream& cout;
  int count;
};

//////////////////////////////////////////////////////////////////////////
// Die Systemobjekte von Co-Stubs

// globale Ein-/Ausgabeobjekte
CgaChannel cga;         // unser CGA-Ausgabekanal
PrintStream out(cga);   // unseren PrintStream mit Ausgabekanal verknuepfen

// Objekte der Prozessverwaltung
ActivityScheduler scheduler;   // der Scheduler

// die Stacks fuer unsere Prozesse/Coroutinen
unsigned stack0[1024];
unsigned stack1[1024];
//unsigned stack2[1024];
//unsigned stack3[1024];
//unsigned stack4[1024];
int main()
{
  HelloAct anton("Anton", out, 5); // anton benutzt den Stack von main
  HelloAct berta("Berta", out, &stack0[1023], 10);
  HelloAct caesar("Caesar", out, &stack1[1023], 15);
//  HelloAct heinz("Heinz", out, &stack2[1023], 7);
//  HelloAct kitty("Kitty", out, &stack3[1023], 4);
//  HelloAct hans("Hans", out, &stack4[1023], 9);
  
  anton.body();
  // da anton keine exit aufruft wie die anderen ist der exit trigger das verlassen des scopes
  // ab hier kommt der destruktor von caesar or what ever
}

