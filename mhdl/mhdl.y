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

%type<node> start abs_prop_def abs_prop_names  alternative alternatives alt_rhs alt_rhs_guard associate_def associate_defs
%type<node> case_expr class_body class_constraint  class_constraints  class_def class_defs class_types column_header column_names
%type<node> comp_alternatives  comp_alternative  comp_case_clause  comp_clause comp_config comp_configs comp_def comp_def_opt comp_defs comp_elseif_clause comp_if_clause comp_name comp_include components
%type<node> cond_expr config_body connections config_def conn_clause conn_opt_names conn_names conn_specs conn_spec
%type<node> constraint_def constraint_report  constructed_type  construct_defs constructors  context conversion_spec
%type<node> deferred_type_def derivative designation designation_indicators  dim_def dim_body
%type<node> indicators indicator_list indicator indicator_exp indicator_post
%type<node> eq_designation equation_def exposure_clause exposure_item exposures exprs expr
%type<node> for_generate_header  for_tail function_apply function_args function_def function_defs
%type<node> generates generate_body generate_def generate_header generate_item  guards guard guard_alts guard_alt hiding_clause
%type<node> hidings ids if_generate_header  inclusions instance_spec instance_body instance_def integral integral_expr
%type<node> lambda_abstract let_expr libraries library_names list literal model model_inclusions  model_library model_body model_items model_item
%type<node> multiplier_spec name name_def named_values names nested_def nested_defs nested_def_list
%type<node> null op operator operator_apply package package_inclusion  package_library package_models pattern patterns
%type<node> physical_value prefix_expr primitive_value property_names qualifier qualifiers rhs rhs_guard
%type<node> selected_name selected_names
%type<node> simple_name struct_config_tail simple_pattern_expr  specified_type_def  string_exprs struct_clause struct_config  struct_config_body  struct_def struct_inclusion  struct_defs struct_comps struct_conns struct_func_create  struct_items struct_item
%type<node> table_def table_header table_column table_data table_data_rows table_entries table_entry table_generate_header  table_row types
%type<node> type_component type_constructor  type_def type_header type_item type_specs type_spec type_specifier type_term typed_expr
%type<node> unit_convert unit_def unit_variations value_def value_defs value_def_target  variable variations variation_ids visibility_item where_clause where_context
%type<node> empty

%type<bucket> L_IDENTIFIER
%type<long_value> L_INTEGER property_kind def_designator
%type<string_value>  L_STRING
%type<bucket> L_COMPONENT L_CONNECTION L_SET L_CONNECTOR L_MEMBER L_STRUCTURE '/' '*' '^' '-' generate_obj_kind L_OPERATOR 
%type<float_value> L_FLOAT multiplier_tail
%type<char_value> L_CHAR
%type<symbol> class_header comp_def_head comp_def_tail config_def_tail label instance_header model_head model_tail package_head package_tail struct_def_head struct_def_tail table_head table_tail
 
%start start

%%

start		:	start package
		|	start model
		|	package
		|	model
		|	expr
		;
abs_prop_def	:	property_kind abs_prop_names ':' type_spec
				{ new_names($2, $1, $4);
				  $$ = new_node(O_ABS_DEF, $2, $4);
				}
		;
abs_prop_names :	abs_prop_names ',' simple_name
				{ $$ = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$ -> symbol = define_node($3, ABS_PROP_NAME);
				  $$ = new_node(O_PAIR, $$, $1);
				}
		|	simple_name
				{ $$ = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$ -> symbol = define_node($1, ABS_PROP_NAME);
				}
		;
alternative	:	pattern alt_rhs
				{ $$ = new_node(O_ALT, $1, $2); }
		;
alternatives	:	alternatives alternative ';'
				{ $$ = new_node(O_PAIR, $1, $2); }
		|	alternative ';'
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		;
alt_rhs		:	alt_rhs_guard where_clause
				{ $$ = new_node(O_RHS, $1, $2); }
		|	alt_rhs_guard
				{ $$ = new_node(O_RHS, $1, Nil(Node)); }
		;
alt_rhs_guard	:	L_RARROW expr
				{ $$ = new_node(O_GUARD, $2, Nil(Node)); }
		|	guard_alts
				{ $$ = $1; }
		;
associate_def	:	L_ASSOCIATE associate_defs
				{ $$ = new_node(O_ASSOC, $2, Nil(Node)); }
		;
associate_defs	:	associate_defs ',' name
				{ $$ = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$ -> symbol = use_name($3);
				  $$ = new_node(O_PAIR, $$, $1);
				}
		|	name
				{ $$ = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$ -> symbol = use_name($1);
				}
		;
		;
case_expr	:	L_CASE expr L_OF '{' alternatives '}'
				{ $$ = new_node(O_CASE, $2, $5); }
		;
class_body	:	'{' class_defs '}'
				{ $$ = $2; }
		|	empty
				{ $$ = Nil(Node); }
		;
class_constraint :	instance_spec
				{ $$ = $1; }
		;
class_constraints :	class_constraints ',' class_constraints
				{ $$ = new_node(O_PAIR, $1, $3); }
		|	class_constraint
				{ $$ = $1; }
		;
class_def	:	class_header class_types class_body where_context
				{ pop_name();
				  $1 -> cell = new_class($1, $2, $3, $4);
				  $$ = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$ -> symbol = $1;
				}
		;
class_defs	:	function_defs
				{ $$ = $1; }
		;
class_header	:	L_CLASS simple_name
				{ $$ = push_name(define_node($2, CLASS_NAME)); }
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
				{ $$ = new_node(O_PAIR, $1, $2); }
		|	comp_alternative
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		;
comp_alternative :	pattern L_RARROW struct_clause ';'
				{ $$ = new_node(O_ALT, $1, $3); }
		;
comp_case_clause :	L_CASE expr L_OF '{' comp_alternatives L_ELSE struct_clause ';' '}' L_END simple_name
				{ check_name($11, N_STRUCTURE);
				  $$ = new_node(O_CASE, $2, new_node(O_ELSE, $5, $7));
				}
		;
comp_clause	:	name
				{ check_name($1, N_STRUCTURE); $$ = $1; }
		|	comp_if_clause
				{ $$ = $1; }
		|	comp_case_clause
				{ $$ = $1; }
		;
comp_config	:	L_FOR simple_name L_USE comp_clause
				{ check_name($2, N_COMPONENT);
				  $$ = new_node(O_CONFIG, $2, $4);
				}
		;
comp_configs	:	comp_configs comp_config ';'
				{ $$ = new_node(O_PAIR, $1, $2); }
		|	comp_config ';'
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		;
comp_def	:	comp_def_head comp_name comp_include comp_def_opt
				{ pop_name();
				  organelle = new_structure($1, F_COMPONENT, $2, Nil(Node), $4);
				  $1 -> cell = ($1 -> cell)? merge_structs($1 -> cell, organelle) : organelle;
				  $$ = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$ -> symbol = $1;
				}
		;
comp_def_head	:	simple_name L_COLONS
				{ $$ = push_name(define_node($1, COMPONENT_NAME)); }
		;
comp_def_opt	:	L_DEFINITIONS struct_items L_END comp_def_tail
				{ $$ = $2; }
		|	empty
				{ $$ = Nil(Node); }
		;
comp_def_tail	:	simple_name
				{ $$ = use_name($1); }
		|	empty
				{ $$ = Nil(Symbol); }
		;
comp_defs	:	comp_defs comp_def ';'
				{ $$ = new_node(O_PAIR, $1, $2); }
		|	comp_def ';'
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		;
comp_elseif_clause :	L_ELSE L_IF expr L_THEN struct_clause comp_elseif_clause
				{ $$ = new_node(O_IF, $3, new_node(O_ELSE, $5, $6)); }
		|	empty
				{ $$ = Nil(Node); }
		;
comp_if_clause	:	L_IF expr L_THEN struct_clause comp_elseif_clause L_ELSE struct_clause L_END simple_name
				{ $$ = new_node(O_IF, $2, new_node(O_ELSE, $4, $7)); }
		;
comp_name	:	name
				{ $$ = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$ -> symbol = use_name($1);
				}
		|	empty
				{ $$ = Nil(Node); }
		;
comp_include	:	inclusions
		|	empty
		;
components	:	L_COMPONENTS comp_defs L_END L_COMPONENTS ';'
				{ $$ = $2; }
		;
cond_expr	:	L_IF expr L_THEN expr L_ELSE expr
				{ $$ = new_node(O_IF, $2, new_node(O_ELSE, $4, $6)); }
		;
config_body	:	struct_config ';'
				{ $$ = $1; }
		|	comp_configs
				{ $$ = $1; }
		;
config_def	:	L_CONFIGURATION simple_name config_body L_END config_def_tail
				{ $$ = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$ -> symbol = define_node($2, CONFIG_NAME);
				  cmp_name($$ -> symbol, $5);
				  new_config($2 -> symbol, $3);
				}
		;
config_def_tail	:	simple_name
				{ $$ = use_name($1); }
		|	empty
				{ $$ = Nil(Symbol); }
		;
connections	:	label L_CONNECT conn_specs
				{ $$ = new_label($1, new_node(O_CONNECT, $3, Nil(Node))); }
		|	L_CONNECT conn_specs
				{ $$ = new_node(O_CONNECT, $2, Nil(Node)); }
		;
conn_clause	:	L_CONNECTORS conn_opt_names ';'
				{ $$ = $2; }
		;
conn_opt_names	:	conn_names
				{ $$ = $1; }
		|	empty
				{ $$ = Nil(Node); }
		;
conn_names	:	conn_names ',' simple_name
				{ $$ = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$ -> symbol = define_node($3, CONNECTOR_NAME);
				  $$ = new_node(O_PAIR, $$, $1);
				}
		|	simple_name
				{ $$ = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$ -> symbol = define_node($1, CONNECTOR_NAME);
				}
		;
conn_specs	:	conn_specs ',' conn_specs
				{ $$ = new_node(O_PAIR, $1, $3); }
		|	conn_spec
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		;
conn_spec	:	name
				{ check_name($1, N_CONNECTOR|N_CONNECT_LIST); $$ = $1; }
		;
constraint_def	:	L_CONSTRAINT simple_name ':' expr constraint_report
				{ $$ = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$ -> symbol = define_node($2, CONSTRAINT_NAME);
				  new_constraint($2 -> symbol, $4, $5);
				}
		;
constraint_report :	L_REPORT expr
				{ $$ = $2; }
		|	empty
				{ $$ = Nil(Node); }
		;
constructed_type :	constructors
				{ $$ = $1; }
		|	constructors L_WITH '{' construct_defs '}'
				{ $$ = new_node(O_WITH, $1, $4); }
		;
construct_defs	:	construct_defs value_def ';'
				{ $$ = new_node(O_PAIR, $1, $2); }
		|	value_def ';'
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		;
constructors 	:	constructors '|' type_constructor
				{ $$ = new_node(O_PAIR, $1, $3); }
		|	type_constructor
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		;
context		:	class_constraint
				{ $$ = $1; }
		|	'{' class_constraints '}'
				{ $$ = $2; }
		;
conversion_spec	:	expr
				{ $$ = $1; }
		|	expr L_INVERSE expr
				{ $$ = new_node(O_INVERSE, $1, $3); }
		;
deferred_type_def :	L_TYPE simple_name where_context
				{ $$ = new_node(O_TYPE, $2,
						new_node(O_PAIR, Nil(Node), $3));
				}
		;
def_designator	:	L_COMPONENT
				{ $$ = F_COMPONENT; }
		|	L_CONNECTOR
				{ $$ = F_CONNECTOR; }
		|	L_CONSTRAINT
				{ $$ = F_CONSTRAINT; }
		|	L_DEFINITION
				{ $$ = F_DEFINITION; }
		|	L_DIMENSION
				{ $$ = F_DIMENSION; }
		|	L_EQUATION
				{ $$ = F_EQUATION; }
		|	L_FUNCTION
				{ $$ = F_FUNCTION; }
		|	L_MODEL
				{ $$ = F_MODEL; }
		|	L_PROPERTY type_spec /***/
				{ $$ = F_PROPERTY; }
		|	L_STRUCTURE
				{ $$ = F_STRUCTURE; }
		|	L_TYPE
				{ $$ = F_TYPE; }
		|	L_UNIT
				{ $$ = F_UNIT; }
		;
derivative	:	L_DERIVATIVE '(' L_IDENTIFIER ')' '(' expr ')'
				{ $$ = new_node(O_DERIV, new_variable($3), $6); }
		;
designation	:	'\'' designation_indicators '\''
				{ $$ = new_node(O_DESIGNATOR, $2, Nil(Node)); }
		;
designation_indicators : indicators
				{ $$ = $1; }
		|	indicators '/' indicators
				{ $$ = new_node(O_DIVIDE, $1, $3); }
		|	'(' designation_indicators ')'
				{ $$ = $2; }
		;
dim_def		:	L_DIMENSION L_IDENTIFIER dim_body unit_variations
				{ new_unit(define_unit($2), $3, $4);
				  declare_variations($4, $2);
				}
		;
dim_body	:	'=' designation
				{ $$ = $2; }
		|	empty
				{ $$ = Nil(Node); }
		;
indicators	:	indicator_list
				{ $$ = $1; }
		|	'(' indicator_list ')'
				{ $$ = $2; }
		;
indicator_list	:	indicator
				{ $$ = $1; }
		|	indicator_list '*' indicator
				{ $$ = new_node(O_MULTIPLY, $1, $3); }
		;
indicator	:	name '^' indicator_exp
				{ check_unit($1);
				  $$ = new_node(O_EXP, $1, $3);
				}
		|	name
				{ check_unit($1); $$ = $1; }
		|	'(' indicator ')'
				{ $$ = $2; }
		;
indicator_exp	:	op L_INTEGER indicator_post
				{ $$ = new_node(O_PREOP, $1, $3); }
		|	L_INTEGER indicator_post
				{ $$ = new_node(O_SCALE, Nil(Node), Nil(Node));
				  $$ -> u.iconstant = $1;
				}
		|	'(' indicator_exp ')'
				{ $$ = $2; }
		;
indicator_post	:	L_OPERATOR L_INTEGER
				{ $$ = new_node(O_POSTOP, Nil(Node), Nil(Node));
				  $$ -> u.iconstant = $2;
				}
		|	empty
				{ $$ = Nil(Node); }
		;
eq_designation	:	'=' designation
				{ $$ = $2; }
		|	empty
				{ $$ = Nil(Node); }
		;
equation_def	:	label expr
				{ $$ = new_label($1, $2); }
		|	expr
				{ $$ = $1; }
		;
exposure_clause	:	exposures L_FROM name
				{ check_name($3, N_MODEL|N_PACKAGE); }
		;
exposure_item	:	name
				{ open_name(use_name($1)); }
		|	name L_AS simple_name
				{ alias_name(use_name($1), use_name($3)); }
		;
exposures	:	exposures ',' exposure_item
		|	exposure_item
		;
exprs		:	exprs ',' expr
				{ $$ = new_node(O_PAIR, $1, $3); }
		|	expr ',' expr
				{ $$ = new_node(O_PAIR, $1, $3); }
		;
expr		:	prefix_expr
				{ $$ = $1; }
		|	prefix_expr op expr
				{ $$ = new_node(O_APPLY, $2, new_node(O_PAIR, $1, $3)); }
		;
for_generate_header :	L_FOR L_EACH generate_obj_kind simple_name for_tail
				{ /***check_name($4, N_GENERATE);***/
				  use_name($4);
				  $$ = new_node(O_PAIR, $4, $5);
				  $$ = new_node(O_FOREACH, $$, Nil(Node));
				  $$ -> bucket = $3;
				}
		;
for_tail	:	L_IN generates
				{ $$ = $2; }
		|	empty
				{ $$ = Nil(Node); }
		;
function_apply	:	simple_pattern_expr '(' function_args ')'
				{ $$ = new_node(O_APPLY, $1, $3); }
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
				{ $$ = new_node(O_SEMI, $1, $2); }
		|	function_def ';'
				{ $$ = $1; }
		;
generates	:	expr
				{ $$ = $1; }
		;
generate_body	:	generate_body generate_item ';'
				{ $$ = new_node(O_PAIR, $1, $2); }
		|	generate_item ';'
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		;
generate_def	:	generate_header L_GENERATE generate_body L_END L_GENERATE
				{ new_generate($1, $3);
				  $$ = new_node(O_GENERATE, $1, $3);
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
				{ $$ = $1; }
		|	L_CONNECTION L_SET
				{ $$ = $1; }
		|	L_CONNECTOR
				{ $$ = $1; }
		|	L_MEMBER
				{ $$ = $1; }
		|	L_STRUCTURE
				{ $$ = $1; }
		;
guards		:	guards guard
				{ $$ = new_node(O_PAIR, $1, $2); }
		|	guard
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		;
guard		:	'|' expr '=' expr
				{ $$ = new_node(O_GUARD, $2, $4); }
		;
guard_alts	:	guard_alts guard_alt
				{ $$ = new_node(O_PAIR, $1, $2); }
		|	guard_alt
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		;
guard_alt	:	'|' expr L_RARROW expr
				{ $$ = new_node(O_ALT, $2, $4); }
		;
hiding_clause	:	name L_EXCEPT hidings
				{ check_name($1, N_PACKAGE|N_MODEL);
				  open_names($1);
				  close_name_list($3);
				}
		;
hidings		:	hidings ',' hidings
				{ $$ = new_node(O_PAIR, $1, $3); }
		|	simple_name
				{ use_name($1);
				  $$ = $1;
				}
ids		:	L_IDENTIFIER '|' ids
				{ $$ = new_node(O_ID, Nil(Node), Nil(Node));
				  $$ -> bucket = $1;
				  $$ = new_node(O_PAIR, $$, $3);
				}
		|	L_IDENTIFIER
				{ $$ = new_node(O_ID, Nil(Node), Nil(Node));
				  $$ -> bucket = $1;
				  $$ = new_node(O_PAIR, $$, Nil(Node));
				}
		;
if_generate_header :	L_IF expr
				{ $$ = new_node(O_IF, Nil(Node), Nil(Node)); }
		;
inclusions	:	inclusions L_INCLUDES visibility_item ';' 
		|	L_INCLUDES visibility_item ';'
		;
instance_header	:	L_INSTANCE simple_name
				{ $$ = push_name(use_name($2)); }
		|	L_INSTANCE op
				{ $$ = push_name(use_name($2)); }
		;
instance_spec	:	type_specs
				{ $$ = $1; }
		|	empty
				{ $$ = Nil(Node); }
		;
instance_body	:	'{' value_defs '}'
				{ $$ = $2; }
		|	empty
				{ $$ = Nil(Node); }
		;
instance_def	:	instance_header instance_spec instance_body where_context
				{
				  $1 -> cell = new_instance($1, $2, $3, $4);
				  $$ = new_node(O_INSTANCE, Nil(Node), Nil(Node));
				  $$ -> symbol = $1;
				}
		;
integral	:	L_INTEGRAL '(' L_IDENTIFIER ')' integral_expr '(' expr ')'
				{ $$ = new_node(O_PAIR, $5, $7);
				  $$ = new_node(O_INTEGRAL, $$, Nil(Node));
				  $$ -> bucket = $3;
				}
		;
integral_expr	:	'(' expr ',' expr ')'
				{ $$ = new_node(O_PAIR, $2, $4); }
		|	empty
				{ $$ = Nil(Node); }
		;
label		:	L_IDENTIFIER ':'
				{ $$ = define_name($1, LABEL_NAME); }
		;
lambda_abstract	:	'\\' '(' patterns ')' L_RARROW expr
				{ $$ = new_node(O_LAMBDA, $3, $6); }
		;
let_expr	:	L_LET nested_defs L_IN expr
				{ $$ = new_node(O_LET, $2, $4); }
		;
libraries	:	L_LIBRARIES library_names ';'
		;
library_names	:	library_names ',' simple_name
				{ load_library($3); }
		|	simple_name
				{ load_library($1); }
		;
list		:	empty
				{ $$ = Nil(Node); }
		|	expr
				{ $$ = $1; }
		|	exprs
				{ $$ = $1; }
		|	expr '|' qualifiers
				{ $$ = new_node(O_QUALIFIED, $1, $3); }
		|	expr L_DOTS expr
				{ $$ = new_node(O_DOTS, $1, $3); }
		|	expr ',' expr L_DOTS
				{ $$ = new_node(O_DOTS, new_node(O_PAIR, $1, $3), $3); }
		|	expr L_DOTS
				{ $$ = new_node(O_DOTS, $1, Nil(Node)); }
		;
literal		:	L_INTEGER
				{ $$ = new_node(O_INT, Nil(Node), Nil(Node));
				  $$ -> u.iconstant = $1;
				}
		|	L_FLOAT
				{ $$ = new_node(O_FLOAT, Nil(Node), Nil(Node));
				  $$ -> u.fconstant = $1;
				}
		|	L_CHAR
				{ $$ = new_node(O_CHAR, Nil(Node), Nil(Node));
				  $$ -> u.cconstant = $1;
				}
		|	L_STRING
				{ $$ = new_node(O_STRING, Nil(Node), Nil(Node));
				  $$ -> u.string = $1;
				}
		;
model		:	model_head model_library model_inclusions model_body model_tail ';'
				{ cmp_name($1, $5);
				  analyze($4);
				  type_check($4, 0);
				  if (debug['t']) print_tree($4);
				}
		;
model_head	:	L_MODEL simple_name
				{ $$ = push_name(define_node($2, MODEL_NAME)); }
		;
model_tail	:	L_END simple_name
				{ print_undefs(name_stack_ptr); pop_name(); $$ = use_name($2); }
		|	empty
				{ print_undefs(name_stack_ptr); pop_name(); $$ = Nil(Symbol); }
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
				{ $$ = Nil(Node); }
		;
model_items	:	model_items model_item ';'
				{ $$ = new_node(O_PAIR, $1, $2); }
		|	model_item ';'
				{ $$ = $1; }
		;
model_item	:	class_def
				{ $$ = $1; }
		|	dim_def
				{ $$ = Nil(Node); }
		|	instance_def
				{ $$ = $1; }
		|	multiplier_spec
				{ $$ = Nil(Node); }
		|	struct_item
				{ $$ = $1; }
		|	struct_def
				{ $$ = $1; }
		|	type_def
				{ $$ = $1; }
		|	unit_def
				{ $$ = Nil(Node); }
		;
multiplier_spec	:	L_MULTIPLIER L_IDENTIFIER '=' multiplier_tail unit_variations
				{ new_multiplier(define_unit($2), $4);
				  declare_variations($5, $2);
				}
		;
multiplier_tail :	L_INTEGER
				{ $$ = (float) $1; }
		|	L_FLOAT
				{ $$ = $1; }
		;
name		:	simple_name
				{ $$ = $1; }
		|	selected_name
				{ $$ = $1; }
		;
name_def	:	L_COERCION named_values L_COLONS type_spec where_context
				{ $$ = new_node(O_COERCE, $2,
						new_node(O_PAIR, $4, $5));
				}
		|	named_values L_COLONS type_spec where_context
				{ $$ = new_node(O_TYPED, $1,
						new_node(O_PAIR, $3, $4));
				}
		;
named_values	:	names
				{ $$ = $1; }
		;
names		:	names ',' name
				{ define_node($3, NAMED_VALUE_NAME);
				  $$ = new_node(O_PAIR, $1, $3); }
		|	name
				{ define_node($1, NAMED_VALUE_NAME);
				  $$ = $1;
				}
		;
nested_def	:	name_def
				{ $$ = $1; }
		|	value_def
				{ $$ = $1; }
		;
nested_defs	:	'{' nested_def_list '}'
				{ $$ = $2; }
		;
nested_def_list	:	nested_def ';'
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		|	nested_def_list nested_def ';'
				{ $$ = new_node(O_PAIR, $1, $2); }
		;
null		:	'(' ')'
				{ $$ = new_node(O_NULL, Nil(Node), Nil(Node)); }
		;
op		:	operator
				{ $$ = $1; }
		|	'/'
				{ $$ = new_node(O_OP, Nil(Node), Nil(Node));
				  $$ -> bucket = $1;
				  $$ -> code = $1 -> token;
				}
		|	'*'
				{ $$ = new_node(O_OP, Nil(Node), Nil(Node));
				  $$ -> bucket = $1;
				  $$ -> code = $1 -> token;
				}
		|	'^'
				{ $$ = new_node(O_OP, Nil(Node), Nil(Node));
				  $$ -> bucket = $1;
				  $$ -> code = $1 -> token;
				}
		|	'-'
				{ $$ = new_node(O_MINUS, Nil(Node), Nil(Node));
				  $$ -> bucket = $1;
				  $$ -> code = $1 -> token;
				}
		;
operator	:	L_OPERATOR
				{ $$ = new_node(O_OP, Nil(Node), Nil(Node));
				  $$ -> bucket = $1;
				}
		|	L_DOUBLE name L_DOUBLE
				{ $$ = $2; }
		;
operator_apply	:	op expr
				{ $$ = new_node(O_APPLY, $1, $2); }
		;
package		:	package_head package_library package_inclusion package_models package_tail ';'
				{ cmp_name($1, $5);
				  analyze($4);
				  type_check($4, 0);
				  if (debug['t']) print_tree($4);
				}
		;
package_head	:	L_PACKAGE simple_name
				{ $$ = push_name(define_node($2, PACKAGE_NAME)); }
		;
package_tail	:	L_END simple_name
				{ print_undefs(name_stack_ptr); pop_name(); $$ = use_name($2); }
		|	empty
				{ print_undefs(name_stack_ptr); pop_name(); $$ = Nil(Symbol); }
		;
package_inclusion :	inclusions
		|	empty
		;
package_library	:	libraries
		|	empty
		;
package_models	:	model_items
				{ $$ = $1; }
		|	empty
				{ $$ = Nil(Node); }
		;
pattern		:	expr
				{ $$ = new_node(O_PATTERN, $1, Nil(Node)); }
		;
patterns	:	patterns ',' pattern
				{ $$ = new_node(O_PAIR, $1, $3); }
		|	pattern
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		;
physical_value	:	prefix_expr designation
		;
prefix_expr	:	case_expr
				{ $$ = $1; }
		|	cond_expr
				{ $$ = $1; }
		|	derivative
				{ $$ = $1; }
		|	function_apply
				{ $$ = $1; }
		|	integral
				{ $$ = $1; }
		|	lambda_abstract
				{ $$ = $1; }
		|	let_expr
				{ $$ = $1; }
		|	operator_apply
				{ $$ = $1; }
		|	physical_value
				{ $$ = $1; }
		|	primitive_value
				{ $$ = $1; }
		|	simple_pattern_expr
				{ $$ = $1; }
		|	struct_func_create
				{ $$ = $1; }
		|	typed_expr
				{ $$ = $1; }
		;
primitive_value	:	L_PRIMITIVE expr
				{ $$ = new_node(O_PRIMITIVE, $2, Nil(Node)); }
		;
property_kind	:	L_ATTRIBUTE
				{ $$ = F_ATTRIBUTE; }
		|	L_SIGNAL
				{ $$ = F_SIGNAL; }
		;
property_names	:	'(' exprs ')'
				{ $$ = $2; }
		|	'(' expr ')'
				{ $$ = $2; }
		;
qualifier	:	pattern L_LARROW expr
				{ $$ = new_node(O_QUALIFIER, $1, $3); }
		|	expr
				{ $$ = $1; }
		;
qualifiers	:	qualifiers ',' qualifier
				{ $$ = new_node(O_PAIR, $1, $3); }
		|	qualifier
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		;
rhs		:	rhs_guard where_clause
				{ $$ = new_node(O_RHS, $1, $2); }
		|	rhs_guard
				{ $$ = new_node(O_RHS, $1, Nil(Node)); }
		;
rhs_guard	:	'=' expr
				{ $$ = $2; }
		|	guards
				{ $$ = $1; }
		;
selected_name	:	selected_names '.' simple_name
				{ $$ = new_node(O_DOT, $1, $3); }
		;
selected_names	:	selected_names '.' L_IDENTIFIER
				{ $$ = new_node(O_ID, Nil(Node), Nil(Node));
				  $$ -> bucket = $3;
				  $$ = new_node(O_DOT, $1, $$);
				}
		|	L_IDENTIFIER
				{ $$ = new_node(O_ID, Nil(Node), Nil(Node));
				  $$ -> bucket = $1;
				}
		;
simple_name	:	L_IDENTIFIER
				{ $$ = new_node(O_ID, Nil(Node), Nil(Node));
				  $$ -> bucket = $1;
				}
		|	'(' op ')'
				{ $$ = $2; }
		;
simple_pattern_expr :	name
				{ $$ = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$ -> symbol = use_name($1);
				}
		|	variable '@' simple_pattern_expr
				{ $$ = new_node(O_AT, $1, $3); }
		|	'~' simple_pattern_expr
				{ $$ = new_node(O_TILDE, $2, Nil(Node)); }
		|	'_'
				{ $$ = new_node(O_WILDCARD, Nil(Node), Nil(Node)); }
		|	literal
				{ $$ = $1; }
		|	null
				{ $$ = $1; }
		|	'(' expr ')'
				{ $$ = $2; }
		|	'(' exprs ')'
				{ $$ = $2; }
		|	'(' pattern patterns ')'
				{ $$ = new_node(O_PAIR, $2, $3); }
		|	'[' list ']'
				{ $$ = new_node(O_LIST, $2, Nil(Node)); }
		;
specified_type_def :	L_TYPE type_header '=' type_specifier where_context
				{ $$ = new_node(O_TYPE, $2,
						new_node(O_PAIR, $4, $5));
				}
		;
string_exprs	:	expr '|' string_exprs
				{ $$ = new_node(O_PAIR, $1, $3); }
		|	expr
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		;
struct_clause	:	name
				{ use_name($1); }
		|	name struct_config
				{ use_name($1); }
		;
struct_config	:	L_FOR name struct_config_body L_END struct_config_tail
				{ full_cmp_name($2, $5);
				  use_name($2);
				  $$ = new_node(O_FOR, $2, $3);
				}
		;
struct_config_tail :	name
				{ $$ = $1; }
		|	empty
				{ $$ = Nil(Node); }
		;
struct_config_body :	comp_configs
				{ $$ = $1; }
		|	L_USE name
				{ check_name($2, N_CONFIG);
				  use_name($2);
				  $$ = $2;
				}
		;
struct_def	:	struct_def_head struct_inclusion struct_conns struct_comps struct_defs L_END struct_def_tail
				{ pop_name();
				  cmp_name($1, $7);
				  $1 -> cell = new_structure($1, F_STRUCTURE, $4, $3,$5);
				  $$ = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$ -> symbol = $1;
				}
		;
struct_def_head	:	L_STRUCTURE simple_name
				{ $$ = push_name(define_node($2, STRUCTURE_NAME)); }
		;
struct_def_tail	:	simple_name
				{ $$ = use_name($1); }
		|	empty
				{ $$ = Nil(Symbol); }
		;
struct_inclusion :	inclusions
		|	empty
		;
struct_defs	:	struct_items
				{ $$ = $1; }
		|	empty
				{ $$ = Nil(Node); }
		;
struct_comps	:	components
				{ $$ = $1; }
		|	empty
				{ $$ = Nil(Node); }
struct_conns	:	conn_clause
				{ $$ = $1; }
		|	empty
				{ $$ = Nil(Node); }
		;
struct_func_create :	property_names L_LEQEQ name property_names
				{ check_name($3, N_STRUCTURE); }
		;
struct_items	:	struct_items struct_item ';'
				{ $$ = new_node(O_PAIR, $1, $2); }
		|	struct_item ';'
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
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
				{ cmp_name($1, $6);
				  $1 -> cell = new_table($1, $2, $3, $4, $5);
				  $$ = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$ -> symbol = $1;
				}
		;
table_head	:	L_TABLE simple_name 
				{ $$ = define_node($2, TABLE_NAME); }
		;
table_tail	:	L_END simple_name
				{ $$ = use_name($2); }
		|	empty
				{ $$ = Nil(Symbol); }
		;
table_header	:	L_TITLE expr ';'
				{ $$ = $2; }
		|	empty
				{ $$ = Nil(Node); }
		;
table_column	:	column_header
				{ $$ = $1; }
		|	empty
				{ $$ = Nil(Node); }
		;
table_data	:	'{' '{' table_data_rows '}' '}'
				{ $$ = $3; }
		|	'{' '{' '}' '}'
				{ $$ = Nil(Node); }
		;
table_data_rows	:	table_data_rows table_row
				{ $$ = new_node(O_PAIR, $1, $2); }
		|	table_row
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		;
table_entries	:	table_entries '|' table_entry
				{ $$ = new_node(O_PAIR, $1, $3); }
		|	table_entry
				{ $$ = $1; }
		;
table_entry	:	expr
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		|	table_entry expr
				{ $$ = new_node(O_PAIR, $1, $2); }
		;
table_generate_header :	L_FOR L_EACH L_ROW L_IN L_TABLE name
				{ check_name($6, N_TABLE);
				  $$ = $6;
				}
		|	L_FOR L_EACH L_ROW simple_name L_IN L_TABLE name
				{ check_name($7, N_TABLE);
				  $$ = $7;
				}
		;
table_row	:	table_entries ';'
				{ $$ = $1; }
		;
types		:	types ',' type_item
				{ $$ = new_node(O_PAIR, $1, $3); }
		|	type_item
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		;
type_component	:	name '(' types ')'
				{ $$ = new_node(O_PREDICATE, $1, $3);
				  $$ -> symbol = use_name($1);
				}
		|	type_term
				{ $$ = $1; }
		|	def_designator
				{ $$ = new_node(O_INT, Nil(Node), Nil(Node));
				  $$ -> u.iconstant = $1;
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
				{ $$ = new_node(O_PAIR, $1, $3); }
		|	type_item
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		;
type_spec	: 	type_spec L_RARROW type_component
				{ $$ = new_node(O_RARROW, $1, $3); }
		|	type_component
				{ $$ = $1; }
		;
type_specifier	:	constructed_type
				{ $$ = $1; }
		;
type_term	:	name
				{ $$ = new_node(O_NAME, Nil(Node), Nil(Node));
				  $$ -> symbol = use_name($1);
				}
		|	'(' ')'
				{ $$ = Nil(Node); }
		|	'(' types ')'
				{ $$ = $2; }
		|	'[' type_spec ']'
				{ $$ = new_node(O_LIST, $2, Nil(Node)); }
		;
typed_expr	:	'(' expr L_COLONS type_spec where_context ')'
				{ $$ = new_node(O_TYPED, $2,
						new_node(O_PAIR, $4, $5));
				}
		;
unit_convert	:	L_CONVERSION conversion_spec name
				{ $$ = new_node(O_PAIR, $2, $3); }
		|	empty
				{ $$ = Nil(Node); }
		;
unit_def	:	L_UNIT L_IDENTIFIER L_OF name eq_designation unit_convert unit_variations
				{ new_unit(define_unit($2), $5, $6);
				  declare_variations($7, $2);
				}
		;
unit_variations	:	variations
				{ $$ = $1; }
		|	empty
				{ $$ = Nil(Node); }
		;
value_def	:	value_def_target rhs
				{ $$ = new_node(O_VALUE_DEF, $1, $2); }
		|	label L_DEFAULT value_def_target rhs
				{ $$ = new_label($1, new_node(O_DEFAULT, $3, $4)); }
		|	L_DEFAULT value_def_target rhs
				{ $$ = new_node(O_DEFAULT, $2, $3); }
		;
value_defs	:	value_defs value_def ';'
				{ $$ = new_node(O_PAIR, $1, $2); }
		|	value_def ';'
				{ $$ = new_node(O_PAIR, $1, Nil(Node)); }
		;
value_def_target :	expr
				{ $$ = $1; }
		;
variable	:	name
				{ $$ = $1; }
		;
variations	:	L_VARIATIONS variation_ids
				{ $$ = $2; }
		;
variation_ids	:	variation_ids ',' variation_ids
				{ $$ = new_node(O_PAIR, $1, $3); }
		|	L_IDENTIFIER
				{ $$ = new_node(O_ID, Nil(Node), Nil(Node));
				  $$ -> bucket = $1;
				}
		;
visibility_item	:	exposure_clause
		|	hiding_clause
		|	name
				{ check_name($1, N_MODEL|N_PACKAGE);
				  open_names($1);
				}
		;
where_clause	:	L_WHERE '{' function_defs '}'
				{ $$ = new_node(O_WHERE, $3, Nil(Node)); }
		;
where_context	:	L_WHERE context
				{ $$ = new_node(O_CONTEXT, $2, Nil(Node)); }
		|	empty
				{ $$ = Nil(Node); }
		;
empty		:
		;
