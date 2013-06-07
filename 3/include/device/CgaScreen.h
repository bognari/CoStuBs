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

#ifndef CgaScreen_h
#define CgaScreen_h

#include "device/CgaAttr.h"
#include "device/CgaChar.h"
#include "io/IOPort.h"

extern "C" {
  #include "lib/tools.h"
}

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

	//! Die I/O-Ports des Grafikcontrollers
	enum Ports  {
		INDEXPORT = 0x3D4,
		DATENPORT = 0x3D5
	};
	
	//! Die Kommandos zum Cursor setzen
	enum Cursor
	{
		HIGH = 14,
		LOW = 15
  };

	//! Die Adresse des Video RAMs
	enum Video
	{
		VIDEO_BASE = 0xB8000
	}; 

public:
	//! Die Bildschirmdimensionen
	enum Screen
	{
		ROWS = 25,
		COLUMNS = 80
	};

	//! Standardattribute waehlen und Bildschirm loeschen
	CgaScreen();

	//! Angegebene Attribute setzen und Bildschirm loeschen
	CgaScreen(CgaAttr attr);

	//! Loeschen des Bildschirms
	void clear ();

	//! Verschieben des Bildschirms um eine Zeile
	void scroll();

	//! Setzen der globalen Bildschirmattribute
	void setAttr(const CgaAttr& attr)
	{
		this -> attr = attr;
	};
	//! Setzen der globalen Bildschirmattribute
	void getAttr(CgaAttr& attr)
	{
		attr = this -> attr;
	};

	//! Setzen des HW-Cursors
	void setCursor(int row, int column);
	//! Lesen des HW-Cursors
  void getCursor(int& row, int& column);


	/*! Anzeigen von c an aktueller Cursorposition
   *  Darstellung mit angegebenen Bildschirmattributen
   */ 
	void show(char ch, const CgaAttr& attr);

	/*! Anzeigen von c an aktueller Cursorposition
   *  Darstellung mit aktuellen Bildschirmattributen
   */
	void show(char ch)
	{
    this -> show(ch, this -> attr);
	};


protected:
	//! die momentan gesetzten attribute
	CgaAttr attr;
	IOPort8 index;
	IOPort8 data;
	//! ein zeiger auf einen cgachar der als bildschrim benutzt wird
	CgaChar* screen;
	//! um etwas mehr preformace raus zu holen. man muss ja nicht immer die hw fragen wo wir uns ebend befinden
	int xPosi;
	int yPosi;
};

#endif
