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

#ifndef MyTree_h
#define MyTree_h

#include "software/lib/tree/MyNode.h"

class MyTree : public MyNode {
  private:
    MyNode heap[4000];
    int size;

  public:
    enum UpDown {
      DOWN = 0,
      UP = 1,
    };

    enum Compare {
      ZEICHEN = 0,
      ATTRIBUT = 1,
      BEIDES = 2,
    };

    enum Wertigkeit {
      NL = 80,
      T = 4,
      VT = 4,
    };

    MyTree() : MyNode()
    {
      this -> size = 4000;
      MyNode* locked = this -> getSpace();
      locked -> setPrev((MyNode*)(this));
      locked -> setNext(0);
      locked -> getValue() -> setChar(' ');
      this -> setNext(locked);
      this -> setPrev(locked);
    }

    /**
     * sucht ab der stelle das genaue objekt
     * wenn er es nicht findet dann gibt er den anfang zurueck
     */
    MyNode* findFrom(MyNode*, CgaChar*, Compare, UpDown);

    /**
     * Gibt ein Item zurueck das X stellen entfernt ist, Die Entfernung richtet sich nach der wertigkeit des zeichens
     */
    MyNode* getItemFrom(MyNode* start, int posi);

    /**
     * Gibt die Entfernung zwischen zwei Items zurueck
     * -1 wenn es keinen weg gibt
     * Die Entfernung richtet sich nach der wertigkeit des zeichens
     */
    int getDistance(MyNode* src, MyNode* dest);

    /**
     * fuegt ein neues element vor X in die queue ein
     */
    void insertHere(MyNode*, CgaChar*);

    /**
     * Aendert den Inhalt von MyNode* in CgaChar*
     * falls MyNode locked war erstellt er eine neue node
     */
    void changeValueHere(MyNode*, CgaChar*);

    /**
     * Loescht das Element aus dem Graphen
     */
    void remove(MyNode*);

    /**
     * gibt das letzte Element aus. nach diesem kommt aber immernoch das locked(prev) element
     */
    MyNode* getLast()
    {
      return (this -> getLocked() -> getPrev());
    }
    /**
     * gibt Root zurueck
     */
    MyNode* getRoot()
    {
      return (this -> getNext());
    }

    /**
     * gibt das locked elem zurueck
     */
    MyNode* getLocked()
    {
      return (this -> getPrev());
    }

  //private:
    /**
     *  Gibt die Anzahl aller sichtbaren Zeichen von Root aus an
     */
    int getZeichenAnzahl(MyNode*);
  private:
    /**
     * Compare = Zeichen
     */
    bool equalChar(CgaChar* a, CgaChar* b)
    {
      return ((a -> getChar()) == (b -> getChar()));
    }

    /**
     * Compare = Attr
     */
    bool equalAttr(CgaChar* a, CgaChar* b)
    {
      bool bg = (a -> getAttr().getBackground()) == (b -> getAttr().getBackground());
      bool fg = (a -> getAttr().getForeground()) == (b -> getAttr().getForeground());
      bool bl = (a -> getAttr().getBlinkState()) == (b -> getAttr().getBlinkState());
      return (bg && fg && bl);
    }

    /**
     * Compare = Beide
     */
    bool equalBoth(CgaChar* a, CgaChar* b)
    {
      return ((this -> equalChar(a, b)) && (this -> equalAttr(a, b)));
    }

    MyNode* getSpace()
    {
      MyNode* curr = &(this -> heap[0]);
      int index = 0;
      while ((curr -> getPrev() != 0) && index < (this -> size)) {
        index++;
        curr = &(this -> heap[index]);
      }
      if (curr -> getPrev() != 0) {
        return ((MyNode*)0);
      }
      return (curr);
    }
};

#endif /* MYTREE_H */
