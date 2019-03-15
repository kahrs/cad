#include <stdio.h>
#ifdef PLAN9
#include <u.h>
#include <libc.h>
#else
#include <string.h>
#endif
#include "mhdl.h"
#include "mhdl.tab.h"

void print_class(Symbol *s);
void print_component(Symbol *s);
void print_typedef(Symbol *s);
void print_function(Symbol *s);
void print_structure(Symbol *s);

long int node_number = 0;

char *op_names[] = {
/*00*/	"NULL",
	"LIST",
	"ALT",
	"RHS",
	"GUARD",
	"CASE",
	"ELSE",
	"IF",
	"INVERSE",
	"DERIV",
/*10*/	"INTEGRAL",
	"DIVIDE",
	"MULTIPLY",
	"EXP",
	"PREOP",
	"SCALE",
	"POSTOP",
	"LET",
	"LAMBDA",
	"QUALIFIED",
/*20*/	"DOTS",
	"MINUS",
	"APPLY",
	"QUALIFIER",
	"AT",
	"TILDE",
	"WILDCARD",
	"VAL_DEF",
	"DEFAULT",
	"NAME",
/*30*/	"OP",
	"RARROW",
	"PREDICATE",
	"TYPE",
	"DOT",
	"COERCE",
	"CONFIG",
	"USE",
	"FOR",
	"FOREACH",
/*40*/	"INSTANCE",
	"CONTEXT",
	"PRIMITIVE",
	"CONNECT",
	"ID",
	"ABS_DEF",
	"ASSOC",
	"GENERATE",
	"TYPED",
	"WITH",
/*50*/	"PAIR",
	"PATTERN",
	"DESIGNATOR",
	"WHERE",
	"SEMI",
	"INT",
	"FLOAT",
	"CHAR",
	"STRING",
/*60*/	0
};

Node *
new_node(int operator, Node *left, Node *right)
{
	Node *new;
	new = (Node *) malloc(sizeof (struct Node));
	new -> operator = operator;
	new -> u.tree.left = left;
	new -> u.tree.right = right;
	new -> symbol = Nil(Symbol);
	new -> bucket = Nil(Bucket);
	new -> line = line_number;
	node_number++;
	return(new);
} /* end new_node */

void
print_node(Node *node)
{
	fprintf(stderr, "node %x: ", node);
	switch (node -> operator) {
case O_INT:
	fprintf(stderr, "INT: %ld", node -> u.iconstant);
	break;
case O_FLOAT:
	fprintf(stderr, "FLOAT: %f", node -> u.fconstant);
	break;
case O_CHAR:
	fprintf(stderr, "CHAR: %c", node -> u.cconstant);
	break;
case O_STRING:
	fprintf(stderr, "STRING: %s", node -> u.string);
	break;
case O_OP:
	if (node -> code)
		fprintf(stderr, "Op, token %d", node -> code);
	else	fprintf(stderr, "OP: %s", node -> bucket -> name);
	break;
case O_PAIR:
	fprintf(stderr, "%s: tree.left %x, tree.right %x", op_names[node -> operator],
	node -> u.tree.left, node -> u.tree.right);
	break;
case O_NULL:
default:
	fprintf(stderr, "%s: tree.left %x, tree.right %x", op_names[node -> operator],
	node -> u.tree.left, node -> u.tree.right);
	if (node -> symbol)
		fprintf(stderr, " [%s]", node -> symbol -> bucket -> name);
	if (node -> bucket)
		fprintf(stderr, " (%s)", node -> bucket -> name);
	} /* end switch */
	if (node -> type) {
		fprintf(stderr, "::");
		print_type(node -> type);
	} /* end if type */
	fprintf(stderr, "\n");
} /* end print_node */

void
print_tree_level(Node *node, int level)
{
	int i;
	if (node == Nil(Node)) return;
	for (i=0; i<level; i++) fprintf(stderr, "   ");
	print_node(node);
	switch (node -> operator) {
case O_ID: case O_NAME: case O_NULL:
case O_INT: case O_FLOAT: case O_CHAR: case O_STRING:
	break;
default:
	print_tree_level(node -> u.tree.left, level+1);
	print_tree_level(node -> u.tree.right, level+1);
	} /* end switch */
} /* end print_tree_level */

void
print_tree(Node *node)
{
	print_tree_level(node, 0);
} /* end print_tree */

int
tree_length(Node *head)
{
	if (head == Nil(Node)) return(0);
	if (head -> operator != O_PAIR) return(0);
	return(1 + tree_length(head -> u.tree.left) + tree_length(head -> u.tree.right));
} /* end tree_length */
		
void
list_strings(char **strings, Node *list, int count)
{
	if (list != Nil(Node)) {
		switch (list -> u.tree.left -> operator) {
		case O_ID:
			strings[count] = (char *) strdup(list -> u.tree.left -> bucket -> name);
			break;
		case O_STRING:
			strings[count] = (char *) strdup(list -> u.string);
			break;
		default:
			fatal("unknown operator in list_strings");
		} /* end switch */
		list_strings(strings, list -> u.tree.right, count+1);
	} /* end if */
} /* end list_strings */

int
duplicate_strings(char **array, int length)
{
	int i, j;
	for(i=0; i<length; i++)
	    for(j=0; j<length; j++)
		if (i != j)
			if (strcmp(array[i], array[j]) == 0) return(i);
	return(-1);
} /* end duplicate_strings */

Cell *
new_cell(Symbol *s)
{
	Cell *new;
	new = (Cell *) malloc(sizeof (struct Cell));
	new -> symbol = s;
	new -> linenumber = line_number;
	new -> filename = filename;
	if (s)
		if (s -> cell) fprintf(stderr, "%s of type %d already used in new_cell?\n", s -> bucket -> name, s -> type);
		else s -> cell = new;
	return(new);
} /* end new_cell */

Cell *
new_class(Symbol *symbol, Node *types, Node *body, Node *context)
{
	int arity;
	Cell *cell;
	Class *class;
	cell = new_cell(symbol);
	arity = tree_length(types);
	class = (Class *) malloc(sizeof (struct Class));
	cell -> cell.class =  class;
	class -> arity = arity;
	class -> signature = Nil(Node); 
	class -> header = types;
	class -> superclass = Nil(Class);
	class -> members = body;
	class -> context = context;
	class -> defaults = Nil(Node);
	class -> instances = Nil(Node);
	symbol -> cell = cell;
	return(cell);
} /* end new_class */

Cell *
new_config(Symbol *symbol, Node *body)
{
	Cell *cell;
	Configuration *configuration;
	cell = new_cell(symbol);
	configuration = (Configuration *) malloc(sizeof (struct Configuration));
	configuration -> body = body;
	cell -> cell.configuration =  configuration;
	return(cell);
} /* end new_config */

Cell *
new_constraint(Symbol *symbol, Node *body, Node *report)
{
	Cell *cell;
	Constraint *constraint;
	cell = new_cell(symbol);
	constraint = (Constraint *) malloc(sizeof (struct Constraint));
	constraint -> definition = body;
	constraint -> report = report;
	cell -> cell.constraint =  constraint;
	return(cell);
} /* end new_constraint */

Cell *
new_generate(Node *header, Node *body)
{
	Cell *cell;
	Generate *generate;
	cell = new_cell(Nil(Symbol));
	generate = (Generate *) malloc(sizeof (struct Generate));
	generate -> header = header;
	generate -> body = body;
	cell -> cell.generate =  generate;
	return(cell);
} /* end new_generate */

Cell *
new_instance(Symbol *sym, Node *spec, Node *body, Node *context)
{
	Cell *cell;
	Instance *instance;
	cell = new_cell(sym);
	instance = (Instance *) malloc(sizeof (struct Instance));
	instance -> scheme = new_type_scheme(spec2type(spec), Nil(TypeList));
	instance -> body = body;
	instance -> context = context;
	if (cell -> cell.instance)
		instance -> chain = cell -> cell.instance;
	cell -> cell.instance =  instance;
	return(cell);
} /* end new_instance */

Node *
new_label(Symbol *sym, Node *def)
{
	Cell *cell;
	Label *label;
	if (sym != Nil(Symbol)) {
		cell = new_cell(sym);
		label = (Label *) malloc(sizeof (struct Label));
		label -> branch = def;
		cell -> cell.label = label;
		sym -> cell = cell;
	} /* end if */
	return(def);
} /* end new_label */

Cell *
new_library(Symbol *sym, char *path)
{
	Cell *cell;
	Library *library;
	cell = new_cell(sym);
	library = (Library *) malloc(sizeof (struct Library));
	library -> path = (char *) strdup(path);
	cell -> cell.library = library;
	sym -> cell = cell;
	return(cell);
} /* end new_library */

Cell *
new_multiplier(Symbol *sym, float scale_factor)
{
	Cell *cell;
	check_multiplier(sym -> bucket -> name);
	cell = new_cell(sym);
	cell -> cell.multiplier = (Multiplier *) malloc(sizeof (struct Multiplier));
	cell -> cell.multiplier -> scale_factor = scale_factor;
	sym -> cell = cell;
	return(cell);
} /* end new_multiplier */

void
new_names(Node *list, int flag, Node *type_spec)
{
	Cell *cell;
	Name *name;
	Node *node;
	if (list == Nil(Node)) return;
	if (list -> operator == O_PAIR) {
		new_names(list -> u.tree.left, flag, type_spec);
		new_names(list -> u.tree.right, flag, type_spec);
	}
	else {
		cell = new_cell(list -> symbol);
		name = (Name *) malloc(sizeof (struct Name));
		name -> flags = flag;
		name -> type_graph = type_spec; /* until converted */
		cell -> cell.name = name;
	} /* end else */
} /* end new_names */

Cell *
new_structure(Symbol *sym, int kind, Node *items, Node *connectors, Node *defs)
{
	Cell *cell;
	if (debug['v']) fprintf(stderr, "new struct: %s\n", sym -> bucket -> name);
	cell = new_cell(sym);
	cell -> cell.structure = (Structure *) malloc(sizeof (struct Structure));
	cell -> cell.structure -> kind = kind;
	cell -> cell.structure -> items = items;
	cell -> cell.structure -> connectors = connectors;
	cell -> cell.structure -> definitions = defs;
/* 	sym -> cell = cell; */
	return(cell);
} /* end new_structure */

Cell *
new_table(Symbol *sym, Node *header, Node *columns, Node *names, Node *data)
{
	int column_length, name_length, data_length, dup;
	Cell *cell;
	cell = new_cell(sym);
	cell -> cell.table = (Table *) malloc(sizeof (struct Table));
	cell -> cell.table -> name = header -> u.string;
	column_length = tree_length(columns);
	name_length = tree_length(names);
	if (name_length == column_length) {
		cell -> cell.table -> column_headers = (char **) calloc(column_length, sizeof(char *));
		cell -> cell.table -> column_names = (char **) calloc(column_length, sizeof(char *));
		list_strings(cell -> cell.table -> column_headers, columns, 0);
		list_strings(cell -> cell.table -> column_names, names, 0);
		dup = duplicate_strings(cell -> cell.table -> column_names, column_length);
		if (dup >= 0) semantics(columns, "duplicate name in column list (2.4.2)",
			cell -> cell.table -> column_names[dup], 0);
	} /* end if */
	else
	if (name_length != 0 && column_length != 0)
		semantics(header, "number of columns doesn't agree with names (2.4.2)", 0, 0);
	print_tree(data);
	data_length = tree_length(data);
fprintf(stderr, "len = %d\n", data_length);
	cell -> cell.table -> data = data;
	return(cell);
} /* end new_table */

Cell *
new_fn(Symbol *sym, int arity, Type *type, Node *context)
{
	Cell *cell;
	cell = new_cell(sym);
	cell -> cell.function = (Function *) malloc(sizeof (struct Function));
	cell -> cell.function -> arity = arity;
	cell -> cell.function -> type = type;
	cell -> cell.function -> context = context;
	return(cell);
} /* end new_fn */

Cell *
new_unit(Symbol *s, Node *designation, Node *conversions)
{
	Cell *cell;
	cell = new_cell(s);
	cell -> cell.unit = (Unit *) malloc(sizeof (struct Unit));
/***	check_designation(designation, ...); ***/
	cell -> cell.unit -> designation = designation;
	cell -> cell.unit -> conversion = conversions;
	return(cell);
} /* end new_unit */

Cell *
merge_structs(Cell *old, Cell *new)
{
	Node *old_items, *new_items;
	old_items = old -> cell.structure -> items;
	new_items = new -> cell.structure -> items;
	if (old_items -> symbol != new_items -> symbol)
		warn("component structures don't match (3.1)", old_items -> symbol->bucket->name, "&", new_items -> symbol->bucket->name, 0);
	/*** merge structures ***/
	return(old);
} /* end merge_structs */

void
load_library(Node *node)
{
	Symbol *library_name;
	library_name = use_name(node);
	if (library_name -> category != N_LIBRARY) {
		warn("library", library_name -> bucket -> name, "not found", 0);
		return;
	} /* end if */
	if (debug['v'])
		fprintf(stderr, "load library %s\n", library_name -> cell -> cell.library -> path);
} /* end load_library */

void
analyze_list(Node *root)
{
	if (root -> operator != O_LIST)
		semantics(root, "list expression expected", 0, 0);
} /* end analyze_list */

void
analyze_generate(Node *root)
{
	Node *iterator, *for_tail, *elements;
	iterator = root -> u.tree.left;
	elements = root -> u.tree.right;
	switch (iterator -> operator) {
	case O_IF:
		break;
	case O_FOREACH:
		for_tail = iterator -> u.tree.right -> u.tree.right;
		if (for_tail != Nil(Node) && iterator -> u.tree.left -> u.iconstant == L_MEMBER)
			if (for_tail -> operator != O_LIST)
				semantics(iterator, "only lists permitted in generate member (2.3.6)", 0, 0);
			else;
		else
		if (for_tail == Nil(Node)) fatal("for_tail nil in analyze_generate");
		else	{
			if (for_tail -> operator == O_LIST)
				semantics(iterator, "list not permitted in generate (2.3)", 0, 0);
			else
			switch (iterator -> u.tree.left -> u.iconstant) {
			case L_COMPONENT:
				if (for_tail -> operator == O_ID)
					verify_name_type(for_tail, N_STRUCTURE);
				else
					analyze_list(for_tail);	
				break;
			case L_CONNECTION:
				if (for_tail -> operator == O_ID)
					verify_name_type(for_tail, N_STRUCTURE);
				else
					analyze_list(for_tail);	
				break;
			case L_CONNECTOR:
				if (for_tail -> operator == O_ID)
					verify_name_type(for_tail, N_STRUCTURE|N_COMPONENT);
				else
					analyze_list(for_tail);	
				break;
			case L_STRUCTURE:
				if (for_tail -> operator == O_ID)
					verify_name_type(for_tail, N_PACKAGE|N_MODEL);
				else
					analyze_list(for_tail);	
				break;
			default:
				fatal("unknown foreach generate_obj_kind");
			break;
			} /* end switch */
		} /* end if */
		analyze(elements);
		break;
	case O_ID: /* table name */
		break;
	default:
		fatal("unknown left node in generate");
	} /* end switch */
} /* end analyze_generate */

void
analyze_name(Node *root)
{
	Symbol *s;
	s = dereference_node(root);
	switch (s -> category) {
	case STRUCTURE_NAME:
		if (debug['S']) print_structure(s);
		analyze(s -> cell -> cell.structure -> items);
		break;
	case COMPONENT_NAME:
		if (debug['S']) print_component(s);
		break;
	case CLASS_NAME:
		if (debug['S']) print_class(s);
		break;
	case TYPE_NAME:
		if (debug['S']) print_typedef(s);
		break;
	case FUNCTION_NAME:
		if (debug['S']) print_function(s);
		break;
	case TABLE_NAME:
	case NO_NAME: /* not yet declared */
		break;
	case CONSTRAINT_NAME:
	case ABS_PROP_NAME:
	default:
		print_node(root);
		fprintf(stderr, "symbol %s type %x\n", s->bucket->name, s->type);
		fatal("unknown type in analyze_name");
	} /* end switch */
} /* end analyze_name */

int
fn_arity(Node *signature)
{
	if (signature == Nil(Node)) return(0);
	if (signature -> operator == O_RARROW) 
		return(fn_arity(signature -> u.tree.left)
			+ fn_arity(signature -> u.tree.right));
	else
	if (signature -> operator == O_LIST)
		return(fn_arity(signature -> u.tree.left));
	else
		return(1);
} /* end fn_arity */


void
analyze_typedef(Node *lhs, Node *rhs)
{
	Node *signature;
	Node *context;
	Cell *type_def;
	Symbol *sym;

	if (lhs -> operator == O_ID) {
		sym = lhs -> bucket -> symbols;
		signature = rhs -> u.tree.left;
		context = rhs -> u.tree.right;
		type_def = new_fn(sym, fn_arity(signature)-1, spec2type(signature), context);
		sym -> category = FUNCTION_NAME;
	} else {
print_node(lhs);
		analyze_typedef(Left(lhs), rhs);
		analyze_typedef(Right(lhs), rhs);
	} /* end else */
} /* end analyze_typedef */

void
analyze(Node *root)
{
	if (root == Nil(Node)) return;
	if (root -> operator > O_STRING)
		fatal("operator out of bounds in analyze");
	switch (root -> operator) {
	case O_LIST: /* unary */
	case O_TILDE:
	case O_CONNECT:
	case O_ASSOC:
	case O_PATTERN:
	case O_DESIGNATOR:
		analyze(root -> u.tree.left);
		if (root -> u.tree.right) fatal("non null right in analyze");
		break;
	case O_NULL: /* nullary */
	case O_MINUS:
	case O_INT:
	case O_FLOAT:
	case O_CHAR:
	case O_STRING:
	case O_WILDCARD:
	case O_OP:
		break;
	case O_GENERATE:
		analyze_generate(root);
		break;
	case O_NAME:
		analyze_name(root);
		break;
	case O_PRIMITIVE:
		break;
	case O_TYPED:
		analyze_typedef(root -> u.tree.left, root -> u.tree.right);
		break;
	case O_PAIR:
	case O_VALUE_DEF:
	case O_APPLY:
	case O_RHS:
	case O_ALT:
	case O_GUARD:
	case O_CASE:
	case O_IF:
	case O_ELSE:
	case O_LAMBDA:
	case O_AT:
	case O_LET:
	case O_QUALIFIED:
	case O_QUALIFIER:
		analyze(root -> u.tree.left);
		analyze(root -> u.tree.right);
		break;
	case O_ID:
		break;
	case O_TYPE:
	case O_DOT:
	case O_INSTANCE:
	case O_CONTEXT:
	case O_COERCE:
	case O_ABS_DEF:
	case O_WHERE:
		break;
	default:
		print_node(root);
		fatal("default op in analyze");
		break;
	} /* end switch */
} /* end analyze */

void
print_component(Symbol *s)
{
	Structure *cs;
	fprintf(stderr, "component %s\n", s -> bucket -> name);
	fprintf(stderr, "\titems:\n");
	cs = s -> cell -> cell.structure;
	print_tree(cs -> items);
	fprintf(stderr, "\tdefinitions:\n");
	analyze(cs -> definitions);
	fprintf(stderr, "\tconnectors:\n");
	print_tree(cs -> connectors);
	fprintf(stderr, "\tproperties:\n");
	print_tree(cs -> properties);
} /* end print_component */

void
print_class(Symbol *s)
{
	Class *class;
	class = s -> cell -> cell.class;
fprintf(stderr, "s->cell=%x\n", s->cell);
if (class == Nil(Class)) fprintf(stderr, "class dismissed.\n");
	fprintf(stderr, "arity: %d\n", class -> arity);
	print_tree(class -> header);
	print_tree(class -> members);
	print_tree(class -> context);
} /* end print_class */

void
print_typedef(Symbol *s)
{
	fprintf(stderr, "type %s: ", s -> bucket -> name);
	print_type_schemes(s -> type);
	fprintf(stderr, "\n");
} /* end print_typedef */

void
print_function(Symbol *s)
{
	Function *function;
	function = s -> cell -> cell.function;
	fprintf(stderr, "function %s, arity %d: ", s -> bucket -> name, function -> arity);
	print_type(function -> type);
	fprintf(stderr, "\n");
	print_tree(function -> context);
} /* end print_function */

void
print_structure(Symbol *s)
{
	fprintf(stderr, "structure %s\n", s -> bucket -> name);
	fprintf(stderr, "\titems:\n");
	print_tree(s -> cell -> cell.structure -> items);
	fprintf(stderr, "\tdefinitions:\n");
	analyze(s -> cell -> cell.structure -> definitions);
	fprintf(stderr, "\tconnectors:\n");
	print_tree(s -> cell -> cell.structure -> connectors);
	fprintf(stderr, "\tproperties:\n");
	print_tree(s -> cell -> cell.structure -> properties);
} /* end print_structure */
