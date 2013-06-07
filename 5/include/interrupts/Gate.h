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

#ifndef Gate_h
#define Gate_h

#include "lib/Chain.h"

/*
 * Gate: Ein Trap/Interrupt Tor
 *
 *     	Alle Treiber, die Geraete mit Interrupts steuern
 *     	muessen fuer jeden Interrupt ein Gate-Objekt anlegen.
 *	Die Gate-Objekte tragen sich selber in die logische
 *	Interrupt-Tabelle ein.
 *	Sobald dies geschehen ist, werden alle an diesem Gate
 *	auftretenden Interrupts ueber die handle()-Methode
 *	dem Treiber mitgeteilt.
 *
 *	Achtung: Gates muessen definiert sein,
 *	*bevor* der zugehoerige Interrupt zugelassen wird!!!!
 */
class Gate : public Chain {
public:
	// Definition eines Gates fuer Vektornummer "num"
	Gate (int num);

	//  Automatisches Abmelden des Gates
	virtual ~Gate ();


	/** 	Nur was sofort in der Interruptbehandlung gemacht werden
	 *	muss, darf im Prolog gemacht werden.
	 */
	virtual bool prologue() = 0;

	/** Nicht jeder Interrupthandler muss einen Epilog haben.
	 */
	virtual void epilogue(){}

	int getNumber()
	{
		return (this -> num);
	}

	bool isDeferred()
	{
		return (this -> deferred);
	}

	void setDeferred(bool value)
	{
		this -> deferred = value;
	}

private:
	int num;
	bool deferred;
};

#endif
