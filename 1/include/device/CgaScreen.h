#ifndef CgaScreen_h
#define CgaScreen_h

#include "device/CgaAttr.h"
#include "device/CgaChar.h"
#include "io/IOPort.h"

/*
 * CgaScreen:	Diese Klasse ist der Softwareprototyp fuer den
 *		CGA-Bildschirm
 *		Man beachte:
 *		Unter den auszugebenden Zeichen befinden
 *		sich sogenannte Steuerzeichen, die geeignet
 *		zu interpretieren sind.
 *
 *		Es reicht fuer diese Uebung, wenn Ihr die
 *		Steuerzeichen '\n' (newline, NL) und '\r' (Carriage Return, CR)
 *		interpretiert.
 *		Bei CR ist der Cursor auf den Anfang der aktuellen Zeile
 *		zu setzen. Bei NL wird der Cursor auf den Anfang
 *		der naechsten Zeile gesetzt.
 */


class CgaScreen {

private:

	// Die I/O-Ports des Grafikcontrollers
	enum Ports  {
		INDEXPORT = 0x3D4,
		DATENPORT = 0x3D5
	};
	
	// Die Kommandos zum Cursor setzen
	enum Cursor {
		HIGH = 14,
		LOW = 15
  };

	// Die Adresse des Video RAMs
	enum Video  {
		VIDEO_BASE = 0xB8000
	}; 

public:
	// Die Bildschirmdimensionen
	enum Screen {
		ROWS = 25,
		COLUMNS = 80
	};

	// Standardattribute waehlen und Bildschirm loeschen
	CgaScreen();

	// Angegebene Attribute setzen und Bildschirm loeschen
	CgaScreen(CgaAttr attr);

	// Loeschen des Bildschirms
	void clear ();

	// Verschieben des Bildschirms um eine Zeile
	void scroll();

	// Setzen/Lesen der globalen Bildschirmattribute
	void setAttr(const CgaAttr& attr)
	{
		this -> attr = attr;
	};

	void getAttr(CgaAttr& attr)
	{
		attr = this -> attr;
	};

	// Setzen/Lesen des HW-Cursors
	void setCursor(int row, int column);
	void getCursor(int& row, int& column);


	// Anzeigen von c an aktueller Cursorposition
    	// Darstellung mit angegebenen Bildschirmattributen
	void show(char ch, const CgaAttr& attr);

	// Anzeigen von c an aktueller Cursorposition
    	// Darstellung mit aktuellen Bildschirmattributen
	void show(char ch)
	{
    this -> show(ch, this -> attr);
	};


protected:

	CgaAttr attr;
	IOPort8 index;
	IOPort8 data;
	CgaChar* screen;


};

#endif
