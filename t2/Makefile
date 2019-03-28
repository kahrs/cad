CFLAGS = -c -g
CC = gcc
.SUFFIXES:
.SUFFIXES: .c .o

t2: t2.o y.tab.o lex.o semantics.o emit.o utilities.o entities.o
	$(CC) t2.o y.tab.o lex.o semantics.o emit.o utilities.o entities.o -lm -o t2

t2.o: t2.c
	$(CC) $(CFLAGS) t2.c

scan.o: scan.c
	$(CC) $(CFLAGS) scan.c

y.tab.o: y.tab.c
	$(CC) $(CFLAGS) -DYYDEBUG y.tab.c

lex.o: lex.c
	$(CC) $(CFLAGS) lex.c

semantics.o: semantics.c y.tab.h t2.h iges.h
	$(CC) $(CFLAGS) semantics.c

emit.o: emit.c t2.h iges.h
	$(CC) $(CFLAGS) emit.c

utilities.o: utilities.c t2.h iges.h
	$(CC) $(CFLAGS) utilities.c

entities.o: entities.c t2.h iges.h
	$(CC) $(CFLAGS) entities.c

y.tab.c: t2.y
	yacc -d t2.y

lex.c: t2.l y.tab.h
	lex t2.l
	mv lex.yy.c lex.c

print:
	a2ps t2.c t2.l t2.y t2.h iges.h semantics.c emit.c scan.c utilities.c entities.c Makefile

ar:
	ar rv t2.ar t2.c t2.l t2.y t2.h iges.h semantics.c utilities.c emit.c scan.c entities.c Makefile

clean:
	rm *.o
