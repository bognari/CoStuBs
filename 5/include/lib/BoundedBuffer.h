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

#ifndef BoundedBuffer_h
#define BoundedBuffer_h

#include "lib/Queue.h"
#include "thread/ActivityScheduler.h"
#include "thread/Activity.h"

extern ActivityScheduler scheduler;

/** Diese Klasse stellt einen begrenzten synchronisierten
 *  Puffer dar, welcher von Interruptbehandlungsroutinen
 *  gefuellt werden kann.
 *
 *  Die Klasse ist eine Templateklasse. Das bedeutet fuer euch
 *  erstmal nur, das ihr alle Methoden hier im Header implementieren
 *  muesst.
 */

template<typename T,unsigned size>

class BoundedBuffer {
public:

	BoundedBuffer()
	{
	  for (unsigned int i = 0; i < size; i++) {
	    this -> buffer[i] = T ();
	  }
	  this -> inIndex = 0;
	  this -> outIndex = size - 1;
	}

	/** Diese Methode wird vom Interrupthandler aufgerufen, um
	 *  ein etwas in den Puffer zu schreiben. Ist der Puffer voll,
	 *  werden die scheduler.active()zu schreibenden Daten verworfen.
	 *  Prozesse die auf eine Eingabe warten muessen hier geweckt werden.
	 */
	void add(T& elem)
	{
	  if (this -> isSpace()) {
	    this -> buffer[this -> inIndex] = elem;
	    this -> nextInIndex();
	  }

	  // damit er auch einen wakeup macht falls er voll ist, was aber eigendlich gar nicht passieren sollte
	  Activity* next = (Activity*) (this -> waitingList.dequeue());
	  if (next) {
	    next -> wakeup();
	  }
	}

	/** Diese Methode wird von Prozessen aufgerufen, um Daten aus dem
	 *  Puffer zu lesen. Ist dieser leer wird der lesende Prozess schlafen
	 *  gelegt. Achtet hier besonders auf die Synchronisierung.
	 */
	T get()
	{

	  // testen ob der buffer leer ist
	  if (this -> isEmpty()) {
	    this -> waitingList.enqueue((Activity*)(scheduler.active()));
	    scheduler.suspend();
	    // hier geht er nach dem wakeup weiter
	  }
	  // ab hier steht etwas zu 100% in dem buffer

	  this -> nextOutIndex();

	  return (this -> buffer[this -> outIndex]);
	}

  bool isEmpty()
  {
    return ((this -> inIndex) == ((this -> outIndex + 1) % size));
  }

  bool isSpace()
  {
    return ((this -> inIndex) != (this -> outIndex));
  }

private:
	T buffer[size];
	volatile unsigned int inIndex;
	volatile unsigned int outIndex;
	Queue waitingList;

	void nextInIndex()
	{
	  this -> inIndex = ((this -> inIndex + 1) % size);
	}

	void nextOutIndex()
	{
	  this -> outIndex = ((this -> outIndex + 1) % size);
	}

};

#endif

