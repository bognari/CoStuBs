#include "system/Console.h"

  /**   Konsole reservieren
   */
  void Console::attach()
  {
    this -> sema.wait();
    //this -> berechntigt = Thread::self();
    //out.println("attach");
  }

  /**   Konsole wieder freigeben
   */
  void Console::detach()
  {
    //this -> berechntigt = 0;
    this -> sema.signal();
    //out.println("detach");
  }

  /**   Daten auf der Console ausgeben
   */
  int Console::write(const char* data, int size)
  {
    int ret = (this -> output.write(data, size));
    return (ret);
  }

  /**   Jedes von der Tastatur eingelesene Zeichen
   *  soll auf dem Bildschirm dargestellt werden (Echo Funktion!)
   *  Wenn ein '\n' erkannt wurde oder bereits "size" Zeichen
   *  gelesen wurden, ist eine Zeile zuende und read() kehrt zurueck.
   *  Alle gelesenen Ascii-zeichen sind in den Puffer einzutragen
   *  und zaehlen als gueltiges Zeichen!
   */
  int Console::read(char* data, int size)
  {
    int index = 0;
    char ch = 0;

    while (!(ch == '\n') && (index < size)) {
      ch = this -> read();
      output.write(ch);
      data[index] = ch;
      index++;
    }

    return (index);
  }

  /**   Liefert das naechste Zeichen aus dem Eingabepuffer zurueck.
   */
  char Console::read()
  {
    char ch;
    input.read(&ch, 1);
    return (ch);
  }
