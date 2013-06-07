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

#ifndef MyNode_h
#define MyNode_h

#include "device/CgaChar.h"

class MyNode {
  protected:

    CgaChar value;
    MyNode* prev ;
    MyNode* next ;

  public:
    MyNode(MyNode* prev = 0, MyNode* next = 0) : prev(prev), next(next)
    {
    }

    void setNext(MyNode* next = (MyNode*)0)
    {
      this -> next = next;
    }

    void setPrev(MyNode* prev = (MyNode*)0)
    {
      this -> prev = prev;
    }

    void setValue(CgaChar* item)
    {
      this -> value.setChar((*item).getChar());
      this -> value.setAttr((*item).getAttr());
    }
    MyNode* getNext()
    {
      return (this -> next);
    }

    MyNode* getPrev()
    {
      return (this -> prev);
    }

    CgaChar* getValue()
    {
      return (&(this -> value));
    }
};

#endif
