# -----------------------------------------------------------------------------
#
#                              M A K E F I L E
#
# zum Uebungsbetriebssystem Co-Stubs der Lehrveranstaltung
# 'Betriebssysteme 1' an der BTU-Cottbus im SS11
# -----------------------------------------------------------------------------
#
# Folgende Make-Targets sind moeglich
#
# depend 	: ueberprueft alle Abhaengigkeiten und schreibt diese in eine Datei
# system.img 	: erstellt das Speicherabbild des Betriebssystems
# bootdisk.img	: erstellt das Speicherabbild des Betriebssystem + Bootcode
# bootdisk	: kopiert das bootfaehig Speicherabbild auf Diskette
# clean		: loescht alle generierten Dateien
#
# -----------------------------------------------------------------------------
#LINUX and CYGWIN so far
GENSYS = LINUX

INITFINI =

# Liste der Quelltexte:
# (Beim Hinzufuegen neuer Module erweitern!)
# Achtung!!!! Hinter dem backslash am Zeilenende darf *kein* Zeichen stehen!!
# Die letzte Zeile bekommt kein backslash!!!


STARTUP_S = \
	boot/startup.asm

BOOT_S = \
	boot/bootsect.asm \
	boot/setup.asm

MACHINE_S = \
	cpu/cpu.asm \
	io/ports.asm \
	thread/switchContext.asm

SYSTEM_C = \
	lib/tools.c

# mainCga
# SYSTEM_CC = \
# 	$(INITFINI) \
# 	device/CgaChannel.cc \
# 	device/CgaScreen.cc \
# 	io/PrintStream.cc \
#     mainCga.cc

# mainAct
# SYSTEM_CC = \
# 	$(INITFINI) \
# 	device/CgaChannel.cc \
# 	device/CgaScreen.cc \
# 	io/PrintStream.cc \
# 	lib/Queue.cc \
#		thread/Activity.cc \
#		thread/ActivityScheduler.cc \
# 	thread/Coroutine.cc \
#		thread/Scheduler.cc \
#     mainAct.cc

# mainCo
#SYSTEM_CC = \
#	 $(INITFINI) \
#	 device/CgaChannel.cc \
#	 device/CgaScreen.cc \
#	 io/PrintStream.cc \
#	 lib/Queue.cc \
#	 thread/Coroutine.cc \
#    mainCo.cc

# mainPre
#SYSTEM_CC = \
#  $(INITFINI) \
#  device/CgaChannel.cc \
#  device/CgaScreen.cc \
#	 device/Clock.cc \
#	 device/PIC.cc \
#	 device/PIT.cc \
#	 interrupts/Gate.cc \
#	 interrupts/InterruptGuardian.cc \
#	 interrupts/PageFaultGate.cc \
#	 interrupts/PanicGate.cc \
#  io/PrintStream.cc \
#  lib/Queue.cc\
#	 thread/Activity.cc \
#	 thread/ActivityScheduler.cc \
#  thread/Coroutine.cc \
#	 thread/Scheduler.cc \
#    mainPre.cc

# mainInt
#SYSTEM_CC = \
#  $(INITFINI) \
#  device/CgaChannel.cc \
#  device/CgaScreen.cc \
#	 device/Clock.cc \
#  device/PIC.cc \
#	 device/PIT.cc \
#	 interrupts/Gate.cc \
#	 interrupts/InterruptGuardian.cc \
#	 interrupts/PageFaultGate.cc \
#	 interrupts/PanicGate.cc \
#  io/PrintStream.cc \
#  lib/Queue.cc \
#	 thread/Activity.cc \
#	 thread/ActivityScheduler.cc \
#  thread/Coroutine.cc \
#	 thread/Scheduler.cc \
#    mainInt.cc

# mainKbd
#SYSTEM_CC = \
# $(INITFINI) \
# device/CgaChannel.cc \
# device/CgaScreen.cc \
# device/CodeTable.cc \
# device/Keyboard.cc \
#	device/Clock.cc \
#	device/PIC.cc \
#	device/PIT.cc \
#	interrupts/Gate.cc \
#	interrupts/InterruptGuardian.cc \
#	interrupts/PageFaultGate.cc \
#	interrupts/PanicGate.cc \
# io/PrintStream.cc \
# lib/Queue.cc\
#	thread/Activity.cc \
#	thread/ActivityScheduler.cc \
# thread/Coroutine.cc \
#	thread/Scheduler.cc \
#   mainKbd.cc

# mainEditor
#SYSTEM_CC = \
# $(INITFINI) \
# device/CgaChannel.cc \
# device/CgaScreen.cc \
# device/CodeTable.cc \
# device/Keyboard.cc \
#	device/Clock.cc \
#	device/PIC.cc \
#	device/PIT.cc \
#	interrupts/Gate.cc \
#	interrupts/InterruptGuardian.cc \
#	interrupts/PageFaultGate.cc \
#	interrupts/PanicGate.cc \
# io/PrintStream.cc \
# lib/Queue.cc\
#	thread/Activity.cc \
#	thread/ActivityScheduler.cc \
# thread/Coroutine.cc \
#	thread/Scheduler.cc \
#	software/lib/tree/MyTree.cc \
#	software/Editor.cc \
#   mainEditor.cc

# mainMonitor
SYSTEM_CC = \
  $(INITFINI) \
  device/CgaChannel.cc \
  device/CgaScreen.cc \
  device/CodeTable.cc \
  device/Keyboard.cc \
	device/Clock.cc \
	device/PIC.cc \
	device/PIT.cc \
	interrupts/Gate.cc \
	interrupts/InterruptGuardian.cc \
	interrupts/PageFaultGate.cc \
	interrupts/PanicGate.cc \
  io/PrintStream.cc \
  lib/Queue.cc \
  sync/KernelSemaphore.cc \
  sync/Monitor.cc \
  system/Console.cc \
	thread/Activity.cc \
	thread/ActivityScheduler.cc \
  thread/Coroutine.cc \
	thread/Scheduler.cc \
	user/Hello.cc \
	user/Init.cc \
    mainMonitor.cc


##############################################################################

STARTUP_SOURCE = $(addprefix ../machine/,$(STARTUP_S))
BOOT_SOURCES = $(addprefix ../machine/,$(BOOT_S))
MACHINE_SOURCES = $(addprefix ../machine/,$(MACHINE_S))
SYSTEM_SOURCES = $(addprefix ../src/,$(SYSTEM_CC))
SYSTEM_C_SOURCES = $(addprefix ../src/,$(SYSTEM_C))

SOURCES = $(MACHINE_SOURCES) $(SYSTEM_SOURCES) $(SYSTEM_C_SOURCES)

FIRST_OBJECT = $(notdir $(STARTUP_SOURCE:.asm=.o))

BOOT_FILES = $(notdir $(BOOT_SOURCES:.asm=.bin))

OBJECTS = $(patsubst %.asm,%.o,$(patsubst %.c,%.o,$(patsubst %.cc,%.o,$(notdir $(SOURCES))) ))

VPATH = $(dir $(SOURCES) $(STARTUP_SOURCE) $(BOOT_SOURCES))

INCLUDES = -I../include \
	-I../machine

DEPENDENCIES_FILE = Dependencies.mk

##############################################################################

# Einstellungen in Abhaengigkeit vom Generierungssystem:
#
#    ASMOBJFORMAT: Ausgabeformat fuer den Assembler. Das Format muss dem
#                  jeweiligen Format des verwendeten C++ Compilers angepasst
#                  werde, damit gemischte Objektdateien gelinkt werden koennen.
#    DRIVE:        Laufwerk, auf das das System-Image geschrieben wird.
#    ASM:          Zu benutzender Assembler
#    CC/CXX:       Zu benutzender C/C++-Compiler.
#    LD:           Zu benutzender Linker.
#    LDLIBS:       Dazuzulinkende Bibliotheken
#    LDHEAD:       Am Anfang zu linkende Dateien
#    LDTAIL:       Am Ende zu linkende Dateien

AS = nasm
CC = gcc
CXX = g++
# CXX = clang++
LD = ld

ifeq ($(GENSYS), LINUX)

ASFLAGS = -DLINUX -f elf32
CFLAGS = -c -m32 -fno-stack-protector -DLINUX -Wall -fno-exceptions $(INCLUDES)
CXXFLAGS = -c -m32 -fno-stack-protector -DLINUX -Wall -fno-rtti -fno-exceptions $(INCLUDES)
LDFLAGS = -melf_i386 -e startup -T ../machine/linux.ls -o system
LDHEAD = $(shell g++ -m32 --print-file-name=crti.o && \
	   g++ -m32 --print-file-name=crtbegin.o)
LDTAIL = $(shell g++ -m32 --print-file-name=crtend.o && \
	   g++ -m32 --print-file-name=crtn.o)

endif

# Einstellungen, die von der jeweiligen Installation und dem geplanten
# Zielsystem abhaengen:
#
#    TOOLS:      Verzeichnis mit Hilfsprogrammen, die im Rahmen der LV zur
#                Verfuegung gestellt werden.
#    BOOT:       Zur Verfuegung gestelltes Verzeichnis mit Dateien, die
#                benoetigt werden, um eine Bootdiskette zu erzeugen.
#    BOOTDEVICE: Beschreibung des Geraetes von dem das System spaeter
#                gebootet wird. Beispiele:
#                0:80:2:18:0:0:1 - 3.5" Diskette im 1. Laufwerk (A)
#                1:80:2:15:0:0:1 - 5.25" Diskette im 2. Laufwerk (B)
#                Eine genauere Beschreibung erhaelt man durch Starten von
#                'build' (gehoert zu den Tools der LV) ohne Parameter.
#

TOOLS      = ../tools/bin

BOOT       = ../boot
BOOTDEVICE = 0:80:2:18:0:0:1

DRIVE = /dev/fd0

# -------------------------------------------------------------------------
# Die Targets fuer die Kompilierung

%.o : %.asm
	$(AS) $(ASFLAGS) -o $@ $<

%.bin : %.asm
	$(AS) -f bin -o $@ $<

%.o : %.cc
	$(CXX) $(CXXFLAGS) -o $@ $<

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

# Linken des Systems
system : $(FIRST_OBJECT) $(OBJECTS)
	$(LD)  $(LDFLAGS) $(FIRST_OBJECT) $(LDHEAD) $(OBJECTS) $(LDTAIL)

# Das Speicherabbild des Systems
system.img : system $(DEPENDENCIES_FILE)
	objcopy -O binary system system.img

# Das Speicherabbild des Bootfaehigen Systems
bootdisk.img : system.img $(BOOT_FILES)
	$(TOOLS)/build $(BOOT_FILES) system.img $(BOOTDEVICE) bootdisk.img

# erstellt eine Bootdiskette
bootdisk: bootdisk.img
	-cp bootdisk.img $(DRIVE)


# Bekanntmachen von Targets die keine Abhaengigkeiten haben
.PHONY: clean depend

depend:
	@echo "" > $(DEPENDENCIES_FILE)
ifneq ($(strip $(SYSTEM_SOURCES)),)
	$(CXX) -MM $(CXXFLAGS) $(SYSTEM_SOURCES) >> $(DEPENDENCIES_FILE)
endif

clean:
	@rm -f *.o
	@rm -f $(DEPENDENCIES_FILE)

# erstellt die Datei mit den Abhaengigkeiten
$(DEPENDENCIES_FILE):
	touch $(DEPENDENCIES_FILE)
	$(MAKE) depend

# einbinden der Datei mit den aktuellen Abhaengigkeiten
sinclude $(DEPENDENCIES_FILE)

