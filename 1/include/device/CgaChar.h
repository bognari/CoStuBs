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
	// setzen des Zeichens
	void setChar(char c) {
		this -> zeichen = c;
	}
	
	// auslesen des Zeichens
	char getChar() {
		return this -> zeichen;
	}
	
	// setzen der Darstellungsattribure
	void setAttr(const CgaAttr& attr) {
		attribut = attr;
	}
	
	// auslesen der Darstellungsattribute
	CgaAttr getAttr() {
		return attribut;
	}

private:
	char zeichen; // das zu zeichnene zeichen
	CgaAttr attribut; // die darstellungsattribute fuer das zeichen
};

#endif

