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

#include "software/Editor.h"

  Editor::Editor(int cpuTime) : CgaChannel(), Activity(cpuTime)
  {
    this -> screenTop = ((MyNode*)&(this -> content));
    this -> modus = INSERT;
    this -> screen = (CgaChar*)VIDEO_BASE;
    this -> isRunning = true;
    this -> setCursor(this -> screenTop -> getNext(), NORMAL);
  }

  void Editor::draw()
  {
    MyNode* curr = (this -> screenTop) -> getNext(); // holen des einstiegs

    int haben = 0; // momentane position im grafik ram (0 - 1999)
    int soll = 0; // die position die erreicht werden soll wenn zeichen eine groessere wertigkeit als 1 haben z.b. \n \t \v

    while (curr && (haben < ZEICHEN)) { // geht den ganzen tree durch bis screen voll
      switch (curr -> getValue() -> getChar()) {
        case '\n' : soll = (((haben / MyTree::NL) + 1) * MyTree::NL); break;
        case '\t' : soll = (((haben / MyTree::T) + 1) * MyTree::T); break;
        case '\v' : soll = (((haben / MyTree::NL) / MyTree::VT) + 1) * MyTree::VT * MyTree::NL; break;
        default   : {
          this -> screen[haben].setChar(curr -> getValue() -> getChar());
          this -> screen[haben].setAttr(curr -> getValue() -> getAttr());
          haben++;
          soll++;
        }; break;
      }
      while ((haben < soll) && (haben < ZEICHEN)) { // wenn ein zeichen eine groessere wertigkeit als 1 hatte dann fuellt er ab hier mit leerzeichen auf
        this -> screen[haben].setChar(' ');
        this -> screen[haben].setAttr(curr -> getValue() -> getAttr()); // die attrs fuer die leerzeichen stammen vom ersetzten zeichen
        haben++;
      }
      curr = curr -> getNext();
    }
    //out.println("ende1");
    while (haben < ZEICHEN) { // wenn der screen noch nicht voll war dann wird mit leerzeichen auf gefuellt
      this -> screen[haben].setChar(' ');
      this -> screen[haben].setAttr(this -> attr);
      haben++;
    }
    //out.println("ende2");
  }

  void Editor::handler()
  {
    //this -> setCursor(this -> screenTop -> getNext());
    Key key;
    do{
      key = keyboard.read();
      //out.print((char)key.getValue());
      if (key.isAscii()) {
        this -> handler_ascii((unsigned char)(key.getValue()));
      } else {
        this -> handler_cont((unsigned char)(key.getValue()));
      }
    } while(this -> isRunning);
  }

  void Editor::handler_ascii(unsigned char c)
  {
    if ((c > 0x0) && (c < 0xff)) { // da page code 437 kann er alles als zeichen darstellen ausser 0 und ff
      switch (c) {
        case ESC : {
          this -> isRunning = false;
        }; break;
        case BS : { // abfangen falls topscreen geloescht wird
          if (this -> screenTop == this -> cursor) { // sollte den fehler beheben
            this -> screenTop = (MyNode*)&(this -> content);
            this -> content.remove((this -> cursor -> getPrev()));
            this -> setCursor(this -> cursor, UP);
          } else {
            this -> content.remove((this -> cursor -> getPrev()));
            this -> setCursor(this -> cursor, NORMAL);
          }
        }; break;
        case '-' : {
          CgaChar zeichen;
          zeichen.setChar(' ');
          this -> setCursor(this -> content.findFrom(this -> cursor, &zeichen, MyTree::ZEICHEN, MyTree::UP ), NORMAL);
        }; break;
        case '+' : {
          CgaChar zeichen;
          zeichen.setChar(' ');
          this -> setCursor(this -> content.findFrom(this -> cursor, &zeichen, MyTree::ZEICHEN, MyTree::DOWN ), NORMAL);
        }; break;
        default : {
          CgaChar zeichen(c, this -> attr);
          if (this -> modus == INSERT) {
            this -> content.insertHere(this -> cursor, &zeichen);
            this -> setCursor(this -> cursor, NORMAL);
          } else {
            if ((this -> cursor -> getValue() -> getChar() == '\n') ||(this -> cursor -> getValue() -> getChar() == '\t') ||(this -> cursor -> getValue() -> getChar() == '\v')) {
              this -> content.insertHere(this -> cursor, &zeichen);
              this -> setCursor(this -> cursor, NORMAL);
            } else {
              this -> content.changeValueHere(this -> cursor, &zeichen);
              this -> setCursor(this -> cursor -> getNext(), NORMAL);
            }
          }
        }; break;
      }
    }
  }

  void Editor::handler_cont(unsigned char scancode)
  {
    switch(scancode) {
      case CodeTable::RIGHT : {
        this -> setCursor(this -> cursor -> getNext(), NORMAL);
      }; break;
      case CodeTable::LEFT : {
        this -> setCursor(this -> cursor -> getPrev(), NORMAL);
      }; break;
      case CodeTable::DOWN : {
        int entfernung = this -> content.getDistance((MyNode*)&(this -> content), this -> cursor) + MyTree::NL;
        MyNode* temp = this -> content.getItemFrom((MyNode*)&(this -> content), entfernung);
        this -> setCursor(temp, NORMAL);
      }; break;
      case CodeTable::UP : {
        int entfernung = this -> content.getDistance((MyNode*)&(this -> content), this -> cursor) + (MyTree::NL * -1);
        MyNode* temp = this -> content.getItemFrom((MyNode*)&(this -> content), entfernung);
        this -> setCursor(temp, NORMAL);
      }; break;
      case CodeTable::DEL : {
        MyNode* temp = this -> cursor -> getNext();
        this -> content.remove(this -> cursor);
        this -> setCursor(temp, NORMAL);
      }; break;
      case CodeTable::POS1 : {
        int entfernung = this -> content.getDistance(this -> screenTop, this -> cursor);
        entfernung = ((entfernung / MyTree::NL) * MyTree::NL);
        MyNode* temp = this -> content.getItemFrom((this -> screenTop), entfernung);
        this -> setCursor(temp, NORMAL);
      }; break;
      case CodeTable::PAGE_DOWN : {
        int entfernung = this -> content.getDistance((MyNode*)&(this -> content), this -> cursor) + (MyTree::NL * ZEILEN);
        MyNode* temp = this -> content.getItemFrom((MyNode*)&(this -> content), entfernung);
        this -> setCursor(temp, NORMAL);
      }; break;
      case CodeTable::PAGE_UP : {
        int entfernung = this -> content.getDistance((MyNode*)&(this -> content), this -> cursor) + (MyTree::NL * ZEILEN * -1);
        MyNode* temp = this -> content.getItemFrom((MyNode*)&(this -> content), entfernung);
        this -> setCursor(temp, NORMAL);
      }; break;
      case CodeTable::END : {
        int entfernung = this -> content.getDistance(this -> screenTop, this -> cursor);
        entfernung = ((((entfernung / MyTree::NL)+ 1) * MyTree::NL) -1);
        MyNode* temp = this -> content.getItemFrom((this -> screenTop), entfernung);
        this -> setCursor(temp, NORMAL);
      }; break;
      case CodeTable::INS : {
        if (this -> modus == INSERT) {
          this -> modus = OVERWITE;
        } else {
          this -> modus = INSERT;
        }
      }; break;
    }
  }

  /**
   * Setzt den HW und den internen Cursor
   */
  void Editor::setCursor(MyNode* set, Cursor richtung = NORMAL)
  {
    if (set == ((MyNode*)&(this -> content))) {
      set = (MyNode*)(this -> content.getRoot());
    } else {
      if (set) {
        this -> cursor = set;
      } else {
        this -> cursor = this -> content.getLocked();
      }
    }
//    debug
//    this -> xPosi = 0;
//    this -> yPosi = 23;

    int entfernung = this -> content.getDistance(this -> screenTop, this -> cursor);

    if ((entfernung < 0) || (richtung == UP)) { 
    // hoch scrollen, da es aber iwie net will, geh ich ganz nach oben und scroll runter bis x
      this -> screenTop = (MyNode*)&(this -> content);
      entfernung = this -> content.getDistance(this -> screenTop, this -> cursor);
      while (entfernung >= MyTree::NL) {
        this -> screenTop = (this -> content.getItemFrom(this -> screenTop, MyTree::NL) -> getPrev());
        entfernung = this -> content.getDistance(this -> screenTop, this -> cursor);
      }
    }

    while ((entfernung >= ZEICHEN) && (richtung == NORMAL)) { //nach unten scrollen
      this -> screenTop = (this -> content.getItemFrom(this -> screenTop, MyTree::NL) -> getPrev());
      entfernung = this -> content.getDistance(this -> screenTop, this -> cursor);
    }

    this -> index.write(LOW);
    this -> data.write((unsigned char)entfernung);
    this -> index.write(HIGH);
    this -> data.write((unsigned char)(entfernung >> 8));

    this -> draw();
  }
