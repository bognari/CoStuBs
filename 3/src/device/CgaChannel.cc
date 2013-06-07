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

#include "device/CgaChannel.h"


// Ausgabekanal mit Standardattributen
CgaChannel::CgaChannel()
{
  this -> setAttr(CgaAttr());
}

// Ausgabekanal mit spezifischen Attributen
CgaChannel::CgaChannel(const CgaAttr& attr)
{
  this -> setAttr(attr);
}

// Die von OutputChannel deklarierte Ausgaberoutine
int CgaChannel::write(const char* data, int size)
{
  int i = 0;

  while(i < size) {
    // utf8 zu page code 437 fix:
    if (((unsigned char)data[i] == 0xC3) && (i + 1 < size)) {
      switch ((unsigned char) data[i+1]) {
        case 0xA4 : i += 2; this -> show(0x84); break; //ä
        case 0x84 : i += 2; this -> show(0x8E); break; //Ä
        case 0xB6 : i += 2; this -> show(0x94); break; //ö
        case 0x96 : i += 2; this -> show(0x99); break; //Ö
        case 0xBC : i += 2; this -> show(0x81); break; //ü
        case 0x9C : i += 2; this -> show(0x9A); break; //Ü
        case 0x9F : i += 2; this -> show(0xE1); break; //ß
        default : this -> show(data[i]); i++; break;
      }
    } else if (((unsigned char)data[i] == 0xC2) && (i + 1 < size)) {
      switch ((unsigned char) data[i+1]) {
        case 0xA7 : i += 2; this -> show(0x15); break; //§
        case 0xB2 : i += 2; this -> show(0xFD); break; //²
        case 0xB3 : i += 2; this -> show(0x5E); this -> show(0x33); break; //³
        case 0xB5 : i += 2; this -> show(0xE6); break; // µ
        case 0xB4 : i += 2; this -> show(0x60); break; // ist zwar genau der andere aber sonst muesste man fuer jered zeichen etwas batseln... naja mal gucken
        default : this -> show(data[i]); i++; break;
      }
    } else if((((unsigned char)data[i] == 0xE2) && (i + 2 < size)) && (((unsigned char)data[i + 1] == 0x82) && ((unsigned char)data[i + 2] == 0xAC))) {
      this -> show('E');
      this -> show('U');
      this -> show('R');
      this -> show('O');
      i +=3;
    } else {
      this -> show(data[i]);
      i++;
    }
  }
  return size;
}
