#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "errno.h"

#include "espectro.h"
#include "espectro.tab.h"

Frame frame_stack[MAXFRAME];
int frame_stack_ptr = 0;
Value *value_stack[MAXSTACK]; /* Only for subckt parameters */
int value_stack_ptr = 0;
NodeBucket *nodehashtable[NHASH];
int node_count = 0;

extern char *op_names[];
extern char debug[];
extern int line_number;
extern void *dl_handle;

Value *evaluate(TreeNode *root);
void elaborate(TreeNode *root);
void print_tree(TreeNode *root);
void print_value(Value *v);
void print_node(TreeNode *node);

void print_symbol(Symbol *s);

Value *new_value(int);
void elaborate_component(Symbol *symbol, TreeNode *component);

void node_warn(TreeNode *node, char *first, ...);

void
init_nodes()
{
	int i;
	for (i = 0; i < NHASH; i++)
		nodehashtable[i] = (NodeBucket *) 0;
} /* end init_nodes */

int
top_frame_size()
{
	return(value_stack_ptr-frame_stack[frame_stack_ptr-1].original_value_stack_ptr);
} /* end arg_check */

Value *
top_frame_arg(int offset)
{
	int frame_bottom = frame_stack[frame_stack_ptr-1].original_value_stack_ptr;
	return(value_stack[frame_bottom+offset]);
} /* end stack_arg */

int
last_instance_frame()
{
	int f;
	for (f=frame_stack_ptr; f>0; f--)
		if (frame_stack[f].name -> type == T_INSTANCE) return(f);
	return(-1);
} /* end last_instance_frame */

int
instance_frame_size()
{
	int f = last_instance_frame();
	if (f == -1)  fatal("can't find instance in frame stack");
	return(frame_stack[f+1].original_value_stack_ptr-frame_stack[f].original_value_stack_ptr);
} /* end instance_frame_size */

Value *
instance_frame_arg(int offset)
{
	int f = last_instance_frame();
	if (f == -1)  fatal("can't find instance in frame stack");
	return(value_stack[frame_stack[f].original_value_stack_ptr+offset]);
} /* end frame_arg */

void
print_frame(int n)
{
	int j;
	Value *v;
	for (j=frame_stack[n+1].original_value_stack_ptr-1; j>=frame_stack[n].original_value_stack_ptr; j--) {
		v = value_stack[j];
		if (v && v -> symbol) fprintf(stderr, "%s=", v->symbol->bucket->name);
		print_value(v);
		fprintf(stderr, ",");
	} /* end for */
	fprintf(stderr, "]\n");
} /* end print_frame */

void
print_frames()
{
	int i, j;
	Symbol *s;
	frame_stack[frame_stack_ptr+1].original_value_stack_ptr = value_stack_ptr;
	for (i=frame_stack_ptr; i>0; i--) {
		fprintf(stderr, "%d :: %s = %d..%d[", i, frame_stack[i].name -> bucket -> name, frame_stack[i+1].original_value_stack_ptr, frame_stack[i].original_value_stack_ptr);
		print_frame(i);
	} /* end for */
} /* end print_frames */

void
push_frame(Symbol *name)
{
	++frame_stack_ptr;
	frame_stack[frame_stack_ptr].name = name;
	frame_stack[frame_stack_ptr].bindings = NIL;
	frame_stack[frame_stack_ptr].original_value_stack_ptr = value_stack_ptr;
	frame_stack[frame_stack_ptr].values = &value_stack[value_stack_ptr];
} /* end push_frame */

void
pop_frame()
{
	Symbol *s, *new_s;
	if (frame_stack_ptr == 0) fatal("frame stack underflow");
	if (debug['b']) fprintf(stderr, "Unbinding %s:\n", frame_stack[frame_stack_ptr].name -> bucket -> name);
	for (s = frame_stack[frame_stack_ptr].bindings; s;) {
		s -> bound.value = NIL; /* now unbound */
		if (debug['b']) fprintf(stderr, "%s,", s -> bucket -> name);
		new_s = s -> chain;
		s -> chain = NIL;
		s = new_s;
	} /* end for */
	if (debug['b']) fprintf(stderr, "\n");
	value_stack_ptr = frame_stack[frame_stack_ptr--].original_value_stack_ptr;
} /* end pop_frame */

char *
frame_names()
{
	int i, j;
	char cbuf[MAXSTRING], *copy;
	char *lastp, *sp;
	int l;
	for (i=1, lastp = cbuf; i<frame_stack_ptr; i++) {
		for (sp = frame_stack[i].name -> bucket -> name; *sp; ) *lastp++ = *sp++;
		*lastp++ = '.';
	} /* end for */
	l = lastp - cbuf; /* evil address arithmetic */
	copy = (char *) malloc(l);
	strncpy(copy, cbuf, l);
	copy[l-1] = '\0';
	return(copy);
} /* end frame_names */

void
print_node_bucket(NodeBucket *b)
{
	if (b -> absolute) fprintf(stderr, "%d ", b -> absolute);
	if (b -> node) 
		fprintf(stderr, "(%s) -> %d", b -> node -> symbol -> bucket -> name, b -> node -> index);
	fprintf(stderr, "\n");
} /* end print_node_bucket */

void
print_node_table(void)
{
	int i;
	NodeBucket *b;
	for (i=0; i<NHASH; i++)
		for(b = nodehashtable[i]; b; b = b->chain)
			print_node_bucket(b);
} /* end symbol_table_print */

NodeBucket *
new_node_bucket(int absolute)
{
	NodeBucket *b;
	b = (NodeBucket *) malloc(sizeof (NodeBucket));
	b -> absolute = absolute;
	return(b);
} /* end new_node_bucket */

NodeBucket *
lookup_node(NodeBucket *hashtable[], int index)
{
	NodeBucket *b;
	int hash = index % NHASH;
	for(b = hashtable[hash]; b != (NodeBucket *) 0; b = b -> chain)
		if (b -> absolute == index)
			return(b);
	return(NIL);
} /* end lookup_node */

NodeBucket *
enter_node(NodeBucket *hashtable[], int index)
{
	NodeBucket *b;
	int hash = index % NHASH;
	b = new_node_bucket(index);
	b -> chain = nodehashtable[index % NHASH];
	nodehashtable[hash] = b;
	b -> absolute = index;
	return(b);
} /* end lookup_node */

CircuitNode *
new_circuit_node(Symbol *symbol, int number)
{
	CircuitNode *n;
	n = (CircuitNode *) malloc(sizeof (CircuitNode));
	n -> symbol = symbol;
	n -> absolute = number;
	n -> index = -1;
	return(n);
} /* end new_circuit_node */

Value *
new_signal(Symbol *symbol, int number)
{
	Value *signal_value = new_value(T_SIGNAL);
	signal_value -> v.node = new_circuit_node(symbol, number);
	return(signal_value);
} /* end new_signal */

int
new_node_number()
{
	return(++node_count);
} /* end new_node_number */

int
map_node(Value *node)
{
	NodeBucket *nb;
	char *signal_name;
	if (node -> type != T_SIGNAL)
		fatal("node value != T_SIGNAL in map_node");
	if (node -> v.node -> absolute == 0)
		return(0);
	if (node -> v.node -> index > 0) /* already mapped */
		return(node -> v.node -> index);
	else
	if (node -> v.node -> absolute > 0) {
		nb = lookup_node(nodehashtable, node -> v.node -> absolute);
		if (!nb) {
			nb = enter_node(nodehashtable, node -> v.node -> absolute);
			nb -> node = new_circuit_node(NIL, node -> v.node -> absolute);
			nb -> node -> index = new_node_number();
		} /* end new map */
	} /* end if */
	else {
		signal_name = node -> v.node -> symbol -> bucket -> name;
		node -> v.node -> index = new_node_number();
		if (debug['m']) fprintf(stderr, "%s - new node %d\n", signal_name, node_count);
		return(node_count);
	} /* end symbolic node */
	if (debug['m'])
		fprintf(stderr, "map %d to %d\n", node -> v.node -> absolute, nb -> node -> index);
	return(nb -> node -> index);
} /* end map_node */

Value *
new_node_value(TreeNode *first) /* call by value copy of circuit nodes */
{
	Symbol *name = first -> symbol;
	Value *new_signal_value;
	if (name)
		if (name -> bound.value)
			if (name -> bound.value -> type == T_SIGNAL)
				new_signal_value = name -> bound.value;
			else
			if (name -> bound.value -> type == T_INT)
				new_signal_value =  new_signal(name, name -> bound.value -> v.lconstant);
			else fatal("unexpected type in new_node_value");
		else { /* must be new symbolic node */
			new_signal_value = new_signal(name, -1);
			name -> bound.value = new_signal_value; /* now bind it */
		} /* end else */
	else /* must be constant */
	if (first -> value && first -> value -> type == T_INT)
		new_signal_value = new_signal(NIL, first -> value -> v.lconstant);
	else fatal("unknown type in new_node_value");
	return(new_signal_value);
} /* end new_node_value */

void
push_nodes(TreeNode *root)
{
	TreeNode *head, *first;
	for (head = root; head; head = head -> branches[1]) {
		first = head -> branches[0];
		value_stack[value_stack_ptr++] = new_node_value(first);
	} /* end for */
} /* end push_nodes */

void
bind_names(TreeNode *namelist)
{
	int offset;
	TreeNode *first;
	if (!namelist) return;
	for (offset=frame_stack[frame_stack_ptr-1].original_value_stack_ptr;
	     namelist && offset<=frame_stack[frame_stack_ptr].original_value_stack_ptr;
	      offset++) {
		if (namelist -> operator == O_LIST) {
			first = namelist -> branches[0];
			if (first -> operator != O_NAME) fatal("not NAME in bind_names");
			if (value_stack[offset]) { /* push stacked value on symbol value thread */
				if (first -> symbol -> bound.value)
					value_stack[offset] -> next = first -> symbol -> bound.value;
				first -> symbol -> bound.value = value_stack[offset];
				if (debug['X']) {
					fprintf(stderr, "(%s,", first -> symbol -> bucket -> name);
					print_value(value_stack[offset]);
					fprintf(stderr, ")");
				} /* end if */
			} /* end if */
			else	fatal("empty value in bind_names");
			namelist = namelist -> branches[1];
		} /* end if */
		else
		fatal("not LIST in bind_names");
	} /* end for */
	if (debug['X']) fprintf(stderr, "\n");
} /* end bind_names */

void
new_binding(Symbol *s, Value *value)
{
	if (debug['B']) {
		print_symbol(s);
		fprintf(stderr, " = ");
		print_value(value);
	} /* end if */
	if (s -> bound.value) {
		if (debug['B']) fprintf(stderr, " (ignored)\n");
		return;
	}
	else {
		if (debug['B']) fprintf(stderr, "\n");
		s -> bound.value = value;
	} /* end else */
	if (frame_stack[frame_stack_ptr].bindings)
		s -> chain = frame_stack[frame_stack_ptr].bindings;
	frame_stack[frame_stack_ptr].bindings = s;
} /* end new_binding */

void
bind_parameters(TreeNode *list)
{
	int type;
	if (!list) return;
	switch (list -> operator) {
	case O_LIST:
		bind_parameters(list -> branches[0]);
		bind_parameters(list -> branches[1]);
		break;
	case O_BIND:
		if (list -> branches[0] -> symbol) {
			type = list -> branches[0] -> symbol -> type;
			if ((type != T_NONE) && (type != T_SUBNODE) && (type != T_BINDING)){
			   fprintf(stderr, "type=%d\n", list -> branches[0] -> symbol -> type);
			warn("unexpected type in bind_parameters", 0);
		}}
		if (list -> branches[0] -> symbol)
			new_binding(list -> branches[0] -> symbol, evaluate(list -> branches[1]));
		else
		fatal("symbol expected in bind_parameters");
		break;
	case O_IF:
	case O_INSTANCE:
		return; /*done binding */
	default:
		print_tree(list);
		fatal("unexpected operator in bind_parameters");
	} /* end switch */
} /* end bind_parameters */

void
elaborate_paramset(TreeNode *names, TreeNode *exprs)
{
	fatal("elaborate_paramset");
} /* end elaborate component */

void
elaborate_model(Symbol *instance_symbol, TreeNode *body)
{
	if (body -> operator != O_NAME) {
		print_tree(body);
		fatal("unexpected operator in elaborate_model");
	} /* end if */
	elaborate_component(instance_symbol, body);
} /* end elaborate_model */

void
elaborate_component(Symbol *instance_symbol, TreeNode *component)
{
	char *name;
	Symbol *symbol;
	void (*loadin)();
	if (!component) return;
	symbol = component -> symbol;
	name = symbol -> bucket -> name;
	if (debug['E']) fprintf(stderr, "Elaborate ");
	push_frame(symbol);
	switch (component -> symbol -> type) {
	case T_MODEL:
		if (debug['E']) fprintf(stderr, "model %s: ", name);
		bind_parameters(symbol -> u.parameters);
		elaborate_model(instance_symbol, symbol -> bound.extended_model);
		break;	
	case T_SUBCKT:
		if (debug['E']) fprintf(stderr, "subckt %s: ", name);
		bind_names(symbol -> u.parameters);
		elaborate(symbol -> bound.body);
		break;
	case T_BUILTIN:
		if (debug['E']) fprintf(stderr, "builtin %s: ", name);
		(void) (symbol -> bound.value -> v.builtin)(instance_symbol);
		break;
	case T_NONE:
		if (dl_handle)
			if (loadin = dlsym(dl_handle, name)) {
				if (debug['E']) fprintf(stderr, "loadin %s: ", name);
				(void) (loadin)();
			} /* end if loadin */
			else
				node_warn(component, "undefined name: ", name, 0);
		else node_warn(component, "undefined name: ", name, 0);
		break;
	default:
		print_tree(component);
		fatal("bad component type in elaborate_component");
	} /* end switch */
	pop_frame();
} /* end elaborate component */

void
elaborate_instance(TreeNode *node)
{
	TreeNode *name, *nodes, *bindings;
	char *instance_name;
	name = node -> branches[0];
	nodes = node -> branches[1];
	bindings = node -> branches[2];
	instance_name = name -> symbol -> bucket -> name;
	if (debug['E']) fprintf(stderr, "instance %s: ", instance_name);
	if (nodes -> operator == O_COMPONENT) {
		push_frame(name -> symbol);
		bind_parameters(bindings);
		push_nodes(nodes -> branches[0]); /* caller save */
		elaborate_component(name -> symbol, nodes -> branches[1]);
		pop_frame();
	} /* end if */
	else
	if (nodes -> operator == O_PARAMSET)
		elaborate_paramset(nodes -> branches[0], nodes -> branches[1]);
	else
	fatal("unknown node in elaborate_instance");
} /* end elaborate_instance */

void
bind_name(TreeNode *root)
{
	Symbol *name;
	TreeNode *name_node = root -> branches[0];
	if (name_node -> operator != O_NAME) fatal("not a NAME in bind_name");
	name_node -> value = evaluate(root -> branches[1]);
	name = name_node -> symbol;
	new_binding(name, name_node -> value);
} /* end bind_name */

void
elaborate(TreeNode *root)
{
	Value *condition;
	if (!root) return;
	switch (root -> operator) {
	case O_LIST:
		if (root -> branches[0] && root -> branches[0] -> operator == O_IF) {
			condition = evaluate(root -> branches[0] -> branches[0]);
			if (condition -> v.bconstant) elaborate(root -> branches[1]);
		}
		else {
			elaborate(root -> branches[0]);
			elaborate(root -> branches[1]);
		} /* end not O_IF */
		break;
	case O_BIND:
		bind_name(root);
		break;
	case O_INSTANCE:
		elaborate_instance(root);
		break;
	case O_CONTROL:
		break;
	case O_NAME:
		node_warn(root, "unknown statement", 0);
		break;
	default:
		print_tree(root);
		fatal("unknown operator in elaborate");
	} /* end switch */
} /* elaborate */
