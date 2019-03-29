#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/wait.h>

#include "espectro.h"

/*
 * known option flags
 *	-S		Symbol tables
 *	-v		Verbosity
 * some known debug flags
 *	-d		(generic) debug
 *	-t		print trees
 */

char *filename;
char *cmdname;
char debug[256];
void *dl_handle = NULL;

TreeNode *new_root, *last_root;

extern int line_number;
extern int node_count;
extern int source_count;

int yyparse(void);
void rwinit(void);
void lexer_init(FILE *f);
void skip_line();

void elaborate(TreeNode *);
void builtin_init();
void new_file(char *name);

void matrix_initialize(int nodes, int sources);
void matrix_fill();
void matrix_output(int nodes, int sources);

TreeNode *link_node(TreeNode *old, TreeNode *new);
void print_tree(TreeNode *);

void print_symbol_table(void);
void final_check();

void print_components();
void init_nodes();

int
main(int argc, char *argv[])
{
	int i, c;
	char *p, *outfile;
	TreeNode *top_node;

	cmdname = argv[0];
	ARGBEGIN {
	default:
		c = ARGC();
		if(c >= 0 && c < sizeof(debug))
			debug[c]++;
		break;
	case 'o':
		outfile = ARGF();
		break;
	case 'L':
		if (dl_handle) warn("dynamic library already loaded", 0);
		dl_handle = dlopen(ARGF(), RTLD_LAZY);
		if (!dl_handle) {
			fputs(dlerror(), stderr);
			fputc('\n', stderr);
			fatal("can't load dynamic library");
		} /* end if */
		break;
	} ARGEND
	if(argc < 1) {
		fprintf(stderr, "usage: %s [-options] files\n", cmdname);
		exit(1);
	}
	rwinit();
	top_node = last_root = link_node(NIL, NIL); /* null O_LIST node */
	builtin_function_init();
	builtin_model_init();
	for (c=0; c<argc; c++)
		new_file(*argv++);
	if (debug['S']) print_symbol_table();
	if (debug['t']) print_tree(top_node);
	final_check();
	init_nodes();
	elaborate(top_node);
	fprintf(stderr, "%d circuit nodes. %d sources.\n", node_count, source_count);
	if (debug['C']) print_components();
} /* end main */

void
new_file(char *name)
{
	FILE *fp;
	char template[16];
	strcpy(template, "espectro.XXXXXX");
	filename = (char *) malloc(strlen(name)+1);
	strcpy(filename, name);
	if (mkstemp(template) < 0) fatal("can't create tmp file"); /* use /tmp */
        if (!debug['P'] && (fork() == 0)) execl("/lib/cpp", "/lib/cpp", filename, template, (char *) 0);
        else wait(0);
        fp = fopen(template, "r");
	line_number = 0;
	if (fp == NULL) {
		error("Unable to open input file", name, 0);
   		return;
	} /* end if */
	lexer_init(fp);
	while (!feof(fp))
		if (yyparse()) skip_line();
		else
		if (new_root) last_root = link_node(last_root, new_root);
	fclose(fp);
	unlink(template);
} /* end new_file */

void
fatal(char *msg)
{
	fprintf(stderr, "espectro fatal error: %s\n", msg);
	fflush(stderr);
	abort();
} /* end fatal */

void
warn(char *first, ...)
{
	va_list argp;
	char *argument;
        fprintf(stderr, "%s: file %s, line %d: %s", cmdname, filename, line_number, first);
        va_start(argp, first);
        for (argument = va_arg(argp, char *);
                argument;
                argument = va_arg(argp, char *))
                fprintf(stderr, "%s ", argument);
        va_end(argp);
        fprintf(stderr, "\n");
        fflush(stderr);
} /* end warn */

void
node_warn(TreeNode *node, char *first, ...)
{
	va_list argp;
	char *argument;	
	int line_number = node -> line_number;
        fprintf(stderr, "%s: file %s, line %d: %s",
		cmdname, node -> filename, node -> line_number, first);
        va_start(argp, first);
        for (argument = va_arg(argp, char *);
                argument;
                argument = va_arg(argp, char *))
                fprintf(stderr, "%s ", argument);
        va_end(argp);
        fprintf(stderr, "\n");
        fflush(stderr);
} /* end node_warn */

void
error(char *first, ...)
{
	va_list argp;
	char *argument;
        fprintf(stderr, "%s: %s", cmdname, first);
        va_start(argp, first);
        for (argument = va_arg(argp, char *);
                argument;
                argument = va_arg(argp, char *))
                fprintf(stderr, "%s ", argument);
        va_end(argp);
        fprintf(stderr, "\n");
        fflush(stderr);
} /* end warn */

