#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stdarg.h"
#include "y.tab.h"
#include "t2.h"
#include "iges.h"

struct BUCKET *symbolHashTable[SYMBOLSIZE];

void PrintTree(struct NODE *head, int level);
struct PARCEL *EvalParseTree(struct NODE *root);
struct PARCEL *NewEntityParcel(struct ENTITY *entity);
struct PARCEL *NewParcel(int type);
struct BUCKET *Lookup(char *name, struct BUCKET *hashTable[], int size);

float CheckFloatUnits();
float CheckFloat();

struct PARCEL *NewEntityParcel(struct ENTITY *entity)
{
	struct PARCEL *new;
	new = NewParcel(ENTITY_PARCEL);
	new -> ptr.entity = entity;
	return(new);
} /* end NewEntityParcel */

struct ENTITY *NewEntity(int type, int form, int count)
{
	va_list ap;
	struct ENTITY *new;
	int i;
	new = Struct_alloc(ENTITY);
	new -> type = type;
	new -> form = form;
	new -> count = count;
	new -> de = Null_struct(DE);
	new -> properties = Null_struct(MATERIAL_VALUES);
	return(new);
} /* end NewEntity */

struct PARCEL *NewCylinder(struct NODE *root)
{
	float radius, height;
	struct ENTITY *new;
	int i;
	height = CheckFloatUnits(EvalParseTree(root -> left));
	radius = CheckFloatUnits(EvalParseTree(root -> right -> left));
	new = NewEntity(IGES_CYLINDER, 0, 12);
	new -> entity.cylinder = Struct_alloc(ENTITY_CYLINDER);
	new -> entity.cylinder -> height = height;
	new -> entity.cylinder -> radius = radius;
	for(i=0; i<3; i++)
		new -> entity.cylinder -> center[i] = new -> entity.cylinder -> axis[i] = 0.0;
	return(NewEntityParcel(new));
} /* end NewCylinder */

struct PARCEL *NewBlock(struct NODE *root)
{
	float lx, lz, ly;
	int i;
	struct ENTITY *new;
	lz = CheckFloatUnits(EvalParseTree(root -> left));
	ly = CheckFloatUnits(EvalParseTree(root -> right -> left));
	lx = CheckFloatUnits(EvalParseTree(root -> right -> right -> left));
	new = NewEntity(IGES_BLOCK, 0, 12);
	new -> entity.block = Struct_alloc(ENTITY_BLOCK);
	new -> entity.block -> length[0] = lx;
	new -> entity.block -> length[1] = ly;
	new -> entity.block -> length[2] = lz;
	for(i=0; i<3; i++)
		new -> entity.block -> corner[i] = 0.0;
	new -> entity.block -> x_axis[0] = 1.0;
	new -> entity.block -> x_axis[1] = new -> entity.block -> x_axis[2] = 0.0;
	new -> entity.block -> y_axis[0] = new -> entity.block -> y_axis[1] = 0.0;
	new -> entity.block -> y_axis[2] = 1.0;
	return(NewEntityParcel(new));
} /* end NewBlock */

struct PARCEL *NewSphere(struct NODE *root)
{
	float radius;
	struct ENTITY *new;
	radius = CheckFloatUnits(EvalParseTree(root));
	new = NewEntity(IGES_SPHERE, 0, 1);
	new -> entity.sphere = Struct_alloc(ENTITY_SPHERE);
	new -> entity.sphere -> radius = radius;
	return(NewEntityParcel(new));
} /* end NewSphere */

struct PARCEL *NewProperty(int ptype, int size, float values[])
{
	int form, nd, ni, j;
	float **d;
	float **i;
	struct ENTITY *new;
	new = NewEntity(IGES_PROPERTY, TABULAR_PROPERTY, size+3);
	new -> entity.property = Struct_alloc(ENTITY_PROPERTY);
	new -> entity.property -> ptype = ptype;
	new -> entity.property -> nd = size;
	new -> entity.property -> ni = 0;
	for (j=0; j<size; j++)
		new -> entity.property -> d[j] = values[j];
	return(NewEntityParcel(new));
} /* end NewProperty */

struct MATERIAL_VALUES *NewMaterialValue(struct PARCEL *parcel)
{
	struct MATERIAL_VALUES *newMaterial;
	newMaterial = Struct_alloc(MATERIAL_VALUES);
	newMaterial -> chain = Null_struct(MATERIAL_VALUES);
	newMaterial -> entity = parcel -> ptr.entity;
	return(newMaterial);
} /* end NewMaterialValue */

struct PARCEL *Terminal(struct NODE *root)
{
	struct PARCEL *primitive, *properties, *location;
	struct ENTITY *entity;
	struct ENTITY_TRANSFORMATION *transformation;
	struct BUCKET *property_bucket;
	struct NODE *id;
	primitive = EvalParseTree(root -> left);
	if (primitive -> type != ENTITY_PARCEL) Bug("terminal parcel not entity");
	if (root -> right -> left) {
		properties = EvalParseTree(root -> right -> left);
		id = root -> right -> left -> left;
		if (properties) {
			property_bucket = Lookup(id -> string, symbolHashTable, SYMBOLSIZE);
			if (property_bucket)
				primitive -> ptr.entity -> properties =
				property_bucket -> contents.material;
			else
			fprintf(stderr, "property %s not found.\n", id -> string);
		} /* end if */
	} /* end if */
	if (root -> right -> right) {
		location = EvalParseTree(root -> right -> right);
		entity = NewEntity(IGES_TRANSFORMATION, 0, 2);
		transformation = Struct_alloc(ENTITY_TRANSFORMATION);
		transformation -> node = primitive -> ptr.entity;
		transformation -> translation = location -> ptr.entity;
		transformation -> rotation = Null_struct(ENTITY);
		entity -> entity.transformation = transformation;
		return(NewEntityParcel(entity));
	} /* end if */
	return(primitive); /* raw, unadulterated */
} /* end Terminal */

void CheckTerminal(struct PARCEL *node, int terminalType)
{
	if (node -> type != terminalType) {
		Trouble("CSG operator doesn't have the right type");
		PrintParcel(node);
	} /* end if */
} /* end CheckTerminal */

struct PARCEL *NewCSG(int operator, struct PARCEL *left, struct PARCEL *right)
{
	int type;
	struct ENTITY *entity;
	struct ENTITY_TRANSFORMATION *transformation;
	struct ENTITY_CSG *csg_node;
	switch (operator) {
	case UNION:
		CheckTerminal(left, ENTITY_PARCEL);
		CheckTerminal(right, ENTITY_PARCEL);
		type = 1;
		break;
	case DIFFERENCE:
		CheckTerminal(left, ENTITY_PARCEL);
		CheckTerminal(right, ENTITY_PARCEL);
		type = 2;
		break;
	case INTERSECT:
		CheckTerminal(left, ENTITY_PARCEL);
		CheckTerminal(right, ENTITY_PARCEL);
		type = 3;
		break;
	case ASSEMBLY:
		CheckTerminal(left, ENTITY_PARCEL);
		CheckTerminal(right, ENTITY_PARCEL);
		entity = NewEntity(IGES_ASSEMBLY, 0, 2);
		csg_node = Struct_alloc(ENTITY_CSG);
		csg_node -> left = left -> ptr.entity;
		csg_node -> right = right -> ptr.entity;
		entity -> entity.csg = csg_node;
		return(NewEntityParcel(entity));
	case ROTATE:
		CheckTerminal(right, POINT_PARCEL);
		CheckTerminal(left, ENTITY_PARCEL);
		entity = NewEntity(IGES_TRANSFORMATION, 0, 2);
		transformation = Struct_alloc(ENTITY_TRANSFORMATION);
		transformation -> node = left -> ptr.entity;
		transformation -> rotation = right -> ptr.entity;
		transformation -> translation = Null_struct(ENTITY);
		entity -> entity.transformation = transformation;
		return(NewEntityParcel(entity));
	default:
		Bug("Bad case for NewCSG");
	} /* end switch */
	entity = NewEntity(IGES_CSG, 0, 2);
	csg_node = Struct_alloc(ENTITY_CSG);
	csg_node -> left = left -> ptr.entity;
	csg_node -> right = right -> ptr.entity;
	csg_node -> operator = type;
	entity -> entity.csg = csg_node;
	return(NewEntityParcel(entity));
} /* end NewCSG */

struct PARCEL *NewPoint(struct NODE *root,  int flag)
{
	struct PARCEL *intermediate;
	struct PARCEL *theParcel;
	float value;
	int pos;
	if (root == Null_struct(NODE)) return(Null_struct(PARCEL));
	theParcel = NewParcel(POINT_PARCEL);
	theParcel -> ptr.entity = NewEntity(IGES_POINT, 0, 3);
	theParcel -> ptr.entity -> entity.point = Struct_alloc(ENTITY_POINT);
	for (pos=0; pos<3; pos++) {
		intermediate = EvalParseTree(root -> left);
		value = flag ? CheckFloatUnits(intermediate) : CheckFloat(intermediate);
                theParcel -> ptr.entity -> entity.point -> point.vector[pos] = value;
		root = root -> right;
	} /* end for */
	return(theParcel);
} /* end NewPoint */

