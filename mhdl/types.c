#include <stdio.h>
#ifdef PLAN9
#include <u.h>
#include <libc.h>
#endif
#include "mhdl.h"
#include "mhdl.tab.h"

#define min(x, y) ((x) < (y)) ? x : y

extern char *op_names[];

Type *new_type_exp(int exp);
TypeList *extend_list(TypeScheme *head, TypeList *tail);
int occurs_in_typelist(TypeVar *typeVar, TypeList *list);
int unify_type(Type *typeExp1, Type *typeExp2);
int unify_vars(TypeVar *var1, TypeVar *var2);
Type *fresh(Type *typeExp, TypeList *list);

Type *bool_type, *int_type, *float_type, *char_type, *string_type;
int var_count = 0;

Type *
new_type_exp(int exp)
{
	Type *r;
	r = (Type *) malloc(sizeof(Type));
	r -> family = exp;
	return(r);
} /* end new_type_exp */

TypeScheme *
new_type_scheme(Type *t, TypeList *vl)
{
	TypeScheme *r;
	r = (TypeScheme *) malloc(sizeof(TypeScheme));
	r -> list = vl;
	r -> type = t;
	return(r);
} /* end new_type_scheme */

Symbol *
new_polymorphic_name(void)
{
	char name[10];
	sprintf(name, "_%d", ++var_count);
	if (debug['T']) fprintf(stderr, "Polymorphic %s\n", name);
	return(bind_name(name, POLYMORPHIC_NAME));
} /* end new_polymorphic_name */

Type *
new_type_var(TypeVar *tv)
{
	Type *t = new_type_exp(T_VAR);
	t -> u.variable = tv;
	return(t);
} /* end new_type_var */

TypeScheme *
new_type_var_scheme(TypeVar *tv)
{
	return(new_type_scheme(new_type_var(tv), Nil(TypeList)));
} /* end new_type_var_scheme */

Type *
new_base_type(char *name)
{
	Type *type;
	Symbol *entry;
	type = new_type_exp(T_BASE);
	entry = bind_name(name, TYPE_NAME);
	type -> u.base_type = entry;
	entry -> type = extend_list(new_type_scheme(type, Nil(TypeList)), entry -> type);
	return(type);
} /* end new_base_type */

Type *
new_fn_type(Type *left, Type *right)
{
	Type *type;
	type = new_type_exp(T_ARROW);
	type -> u.function.left = left;
	type -> u.function.right = right;
	return(type);
} /* end new_fn_type */

Type *
new_list_type(Type *of)
{
	Type *type;
	type = new_type_exp(T_CONSTRUCTOR);
	type -> u.list = of;
	return(type);
} /* end new_base_type */

TypeList *
new_typelist(void)
{
	TypeList *result;
	result = (TypeList *) malloc(sizeof (TypeList));
	result -> tail = Nil(TypeList);
	return(result);
} /* end new_typelist */

TypeList *
extend_list(TypeScheme *head, TypeList *tail)
{
	TypeList *r;
	if (head == Nil(TypeScheme)) return(tail);
	r = (TypeList *) malloc(sizeof(TypeList));
	r -> head.scheme = head;
	r -> tail = tail;
	return(r);
} /* end extend_list */

#define MAXDEPTH 100000

TypeVar *
fresh_type_var(int depth, Symbol *s)
{
	TypeVar *tv;
	tv = (TypeVar *) malloc(sizeof(TypeVar));
	tv -> kind = K_QUANTIFIER;
	tv -> depth = depth;
	tv -> symbol = s;
	return(tv);
} /* end fresh_type_var */

TypeList *
freshen_list(TypeList *list)
{
	TypeList *ip;
	Symbol *s;
	if (!list) return(Nil(TypeList));
	for (ip = list; ip; ip = ip -> tail)
		ip -> head.variable = fresh_type_var(MAXDEPTH, ip -> head.variable -> symbol);
	return(ip);
} /* end freshen_list */

Type *
freshen_type(Type *type, TypeList *list)
{
	Type *result;
	switch (type -> family) {
	case T_VAR:
		switch (type -> u.variable -> kind) {
		case K_INSTANCE:
			return(freshen_type(type -> u.variable -> instance, list));
			break;
		case K_QUANTIFIER:
			return(type);
		default:
			fatal("unknown kind in freshen_type");
		} /* end switch kind */
		break;
	case T_BASE:
		return(type);
	case T_ARROW:
		return(new_fn_type(freshen_type(type -> u.function.left, list), freshen_type(type -> u.function.right, list)));
	case T_ANY:
	default:
		fatal("unknown family in freshen_type");
	} /* end switch family */
} /* end freshen_type */

Type *
fresh_type_scheme(TypeScheme *scheme)
{
	TypeList *fresh_typelist;
	fresh_typelist = freshen_list(scheme -> list);
	return(freshen_type(scheme -> type, fresh_typelist));
} /* end fresh_type */

void
type_init(void)
{
	bool_type = new_base_type("Bool");
	int_type = new_base_type("Int");
	float_type = new_base_type("Float");
	char_type  = new_base_type("Char");
	string_type = new_base_type("String");
} /* end type_init */

Type *
spec2type(Node *spec)
{
	Type *type_var;
	TypeList *list;
	TypeScheme *var_scheme;
	if (spec == Nil(Node)) return(Nil(Type));
	switch (spec -> operator) {
	case O_PREDICATE:		
		return(new_list_type(spec2type(Right(spec))));
	case O_LIST:
		return(new_list_type(spec2type(Left(spec))));
	case O_PAIR:
		return(spec2type(Left(spec)));
	case O_RARROW:
		return(new_fn_type(spec2type(Left(spec)), spec2type(Right(spec))));
	case O_NAME:
		list = spec -> symbol -> type;
		if (!list) {
			list = extend_list(new_type_var_scheme(fresh_type_var(MAXDEPTH, spec -> symbol)), spec -> symbol -> type);
			spec -> symbol -> type = list;
		} /* end else */
		return(list -> head.scheme -> type);
	default:
		print_tree(spec);
		fatal("unknown code in spec2type");
	} /* end switch */
} /* end spec2type */

void
print_type_var(TypeVar *var)
{
	fprintf(stderr, "%s: ", var -> symbol -> bucket -> name);
	switch (var -> kind) {
	case K_NO:
		fprintf(stderr, "No");
		break;
	case K_INSTANCE:
		fprintf(stderr, "I ");
		print_type(var -> instance);
		break;
	case K_QUANTIFIER:
		if (var -> depth == MAXDEPTH)
			fprintf(stderr, "Q?");
		else	fprintf(stderr, "Q%d", var -> depth);
		break;
	default:
		fatal("unknown kind in print_type_var");
	} /* end switch */
} /* end print_type_var */

void
print_type(Type *exp)
{
	if (exp == Nil(Type)) fprintf(stderr, "<nil>");
	else
	switch (exp -> family) {
	case T_NO:
		fprintf(stderr, "?");
		break;
	case T_VAR:
		print_type_var(exp -> u.variable);
		break;
	case T_ARROW:
		print_type(exp -> u.function.left);
		fprintf(stderr, "->");
		print_type(exp -> u.function.right);
		break;
/*	case T_LIST:
		fprintf(stderr, "[");
		print_type(exp -> u.list);
		fprintf(stderr, "]");
		break;
*/
	case T_BASE:
		fprintf(stderr, "%s", exp -> u.base_type -> bucket -> name);
		break;
	case T_ANY:
		fprintf(stderr, "<any>");
		break;
case 	T_PRODUCT:
case	T_CONSTRUCTOR:
		fprintf(stderr, "NEW NEW NEW\n");
		break;
	default:
		fatal("print_type");
	}
} /* end print_type */

void
print_list(TypeList *list)
{
	TypeList *s;
	for (s = list; s; s = s -> tail)
		print_type(s -> head.type);
} /* end print_type_schemes */

void
print_type_scheme(TypeScheme *scheme)
{
	if (scheme == Nil(TypeScheme)) return;
	print_type(scheme -> type);
	print_list(scheme -> list);
	/*TypeConstraint *constraint;*/
	print_type_scheme(scheme -> result);
} /* end print_type_scheme */

void
print_type_schemes(TypeList *list)
{
	TypeList *s;
	for (s = list; s; s = s -> tail)
		print_type_scheme(s -> head.scheme);
} /* end print_type_schemes */

min_depth(Type *var)
{
	switch (var -> family) {
	case T_VAR:
		switch (var -> u.variable -> kind) {
		case K_INSTANCE:
			return(min_depth(var -> u.variable -> instance));
		case K_QUANTIFIER:
			return(var -> u.variable -> depth);
		default:
			fatal("unknown kind in min_depth");
		} /* end switch kind */
	case T_BASE:
		return(MAXDEPTH);
	case T_ARROW:
		return(min(min_depth(var -> u.function.left), min_depth(var -> u.function.right)));
	default:
		fatal("unknown family in min_depth");
	} /* end switch */
} /* end min_depth */

void
adjust_depth(Type *var, int depth)
{
	switch (var -> family) {
	case T_VAR:
		switch (var -> u.variable -> kind) {
		case K_INSTANCE:
			adjust_depth(var -> u.variable -> instance, depth);
			break;
		case K_QUANTIFIER:
			if (depth < var -> u.variable -> depth)
				var -> u.variable -> depth = depth;
			break;
		default:
			fatal("unknown kind in adjust_depth");
		} /* end switch kind */
	case T_BASE:
		return;
	case T_ARROW:
		adjust_depth(var -> u.function.left, depth);
		adjust_depth(var -> u.function.right, depth);
		break;
	default:
		fatal("unknown family in adjust_depth");
	} /* end switch */
} /* end adjust_depth */

int
same_type(Type *exp1, Type *exp2)
{
	return(exp1 == exp2 ? 1 : 0);
} /* end same_type */

Type *
prune(Type *exp)
{
	if (exp == Nil(Type)) return(exp);
fprintf(stderr, "prune ");
print_type(exp);
	switch (exp -> family) {
	case T_VAR:
		switch (exp -> u.variable -> kind) {
		case K_INSTANCE:
			if (exp -> u.variable -> instance != Nil(Type)) {
				exp -> u.variable -> instance = prune(exp -> u.variable -> instance);
fprintf(stderr, " returns ");
print_type(exp -> u.variable -> instance);
				return(exp -> u.variable -> instance);
			} /* end else */
			else	return(exp);
			break;
		case K_QUANTIFIER:
			return(exp);
			break;
		default:
			fatal("unknown kind in prune");
		} /* end switch kind */
	case T_ANY:
	case T_BASE:
		return(exp);
	case T_ARROW:
		return(new_fn_type(prune(exp -> u.function.left),
			prune(exp -> u.function.right)));
		break;
	default:
		fatal("unknown family in prune");
	} /* end switch */
} /* end prune */

TypeList *
free_vars_in_scheme(TypeScheme *scheme)
{
	fatal("... in free vars in scheme");
} /* end free_vars_in_scheme */

TypeList *
generics(Type *type, int depth, TypeList *list)
{
	TypeList *result;
	if (type == Nil(Type)) return(list);
	switch (type -> family) {
	case T_VAR:
		switch (type -> u.variable -> kind) {
		case K_INSTANCE:
			return(generics(type -> u.variable -> instance, depth, list));
		case K_QUANTIFIER:
			if (depth < type -> u.variable -> depth) {
				result = new_typelist();
				result -> head.type = type;
				result -> tail = list;
				return(result);
			} /* end if */
			else	return(list);
		default:
			fatal("unknown kind in generics");
		} /* end switch kind */
	case T_BASE:
		return(list);
	case T_ARROW:
		result = generics(type -> u.function.left, depth, list);
		result = generics(type -> u.function.right, depth, result);
		return(result);
		break;
	default:
		fatal("unknown family in generics");
	} /* end switch */
} /* end generics */

TypeScheme *
close_type(Type *type, int depth)
{
	TypeScheme *scheme;
	TypeList *list;
	list = generics(type, depth, Nil(TypeList));
fatal("in close type");
/***	scheme = new_type_scheme(type, list);	***/
	return(scheme);
} /* end close_type */

int
occurs_in_type(TypeVar *var, Type *type)
{
	switch (type -> family) {
	case T_VAR:
		switch (type -> u.variable -> kind) {
		case K_INSTANCE:
			return(occurs_in_type(var, type -> u.variable -> instance));
		case K_QUANTIFIER:
			return((type -> u.variable == var) ? 1 : 0);
		default:
			fatal("unknown kind in occurs_in_type");
		} /* end switch kind */
	case T_BASE:
		return(0);
	case T_ARROW:
		return(occurs_in_type(var, type -> u.function.left) ||
			occurs_in_type(var, type -> u.function.right));
	default:
		fatal("unknown family in occurs_in_type");
	} /* end switch */
} /* end occurs_in_type */

int
unify_failure(Type *left, Type *right)
{
	print_type(left);
	print_type(right);
	fatal("Can't unify.");
	return(0);
} /* end unify_failure */

int
unify_var_with_type(TypeVar *var, Type *type)
{
	switch(var -> kind) {
	case K_INSTANCE:
		return(unify_type(var -> instance, type));
	case K_QUANTIFIER:
		if (occurs_in_type(var, type))
			return(unify_failure(Nil(Type), type));
		if (var -> depth < min_depth(type))
			adjust_depth(type, var -> depth);
		var -> kind = K_INSTANCE;
		var -> instance = type;
		return(1);
	default:
		fatal("unknown kind in unify_var_with_type");
	} /* end switch kind */
} /* end unify_var_with_type */

int
unify_vars(TypeVar *var1, TypeVar *var2)
{
	int kind1 = var1 -> kind;
	int kind2 = var2 -> kind;
	switch (kind1) {
	case K_INSTANCE:
		return(unify_var_with_type(var2, var1 -> instance));
	case K_QUANTIFIER:
		if (var1 -> depth <
		    var2 -> depth)
			var2 -> kind = var1 -> kind;
		else	var1 -> kind = var2 -> kind;
		return(1);
	default:
		fatal("unknown kind in occurs_in_type");
	} /* end switch kind */
} /* end unify_vars */

int
unify_type(Type *typeExp1, Type *typeExp2)
{
	if (debug['T']) {
		fprintf(stderr, "in unify_type(");
		print_type(typeExp1);
		fprintf(stderr, ",");
		print_type(typeExp2);
		fprintf(stderr, ")\n");
	} /* end if debug */
	if (typeExp1 == Nil(Type)) return(0);
	else
	if (typeExp2 == Nil(Type)) return(0);
	if (typeExp1 -> family == T_ANY) return(1);
	else
	if (typeExp2 -> family == T_ANY) return(1);
	typeExp1 = prune(typeExp1);
	typeExp2 = prune(typeExp2);
	switch(typeExp1 -> family) {
	case T_VAR:
		if (typeExp2 -> family == T_VAR)
			if (typeExp1 == typeExp2) return(1);
			else return(unify_vars(typeExp1 -> u.variable, typeExp2 -> u.variable));
		else	return(unify_var_with_type(typeExp1 -> u.variable, typeExp2));
		break;
	case T_BASE:
		if (typeExp2 -> family == T_BASE)
			if (typeExp1 == typeExp2) return(1);
			else break;
		else
		if (typeExp2 -> family == T_VAR)
			return(unify_var_with_type(typeExp2 -> u.variable, typeExp1));
		break;
	case T_ARROW:
		if (typeExp2 -> family == T_ARROW)
			return(unify_type(typeExp1 -> u.function.left,
				typeExp2 -> u.function.left) &&
				unify_type(typeExp1 -> u.function.right,
				typeExp2 -> u.function.right));
		else
		if (typeExp2 -> family == T_VAR)
			return(unify_var_with_type(typeExp2 -> u.variable, typeExp1));
		break;
	default:
		fatal("unknown family in unify_type");
	} /* end switch exp1 -> family */
	unify_failure(typeExp1, typeExp2);
	return(0);
} /* end unify_type */

TypeList *
fresh_list(TypeList *list)
{
	TypeList *p;
	fatal("in fresh_list");
/*	for (p=list; p; p = p -> tail)
		if (isbound(p -> head)) p -> head = fresh_type_var(MAXDEPTH);
	return(list);*/
} /* end fresh_list */

Type *
function_type(Type *domain, Type *codomain)
{
	Type *new;
	new = new_type_exp(T_ARROW);
	new -> u.function.left = domain;
	new -> u.function.right = codomain;
	return(new);
} /* end function_type */

void
type_fn_def(Node *root, int depth)
{
	int arity;
	Node *id, *arglist;
	id = Left(root);
	arglist = Right(root);
	if (id -> symbol && id -> symbol -> cell) {
		arity = (id -> symbol) ?
			id -> symbol -> cell -> cell.function -> arity : 0;
		if (arity && arity != tree_length(arglist))

			warn("function arity miscount", 0);
	}
	id -> symbol -> type = extend_list(new_type_var_scheme(fresh_type_var(depth, id -> symbol)),
		id -> symbol -> type);
} /* end type_fn_def */

Type *
newinst(TypeScheme *scheme, int depth)
{
	TypeVar *binder;
	TypeScheme *new;
	if (!scheme -> list) return(scheme -> type);
	fatal("subst in newinst");
} /* end newinst */

TypeScheme *
generalize_type(Type *type)
{
	TypeScheme *result;
	switch (type -> family) {
	case T_VAR:
		switch (type -> u.variable -> kind) {
		case K_INSTANCE:
			break;
		default:
			fatal("unknown kind in generalize_type");
		} /* end switch kind */
		break;
	case T_BASE:
	case T_ANY:
		result = new_type_scheme(type, Nil(TypeList));
		return(result);
	} /* end switch family */
	fatal("unknown family in generalize_type");
} /* end generalize */

Type *
skolemize(TypeScheme *scheme)
{
	if (!scheme -> list) return(scheme -> type);
	fatal("subst in skolemize");
} /* end skolemize */

void
instantiate_op(Instance *instance, int depth)
{
	while (instance) {
fprintf(stderr, "instantiate %x\n", instance);
		instance = instance -> chain;
	} /* end while */
} /* end instantiate_op */


void
type_op(Node *root, int depth)
{
	Symbol *symbol;
	Instance *instance;
	symbol = root -> bucket -> symbols;
	if (symbol) {
		instance = symbol -> cell -> cell.instance;
		if (instance)
			(void) instantiate_op(instance, depth);
		else	warn("operator", root -> bucket -> name, "missing instance declaration", 0);
	}
	else	warn("operator", root -> bucket -> name, "unknown", 0);
} /* end type_op */

void
type_check_instance(Node *root, int depth)
{
	Instance *instance, *new_instance;
	TypeScheme *body_schema;
	Type *instance_type, *instance_spec;
	instance = root -> symbol -> cell -> cell.instance;
	if (!type_check(instance -> body, depth)) return;
	body_schema = generalize_type(instance -> body -> type);
	if (instance -> scheme) {
		instance_type = skolemize(instance -> scheme);
		instance_spec = newinst(instance -> scheme, depth);
		instance = root -> symbol -> cell -> cell.instance;
		root -> type = instance -> body -> type; /* default */
		if (instance)
		   for (;instance; instance = instance -> chain)
			if (!same_type(instance -> body -> type,
					body_schema -> type) &&
				unify_type(instance_type, instance_spec))
					fprintf(stderr, "new inst\n");
			else;
		else
			fatal("init inst in type_check_instance");
	} /* end if type declaration */
	else	fprintf(stderr, "new inst\n");
} /* end type_check_instance */

void
type_def(Node *root, int depth)
{
	Node *spec;
	Symbol *symbol;
	if (Right(Right(root)))
		warn("type context ignored.", 0);
	spec = Left(Right(root));
	if (spec) (void) type_check(spec, depth);
	symbol = use_name(Left(root));
	if (symbol -> type &&
	    symbol -> type -> head.scheme -> type -> family == T_BASE)
		warn("base type", Left(root) -> bucket -> name, "type declaration ignored", 0);
	else fatal("O_TYPE type_check");
} /* end type_def */

int
type_check(Node *root, int depth)
{
	Node *left, *right;	
	TypeScheme *binder;
	TypeList *bound_type;
	Type *type_var;
	if (root == Nil(Node)) return(1);
	left = Left(root);
	right = Right(root);
	if (debug['T'])
		fprintf(stderr, "%d %x %s\n", depth, root, op_names[root -> operator]);
	switch (root -> operator) {
	case O_NAME:
		if (root -> symbol -> type)
			root -> type = fresh_type_scheme(root -> symbol -> type -> head.scheme);
		else {
			binder = new_type_var_scheme(fresh_type_var(depth, root -> symbol));
			root -> type = binder -> type;
		} /* end if found */
		break;
	case O_ID:
/***/ if (root -> symbol) fprintf(stderr, "Found %s\n", root -> bucket -> name);
		if (root -> symbol && root -> symbol -> type)
			root -> type = root -> symbol -> type -> head.type;
		else
			warn(root -> bucket -> name, "undeclared", 0);
		break;
	case O_IF:
		(void) type_check(left, depth);
		if (!unify_type(left -> type, bool_type)) {
			warn("if term not boolean", 0);
			break;
		} /* end if */
		(void) type_check(right, depth);
		if (unify_type(left -> type, right -> type))
			root -> type = left -> type; /* or else */
		break;
	case O_LAMBDA:
/***/		print_tree(root);
		binder = new_type_var_scheme(fresh_type_var(depth+1, new_polymorphic_name()));
		(void) type_check(right, depth+1);
		root -> type = function_type(prune(binder -> type), right -> type);
		break;
	case O_APPLY:
		(void) type_check(left, depth);
		(void) type_check(right, depth);
		type_var = new_type_var(fresh_type_var(depth, new_polymorphic_name()));
		if (left -> type && right -> type)
			if (unify_type(left -> type, function_type(right -> type, type_var)))
				root -> type = prune(type_var);
		break;
	case O_LET:
		print_tree(root);
		fatal("O_LET type check");
		type_check(right, depth);
	case O_LIST: /* unary */
		break;
	case O_TILDE:
	case O_CONNECT:
	case O_ASSOC:
	case O_PATTERN:
	case O_DESIGNATOR:
		fprintf(stderr, "unary op %d\n", root -> operator);
		type_check(left, depth);
		break;
	case O_NULL: /* nullary */
		break;
	case O_INT:
		root -> type = int_type;
		break;
	case O_FLOAT:
		root -> type = float_type;
		break;
	case O_CHAR:
		root -> type = char_type;
		break;
	case O_STRING:
		root -> type = string_type;
		break;
	case O_WILDCARD:
	case O_MINUS:
		break;
	case O_OP:
		(void) type_op(root, depth);
		break;
	case O_SEMI:
		(void) type_check(left, depth);
		(void) type_check(right, depth);
		if (unify_type(left -> type, right -> type))
			root -> type = left -> type;
		break;
	case O_VALUE_DEF:
		if (left -> operator == O_APPLY) {
			(void) type_fn_def(left, depth);
/***/			(void) type_check(Right(left), depth);
			(void) type_check(right, depth);
			root -> type = left -> type;
			break;
		} /* fn def */
		else 
		if (left -> operator == O_NAME) {
			(void) type_check(right, depth);
			root -> type = right -> type;
		} /* name def */
		else
			fatal("VAL_DEF type check (non fn)");
		break;
	case O_RHS:
		(void) type_check(right, depth); /* where */
		(void) type_check(left, depth);
		root -> type = left -> type;
		break;
	case O_PREDICATE:
		(void) type_check(left, depth);
		(void) type_check(right, depth);
		root -> type = right -> type;
		break;
	case O_WHERE:
		(void) type_check(left, depth);
		root -> type = left -> type;
		break;
	case O_PAIR:
		(void) type_check(left, depth);
		(void) type_check(right, depth);
		if (right && !unify_type(left -> type, right -> type))
			return(0);
		root -> type = left -> type;
		break;
	case O_INSTANCE:
		(void) type_check_instance(root, depth);
		break;
	case O_TYPED:
		(void) type_check(Right(right), depth);
		(void) type_check(Left(right), depth);
	case O_CONTEXT:
		(void) type_check(left, depth);
		break;
	case O_RARROW:
		(void) type_check(left, depth);
		(void) type_check(right, depth);
		root -> type = function_type(left -> type, right -> type);
		break;
	case O_PRIMITIVE:
		root -> type = new_type_exp(T_ANY);
		break;
	case O_TYPE:
		(void) type_def(root, depth);
		break;
	case O_GENERATE:
		type_check(left, depth);
	case O_FOREACH:
		type_check(right, depth);
		root -> type = new_type_exp(T_NO);
		break;
	default: /* binary */
		fprintf(stderr, "type_check default binary op %s\n", op_names[root -> operator]);
		print_tree(root);
		type_check(left, depth);
		type_check(right, depth);
		break;
	} /* end switch */
	return(1);
} /* end type_check */
