#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errno.h"
#include <math.h>

#include "espectro.h"
#include "espectro.tab.h"

extern char *op_names[];
extern char debug[];
extern int line_number;

extern Value *value_stack[];
extern int value_stack_ptr;

Value *new_value(int type);
Value *copy_value(Value *original);
Value *evaluate(TreeNode *root);

void push_frame(Symbol *name);
void pop_frame();
void print_frames();

void add_builtin(char *name, double (*function)(char *));

void node_warn(TreeNode *node, char *first, ...);

void print_tree(TreeNode *root);

#define max(x,y) ((x > y) ? (x) : (y))
#define min(x,y) ((x < y) ? (x) : (y))

int
max_type(Value *v1, Value *v2)
{
	return(v1 -> type > v2 -> type ? v1 -> type : v2 -> type);
} /* end max_type */

long
coerce_int(Value *v)
{
	switch (v -> type) {
	case T_NONE: warn("can't coerce a void type to int", 0); break;
	case T_BOOL: return((int) v -> v.bconstant ? 1 : 0); break;
	case T_INT: return(v -> v.lconstant); break;
	case T_FLOAT:  return((int) v -> v.dconstant); break;
	case T_STRING: warn("can't coerce a string type to int", 0); break;
	default: fatal("unknown type in coerce_int");
	} /* end switch*/
	return(0); /* a nice default */
} /* end coerce_int */

double
coerce_float(Value *v)
{
	switch (v -> type) {
	case T_NONE: warn("can't coerce a void type to float", 0); break;
	case T_BOOL: return((double) v -> v.bconstant ? 1.0 : 0.0); break;
	case T_INT: return((double) v -> v.lconstant); break;
	case T_FLOAT:  return(v -> v.dconstant); break;
	case T_STRING: warn("can't coerce a string type to float", 0); break;
	default: fatal("unknown type in coerce_float");
	} /* end switch*/
	return(0.0); /* a nice default */
} /* end coerce_float */

void
type_error(TreeNode *node, Value *left, Value *right, int type)
{
	print_tree(node);
	node_warn(node, "type error", 0); /* more later */
} /* end type_error */

void
push_values(TreeNode *root)
{
	TreeNode *head, *first;
	for (head = root; head; head = head -> branches[1]) {
		switch (head -> branches[0] -> operator) {
		case O_VALUE:
			value_stack[value_stack_ptr++] = copy_value(head -> branches[0] -> value);
			break;
		case O_NAME:
			value_stack[value_stack_ptr++] = copy_value(head -> branches[0] -> symbol -> bound.value);
			break;
		default:
			value_stack[value_stack_ptr++] = copy_value(evaluate(head -> branches[0]));
			break;
		} /* end switch */
	} /* end for */
} /* end push_values */

double
value_stack_double(int arg)
{
	Value *stacked = top_frame_arg(arg);
	if (!stacked) fatal("NULL stack value in value_stack_double");
	if (stacked -> type == T_INT)
		return((double) stacked -> v.lconstant);
	else
	if (stacked -> type == T_FLOAT)
		return(stacked -> v.dconstant);
	else
		warn("expected an INT or FLOAT", 0);
	return(0.0);
} /* end value_stack_double */

Value *
evaluate_defined_function(int type, TreeNode *body)
{
	Value *retval = new_value(type);
	Value *callval = evaluate(body);
	switch (type) {
	case T_FLOAT:
		retval -> v.dconstant = coerce_float(callval);
		break;
	case T_INT:
		retval -> v.lconstant = coerce_int(callval);
		break;
	default:
		fatal("unknown type in evaluate_defined_function");
	} /* end switch */
	return(retval);
} /* end evaluate_defined_function */

Value *
evaluate_fn(TreeNode *left, TreeNode *right)
{
	Value *retval;
	Symbol *symbol = left -> symbol;
	char *fnname = symbol -> bucket -> name;
	push_frame(symbol);
	if (right) push_values(right); /* caller save */
	if (debug['F']) print_frames();
	if (symbol -> type == T_BUILTIN) {
		retval = new_value(T_FLOAT);
		retval -> v.dconstant = (symbol -> bound.value -> v.builtin)();
	} /* builtin defined fn */
	else
	if (symbol -> type == T_FN)
		retval = evaluate_defined_function(symbol -> return_type, symbol -> bound.body);
	else {
		node_warn(left, "function call ", fnname, 0);
		retval = new_value(T_FLOAT);
		retval -> v.dconstant = 0.0;
	} /* end else */
	pop_frame();
	return(retval);
} /* end evaluate_fn */
	
Value *
evaluate_name(TreeNode *name)
{
	Value *zero;
	if (name -> symbol -> bound.value)
		return(name -> symbol -> bound.value);
	node_warn(name, "unbound variable ", name -> symbol -> bucket -> name, 0);
	zero = new_value(T_FLOAT);
	zero -> v.dconstant = 0.0;
	return(zero);
} /* end evaluate_name */
	
Value *
evaluate(TreeNode *root)
{
	Value *left, *right, *result;
	int new_type;
	if (!root) return NIL;
	switch (root -> operator) {
	case O_LIST:
		return(evaluate(root -> branches[1]));
		break;
	case O_FN:
		return(evaluate_fn(root -> branches[0], root -> branches[1]));
	case O_RETURN:
		return(evaluate(root -> branches[0]));
	case O_VALUE:
		return(root -> value);
	case O_NAME:
		return(evaluate_name(root));
	case O_MUL:		
		left = evaluate(root -> branches[0]);
		right = evaluate(root -> branches[1]);
		new_type = max_type(left, right);
		result = new_value(new_type);
		switch (new_type) {
		case T_INT: result -> v.lconstant = coerce_int(left) * coerce_int(right); break;
		case T_FLOAT: result -> v.dconstant = coerce_float(left) * coerce_float(right); break;
		default: type_error(root, left, right, new_type);
		} /* end switch */
		break;
	case O_DIV:
		left = evaluate(root -> branches[0]);
		right = evaluate(root -> branches[1]);
		new_type = max_type(left, right);
		result = new_value(new_type);
		switch (new_type) {
		case T_INT: result -> v.lconstant = coerce_int(left) / coerce_int(right); break;
		case T_FLOAT: result -> v.dconstant = coerce_float(left) / coerce_float(right); break;
		default: type_error(root, left, right, new_type);
		} /* end switch */
		break;
	case O_ADD:
		left = evaluate(root -> branches[0]);
		right = evaluate(root -> branches[1]);
		new_type = max_type(left, right);
		result = new_value(new_type);
		switch (new_type) {
		case T_INT: result -> v.lconstant = coerce_int(left) + coerce_int(right); break;
		case T_FLOAT: result -> v.dconstant = coerce_float(left) + coerce_float(right); break;
		default: type_error(root, left, right, new_type);
		} /* end switch */
		break;
	case O_SUB:
		left = evaluate(root -> branches[0]);
		right = evaluate(root -> branches[1]);
		new_type = max_type(left, right);
		result = new_value(new_type);
		switch (new_type) {
		case T_INT: result -> v.lconstant = coerce_int(left) - coerce_int(right); break;
		case T_FLOAT: result -> v.dconstant = coerce_float(left) - coerce_float(right); break;
		default: type_error(root, left, right, new_type);
		} /* end switch */
		break;
	case O_EQ:
		left = evaluate(root -> branches[0]);
		right = evaluate(root -> branches[1]);
		result = new_value(T_BOOL);
		if (left -> type != right -> type)
			type_error(root, left, right, T_BOOL);
		else
		switch (left -> type) {
		case T_INT: result -> v.bconstant = (left -> v.lconstant == right -> v.lconstant)? 1 : 0; break;
		case T_FLOAT: result -> v.bconstant = fabs(left -> v.lconstant - right -> v.lconstant) < EPSILON ? 1 : 0; break;
		default: type_error(root, left, right, new_type);
		} /* end switch */
		break;
	case O_LE:
		left = evaluate(root -> branches[0]);
		right = evaluate(root -> branches[1]);
		result = new_value(T_BOOL);
		if (left -> type != right -> type)
			type_error(root, left, right, T_BOOL);
		else
		switch (left -> type) {
		case T_INT: result -> v.bconstant = (left -> v.lconstant <= right -> v.lconstant)? 1 : 0; break;
		case T_FLOAT: result -> v.bconstant = (left -> v.lconstant <= right -> v.lconstant)? 1 : 0; break;
		default: type_error(root, left, right, new_type);
		} /* end switch */
		break;
	case O_OR:
		left = evaluate(root -> branches[0]);
		right = evaluate(root -> branches[1]);
		result = new_value(T_BOOL);
		if (left -> type != right -> type)
			type_error(root, left, right, T_BOOL);
		else
		switch (left -> type) {
		case T_BOOL: result -> v.bconstant = (left -> v.bconstant | right -> v.bconstant); break;
		default: type_error(root, left, right, new_type);
		} /* end switch */
		break;
	case O_AND:
		left = evaluate(root -> branches[0]);
		right = evaluate(root -> branches[1]);
		result = new_value(T_BOOL);
		if (left -> type != right -> type)
			type_error(root, left, right, T_BOOL);
		else
		switch (left -> type) {
		case T_BOOL: result -> v.bconstant = (left -> v.bconstant & right -> v.bconstant); break;
		default: type_error(root, left, right, new_type);
		} /* end switch */
		break;
	case O_POWER:
		left = evaluate(root -> branches[0]);
		right = evaluate(root -> branches[1]);
		new_type = max_type(left, right);
		result = new_value(new_type);
		switch (new_type) {
		case T_INT: result -> v.lconstant = (int) pow(left -> v.lconstant, right -> v.lconstant); break;
		case T_FLOAT: result -> v.dconstant = pow(left -> v.lconstant, right -> v.lconstant); break;
		default: type_error(root, left, right, new_type);
		} /* end switch */
		break;
	case O_NEGATE:
		left = evaluate(root -> branches[0]);
		result = new_value(left -> type);
		switch (left -> type) {
		case T_INT: result -> v.lconstant = -left -> v.lconstant; break;
		case T_FLOAT: result -> v.dconstant = -left -> v.dconstant; break;
		default: type_error(root, left, right, new_type);
		} /* end switch */
		break;
	default:
		print_tree(root);
		fatal("unknown operator in evaluate");
	} /* end switch */
	return(result);
} /* end evaluate */

double
builtin_pow()
{
	if (top_frame_size() != 2) {
		warn("pow expects 2 arguments", 0);
		return(0.0);
	} /* end arg test */
	return(pow(value_stack_double(0), value_stack_double(1)));
} /* end pow */

double
builtin_min()
{
	if (top_frame_size() != 2) {
		warn("min expects 2 arguments", 0);
		return(0.0);
	} /* end arg test */
	return(min(value_stack_double(0), value_stack_double(1)));
} /* end min */

double
builtin_max()
{
	if (top_frame_size() != 2) {
		warn("max expects 2 arguments", 0);
		return(0.0);
	} /* end arg test */
	return(max(value_stack_double(0), value_stack_double(1)));
} /* end max */

double
builtin_abs()
{
	if (top_frame_size() != 1) {
		warn("abs expects 1 argument", 0);
		return(0.0);
	} /* end arg test */
	return(fabs(value_stack_double(0)));
} /* end abs */

double
builtin_sqrt()
{
	if (top_frame_size() != 1) {
		warn("sqrt expects 1 argument", 0);
		return(0.0);
	} /* end arg test */
	return(sqrt(value_stack_double(0)));
} /* end sqrt */

double
builtin_atan()
{
	if (top_frame_size() != 1) {
		warn("atan expects 1 argument", 0);
		return(0.0);
	} /* end arg test */
	return(atan(value_stack_double(0)));
} /* end atan */

double
builtin_log10()
{
	if (top_frame_size() != 1) {
		warn("log10 expects 1 argument", 0);
		return(0.0);
	} /* end arg test */
	return(log10(value_stack_double(0)));
} /* end log10 */

void
builtin_function_init(void)
{
	add_builtin("pow", &builtin_pow);
	add_builtin("min", &builtin_min);
	add_builtin("max", &builtin_max);
	add_builtin("abs", &builtin_abs);
	add_builtin("sqrt", &builtin_sqrt);
	add_builtin("atan", &builtin_atan);
	add_builtin("log10", &builtin_log10);
} /* end builtin_function_init */

