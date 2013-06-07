#include "user/Hello.h"

#include "system/Environment.h"

Hello::Hello(const char* name, int runs, int slice, void* sp, Console& console) : Thread(sp, slice), console(console), runs(runs), name(name)
{
  out.print(name);
	out.println(" is created!");
	this -> start();
}

Hello::~Hello()
{
	this -> console.attach();
	out.print("Waiting for termination of ");
	out.println(name);
	this -> console.detach();
	this -> join();
	this -> console.attach();
	out.print(name);
	out.println(" is terminated");
	this -> console.detach();
}

void Hello::run()
{
	this -> console.attach();
	out.print(name);
	out.println("is running ");
	this -> console.detach();

	for (int i = 0; i < runs; i++) {
		this -> console.attach(); // Konsole reservieren

		out.print(name);
		out.print("> ");

		int size = (this -> console.read(line, LINE_SIZE));

		out.print(name);
		out.print(" got: ");
		out.print(size);
		out.print(" ");

		line[size - 1] = '\0'; // '\n' durch '\0' ersetzen

		// jetzt koennen wir die Zeile ausgeben
		out.println(line);

		this -> console.detach(); // und freigeben
	}

	this -> console.attach();
	out.print(name);
	out.println("finished");
	this -> console.detach();
}
