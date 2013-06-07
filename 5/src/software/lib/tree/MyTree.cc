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

#include "software/lib/tree/MyTree.h"

#include "io/PrintStream.h"

//extern PrintStream out; // debug

    /**
     * sucht ab der stelle das gesuchte
     */
    MyNode* MyTree::findFrom(MyNode* start, CgaChar* item, Compare vergleich, UpDown richtung)
    {
      bool erg = false;
      MyNode* curr = start;

      switch (richtung) {
        case DOWN : {
          //while (((curr -> getNext()) && !erg) && ((curr -> getNext()) != this)) {
          while ((curr -> getNext()) && !erg) {
            curr = curr -> getNext();
            switch (vergleich) {
              case ZEICHEN  : erg = (this -> equalChar(curr -> getValue(), item)); break;
              case ATTRIBUT : erg = (this -> equalAttr(curr -> getValue(), item)); break;
              case BEIDES   : erg = (this -> equalBoth(curr -> getValue(), item)); break;
            }
          }
          if (!(curr -> getNext())) {
            curr = start;
          }
        }; break;
        case UP : {
          //while (((curr -> getPrev()) && !erg) && ((curr -> getPrev()) != this)) {
          while (!erg && ((curr -> getPrev()) != this)) {
            curr = curr -> getPrev();
            switch (vergleich) {
              case ZEICHEN  : erg = (this -> equalChar(curr -> getValue(), item)); break;
              case ATTRIBUT : erg = (this -> equalAttr(curr -> getValue(), item)); break;
              case BEIDES   : erg = (this -> equalBoth(curr -> getValue(), item)); break;
            }
          }
          if ((curr -> getPrev()) == this) {
            curr = start;
          }
        }; break;
      }
      return (curr);
    }

    /**
     * Gibt ein Item zurueck das X stellen entfernt ist, Die Entfernung richtet sich nach der wertigkeit des zeichens
     */
    MyNode* MyTree::getItemFrom(MyNode* start, int posi)
    {
      MyNode* curr = start -> getNext();

      int entfernung = (this -> getZeichenAnzahl(curr)) % NL;
      while (curr && (entfernung < posi)) {
        switch(curr -> getValue() -> getChar()) {
          case '\n' : entfernung = ((entfernung / NL) + 1) * NL; break;
          case '\t' : entfernung = ((entfernung / T) + 1) * T; break;
          case '\v' : entfernung = (((entfernung / NL) / VT) + 1) * VT * NL; break;
          default   : entfernung++; break;
        }
        if ((entfernung <= posi) && (curr -> getNext())) { // damit er sich immer nur das weitere holt wenn die entfernung noch nicht erreicht wurde
          curr = curr -> getNext();
        }
      }
      return (curr);
    }

    /**
     * Gibt die Entfernung zwischen zwei Items zurueck
     * -1 wenn es keinen weg gibt
     * Die Entfernung richtet sich nach der wertigkeit des zeichens
     */
    int MyTree::getDistance(MyNode* src, MyNode* dest)
    {
      int src_enf = this -> getZeichenAnzahl(src -> getNext());
      int dest_enf = this -> getZeichenAnzahl(dest);
      int entfernung = (dest_enf - src_enf);
      return (entfernung);
    }

    /**
     * fuegt ein neues element vor X in den baum ein
     */
    void MyTree::insertHere(MyNode* here, CgaChar* item)
    {
      MyNode* node = (this -> getSpace());
      if (node) {
        node -> setValue(item);// value setzen

        node -> setPrev(here -> getPrev()); // die neue node mit vorgaenger und nachfolger verlinken
        node -> setNext(here);

        (here -> getPrev()) -> setNext(node); // die vorgaenger und nachfolger mit der node verlinken
        here -> setPrev(node);
      }
    }

    /**
     * Aendert den Inhalt von MyNode* in CgaChar*
     * falls MyNode locked war erstellt er eine neue node
     */
    void MyTree::changeValueHere(MyNode* here, CgaChar* item)
    {
      if (here != this) {
        if (here == (this -> getLocked())) {
          this -> insertHere(here, item);
        } else {
          here -> setValue(item);
        }
      }
    }


    /**
     * Loescht das Element aus dem Graphen
     */
    void MyTree::remove(MyNode* here)
    {
      if ((!(here == this)) && (!(here == (this -> getLocked())))) { // wenn das zu loeschene nicht root oder locked ist
        here -> getPrev() -> setNext(here -> getNext()); // den vorgaenger mit dem nachfolger
        here -> getNext() -> setPrev(here -> getPrev()); // und den nachfolger mit dem vorgaenger verlinken
        here -> setPrev(0);
        here -> setNext(0);
        here -> getValue() -> setChar(0x0);
      } // root und locked sind nicht loeschbar !
    }

    /**
     *  Gibt die Anzahl aller sichtbaren Zeichen von Root aus an
     */
    int MyTree::getZeichenAnzahl(MyNode* dest)
    {
      int entfernung = 0;

      MyNode* curr = (MyNode*)this;

      while (curr && (curr != dest)) {
        switch(curr -> getValue() -> getChar()) {
          case '\n' : entfernung = ((entfernung / NL) + 1) * NL; break;
          case '\t' : entfernung = ((entfernung / T) + 1) * T; break;
          case '\v' : entfernung = (((entfernung / NL) / VT) + 1) * VT * NL; break;
          case 0x0  : break;
          default   : entfernung++; break;
        }
        curr = curr -> getNext();
      }
      return (entfernung);
    }
