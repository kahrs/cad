/*
 * IGES 4.0 definitions
 */

/* Directory for Entry */

struct DE {
	int type;
	short int parameter;
	short int structure;
	char lineFont;
	short int levels;
	short int view;
	short int transformation;
	short int labelAssociativity;
	char independence, use, hierarchy;
	char lineWeight, color;
	char count;
	char form;
	char *label;
	short int subscript;
	struct ENTITY *entity;
}  DEproto;

#define LINE_SOLID 1
#define LINE_DASHED 2
#define LINE_PHANTOM 3
#define LINE_CENTERLINE 4
#define LINE_DOTTED 5

#define INDEPENDENT 0
#define PDEPENDENT 1
#define LDEPENDENT 2
#define BDEPENDENT 3

#define USE_GEOMETRY 0
#define USE_ANNOTATION 1
#define USE_DEFINITION 2
#define USE_OTHER 3
#define USE_LOGICAL 4
#define USE_2D 5

#define ALL 0
#define NONE 1
#define INDIVIDUAL 2

#define NRW 18

struct ENTITY {
	int form;
	int count;
	int type;
	union  {
		struct ENTITY_POINT *point;
		struct ENTITY_BLOCK *block;
		struct ENTITY_WEDGE *wedge;
		struct ENTITY_CYLINDER *cylinder;
		struct ENTITY_CONE *cone;
		struct ENTITY_SPHERE *sphere;
		struct ENTITY_CSG *csg;
		struct ENTITY_DEFINITION *macro;
		struct ENTITY_TRANSFORMATION *transformation;
		struct ENTITY_PROPERTY *property;
	} entity;
	struct DE *de;
	struct MATERIAL_VALUES *properties;
};

struct ENTITY_POINT {
	union {
		float x, y, z;
		float vector[3];
	} point;
};

struct ENTITY_TRANSFORMATION {
	struct ENTITY *node;
	struct ENTITY *rotation;
	struct ENTITY *translation;
};

struct ENTITY_BLOCK {
	float length[3];
	float corner[3];
	float x_axis[3];
	float y_axis[3];
};

struct ENTITY_WEDGE {
	float length[3];
	float corner[3];
	float x_axis[3];
	float y_axis[3];
};

struct ENTITY_CYLINDER {
	float height, radius;
	float center[3], axis[3];
};

struct ENTITY_CONE {
	float height, large_face_radius, small_face_radius;
	float center[3], axis[3];
};

struct ENTITY_SPHERE {
	float radius;
	float center[3];
};

struct ENTITY_CSG {
	int operator;
	struct ENTITY *left, *right;
};

#define MAXVALUES 10
struct ENTITY_PROPERTY {
	int form, ptype, nd, ni;
	float d[MAXVALUES];
	float i[MAXVALUES];
};

/*
 * IGES entity definitions
 */

#define IGES_MATRIX 124
#define IGES_POINT 130
#define IGES_BLOCK 150
#define IGES_CYLINDER 154
#define IGES_SPHERE 158
#define IGES_CSG 180
#define IGES_ASSEMBLY 184
#define IGES_PROPERTY 406
#define IGES_TRANSFORMATION 430

/*
 * property forms
 */

#define TABULAR_PROPERTY 11

