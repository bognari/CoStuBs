/*** coff information for Intel 386/486.  */


/********************** FILE HEADER **********************/

typedef struct {
   unsigned short f_magic;	/* magic number			*/
   unsigned short f_nscns;	/* number of sections		*/
   long f_timdat;               /* time & date stamp		*/
   long f_symptr;               /* file pointer to symtab	*/
   long f_nsyms;                /* number of symtab entries	*/
   unsigned short f_opthdr;	/* sizeof(optional hdr)		*/
   unsigned short f_flags;	/* flags			*/
 } FILHDR;

#define	FILHDR_SIZE (sizeof(FILHDR))

/* Bits for f_flags:
 *	F_RELFLG	relocation info stripped from file
 *	F_EXEC		file is executable (no unresolved external references)
 *	F_LNNO		line numbers stripped from file
 *	F_LSYMS		local symbols stripped from file
 *	F_AR32WR	file has byte ordering of an AR32WR machine (e.g. vax)
 */

#define F_RELFLG	(0x0001)
#define F_EXEC		(0x0002)
#define F_LNNO		(0x0004)
#define F_LSYMS		(0x0008)


#define	I386MAGIC	0x14c
#define I386PTXMAGIC	0x154
#define I386AIXMAGIC	0x175
#define LYNXCOFFMAGIC	0415

#define I386BADMAG(x) (((x).f_magic != I386MAGIC) \
		       && (x).f_magic != I386AIXMAGIC \
		       && (x).f_magic != I386PTXMAGIC \
		       && (x).f_magic != LYNXCOFFMAGIC)

/********************** AOUT "OPTIONAL HEADER" **********************/


typedef struct 
 {
   unsigned short magic;         /* type of file			*/
   unsigned short vstamp;        /* version stamp		        */
   long tsize;                   /* text size in bytes,padded to FW bdry*/
   long dsize;                   /* initialized data "  "	        */
   long bsize;                   /* uninitialized data "   "	        */
   long entry;                   /* entry pt.			        */
   long text_start;	         /* base of text used for this file     */
   long data_start;	         /* base of data used for this file     */
 }
AOUTHDR;

#define AOUTHDR_SIZE (sizeof(AOUTHDR))

#define OMAGIC          0404    /* object files, eg as output */
#define ZMAGIC          0413    /* demand load format, eg normal ld output */
#define STMAGIC		0401	/* target shlib */
#define SHMAGIC		0443	/* host   shlib */


/* define some NT default values */
/*  #define NT_IMAGE_BASE        0x400000 moved to internal.h */
#define NT_SECTION_ALIGNMENT 0x1000
#define NT_FILE_ALIGNMENT    0x200
#define NT_DEF_RESERVE       0x100000
#define NT_DEF_COMMIT        0x1000

/********************** SECTION HEADER **********************/


typedef struct
 {
   char	          s_name[8];	/* section name			*/
   long           s_paddr;	/* physical address, aliased s_nlib */
   long           s_vaddr;	/* virtual address		*/
   long           s_size;	/* section size			*/
   long           s_scnptr;	/* file ptr to raw data for section */
   long           s_relptr;	/* file ptr to relocation	*/
   long           s_lnnoptr;	/* file ptr to line numbers	*/
   unsigned short s_nreloc;	/* number of relocation entries	*/
   unsigned short s_nlnno;	/* number of line number entries*/
   long           s_flags;	/* flags			*/
 } SCNHDR;

#define	SCNHDR_SIZE (sizeof(SCNHDR))

/*
 * names of "special" sections
 */
#define _TEXT	".text"
#define _DATA	".data"
#define _BSS	".bss"
#define _COMMENT ".comment"
#define _LIB ".lib"

/********************** LINE NUMBERS **********************/

/* 1 line number entry for every "breakpointable" source line in a section.
 * Line numbers are grouped on a per function basis; first entry in a function
 * grouping will have l_lnno = 0 and in place of physical address will be the
 * symbol table index of the function name.
 */
struct external_lineno {
	union {
		char l_symndx[4];	/* function name symbol index, iff l_lnno == 0*/
		char l_paddr[4];	/* (physical) address of line number	*/
	} l_addr;
	char l_lnno[2];	/* line number		*/
};


#define	LINENO	struct external_lineno
#define	LINESZ	6


/********************** SYMBOLS **********************/

#define E_SYMNMLEN	8	/* # characters in a symbol name	*/
#define E_FILNMLEN	14	/* # characters in a file name		*/
#define E_DIMNUM	4	/* # array dimensions in auxiliary entry */

struct external_syment 
{
  union {
    char e_name[E_SYMNMLEN];
    struct {
      char e_zeroes[4];
      char e_offset[4];
    } e;
  } e;
  char e_value[4];
  char e_scnum[2];
  char e_type[2];
  char e_sclass[1];
  char e_numaux[1];
};

#define N_BTMASK	(0xf)
#define N_TMASK		(0x30)
#define N_BTSHFT	(4)
#define N_TSHIFT	(2)
  
union external_auxent {
	struct {
		char x_tagndx[4];	/* str, un, or enum tag indx */
		union {
			struct {
			    char  x_lnno[2]; /* declaration line number */
			    char  x_size[2]; /* str/union/array size */
			} x_lnsz;
			char x_fsize[4];	/* size of function */
		} x_misc;
		union {
			struct {		/* if ISFCN, tag, or .bb */
			    char x_lnnoptr[4];	/* ptr to fcn line # */
			    char x_endndx[4];	/* entry ndx past block end */
			} x_fcn;
			struct {		/* if ISARY, up to 4 dimen. */
			    char x_dimen[E_DIMNUM][2];
			} x_ary;
		} x_fcnary;
		char x_tvndx[2];		/* tv index */
	} x_sym;

	union {
		char x_fname[E_FILNMLEN];
		struct {
			char x_zeroes[4];
			char x_offset[4];
		} x_n;
	} x_file;

	struct {
		char x_scnlen[4];	/* section length */
		char x_nreloc[2];	/* # relocation entries */
		char x_nlinno[2];	/* # line numbers */
		char x_checksum[4];	/* section COMDAT checksum */
		char x_associated[2];	/* COMDAT associated section index */
		char x_comdat[1];	/* COMDAT selection number */
	} x_scn;

        struct {
		char x_tvfill[4];	/* tv fill value */
		char x_tvlen[2];	/* length of .tv */
		char x_tvran[2][2];	/* tv range */
	} x_tv;		/* info about .tv section (in auxent of symbol .tv)) */


};

#define	SYMENT	struct external_syment
#define	SYMESZ	18	
#define	AUXENT	union external_auxent
#define	AUXESZ	18


#	define _ETEXT	"etext"


/********************** RELOCATION DIRECTIVES **********************/



struct external_reloc {
  char r_vaddr[4];
  char r_symndx[4];
  char r_type[2];
};


#define RELOC struct external_reloc
#define RELSZ 10

