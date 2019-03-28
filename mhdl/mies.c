#ifdef PLAN9
#include <u.h>
#include <libc.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "mhdl.h"

/*
 * some known debug flags
 *	-d		print declarations
 *	-t		print trees
 *	-v		verbose printing
 *	-T		visible type checking
 */

extern void yyparse(void);
extern void initialize_lexer(FILE *);

void new_file(char *name);
void exits(char *msg);
void read_options(void);
void define_library(char *, char *);

char *packages[NPACKAGES];
char *filename;
char *cmdname;
char *rcfilename;
int npackage = 0;

void
main(int argc, char *argv[])
{
	int i, c;
	char *p, *outfile;
	char Str[80];

	cmdname = argv[0];
	rcfilename = ".mhdlrc";
	ARGBEGIN {
	default:
		c = ARGC();
		if(c >= 0 && c < sizeof(debug))
			debug[c]++;
		break;

	case 'o':
		outfile = ARGF();
		break;

	case 'P':
		p = ARGF();
		if (p)
			packages[npackage++] = p;
		break;
	} ARGEND
	if(argc < 1) {
		fprintf(stderr, "usage: %s [-options] files\n", cmdname);
		exits("usage");
	}
	rwinit();
	if (!debug['L']) read_options();
	node_number = 0;
	type_init();
	for (c=0; c<argc; c++)
		new_file(*argv++);
	if (debug['n']) fprintf(stderr, "%ld nodes.\n", node_number);
} /* end main */

void
new_file(char *name)
{
	FILE *fp;
	filename = (char *) malloc(strlen(name)+1);
	strcpy(filename, name);
	fp = fopen(filename, "r");
	line_number = 0;
	if (fp == NULL) {
		warn("Unable to open input file", name, 0);
   		exits("can't open file");
	} /* end if */
	initialize_lexer(fp);              /* Lex will close this file */
	yyparse();
	fclose(fp);
	if (debug['S']) print_symbol_table();
} /* end new_file */

void
read_options(void)
{
	FILE *fp, *lp;
	char line[MAXLINE];
	char *wp, *ep;
	filename = rcfilename;
	fp = fopen(rcfilename, "r");
	if (fp == NULL) {
		warn("unable to open option file", rcfilename, 0);
   		return;
	} /* end if */
	for (line_number=1;;line_number++) {
		if (fgets(line, MAXLINE, fp) == NULL) break;
		wp = strtok(line, " \t\n");
		if (strcmp(wp, "library") == 0) define_library(wp, ep);
		else
		if (strcmp(wp, "preload") == 0) {
			wp = strtok(NULL, " \t\n:");
			if (debug['v'])
				fprintf(stderr, "preloading %s\n", wp);
			lp = fopen(wp, "r");
			if (lp == NULL) {
				warn("Unable to open preload file", wp, 0);
		   		continue;
			} /* end if */
			new_file(wp);
			fclose(lp);
		} /* end if */
		else
		if (strcmp(wp, "debug") == 0) {
			wp = strtok(NULL, " \t\n:");
			if (wp)
			    while (*wp)
				debug[*wp++]++;
		} /* end if */
		else
		warn("unknown command in", rcfilename, 0);
	} /* end for */
	fclose(fp);
} /* end read_options */

#ifndef PLAN9
void
exits(char *msg)
{
	if (*msg) fprintf(stderr, "mhdl: %s\n", msg);
	exit(1);
} /* end exits */
#endif

void
fatal(char *msg)
{
	fprintf(stderr, "mhdl fatal error: %s\n", msg);
	fflush(stderr);
	abort();
} /* end fatal */

void
warn(char *first, ...)
{
#ifdef __GNUC__
        va_list argp;
#else
	char *argp;
#endif
        char *argument;
        fprintf(stderr, "%s: file %s, line %ld: ", cmdname, filename, line_number);
        va_start(argp, first);
        for (argument = first; (argument != (char *) 0) && ((long int) argument != -1);argument = va_arg(argp, char *))
                    fprintf(stderr, "%s ", argument);
        va_end(argp);
        fprintf(stderr, "\n");
        fflush(stderr);
} /* end warn */

void
semantics(Node *node, char *first, ...)
{
#ifdef __GNUC__
        va_list argp;
#else
	char *argp;
#endif
        char *argument;
        va_start(argp, first);
        fprintf(stderr, "%s: file %s, line %d: ", cmdname, filename, node -> line);
        for (argument = first;
                argument != (char *) 0;
                argument = va_arg(argp, char *))
                	fprintf(stderr, "%s ", argument);
        va_end(argp);
        fprintf(stderr, "\n");
        fflush(stderr);
} /* end warn */
