/*
 * t square input language
  */

%{

#include "t2.h"

extern struct NODE *NullaryNode();
extern struct NODE *StringNode();
extern struct NODE *UnaryNode();
extern struct NODE *BinaryNode();
extern struct NODE *DeclarePlan();
extern char *CopyString();

extern struct PROPERTY_VALUE *PatchManifests();
extern struct PROPERTY_VALUE *DeclareManifest();
extern struct MATERIAL_VALUES *DeclareProperty();
extern struct MATERIAL_VALUES *PatchProperties();

extern struct NODE *treeRoot;
extern struct NODE *materialName, *propertyName;

typedef union {
	struct NODE *node;
	struct PROPERTY_VALUE *property;
	struct MATERIAL_VALUES *material;
} YYSTYPE;

extern int integerConstant;
extern float floatingConstant;
extern char stringBuffer[128];
extern char yytext[];

char *quoted;

%}

%token ID NUMBER
%token UMINUS LT LE EQ GE GT NE EXP
%token MATERIAL OBJECT GLOBAL PROPERTIES
%token CYLINDER BLOCK SPHERE
%token IN FT M CM MM
%token DO IF FOR THEN ELSE AT SWITCH
%token INTEGER FLOAT STRING

%token CONSTANT LIST FUNCTION CALL TERMINAL PROPERTY COMPOUND TUPLE
%token UNION INTERSECT ROTATE DIFFERENCE ASSEMBLY TUPLE UPTO DOWNTO BIND
%token ALTERNATIVE LABEL /* not used by parser */

%left '|' '&'
%left '+' '-'
%left '*' '/'
%left '^'
%left UMINUS
%right EXP
%nonassoc LT LE EQ GE GT NE

%type <node> plan stmnt declaration material property_list alternatives
%type <node> object params idlist plan csg primitive for range switch label
%type <node> optionalList list location double triple units expression
%type <node> conditional constant variable objective if terminal postpositions
%type <node> STRING ID
%type <property> plist pequals
%type <material> property properties
 
%%

start	:	plan
			{ treeRoot = $1; }
	;
plan	:	plan stmnt
			{ $$ = BinaryNode(COMPOUND, $1, $2); }
	|	stmnt
			{ $$ = $1; }
	;
stmnt	:	declaration
			{ $$ = $1; }
	|	object
			{ $$ = $1; }
	;

declaration :	material
			{ $$ = Null_struct(NODE); }
	|	global
			{ $$ = Null_struct(NODE); }
	;
material :	MATERIAL variable '{' properties '}'
			{ DeclareMaterial($2, $4);  }
	;
properties :	properties property
			{ $$ = PatchProperties($1, $2); }
	|	property
			{ $$ = $1; }
	;
property :	PROPERTIES variable '{' plist '}'
			{ $$ = DeclareProperty($2, $4); }
	;
plist	:	plist ',' pequals
			{ $$ = PatchManifests($1, $3); }
	|	pequals
			{ $$ = $1; }
	;
pequals	:	variable '=' constant
			{ $$ = DeclareManifest($1 -> string, $3); }
	;
global	:	GLOBAL '{' glist '}'
	;
glist	:	glist ',' gequals
	|	gequals
	;
gequals	:	variable '=' constant
			{ DeclareGlobal($1 -> string, $3); }
	;

object	:	OBJECT variable params '=' objective
			{ DeclareObject($2, BinaryNode(OBJECT, $3, $5)); }
	;
params	:	'(' idlist ')'
			{ $$ = $2; }
	|	empty
			{ $$ = Null_struct(NODE); }
	;
idlist	:	variable
			{ $$ = BinaryNode(TUPLE, $1, Null_struct(NODE)); }
	|	variable ',' idlist
			{ $$ = BinaryNode(TUPLE, $1, $3); }
	;
objective :	if
			{ $$ = $1; }
	|	for
			{ $$ = $1; }
	|	switch
			{ $$ = $1; }
	|	csg
			{ $$ = $1; }
	;
for	:	FOR variable IN range DO objective
			{ $$ = BinaryNode(FOR, BinaryNode(BIND, $2, $4), $6); }
	;
range	:	expression UPTO expression
			{ $$ = BinaryNode(UPTO, $1, $3); }
	|	expression DOWNTO expression
			{ $$ = BinaryNode(DOWNTO, $1, $3); }
	;
if	:	IF '(' conditional ')' THEN objective ELSE objective
			{ $$ = BinaryNode(IF, $3, BinaryNode(ELSE, $6, $8)); }
	;
switch	:	SWITCH '(' expression ')' IN '{' alternatives '}'
			{ $$ = BinaryNode(SWITCH, $3, $7); }
	;
alternatives :	alternatives ',' label
			{ $$ = BinaryNode(ALTERNATIVE, $1, $3); }
	|	label
			{ $$ = Null_struct(NODE); }
	;
label	:	constant ':' csg
			{ $$ = BinaryNode(LABEL, $1, $3); }
	|	constant ':' constant
			{ $$ = BinaryNode(LABEL, $1, $3); }
	;
csg	:	primitive
			{ $$ = $1; }
	|	csg '|' csg
			{ $$ = BinaryNode(UNION, $1, $3); }
	|	csg '&' csg
			{ $$ = BinaryNode(INTERSECT, $1, $3); }
	|	csg '-' csg
			{ $$ = BinaryNode(DIFFERENCE, $1, $3); }
	|	csg '+' csg
			{ $$ = BinaryNode(ASSEMBLY, $1, $3); }
	|	csg '*' '[' triple ']'
			{ $$ = BinaryNode(ROTATE, $1, $4); }
	|	'(' csg ')'
			{ $$ = $2; }
	;
primitive :	terminal postpositions location
			{ $$ = BinaryNode(TERMINAL, $1, BinaryNode(LIST, $2, $3)); }
	;
postpositions :	':' property_list
			{ $$ = $2; }
	|	empty
			{ $$ = Null_struct(NODE); }
	;
property_list :	property_list variable
			{ $$ = BinaryNode(PROPERTY, $2, $1); }
	|	variable
			{ $$ = BinaryNode(PROPERTY, $1, Null_struct(NODE)); }
	;
terminal :	CYLINDER '(' double ')'
			{ $$ = UnaryNode(CYLINDER, $3); }
	|	BLOCK '(' triple ')'
			{ $$ = UnaryNode(BLOCK, $3); }
	|	SPHERE '(' expression ')'
			{ $$ = UnaryNode(SPHERE, $3); }
	|	variable optionalList
			{ $$ = BinaryNode(CALL, $1, $2); }
	;
optionalList :	'(' list ')'
			{ $$ = $2; }
	|	empty
			{ $$ = Null_struct(NODE); }
	;
list	:	expression
			{ $$ = BinaryNode(TUPLE, $1, Null_struct(NODE)); }
	|	expression ',' list
			{ $$ = BinaryNode(TUPLE, $1, $3); }
	;
location :	AT '[' triple ']'
			{ $$ = UnaryNode(AT, $3); }
	|	empty
			{ $$ = Null_struct(NODE); }
	;
double	:	expression ',' expression
			{ $$ = BinaryNode(TUPLE, $1, BinaryNode(TUPLE, $3, Null_struct(NODE))); }
	;
triple	:	expression ',' expression ',' expression
			{ $$ = BinaryNode(TUPLE, $1, BinaryNode(TUPLE, $3, BinaryNode(TUPLE, $5, Null_struct(NODE)))); }
	;
units	:	IN
			{ $$ = NullaryNode(IN); }
	|	FT
			{ $$ = NullaryNode(FT); }
	|	M
			{ $$ = NullaryNode(M); }
	|	CM
			{ $$ = NullaryNode(CM); }
	|	MM
			{ $$ = NullaryNode(MM); }
	|	STRING
			{ $$ = UnaryNode(CONSTANT, $1); }
	|	empty
			{ $$ = Null_struct(NODE); }
	;
expression :	expression '+' expression
			{ $$ = BinaryNode('+', $1, $3); }
	|	expression '-' expression
			{ $$ = BinaryNode('-', $1, $3); }
	|	expression '*' expression
			{ $$ = BinaryNode('*', $1, $3); }
	|	expression '/' expression
			{ $$ = BinaryNode('/', $1, $3); }
	|	expression EXP expression
			{ $$ = BinaryNode(EXP, $1, $3); }
	|	'-' expression %prec UMINUS
			{ $$ = UnaryNode(UMINUS, $2); }
	|	variable
			{ $$ = $1; }
	| 	constant units
			{ $$ = BinaryNode(CONSTANT, $1, $2); }
	|	variable '(' list ')'
			{ $$ = BinaryNode(FUNCTION, $1, $3); }
	;
conditional :	expression LE expression
			{ $$ = BinaryNode(LE, $1, $3); }
	|	expression LT expression
			{ $$ = BinaryNode(LT, $1, $3); }
	|	expression EQ expression
			{ $$ = BinaryNode(EQ, $1, $3); }
	|	expression GE expression
			{ $$ = BinaryNode(GE, $1, $3); }
	|	expression GT expression
			{ $$ = BinaryNode(GT, $1, $3); }
	|	expression NE expression
			{ $$ = BinaryNode(NE, $1, $3); }
	;
constant :	INTEGER
			{ $$ = StringNode(INTEGER, CopyString(yytext)); }
	|	FLOAT
			{ $$ = StringNode(FLOAT, CopyString(yytext)); }
	|	STRING
			{ quoted = CopyString(yytext+1);
			  quoted[strlen(quoted)-1] = '\0';
			  $$ = StringNode(STRING, quoted);
			}
	;
variable :	ID
			{ $$ = StringNode(ID, CopyString(yytext)); }
	;
empty	:
	;
%%
