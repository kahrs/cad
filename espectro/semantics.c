#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "errno.h"

#include "espectro.h"
#include "espectro.tab.h"

int node_number = 0;
TreeNode *node_stack[MAXSTACK];
int node_stack_ptr = 0;

extern int line_number;
extern char debug[];
extern int errno;
extern char *filename;
extern TreeNode *last_root;
extern char *type_names[];

double check_multiplier(char *name);

char *op_names[] = {
	"NULL",
	"CONTROL",
	"FN",
	"GT",
	"GE",
	"LT",
	"LE",
	"EQ",
	"NE",
	"UMINUS",
	"LIST",
	"RESISTOR",
	"CAPACITOR",
	"INDUCTOR",
	"SOURCE",
	"CALL",
	"NAME",
	"VALUE",
	"STRING",
	"BIND",
	"ADD",
	"SUB",
	"MUL",
	"DIV",
	"MOD",
	"POWER",
	"NEGATE",
	"INSTANCE",
	"COMPONENT",
	"PARAMSET",
	"RETURN",
	"CONDEXPR",
	"IC",	
	"IF",
	"MODEL",
	"NOT",
	"AND",
	"OR",
	"ELSE",
	0
};

TreeNode *
new_tree_node(int operator, int limit, ...)
{
        TreeNode *new_node;
	int oc;
	va_list(ap);
        va_start(ap, limit);
	new_node = (TreeNode *) malloc(sizeof (struct TreeNode));
	for (oc = 0; oc < limit; oc++) new_node -> branches[oc] = NIL;
	for (oc = 0; oc < limit; oc++) new_node -> branches[oc] = va_arg(ap, TreeNode *);
	va_end(ap);
        new_node -> operator = operator;
        new_node -> line_number = line_number;
	new_node -> filename = filename;
	new_node -> limit = limit;
	new_node -> value = (Value *) 0;
	new_node -> symbol = (Symbol *) 0;
        node_number++;
        return(new_node);
} /* end new_node */

TreeNode *
node0(int operator)
{
	new_tree_node(operator, 0);
}

TreeNode *
node1(int operator, TreeNode *branch1)
{
	new_tree_node(operator, 1, branch1);
}

TreeNode *
node2(int operator, TreeNode *branch1, TreeNode *branch2)
{
	new_tree_node(operator, 2, branch1, branch2);
}

TreeNode *
node3(int operator, TreeNode *branch1, TreeNode *branch2, TreeNode *branch3)
{
	new_tree_node(operator, 3, branch1, branch2, branch3);
}

TreeNode *
node4(int operator, TreeNode *branch1, TreeNode *branch2, TreeNode *branch3, TreeNode *branch4)
{
	new_tree_node(operator, 4, branch1, branch2, branch3, branch4);
}

TreeNode *
node5(int operator, TreeNode *branch1, TreeNode *branch2, TreeNode *branch3, TreeNode *branch4, TreeNode *branch5)
{
	new_tree_node(operator, 5, branch1, branch2, branch3, branch4, branch5);
}

TreeNode *
node6(int operator, TreeNode *branch1, TreeNode *branch2, TreeNode *branch3, TreeNode *branch4, TreeNode *branch5, TreeNode *branch6)
{
	new_tree_node(operator, 6, branch1, branch2, branch3, branch4, branch5, branch6);
}

TreeNode *
node7(int operator, TreeNode *branch1, TreeNode *branch2, TreeNode *branch3, TreeNode *branch4, TreeNode *branch5, TreeNode *branch6, TreeNode *branch7)
{
	new_tree_node(operator, 7, branch1, branch2, branch3, branch4, branch5, branch6, branch7);
}

void
print_value(Value *v)
{
	CircuitNode *n;
	if (v)
		switch(v -> type) {
		case T_NONE:
			fprintf(stderr, "[no type]"); break;
		case T_BOOL:
			fprintf(stderr, " %c", v -> v.bconstant?'T':'F' ); break;
		case T_INT:
			fprintf(stderr, " %ld", v -> v.lconstant); break;
		case T_FLOAT:
			fprintf(stderr, " %e", v -> v.dconstant); break;
		case T_STRING:
			fprintf(stderr, " '%s'", v -> v.string); break;
		case T_SIGNAL:
			if (v -> symbol)
				fprintf(stderr, "@%s:", v -> symbol -> bucket -> name);
			if (v -> v.lconstant == -1)
				fprintf(stderr, "#?");
			else {
				n = v -> v.node;
				fprintf(stderr, "%s::", n -> symbol ? n -> symbol -> bucket -> name : "");
				if (n -> absolute != -1)
					fprintf(stderr, "#%d", n -> absolute);
				else
				if (n -> index != -1)
					fprintf(stderr, "%d", n -> index);
			} /* end symbolic node */
			break;
		default:
			fatal("unknown type in print_value");
		} /* end switch */
} /* end print_value */

void
print_node(TreeNode *node)
{
        fprintf(stderr, "node %p - %s: ", node, op_names[node -> operator]);
        if (node -> symbol) {
                fprintf(stderr, " [%s (LL %d, symbol %p) = ",
			node -> symbol -> bucket -> name, node -> symbol -> ll, node -> symbol);
		switch (node -> symbol -> type) {
		case T_MODEL:
		case T_SUBCKT:
		case T_FN:
		case T_INSTANCE:
			fprintf(stderr, ".%s", type_names[node -> symbol -> type]);
			break;
		case T_FORMAL:
		case T_SUBNODE:
			break;
		case T_BINDING:
			print_value(node -> symbol -> bound.value);
			break;
		case T_BUILTIN:
			fprintf(stderr, "=0x%p", node -> symbol -> bound.value -> v.builtin);
			break;
		case T_NONE:
			fprintf(stderr, "?");
			break;
		default:
			fatal("unknown symbol type in print_node");
		} /* end switch */
	} /* end if */
	else
	if (node -> value) print_value(node -> value);
        fprintf(stderr, "\n");
} /* end print_node */

void
print_tree_level(TreeNode *node, int level)
{
        int i;
        if (node == NIL) return;
        for (i=0; i<level; i++) fprintf(stderr, "   ");
        print_node(node);
        switch (node -> operator) {
default:
        for (i=0; i<node -> limit; i++)
		print_tree_level(node -> branches[i], level+1);
        } /* end switch */
} /* end print_tree_level */

void
print_tree(TreeNode *root)
{
	print_tree_level(root, 0);
} /* end print_tree */

TreeNode *link_node(TreeNode *old, TreeNode *new)
{
	TreeNode *new_node = node2(O_LIST, new, NIL);
	if (old) old -> branches[1] = new_node;
	return(new_node);
} /* end link_node */

Value *
new_value(int type)
{
	Value *new_value;
	new_value = (Value *) malloc(sizeof (struct Value));
	new_value -> type = type;
	new_value -> level = -1; /* dynamic level unknown */
	new_value -> next = (Value *) 0;
	new_value -> v.lconstant = 0;
	new_value -> symbol = (Symbol *) 0;
	return(new_value);
} /* end new_value */

Value *
copy_value(Value *original)
{
	Value *copy = (Value *) malloc(sizeof (struct Value));
	return(memcpy(copy, original, sizeof (struct Value)));
} /* end copy_value */

void
push_node(TreeNode *top)
{
	node_stack[node_stack_ptr++] = top;
} /* end push_node */

TreeNode *
pop_node(void)
{
	return(node_stack[--node_stack_ptr]);
} /* end pop_node */

void
start_subckt(Symbol *s, TreeNode *parameters)
{
	if (debug['v']) fprintf(stderr, "new subckt: %s\n", s -> bucket -> name);
	s -> u.parameters = parameters;
	push_node(last_root);
	last_root = link_node(NIL, NIL); /* null O_LIST node */
	push_node(last_root);
} /* end start_subckt */

void
end_subckt(Symbol *end_s, Symbol *stacked_s)
{
	if (debug['v']) fprintf(stderr, "end subckt: %s\n", end_s -> bucket -> name);
	end_s -> bound.body = pop_node() -> branches[1];
	if (strcmp(stacked_s -> bucket -> name, end_s -> bucket -> name) != 0)
		warn("subckt names don't agree: ",
			stacked_s -> bucket -> name, end_s -> bucket -> name, 0);
	last_root = pop_node();
} /* end end_subckt */

void
new_model(TreeNode *name, TreeNode *old_name, TreeNode *bindings)
{
	if (debug['v']) fprintf(stderr, "new model: %s extends %s\n",
		name -> symbol -> bucket -> name, old_name -> symbol -> bucket -> name);
	name -> symbol -> u.bindings = bindings;
	name -> symbol -> bound.extended_model = old_name;
} /* end new_model */

void
new_function(TreeNode *type, TreeNode *name, TreeNode *formals, TreeNode *body)
{
	Symbol *s = name -> symbol;
	if (debug['v']) fprintf(stderr, "new function: %s\n", s -> bucket -> name);
	s -> u.bindings = formals;
	s -> bound.body = body;
	s -> return_type = type -> value -> type;
} /* end new_model */

TreeNode *
new_instance(TreeNode *name, TreeNode *body, TreeNode *bindings)
{
	if (debug['I']) fprintf(stderr, "new instance: %s\n", name -> symbol -> bucket -> name);
	return(node3(O_INSTANCE, name, body, bindings));
} /* end new_instance */

