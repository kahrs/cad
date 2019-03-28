/*
 * utility routines for t2
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "t2.h"
#include "iges.h"

#define YYSTYPE int
#include "y.tab.h"

#define PARCELSTACKLIMIT 100
struct PARCEL *parcelStack[PARCELSTACKLIMIT];
int callStack[PARCELSTACKLIMIT];

int parcelStackCount = 0;
int callStackCount = 0;
int deCount = 1;

extern int defaultUnits;

#define Abs(x) ((x > 0) ? x : -x)

int LookupString(char *target, char **table, int length);
struct PARCEL *NewParcel(int type);
struct VALUE *NewValue(float value, int units);
void PushParcel(struct PARCEL *theParcel);
struct PARCEL *PopParcel(void);
float PopFloatParcel(void);
float PopFloatUnitsParcel(void);
void PrintParcel(struct PARCEL *theParcel);
struct PARCEL *SearchStack(char *name);
void StackTrace(void);
float ChangeUnits(struct PARCEL *theParcel);
void PushCall(void);
void PopCall(void);

void Bug();
void Trouble();

void EmitDE();

char *strdup();

/*
 * Symbol table stuff
 */

int LookupString(char *string, char *table[], int size)
{
	int i;
	for (i=0; i<size; i++) {
		if (table[i] == NULL) return(-1);
		if (strcmp(string, table[i]) == 0) return(i);
	} /* end for */
	return(-1);
} /* end LookupString */

int HashName(char *name, int tableSize)
{
	int sum = 0;
	char *namePointer;
	namePointer = name;
	while (*namePointer) sum = (sum << 5) + *namePointer++;
	return(Abs(sum) % tableSize);
} /* end HashName */

struct BUCKET *NewBucket(char *name)
{
	struct BUCKET *new;
	new = Struct_alloc(BUCKET);
	new -> name = strdup(name);
	new -> next = Null_struct(BUCKET);
	new -> type = 0;
	return(new);
} /* end NewBucket */

struct BUCKET *Lookup(char *name, struct BUCKET *hashTable[], int size)
{
	int hash;
	struct BUCKET *newBucket, *BUCKETPointer, *lastBucketPointer;
	hash = HashName(name, size);
	if (hashTable[hash] != Null_struct(BUCKET))
	{
		for (BUCKETPointer = hashTable[hash];
		     BUCKETPointer != Null_struct(BUCKET);
		     lastBucketPointer = BUCKETPointer,
		     BUCKETPointer = BUCKETPointer -> next)
			if (strcmp(BUCKETPointer -> name, name) == 0)
			return(BUCKETPointer);
	} /* end if */
	return(Null_struct(BUCKET));
} /* end Lookup */

struct BUCKET *LookupOrEnter(char *name, struct BUCKET *hashTable[], int size)
{
	struct BUCKET *oldBucket, *newBucket;
	int hash;
	oldBucket = Lookup(name, hashTable, size);
	if (oldBucket != Null_struct(BUCKET)) return(oldBucket);
	newBucket = NewBucket(name);
	hash = HashName(name, size);
	if (hashTable[hash] == Null_struct(BUCKET))	
		hashTable[hash] = newBucket;
	else
	{
		newBucket -> next = hashTable[hash];
		hashTable[hash] = newBucket;
	} /* end else */
	return(newBucket);
} /* end LookupOrEnter */

/*
 * parse tree stuff
 */

void
PrintTree(struct NODE *head, int level)
{
	int i;
	if (head == Null_struct(NODE)) return;
	for (i=0; i<level; i++) fprintf(stderr, "  ");
	if (head -> string)
		fprintf(stderr, "%d (%s)\n", head -> operator, head -> string);
	else	fprintf(stderr, "%d\n", head -> operator);
	(void) PrintTree(head -> left, level+1);
	(void) PrintTree(head -> right, level+1);
} /* end PrintTree */

struct NODE *
NullaryNode(int operator)
{
	struct NODE *node;
	node = Struct_alloc(NODE);
	node -> operator = operator;
	node -> left = node -> right = Null_struct(NODE);
	node -> string = (char *) 0;
	return(node);
} /* end NullaryNode */

struct NODE *
UnaryNode(int operator, struct NODE *left)
{
	struct NODE *node;
	node = Struct_alloc(NODE);
	node -> operator = operator;
	node -> left = left;
	node -> right = Null_struct(NODE);
	node -> string = (char *) 0;
	return(node);
} /* end UnaryNode */

struct NODE *
StringNode(int operator, char *string)
{
	struct NODE *node;
	node = Struct_alloc(NODE);
	node -> operator = operator;
	node -> left = node -> right = Null_struct(NODE);
	node -> string = string;
	return(node);
} /* end StringNode */

struct NODE *
BinaryNode(int operator, struct NODE *left, struct NODE *right)
{
	struct NODE *node;
	node = Struct_alloc(NODE);
	node -> operator = operator;
	node -> left = left;
	node -> right = right;
	node -> string = (char *) 0;
	return(node);
} /* end BinaryNode */

char *
CopyString(char *from)
{
	char *to;
	to = strdup(from);
	return(to);
} /* end CopyString */

/*
 * Stack parcel stuff
 */

struct VALUE *NewValue(float value, int units)
{
	struct VALUE *newValue;
	newValue = Struct_alloc(VALUE);
	newValue -> value = value;
	newValue -> units = units;
	return(newValue);
} /* end NewValue */

struct PARCEL *NewParcel(int type)
{
	struct PARCEL *newParcel;
	newParcel = Struct_alloc(PARCEL);
	newParcel -> type = type;
	newParcel -> bound_name = (char *) 0;
	return(newParcel);
} /* end NewParcel */

void PushParcel(struct PARCEL *theParcel)
{
	if (parcelStackCount > PARCELSTACKLIMIT)
		Bug("ParcelStack overflow in PushParcel");
	parcelStack[parcelStackCount++] = theParcel;
} /* end PushParcel */

struct PARCEL *PopParcel()
{
	if (parcelStackCount <= 0)
		Bug("ParcelStack underflow in PopParcel");
	return(parcelStack[--parcelStackCount]);
} /* end PopParcel */

float PopFloatUnitsParcel()
{
	struct PARCEL *theParcel;
	theParcel = PopParcel();
	if (theParcel -> type != VALUE_PARCEL)
		Trouble("floating point constant not found");
	else
	if (theParcel -> ptr.constant -> units == 0)
		if (theParcel -> bound_name)
			Trouble("units not found for %s", theParcel -> bound_name);
		else
			Trouble("units not found for constant %f", theParcel -> ptr.constant -> value);
	else	return(ChangeUnits(theParcel));
	return(0.0);
} /* end PopFloatUnitsParcel */

float PopFloatParcel()
{
	struct PARCEL *theParcel;
	theParcel = PopParcel();
	if (theParcel -> type != VALUE_PARCEL)
		Trouble("floating point constant not found");
	else	return(theParcel -> ptr.constant -> value);
	return(0.0);
} /* end PopFloatParcel */

void PrintParcel(struct PARCEL *theParcel)
{
	int units;
	char *unitString;
	if (theParcel -> bound_name)
		fprintf(stderr, "%s=", theParcel -> bound_name);
	switch (theParcel -> type) {
	case EMPTY_PARCEL:
		fprintf(stderr, "EMPTY");
		break;
	case STRING_PARCEL:
		fprintf(stderr, "\"%s\"", theParcel -> ptr.string);
		break;
	case VALUE_PARCEL:
		units = theParcel -> ptr.constant -> units;
		unitString = (units == IN) ? "inch" :
			(units == FT) ? "feet" :
			(units == MM) ? "mm" :
			(units == CM) ? "cm" :
			(units == M) ? "m" : "(unknown units)";
		fprintf(stderr, "%f(%s)", theParcel -> ptr.constant -> value, unitString);
		break;
	case ENTITY_PARCEL:
		fprintf(stderr, "ENTITY %d", theParcel -> ptr.entity -> type);
		break;
	case DE_PARCEL:
		fprintf(stderr, "DE %d", theParcel -> ptr.de -> type);
		break;
	case POINT_PARCEL:
		fprintf(stderr, "[,,]");
		break;
	case MATERIAL_PARCEL:
		fprintf(stderr, "Material");
		break;
	default:
		fprintf(stderr, "type=%d\n", theParcel -> type);
		Bug("unknown type in PrintParcel");
	} /* end switch */
} /* end PrintParcel */

void PrintEntityTree(struct ENTITY *root, int level)
{
	int i;
	for (i=0; i<level; i++) fprintf(stderr, "    ");
	if (root == Null_struct(ENTITY)) {
		fprintf(stderr, "nil\n");
		return;
	} /* end if */
	switch (root -> type) {
	case IGES_ASSEMBLY:
		fprintf(stderr, "csg assembly:\n");
		PrintEntityTree(root -> entity.csg -> left, level+1);
		PrintEntityTree(root -> entity.csg -> right, level+1);
		break;
	case IGES_CSG:
		fprintf(stderr, "csg operator %d:\n", root -> entity.csg -> operator);
		PrintEntityTree(root -> entity.csg -> left, level+1);
		PrintEntityTree(root -> entity.csg -> right, level+1);
		break;
	case IGES_TRANSFORMATION:
		fprintf(stderr, "transform:\n");
		PrintEntityTree(root -> entity.transformation -> node, level+1);
		PrintEntityTree(root -> entity.transformation -> translation, level+1);
		PrintEntityTree(root -> entity.transformation -> rotation, level+1);
		break;
	case IGES_BLOCK:
		fprintf(stderr, "block(%f, %f, %f)\n",
			root -> entity.block  -> length[0],
			root -> entity.block  -> length[1],
			root -> entity.block  -> length[2]);
		break;
	case IGES_SPHERE:
		fprintf(stderr, "sphere(%f)\n", root -> entity.sphere  -> radius);
		break;
	case IGES_POINT:
		fprintf(stderr, "point(%f,%f,%f)\n",
			root -> entity.point  -> point.vector[0],
			root -> entity.point  -> point.vector[1],
			root -> entity.point  -> point.vector[2]);
		break;
	case IGES_CYLINDER:
		fprintf(stderr, "cylinder(%f, %f)\n",
			root -> entity.cylinder  -> height,
			root -> entity.cylinder  -> radius);
		break;
	default:
		fprintf(stderr, "type=%d\n", root -> type);
		Bug("unknown type in PrintEntity");
	} /* end switch */
	if (root -> properties) {
		for (i=0; i<level; i++) fprintf(stderr, "    ");
		fprintf(stderr, "properties->%p\n", root -> properties);
	} /* end for */
} /* end PrintEntity */

struct PARCEL *SearchStack(char *name)
{
	int offset;
	if (parcelStackCount != 0)
	    for(offset=parcelStackCount-1; offset >=callStack[callStackCount-1]; offset--)
		if (parcelStack[offset] -> bound_name)
			if (strcmp(name, parcelStack[offset] -> bound_name) == 0)
				return(parcelStack[offset]);
	return(NewParcel(EMPTY_PARCEL));
} /* end SearchStack */

int BindNameToParcel(char *name)
{
	int offset;
	for (offset=callStack[callStackCount-1]; offset <parcelStackCount; offset++)
		if ((parcelStack[offset] -> type == VALUE_PARCEL) &&
			(parcelStack[offset] -> bound_name == NULL)) {
			parcelStack[offset] -> bound_name = strdup(name);
			return(offset);
		} /* end if */
	return(-1);
} /* end BindNameToParcel */

void PushCall(void)
{
	callStack[callStackCount++] = parcelStackCount;
} /* end PushCall */

void PopCall(void)
{
	if (callStackCount == 0)
		Bug("Call stack underflow!");
	parcelStackCount = callStack[--callStackCount];
} /* end PopCall */

void StackTrace()
{
	int i, j, k, top;
	for (i=0; i< callStackCount; i++) {
		for (k=0; k<i; k++) fprintf(stderr, "\t");
		fprintf(stderr, "[");
		top =  (i == callStackCount-1) ? parcelStackCount : callStack[i+1];
		for (j=callStack[i]; j < top; j++) {
			PrintParcel(parcelStack[j]);
			fprintf(stderr, ",");
		} /* end for */
		fprintf(stderr, "]\n");
	} /* end for */
} /* end StackTrace */

float ChangeUnits(struct PARCEL *theParcel)
{
	float value = theParcel -> ptr.constant -> value;
	if (defaultUnits == theParcel -> ptr.constant -> units)
		return(value);
	switch (theParcel -> ptr.constant -> units) {
	case IN:
		switch (defaultUnits) {
		case FT:	value /= 12; break;
		case MM:	value *= 25.4; break;
		case CM:	value *= 2.54; break;
		case M:	value *= 0.0254; break;
		} /* end switch */
		break;
	case FT:
		switch (defaultUnits) {
		case IN:	value *= 12; break;
		case MM:	value *= 304.8; break;
		case CM:	value *= 30.48; break;
		case M:	value *= 0.0254; break;
		} /* end switch */
		break;
	case MM:
	case CM:
	case M:
		Trouble("metric unit conversion not implemented");
		break;
	} /* end switch */
	return(value);
} /* end ChangeUnits */

int CheckUnits(struct PARCEL *left, struct PARCEL *right)
{
	if (left -> type != VALUE_PARCEL || right -> type != VALUE_PARCEL) {
		Trouble("type mismatch in arithmetic op");
		return 0;
	} /* end if */
	if (left -> ptr.constant -> units == right -> ptr.constant -> units)
		return(left -> ptr.constant -> units);
	Trouble("units mismatch in arithmetic op");
	return(0);
} /* end CheckUnits */

float CheckFloat(struct PARCEL *theParcel)
{
	if (theParcel -> type != VALUE_PARCEL)
		Trouble("floating point constant not found");
	else	return(theParcel -> ptr.constant -> value);
	return(0.0);
} /* end CheckFloat */

float CheckFloatUnits(struct PARCEL *theParcel)
{
	if (theParcel -> type != VALUE_PARCEL) {
		PrintParcel(theParcel);
		Bug("floating point constant with units not found");
}
	else
	if (theParcel -> ptr.constant -> units == 0)
		if (theParcel -> bound_name)
			Trouble("units not found for %s", theParcel -> bound_name);
		else
			Trouble("units not found for constant %f", theParcel -> ptr.constant -> value);
	else	return(ChangeUnits(theParcel));
	return(0.0);
} /* end CheckFloatUnits */

void CheckType(struct PARCEL *parcel, int type)
{
	if (parcel -> type != type) {
		PrintParcel(parcel);
		Bug("Types don't agree");
	}
} /* end CheckType */

struct DE *NewDE(int type, int parameter, int count, int form, int transform)
{
	struct DE *theDE;
	theDE = Struct_alloc(DE);
	theDE -> type = type;
	theDE -> parameter = parameter;
	theDE -> count = count;
	theDE -> form = form;
	theDE -> label = (char *) 0;
	theDE -> transformation = transform;
	theDE -> subscript = deCount;
	EmitDE(theDE);
	return(theDE);
} /* end NewDE */
