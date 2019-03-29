#include <ctype.h>
#include <stdio.h>

#include <values.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

#include "espectro.h"
#include "espectro.tab.h"

extern int line_number;

int lexical_level = 0;
Symbol *lexical_stack[MAXLEX];

extern Frame frame_stack[];
extern int frame_stack_ptr;

extern Symbol *model_symbol;

void print_tree(TreeNode *root);

Bucket *namehashtable[NHASH];

char *type_names[] = {
	"NONE",
	"MODEL",
	"SUBCKT",
	"BINDING",
	"SUBNODE",
	"FN",
	"FORMAL",
	"BOOL",
	"INT",
	"FLOAT",
	"STRING",
	"LIST",
	"INSTANCE",
	"GLOBAL",
	"SIGNAL",
	"BUILTIN",
	0
};

void
final_check()
{
	if (lexical_level != 0) warn("lexical level not zero", 0);
} /* end final_check */

char *
full_symbol(Symbol *s, char *lastp)
{
	char *sp;
	if (s) {
		lastp = full_symbol(s -> up, lastp);
		for (sp = s -> bucket -> name; *sp; ) *lastp++ = *sp++;
		*lastp++ = '.';
		return(lastp);
	} /* end if */
	return(lastp);
} /* end full_symbol */

char *
full_symbol_name(Symbol *s)
{
	char cbuf[MAXSTRING], *copy;
	char *endp;
	int l;
	cbuf[0] = '\0';
	endp = full_symbol(s, cbuf);
	l = endp - cbuf; /* evil address arithmetic */
	copy = (char *) malloc(l);
	strncpy(copy, cbuf, l); /*strdup is too gnu */
	copy[l-1] = '\0';
	return(copy);
} /* end full_symbol_name */

void
print_symbol(Symbol *s)
{
	char *full_name = full_symbol_name(s);
	fprintf(stderr, "%s", full_name);
	/*free(full_name);*/	/* Leaky */
} /* end print_symbol */

void
print_symbol_chain(Symbol *s)
{
	for (; s; s = s -> next)
		fprintf(stderr, "%d ", s -> ll);
} /* end print_symbol_chain */

void
print_bucket(Bucket *b)
{
	Symbol *s;
	if (b && b -> token)
		if (debug['v'])
		 fprintf(stderr, "%s: token %d", b->name, b -> token);
		else;
	else {
		fprintf(stderr, "%s:", b->name);
		print_symbol_chain(b -> symbols);
		fprintf(stderr, "\n");
	} /* end else */
} /* end print_bucket */

void
print_symbol_table(void)
{
	int i;
	Bucket *b;
	for (i=0; i<NHASH; i++)
		for(b = namehashtable[i]; b; b = b->chain)
			print_bucket(b);
} /* end symbol_table_print */

Bucket *
new_bucket(char *name)
{
	Bucket *b;
	b = (Bucket *) malloc(sizeof (Bucket));
	b -> name = (char *) malloc(strlen(name) + 1);
	b -> token = 0;
	b -> symbols = (Symbol *) 0;
	strcpy(b -> name, name);
	return(b);
} /* end new_bucket */

Symbol *
new_symbol(Bucket *b)
{
        Symbol *s;
        if (b == (struct Bucket *) 0) fatal("broken Bucket chain in new_symbol");
	s = (Symbol *) malloc(sizeof (Symbol));
	s -> bucket = b;
	s -> type = T_NONE;
	s -> ll = 0;
        s -> up = s -> next = s -> chain = (Symbol *) 0;
	s -> fixup = (TreeNode *) 0;
	s -> bound.value = (Value *) 0;
	return(s);
} /* end new_symbol */

int
hash_name(char *name)
{
	int sum = 0;
	char *namep;
	for(namep = name; *namep; ) {
		sum *= 3;
		sum += *namep++;
	} /* end for */
	if (sum < 0) sum = ~sum;
	return(sum % NHASH);
} /* end hash_name */

Bucket *
lookup_name(Bucket *hashtable[], char *name)
{
	Bucket *b;
	int hash = hash_name(name);
	for(b = hashtable[hash]; b != (Bucket *) 0; b = b -> chain)
		if (strcmp(b -> name, name) == 0)
			return(b);
	b = new_bucket(name);
	b -> chain = hashtable[hash];
	hashtable[hash] = b;
	return(b);
} /* end lookup_name */

void
fixup_symbol(Symbol *sp, Symbol *s)
{
	TreeNode *fp;
	for (fp = sp -> fixup; fp; fp = fp -> fixup) {
		fp -> symbol = s;
		if (debug['S']) fprintf(stderr, "fixup %p to %s %p\n", fp, full_symbol_name(s), s);
	} /* end for fixups */
} /* end fixup_symbol */

void
type_symbol(Symbol *s, int type)
{
	Symbol *sp;
	if (s -> type && s -> type != type)
		warn("name ", s -> bucket -> name, "was already declared a ",
			type_names[s -> type], 0);
	s -> type = type;
	if (debug['S']) fprintf(stderr, "type %s %p %s\n", s -> bucket -> name, s, type_names[type]);
	for(sp = s -> bucket -> symbols; sp; sp = sp -> next)
		if (!sp -> type && (sp -> ll >= lexical_level))
			fixup_symbol(sp, s);
} /* end type_symbol */

Symbol *
lookup_symbol(Bucket *b, Symbol *context)
{
	Symbol *s = (Symbol *) 0;
	if (debug['S']) fprintf(stderr, "lookup %s in %p; ", b -> name, context);
	if (b -> token) {
		warn("attempt to lookup a reserved word", b -> name, "as a identifier", 0);
		return(0);
	} /* end if */
	for (s = b -> symbols; s; s = s -> next)
		if (s -> up == context) return(s);
	return(0);
} /* end find_symbol */

Symbol *
use_symbol(Bucket *b)
{
	int ll;
	Symbol *s = 0;
	for (ll = lexical_level; ll >= 0; ll--) {
		s = lookup_symbol(b, lexical_stack[ll]);
		if (s) break;
	} /* end for */
	if (!s) {
		s = new_symbol(b);
		s -> next = b -> symbols;
		s -> type = T_NONE;
		s -> ll = lexical_level;
	        s -> up = lexical_stack[lexical_level];
		b -> symbols = s;
	} /* end if */
	if (debug['S']) fprintf(stderr, "= 0x%p, up = %p, type = %d\n", s, s -> up, s -> type);
/*** if (!s -> type) fprintf(stderr, "undeclared %s\n", b -> name); /*****/
	return(s);
} /* end use_symbol */

Symbol *
define_symbol(Bucket *b)
{
	Symbol *s = (Symbol *) 0;
	if (debug['S']) fprintf(stderr, "define %s in %p = ", b -> name, lexical_stack[lexical_level]);
	if (b -> token) {
		warn("attempt to use a reserved word", b -> name, "as a identifier", 0);
		return(0);
	} /* end if */
	s = new_symbol(b);
	s -> next = b -> symbols;
	s -> type = T_NONE;
	s -> ll = lexical_level;
        s -> up = lexical_stack[lexical_level];
	b -> symbols = s;
	if (debug['S']) fprintf(stderr, "%p, type = %d\n", s, s -> type);
	return(s);
} /* end define_symbol */

Symbol *
use_model_symbol(Bucket *b)
{
	Symbol *s = (Symbol *) 0;
	s = lookup_symbol(b, model_symbol);
	if (!s) { /* not found, better define it */
		s = new_symbol(b);
		s -> next = b -> symbols;
		s -> type = T_NONE;
		s -> ll = model_symbol -> ll + 1;
	        s -> up = model_symbol;
		b -> symbols = s;
	} /* end if */
	if (debug['S']) fprintf(stderr, "%p, type = %d\n", s, s ? s -> type : 0);
	return(s);
} /* end use_model_symbol */

Symbol *
add_symbol(char *name)
{
	Symbol *new_symbol = define_symbol(lookup_name(namehashtable, name));
	return(new_symbol);
} /* end add_symbol */

Symbol *
find_symbol(char *name)
{
	int dl;
	Symbol *s;
	Bucket *b = lookup_name(namehashtable, name);
	if (!b) return(NIL);
	if (b -> token) {
		warn("attempt to lookup a reserved word", b -> name, "as a identifier", 0);
		return(0);
	} /* end if */
	if (debug['S']) fprintf(stderr, "find %s ", b -> name);
	for (s = b -> symbols; s; s = s -> next)
		for (dl=frame_stack_ptr; dl>=0; dl--)
			if (s -> up == frame_stack[dl].name) {
				if (debug['S']) fprintf(stderr, "= %p\n", s);
				return(s);
			} /* end if */
	/* not in the dynamic chain */
	if (debug['S']) fprintf(stderr, "...not found in context");
	return((Symbol *) 0);
} /* end find_symbol */

void
chain_fixup(TreeNode *node)
{
	if (node -> symbol -> fixup)
		node -> fixup = node -> symbol -> fixup;
	node -> symbol -> fixup = node;
	if (debug['S']) fprintf(stderr, "chained %p to %p (%s)\n", node, node -> symbol, full_symbol_name(node -> symbol));
} /* end chain_fixup */

double
find_symbol_double(char *name, double def)
{
	Symbol *s;
	char defstr[8];
	s = find_symbol(name);
	if (!s) {
		if (debug['U']) warn("variable not found in environment: ", name, ": defaulting to ", gcvt(def, 8, defstr), 0);
		return(def);
	}
	if (!s -> bound.value) warn("variable unbound: ", name, 0);
	else
	if (s -> bound.value -> type == T_INT)
		return((double) s -> bound.value -> v.lconstant);
	else
	if (s -> bound.value -> type != T_FLOAT)
		warn("variable should be a double: ", name, 0);
	else {
		if (debug['D']) fprintf(stderr, "%s = %f\n", name, s -> bound.value -> v.dconstant);
		return(s -> bound.value -> v.dconstant);
	} /* end final else */
	return(def);
} /* end find_symbol_double */

int
find_symbol_int(char *name, int def)
{
	Symbol *s;
	char defstr[8];
	s = find_symbol(name);
	if (!s) {
		if (debug['U']) warn("variable not found in environment: ", name, ": defaulting to ", gcvt((double) def, 8, defstr), 0);
		return(def);
	}
	else
	if (!s -> bound.value)  warn("variable unbound: ", name, 0);
	else
	if (s -> bound.value -> type == T_FLOAT)
		return((int) s -> bound.value -> v.dconstant);
	else
	if (s -> bound.value -> type != T_INT)
		warn("variable should be a int: ", name, 0);
	else
		return(s -> bound.value -> v.lconstant);
	return(def);
} /* end find_symbol_int */

TreeNode *
declare_names(TreeNode *root, int type)
{
	Symbol *s;
	if (!root) return(root);
	switch (root -> operator) {
	case O_LIST:
		declare_names(root -> branches[0], type);
		declare_names(root -> branches[1], type);
		break;
	case O_NAME:
		type_symbol(root -> symbol, type);
		break;
	case O_BIND:
		declare_names(root -> branches[0], type);
		break;
	/* ignore constants */
	case O_VALUE:
		break;
	default:
		print_tree(root);
		fatal("name node not in parameter list");
	} /* end switch */
	return(root);
} /* end declare_names */

void
push_lexical_level(Symbol *s)
{
	if (++lexical_level == MAXLEX) fatal("too many lexical levels");
	if (debug['S']) fprintf(stderr, "push ll = %p\n", s);
	lexical_stack[lexical_level] = s;
} /* push_lexical_level */

Symbol *
pop_lexical_level()
{
	Symbol *thread;
/*	for (thread = lexical_stack[lexical_level]; thread; thread = thread -> next)
		thread -> bucket -> symbols = thread -> up;*/
	if (debug['S']) fprintf(stderr, "pop ll = %p\n", lexical_stack[lexical_level]);
	return(lexical_stack[lexical_level--]);
} /* pop_lexical_level */

struct token {
	char *name;
	unsigned short token;
};

struct token rwtable[] =
{
	"time_sweep", L_TIME_SWEEP,
	"dc_sweep", L_DC_SWEEP,
	"save", L_SAVE,
	"sens", L_SENS,
	"to", L_TO,
	"for", L_FOR,
	"simulator", L_SIMULATOR,
	"paramset", L_PARAMSET,
	"parameters", L_PARAMETERS,
	"global", L_GLOBAL,
	"subckt", L_SUBCKT,
	"ends", L_ENDS,
	"integer", L_INTEGER,
	"real", L_REAL,
	"return", L_RETURN,
	"altergroup", L_ALTERGROUP,
	"correlate", L_CORRELATE,
	"include", L_INCLUDE,
	"inline", L_INLINE,
	"library", L_LIBRARY,
	"local", L_LOCAL,
	"march", L_MARCH,
	"nodeset", L_NODESET,
	"paramtest", L_PARAMTEST,
	"print", L_PRINT,
	"statistics", L_STATISTICS,
	"ic", L_IC,
	"if", L_IF,
	"else", L_ELSE,
	"model", L_MODEL,
	"xf", L_XF,
	"noise", L_NOISE,
	"sp", L_SP,
	"ac", L_AC,
	"options", L_OPTIONS,
	"info", L_INFO,
	"tran", L_TRAN,
	0, 0
};

void
rwinit(void)
{
	int i;
	Bucket *b;
	Symbol *s;
	for (i=0; i<NHASH; i++)
		namehashtable[i] = (struct Bucket *) 0;
	for (i=0; rwtable[i].name; i++) {
		b = lookup_name(namehashtable, rwtable[i].name);
		b -> token = rwtable[i].token;
	} /* end for */
	for (i=0; rwtable[i].name; i++) {
		b = lookup_name(namehashtable, rwtable[i].name);
		b -> token = rwtable[i].token;
	} /* end for */
	lexical_stack[0] = 0;
} /* end rwinit */

