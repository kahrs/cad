%{

#include <stdio.h>
#include "espectro.h"
#include "espectro.debug"

void yyerror(char *);
int yylex(void);

TreeNode *new_root;
Symbol *model_symbol;
Symbol *outer_symbol;

int inside = 0;

%}

%union {
        TreeNode    *node;
        Bucket  *bucket;
        Symbol  *symbol;
	double	double_value;
	long	long_value;
        char    *string_value;
}

%token SYMBOL
%token L_STRING L_INT L_FLOAT
%token L_TIME_SWEEP L_DC_SWEEP L_SAVE L_SENS L_TO L_FOR L_SIMULATOR L_PARAMSET L_PARAMETERS L_GLOBAL
%token L_SUBCKT L_ENDS L_INTEGER L_REAL L_RETURN L_DC  L_CORRELATE L_INCLUDE L_INLINE L_LIBRARY
%token L_LOCAL L_MARCH L_NODESET L_PRINT L_STATISTICS L_IC L_IF L_MODEL L_ALTERGROUP
%token L_XF L_AC L_NOISE L_SP L_INFO L_OPTIONS L_PARAMTEST L_ELSE L_TRAN

%right  '='
%right	L_UMINUS L_UPLUS
%right	L_EXP
%left   '*' '/' '%'
%left   '+' '-'
%left	L_LSHIFT L_RSHIFT
%left   L_GT L_GE L_LT L_LE
%left	L_EQ L_NE
%left	'&'
%left	L_XNOR L_XOR
%left	L_AND L_OR
%left  '?'

%type<node> start statement element control optbindings special analysis op instance nodes node parameters globals subckt ends
%type<node> subparams function type formals body return ic if model pairings pairing insidename
%type<node> bindings binding names lname name signals signal parameter exprs expr list

%type<string_value> L_STRING

%start start

%%

start		:	statement
				{ new_root = $1; }
		;
statement	:	element
				{ $$ = $1; }
                |       control
				{ $$ = $1; }
		|	analysis
				{ $$ = NIL; }
		;
element		:	instance
				{ $$ = $1; }
		|	subckt
				{ $$ = NIL; }
		|	ends
				{ $$ = NIL; }
		|	parameters
				{ $$ = $1; }
		|	globals
				{ $$ = $1; }
		|	function
				{ $$ = $1; }
		|	ic
				{ $$ = $1; }
		|	if
				{ $$ = $1; }
		|	model
				{ $$ = $1; }
		;
control		:	L_TIME_SWEEP name bindings
				{ $$ = node0(O_CONTROL); }
		|	L_DC_SWEEP name bindings
				{ $$ = node0(O_CONTROL); }
		|	L_SAVE signals
				{ $$ = node0(O_CONTROL); }
		|	L_SENS '(' signals ')' L_TO '(' signals ')' L_FOR '(' SYMBOL ')'
				{ $$ = node0(O_CONTROL); }
		|	L_SIMULATOR binding
				{ $$ = NIL; }
		|	L_ALTERGROUP
				{ $$ = node0(O_CONTROL); }
		|	L_CORRELATE
				{ $$ = node0(O_CONTROL); }
		|	L_INCLUDE L_STRING
				{ include($2); $$ = NIL; }
		|	L_INLINE
				{ $$ = node0(O_CONTROL); }
		|	L_LIBRARY L_STRING
				{ library($2); $$ = NIL; }
		|	L_LOCAL
				{ $$ = node0(O_CONTROL); }
		|	L_MARCH
				{ $$ = node0(O_CONTROL); }
		|	L_NODESET
				{ $$ = node0(O_CONTROL); }
		|	L_PRINT
				{ $$ = node0(O_CONTROL); }
		|	L_STATISTICS
				{ $$ = node0(O_CONTROL); }
		|	SYMBOL L_OPTIONS optbindings
				{ $$ = node0(O_CONTROL); }
		|	SYMBOL L_INFO optbindings
				{ $$ = node0(O_CONTROL); }
		|	SYMBOL L_PARAMTEST optbindings
				{ $$ = node0(O_CONTROL); }
		|	SYMBOL L_TRAN optbindings
				{ $$ = node0(O_CONTROL); }
		|	SYMBOL L_AC optbindings
				{ $$ = node0(O_CONTROL); }
		|	SYMBOL L_DC optbindings
				{ $$ = node0(O_CONTROL); }
		;
optbindings	:	binding optbindings
				{ $$ = node2(O_LIST, $1, $2); }
		|	special optbindings
				{ $$ = node2(O_LIST, $1, $2); }
		|	empty
				{ $$ = NIL; }
		;
special		:	L_SAVE '=' expr
				{ $$ = NIL; }
analysis	:	name '(' nodes ')' op bindings
				{ $$ = NIL; warn("analysis line encountered", ""); }
		;
op		:	L_XF
				{ $$ = NIL; }
		|	L_AC
				{ $$ = NIL; }
		|	L_NOISE
				{ $$ = NIL; }
		|	L_SP
				{ $$ = NIL; }
		;	
instance	:	name '(' nodes ')' name
				{ model_symbol = $5 -> symbol; } /* NOT recursive */
			pairings
				{ 
				  type_symbol($1 -> symbol, T_INSTANCE);
				  $$ = new_instance($1,
						node2(O_COMPONENT, $3, $5), $7);
				}
		|	name L_PARAMSET '{' names exprs '}'
				{ type_symbol($1 -> symbol, T_INSTANCE);
				  $$ = new_instance($1,
						node2(O_PARAMSET, $4, $5), NIL); }
		;
nodes		:	node nodes
				{ $$ = node2(O_LIST, $1, $2); }
		|	node
				{ $$ = node2(O_LIST, $1, NIL); }
		;
node		:	L_INT
				{ $$ = node0(O_VALUE);
				  $$ -> value = new_value(T_INT);
				  $$ -> value -> v.lconstant = yylval.long_value;
				}
		|	name
				{ $$ = $1; }
		;
parameters	:	L_PARAMETERS bindings
				{ $$ = $2; declare_names($2, T_BINDING); }
		;
globals		:	L_GLOBAL names
				{ $$ = NIL; declare_names($2, T_GLOBAL); }
		;
subckt		:	L_SUBCKT name { type_symbol($2 -> symbol, T_SUBCKT);
					push_lexical_level($2 -> symbol); } subparams
				{ start_subckt($2 -> symbol, $4); $$ = NIL; }
		;
ends		:	L_ENDS SYMBOL { outer_symbol = pop_lexical_level(); end_subckt(use_symbol(yylval.bucket), outer_symbol); $$ = NIL; }
		;
subparams	:	'(' formals ')'
				{ $$ = $2; declare_names($2, T_SUBNODE); }
		|	formals
				{ $$ = $1; declare_names($1, T_SUBNODE); }
		|	empty
				{ $$ = NIL; }
		;
function	:	type name { declare_names($2, T_FN);
				    push_lexical_level($2 -> symbol); }
				'(' formals ')' '{' body '}'
				{ declare_names($5, T_FORMAL);
				  pop_lexical_level();
				  new_function($1, $2, $5, $8);
				  $$ = NIL;
				}
		;
type		:	L_INTEGER
				{ $$ = node0(O_FN);
				  $$ -> value = new_value(T_INT);
				}
		|	L_REAL
				{ $$ = node0(O_FN);
				  $$ -> value = new_value(T_FLOAT);
				}
		;
formals		:	{ inside = 1; } names { inside = 0; }
				{ $$ = $2; }
body		:	bindings return
				{ $$ = node2(O_LIST, $1, $2); }
		;
return		:	L_RETURN expr
				{ $$ = node1(O_RETURN, $2); }
		;
ic		:	L_IC bindings
				{ $$ = node1(O_IC, $2); }
		;
if		:	L_IF expr '{'
				{ $$ = node1(O_IF, $2); }
		|	L_ELSE '{'
				{ $$ = node0(O_ELSE); }
		|	'}'
				{ $$ = NIL; }
		;
model		:	L_MODEL name name { model_symbol = $3 -> symbol; push_lexical_level(model_symbol); } /* NOT recursive */
				bindings
				{ type_symbol($2 -> symbol, T_MODEL);
				  new_model($2, $3, $5);
				  $$ = NIL; model_symbol = NIL;
				  (void) pop_lexical_level();
				}
		;
pairings	:	pairing pairings
				{ $$ = node2(O_LIST, $1, $2); }
		|	empty
				{ $$ = NIL; }
		;
pairing		:	insidename '=' expr
				{ $$ = node2(O_BIND, $1, $3); }

		;
insidename	:	SYMBOL
				{ $$ = node0(O_NAME);
				  $$ -> symbol = use_model_symbol(yylval.bucket);
				}
		;	
bindings	:	binding bindings
				{ $$ = node2(O_LIST, $1, $2); }
		|	empty
				{ $$ = NIL; }
		;
binding		:	lname '=' expr
				{ $$ = node2(O_BIND, $1, $3); }

		;
names		:	name names
				{ $$ = node2(O_LIST, $1, $2); }
	
		|	name
				{ $$ = node2(O_LIST, $1, NIL); }
		;
lname		:	SYMBOL
				{ $$ = node0(O_NAME);
				  $$ -> symbol = define_symbol(yylval.bucket);
				  type_symbol($$ -> symbol, T_BINDING);
				}
		;
name		:	SYMBOL
				{ $$ = node0(O_NAME);
				  if (inside) $$ -> symbol = define_symbol(yylval.bucket);
				  else {
				    $$ -> symbol = use_symbol(yylval.bucket);
				    }
				}
		;
signals		:	signal signals
				{ $$ = node2(O_LIST, $1, $2); }
		|	signal
				{ $$ = node0(O_NAME);
				  $$ -> symbol = use_symbol(yylval.bucket); }
		;
signal		:	SYMBOL
				{ $$ = node0(O_NAME);
				  $$ -> symbol = use_symbol(yylval.bucket); }
		;
parameters	:	parameter parameters
				{ $$ = node2(O_LIST, $1, $2); }
		|	empty
				{ $$ = NIL; }
		;
parameter	:	name
				{ $$ = $1; }
		|	L_STRING
				{ $$ = node0(O_VALUE);
				  $$ -> value = new_value(T_STRING);
				  $$ -> value -> v.string = yylval.string_value;
				}
		|	binding
				{ $$ = $1; }
		;
exprs		:	exprs expr
				{ $$ = node2(O_LIST, $1, $2); }
		|	expr
				{ $$ = $1; }
		;
list            :       expr ',' list
                                { $$ = node2(O_LIST, $1, $3); }
                |       expr
				{ $$ = node2(O_LIST, $1, NIL); }
                ;
expr		:	name   
				{ $$ = $1; }
		|	name '(' list ')'
				{ $$ = node2(O_FN, $1, $3); }
		|	'(' expr ')' 
				{ $$ = $2; }
		|	expr '+' expr
				{ $$ = node2(O_ADD, $1, $3); }
		|	expr '-' expr
				{ $$ = node2(O_SUB, $1, $3); }
		|	expr '*' expr
				{ $$ = node2(O_MUL, $1, $3); }
		|	expr '/' expr
				{ $$ = node2(O_DIV, $1, $3); }
		|	expr '%' expr
				{ $$ = node2(O_MOD, $1, $3); }
		|	expr L_EXP expr
				{ $$ = node2(O_POWER, $1, $3); }
		|	'+' expr   %prec L_UPLUS
				{ $$ = $2; }
		|	'-' expr   %prec L_UMINUS  
				{ $$ = node1(O_NEGATE, $2); }
		|	'!' expr   %prec L_UMINUS  
				{ $$ = node1(O_NOT, $2); }
		|	expr '&' expr
				{ $$ = node2(O_AND, $1, $3); }
		|	expr L_AND expr
				{ $$ = node2(O_AND, $1, $3); }
		|	expr '|' expr
				{ $$ = node2(O_OR, $1, $3); }
		|	expr L_OR expr
				{ $$ = node2(O_OR, $1, $3); }
		|	expr L_GT expr
				{ $$ = node2(O_GT, $1, $3); }
		|	expr L_GE expr
				{ $$ = node2(O_GE, $1, $3); }
		|	expr L_LT expr
				{ $$ = node2(O_LT, $1, $3); }
		|	expr L_LE expr
				{ $$ = node2(O_LE, $1, $3); }
		|	expr L_EQ expr
				{ $$ = node2(O_EQ, $1, $3); }
		|	expr L_NE expr
				{ $$ = node2(O_NE, $1, $3); }
		|	expr '?' expr ':' expr
				{ $$ = node3(O_CONDEXPR, $1, $3, $5); }
		|	L_STRING
				{ $$ = node0(O_VALUE);
				  $$ -> value = new_value(T_STRING);
				  $$ -> value -> v.string = yylval.string_value;
				}
		|	L_INT
				{ $$ = node0(O_VALUE);
				  $$ -> value = new_value(T_INT);
				  $$ -> value -> v.lconstant = yylval.long_value;
				}
		|	L_FLOAT
				{ $$ = node0(O_VALUE);
				  $$ -> value = new_value(T_FLOAT);
				  $$ -> value -> v.dconstant = yylval.double_value;
				}
		|	'[' exprs ']'
				{ $$ = node0(O_VALUE);
				  $$ -> value = new_value(T_LIST);
				  /** $$ -> value = cvlist($2); **/
				}
		;
empty		:
		;
