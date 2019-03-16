/*
 * t2 common definitions
 */

#define Struct_alloc(structure) (struct structure *) calloc(1, sizeof (struct structure))
#define Null_struct(structure) (struct structure *) 0

#define MAXGLOBALS 24
#define SYMBOLSIZE 101

struct NODE {
	int operator;
	struct NODE *left, *right;
	char *string;
};

struct VALUE {
	int units;
	float value;
};

struct BINDING {
	struct BUCKET *name;
	struct VALUE *first, *second, *step;
};

struct PARCEL {
	int type;
	char *bound_name;
	union {
		struct VALUE *constant;
		struct BINDING *binding;
		struct DE *de;
		struct MATERIAL_VALUES *material;
		struct ENTITY *entity;
		char *string;
		float translation[3];
	} ptr;
};

struct PROPERTY_VALUE {
	char *name;
	float value;
	struct PROPERTY_VALUE *chain;
};

struct MATERIAL_VALUES {
	struct MATERIAL_VALUES *chain;
	struct ENTITY *entity;
};

struct BUCKET {
	char *name;
	struct BUCKET *next, *chain;
	int type;
	union {
		struct NODE *pointer;
		struct VALUE *constant;
		struct MATERIAL_VALUES *material;
	} contents;
};

typedef enum { EMPTY_PARCEL, VALUE_PARCEL, DE_PARCEL, ENTITY_PARCEL, STRING_PARCEL, POINT_PARCEL, MATERIAL_PARCEL, BINDING_PARCEL } PARCEL_ENUM;

typedef enum { EMPTY_BUCKET, VARIABLE_BUCKET, CONSTANT_BUCKET, MATERIAL_BUCKET } BUCKET_ENUM;

struct LINE {
	struct LINE *chain;
	char *string;
	int de;
};

#define GLOBAL_COMMENT 0
#define GLOBAL_UNITS 15
#define GLOBAL_TITLE 3
#define GLOBAL_AUTHOR 21
#define GLOBAL_ORG 22

