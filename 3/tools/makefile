OBJDIR = bin
GENSYS = FEDORA3

LIBS = -lbfd -liberty
ifeq ($(GENSYS), CYGWIN)
LIBS = -lbfd -liberty -lintl
endif

all : \
	$(OBJDIR)/build \
	$(OBJDIR)/coff2bin \
	$(OBJDIR)/bfd2bin

$(OBJDIR)/build : build.c
	gcc -o $@ -D$(GENSYS) $<

$(OBJDIR)/bfd2bin : bfd2bin.c
	gcc -o $@  -D$(GENSYS) $< $(LIBS)

$(OBJDIR)/coff2bin : coff2bin.c coffi386.h
	gcc -o $@  -D$(GENSYS) $< $(LIBS)

clean:
	rm -f $(OBJDIR)/*

