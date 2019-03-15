/*
 * MIES - MHDL Interpreter / Evaluator System
 */

#define NPACKAGES 10
#define NNAMESTACK 10
#define NMULTIPLIER 100
#define NHASH 1023
#define MAXLINE 80

#define Nil(t) (struct t *) 0
#define NIL (void *) 0

enum names
{
/*0*/	NO_NAME,
	ABS_PROP_NAME,
	CLASS_NAME,
	COMPONENT_NAME,
	CONFIG_NAME,
	CONNECT_LIST_NAME,
	CONNECTOR_NAME,
	CONSTRAINT_NAME,
	CONSTRUCTOR_NAME,
	DIM_NAME,
/*10*/	EQUATION_NAME,
	FIELD_NAME,
	FUNCTION_NAME,
	INSTANCE_NAME,
	LABEL_NAME,
	LIBRARY_NAME,
	MODEL_NAME,
	MULTIPLIER_NAME,
	NAMED_VALUE_NAME,
	OBJECT_NAME,
/*20*/	PACKAGE_NAME,
	POLYMORPHIC_NAME,
	STRUCTURE_MODEL_NAME,
	STRUCT_MODEL_COMP_NAME,
	STRUCTURE_NAME,	
	TABLE_NAME,
	TYPE_NAME,
	UNIT_NAME,
	END_NAME
};

#define N_NO 0
#define N_ABS_PROP (1 << ABS_PROP_NAME)
#define N_CLASS (1 << CLASS_NAME)
#define N_COMPONENT (1 << COMPONENT_NAME)
#define N_CONFIG (1 << CONFIG_NAME)
#define N_CONNECT_LIST  (1 << CONNECT_LIST_NAME)
#define N_CONNECTOR (1 << CONNECTOR_NAME)
#define N_CONSTRAINT (1 << CONSTRAINT_NAME)
#define N_CONSTRUCTOR (1 << CONSTRUCTOR_NAME)
#define N_DIM (1 << DIM_NAME)
#define N_EQUATION (1 << EQUATION_NAME)
#define N_FIELD (1 << FIELD_NAME)
#define N_FUNCTION (1 << FUNCTION_NAME)
#define N_INSTANCE (1 << INSTANCE_NAME)
#define N_LABEL (1 << LABEL_NAME)
#define N_LIBRARY (1 << LIBRARY_NAME)
#define N_MODEL (1 << MODEL_NAME)
#define N_MULTIPLIER (1 << MULTIPLIER_NAME)
#define N_NAMED_VALUE (1 << NAMED_VALUE_NAME)
#define N_OBJECT  (1 << OBJECN_NAME)
#define N_PACKAGE (1 << PACKAGE_NAME)
#define N_POLYMORPHIC (1 << POLYMORPHIC_NAME)
#define N_STRUCTURE_MODEL  (1 << STRUCTURE_MODEL_NAME)
#define N_STRUCTURE (1 << STRUCTURE_NAME)
#define N_STRUCN_MODEL_COMP (1 << STRUCN_MODEL_COMP_NAME)
#define N_TABLE (1 << TABLE_NAME)
#define N_TYPE (1 << TYPE_NAME)
#define N_UNIT (1 << UNIT_NAME)

#define T_DEFINED -1

typedef struct Symbol Symbol;

/*
 * Structures specific to the type checker & inferencer
 */

typedef struct Type Type;
typedef struct TypeVar TypeVar;
typedef struct TypeList TypeList;
typedef struct TypePair TypePair;
typedef struct TypeScheme TypeScheme;
typedef struct TypeConstraint TypeConstraint;
typedef struct TypeConstructor TypeConstructor;

enum families {
	T_NO,
	T_VAR,
	T_BASE,
	T_ARROW,
	T_PRODUCT,
	T_CONSTRUCTOR,
	T_ANY
};

enum kinds {
	K_NO,
	K_INSTANCE,
	K_QUANTIFIER
};

struct TypeVar {
	unsigned char kind;
	Symbol *symbol;
	Type *instance; /* K_INSTANCE */
	int depth; /* K_QUANTIFIER */
};

struct TypeList {
	union {
		TypeScheme *scheme;
		TypeVar *variable;
		Type *type;
	} head;	
	TypeList *tail;
};

struct TypePair {
	Type *left;
	Type *right;
};

struct TypeScheme {
	Type *type;
	TypeList *list;
	TypeConstraint *constraint;
	TypeScheme *result;
};

struct TypeConstraint {
	Symbol *op;
	TypePair f;
	TypeConstraint *next;
};

struct TypeConstructor {
	Symbol *op;
	TypeList *list;
};

struct Type {
	unsigned char family;
	union {
		TypeVar *variable;
		Symbol *base_type;
		TypePair function;
		TypePair product;
		TypeConstructor *constructor;
		Type *list;
	} u;
};

typedef struct Bucket Bucket;
typedef struct Cell Cell;
typedef struct Node Node;

struct Bucket {
	char *name;
	int token;
	Bucket *chain;
	Symbol *symbols;
};

struct Symbol {
	/*
	 * bucket -> pointer to one and only hashed bucket
	 */
	Bucket *bucket;
	/* 
	 * up -> upward scope chain 
	 * down -> downward scope chain
	 * chain -> list of symbols with the same scope
	 * back -> backwards scope chain with the SAME name
	 * alias -> Symbol at same scope with a different name
	 *
	 * category = integer category code
	 * type = declared or derived type
	 * invisible = bit for visibility
	 * linenumber = where Symbol was created
	 */
	Symbol *up, *down;
	Symbol *chain, *back;
	Symbol *alias;
	Cell *cell;
	TypeList *type;
	int category;
	char invisible;
	int linenumber;
};

struct Node {
	unsigned char operator;
	union {
		struct {
			Node *left, *right;
		} tree;
		double	fconstant;
		long	iconstant;
		char	cconstant;
		char*	string;
	} u;
	Bucket	*bucket;
	Symbol	*symbol;
	Type	*type;
	int	code;
	int	line;
};

#define Left(x) (x -> u.tree.left)
#define Right(x) (x -> u.tree.right)

/*
 * Type specific structures
 */

typedef struct Class Class;
typedef struct Configuration Configuration;
typedef struct Constraint Constraint;
typedef struct Function Function;
typedef struct Generate Generate;
typedef struct Instance Instance;
typedef struct Label Label;
typedef struct Library Library;
typedef struct Multiplier Multiplier;
typedef struct Name Name;
typedef struct Structure Structure;
typedef struct Table Table;
typedef struct Unit Unit;

struct Cell {
	Symbol *symbol;
	char *filename;
	long int linenumber;
	union {
		Class *class;
		Configuration *configuration;
		Constraint *constraint;
		Function *function;
		Generate *generate;
		Instance *instance;
		Label *label;
		Library *library;
		Multiplier *multiplier;
		Name *name;
		Structure *structure;
		Table *table;
		Unit *unit;
	} cell;
	Cell *chain;
};

struct Class {
	int arity;
	Node *signature;
	Node *header;
	Node *context;
	Class *superclass;
	Node *members;
	Node *defaults;
	Node *instances;
};

struct Configuration {
	Cell *parent;
	Node *body;
};

struct Constraint {
	Node *definition;
	Node *properties;
	Node *report;
	char dependency;
};

struct Generate {
	Node *header;
	Node *body;
};

struct Instance {
	int signature; /* eventually a hashcode */
	TypeScheme *scheme;
	Node *body;
	Node *context;
	Instance *chain;
};

struct Label {
	Node *branch;
	Node *properties;
};

struct Library {
	char *path;
};

struct Multiplier {
	float scale_factor;
};

enum flags {
	F_NULL,
	F_DEFAULT,
	F_COERCION,
	F_DEPENDANT,
	F_ATTRIBUTE,
	F_SIGNAL,
	F_COMPONENT,
	F_CONNECTOR,
	F_CONSTRAINT,
	F_DEFINITION,
	F_DIMENSION,
	F_EQUATION,
	F_FUNCTION,
	F_MODEL,
	F_PROPERTY,
	F_STRUCTURE,
	F_TYPE,
	F_UNIT
};

struct Name {
	Node *type_graph;
	Node *inferred_type;
	Cell *primitive;	
	Node *properties;
	int flags; /* see flags above */
};

struct Structure {
	int kind;
	Node *definitions;
	Node *items;
	Node *connectors;
	Node *properties;
};

struct Table {
	char *name;
	int length;
	char **column_headers;
	char **column_names;
	Node *data;
};

struct Function {
	int arity;
	int family;
	Type *type;
	Node *context;
};

struct Unit {
	int kind; /* dimension or unit */
	long conversion_factor;
	Node *designation;
	Node *conversion;
};

/*
 * Parse tree node operators
 */

enum operators {
	O_NULL,
	O_LIST,
	O_ALT,
	O_RHS,
	O_GUARD,
	O_CASE,
	O_ELSE,
	O_IF,
	O_INVERSE,
	O_DERIV,
/*10*/	O_INTEGRAL,
	O_DIVIDE,
	O_MULTIPLY,
	O_EXP,
	O_PREOP,
	O_SCALE,
	O_POSTOP,
	O_LET,
	O_LAMBDA,
	O_QUALIFIED,
/*20*/	O_DOTS,
	O_MINUS,
	O_APPLY,
	O_QUALIFIER,
	O_AT,
	O_TILDE,
	O_WILDCARD,
	O_VALUE_DEF,
	O_DEFAULT,
	O_NAME,
/*30*/	O_OP,
	O_RARROW,
	O_PREDICATE,
	O_TYPE,
	O_DOT,
	O_COERCE,
	O_CONFIG,
	O_USE,
	O_FOR,
	O_FOREACH,
/*40*/	O_INSTANCE,
	O_CONTEXT,
	O_PRIMITIVE,
	O_CONNECT,
	O_ID,
	O_ABS_DEF,
	O_ASSOC,
	O_GENERATE,
	O_TYPED,
	O_WITH,
/*50*/	O_PAIR,
	O_PATTERN,
	O_DESIGNATOR,
	O_WHERE,
	O_SEMI,
	O_INT,
	O_FLOAT,
	O_CHAR,
	O_STRING,
/*60*/	O_END
};

/*
 * from lex.c
 */

extern char *filename;
extern long int line_number;
	
/*
 * from mhdl.c
 */

void fatal(char *);
void warn(char *first, ...);
void semantics(Node *, char *first, ...);

/*
 * from sym.c
 */

void print_symbol_table(void);
void check_name(Node *node, unsigned int category);
void verify_name_type(Node *node, unsigned int category);
Symbol *declare_name(Symbol *name, int category);
Symbol *push_name(Symbol *s);
void cmp_name(Symbol *a, Symbol *b);
void full_cmp_name(Symbol *a, Symbol *b);
Symbol *pop_name(void);
Bucket *lookup_name(Bucket **hashtable, char *name);
Symbol *define_name(Bucket *b, int category);
Symbol *define_node(Node *node, int category);
Symbol *use_name(Node *n);
Symbol *use_id(Node *node);
Symbol *new_symbol(Bucket *b);
Symbol *alias_name(Symbol *from, Symbol *to);
void open_names(Node *n);
void open_name(Symbol *s);
void close_name_list(Node *head);
Symbol *define_unit(Bucket *name);
void declare_variations(Node *head, Bucket *original);
void check_unit(Node *node);
void check_multiplier(char *name);
void print_undefs(Symbol *top);
void rwinit(void);
Symbol *dereference_node(Node *node);

char debug[256];
extern char *cmdname;

long int maxint;
float logmaxint;

/*
 * from semantics.c
 */

extern long int node_number;

Node *new_node(int operator, Node *left, Node *right);
void print_node(Node *node);
Cell *new_class(Symbol *symbol, Node *types, Node *body, Node *context);
Cell *new_config(Symbol *header, Node *body);
Cell *new_constraint(Symbol *symbol, Node *body, Node *report);
Type *new_fn_type(Type *left, Type *right);
Cell *new_generate(Node *header, Node *body);
Cell *new_instance(Symbol *sym, Node *spec, Node *body, Node *context);
Node *new_label(Symbol *label, Node *def);
Cell *new_library(Symbol *sym, char *path);
Cell *new_multiplier(Symbol *sym, float scale_factor);
void new_names(Node *list, int flag, Node *type_spec);
Cell *new_structure(Symbol *sym, int kind, Node *name, Node *connectors, Node *defs);
Cell *new_table(Symbol *sym, Node *header, Node *columns, Node *names, Node *data);
Cell *new_fn(Symbol *sym, int arity, Type *signature, Node *context);
Cell *new_unit(Symbol *s, Node *body, Node *variations);
Cell *merge_structs(Cell *old, Cell *new);
void load_library(Node *node);
void analyze(Node *root);
void print_tree(Node *root);
int tree_length(Node *head);

/*
 * from sym.c
 */

Symbol *bind_name(char *name, int type);

/*
 * from types.c
 */

int type_check(Node *root, int depth);
void type_init(void);
void print_type(Type *exp);
void print_type_schemes(TypeList *list);
Type *new_type(int family);
Type *new_list_type(Type *of);
Type *new_fn_type(Type *left, Type *right);
Type *spec2type(Node *spec);
TypeScheme *new_type_scheme(Type *t, TypeList *vl);

/*
 * stolen from plan 9
 */

#ifndef PLAN9
#define	ARGBEGIN	for((argv0? 0: (argv0=*argv)),argv++,argc--;\
			    argv[0] && argv[0][0]=='-' && argv[0][1];\
			    argc--, argv++) {\
				char *_args, *_argt, _argc;\
				_args = &argv[0][1];\
				if(_args[0]=='-' && _args[1]==0){\
					argc--; argv++; break;\
				}\
				while(*_args) switch(_argc=*_args++)
#define	ARGEND		}
#define	ARGF()		(_argt=_args, _args="",\
				(*_argt? _argt: argv[1]? (argc--, *++argv): 0))
#define	ARGC()		_argc
char *argv0;
#endif

#define YYSTYPE yystype
