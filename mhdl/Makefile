CC=cc
CFLAGS=-g
YACC=yacc
YFLAGS=-dv
FILES=lex.c mies.c mhdl.h mhdl.y sym.c semantics.c types.c stdarg.h \
	Makefile.sun Makefile.others \
	units.mhdl standard.mhdl errors.awk tokens.awk mhdl.1 \
	LICENSE COPYING README HISTORY

mies: mies.o mhdl.tab.o lex.o sym.o errors.o semantics.o types.o
	$(CC) -o mies mies.o mhdl.tab.o lex.o sym.o errors.o semantics.o types.o -lm


mhdl.debug: mhdl.y
	cp /dev/null mhdl.debug

mhdl.tab.o: mhdl.tab.c
	$(CC) -c mhdl.tab.c

mhdl.tab.c: mhdl.y mhdl.debug
	$(YACC) $(YFLAGS) mhdl.y
	mv y.tab.h mhdl.tab.h
	mv y.tab.c mhdl.tab.c
	
.c.o: mhdl.h
	$(CC) -c -g $*.c

mhdl.tar: $(FILES)
	tar cvf mhdl.tar $(FILES)

mhdl.ar: $(FILES)
	ar cvf mhdl.ar $(FILES)

clean:
	rm -rf *.o
