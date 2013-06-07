#include "device/CgaChannel.h"
#include "io/OutputChannel.h"
#include "device/CgaScreen.h"

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
  unsigned i = 0;

  while(i < size) {
    this -> show(data[i]);
    i++;
  }
  return size;
}