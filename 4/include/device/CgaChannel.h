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

#ifndef CgaChannel_h
#define CgaChannel_h

#include "io/OutputChannel.h"
#include "device/CgaScreen.h"

/*
 * CgaChannel:	Diese Klasse implementiert einen Ausgabekanal
 *		fuer den CGA-Bildschirm
 *
 *		Sie *muss* die 'write' Methode implementieren,
 *		und alle write() Aufrufe geeignet auf den CgaScreen abbilden.
 */

class CgaChannel: public OutputChannel, public CgaScreen {
public:
	//! Ausgabekanal mit Standardattributen
	CgaChannel() ;

	//! Ausgabekanal mit spezifischen Attributen
	CgaChannel(const CgaAttr& attr);

	//! Die von OutputChannel deklarierte Ausgaberoutine
	virtual int write(const char* data, int size);
};

#endif
