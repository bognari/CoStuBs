#include "device/CgaChannel.h"
#include "io/PrintStream.h"

//der Wert sollte variiert werden oder man bastelt sich lieber eine rein "zeitabhängige" Pause ;)
#define PAUSE 100000


CgaChannel cga;        // unser CGA-Ausgabekanal
PrintStream out(cga);    // unseren PrintStream mit Ausgabekanal verknuepfen

int main()
{
    out.println("Test der formatierten Ausgabe zur Basis:");

    for(int i = -30; i < 30; i++)
    {
        if (i % 6 == 0)
        {
            out.print("Dezimal: ");
            out.print(i);
            out.print(" ; Binaer: ");
            out.print(i, 2);
            out.print(" ; Hexadezimal: ");
            out.print(i, 16);
            out.println();
        }
    }

    out.println();
    out.print("Test mit falscher Basis: out.print(133,7): ");
    out.print(133, 7);

    out.println();
    out.println();
    out.println("Es folgen alle Farbkombinationen:");
    for(int blink = 0; blink < 2; blink++)
    {
        for(int bg = 0; bg < 8; bg++)
        {
            for(int fg = 0; fg < 16; fg++)
            {
                cga.setAttr(CgaAttr((CgaAttr::Color) (fg), (CgaAttr::Color) (bg), (CgaAttr::Color) blink));
                out.print("X");
            }
        }
    }

    out.println("\n");
    //kurze Pause
   for(int i = 0; i < PAUSE; i++)
   {
        out.print("\r|\r\\\r-\r/");
    };

    cga.setAttr(CgaAttr());
    cga.clear();
    cga.setAttr(CgaAttr(CgaAttr::RED, CgaAttr::YELLOW, false));
    for(int i = 0; i < 19; i++)
    {
        cga.setCursor((i < 9)?i:(18-i), i);
        out.println("x");

        cga.setCursor((i < 9)?i:(18-i), i+19);
        out.println("x");

        cga.setCursor((i < 9)?i:(18-i), i+38);
        out.println("x");

        cga.setCursor((i < 9)?i:(18-i), i+57);
        out.println("x");
    }
    cga.setCursor(11,0);
    cga.setAttr(CgaAttr());

    out.println("Test der Sonderzeicheninterpretation:");
    out.print("Hier stehen jetzt fuenf Worte\nund auf der naechsten Zeile geht es weiter.\nHier wird gleich \"Hier\" ueberschrieben");

/*
    //kurze Pause zum Test
    for(int i = 0; i < PAUSE; i++)
    {
        out.print("\r|\r\\\r-\r/");
    };
*/

    cga.setAttr(CgaAttr(CgaAttr::GREEN, CgaAttr::BLUE, false));
    out.println("\rDort\n");

    out.println("Das ist ein Testsatz, der laenger als 80 Zeichen sein soll. Mal sehen, ob der Zeilenumbruch klappt. Haha Haha Haha Haha Haha Haha Haha Haha.\n");

    out.println("Gleich wird das Scrollen getestet. Das Scrollen sollte uebrigens mit der selber zu schreibenden memcpy-Methode geloest werden - Zusatzaufgabe (und nicht mit einer einfachen Zuweisung).");
    out.println("\n");
    //kurze Pause
    for(int i = 0; i < PAUSE; i++)
    {
        out.print("\r|\r\\\r-\r/");
    };

    for (int i = 0; i < 40; i++)
    {
        cga.setAttr(CgaAttr((CgaAttr::Color) (i % 16), (CgaAttr::Color) (8), (CgaAttr::Color) false));
        out.print("Gleich wird das Scrollen getestet. Das Scrollen sollte uebrigens mit der selber zu schreibenden memcpy-Methode geloest werden - Zusatzaufgabe (und nicht mit einer einfachen Zuweisung).");

    };


    out.println("\n\nSonderzeichentest:\näöü;,:.-_");

    out.println();

    out.println("Ausgabe von Adressen...");
    out.println("Wie weit liegen sie auseinander? Warum?");
    int x = 5;
    int y = 6;
    out.print("x: ");
    out.print(&x);
    out.print("; y: ");
    out.print(&y);
	out.println("\n");


    out.println("Test von Grenzwerten:");
    unsigned ux = 0;
    out.print("0x0: ");
    out.print(ux, 16);
    out.println();
    ux = 0xFFFFFFFF;
    out.print("0xFFFFFFFF: ");
    out.print(ux, 16);

	out.println("\n");
    out.println("Ende.");
	out.println("\n");


    //kurze Pause
    for(int i = 0; i < PAUSE; i++)
    {
        out.print("\r|\r\\\r-\r/");
    };

	int i = 0;
	bool help = false;
	CgaAttr attr;

	cga.clear();
	for (int k = 0; k < ((25 * 80)-1); k++) {
		switch (i) {
			case 0:
				attr.setForeground(attr.BLACK);
				attr.setBackground(attr.BLACK);
				break;
			case 1:
				attr.setForeground(attr.BLUE);
				attr.setBackground(attr.BLUE);
				break;
			case 2:
				attr.setForeground(attr.GREEN);
				attr.setBackground(attr.GREEN);
				break;
			case 3:
				attr.setForeground(attr.CYAN);
				attr.setBackground(attr.CYAN);
				break;
			case 4:
				attr.setForeground(attr.RED);
				attr.setBackground(attr.RED);
				break;
			case 5:
				attr.setForeground(attr.MAGENTA);
				attr.setBackground(attr.MAGENTA);
				break;
			case 6:
				attr.setForeground(attr.BROWN);
				attr.setBackground(attr.BROWN);
				break;
			case 7:
				attr.setForeground(attr.LIGHTGREY);
				attr.setBackground(attr.LIGHTGREY);
				break;
			case 8:
				attr.setForeground(attr.DARKGREY);
				attr.setBackground(attr.DARKGREY);
				break;
			case 9:
				attr.setForeground(attr.LIGHTBLUE);
				attr.setBackground(attr.LIGHTBLUE);
				break;
			case 10:
				attr.setForeground(attr.LIGHTGREEN);
				attr.setBackground(attr.LIGHTGREEN);
				break;
			case 11:
				attr.setForeground(attr.LIGHTCYAN);
				attr.setBackground(attr.LIGHTCYAN);
				break;
			case 12:
				attr.setForeground(attr.LIGHTRED);
				attr.setBackground(attr.LIGHTRED);
				break;
			case 13:
				attr.setForeground(attr.LIGHTMAGENTA);
				attr.setBackground(attr.LIGHTMAGENTA);
				break;
			case 14:
				attr.setForeground(attr.YELLOW);
				attr.setBackground(attr.YELLOW);
				break;
			case 15:
				attr.setForeground(attr.WHITE);
				attr.setBackground(attr.WHITE);
				break;
		}
		attr.setBlinkState(help);
		cga.setAttr(attr);
		out.print('#');
		help = not help;
		i++;
		if (i > 15)
			i = 0;
	}

	attr.setForeground(attr.WHITE);
	attr.setBackground(attr.BLACK);
	attr.setBlinkState(false);
	cga.setAttr(attr);

	 //out.print('\b');
    while(4711)
    {
        out.print("\r|\r\\\r-\r/");
    };
    return 0;
}
