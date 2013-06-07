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

#ifndef Editor_h
#define Editor_h

#include "device/CgaChar.h"
#include "device/CgaAttr.h"
#include "software/lib/tree/MyNode.h"
#include "software/lib/tree/MyTree.h"
#include "device/CgaChannel.h"
#include "device/Keyboard.h"
#include "device/CodeTable.h"
#include "thread/Activity.h"

#include "io/PrintStream.h"

extern PrintStream out; // debug


class Editor: public CgaChannel, public Activity {
  public:

    /**
     * Modus des Editors
     */
    enum Modi {
      OVERWITE, INSERT
    };

    /**
     * Spezielle ASCII zeichen
     */
    enum MenuComAsASCII {
      ESC = 27,
      BS = 8, // \b
    };

    enum Config {
      ZEICHEN = 2000,
      ZEILEN = 24,
    };

    enum Cursor {
      UP,
      NORMAL
    };

  //private:
    MyNode* screenTop;
    MyNode* cursor;
    MyTree content;
    Modi modus;
    bool isRunning;
    int zeile;

  public:
    Editor(int cpuTime = 1);


    /**
     * zeichnet ab "start" 2000 zeichen auf dem bildschirm
     */
    void draw();

    /**
     * Die Methode die in alles Verwaltet
     */
    void handler();

    /**
     * arbeitet die ascii zeichen ab. frage ist nur sind ascii alle zeichenbaren zeichen oder auch steuerzeichen?
     */
    void handler_ascii(unsigned char);

    /**
     * arbeitet alles nicht sichtbare ab
     */
    void handler_cont(unsigned char);

    /**
     * Setzt den HW und den internen Cursor
     */
    void setCursor(MyNode*, Cursor);

    /**
     * das was etwas macht
     */
    void body()
    {
      // ich hasse stack objekte in cpp ! ich hasse es einfach so wenn man mal java gewoehnt war...
      this -> handler();
    }
};

#endif
