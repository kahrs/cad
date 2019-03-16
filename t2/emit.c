/*
 * IGES "code" emit
 */

#include <stdio.h>
#include "stdarg.h"
#include <string.h>
#include <math.h>
#include "t2.h"
#include "iges.h"

#ifndef PI
#define PI	3.1415926535897932384626433832795028841971693993751
#endif

extern char *globalConstants[];
extern int parcelStackCount;
extern int globalFlag;
extern char *fileName;

int sequence = 0;
extern int deCount;
int parameterCount = 1;
struct LINE *lastLine, *firstLine;
int globalCount;

void PrintParcel(struct PARCEL *theParcel);
void PushParcel(struct PARCEL *theParcel);
struct PARCEL *NewParcel();
struct DE *NewDE(int type, int parameter, int count, int form, int transform);
struct MATERIAL_VALUES *CloneAppendedLists(struct MATERIAL_VALUES *a, struct MATERIAL_VALUES *b);

void EmitStart(void);
void EmitFinish(void);
struct DE *EmitEntities(struct ENTITY *root, struct MATERIAL_VALUES *properties);
struct DE *EmitFloatEntity(int pflag, int type, int form, int count, ...);
struct DE *EmitIntEntity(int pflag, int type, int transform, int form, int count, ...);
struct DE *EmitMatrixEntity(struct ENTITY *translation, struct ENTITY *rotation);
void EmitProperties(struct MATERIAL_VALUES *head);
void EmitNewProperties(struct MATERIAL_VALUES *head);
void EmitForm(char *line, char section);
void EmitGlobals(void);
void AddToForm(char line[], char *addition);
void DontCare(char line[]);
void EmitLine(char *string, char section, int de);

char *strdup();

void EmitIGES(struct ENTITY *top)
{
	EmitStart();
	EmitGlobals();
	EmitEntities(top, Null_struct(MATERIAL_VALUES));
	EmitFinish();
} /* end EmitIGES */

void EmitFx(struct ENTITY *top)
{
} /* end EmitFx */

void EmitStart()
{
	if (globalConstants[0]) EmitForm(globalConstants[0], 'S');
	else EmitForm("t square output", 'S');
} /* end EmitStart */

void EmitGlobals()
{
	int i;
	char line[72];
	char format[72];
	line[0] = '\0';
	for (i=1; i<MAXGLOBALS; i++)
	    switch (i) {
	case 1:
		strcat(line, "1H,"); continue;
	case 2:
		AddToForm(line, "1H;"); continue;
	case 3: case 15: case 21: case 22:
		if (globalConstants[i]) {
		    sprintf(format, "%dH%s", strlen(globalConstants[i]), globalConstants[i]);
		    AddToForm(line, format);
		} /* end if */
		continue;
	case 4:	sprintf(format, "%dH%s", strlen(fileName), fileName);
		AddToForm(line, format); continue;
	case 5:	AddToForm(line, "2Ht2"); continue;
	case 6: AddToForm(line, "1H0"); continue;
	case 7: AddToForm(line, "32"); continue;
	case 8: case 9: case 10: case 11: case 12: case 13:
		DontCare(line); continue;
	case 14: case 16: case 17:
		DontCare(line); continue;
	default:
		DontCare(line); continue;
	} /* end switch */
	AddToForm(line, ";");
	EmitForm(line, 'G');
	globalFlag++;
	globalCount = 1;
	sequence = 0;
} /* end EmitGlobals */

struct DE *EmitEntities(struct ENTITY *root, struct MATERIAL_VALUES *inherited)
{
	struct DE *left, *right, *center;
	struct MATERIAL_VALUES *newList;
	int flag;
	if (root == Null_struct(ENTITY)) return(Null_struct(DE));
	else
	if (root -> de) return(root -> de);

	newList = (inherited != Null_struct(MATERIAL_VALUES)) ?
		((root -> properties != Null_struct(MATERIAL_VALUES)) ?
			CloneAppendedLists(inherited, root -> properties) :
			inherited)
		: root -> properties;
	EmitNewProperties(newList);
	flag = (newList != Null_struct(MATERIAL_VALUES)) ? 1 : 0;

	switch (root -> type) {
	case IGES_CSG:
		left = EmitEntities(root -> entity.csg -> left, newList);
		right = EmitEntities(root -> entity.csg -> right, newList);
		center = EmitIntEntity(flag, root -> type, 0, 0, 4, 3,
		root -> entity.csg -> operator, -left -> subscript, -right -> subscript);
		break;
	case IGES_ASSEMBLY:
		left = EmitEntities(root -> entity.csg -> left, newList);
		right = EmitEntities(root -> entity.csg -> right, newList);
		center = EmitIntEntity(flag, root -> type, 0, 0, 5, 2,
		-left -> subscript, -right -> subscript, 0, 0);
		break;
	case IGES_TRANSFORMATION:
		left = EmitEntities(root -> entity.transformation -> node, newList);
		right = EmitMatrixEntity(root -> entity.transformation -> translation, root -> entity.transformation -> rotation);
		center = EmitIntEntity(flag, root -> type, right ? right -> subscript : 0, 0, 1, -left -> subscript);
		break;
	case IGES_BLOCK:
		center = EmitFloatEntity(flag, root -> type, 0, 12,
			root -> entity.block  -> length[0],
			root -> entity.block  -> length[1],
			root -> entity.block  -> length[2],
			root -> entity.block -> corner[0],
			root -> entity.block -> corner[1],
			root -> entity.block -> corner[2],
			root -> entity.block -> x_axis[0],
			root -> entity.block -> x_axis[1],
			root -> entity.block -> x_axis[2],
			root -> entity.block -> y_axis[0],
			root -> entity.block -> y_axis[1],
			root -> entity.block -> y_axis[2]);
		break;
	case IGES_SPHERE:
		center = EmitFloatEntity(flag, root -> type, 0, 4,
			root -> entity.sphere  -> radius,
			root -> entity.cylinder -> center[0],
			root -> entity.cylinder -> center[1],
			root -> entity.cylinder -> center[2]);
		break;
	case IGES_POINT:
		center = EmitFloatEntity(flag, root -> type, 0, 3,
			root -> entity.point  -> point.vector[0],
			root -> entity.point  -> point.vector[1],
			root -> entity.point  -> point.vector[2]);
		break;
	case IGES_CYLINDER:
		center = EmitFloatEntity(flag, root -> type, 0, 8,
			root -> entity.cylinder  -> height,
			root -> entity.cylinder  -> radius,
			root -> entity.cylinder -> center[0],
			root -> entity.cylinder -> center[1],
			root -> entity.cylinder -> center[2],
			root -> entity.cylinder -> axis[0],
			root -> entity.cylinder -> axis[1],
			root -> entity.cylinder -> axis[2]);
		break;
	default:
		fprintf(stderr, "type=%d\n", root -> type);
		Bug("unknown type in EmitEntities");
	} /* end switch */
	root -> de = center;
	if (newList) EmitProperties(newList);
	return(center);
} /* end EmitEntities */

void EmitForm(char *input_line, char section)
{
	char line[81];
	int length;
	length = strlen(input_line);
	strncpy(line, input_line, 72);
	memset(line + length, ' ', 80-length-1);
	sprintf(line+72, "%c%07.7d", section, 1);
	line[80] = '\0';
	printf("%s\n", line);
} /* end EmitForm */

void AddToForm(char line[], char *addition)
{
	strcat(line, ",");
	if ((strlen(line) + strlen(addition) + 1)>= 72) {
		EmitForm(line, 'G');
		strncpy(line, addition, 72);
	}
	else strcat(line, addition);
} /* end AddToForm */

void DontCare(char line[])
{
	if (strlen(line)+1 >= 72)
		EmitForm(line, 'G');
	strcat(line, ",");
} /* end DontCare */

void AddFloatToLine(char *line, char *format, int de, float argument, char terminator)
{
	char addition[65];
	sprintf(addition, format, argument, terminator);
	if (strlen(line) + strlen(addition) + 1 > 64) {
		EmitLine(line, 'P', de);
		strncpy(line, addition, 64);
	}
	else strcat(line, addition);
} /* end AddFloatToLine */

void AddIntToLine(char *line, char *format, int de, int argument, char terminator)
{
	char addition[65];
	sprintf(addition, format, argument, terminator);
	if (strlen(line) + strlen(addition) + 1 > 64) {
		EmitLine(line, 'P', de);
		strncpy(line, addition, 64);
	}
	else strcat(line, addition);
} /* end AddIntToLine */

struct DE *EmitFloatEntity(int pflag, int type, int form, int count, ...)
{
	va_list ap;
	char format[65];
	int i;
	float next, last;
	struct DE *de;
	de = NewDE(type, parameterCount++, 0, form, 0);
	va_start(ap, count);
	sprintf(format, "%d, ", type);
	for (i=0; i<count-1; i++)
		AddFloatToLine(format, "%f%c", deCount, va_arg(ap, double), ',');
	AddFloatToLine(format, "%f%c", deCount, va_arg(ap, double), pflag ? ',' : ';');
	EmitLine(format, 'P', deCount);
	va_end(ap);
	deCount += 2;
	return(de);
} /* end EmitFloatEntity */

struct DE *EmitIntEntity(int pflag, int type, int transform, int form, int count, ...)
{
	va_list ap;
	char format[65];
	int i;
	float next, last;
	struct DE *de;
	de = NewDE(type, parameterCount++, 0, form, transform);
	va_start(ap, count);
	sprintf(format, "%d, ", type);
	for (i=0; i<count-1; i++)
		AddIntToLine(format, "%d%c", deCount, va_arg(ap, int), ',');
	AddIntToLine(format, "%d%c", deCount, va_arg(ap, int), pflag ? ',' : ';');
	EmitLine(format, 'P', deCount);
	va_end(ap);
	deCount += 2;
	return(de);
} /* end EmitIntEntity */

struct DE *EmitMatrixEntity(struct ENTITY *translation, struct ENTITY *rotation)
{
	float matrix[3][4];
	int i,j;
	double x, y, z;
	for (i=0; i<3; i++)
	    for (j=0; j<4; j++)
		matrix[i][j] = (i == j) ? 1.0 : 0.0;
	if (translation) {
		if (translation -> type != IGES_POINT) Bug("translation.type!=POINT");
		for (i=0; i<3; i++)
			matrix[i][i] = translation -> entity.point -> point.vector[i];
	} /* end if */
	if (rotation) {
		if (rotation -> type != IGES_POINT) Bug("rotation.type!=POINT");
		for (i=0; i<3; i++)
			matrix[i][3] = rotation -> entity.point -> point.vector[i];
	} /* end if */
/*	for (i=0; i<3; i++) {
	    for (j=0; j<4; j++)
		fprintf(stderr, "%f ", matrix[i][j]);
	    fprintf(stderr, "\n");
	}
 */
	x = (double) ((matrix[0][0] / 360.0) * 2.0 * PI);
	y = (double) ((matrix[1][1] / 360.0) * 2.0 * PI);
	z = (double) ((matrix[2][2] / 360.0) * 2.0 * PI);
	return(EmitFloatEntity(0, IGES_MATRIX, 0, 12,
		(float) cos(z)*cos(y), (float) -sin(z)*cos(x),
		(float) cos(z)*sin(y)*sin(x), (float) 0.0,
		(float) sin(z)*cos(y), (float) cos(z)*cos(x)+cos(y)*cos(x),
		(float) cos(y)*cos(x)-cos(z)*sin(x), (float) 0.0,
		(float) -sin(y), (float) cos(y)*sin(x),
		(float) cos(y)*cos(x), (float) 0.0));

/*	return(EmitFloatEntity(0, IGES_MATRIX, 0, 12,
		matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3],
		matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3],
		matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3]));
 */
} /* end EmitMatrixEntity */

struct DE *EmitProperty(struct ENTITY *deed)
{
	char format[65];
	int i, size;
	struct DE *de;
	size = deed -> count;
	memset(format, '\0', 65);
	de = EmitIntEntity(1, deed -> type, 0,
		deed -> entity.property -> ptype, 2,
		deed -> entity.property -> nd, deed -> entity.property -> ni);
	for (i=0; i<(size-4); i++)
		AddFloatToLine(format, "%f%c", deCount, deed -> entity.property -> d[i], ',');
	AddFloatToLine(format, "%f%c", deCount, deed -> entity.property -> d[i], ';');
	EmitLine(format, 'P', deCount);
	return(de);
} /* end EmitProperty */

void EmitNewProperties(struct MATERIAL_VALUES *head)
{
	struct DE *de;
	char format[65];
	while (head) {
		de = head -> entity -> de;
		if (!de) head -> entity -> de = EmitProperty(head -> entity);
		head = head -> chain;
	} /* end while */
} /* end EmitNewProperties */

void EmitProperties(struct MATERIAL_VALUES *head)
{
	struct DE *de;
	struct MATERIAL_VALUES *top;
	char format[65];
	int count;
	memset(format, '\0', 65);
	for (top = head, count = 0; top; count++, top = top -> chain);
	AddIntToLine(format, "%d%c", deCount, 0, ',');
	AddIntToLine(format, "%d%c", deCount, count, ',');
	while (head) {
		de = head -> entity -> de;
		if (!de) Bug("de == 0 in EmitProperties");
		AddIntToLine(format, "%d%c", deCount, -(de -> subscript), (head -> chain) ? ',' : ';');
		head = head -> chain;
	} /* end while */
	EmitLine(format, 'P', deCount);
} /* end EmitProperties */

void EmitDE(struct DE *theDE)
{
	char *label;
	if (theDE -> label == NULL) label = "";
	printf("%8d%8d%8d%8d%8d%8d%8d%8.8s%8dD%7d\n",
	theDE -> type, theDE -> parameter, theDE -> structure, theDE -> lineFont,
	theDE -> levels, theDE -> view, theDE -> transformation, label, 0, ++sequence);
	printf("%8d%8d%8d%8d%8d%8d%8d%8.8s%8dD%7d\n",
	theDE -> type, theDE -> parameter, theDE -> color, theDE -> count, theDE -> form,
	0, 0, label, theDE -> subscript, ++sequence);
} /* end EmitDE */

void EmitLine(char *string, char section, int de)
{
	struct LINE *line;
	line = Struct_alloc(LINE);
	line -> chain = Null_struct(LINE);
	line -> string = strdup(string);
	line -> de = de;
	if (lastLine) lastLine -> chain = line;
	else firstLine = line;
	lastLine = line;
} /* end EmitLine */

void EmitLines()
{
	while (firstLine) {
		printf("%64.64s%8d%c%7d\n",
			firstLine -> string, firstLine -> de, 'P', ++sequence);
		firstLine = firstLine -> chain;
	} /* end while */
} /* end EmitLines */

void EmitFinish()
{
	if (parcelStackCount != 0) {
		StackTrace();
		Trouble("stack not empty");
	} /* end if */
	sequence = 0;
	EmitLines();
	printf("S%7.7dG%7.7dD%7.7dP%7.7d                                        T%7.7d\n",
	1, globalCount, deCount, sequence, 1);
} /* end EmitFinish */
