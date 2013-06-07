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

#ifndef Queue_h
#define Queue_h

#include "lib/Chain.h"

class Queue {
public:
	Queue () { head = 0; tail = &head; }

	//! Einfuegen eines Elementes an das Ende der Liste
	void enqueue(Chain* item);

	//! Entfernen des Listenkopfes
	Chain* dequeue();

	//! Entfernen des angegebenen Elementes
	void remove(Chain* item);

  /*! gibt einen Zeiger auf das Element der jeweiligen Position
  *   so kann man in der liste suchen ohne diese zu zerstoeren
  *   liefert 0 wenn das ende der liste erreicht wurde.
  */
  Chain* getItem(int);


private:
  //! der Listenkopf
	Chain* head;
  //! Zeiger auf den Zeiger auf das Listenende
	Chain** tail;
};

#endif
