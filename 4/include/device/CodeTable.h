#ifndef CodeTable_h
#define CodeTable_h

/** Die Code Tabelle beschreibt die Umsetzung von Scancodes der Tastatur
 *  auf ASCII-Zeichen. Weiterhin wird festgelegt welche Scancodes als
 *  Steuerzeichen betrachtet werden, und nicht in ein ASCII-Zeichen
 *  umgesetzt werden.
 */
struct CodeTable {
public:

	/** Hier werden Zeichen definiert, welche nicht zu einem AsciiZeichen
	 *  umgewandelt werden sollen, da sie als Steuerzeichen dienen.
	 */
	enum {
		CTRL 		    = 29,
		SHIFT_LEFT 	= 42,
		SHIFT_RIGHT = 54,
		ALT 		    = 56,
		CAPS_LOCK 	= 58,
		NUM_LOCK 	  = 69,
		SCROLL_LOCK = 70,
		POS1 		    = 71,
		UP 		      = 72,
		PAGE_UP 	  = 73,
		LEFT 		    = 75,
		RIGHT 		  = 77,
		END 		    = 79,
		DOWN 		    = 80,
		PAGE_DOWN 	= 81,
		INS 		    = 82,
		DEL 		    = 83
	};

	enum PageCode {
//	  A     = 'a',
//	  A_G   = 'A',
//	  B     = 'b',
//	  B_G   = 'B',
//	  C     = 'c',
//	  C_G   = 'C',
//	  D     = 'd',
//	  D_G   = 'D',
//	  E     = 'e',
//	  E_G   = 'E',
//	  F     = 'f',
//	  F_G   = 'F',
//	  G     = 'g',
//	  G_G   = 'G',
//	  H     = 'h',
//	  H_G   = 'H',
//	  I     = 'i',
//	  I_G   = 'I',
//	  J     = 'j',
//	  J_G   = 'J',
//	  K     = 'k',
//	  K_G   = 'K',
//	  L     = 'l',
//	  L_G   = 'L',
//	  M     = 'm',
//	  M_G   = 'M',
//	  N     = 'n',
//	  N_G   = 'N',
//	  O     = 'o',
//	  O_G   = 'O',
//	  P     = 'p',
//	  P_G   = 'P',
//	  Q     = 'q',
//	  Q_G   = 'Q',
//	  R     = 'r',
//	  R_G   = 'R',
//	  S     = 's',
//	  S_G   = 'S',
//	  T     = 't',
//	  T_G   = 'T',
//	  U     = 'u',
//	  U_G   = 'U',
//	  V     = 'v',
//	  V_G   = 'V',
//	  W     = 'w',
//	  W_G   = 'W',
//	  X     = 'x',
//	  X_G   = 'X',
//	  Y     = 'y',
//	  Y_G   = 'Y',
//	  Z     = 'z',
//	  Z_G   = 'Z',
//	  AUSRUFEZEICHEN = '!',
//	  ANFUEHRUNGSZEICHEN = '"',
	  HOCH_ZWEI = 0xfd,
	  PARAGRAPH = 0x15,
//	  DOLLER = '$',
//	  PROZENT = '%',
//	  UND = '&',
//	  SLASH = '/',
//	  RUND_KLAMMER_AUF = '(',
//	  RUND_KLAMMER_ZU = ')',
//	  GESCHWEIFT_KLAMMER_AUF = '{',
//	  GESCHWEIFT_KLAMMER_ZU = '}',
//	  ECK_KLAMMER_AUF = '[',
//	  ECK_KLAMMER_ZU = ']',
//	  ISTGLEICH = '=',
	  ESZET = 0xe1,
//	  FRAGEZEICHEN = '?',
//	  BACKSLASH = '\\',
	  APOSTROPH = 0x60,
//	  AT    = '@',
	  MU    = 0xe6,
	  AE    = 0x84,
	  AE_G  = 0x8e,
	  UE    = 0x81,
	  UE_G  = 0x9a,
	  OE    = 0x94,
	  OE_G  = 0x99,
//	  PLUS = '+',
//	  MINUS = '-',
//	  RAUTE = '#',
//	  MAL = '*',
//	  KOMMA = ',',
//	  SEMIKOLON = ';',
//	  PUNKT = '.',
//	  DOPPEL_PUNKT = ':',
//	  UNTER_STRICH = '_',
//	  KLEINER = '<',
//	  GROESSER = '>',
//	  STRICH_SENKRECHT = '|',
	};

	CodeTable()
	{
		lookup[CTRL] = true;
		lookup[SHIFT_LEFT] = true;
		lookup[SHIFT_RIGHT] = true;
		lookup[ALT] = true;
		lookup[CAPS_LOCK] = true;
		lookup[NUM_LOCK] = true;
		lookup[SCROLL_LOCK] = true;
		lookup[POS1] = true;
		lookup[UP] = true;
		lookup[PAGE_UP] = true;
		lookup[LEFT] = true;
		lookup[RIGHT] = true;
		lookup[END] = true;
		lookup[DOWN] = true;
		lookup[PAGE_DOWN] = true;
		lookup[INS] = true;
		lookup[DEL] = true;
	}

	static bool isControl(unsigned char scanCode)
	{
		return lookup[scanCode];
	}

	static const unsigned char normalAscii[];
	static const unsigned char shiftAscii[];
	static const unsigned char strgAscii[];
	static const unsigned char altAscii[];
	static const unsigned char numblockAscii[];

private:
	static bool lookup[];
};

#endif

