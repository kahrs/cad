#include <ctype.h>
#include <stdio.h>
#ifdef PLAN9
#include <u.h>
#include <libc.h>
#else
#include <values.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <math.h>
#endif

#include "mhdl.h"
#include "mhdl.tab.h"

extern char debug[];

Bucket *namehashtable[NHASH];
Bucket *unithashtable[NHASH];

long int maxint;

char *type_names[] = {
	"undeclared",
	"abs_prop",
	"class",
	"component",
	"config",
	"connect_list",
	"connector",
	"constraint",
	"constructor",
	"dim",
	"equation",
	"field",
	"function",
	"instance",
	"label",
	"library",
	"model",
	"multiplier",
	"named_value",
	"object",
	"package",
	"polymorphic",
	"poly",
	"structure_model",
	"struct_model_comp",
	"structure",	
	"table",
	"type",
	"unit",
	0
};

struct multiplier {
	char *name;
	int exponent;
};

struct multiplier multable[] =
{
	"yotta", 24,
	"zetta", 21,
	"exa",	18,
	"E",	18,
	"peta",	15,
	"P",	15,
	"tera",	12,
	"T",	12,
	"giga",	9,
	"G",	9,
	"mega",	6,
	"M",	6,
	"kilo",	3,
	"k",	3,
	"hecto", 2,
	"h",	2,
	"deca",	1,
	"da",	1,
	"deci",	-1,
	"d",	-1,
	"centi", -2,
	"c",	-2,
	"milli", -3,
	"m",	-3,
	"micro", -6,
	"u",	-6,
	"nano",	-9,
	"n",	-9,
	"pico",	-12,
	"p",	-12,
	"femto", -15,
	"f",	-15,
	"atto",	-18,
	"a",	-18,
	"zepto", -21,
	"yocto", -24,
	0
};

Symbol *name_stack_ptr = Nil(Symbol);

void
print_bucket(Bucket *b)
{
	Symbol *s;
	s = b -> symbols;
	if (b && b -> token) /* fprintf(stderr, "token %d\n", s -> token) */;
	else {
		fprintf(stderr, "%s:", b->name);
		if (b -> symbols)
		    for (s = b -> symbols; s; s = s -> back) {
			fprintf(stderr, "\t%s - %s (%s): ", type_names[s -> category],
			s -> invisible ? "invisible" : "visible",
			s -> up ? s->up->bucket->name : "");
			print_type_schemes(s -> type);
		}
		else fprintf(stderr, "\tundefined");
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

void
print_name_stack(Symbol *s)
{
	if (s == Nil(Symbol)) return;
	print_name_stack(s->up);
	fprintf(stderr, "%s.", s->bucket->name);
} /* end print_name_stack */

void
print_linked_nodes(Node *n)
{
	if (n == Nil(Node)) return;
	print_linked_nodes(n -> u.tree.left);
	fprintf(stderr, "%s.", n -> bucket -> name);
} /* end print_linked_nodes */

void
print_nested_node(Node *node)
{
	Node *n;
	if (node == Nil(Node)) return;
	for(n = node; n && !(n -> bucket); n = n -> u.tree.right);
	if (n -> symbol) print_name_stack(n->symbol->up);
	print_linked_nodes(node -> u.tree.left);
	fprintf(stderr, "%s", n -> bucket -> name);
} /* end print_nested_node */

void
print_name(Symbol *s)
{
	print_name_stack(s->up);
	fprintf(stderr, "%s", s->bucket->name);
} /* end print_name */

void
print_undefs(Symbol *top)
{
	Symbol *s;
	char linestring[10];
	if (top == Nil(Symbol)) return;
	if (!debug['U']) return;
	for (s = top; s; s = s -> chain)
	    if (s -> category == N_NO)
		if (!s -> invisible) {
		    sprintf(linestring, "%d", s -> linenumber);
		    warn("undefined in line", linestring, ":", s -> bucket -> name, 0);
		} /* end if */
	print_undefs(top -> down);
} /* end print_undefs */

Symbol *
dotted_name(Node *node)
{
	Symbol *nt;
	Bucket *bucket;
	Symbol *s, *old, *new;
	node = node->u.tree.right;
	bucket = node -> bucket;
	if (bucket == Nil(Bucket)) return(Nil(Symbol)); /* must be operator */
	if (bucket -> token) {
		warn("attempt to use reserved word", bucket -> name, 0);
		return(Nil(Symbol));
	} /* end if */
	for (s = bucket -> symbols; s; s = s->back)
		if (!(s -> invisible)) return(s);
	/* not visible at current level so must be undef */
	new = new_symbol(bucket);
	old = bucket -> symbols;
	bucket -> symbols = new;
	new -> chain = old;
	return(new);
} /* end dotted_name */

Symbol *
dereference_node(Node *node)
{
	switch (node -> operator) {
	case O_OP:
		return(Nil(Symbol));
	case O_DOT:
		return(dotted_name(node));
	case O_ID:
	case O_NAME:
		return(use_name(node));
	case O_PAIR:
	default:
		print_node(node);
		fatal("dereference_node");
	} /* end switch */
} /* end dereference_node */

void
compare_types(int type, int declared_type, Node *node, int line)
{
	int t;
	if ((1 << declared_type) & type) return;
	fprintf(stderr, "%s: line %d: ", cmdname, line);
	print_nested_node(node);
	if (declared_type == 0)
		fprintf(stderr, ": undeclared, should have been ");
	else {
		fprintf(stderr, ": type mismatch; ");
		fprintf(stderr, "declared %s, should have been ", type_names[declared_type]);
	} /* end else */
	for (t=0; type != 0; t++) {
		if (type & 1)
			if (type & ~1) fprintf(stderr, "%s or ", type_names[t]);
			else
			fprintf(stderr, "%s ", type_names[t]);
		type >>= 1;
	} /* end for */
	fprintf(stderr, "\n");
} /* end compare_types */

void
check_name(Node *node, unsigned int category)
{
	int declared_category;
	Symbol *stack_symbol;
	stack_symbol = dereference_node(node);
	declared_category = stack_symbol -> category;
/***	if (declared_type == 0) return; ***/
	compare_types(category, declared_category, node, line_number);
} /* end check_name */

void
verify_name_type(Node *node, unsigned int type)
{
	Symbol *stack_symbol;
	int declared_type;
	stack_symbol = node -> symbol;
	declared_type = (stack_symbol == Nil(Symbol))? 0 : stack_symbol -> category;
	compare_types(type, declared_type, node, node -> line);
} /* end verify_name_type */

void
fixup_undefines(Symbol *scope_ptr, Symbol *symbol)
{
	Bucket *bucket;
	Symbol *s, *undef_ptr, *old, *clone;
	if (scope_ptr == Nil(Symbol)) return;
	for (s = scope_ptr->down; s; s = s->chain) {
	    for (undef_ptr = old = s; undef_ptr; old = undef_ptr, undef_ptr = undef_ptr -> back)
		if (undef_ptr -> type == N_NO &&
		    strcmp(undef_ptr -> bucket -> name, symbol -> bucket -> name) == 0) {
		    bucket = symbol -> bucket;
		    clone = new_symbol(bucket);
		    clone -> up = undef_ptr -> up;
		    clone -> down = undef_ptr -> down;
		    clone -> linenumber = undef_ptr -> linenumber;
		    bucket -> symbols = clone;
		    undef_ptr -> invisible = 1; /* done */
		    if (debug['d'])
			fprintf(stderr, "declare fixup %s.%s\n", s -> bucket -> name, symbol -> bucket -> name);
		} /* end if name = */
		fixup_undefines(scope_ptr -> down, symbol);
	} /* end for */
} /* end fixup_undefines */

Symbol *
define_name(Bucket *bucket, int category)
{
	Symbol *new, *old, *s;
	if (bucket == Nil(Bucket)) return(Nil(Symbol)); /* must be operator */
	if (debug['d'])
		fprintf(stderr, "define name %s: ", bucket -> name);
	if (bucket -> token) {
		warn("attempt to redefine reserved word", bucket -> name, 0);
		return(Nil(Symbol));
	} /* end if */
	for (s = bucket -> symbols; s; s = s->back)
		if (!(s -> invisible)) {
		    if (s -> category != 0 && s -> category != category)
			warn(s->bucket->name, "was category", type_names[s->category], "now category", type_names[category], 0);
		    if (debug['d']) fprintf(stderr, "%p old\n", new);
		    return(s);
		} /* end if visible */
	new = new_symbol(bucket);
	old = bucket -> symbols;
	new -> back = old;
	new -> category = category;
	bucket -> symbols = new;
	fixup_undefines(name_stack_ptr, new);
	if (debug['d']) fprintf(stderr, "%p new symbol %p bucket\n", new, bucket);
	return(new);
} /* end define_name */

Symbol *
define_node(Node *node, int category)
{
	Bucket *bucket;
	if (node -> operator == O_ID)
		bucket = node -> bucket;
	else
	if (node -> operator == O_NAME)
		bucket = node -> symbol -> bucket;
	else 
	if (node -> operator == O_OP)
		bucket = node -> bucket;
	else
	if (node -> operator == O_DOT)
		return(dotted_name(node));
	else {
		print_tree(node);
		fatal("unknown op in define_node");
	} /* end else */
	return(define_name(bucket, category));
} /* end define_node */

Symbol *
use_name(Node *node)
{
	Bucket *bucket;
	Symbol *s, *old, *new;
	if (node -> operator == O_ID || node -> operator == O_OP)
		bucket = node -> bucket;
	else
	if (node -> operator == O_NAME)
		bucket = node -> symbol -> bucket;
	else
	if (node -> operator == O_DOT)
		return(dotted_name(node));
	else {
		print_tree(node);
		fatal("unknown op in use_name");
	} /* end else */
	if (debug['d'])
		fprintf(stderr, "use name %s = %p ", bucket -> name, bucket);
	if (bucket -> token && !node -> code) {
		warn("attempt to use reserved word", bucket -> name, 0);
		return(Nil(Symbol));
	} /* end if */
	if (node -> operator == O_NAME) {
		if (debug['d']) fprintf(stderr, "easy %p\n", node -> symbol);
		return(node -> symbol);
	} /* end if */
	for (s = bucket -> symbols; s; s = s->back)
		if (!(s -> invisible)) {
			if (debug['d']) fprintf(stderr, "found %p\n", s);
			return(s);
		} /* end if */
	/* not visible at current level so must be undef */
	new = new_symbol(bucket);
	old = bucket -> symbols;
	new -> back = old;
	new -> type = T_NO;
	bucket -> symbols = new;
	if (debug['d'])
		fprintf(stderr, "new symbol = %p\n", new);
	return(new);
} /* end use_name */

Symbol *
bind_name(char *name, int type)
{
	return(define_name(lookup_name(namehashtable, name), type));
} /* end assign_type */

void
open_name(Symbol *s)
{
	s -> invisible = 0;
} /* end open_name */

void
open_names(Node *node)
{
	Symbol *sp, *s;
	sp = use_name(node);
	if (sp == Nil(Symbol)) fatal("symbol link 0 in open_names\n");
	s = sp -> down;
	if ((s == Nil(Symbol)) || (!(s -> invisible))) return;
	for (sp=s; sp; sp = sp ->chain)
		sp -> invisible = 0;
} /* end open_names */

void
close_names(Symbol *s)
{
	Symbol *sp;
	if (s == Nil(Symbol)) return;
	for (sp=s; sp; sp = sp ->chain)
		sp -> invisible++;
} /* end close_names */

void
close_name_list(Node *head)
{
	if (head == Nil(Node)) return;
	if (head -> operator == O_PAIR) {
		close_name_list(head -> u.tree.left);
		close_name_list(head -> u.tree.right);
	}
	else
	if (head -> symbol) /*** should be there ***/
		head -> symbol -> invisible++;
} /* end close_name_list */

Symbol *
push_name(Symbol *s)
{
	if (name_stack_ptr != Nil(Symbol))
		name_stack_ptr -> down = s;
	s -> up = name_stack_ptr;
	name_stack_ptr = s;
	return(s);
} /* end push_name */

Symbol *
pop_name(void)
{
	if (name_stack_ptr == Nil(Symbol))
		fatal("name stack underflow");
	close_names(name_stack_ptr -> down);
	name_stack_ptr = name_stack_ptr -> up;
	return (name_stack_ptr);
} /* end pop_name */

void
cmp_name(Symbol *a, Symbol *b)
{
	if (b == (Symbol *) 0) return;
	if (strcmp(a -> bucket -> name, b -> bucket -> name) == 0) return;
	warn(a -> bucket -> name, "and", b -> bucket -> name, "doesn't match", 0);
} /* end cmp_name */

void
full_cmp_name(Node *a, Node *b)
{
	if (b == (Node *) 0) return;
	if (a != b) {
		fprintf(stderr, "mhdl: line %ld: ", line_number);
		print_name(a -> symbol);
		fprintf(stderr, " doesn't match ");
		print_name(b -> symbol);
		fprintf(stderr, "\n");
	} /* end if */
} /* end full_cmp_name */

Symbol *
new_symbol(Bucket *b)
{
	Symbol *s;
	s = (Symbol *) malloc(sizeof (Symbol));
	s -> up = name_stack_ptr;
	s -> down = Nil(Symbol);
	s -> chain = Nil(Symbol);
	s -> back = Nil(Symbol);
	s -> cell = Nil(Cell);
	s -> type = Nil(TypeList);
	if (name_stack_ptr) {
		s -> chain = name_stack_ptr -> down;
		name_stack_ptr -> down = s;
	} /* end if top_level */
	s -> bucket = b;
	s -> category = N_NO; /* start undefined */
	s -> invisible = 0;
	s -> linenumber = line_number;
	return(s);
} /* end new_symbol */

Bucket *
new_bucket(char *name)
{
	Bucket *b;
	b = (Bucket *) malloc(sizeof (Bucket));
	b -> name = (char *) malloc(strlen(name) + 1);
	b -> token = 0;
	b -> symbols = Nil(Symbol);
	strcpy(b -> name, name);
	return(b);
} /* end new_bucket */

Bucket *
lookup_name(Bucket *hashtable[], char *name)
{
	int sum, hash;
	char *namep;
	Bucket *b;
	sum = 0;
	for(namep = name; *namep; ) {
		sum = sum * 3;
		sum += *namep++;
	} /* end for */
	if (sum < 0) sum = ~sum;
	hash = sum % NHASH;
	for(b = hashtable[hash]; b != (Bucket *) 0; b = b -> chain)
		if (strcmp(b -> name, name) == 0)
			return(b);
	b = new_bucket(name);
	b -> chain = hashtable[hash];
	hashtable[hash] = b;
	return(b);
} /* end lookup_name */

Symbol *
alias_name(Symbol *from, Symbol *to)
{
	to -> alias = from;
	return(to);
} /* end alias_name */

Symbol *
define_unit(Bucket *bucket)
{
	Bucket *clone;
	Symbol *new, *old, *s;
	if (debug['d'])
		fprintf(stderr, "define unit %s\n", bucket -> name);
	if (bucket -> token) {
		warn("attempt to redefine reserved word as a unit:", bucket -> name, 0);
		return(Nil(Symbol));
	} /* end if */
	for (s = bucket -> symbols; s; s = s->back)
		if (!(s -> invisible))
		    return(s);
	clone = lookup_name(unithashtable, bucket -> name);
	new = new_symbol(clone);
	old = clone -> symbols;
	new -> back = old;
	clone -> symbols = new;
	return(new);
} /* end define_unit */

void
declare_variations(Node *head, Bucket *original)
{
	Symbol *alias;
	Bucket *ordinary;
	if (head == Nil(Node)) return;
	if (head -> operator == O_PAIR) {
		declare_variations(head -> u.tree.left, original);
		declare_variations(head -> u.tree.right, original);
	}
	else {
		alias = define_unit(head -> bucket);
		ordinary = lookup_name(unithashtable, original -> name);
		if (!ordinary -> symbols)
			fatal("unit missing symbols in declare_variations");
		else
			alias -> alias = ordinary -> symbols;
	}
} /* end declare_variations */

void
check_unit(Node *node)
{
	Bucket *b;
	Symbol *s;
	char *name, *substr;
	int i;
	name = node -> bucket -> name;
	b = lookup_name(unithashtable, name);
	if (b -> symbols && !(b -> symbols -> invisible)) return;
	for (i=0; multable[i].exponent; i++) {
		if (strcmp(name, multable[i].name) == 0) return;
		substr = strstr(name, multable[i].name);
		if (substr == name) {
			b = lookup_name(unithashtable, name+strlen(multable[i].name));
			if (b -> symbols && !(b -> symbols -> invisible)) return;
		} /* end if */
	} /* end for */
	warn("unit", name, "not found", 0);
} /* end check_unit */

void
check_multiplier(char *name)
{
	int i;
	for (i=0; multable[i].exponent; i++)
		if (strcmp(name, multable[i].name) == 0) return;
	warn("multiplier", name, "not found", 0);
} /* end check_multiplier */

void
define_library(char *wp, char *ep)
{
#ifdef PLAN9
	Dir dirbuf;
#else
	struct stat dirbuf;
#endif
	Symbol *sp;
	wp = strtok(NULL, " \t\n:");
	ep = strtok(NULL, " \t\n:");
	if (ep == NULL) {
		warn("missing directory for library", wp, 0);
		return;
	} /* end if */
	if (debug['v'])
		fprintf(stderr, "checking library %s:%s\n", wp, ep);
#ifdef PLAN9
	if (dirstat(ep, &dirbuf))
#else
	if (stat(ep, &dirbuf))
#endif
	{
		warn("Unable to locate library", ep, 0);
	   	return;
	} /* end if */
#ifdef PLAN9
	if (!(dirbuf.mode & CHDIR)) {
#else
	if (!(dirbuf.st_mode & S_IFDIR)) {
#endif
		warn("library filename not a directory:", ep, 0);
		return;
	} /* end if */
	sp = define_name(lookup_name(namehashtable, wp), N_LIBRARY);
	(void) new_library(sp, ep);
} /* end define_library */

char *
strupperdup(char *s)
{
	char upper[MAXLINE];
	char *sp, *dp;
	for (dp=upper, sp=s; *sp;)
		*dp++ = toupper(*sp++);
	*dp = '\0';
	return((char *) strdup(upper));
} /* end strupperdup */

struct token {
	char *name;
	unsigned short token;
};

struct token rwtable[] =
{
	"as",		L_AS,
	"associate",	L_ASSOCIATE,
	"attribute",	L_ATTRIBUTE,
	"case",		L_CASE,
	"char",		L_CHAR,
	"class",	L_CLASS,
	"coercion",	L_COERCION,
	"columns",	L_COLUMNS,
	"component",	L_COMPONENT,
	"components",	L_COMPONENTS,
	"configuration", L_CONFIGURATION,
	"connect",	L_CONNECT,
	"connector",	L_CONNECTOR,
	"connectors",	L_CONNECTORS,
	"connection",	L_CONNECTION,
	"constraint",	L_CONSTRAINT,
	"conversion",	L_CONVERSION,
	"default",	L_DEFAULT,
	"definition",	L_DEFINITION,
	"definitions",	L_DEFINITIONS,
	"derivative",	L_DERIVATIVE,
	"dimension",	L_DIMENSION,
	"each",		L_EACH,
	"else",		L_ELSE,
	"end",		L_END,
	"equation",	L_EQUATION,
	"except",	L_EXCEPT,
	"float",	L_FLOAT,
	"for",		L_FOR,
	"from",		L_FROM,
	"function",	L_FUNCTION,
	"generate",	L_GENERATE,
	"graphic",	L_GRAPHIC,
	"identifier",	L_IDENTIFIER,
	"if",		L_IF,
	"in",		L_IN,
	"includes",	L_INCLUDES,
	"instance",	L_INSTANCE,
	"integral",	L_INTEGRAL,
	"inverse",	L_INVERSE,
	"let",		L_LET,
	"libraries",	L_LIBRARIES,
	"member",	L_MEMBER,
	"model",	L_MODEL,
	"multiplier",	L_MULTIPLIER,
	"names",	L_NAMES,
	"of",		L_OF,
	"operator",	L_OPERATOR,
	"package",	L_PACKAGE,
	"primitive",	L_PRIMITIVE,
	"property",	L_PROPERTY,
	"report",	L_REPORT,
	"row",		L_ROW,
	"set",		L_SET,
	"signal",	L_SIGNAL,
	"string",	L_STRING,
	"structure",	L_STRUCTURE,
	"table",	L_TABLE,
	"then",		L_THEN,
	"title",	L_TITLE,
	"type",		L_TYPE,
	"unit",		L_UNIT,
	"use",		L_USE,
	"variations",	L_VARIATIONS,
	"where",	L_WHERE,
	0
};

struct operator {
	char *name;
	unsigned short token;
};

struct operator optable[] =
{
	"->",		L_RARROW,
	"<-",		L_LARROW,
	"..",		L_DOTS,
	".",		'.',
	":",		':',
	"|",		'|',
	"::",		L_COLONS,
	"<==",		L_LEQEQ,
	"=",		'=',
	"@",		'@',
	"^",		'^',
	"`",		'`',
	"~",		'~',
	"/",		'/',
	"*",		'*',
	"\\",		'\\',
	0
};

void
rwinit(void)
{
	int i;
	Bucket *b;
	Symbol *s;
	for (i=0; i<NHASH; i++)
		namehashtable[i] = unithashtable[i] = (struct Bucket *) 0;
	for (i=0; rwtable[i].name; i++) {
		b = lookup_name(namehashtable, rwtable[i].name);
		b -> token = rwtable[i].token;
	} /* end for */
	for (i=0; rwtable[i].name; i++) {
		b = lookup_name(namehashtable, strupperdup(rwtable[i].name));
		b -> token = rwtable[i].token;
	} /* end for */
	for (i=0; optable[i].name; i++) {
		b = lookup_name(namehashtable, optable[i].name);
		b -> token = optable[i].token;
	} /* end for */
	for (i=0; multable[i].name; i++) {
		b = lookup_name(unithashtable, multable[i].name);
		b -> token = multable[i].exponent;
	} /* end for */
#ifdef MAXINT
	logmaxint = (float) log10((float) MAXINT);
#else
	maxint = (1 << (sizeof(long int)*8)-1) - 1;
	logmaxint = (float) log10((float) maxint);
#endif
} /* end rwinit */
