.y.c:
	$(YACC) $(YFLAGS) $*.y
	mv y.tab.h $*.tab.h
	mv y.tab.c $*.tab.c

.c:
	$(CC) -c $*.c

CC=gcc
CFLAGS=-g
YACC=yacc
YFLAGS=-dv
FILES=lex.c espectro.c espectro.h espectro.y commands.c elaborate.c evaluate.c semantics.c sym.c reader.c
BINARIES=espectro.tab.o lex.o sym.o semantics.o commands.o elaborate.o evaluate.o models.o

espectro: espectro.o $(BINARIES)
	$(CC) -o espectro -rdynamic espectro.o $(BINARIES) -lm -ldl

test: test.o reader.o $(BINARIES)
	$(CC) -o tester -rdynamic test.o reader.o $(BINARIES) -lm -ldl

espectro.tab.o: espectro.tab.c
	$(CC) -c -g -DYYDEBUG espectro.tab.c

espectro.tab.c: espectro.y espectro.debug
	$(YACC) $(YFLAGS) espectro.y
	mv y.tab.h espectro.tab.h
	mv y.tab.c espectro.tab.c

espectro.debug: espectro.y
	cp /dev/null espectro.debug

espectro.o: espectro.c espectro.h
	$(CC) -c $(CFLAGS) espectro.c

elaborate.o: elaborate.c espectro.h
	$(CC) -c $(CFLAGS) elaborate.c

evaluate.o: evaluate.c espectro.h
	$(CC) -c $(CFLAGS) evaluate.c

semantics.o: semantics.c espectro.h
	$(CC) -c $(CFLAGS) semantics.c

sym.o: sym.c espectro.h
	$(CC) -c $(CFLAGS) sym.c

models.o: models.c espectro.h
	$(CC) -c $(CFLAGS) models.c

reader.o: reader.c espectro.h
	$(CC) -c $(CFLAGS) reader.c

test.o: test.c espectro.h
	$(CC) -c $(CFLAGS) test.c

library.o: library.c
	$(CC) -c $(CFLAGS) library.c

library.dll: library.o
	ld -shared -o library.dll library.o

clean:
	rm -f *.o espectro *.tab.*
