#ifndef CgaAttr_h
#define CgaAttr_h

/*
 * CgaAttr: 	Softwareprototyp fuer CGA Darstellungsattribute
 *		Hier braucht man Bitoperationen!
 *
 *		Da *alle* Operationen sehr einfach und kurz sind,
 *		duerft Ihr sie direkt in der Klasse
 *		als inline Methoden deklarieren.
 */

class CgaAttr {
private:
	enum AttrMaskAndShifts {
    FGP = 0, // Positionen
    BGP = 4,
    BLP = 7,
    FGCLEAR = 0xF0, // 11110000 // bei & bleiben alle werde bis auf die die geloescht werden sollen
    BGCLEAR = 0x8F, // 10001111
    BLCLEAR = 0x7F, // 01111111
    BGMAX = 7,  // da wir nur 3 bit haben ist die max zahl 7
    FGMASK = 0x0F, //  00001111 // eingabe Masken
    BGMASK = 0x07, //  00000111
    BLMASK = 0x01  //  00000001
  };
// 1 byte
// bit 0 - 3 fg | 4
// bit 4 - 6 bg | 3
// bit 7 blink  | 1

public:
	/**	Diese Aufzählung enthält die CGA-Farben als Farbkonstanten
	 *	Tragt hier *alle* CGA Farben mit den richtigen Werten ein
	 */
	enum Color {BLACK = 0, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE};
//0	Schwarz		8	Dunkelgrau
//1	Blau		9	Hellblau
//2	Grün		10	Hellgrün
//3	Cyan		11	Hellcyan
//4	Rot			12	Hellrot
//5	Magenta		13	Hellmagenta
//6	Braun		14	Gelb
//7	Hellgrau	15	Weiß

	/** Konstruktor. Erzeugt ein CgaAttr-Objekt mit den uebergebenen Werten für
	  * Vorder- und Hintergrundfarbe. Werden keine Parameter uebergeben,
	  * so werden die Defaultwerte (Vordergrund weiss, Hintergrund schwarz, Blinken deaktiviert)
	  * verwendet.
	  */
	CgaAttr(Color fg=WHITE, Color bg=BLACK, bool blink=false)
	{
    if (bg > 7) {
      bg = BLACK;
    }
    this -> value = (blink << BLP) | (bg << BGP) | (fg << FGP); 
	}

	// setzen der Schriftfarbe
	void setForeground(Color col)
	{
    this -> value = (this -> value & FGCLEAR) | (col << FGP); // setzt den alten wert null und schreibt den neuen rein.
	}

	// setzen der Hintergrundfarbe
	void setBackground(Color col)
	{
    if (col > 7) {
      col = Color(col);
    }
    this -> value = (this -> value & BGCLEAR) | (col << BGP);
	}

	// setzen blinkender/nicht blinkender Text
	void setBlinkState(bool blink)
	{
    this -> value = (this -> value & BLCLEAR) | (blink << BLP);
	}

	// setzen aller Attribute
	void setAttr(CgaAttr attr)
	{
    this -> value = attr.value;
	}

	// ermitteln der Schriftfarbe
	Color getForeground()
	{ // unsinniges loeschen und shiften
    return (Color) ((this -> value & (~FGCLEAR)) >> FGP);
	}

	// ermitteln der Hintergrundfarbe
	Color getBackground()
	{
    return (Color) ((this -> value & (~BGCLEAR)) >> BGP);
	}

	// ermitteln ob Blink-Flag gesetzt ist
	bool getBlinkState()
	{
    return (bool) ((this -> value & (~BLCLEAR)) >> BLP);
	}

private:
  char value;
};

#endif
