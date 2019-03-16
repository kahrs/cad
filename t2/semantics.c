#include <stdio.h>
#include <string.h>
#include "stdarg.h"
#include "y.tab.h"
#include "t2.h"
#include "iges.h"

#ifndef PI
#define PI	3.1415926535897932384626433832795028841971693993751
#endif

extern int TFlag;
extern int parcelStackCount;
extern int bindTop;
extern int sequence;

char stringBuffer[128];
int integerConstant;
float floatingConstant;
int defaultUnits = IN;

struct BUCKET *symbolHashTable[SYMBOLSIZE];

char *globalConstants[MAXGLOBALS];

struct NODE *materialName;
struct NODE *propertyName;

char *globalStrings[] = { "comment", "units", "title", "author", "organization" };
int globalCodes[] = { 0, 15, 3, 21, 22 };
int globalFlag = 0;
#define NGLOBALS 5

char *unitsStringTable[] = { "mm", "cm", "m", "in", "ft" };
int unitsTable[] = { MM, CM, M, IN, FT };
#define MAXUNITS 5

char *formStringTable[] = { "youngs_modulus", "poissons_modulus",
"shear_modulus", "material_matrix", "mass_density", "thermal_expansion",
"stiffness_matrix", "bending_matrix", "transverse_shear", "coupling",
"coordinate_system", "nodal_load", "sectional_properties", "beam_end",
"offsets", "stress_recovery", "element_thickness", "nonstructural_mass",
"thermal_conductivity", "heat_capacity", "convective_coefficient", "radiation" };
#define MAXFORMS 22

char *radiationTable[] = { "absorptivity", "transmissivity", "reflectivity", "emissivity", 0 };

char *capacityTable[] = { "absorptivity", "transmissivity", "reflectivity", "emissivity", 0 };

char **formIndirectTable[] =
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, capacityTable, 0, radiationTable };

void PrintTree(struct NODE *head, int level);
void EvalObject(struct NODE *id, struct NODE *object);
struct PARCEL *EvalParseTree(struct NODE *root);
struct PARCEL *EvalBooleanOp(int op, struct PARCEL *left, struct PARCEL *right);
struct PARCEL *EvalArithmeticOp(int op, struct PARCEL *left, struct PARCEL *right);
struct PARCEL *NewPoint(struct NODE *root,  int flag);
struct PARCEL *CallInstance(struct NODE *id, struct NODE *root);
struct PARCEL *EvalConstant(struct NODE *constant);
void EvalConstructionPlan(struct NODE *root);
void DefineParameters(struct NODE *id, struct NODE *root);
void CheckTerminal(struct PARCEL *node, int terminalType);
struct PARCEL *NewCSG(int operator, struct PARCEL *left, struct PARCEL *right);

struct PARCEL *NewCylinder(struct NODE *root);
struct PARCEL *NewBlock(struct NODE *root);
struct PARCEL *NewSphere(struct NODE *root);
struct PARCEL *NewInstance(struct NODE *root, struct NODE *modifier);
struct PARCEL *Terminal(struct NODE *root);
struct PARCEL *NewProperty(int type, int size, float values[]);
struct MATERIAL_VALUES *NewMaterialValue(struct PARCEL *parcel);
int LookupString(char *target, char **table, int length);
struct BUCKET *Lookup(char *name, struct BUCKET *hashTable[], int size);
struct BUCKET *LookupOrEnter(char *name, struct BUCKET *hashTable[], int size);
struct PARCEL *NewParcel(int type);
struct VALUE *NewValue(float value, int units);
void PushParcel(struct PARCEL *theParcel);
struct PARCEL *PopParcel(void);
float PopFloatParcel(void);
float PopFloatUnitsParcel(void);
void PrintParcel(struct PARCEL *theParcel);
struct PARCEL *SearchStack(char *name);
void StackTrace(void);
int CheckUnits(struct PARCEL *left, struct PARCEL *right);
float CheckFloatUnits(struct PARCEL *theParcel);
float CheckFloat(struct PARCEL *theParcel);
void CheckType(struct PARCEL *parcel, int type);
struct PARCEL *DoFor(struct NODE *left, struct NODE *right);
struct PARCEL *NewRange(struct NODE *left, struct NODE *right, float step);
struct PARCEL *NewBinding(struct NODE *left, struct NODE *right);

void SaveGlobal(int index, struct PARCEL *theParcel);
void EmitGlobals(void);
struct DE *EmitEntity(int type, int form, int count, float f1, float f2, float f3, float f4, ...);
struct DE *EmitPointerEntity(int type, int transform, int count, int p1, ...);
void EmitLines(void);

char *strdup();

void EvalEntityTree(struct ENTITY *root, void (*proc)())
{
	if (root == Null_struct(ENTITY)) return;
	switch (root  -> type) {
	case IGES_TRANSFORMATION:
		(*proc)(root);
		break;
	default:
		Bug("\nunknown type in EvalEntityTree");
	} /* end switch */
} /* end EvalEntityTree */

struct PARCEL *EvalParseTree(struct NODE *root)
{
	struct PARCEL *theParcel;
	struct BUCKET *theBucket;
	if (root == Null_struct(NODE)) return(Null_struct(PARCEL));
	switch (root -> operator) {
	case 0:
		Bug("Null operator in EvalParseTree");
	case COMPOUND:
		EvalParseTree(root -> left);
		EvalParseTree(root -> right);
		break;
	case TUPLE:
		PushParcel(EvalParseTree(root -> left));
		EvalParseTree(root -> right);
		break;
	case PROPERTY:
		return(EvalParseTree(root -> left));
	case LT:
	case LE:
	case EQ:
	case GE:
	case GT:
	case NE:
		return(EvalBooleanOp(root -> operator, EvalParseTree(root->left), EvalParseTree(root->right)));
	case '+':
	case '-':
	case '*':
	case '/':
	case EXP:
	case UMINUS:
		return(EvalArithmeticOp(root -> operator, EvalParseTree(root->left), EvalParseTree(root->right)));
		break;
	case AT:
		return(NewPoint(root -> left,  1));
	case CONSTANT:
		return(EvalConstant(root));
	case ID:
		theBucket = Lookup(root -> string, symbolHashTable, SYMBOLSIZE);
		if (theBucket == Null_struct(BUCKET))
			Trouble("%s not found", root -> string);
		else
		switch(theBucket -> type) {
			case VARIABLE_BUCKET:
				theParcel = SearchStack(root -> string);
				break;
			case MATERIAL_BUCKET:
				theParcel = NewParcel(MATERIAL_PARCEL);
				theParcel -> ptr.material = theBucket -> contents.material;
				break;
			default:
				fprintf(stderr, "type=%d\n", theBucket -> type);
				Bug("unknown type in ID case");
		} /* end switch */
		return(theParcel);
		break;
	case INTERSECT:
	case UNION:
	case DIFFERENCE:
	case ASSEMBLY:
		return(NewCSG(root -> operator, EvalParseTree(root -> left), EvalParseTree(root -> right)));
	case ROTATE:
		return(NewCSG(root -> operator, EvalParseTree(root -> left), NewPoint(root -> right,  0)));
	case TERMINAL:
		return(Terminal(root));
	case CYLINDER:
		if (root -> right) Bug("non nil right in EvalParseTree: CYLINDER");
		return(NewCylinder(root -> left));
	case BLOCK:
		if (root -> right) Bug("non nil right in EvalParseTree: BOX");
		return(NewBlock(root -> left));
		break;
	case SPHERE:
		if (root -> right) Bug("non nil right in EvalParseTree: SPHERE");
		return(NewSphere(root -> left));
		break;
	case CALL:
		return(NewInstance(root -> left, root -> right));
	case OBJECT:
		if (root -> left) Bug("non nil left in EvalParseTree: OBJECT");
		return(EvalParseTree(root -> right));
		break;
	case FOR:
		return(DoFor(root -> left, root -> right));
		break;
	case BIND:
		return(NewBinding(root -> left, root -> right));
		break;
	case UPTO:
		return(NewRange(root -> left, root -> right, 1.0));
		break;
	case DOWNTO:
		return(NewRange(root -> left, root -> right, -1.0));
		break;
	case IF:
		EvalParseTree(root -> left);
		EvalParseTree(root -> right);
		break;
	default:
		PrintTree(root, 0);
		fprintf(stderr, "operator=%d\n", root -> operator);
		Bug("unknown operator in EvalParseTree");
	} /* end switch */
	return(Null_struct(PARCEL));
} /* end EvalParseTree */

struct PARCEL *EvalBooleanOp(int op, struct PARCEL *left, struct PARCEL *right)
{
	struct PARCEL *result;
	StackTrace();
	fprintf(stderr, "boolean %d\n", op);
	Bug("unknown op in EvalBooleanOp");
	return(result);
} /* end EvalBooleanOp */

struct PARCEL *EvalArithmeticOp(int op, struct PARCEL *left, struct PARCEL *right)
{
	struct PARCEL *result;
	int units;
	float value;
	units = CheckUnits(left, right);
	switch (op) {
	case '+':
		value = left -> ptr.constant -> value +
			right -> ptr.constant -> value;
		break;
	default:
		Bug("unknown op in EvalArithmeticOp");
	} /* end switch */
	result = NewParcel(VALUE_PARCEL);
	result -> ptr.constant = NewValue(value, units);
	return(result);
} /* end EvalArithmeticOp */

struct PARCEL *EvalConstant(struct NODE *constant)
{
	struct PARCEL *parcel;
	float floatvalue;
	switch (constant -> left -> operator) {
	case FLOAT:
		parcel = NewParcel(VALUE_PARCEL);
		sscanf(constant -> left -> string, "%f", &floatvalue);
		parcel -> ptr.constant = NewValue(floatvalue, 0);
		if (constant -> right != Null_struct(NODE))
			parcel -> ptr.constant -> units = constant -> right -> operator;
		break;
	case STRING:
		parcel = NewParcel(STRING_PARCEL);
		parcel -> ptr.string = strdup(constant -> left -> string);
		break;
	default:
		fprintf(stderr, "op=%d\n", constant -> left -> operator);
		Bug("unknown constant operator in EvalConstant");
	} /* end switch */
	return(parcel);
} /* end EvalConstant */

struct PARCEL *NewInstance(struct NODE *root, struct NODE *parameters)
{
	struct BUCKET *theBucket;
	struct PARCEL *location;
	struct PARCEL *property;
	struct PARCEL *retval;
	char *id;
	id = root -> string;
	theBucket = Lookup(id, symbolHashTable, SYMBOLSIZE);
	if (theBucket == Null_struct(BUCKET))
		Trouble("definition of %s not found", id);
	else
	switch (theBucket -> type) {
	case VARIABLE_BUCKET:
		if (TFlag) fprintf(stderr, "Call object %s\n", id);
		PushCall();
		EvalParseTree(parameters);
		retval = CallInstance(root, theBucket -> contents.pointer);
		PopCall();
		break;
	default:
		Trouble("Can't call a non object: %s", id);
	} /* end switch */
	return(retval);
} /* end NewInstance */

struct PARCEL *NewBinding(struct NODE *left, struct NODE *right)
{
	struct PARCEL *rangeParcel;
	rangeParcel = EvalParseTree(right);
	rangeParcel -> bound_name = strdup(left -> string);
	return(rangeParcel);
} /* end NewBinding */

struct PARCEL *DoFor(struct NODE *left, struct NODE *right)
{
	struct PARCEL *result;
	struct BINDING *binding;
/***	int from, to, step;
	binding = EvalParseTree(left) -> ptr.binding;
	from = binding -> first -> ptr.constant -> value;
	to = binding -> second -> ptr.constant -> value;
	step = binding -> step -> ptr.constant -> value;
	for (var=from; var<from; var+=step) {
		binding -> ;
		EvalParseTree(right);
	} /* end for */
} /* end DoFor */

struct PARCEL *NewRange(struct NODE *left, struct NODE *right, float step)
{
	struct PARCEL *newParcel, *leftParcel, *rightParcel;
	struct BINDING *newBinding;
	newParcel = NewParcel(BINDING_PARCEL);
	newBinding = Struct_alloc(BINDING);
	leftParcel = EvalParseTree(left);
	rightParcel = EvalParseTree(right);
	if (leftParcel -> type != VALUE_PARCEL)
		Trouble("from not a value");
	if (rightParcel -> type != VALUE_PARCEL)
		Trouble("to not a value");
	newBinding -> first = leftParcel -> ptr.constant;
	newBinding -> second = rightParcel -> ptr.constant;
	newBinding -> step = NewValue(step, 0);
	return(newParcel);
} /* end NewRange */

void DefineParameters(struct NODE *id, struct NODE *root)
{
	struct BUCKET *theBucket;
	int newTop;
	if (root == Null_struct(NODE)) return;
	theBucket = LookupOrEnter(root -> left -> string, symbolHashTable, SYMBOLSIZE);
	if (theBucket -> type == MATERIAL_BUCKET)
		Trouble("%s already used as a material", root -> string);
	else
	if (theBucket -> type == CONSTANT_BUCKET)
		Trouble("%s already used as a constant", root -> string);
	else
		theBucket -> type = VARIABLE_BUCKET;
	newTop = BindNameToParcel(root -> left -> string);
	if (newTop == -1) {
		Trouble("Inside %s: ", id -> string);
		Trouble("%s can't be bound; not enough parameters supplied",root -> left -> string);
	} /* end if */
	DefineParameters(id, root -> right);
} /* end DefineParameters */

struct PARCEL *CallInstance(struct NODE *id, struct NODE *root)
{
	DefineParameters(id, root -> left);
	return(EvalParseTree(root -> right));
} /* end CallInstance */

void DeclareMaterial(struct NODE *node, struct MATERIAL_VALUES *material)
{
	struct BUCKET *theBucket;
	if (node == Null_struct(NODE)) return;
	theBucket = LookupOrEnter(node -> string, symbolHashTable, SYMBOLSIZE);
	if (theBucket -> type != EMPTY_BUCKET) {
		Trouble("symbol %s already declared", node -> string);
		return;
	} /* end if */
	theBucket -> type = MATERIAL_BUCKET;
	theBucket -> contents.material = material;
} /* end DeclareMaterial */

struct MATERIAL_VALUES *PatchProperties(struct MATERIAL_VALUES *left, struct MATERIAL_VALUES *right)
{
	right -> chain = left;
	return(right);
} /* end PatchProperties */

struct MATERIAL_VALUES *DeclareProperty(struct NODE *node, struct PROPERTY_VALUE *properties)
{
	int index, ptype, psize;
	float values[MAXVALUES];
	ptype = LookupString(node -> string, formStringTable, MAXFORMS);
	if (ptype == -1) {
		Trouble("property form %s not found", node -> string);
		return(Null_struct(MATERIAL_VALUES));
	} /* end if */
	for (psize=0; (formIndirectTable[ptype])[psize]; psize++);
	while (properties) {
		index = LookupString(properties -> name, formIndirectTable[ptype], psize);
		if (index == -1)
			Trouble("property variable %s not found", properties -> name);
		else values[index] = properties -> value;
		properties = properties -> chain;
	} /* end while */
	return(NewMaterialValue(NewProperty(ptype, psize, values)));
} /* end DeclareProperty */

struct PROPERTY_VALUE *PatchManifests(struct PROPERTY_VALUE *left, struct PROPERTY_VALUE *right)
{
	right -> chain = left;
	return(right);
} /* end PatchManifests */

struct PROPERTY_VALUE *DeclareManifest(char *name, struct NODE *value)
{
	float convertedValue;
	struct PROPERTY_VALUE *property;
	if (value -> operator != FLOAT)
		Trouble("float constant expected");
	else {
		property = Struct_alloc(PROPERTY_VALUE);
		sscanf(value -> string, "%f", &convertedValue);
		property -> name = strdup(name);
		property -> value = convertedValue;
		property -> chain = Null_struct(PROPERTY_VALUE);
		return(property);
	} /* end else */
	return(Null_struct(PROPERTY_VALUE));
} /* end DeclareManifest */

void DeclareGlobal(char *name, struct NODE *value)
{
	int index;
	if (value -> operator != STRING) {
		Trouble("string constant expected for global %s", name);
		return;
	} /* end if */
	index = LookupString(name, globalStrings, NGLOBALS);
	if (index != -1) {
		globalConstants[globalCodes[index]] = value -> string;
		switch (globalCodes[index]) {
		case GLOBAL_UNITS:
			index = LookupString(value -> string, unitsStringTable, MAXUNITS);
			if (index == -1) Trouble("global units not found");
			else defaultUnits = unitsTable[index];
		} /* end switch */
	} /* end if */
	else Trouble("global string %s not found", name);
} /* end DeclareGlobal */

void DeclareObject(struct NODE *name, struct NODE *csg)
{
	struct BUCKET *theBucket;
	if (name == Null_struct(NODE)) Bug("null variable in DeclareObject");
	theBucket = LookupOrEnter(name -> string, symbolHashTable, SYMBOLSIZE);
	theBucket -> type = VARIABLE_BUCKET;
	theBucket -> contents.pointer = csg;
} /* end DeclareObject */

struct MATERIAL_VALUES *CopyProperty(struct MATERIAL_VALUES *old)
{
	struct MATERIAL_VALUES *newMaterial;
	newMaterial = Struct_alloc(MATERIAL_VALUES);
	newMaterial -> chain = Null_struct(MATERIAL_VALUES);
	newMaterial -> entity = old -> entity;
	return(newMaterial);
} /* end CopyProperty */

struct MATERIAL_VALUES *CloneAppendedLists(struct MATERIAL_VALUES *a, struct MATERIAL_VALUES *b)
{
	struct MATERIAL_VALUES *start, *current, *new;
	start = Null_struct(MATERIAL_VALUES);
	current = Null_struct(MATERIAL_VALUES);
	while (a) {
		new = CopyProperty(a);
		if (current) current -> chain = new;
		else start = new;
		current = new;
		a = a -> chain;
	} /* end while */
	while (b) {
		new = CopyProperty(b);
		if (current) current -> chain = new;
		else start = new;
		current = new;
		b = b -> chain;
	} /* end while */
	return(start);
} /* end CloneAppendedLists */
