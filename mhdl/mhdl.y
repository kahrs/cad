%{

#include <stdio.h>
#include "mhdl.h"
#include "mhdl.debug"

void yyerror(char *);
int yylex(void);

extern Symbol *name_stack_ptr;

Cell *organelle;

%}

%union {
	Node	*node;
	Bucket	*bucket;
	Symbol	*symbol;
	Type	*type;
	long	long_value;
	char	char_value;
	double	float_value;
	char	*string_value;
}

%token L_AS L_ASSOCIATE L_ATTRIBUTE
%token L_CASE L_CHAR L_CLASS L_COERCION L_COLONS L_COLUMNS L_COMPONENT
%token L_COMPONENTS L_CONFIGURATION L_CONNECT L_CONNECTOR L_CONNECTORS
%token L_CONNECTION L_CONSTRAINT L_CONVERSION
%token L_DEFAULT L_DEFINITION L_DEFINITIONS L_DERIVATIVE L_DIMENSION
%token L_DOTS L_DOUBLE
%token L_EACH L_ELSE L_END L_EQUATION L_EXCEPT
%token L_FLOAT L_FOR L_FROM L_FUNCTION
%token L_GENERATE L_GRAPHIC
%token L_IDENTIFIER L_IF L_IN L_INCLUDES L_INSTANCE L_INTEGER L_INTEGRAL L_INVERSE
%token L_LARROW L_LEQEQ L_LET L_LIBRARIES
%token L_MEMBER L_MODEL L_MULTIPLIER L_NAMES
%token L_OF L_OPERATOR
%token L_PACKAGE L_PRIMITIVE L_PROPERTY
%token L_RARROW L_REPORT L_ROW
%token L_SET L_SIGNAL L_STRING L_STRUCTURE L_SUBTYPE
%token L_TABLE L_THEN L_TITLE L_TYPE
%token L_UNIT L_USE L_VARIATIONS
%token L_WHERE L_WITH

%right L_RARROW
%left  '|'
%right L_IF L_LET
%right ':'
%right '^'
%right '.'
%right '~' '@'

%start start

%%

start		:	start package
		|	start model
		|	package
		|	model
		|	expr
		;
abs_prop_def	:	property_kind abs_prop_names ':' type_spec
				{ new_names($2.node, $1.long_value, $4.node);
				  $$.node = new_node(O_ABS_DEF, $2.node, $4.node);
				}
		;
abs_prop_names :	abs_prop_names ',' simple_name
				{ $$.node = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$.node -> symbol = define_node($3.node, ABS_PROP_NAME);
				  $$.node = new_node(O_PAIR, $$.node, $1.node);
				}
		|	simple_name
				{ $$.node = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$.node -> symbol = define_node($1.node, ABS_PROP_NAME);
				}
		;
alternative	:	pattern alt_rhs
				{ $$.node = new_node(O_ALT, $1.node, $2.node); }
		;
alternatives	:	alternatives alternative ';'
				{ $$.node = new_node(O_PAIR, $1.node, $2.node); }
		|	alternative ';'
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
alt_rhs		:	alt_rhs_guard where_clause
				{ $$.node = new_node(O_RHS, $1.node, $2.node); }
		|	alt_rhs_guard
				{ $$.node = new_node(O_RHS, $1.node, Nil(Node)); }
		;
alt_rhs_guard	:	L_RARROW expr
				{ $$.node = new_node(O_GUARD, $2.node, Nil(Node)); }
		|	guard_alts
				{ $$.node = $1.node; }
		;
associate_def	:	L_ASSOCIATE associate_defs
				{ $$.node = new_node(O_ASSOC, $2.node, Nil(Node)); }
		;
associate_defs	:	associate_defs ',' name
				{ $$.node = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$.node -> symbol = use_name($3.node);
				  $$.node = new_node(O_PAIR, $$.node, $1.node);
				}
		|	name
				{ $$.node = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$.node -> symbol = use_name($1.node);
				}
		;
		;
case_expr	:	L_CASE expr L_OF '{' alternatives '}'
				{ $$.node = new_node(O_CASE, $2.node, $5.node); }
		;
class_body	:	'{' class_defs '}'
				{ $$.node = $2.node; }
		|	empty
				{ $$.node = Nil(Node); }
		;
class_constraint :	instance_spec
				{ $$.node = $1.node; }
		;
class_constraints :	class_constraints ',' class_constraints
				{ $$.node = new_node(O_PAIR, $1.node, $2.node); }
		|	class_constraint
				{ $$.node = $1.node; }
		;
class_def	:	class_header class_types class_body where_context
				{ pop_name();
				  $1.symbol -> cell = new_class($1.symbol, $2.node, $3.node, $4.node);
				  $$.node = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$.node -> symbol = $1.symbol;
				}
		;
class_defs	:	function_defs
				{ $$ = $1; }
		;
class_header	:	L_CLASS simple_name
				{ $$.symbol = push_name(define_node($2.node, CLASS_NAME)); }
		;
class_types	:	type_spec
				{ $$ = $1; }
		;
column_header	:	L_COLUMNS string_exprs ';'
				{ $$ = $2; }
		;
column_names	:	L_NAMES ids ';'
				{ $$ = $2; }
		;
comp_alternatives :	comp_alternatives comp_alternative
				{ $$.node = new_node(O_PAIR, $1.node, $2.node); }
		|	comp_alternative
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
comp_alternative :	pattern L_RARROW struct_clause ';'
				{ $$.node = new_node(O_ALT, $1.node, $3.node); }
		;
comp_case_clause :	L_CASE expr L_OF '{' comp_alternatives L_ELSE struct_clause ';' '}' L_END simple_name
				{ check_name($11.node, N_STRUCTURE);
				  $$.node = new_node(O_CASE, $2.node, new_node(O_ELSE, $5.node, $7.node));
				}
		;
comp_clause	:	name
				{ check_name($1.node, N_STRUCTURE); $$ = $1; }
		|	comp_if_clause
				{ $$ = $1; }
		|	comp_case_clause
				{ $$ = $1; }
		;
comp_config	:	L_FOR simple_name L_USE comp_clause
				{ check_name($2.node, N_COMPONENT);
				  $$.node = new_node(O_CONFIG, $2.node, $4.node);
				}
		;
comp_configs	:	comp_configs comp_config ';'
				{ $$.node = new_node(O_PAIR, $1.node, $2.node); }
		|	comp_config ';'
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
comp_def	:	comp_def_head comp_name comp_include comp_def_opt
				{ pop_name();
				  organelle = new_structure($1.symbol, F_COMPONENT, $2.node, Nil(Node), $4.node);
				  $1.symbol -> cell = 
					($1.symbol -> cell)?
					merge_structs($1.symbol -> cell, organelle) :
				  	organelle;
				  $$.node = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$.node -> symbol = $1.symbol;
				}
		;
comp_def_head	:	simple_name L_COLONS
				{ $$.symbol = push_name(define_node($1.node, COMPONENT_NAME)); }
		;
comp_def_opt	:	L_DEFINITIONS struct_items L_END comp_def_tail
				{ $$.node = $2.node; }
		|	empty
				{ $$.node = Nil(Node); }
		;
comp_def_tail	:	simple_name
				{ $$.symbol = use_name($1.node); }
		|	empty
				{ $$.symbol = Nil(Symbol); }
		;
comp_defs	:	comp_defs comp_def ';'
				{ $$.node = new_node(O_PAIR, $1.node, $2.node); }
		|	comp_def ';'
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
comp_elseif_clause :	L_ELSE L_IF expr L_THEN struct_clause comp_elseif_clause
				{ $$.node = new_node(O_IF, $3.node, new_node(O_ELSE, $5.node, $6.node)); }
		|	empty
				{ $$.node = Nil(Node); }
		;
comp_if_clause	:	L_IF expr L_THEN struct_clause comp_elseif_clause L_ELSE struct_clause L_END simple_name
				{ $$.node = new_node(O_IF, $2.node, new_node(O_ELSE, $4.node, $7.node)); }
		;
comp_name	:	name
				{ $$.node = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$.node -> symbol = use_name($1.node);
				}
		|	empty
				{ $$.node = Nil(Node); }
		;
comp_include	:	inclusions
		|	empty
		;
components	:	L_COMPONENTS comp_defs L_END L_COMPONENTS ';'
				{ $$ = $2; }
		;
cond_expr	:	L_IF expr L_THEN expr L_ELSE expr
				{ $$.node = new_node(O_IF, $2.node, new_node(O_ELSE, $4.node, $6.node)); }
		;
config_body	:	struct_config ';'
				{ $$ = $1; }
		|	comp_configs
				{ $$ = $1; }
		;
config_def	:	L_CONFIGURATION simple_name config_body L_END config_def_tail
				{ $$.node = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$.node -> symbol = define_node($2.node, CONFIG_NAME);
				  cmp_name($$.node -> symbol, $5.symbol);
				  new_config($2.node -> symbol, $3.node);
				}
		;
config_def_tail	:	simple_name
				{ $$.symbol = use_name($1.node); }
		|	empty
				{ $$.symbol = Nil(Symbol); }
		;
connections	:	label L_CONNECT conn_specs
				{ $$.node = new_label($1.symbol, new_node(O_CONNECT, $3.node, Nil(Node))); }
		|	L_CONNECT conn_specs
				{ $$.node = new_node(O_CONNECT, $2.node, Nil(Node)); }
		;
conn_clause	:	L_CONNECTORS conn_opt_names ';'
				{ $$ = $2; }
		;
conn_opt_names	:	conn_names
				{ $$ = $1; }
		|	empty
				{ $$.node = Nil(Node); }
		;
conn_names	:	conn_names ',' simple_name
				{ $$.node = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$.node -> symbol = define_node($3.node, CONNECTOR_NAME);
				  $$.node = new_node(O_PAIR, $$.node, $1.node);
				}
		|	simple_name
				{ $$.node = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$.node -> symbol = define_node($1.node, CONNECTOR_NAME);
				}
		;
conn_specs	:	conn_specs ',' conn_specs
				{ $$.node = new_node(O_PAIR, $1.node, $3.node); }
		|	conn_spec
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
conn_spec	:	name
				{ check_name($1.node, N_CONNECTOR|N_CONNECT_LIST); $$ = $1; }
		;
constraint_def	:	L_CONSTRAINT simple_name ':' expr constraint_report
				{ $$.node = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$.node -> symbol = define_node($2.node, CONSTRAINT_NAME);
				  new_constraint($2.node -> symbol, $4.node, $5.node);
				}
		;
constraint_report :	L_REPORT expr
				{ $$.node = $2.node; }
		|	empty
				{ $$.node = Nil(Node); }
		;
constructed_type :	constructors
				{ $$ = $1; }
		|	constructors L_WITH '{' construct_defs '}'
				{ $$.node = new_node(O_WITH, $1.node, $3.node); }
		;
construct_defs	:	construct_defs value_def ';'
				{ $$.node = new_node(O_PAIR, $1.node, $2.node); }
		|	value_def ';'
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
constructors 	:	constructors '|' type_constructor
				{ $$.node = new_node(O_PAIR, $1.node, $3.node); }
		|	type_constructor
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
context		:	class_constraint
				{ $$ = $1; }
		|	'{' class_constraints '}'
				{ $$ = $2; }
		;
conversion_spec	:	expr
				{ $$.node = $1.node; }
		|	expr L_INVERSE expr
				{ $$.node = new_node(O_INVERSE, $1.node, $3.node); }
		;
deferred_type_def :	L_TYPE simple_name where_context
				{ $$.node = new_node(O_TYPE, $2.node,
						new_node(O_PAIR, Nil(Node), $3.node));
				}
		;
def_designator	:	L_COMPONENT
				{ $$.long_value = F_COMPONENT; }
		|	L_CONNECTOR
				{ $$.long_value = F_CONNECTOR; }
		|	L_CONSTRAINT
				{ $$.long_value = F_CONSTRAINT; }
		|	L_DEFINITION
				{ $$.long_value = F_DEFINITION; }
		|	L_DIMENSION
				{ $$.long_value = F_DIMENSION; }
		|	L_EQUATION
				{ $$.long_value = F_EQUATION; }
		|	L_FUNCTION
				{ $$.long_value = F_FUNCTION; }
		|	L_MODEL
				{ $$.long_value = F_MODEL; }
		|	L_PROPERTY type_spec /***/
				{ $$.long_value = F_PROPERTY; }
		|	L_STRUCTURE
				{ $$.long_value = F_STRUCTURE; }
		|	L_TYPE
				{ $$.long_value = F_TYPE; }
		|	L_UNIT
				{ $$.long_value = F_UNIT; }
		;
derivative	:	L_DERIVATIVE '(' L_IDENTIFIER ')' '(' expr ')'
				{ $$.node = new_node(O_DERIV, $3.node, $6.node); }
		;
designation	:	'\'' designation_indicators '\''
				{ $$.node = new_node(O_DESIGNATOR, $2.node, Nil(Node)); }
		;
designation_indicators : indicators
				{ $$.node = $1.node; }
		|	indicators '/' indicators
				{ $$.node = new_node(O_DIVIDE, $1.node, $3.node); }
		|	'(' designation_indicators ')'
				{ $$.node = $2.node; }
		;
dim_def		:	L_DIMENSION L_IDENTIFIER dim_body unit_variations
				{ new_unit(define_unit($2.bucket), $3.node, $4.node);
				  declare_variations($4.node, $2.bucket);
				}
		;
dim_body	:	'=' designation
				{ $$.node = $2.node; }
		|	empty
				{ $$.node = Nil(Node); }
		;
indicators	:	indicator_list
				{ $$.node = $1.node; }
		|	'(' indicator_list ')'
				{ $$.node = $2.node; }
		;
indicator_list	:	indicator
				{ $$.node = $1.node; }
		|	indicator_list '*' indicator
				{ $$.node = new_node(O_MULTIPLY, $1.node, $3.node); }
		;
indicator	:	name '^' indicator_exp
				{ check_unit($1.node);
				  $$.node = new_node(O_EXP, $1.node, $3.node);
				}
		|	name
				{ check_unit($1.node); $$.node = $1.node; }
		|	'(' indicator ')'
				{ $$.node = $2.node; }
		;
indicator_exp	:	op L_INTEGER indicator_post
				{ $$.node = new_node(O_PREOP, $1.node, $2.node); }
		|	L_INTEGER indicator_post
				{ $$.node = new_node(O_SCALE, $1.node, $2.node); }
		|	'(' indicator_exp ')'
				{ $$.node = $2.node; }
		;
indicator_post	:	L_OPERATOR L_INTEGER
				{ $$.node = new_node(O_POSTOP, $1.node, $2.node); }
		|	empty
				{ $$.node = Nil(Node); }
		;
eq_designation	:	'=' designation
				{ $$.node = $2.node; }
		|	empty
				{ $$.node = Nil(Node); }
		;
equation_def	:	label expr
				{ $$.node = new_label($1.symbol, $2.node); }
		|	expr
				{ $$ = $1; }
		;
exposure_clause	:	exposures L_FROM name
				{ check_name($3.node, N_MODEL|N_PACKAGE); }
		;
exposure_item	:	name
				{ open_name(use_name($1.node)); }
		|	name L_AS simple_name
				{ alias_name(use_name($1.node), use_name($3.node)); }
		;
exposures	:	exposures ',' exposure_item
		|	exposure_item
		;
exprs		:	exprs ',' expr
				{ $$.node = new_node(O_PAIR, $1.node, $3.node); }
		|	expr ',' expr
				{ $$.node = new_node(O_PAIR, $1.node, $3.node); }
		;
expr		:	prefix_expr
				{ $$ = $1; }
		|	prefix_expr op expr
				{ $$.node = new_node(O_APPLY, $2.node, new_node(O_PAIR, $1.node, $3.node)); }
		;
for_generate_header :	L_FOR L_EACH generate_obj_kind simple_name for_tail
				{ /***check_name($4.node, N_GENERATE);***/
				  use_name($4.node);
				  $$.node = new_node(O_INT, Nil(Node), Nil(Node));
				  $$.node -> u.iconstant = $3.long_value;
				  $$.node = new_node(O_FOREACH, $$.node,
					new_node(O_PAIR, $4.node, $5.node));
				}
		;
for_tail	:	L_IN generates
				{ $$ = $2; }
		|	empty
				{ $$.node = Nil(Node); }
		;
function_apply	:	simple_pattern_expr '(' function_args ')'
				{ $$.node = new_node(O_APPLY, $1.node, $3.node); }
		;
function_args	:	expr
				{ $$ = $1; }
		|	exprs
				{ $$ = $1; }
		;
function_def	:	name_def
				{ $$ = $1; }
		|	value_def
				{ $$ = $1; }
		;
function_defs	:	function_defs function_def ';'
				{ $$.node = new_node(O_SEMI, $1.node, $2.node); }
		|	function_def ';'
				{ $$.node = $1.node; }
		;
generates	:	expr
				{ $$ = $1; }
		;
generate_body	:	generate_body generate_item ';'
				{ $$.node = new_node(O_PAIR, $1.node, $2.node); }
		|	generate_item ';'
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
generate_def	:	generate_header L_GENERATE generate_body L_END L_GENERATE
				{ new_generate($1.node, $3.node);
				  $$.node = new_node(O_GENERATE, $1.node, $3.node);
				}
		;
generate_header	:	if_generate_header
				{ $$ = $1; }
		|	for_generate_header
				{ $$ = $1; }
		|	table_generate_header
				{ $$ = $1; }
		;
generate_item	:	struct_item
				{ $$ = $1; }
		|	struct_def
				{ $$ = $1; }
		;
generate_obj_kind :	L_COMPONENT
				{ $$.long_value = $1.bucket -> token; }
		|	L_CONNECTION L_SET
				{ $$.long_value = $1.bucket -> token; }
		|	L_CONNECTOR
				{ $$.long_value = $1.bucket -> token; }
		|	L_MEMBER
				{ $$.long_value = $1.bucket -> token; }
		|	L_STRUCTURE
				{ $$.long_value = $1.bucket -> token; }
		;
guards		:	guards guard
				{ $$.node = new_node(O_PAIR, $1.node, $2.node); }
		|	guard
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
guard		:	'|' expr '=' expr
				{ $$.node = new_node(O_GUARD, $2.node, $4.node); }
		;
guard_alts	:	guard_alts guard_alt
				{ $$.node = new_node(O_PAIR, $1.node, $2.node); }
		|	guard_alt
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
guard_alt	:	'|' expr L_RARROW expr
				{ $$.node = new_node(O_ALT, $2.node, $4.node); }
		;
hiding_clause	:	name L_EXCEPT hidings
				{ check_name($1.node, N_PACKAGE|N_MODEL);
				  open_names($1.node);
				  close_name_list($3.node);
				}
		;
hidings		:	hidings ',' hidings
				{ $$.node = new_node(O_PAIR, $1.node, $3.node); }
		|	simple_name
				{ use_name($1.node);
				  $$.node = $1.node;
				}
ids		:	L_IDENTIFIER '|' ids
				{ $$.node = new_node(O_ID, Nil(Node), Nil(Node));
				  $$.node -> bucket = $1.bucket;
				  $$.node = new_node(O_PAIR, $$.node, $3.node);
				}
		|	L_IDENTIFIER
				{ $$.node = new_node(O_ID, Nil(Node), Nil(Node));
				  $$.node -> bucket = $1.bucket;
				  $$.node = new_node(O_PAIR, $$.node, Nil(Node));
				}
		;
if_generate_header :	L_IF expr
				{ $$.node = new_node(O_IF, Nil(Node), Nil(Node)); }
		;
inclusions	:	inclusions L_INCLUDES visibility_item ';' 
		|	L_INCLUDES visibility_item ';'
		;
instance_header	:	L_INSTANCE simple_name
				{ $$.symbol = push_name(use_name($2.node)); }
		|	L_INSTANCE op
				{ $$.symbol = push_name(use_name($2.node)); }
		;
instance_spec	:	type_specs
				{ $$ = $1; }
		|	empty
				{ $$.node = Nil(Node); }
		;
instance_body	:	'{' value_defs '}'
				{ $$ = $2; }
		|	empty
				{ $$.node = Nil(Node); }
		;
instance_def	:	instance_header instance_spec instance_body where_context
				{
				  $1.symbol -> cell = new_instance($1.symbol, $2.node, $3.node, $4.node);
				  $$.node = new_node(O_INSTANCE, Nil(Node), Nil(Node));
				  $$.node -> symbol = $1.symbol;
				}
		;
integral	:	L_INTEGRAL '(' L_IDENTIFIER ')' integral_expr '(' expr ')'
				{ $$.node = new_node(O_INTEGRAL, $3.node, new_node(O_PAIR, $5.node, $7.node)); }
		;
integral_expr	:	'(' expr ',' expr ')'
				{ $$.node = new_node(O_PAIR, $2.node, $4.node); }
		|	empty
				{ $$.node = Nil(Node); }
		;
label		:	L_IDENTIFIER ':'
				{ $$.symbol = define_name($1.bucket, LABEL_NAME); }
		;
lambda_abstract	:	'\\' '(' patterns ')' L_RARROW expr
				{ $$.node = new_node(O_LAMBDA, $3.node, $6.node); }
		;
let_expr	:	L_LET nested_defs L_IN expr
				{ $$.node = new_node(O_LET, $2.node, $4.node); }
		;
libraries	:	L_LIBRARIES library_names ';'
		;
library_names	:	library_names ',' simple_name
				{ load_library($3.node); }
		|	simple_name
				{ load_library($1.node); }
		;
list		:	empty
				{ $$.node = Nil(Node); }
		|	expr
				{ $$.node = $1.node; }
		|	exprs
				{ $$.node = $1.node; }
		|	expr '|' qualifiers
				{ $$.node = new_node(O_QUALIFIED, $1.node, $3.node); }
		|	expr L_DOTS expr
				{ $$.node = new_node(O_DOTS, $1.node, $3.node); }
		|	expr ',' expr L_DOTS
				{ $$.node = new_node(O_DOTS, new_node(O_PAIR, $1.node, $3.node), $3.node); }
		|	expr L_DOTS
				{ $$.node = new_node(O_DOTS, $1.node, Nil(Node)); }
		;
literal		:	L_INTEGER
				{ $$.node = new_node(O_INT, Nil(Node), Nil(Node));
				  $$.node -> u.iconstant = $1.long_value;
				}
		|	L_FLOAT
				{ $$.node = new_node(O_FLOAT, Nil(Node), Nil(Node));
				  $$.node -> u.fconstant = $1.float_value;
				}
		|	L_CHAR
				{ $$.node = new_node(O_CHAR, Nil(Node), Nil(Node));
				  $$.node -> u.cconstant = $1.char_value;
				}
		|	L_STRING
				{ $$.node = new_node(O_STRING, Nil(Node), Nil(Node));
				  $$.node -> u.string = $1.string_value;
				}
		;
model		:	model_head model_library model_inclusions model_body model_tail ';'
				{ cmp_name($1.symbol, $5.symbol);
				  analyze($4.node);
				  type_check($4.node, 0);
				  if (debug['t']) print_tree($4.node);
				}
		;
model_head	:	L_MODEL simple_name
				{ $$.symbol = push_name(define_node($2.node, MODEL_NAME)); }
		;
model_tail	:	L_END simple_name
				{ print_undefs(name_stack_ptr); pop_name(); $$.symbol = use_name($2.node); }
		|	empty
				{ print_undefs(name_stack_ptr); pop_name(); $$.symbol = Nil(Symbol); }
		;
model_inclusions :	inclusions
		|	empty
		;
model_library	:	libraries
		|	empty
		;
model_body	:	model_items
				{ $$ = $1; }
		|	empty
				{ $$.node = Nil(Node); }
		;
model_items	:	model_items model_item ';'
				{ $$.node = new_node(O_PAIR, $1.node, $2.node); }
		|	model_item ';'
				{ $$ = $1; }
		;
model_item	:	class_def
				{ $$ = $1; }
		|	dim_def
				{ $$.node = Nil(Node); }
		|	instance_def
				{ $$ = $1; }
		|	multiplier_spec
				{ $$.node = Nil(Node); }
		|	struct_item
				{ $$ = $1; }
		|	struct_def
				{ $$ = $1; }
		|	type_def
				{ $$ = $1; }
		|	unit_def
				{ $$.node = Nil(Node); }
		;
multiplier_spec	:	L_MULTIPLIER L_IDENTIFIER '=' multiplier_tail unit_variations
				{ new_multiplier(define_unit($2.bucket), $4.float_value);
				  declare_variations($5.node, $2.bucket);
				}
		;
multiplier_tail :	L_INTEGER
				{ $$.float_value = (float) $1.long_value; }
		|	L_FLOAT
				{ $$.float_value = $1.float_value; }
		;
name		:	simple_name
				{ $$ = $1; }
		|	selected_name
				{ $$ = $1; }
		;
name_def	:	L_COERCION named_values L_COLONS type_spec where_context
				{ $$.node = new_node(O_COERCE, $2.node,
						new_node(O_PAIR, $4.node, $5.node));
				}
		|	named_values L_COLONS type_spec where_context
				{ $$.node = new_node(O_TYPED, $1.node,
						new_node(O_PAIR, $3.node, $4.node));
				}
		;
named_values	:	names
				{ $$ = $1; }
		;
names		:	names ',' name
				{ define_node($3.node, NAMED_VALUE_NAME);
				  $$.node = new_node(O_PAIR, $1.node, $3.node); }
		|	name
				{ define_node($1.node, NAMED_VALUE_NAME);
				  $$.node = $1.node;
				}
		;
nested_def	:	name_def
				{ $$ = $1; }
		|	value_def
				{ $$ = $1; }
		;
nested_defs	:	'{' nested_def_list '}'
				{ $$.node = $2.node; }
		;
nested_def_list	:	nested_def ';'
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		|	nested_def_list nested_def ';'
				{ $$.node = new_node(O_PAIR, $1.node, $2.node); }
		;
null		:	'(' ')'
				{ $$.node = new_node(O_NULL, Nil(Node), Nil(Node)); }
		;
op		:	operator
				{ $$.node = $1.node; }
		|	'/'
				{ $$.node = new_node(O_OP, Nil(Node), Nil(Node));
				  $$.node -> bucket = $1.bucket;
				  $$.node -> code = $1.bucket -> token;
				}
		|	'*'
				{ $$.node = new_node(O_OP, Nil(Node), Nil(Node));
				  $$.node -> bucket = $1.bucket;
				  $$.node -> code = $1.bucket -> token;
				}
		|	'^'
				{ $$.node = new_node(O_OP, Nil(Node), Nil(Node));
				  $$.node -> bucket = $1.bucket;
				  $$.node -> code = $1.bucket -> token;
				}
		|	'-'
				{ $$.node = new_node(O_MINUS, Nil(Node), Nil(Node));
				  $$.node -> bucket = $1.bucket;
				  $$.node -> code = $1.bucket -> token;
				}
		;
operator	:	L_OPERATOR
				{ $$.node = new_node(O_OP, Nil(Node), Nil(Node));
				  $$.node -> bucket = $1.bucket;
				}
		|	L_DOUBLE name L_DOUBLE
				{ $$ = $2; }
		;
operator_apply	:	op expr
				{ $$.node = new_node(O_APPLY, $1.node, $2.node); }
		;
package		:	package_head package_library package_inclusion package_models package_tail ';'
				{ cmp_name($1.symbol, $5.symbol);
				  analyze($4.node);
				  type_check($4.node, 0);
				  if (debug['t']) print_tree($4.node);
				}
		;
package_head	:	L_PACKAGE simple_name
				{ $$.symbol = push_name(define_node($2.node, PACKAGE_NAME)); }
		;
package_tail	:	L_END simple_name
				{ print_undefs(name_stack_ptr); pop_name(); $$.symbol = use_name($2.node); }
		|	empty
				{ print_undefs(name_stack_ptr); pop_name(); $$.symbol = Nil(Symbol); }
		;
package_inclusion :	inclusions
		|	empty
		;
package_library	:	libraries
		|	empty
		;
package_models	:	model_items
				{ $$.node = $1.node; }
		|	empty
				{ $$.node = Nil(Node); }
		;
pattern		:	expr
				{ $$.node = new_node(O_PATTERN, $1.node, Nil(Node)); }
		;
patterns	:	patterns ',' pattern
				{ $$.node = new_node(O_PAIR, $1.node, $3.node); }
		|	pattern
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
physical_value	:	prefix_expr designation
		;
prefix_expr	:	case_expr
				{ $$.node = $1.node; }
		|	cond_expr
				{ $$.node = $1.node; }
		|	derivative
				{ $$.node = $1.node; }
		|	function_apply
				{ $$.node = $1.node; }
		|	integral
				{ $$.node = $1.node; }
		|	lambda_abstract
				{ $$.node = $1.node; }
		|	let_expr
				{ $$.node = $1.node; }
		|	operator_apply
				{ $$.node = $1.node; }
		|	physical_value
				{ $$.node = $1.node; }
		|	primitive_value
				{ $$.node = $1.node; }
		|	simple_pattern_expr
				{ $$.node = $1.node; }
		|	struct_func_create
				{ $$.node = $1.node; }
		|	typed_expr
				{ $$.node = $1.node; }
		;
primitive_value	:	L_PRIMITIVE expr
				{ $$.node = new_node(O_PRIMITIVE, $2.node, Nil(Node)); }
		;
property_kind	:	L_ATTRIBUTE
				{ $$.long_value = F_ATTRIBUTE; }
		|	L_SIGNAL
				{ $$.long_value = F_SIGNAL; }
		;
property_names	:	'(' exprs ')'
				{ $$.node = $2.node; }
		|	'(' expr ')'
				{ $$.node = $2.node; }
		;
qualifier	:	pattern L_LARROW expr
				{ $$.node = new_node(O_QUALIFIER, $1.node, $3.node); }
		|	expr
				{ $$.node = $1.node; }
		;
qualifiers	:	qualifiers ',' qualifier
				{ $$.node = new_node(O_PAIR, $1.node, $3.node); }
		|	qualifier
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
rhs		:	rhs_guard where_clause
				{ $$.node = new_node(O_RHS, $1.node, $2.node); }
		|	rhs_guard
				{ $$.node = new_node(O_RHS, $1.node, Nil(Node)); }
		;
rhs_guard	:	'=' expr
				{ $$.node = $2.node; }
		|	guards
				{ $$.node = $1.node; }
		;
selected_name	:	selected_names '.' simple_name
				{ $$.node = new_node(O_DOT, $1.node, $3.node); }
		;
selected_names	:	selected_names '.' L_IDENTIFIER
				{ $$.node = new_node(O_ID, Nil(Node), Nil(Node));
				  $$.node -> bucket = $3.bucket;
				  $$.node = new_node(O_DOT, $1.node, $$.node);
				}
		|	L_IDENTIFIER
				{ $$.node = new_node(O_ID, Nil(Node), Nil(Node));
				  $$.node -> bucket = $1.bucket;
				}
		;
simple_name	:	L_IDENTIFIER
				{ $$.node = new_node(O_ID, Nil(Node), Nil(Node));
				  $$.node -> bucket = $1.bucket;
				}
		|	'(' op ')'
				{ $$.node = $2.node; }
		;
simple_pattern_expr :	name
				{ $$.node = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$.node -> symbol = use_name($1.node);
				}
		|	variable '@' simple_pattern_expr
				{ $$.node = new_node(O_AT, $1.node, $3.node); }
		|	'~' simple_pattern_expr
				{ $$.node = new_node(O_TILDE, $2.node, Nil(Node)); }
		|	'_'
				{ $$.node = new_node(O_WILDCARD, Nil(Node), Nil(Node)); }
		|	literal
				{ $$.node = $1.node; }
		|	null
				{ $$.node = $1.node; }
		|	'(' expr ')'
				{ $$.node = $2.node; }
		|	'(' exprs ')'
				{ $$.node = $2.node; }
		|	'(' pattern patterns ')'
				{ $$.node = new_node(O_PAIR, $2.node, $3.node); }
		|	'[' list ']'
				{ $$.node = new_node(O_LIST, $2.node, Nil(Node)); }
		;
specified_type_def :	L_TYPE type_header '=' type_specifier where_context
				{ $$.node = new_node(O_TYPE, $2.node,
						new_node(O_PAIR, $4.node, $5.node));
				}
		;
string_exprs	:	expr '|' string_exprs
				{ $$.node = new_node(O_PAIR, $1.node, $3.node); }
		|	expr
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
struct_clause	:	name
				{ use_name($1.node); }
		|	name struct_config
				{ use_name($1.node); }
		;
struct_config	:	L_FOR name struct_config_body L_END struct_config_tail
				{ full_cmp_name($2.symbol, $5.symbol);
				  use_name($2.node);
				  $$.node = new_node(O_FOR, $2.node, $3.node);
				}
		;
struct_config_tail :	name
				{ $$.bucket = $1.node -> bucket; }
		|	empty
				{ $$.bucket = Nil(Bucket); }
		;
struct_config_body :	comp_configs
				{ $$ = $1; }
		|	L_USE name
				{ check_name($2.node, N_CONFIG);
				  use_name($2.node);
				  $$ = $2;
				}
		;
struct_def	:	struct_def_head struct_inclusion struct_conns struct_comps struct_defs L_END struct_def_tail
				{ pop_name();
				  cmp_name($1.symbol, $7.symbol);
				  $1.symbol -> cell = new_structure($1.symbol, F_STRUCTURE, $4.node, $3.node,$5.node);
				  $$.node = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$.node -> symbol = $1.symbol;
				}
		;
struct_def_head	:	L_STRUCTURE simple_name
				{ $$.symbol = push_name(define_node($2.node, STRUCTURE_NAME)); }
		;
struct_def_tail	:	simple_name
				{ $$.symbol = use_name($1.node); }
		|	empty
				{ $$.symbol = Nil(Symbol); }
		;
struct_inclusion :	inclusions
		|	empty
		;
struct_defs	:	struct_items
				{ $$ = $1; }
		|	empty
				{ $$.node = Nil(Node); }
		;
struct_comps	:	components
				{ $$ = $1; }
		|	empty
				{ $$.node = Nil(Node); }
struct_conns	:	conn_clause
				{ $$ = $1; }
		|	empty
				{ $$.node = Nil(Node); }
		;
struct_func_create :	property_names L_LEQEQ name property_names
				{ check_name($3.node, N_STRUCTURE); }
		;
struct_items	:	struct_items struct_item ';'
				{ $$.node = new_node(O_PAIR, $1.node, $2.node); }
		|	struct_item ';'
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
struct_item	:	abs_prop_def
				{ $$ = $1; }
		|	associate_def
				{ $$ = $1; }
		|	config_def
				{ $$ = $1; }
		|	connections
				{ $$ = $1; }
		|	constraint_def
				{ $$ = $1; }
		|	equation_def
				{ $$ = $1; }
		|	generate_def
				{ $$ = $1; }
		|	name_def
				{ $$ = $1; }
		|	table_def
				{ $$ = $1; }
		|	value_def
				{ $$ = $1; }
		;
table_def	:	table_head table_header table_column column_names table_data table_tail
				{ cmp_name($1.symbol, $6.symbol);
				  $1.symbol -> cell = new_table($1.symbol, $2.node, $3.node, $4.node, $5.node);
				  $$.node = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$.node -> symbol = $1.symbol;
				}
		;
table_head	:	L_TABLE simple_name 
				{ $$.symbol = define_node($2.node, TABLE_NAME); }
		;
table_tail	:	L_END simple_name
				{ $$.symbol = use_name($2.node); }
		|	empty
				{ $$.symbol = Nil(Symbol); }
		;
table_header	:	L_TITLE expr ';'
				{ $$ = $2; }
		|	empty
				{ $$.node = Nil(Node); }
		;
table_column	:	column_header
				{ $$ = $1; }
		|	empty
				{ $$.node = Nil(Node); }
		;
table_data	:	'{' '{' table_data_rows '}' '}'
				{ $$ = $3; }
		|	'{' '{' '}' '}'
				{ $$.node = Nil(Node); }
		;
table_data_rows	:	table_data_rows table_row
				{ $$.node = new_node(O_PAIR, $1.node, $2.node); }
		|	table_row
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
table_entries	:	table_entries '|' table_entry
				{ $$.node = new_node(O_PAIR, $1.node, $3.node); }
		|	table_entry
				{ $$ = $1; }
		;
table_entry	:	expr
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		|	table_entry expr
				{ $$.node = new_node(O_PAIR, $1.node, $2.node); }
		;
table_generate_header :	L_FOR L_EACH L_ROW L_IN L_TABLE name
				{ check_name($6.node, N_TABLE);
				  $$.node = $6.node;
				}
		|	L_FOR L_EACH L_ROW simple_name L_IN L_TABLE name
				{ check_name($7.node, N_TABLE);
				  $$.node = $7.node;
				}
		;
table_row	:	table_entries ';'
				{ $$ = $1; }
		;
types		:	types ',' type_item
				{ $$.node = new_node(O_PAIR, $1.node, $3.node); }
		|	type_item
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
type_component	:	name '(' types ')'
				{ $$.node = new_node(O_PREDICATE, $1.node, $3.node);
				  $$.node -> symbol = use_name($1.node);
				}
		|	type_term
				{ $$ = $1; }
		|	def_designator
				{ $$.node = new_node(O_INT, Nil(Node), Nil(Node));
				  $$.node -> u.iconstant = $1.long_value;
				}
		;
type_constructor :	type_component op type_component
		|	type_spec
				{ $$ = $1; }
		;
type_def	:	deferred_type_def
				{ $$ = $1; }
		|	specified_type_def
				{ $$ = $1; }
		;
type_header	:	type_spec
				{ $$ = $1; }
		;
type_item	:	simple_name L_COLONS type_term
				{ fatal(" type_item "); }
		|	type_spec
				{ $$ = $1; }
		;
type_specs	:	type_specs ',' type_specs
				{ $$.node = new_node(O_PAIR, $1.node, $3.node); }
		|	type_item
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
type_spec	: 	type_spec L_RARROW type_component
				{ $$.node = new_node(O_RARROW, $1.node, $3.node); }
		|	type_component
				{ $$ = $1; }
		;
type_specifier	:	constructed_type
				{ $$ = $1; }
		;
type_term	:	name
				{ $$.node = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$.node -> symbol = use_name($1.node);
				}
		|	'(' ')'
				{ $$.node = Nil(Node); }
		|	'(' types ')'
				{ $$.node = $2.node; }
		|	'[' type_spec ']'
				{ $$.node = new_node(O_LIST, $2.node, Nil(Node)); }
		;
typed_expr	:	'(' expr L_COLONS type_spec where_context ')'
				{ $$.node = new_node(O_TYPED, $2.node,
						new_node(O_PAIR, $4.node, $5.node));
				}
		;
unit_convert	:	L_CONVERSION conversion_spec name
				{ $$.node = new_node(O_PAIR, $2.node, $3.node); }
		|	empty
				{ $$.node = Nil(Node); }
		;
unit_def	:	L_UNIT L_IDENTIFIER L_OF name eq_designation unit_convert unit_variations
				{ new_unit(define_unit($2.bucket), $5.node, $6.node);
				  declare_variations($7.node, $2.bucket);
				}
		;
unit_variations	:	variations
				{ $$ = $1; }
		|	empty
				{ $$.node = Nil(Node); }
		;
value_def	:	value_def_target rhs
				{ $$.node = new_node(O_VALUE_DEF, $1.node, $2.node); }
		|	label L_DEFAULT value_def_target rhs
				{ $$.node = new_label($1.symbol, new_node(O_DEFAULT, $2.node, $3.node)); }
		|	L_DEFAULT value_def_target rhs
				{ $$.node = new_node(O_DEFAULT, $2.node, $3.node); }
		;
value_defs	:	value_defs value_def ';'
				{ $$.node = new_node(O_PAIR, $1.node, $2.node); }
		|	value_def ';'
				{ $$.node = new_node(O_PAIR, $1.node, Nil(Node)); }
		;
value_def_target :	expr
				{ $$.node = $1.node; }
		;
variable	:	name
				{ $$.node = $1.node; }
		;
variations	:	L_VARIATIONS variation_ids
				{ $$.node = $2.node; }
		;
variation_ids	:	variation_ids ',' variation_ids
				{ $$.node = new_node(O_PAIR, $1.node, $3.node); }
		|	L_IDENTIFIER
				{ $$.node = new_node(O_ID, Nil(Node), Nil(Node));
				  $$.node -> bucket = $1.bucket;
				}
		;
visibility_item	:	exposure_clause
		|	hiding_clause
		|	name
				{ check_name($1.node, N_MODEL|N_PACKAGE);
				  open_names($1.node);
				}
		;
where_clause	:	L_WHERE '{' function_defs '}'
				{ $$.node = new_node(O_WHERE, $3.node, Nil(Node)); }
		;
where_context	:	L_WHERE context
				{ $$.node = new_node(O_CONTEXT, $2.node, Nil(Node)); }
		|	empty
				{ $$.node = Nil(Node); }
		;
empty		:
		;
