#include "io/PrintStream.h"
#include "io/OutputChannel.h"

// Ausgabe eines mit einem NULL-Byte terminierten Strings
void PrintStream::print(const char* str)
{ // schreibt vom ersten zeichen bis zum \0 =  Stringende
  int i = 0;
  while(str[i] != 0)
  {
    i++;
  }
  this -> channel.write(str, i);
}

void PrintStream::print(char ch)
{
  this -> channel.write(ch); // OutputChannel::write(char c)
}

// Ausgabe eines Strings mit anschliessendem Zeilenvorschub
void PrintStream::println(const char* str)
{
  this -> print(str);
  this -> println();
}

// Zeilenvorschub
void PrintStream::println()
{
  this -> channel.write("\n\r", 2);
}

// numerische Werte werden zur Basis 'base' Ausgegeben
// implementiere die Basen 2, 10 und 16
void PrintStream::print(int x, int base)
{ // wenn die zahl negativ ist schreibt er ein minus und schickt den betrag weiter
  if (x < 0) {
    x = x * (- 1);
    this -> channel.write('-');
  }
  switch(base){
    case BINARY : this -> print("0b"); break;
    case HEX : this -> print("0x"); break;
  }
  this -> print((unsigned)x, base);
}

void PrintStream::print(unsigned x, int base)
{ // wandelt den betrag einer zahl in das zahlensystem und und gibt es aus
  const char* chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //
  char ausgabe[128]; // wer laengere zahlen benutzt ist selber schuld ! // bei 65 bit ugly im binaer system aber ka warum... deswegen wieder auf 128
  int size = 0;
  do
  {
    ausgabe[size] = chars[x % base];
    size++;
    x = (x / base);
  }
  while (x > 0);
  for (int i = size; i >= 0; i--) {
    this -> channel.write(ausgabe[i]);
  }
}

// Zeigertypen werden immer zur Basis 16 ausgegeben!
void PrintStream::print(void* p)
{
  this -> print("0x");
  this -> print((unsigned)p, HEX);
}

