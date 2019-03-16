CFLAGS = -c -g

t2: t2.o scan.o parser.o lex.o semantics.o emit.o utilities.o entities.o
	cc t2.o scan.o parser.o lex.o semantics.o emit.o utilities.o entities.o -o t2

t2.o: t2.c
	cc $(CFLAGS) t2.c

scan.o: scan.c
	cc $(CFLAGS) scan.c

parser.o: parser.c
	cc $(CFLAGS) -DYYDEBUG parser.c

lex.o: lex.c
	cc $(CFLAGS) lex.c

semantics.o: semantics.c y.tab.h t2.h iges.h
	lcc $(CFLAGS) semantics.c

emit.o: emit.c t2.h iges.h
	lcc $(CFLAGS) emit.c

utilities.o: utilities.c t2.h iges.h
	lcc $(CFLAGS) utilities.c

entities.o: entities.c t2.h iges.h
	lcc $(CFLAGS) entities.c

parser.c: t2.y
	yacc -d -D t2.y
	mv y.tab.c parser.c

lex.c: t2.l y.tab.h
	lex t2.l
	mv lex.yy.c lex.c

print:
	pr t2.c t2.l t2.y t2.h iges.h semantics.c emit.c scan.c utilities.c entities.c Makefile

ar:
	ar rv t2.ar t2.c t2.l t2.y t2.h iges.h semantics.c utilities.c emit.c scan.c entities.c Makefile
