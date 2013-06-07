SECTIONS 
 {
   . = 0x10000;     /* Startadresse des Systems */

   .text :
    {
      *(".text")
      *(".text$")
      *(".init")
      *(".fini") 
    }

   .data :
    {
      *(".data")
      *(".data$")
      *(".rodata")
      *(".rodata.str1.1")
      *(".debug_line")
      *(".debug_info")
      *(".debug_abbrev")
      *(".debug_aranges")
      ___CTOR_LIST__ = .;
      *(".ctors")
      *(".ctor")
      ___CTOR_LIST_END__ = .;
      ___DTOR_LIST__ = .;
      *(".dtors")
      *(".dtor")
      ___DTOR_LIST_END__ = .;
      *(".got")
      *(".got.plt")
      *(".eh_frame")
      *(".eh_fram")
    }

   .bss : 
    {
      *(".bss")
    }

   .paging :
    {
       . = ALIGN(4096);
       *(".paging")
    }

   /DISCARD/ :
    {
      *(".note")
      *(".comment")
      *(".note.GNU-stack")
    }
 }
