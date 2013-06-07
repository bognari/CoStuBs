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

#ifndef CgaChar_h
#define CgaChar_h

#include "device/CgaAttr.h"

/*
 * CgaChar:
 * 
 *	Diese Klasse stellt den Prototyp eines
 *	Zeichens des Bildschirms dar.
 *	Dieses besteht aus darstellbarem Zeichen
 *	und Darstellungsattributen.
 */


class CgaChar {

public:
	//! setzen des Zeichens
	void setChar(unsigned char c)
	{
		this -> zeichen = c;
	}
	
	//! auslesen des Zeichens
	unsigned char getChar()
	{
		return this -> zeichen;
	}
	
	//! setzen der Darstellungsattribure
	void setAttr(const CgaAttr& attr)
	{
		attribut = attr;
	}
	
	//! auslesen der Darstellungsattribute
	CgaAttr getAttr()
	{
		return attribut;
	}

private:
	//! das zu zeichnene zeichen
  unsigned char zeichen;
  //! die darstellungsattribute fuer das zeichen
	CgaAttr attribut;
};

#endif

