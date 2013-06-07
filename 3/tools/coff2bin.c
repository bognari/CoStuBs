#include <stdio.h>        /* fprintf */
#include <string.h>
#include <stdlib.h>       /* contains exit */
#include <unistd.h>       /* contains read/write */
#include <fcntl.h>
#include <sys/stat.h>

#include "coffi386.h"

#ifdef LINUX
#define O_BINARY 0
#endif

#ifdef FEDORA3
#define O_BINARY 0
#endif

#define SCNBUF_SIZE 4096
char scn_buffer[SCNBUF_SIZE];

void die (const char* str)
 {
   fprintf(stderr,"%s\n",str);
   exit(1);
 }

int main (int argc, char** argv)
 {
   FILHDR coff_hdr;
   AOUTHDR aout_hdr;
   SCNHDR scn_hdr;
   int fd;
   int fd_bin;
   int to_read;
   int bytes_read;
   int curr_scn;
   char name[9];
   int curr_pos;
   int text_vma = -1;

   if (argc != 3)
      die ("usage: coff2bin COFF-inputfile binary");

   if ((fd = open (argv[1], O_RDONLY|O_BINARY, 0)) < 0)
      die ("Unable to open input file.");

   bytes_read = read (fd, (char*)&coff_hdr, FILHDR_SIZE);
   if (bytes_read != FILHDR_SIZE)
      die ("Bad input file: can't read coff header");

   if (coff_hdr.f_magic != I386MAGIC)
      die ("Bad input file: unknown magic number in file header");

#ifdef DEBUG
   printf ("\nFile header information:\n\n");
   printf ("%d section(s) in file\n", (int)coff_hdr.f_nscns);
   printf ("time/date is %d\n", coff_hdr.f_timdat);
   printf ("file pointer to symbol table is %d\n", coff_hdr.f_symptr);
   printf ("%d symbols in file\n", coff_hdr.f_nsyms);
   printf ("size of optional header is %d\n", (int)coff_hdr.f_opthdr);
   printf ("flags are %d\n", (int)coff_hdr.f_flags);
#endif

   if (coff_hdr.f_opthdr != AOUTHDR_SIZE)
      die ("Bad input file: no a.out header");

   bytes_read = read (fd, (char*)&aout_hdr, AOUTHDR_SIZE);
   if (bytes_read != AOUTHDR_SIZE)
      die ("Bad input file: can't read a.out header");

   if (aout_hdr.magic != ZMAGIC)
      die ("Bad input file: magic number of a.out header is not ZMAGIC");

#ifdef DEBUG
   printf ("\na.out header information\n\n");
   printf ("Version %d\n", (int)aout_hdr.vstamp);
   printf ("Text size %d\n",aout_hdr.tsize);
   printf ("Initialized data %d\n",aout_hdr.dsize);
   printf ("Uninitialized data %d\n",aout_hdr.bsize);
   printf ("Entry address %x\n", aout_hdr.entry);
   printf ("Text start in file %d\n", aout_hdr.text_start);
   printf ("Data start in file %d\n", aout_hdr.data_start);
#endif

   if ((fd_bin = open (argv[2], O_WRONLY|O_CREAT|O_TRUNC|O_BINARY, 0644)) < 0)
      die ("Unable to open output file.");

   for (curr_scn = 0; curr_scn < coff_hdr.f_nscns; curr_scn++)
    {
      bytes_read = read (fd, (char*)&scn_hdr, SCNHDR_SIZE);
      if (bytes_read != SCNHDR_SIZE)
         die ("Bad input file: error while reading section header");

      memmove (name, scn_hdr.s_name, 8);
      name[8] = '\0';

#ifdef DEBUG
      printf ("\nSection header\n\n");
      printf ("Name is %s\n", name);
      printf ("Physical address 0x%x\n", scn_hdr.s_paddr);
      printf ("Virtual address 0x%x\n", scn_hdr.s_vaddr);
      printf ("Section size 0x%x\n", scn_hdr.s_size);
      printf ("File pointer to raw data %d\n", scn_hdr.s_scnptr);
      printf ("File pointer to relocation %d\n", scn_hdr.s_relptr);
      printf ("File pointer to line numbers %d\n", scn_hdr.s_lnnoptr);
      printf ("Number of relocation entries %d\n", (int)scn_hdr.s_nreloc);
      printf ("Number of line number entries %d\n", (int)scn_hdr.s_nlnno);
      printf ("Flags %d\n", scn_hdr.s_flags);
      printf ("\n");
#endif

      if (strcmp (name, ".text") == 0)
	 text_vma = scn_hdr.s_vaddr;

      if (strcmp (name, ".text") == 0 ||
	  strcmp (name, ".init") == 0 ||
	  strcmp (name, ".fini") == 0 ||
	  strcmp (name, ".ctors") == 0 ||
	  strcmp (name, ".dtors") == 0 ||
	  strcmp (name, ".data") == 0 ||
	  strcmp (name, ".rodata") == 0)
       {
	 if (text_vma == -1)
	    die ("Bad input file: text section is not the first");

#ifdef DEBUG
	 printf ("Storing raw data from section %s\n", name);
#endif

	 if ((curr_pos = lseek (fd, 0, SEEK_CUR)) < 0)
            die ("Bad input file: error in lseek");
	 if (lseek (fd_bin, scn_hdr.s_vaddr - text_vma, SEEK_SET) < 0)
            die ("error in lseek (binary output file)");
	 if (lseek (fd, scn_hdr.s_scnptr, SEEK_SET) < 0)
            die ("Bad input file: error when searching raw section data");
	 to_read = scn_hdr.s_size;

	 while (to_read > 0)
	  { int l;

	    l = (to_read < SCNBUF_SIZE) ? to_read : SCNBUF_SIZE;
	    bytes_read = read (fd, scn_buffer, l);

#ifdef DEBUG
	    printf ("got %d bytes\n", bytes_read);
#endif

	    if (bytes_read != l)
	      die ("Bad input file: Read error while reading section.");

	    write (fd_bin, scn_buffer, l);
	    to_read -= l;
	  }

	 if (lseek (fd, curr_pos, SEEK_SET) < 0)
            die ("Bad input file: error in lssek");
       }
    }
   close (fd_bin);
   close (fd);
 }
