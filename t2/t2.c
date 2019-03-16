/*
 * t2 - t square: design program with csg
 */

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "t2.h"

extern int yydebug;

int lineNumber;
FILE *asStream;
int PFlag = 0;
int TFlag = 0;
int dFlag = 0;
int eFlag = 0;
int tFlag = 0;
int fFlag = 0;

char template[18] = "/tmp/t2XXXXXX";
char topName[5] = "main";
char *fileName;
int errorCount = 0;
int finished = 0;

struct NODE *treeRoot;
struct BUCKET *topLevel;
struct BUCKET *symbolHashTable[];
struct PARCEL *topParcel;

char *mktemp();
char *strcpy();
void Error();
void Trouble();
struct BUCKET *Lookup();
struct PARCEL *EvalParseTree();
void EvalEntityTree();
void PrintParcel();
void PrintEntityTree();

main(argc, argv)
int argc;
char **argv;
{
	int fd;
	int advance = 1;
	char *asFilename;

	if (argc == 1)
	{
		(void) Trouble("correct usage: t2 [-options] files");
		exit(1);
	} /* end if */
	argv++;
	argc--;
	while (argc > 0)
	{
top:		if (*argv[0] == '-')
		{
		    while (*++*argv)
			switch (**argv)
			{
			case 'd':
				dFlag++;
				continue;
			case 'e':
				eFlag++;
				continue;
			case 'P':
				PFlag++;
				continue;
			case 'T':
				TFlag++;
				continue;
			case 't':
				tFlag++;
				continue;
			default:
				(void) Trouble("Illegal switch '%c'; ignored", **argv);
			} /* end switch */
		} /* end if */
		else
		{
			if ((fd = open(argv[0], 0)) != -1)
			{
				fileName = strdup(argv[0]);
				close(fd);
				asFilename = mktemp(template); /* use /tmp */
				if (!PFlag && fork() == 0)
					execl("/lib/cpp", "/lib/cpp", argv[0], asFilename, 0);
				else wait(0);
				asStream = fopen(asFilename, "r");
				if (asStream == NULL)
				{
					(void) Trouble("couldn't open %s", asFilename);
					perror("t2");
				} /* end if */
				else
				{
					finished = 0;
					lineNumber = 1;
					yydebug = dFlag;
					finished = yyparse();
					fclose(asStream);
					unlink(asFilename);
					if  (topLevel = Lookup(topName, symbolHashTable, SYMBOLSIZE)) {
						if (tFlag) PrintTree(topLevel -> contents.pointer, 0);
						topParcel = EvalParseTree(topLevel -> contents.pointer);
						if (eFlag && (topParcel -> type == ENTITY_PARCEL)) PrintEntityTree(topParcel -> ptr.entity, 0);
						if (fFlag) EmitFx(topParcel -> ptr.entity);
						else EmitIGES(topParcel -> ptr.entity);
					} /* end if */
					else Trouble("top symbol %s not found", topName);
				} /* end else */
			} /* end if */
			else
			{
				(void) Trouble("couldn't open %s", argv[0]);
				perror("t2");
			} /* end if */
		} /* end else */
		argc -= advance;
		argv += advance;
	} /* end while */
	(void) exit(errorCount); /* Make will halt if != 0 */
} /* end main */

void Error(message, firstArgument, secondArgument)
char *message, *firstArgument, *secondArgument;
{
	char messageBuffer[64];
	sprintf(messageBuffer, message, firstArgument, secondArgument);
	fprintf(stderr, "t2: %s: line %d: %s\n", fileName, lineNumber, messageBuffer);
	errorCount++;
} /* end Error */

void Trouble(message, argument)
char *message, *argument;
{
	fprintf(stderr, "t2: ");
	fprintf(stderr, message, argument);
	fprintf(stderr, "\n");
} /* end Trouble */

void Bug(message)
char *message;
{
	fprintf(stderr, message);
	fprintf(stderr, "\n");
	kill(0, SIGQUIT);
} /* end Bug */

/*
 * yacc interface
 */

yyerror(message, argument)
char *message, *argument;
{
	fprintf(stderr, "%s: line %d: ", fileName, lineNumber);
	fprintf(stderr, message, argument);
	fprintf(stderr, "\n");
} /* end yyerror */
