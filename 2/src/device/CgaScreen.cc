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

#include "device/CgaScreen.h"
#include "device/CgaAttr.h"
#include "io/IOPort.h"

extern "C" { // ok doch einfacher als ich dachte
  #include "lib/tools.h"
}

// Standardattribute waehlen und Bildschirm loeschen
CgaScreen::CgaScreen():index(INDEXPORT), data(DATENPORT)
{
  this -> setAttr(CgaAttr()); // setzt die default einstellungen, da der leere konstruktor aufgerufen wurde
  this -> show('\f');
}

// Angegebene Attribute setzen und Bildschirm loeschen
CgaScreen::CgaScreen(CgaAttr attr):index(INDEXPORT), data(DATENPORT)
{
  this -> attr = attr;
  this -> show('\f');
}

// Loeschen des Bildschirms
void CgaScreen::clear()
{
  this -> screen = (CgaChar*)VIDEO_BASE;
  for (int i = 0; i < (ROWS * COLUMNS); i++)
  {
    this -> screen[i].setChar((unsigned char)' ');
    this -> screen[i].setAttr(CgaAttr());
  }
  this -> setCursor(0, 0); // da in der versuchs main sinnfreierweise aus auch gerufen wird statt print('\f')
}

// Verschieben des Bildschirms um eine Zeile
void CgaScreen::scroll()
{
  void* dest = (void*)VIDEO_BASE;
  const void* src = (void*)(VIDEO_BASE + (COLUMNS * 2));
  unsigned n = (ROWS - 1) * COLUMNS * 2;
  
  memcpy(dest, src, n);
  
  for (int i = 0; i < COLUMNS; i++)
  { // loescht die letzte Zeile (daten und attribute)
    this -> screen[(ROWS - 1) * COLUMNS + i].setChar((unsigned char)' ');
    this -> screen[(ROWS - 1) * COLUMNS + i].setAttr(CgaAttr()); // dann halt den urstandart laden statt den momentan gesetzten
  }
}

// Setzen/Lesen des HW-Cursors
void CgaScreen::setCursor(int row, int column)
{
  // "overflow" abfangen
  // testen ob column = valid
  while (column >= COLUMNS) { // wird nur einmal druchlaufen aber evtl geht es ja auch mehr
      column = column - COLUMNS; // fast immer null aber ka evtl doch mal weiter nach innen
      row++;
  }

  while (row >= ROWS) { // testen ib row = valid
    row--; // wird auch meistens nur ein mal druch geführt
    this -> scroll();
  }

  // "underflow" abfangen

  while (column < 0) {
    column = column + COLUMNS;
    row--;
  }

  if (row < 0) { // ein hoch scrollen haben wir ja nicht deswegen dann 0
    row = 0;
  }

  unsigned posi = row * COLUMNS + column;
  char low_posi = posi;
  char high_posi = posi >> 8;
  this -> index.write(LOW);
  this -> data.write(low_posi);
  this -> index.write(HIGH);
  this -> data.write(high_posi);
}

// ok ab posi 128 = -1 wtf vorzeichenbit ~~
void CgaScreen::getCursor(int& row, int& column)
{
  this -> index.write(LOW);
  unsigned low_posi = this -> data.read();
  this -> index.write(HIGH);
  unsigned high_posi = this -> data.read();
  unsigned posi = 0;
  posi = high_posi;
  posi = posi << 8;
  posi = posi | low_posi;
  row = (int)(posi / COLUMNS);
  column = (int)(posi % COLUMNS);
}


// Anzeigen von c an aktueller Cursorposition
// Darstellung mit angegebenen Bildschirmattributen
void CgaScreen::show(char ch, const CgaAttr& attr)
{
  // damit er NIE NIE NIEEEEEE !!!! etwas versucht zu zeichnen das er net darf !
  // alle sichtbaren zeichen.
  // ok er nutzt kein ascii sondern code page 437... gut zu wissen
  unsigned char c = (unsigned char) ch;
  if ((31 < (int)c && (int)c != 127) || c == '\b' || c == '\t' || c == '\n' || c == '\f' || c == '\r' || c == '\v' || c == 0x15) {

    this->screen = (CgaChar*)VIDEO_BASE;
    int y, x;
    this -> getCursor(y, x);
    this -> screen = (CgaChar*)VIDEO_BASE;

    switch (c)
    {
      case '\n': { // geht in die neue zeite und setzt den cursor an den anfang
        y++;
        x = 0; // zwar falsch aber wollen es ja so....
      }; break;
      case '\r': { // setzt den cursor an den anfang
        x = 0;
      }; break;
      case '\b': { // geht einen schritt zurueck. wenn der curser am anfang war dann geht er eine zeile nach oben ans ende. löscht auch das alte zeichen.    
        x--;
        if ((y * COLUMNS + x) >= 0) {
          this -> screen[y * COLUMNS + x].setChar((unsigned char)' ');
          this -> screen[y * COLUMNS + x].setAttr(attr);
        }
      }; break;
      case '\t' : { // tabzeichen 4 ' ' breit
        // schreibt selber keine ' ' sondern setzt den courser 4 zeichen weiter. oder auf die neue zeile
        x = ((x / 4) * 4) + 4;
      }; break;
      case '\v' : { // Vtabzeichen 4 '\n' hoch
        y = ((y / 4) * 4) + 4;
      }; break;
      case '\f' : { // loescht den screen und setzt den cursor wieder auf 0/0
        this -> clear();
        x = 0;
        y = 0;
      }; break;
      default: {
        this -> screen[y * COLUMNS + x].setChar(c);
        this -> screen[y * COLUMNS + x].setAttr(attr);
        x++;
      }; break;
    }
    this -> setCursor(y, x);
  }
}
