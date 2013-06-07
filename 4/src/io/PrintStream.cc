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

#include "io/PrintStream.h"

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

// weil ist so
void PrintStream::println(char c)
{
  this -> print(c);
  this -> println();
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
  this -> channel.write('\n');
}

/*! numerische Werte werden zur Basis 'base' Ausgegeben
* implementiere die Basen 2, 10 und 16
*/
void PrintStream::print(int x, int base)
{ // wenn die zahl negativ ist schreibt er ein minus und schickt den betrag weiter
  if (x < 0) {
    x = -x;
    this -> channel.write('-');
  }
  switch(base)
  {
    case BINARY   : this -> channel.write("0b", 2); break;
    case HEX      : this -> channel.write("0x", 2); break;
    case DECIMAL  :                               ; break;
    default       : this -> print((unsigned)base, 10); this -> channel.write("x_", 2); break;
  }
  this -> print((unsigned)x, base);
}

void PrintStream::print(unsigned x, int base)
{ // wandelt den betrag einer zahl in das zahlensystem und und gibt es aus
  if (base < 2|| base > 36) {
    this -> println("ERROR !: unzulaessige Basis");
  } else {
    const char* chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //
    char ausgabe[65]; // wer laengere zahlen benutzt ist selber schuld ! // bei 65 bit ugly im binaer system aber ka warum... deswegen wieder auf 128
    int size = 0;
    do
    {
      ausgabe[size] = chars[x % base];
      size++;
      x = (x / base);
    }
    while ((x > 0) && (size < 64)); // ups overflow moeglich gewesen bei 65
    size--;
    for (int i = size; i >= 0; i--) { // von hinten nach vone ausgeben weil der algorithmus so war
      this -> channel.write(ausgabe[i]);
    }
  }
}

// Zeigertypen werden immer zur Basis 16 ausgegeben!
void PrintStream::print(void* p)
{
  this -> channel.write("0x", 2);
  this -> print((unsigned)p, HEX);
}

