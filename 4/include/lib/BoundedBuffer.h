#ifndef BoundedBuffer_h
#define BoundedBuffer_h

#include "interrupts/IntLock.h"
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
	 *  werden die zu schreibenden Daten verworfen.
	 *  Prozesse die auf eine Eingabe warten muessen hier geweckt werden.
	 */
	void add(T& elem)
	{
	  if (this -> inIndex != this -> outIndex) {
	    this -> buffer[this -> inIndex] = elem;
	    this -> nextInIndex();
	    if (this -> waitingList.getItem(0)) {
	      Activity* next = (Activity*) (this -> waitingList.getItem(0));
	      next -> changeTo(Activity::READY);
	      scheduler.schedule(next); // kann so problemen fuehren
//	      scheduler.activate(next); // zwar unfair den anderen gegenueber aber naja
	    }
	  }
	}

	/** Diese Methode wird von Prozessen aufgerufen, um Daten aus dem
	 *  Puffer zu lesen. Ist dieser leer wird der lesende Prozess schlafen
	 *  gelegt. Achtet hier besonders auf die Synchronisierung.
	 */
	T get()
	{
	  IntLock lock;
	  Activity* curr = (Activity*) (scheduler.active());
	  this -> waitingList.enqueue(curr);

	  if (!(((Activity*)(this -> waitingList.getItem(0))) == curr)) { // gucken ob er lese berechtigung hat
	    curr -> changeTo(Activity::BLOCKED);
	    lock.restore();
	    scheduler.reschedule();
	    // hier geht er nach dem wakeup weiter
	    lock.lock();
	  }

	  // ab hier haben wir die berechtigung

	  // testen ob der buffer leer ist
	  if (this -> isEmpty()) {
	    curr -> changeTo(Activity::BLOCKED);
	    lock.restore();
	    scheduler.reschedule();
	    // hier geht er nach dem wakeup weiter
	    lock.lock();
	  }
	  // ab hier steht etwas zu 100% in dem buffer

	  this -> waitingList.dequeue();

	  this -> nextOutIndex();

	  return this -> buffer[this -> outIndex];
	}

private:
	T buffer[size];
	volatile unsigned int inIndex;
	volatile unsigned int outIndex;
	//unsigned int size;
	Queue waitingList;

	bool isEmpty()
	{
	  if ((this -> inIndex) == ((this -> outIndex + 1) % size)) {
	    return true;
	  }
	  return false;
	}

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

