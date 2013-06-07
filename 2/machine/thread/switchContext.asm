; This file is part of CoStuBS.
;
; CoStuBS is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
;
; CoStuBS is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with CoStuBS.  If not, see <http://www.gnu.org/licenses/>.



%include "../machine/csym.inc"	; Innerhalb des Include-Files 'csym.inc'
				; wird das Macro CSYM(name) definiert,
				; das dem uebergebenen Symbolnamen in
				; Abhaegigkeit vom verwendeten Generierungs-
				; system einen Unterstrich ('_') voranstellt.

; EXPORTIERTE FUNKTIONEN

csym switchContext

[GLOBAL switchContext]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; switchContext: Der Coroutinenwechsel
;
; C-Prototyp:
;
;     void switchContext (void*& from, void*& to);
;

switchContext:
; fuegt hier Euren Code ein!
  push ebp      ; ebp des aufrufers retten
  mov ebp, esp  ; eigenen ebp setzen

; lasst das retten beginnen
  push ebx;
  push esi;
  push edi;

; from parameter

  mov eax, [ebp + 8]
  mov [eax], esp ; from esp retten

; to parameter

  mov eax, [ebp + 12]
  mov esp, [eax]; und den neuen esp setzen

; wiederherstellen der "neuen" register
  pop edi
  pop esi
  pop ebx

  pop ebp ; am ende die basis wieder setzen

  ret ; Ruecksprung zum Aufrufer
