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
	// Ausgabekanal mit Standardattributen
	CgaChannel() ;

	// Ausgabekanal mit spezifischen Attributen
	CgaChannel(const CgaAttr& attr);

	// Die von OutputChannel deklarierte Ausgaberoutine
	virtual int write(const char* data, int size);
};

#endif
