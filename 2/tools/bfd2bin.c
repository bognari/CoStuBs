#include <stdio.h>
#include <string.h>
#include <stdlib.h>       /* contains exit */
#include <unistd.h>       /* contains read/write */
#include <fcntl.h>
#include <sys/stat.h>

#include "bfd.h"

#ifdef LINUX
#define O_BINARY 0
#define RAWSIZE _raw_size
#endif

#ifdef FEDORA3
#define O_BINARY 0
#define RAWSIZE rawsize
#endif

#ifdef CYGWIN
#define RAWSIZE _raw_size
#endif

#define SECTION_BUFFER_SIZE 4096
char section_buffer[SECTION_BUFFER_SIZE];

void die (const char* msg)
 {
   fprintf (stderr, "%s\n", msg);
   exit (1);
 }

int main (int argc, char** argv)
 {
   bfd* abfd;
   int verbose = 1;
   asection* sec;
   int idx;
   char** matching;
   int fd_bin;
   int text_vma = -1;
   const char* name;
   int to_read;
   int bytes_read;

   /* Check parameters */
   if (argc != 3)
      die ("usage: BFD2Bin BFD-inputfile binary-outputfile");

   /* Initialize BFD-Library */
   bfd_init ();

   /* Open the input file */
   if (!(abfd = bfd_openr (argv[1], "default")))
      die ("Unable to open input file.");

   /* Check the input file format */
   if (!bfd_check_format_matches (abfd, bfd_object, &matching))
    {
      free (matching);
      die ("Can't find out input file type.");
    }

   if (verbose)
      printf ("The input file \"%s\" has target format \"%s\"\n",
	      abfd->filename, abfd->xvec->name);

   /* Open the output file */
   if ((fd_bin = open (argv[2], O_WRONLY|O_CREAT|O_TRUNC|O_BINARY, 0644)) < 0)
      die ("Unable to open output file.");

   /* Now scan all sections */
   if (verbose)
    {
      printf ("%d sections:\n", abfd->section_count);
      printf ("Idx Name            VMA      Size\n");
    }
   sec = abfd->sections;
   idx = 0;
   while (sec)
    {
      name = sec->name;
      if (verbose)
         printf ("%3d %15s %08x %08x\n", idx, name, sec->vma, sec->RAWSIZE);

      if (strcmp (name, ".text") == 0)
	 text_vma = sec->vma;

      if (bfd_get_section_flags (abfd, sec) & SEC_LOAD)
       {
	 if (text_vma == -1)
	    die ("Bad input file: text section is not the first");

#ifdef DEBUG
	 printf ("Storing raw data from section %s\n", name);
	 printf ("Text: %x, Section: %x\n");
#endif

	 if (lseek (fd_bin, sec->vma - text_vma, SEEK_SET) < 0)
            die ("error in lseek (binary output file)");
	 to_read    = sec->RAWSIZE;
	 bytes_read = 0;

	 while (to_read > 0)
	  { int l;

	    l = (to_read < SECTION_BUFFER_SIZE)? to_read:SECTION_BUFFER_SIZE;
	    if (!bfd_get_section_contents (abfd, sec, section_buffer,
					   bytes_read, l))
 	       die ("Bad input file: Read error while reading section.");

#ifdef DEBUG
	    printf ("got %d of %d bytes\n", bytes_read + l, sec->RAWSIZE);
#endif

	    write (fd_bin, section_buffer, l);

	    bytes_read += l;
	    to_read -= l;
	  }
       }
      idx++;
      sec = sec->next;
    }

   /* Close the output file */
   close (fd_bin);

   /* Close the input file */
   if (!bfd_close (abfd))
      die ("An error occurred while closing the input file.");

   exit (0);
 }
