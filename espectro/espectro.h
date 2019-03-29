/*
 * stolen from plan 9
 */

#ifndef PLAN9
#define ARGBEGIN        for((argv0? 0: (argv0=*argv)),argv++,argc--;\
                            argv[0] && argv[0][0]=='-' && argv[0][1];\
                            argc--, argv++) {\
                                char *_args, *_argt, _argc;\
                                _args = &argv[0][1];\
                                if(_args[0]=='-' && _args[1]==0){\
                                        argc--; argv++; break;\
                                }\
                                while(*_args) switch(_argc=*_args++)
#define ARGEND    }
#define ARGF()    (_argt=_args, _args="",\
                                (*_argt? _argt: argv[1]? (argc--, *++argv): 0))
#define ARGC()    _argc
char *argv0;
#endif

#define NIL (void *) 0
#define NHASH 1023
#define MAXLEX 10
#define MAXFRAME 20
#define MAXSTACK 200
#define MAXSTRING 200
#define EPSILON 1e-12

typedef struct Symbol Symbol;
typedef struct Bucket Bucket;
typedef struct TreeNode TreeNode;
typedef struct Value Value;
typedef struct Frame Frame;
typedef struct NodeBucket NodeBucket;
typedef struct CircuitNode CircuitNode;
typedef struct IntPair IntPair;
typedef struct DoublePair DoublePair;
typedef struct Component Component;
typedef struct ExternalNode ExternalNode;
typedef struct ReducedTemplate ReducedTemplate;
typedef union Pair Pair;

struct Bucket {
	char *name;
	int token;
	Bucket *chain;
	Symbol *symbols;
};

struct Symbol {
	Bucket *bucket;	/* bucket -> pointer to one and only hashed bucket */
	Symbol *up;	/* previous scope */
	Symbol *next;	/* next Symbol in the same scope */
	Symbol *chain;	/* next Symbol in the same Frame */
	TreeNode *fixup; /* Pointer to the O_NAME node with this symbol pointer */
	int type;
	int return_type; /* only for functions */
	int ll; /* lexical level */
	union {
		TreeNode	*bindings;
		TreeNode	*parameters;
	} u;
	union {
		TreeNode	*extended_model;
		TreeNode	*body;
		Value		*value;
	} bound;
};

struct NodeBucket {
	int absolute;
	CircuitNode *node;
	NodeBucket *chain;
};

struct TreeNode {
	unsigned char operator;
	int	limit;
	TreeNode *branches[7];
	Value	*value;
	Symbol  *symbol;
	TreeNode *fixup; /* fixup chain */
	int     line_number;
	char	*filename;
};

struct CircuitNode {
	Symbol	*symbol;
	int index;
	int absolute;
};

struct Value {
	int type;
	int level; /* dynamic level */
	Value *next; /* next Value in the current dynamic level */
	Symbol *symbol; /* backwards pointer */
	union {
		int	bconstant;
		long	lconstant;
		double  dconstant;
		char	cconstant;
		char	*string;
		double	(*builtin)(); /* could be builtin fn or model */
		CircuitNode *node;
		ReducedTemplate *template;
	} v;
};

struct Frame {
	Symbol *name; /* name of component */
	Symbol *bindings; /* chain of properties defined at this level */
	Value **values; /* pointer to the bottom of the value stack for this frame */
	int original_value_stack_ptr; /* at entry - restored at exit */
};
	
struct IntPair {
	char *name;
	int *var;
	int default_value;
};
	
struct DoublePair {
	char *name;
	double *var;
	double default_value;
};

union Pair {
	IntPair int_pair;
	DoublePair double_pair;
};

struct ExternalNode {
	char *name;
	int index;
};

struct Component {
	char *instance_name;
	char *component_name;
	Pair *bindings;
	int node_count;
	ExternalNode *nodes;
	Component *next;
}; 

struct ReducedTemplate {
	char *name;
	int nodes;
	char **node_names;
	DoublePair **bindings;
	int sources;
};

TreeNode *node0(int operator);
TreeNode *node1(int operator, TreeNode *branch1);
TreeNode *node2(int operator, TreeNode *branch1, TreeNode *branch2);
TreeNode *node3(int operator, TreeNode *branch1, TreeNode *branch2, TreeNode *branch3);
TreeNode *node4(int operator, TreeNode *branch1, TreeNode *branch2, TreeNode *branch3, TreeNode *branch4);
TreeNode *node5(int operator, TreeNode *branch1, TreeNode *branch2, TreeNode *branch3, TreeNode *branch4, TreeNode *branch5);
TreeNode *node6(int operator, TreeNode *branch1, TreeNode *branch2, TreeNode *branch3, TreeNode *branch4, TreeNode *branch5, TreeNode *branch6);
TreeNode *node7(int operator, TreeNode *branch1, TreeNode *branch2, TreeNode *branch3, TreeNode *branch4, TreeNode *branch5, TreeNode *branch6, TreeNode *branch7);

/*
 * Parse tree node operators
 */

enum parse_nodes {
	O_NULL,
	O_CONTROL,
	O_FN,
	O_GT,
	O_GE,
	O_LT,
	O_LE,
	O_EQ,
	O_NE,
	O_UMINUS,
/*10*/	O_LIST,
	O_RESISTOR,
	O_CAPACITOR,
	O_INDUCTOR,
	O_SOURCE,
	O_CALL,
	O_NAME,
	O_VALUE,
	O_STRING,
	O_BIND,
/*20*/	O_ADD,
	O_SUB,
	O_MUL,
	O_DIV,
	O_MOD,
	O_POWER,
	O_NEGATE,
	O_INSTANCE,
	O_COMPONENT,
	O_PARAMSET,
/*30*/	O_RETURN,
	O_CONDEXPR,
	O_IC,
	O_IF,
	O_MODEL,
	O_NOT,
	O_AND,
	O_OR,
	O_ELSE,
	O_END
/*40*/
};

enum types {
	T_NONE,
	T_MODEL,
	T_SUBCKT,
	T_BINDING,
	T_SUBNODE,
/* 5*/	T_FN,
	T_FORMAL,
	T_BOOL,
	T_INT,
	T_FLOAT,
/*10*/	T_STRING,
	T_LIST,
	T_INSTANCE,
	T_GLOBAL,
	T_SIGNAL,
/*15*/	T_BUILTIN,
	T_TEMPLATE,
	T_END
};

enum matrix {
	M_NONE,
	M_STORE,
	M_ADD,
	V_STORE,
	V_ADD,
	M_END
};

/* prototypes */

TreeNode *declare_names(TreeNode *head, int type);
Symbol *use_symbol(Bucket *name);
Symbol *use_model_symbol(Bucket *name);
void push_lexical_level(Symbol *);
Symbol *pop_lexical_level();
void type_symbol(Symbol *s, int type);
Symbol *define_symbol(Bucket *b);

double find_symbol_double(char *name, double def);
int find_symbol_int(char *name, int def);
int top_frame_size();
Value *top_frame_arg(int offset);
Symbol *add_symbol(char *name);
Symbol *find_symbol(char *name);
int new_node();
char *full_symbol_name(Symbol *s);
void chain_fixup(TreeNode *node);

void start_subckt(Symbol *s, TreeNode *parameters);
void end_subckt(Symbol *end_s, Symbol *stacked_s);
void new_model(TreeNode *name, TreeNode *old_name, TreeNode *bindings);
void new_function(TreeNode *type, TreeNode *name, TreeNode *formals, TreeNode *body);
Value *new_value(int type);
TreeNode *new_instance(TreeNode *name, TreeNode *body, TreeNode *bindings);
char *frame_names();

void fill_double_pairs(DoublePair pairs[]);
void fill_int_pairs(IntPair pairs[]);

extern char debug[];

void include(char *filename);
void library(char *filename);

void builtin_function_init(void);
void builtin_model_init();

void fatal(char *msg);
void warn(char *first, ...);
void error(char *first, ...);

