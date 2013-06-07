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

#include "thread/Coroutine.h"

/*
 * Coroutine:
 * Diese Klasse implementiert Coroutinen, welche die Basis
 * für alle Arten von Prozessen in Co-Stubs sind.
 *
 *  Anmerkung: wir verwenden ein objektorientiertes
 *  Coroutinen-Modell, daher ist diese Klasse abstrakt.
 *  Eine Coroutine muss sich von dieser Klasse ableiten
 *  und eine "body" Methode definieren.
 *  Diese Methode ist dann gewissermassen die "main" Funktion
 *  fuer die Coroutine.
 *
 */


/* Diese Funktion hat nur die Aufgabe
 * den Rumpf der uebergebenen Coroutine aufzurufen
 * und nach der Rueckkehr exit() aufzurufen,
 * um die Termination des Rumpfes bekanntzugeben.
 * Diese Prozedur dient so als eine Bruecke zwischen der
 * nicht objektorientierten und der objektorientierten Welt
 * Beachte, das "startup" als "static deklariert ist
 * und deshalb keinen impliziten "this"-Zeiger uebergeben bekommt.
 */
void Coroutine::startup(Coroutine* obj)
{
  cpu.enableInterrupts();
  obj -> body();  // leben
                  // und
  obj -> exit();  // sterben
}

/* Aufsetzen einer neuen Coroutine.
 * Der Parameter "tos" (top of stack) ist der
 * initiale Stackpointerwert fuer die neue Coroutine
 * ACHTUNG: tos kann NULL sein (siehe Constructor)!
 */
void Coroutine::setup(void* tos) {
  if(tos != 0) { // wenn null dann laeuft er auf dem main stack und brauch dadurch keinen eigenen.
    TOS* _tos = (TOS*) tos;
    _tos--; // richtige adresse holen

    _tos -> edi = 0;
    _tos -> esi = 0;
    _tos -> ebx = 0;
    _tos -> ebp = 0;
    _tos -> coroutine = startup;
    _tos -> nirwana = 0;
    _tos -> arg = this;

    this -> sp = _tos;
  }
}
