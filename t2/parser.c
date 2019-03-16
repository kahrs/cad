
# line 6 "t2.y"

#include "t2.h"

extern struct NODE *NullaryNode();
extern struct NODE *StringNode();
extern struct NODE *UnaryNode();
extern struct NODE *BinaryNode();
extern struct NODE *DeclarePlan();
extern char *CopyString();

extern struct PROPERTY_VALUE *PatchManifests();
extern struct PROPERTY_VALUE *DeclareManifest();
extern struct MATERIAL_VALUES *DeclareProperty();
extern struct MATERIAL_VALUES *PatchProperties();

extern struct NODE *treeRoot;
extern struct NODE *materialName, *propertyName;

typedef union {
	struct NODE *node;
	struct PROPERTY_VALUE *property;
	struct MATERIAL_VALUES *material;
} YYSTYPE;

extern int integerConstant;
extern float floatingConstant;
extern char stringBuffer[128];
extern char yytext[];

char *quoted;

# define ID 257
# define NUMBER 258
# define UMINUS 259
# define LT 260
# define LE 261
# define EQ 262
# define GE 263
# define GT 264
# define NE 265
# define EXP 266
# define MATERIAL 267
# define OBJECT 268
# define GLOBAL 269
# define PROPERTIES 270
# define CYLINDER 271
# define BLOCK 272
# define SPHERE 273
# define IN 274
# define FT 275
# define M 276
# define CM 277
# define MM 278
# define DO 279
# define IF 280
# define FOR 281
# define THEN 282
# define ELSE 283
# define AT 284
# define SWITCH 285
# define INTEGER 286
# define FLOAT 287
# define STRING 288
# define CONSTANT 289
# define LIST 290
# define FUNCTION 291
# define CALL 292
# define TERMINAL 293
# define PROPERTY 294
# define COMPOUND 295
# define TUPLE 296
# define UNION 297
# define INTERSECT 298
# define ROTATE 299
# define DIFFERENCE 300
# define ASSEMBLY 301
# define UPTO 302
# define DOWNTO 303
# define BIND 304
# define ALTERNATIVE 305
# define LABEL 306
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern short yyerrflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
YYSTYPE yylval, yyval;
# define YYERRCODE 256

# line 282 "t2.y"

short yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
	};
# define YYNPROD 88
# define YYLAST 386
short yyact[]={

 109, 107,  41, 108,  84, 110, 121, 122, 123, 124,
 125,  41,  54,  55,  56,  91, 175, 144, 157, 160,
 126,  87,  41,  49,   9,   8,  10, 111,  28,  13,
 177,  36,  32, 109, 107, 174, 108, 103, 110,  97,
 100, 182, 141,  30, 109, 107, 172, 108,  76, 110,
 109, 107, 139, 108, 109, 110, 137, 109, 107, 110,
 108,  19, 110, 109, 107, 136, 108,  15, 110, 109,
 107, 134, 108,  65, 110, 130, 109, 107, 173, 108,
 143, 110, 109, 107, 131, 108,  81, 110,  18,  77,
  78,  79,  80, 142,  31,  58,  23, 183,  89,  61,
  60,  67,  59,  58,  24,  48,  61,  61,  60, 168,
  59,  61,  60, 138,  59, 135, 133, 106,  47, 119,
  73, 105, 181, 140,  29,  71,  70,  85,  69,  64,
  62,  68,  17,  21,  27,  74,  12,  14,   3,  20,
   7,  11,   1,  22,  26,  25, 102,  66,  42,  33,
  82,  46, 120,  75,  95,  92,  51,  90,  22,  86,
 156,  50,  72,  35,  52, 128,  63,  34,  28,  46,
  40, 161,  16,   5, 176, 127,  25, 167,  93, 165,
 164,  57,   6,   4,   2,  46,  46,  46,  46,  57,
 169,  53,   0,   0,   0,  94,   0,   0,   0,   0,
   0,   0,   0,   0, 104,   0,   0,   0, 180,   0,
  98,   0,   0, 184,   0, 185,  13,   0,   0,  13,
   0, 132,   0,   0, 111,   0,   0,   0,  13,   0,
   0,   0,   0,  43,  44,  45,   0,   0,   0,  13,
   0,   0,  43,  44,  45,  54,  55,  56,  54,  55,
  56,  37,  38,  43,  44,  45,  39, 111,   0,   0,
 158, 159, 113, 112, 114, 115, 116, 117, 111, 104,
   0,   0,  46,  83, 111,  88,   0,   0, 111,   0,
  96, 111,  99,   0, 101,  46,   0, 111,   0,   0,
   0,   0,   0, 111,   0, 118,   0,   0, 129,   0,
 111,   0, 166,  46,   0,   0, 111,   0,   0,   0,
   0,  46,   0,   0,   0,   0,   0,   0, 145, 146,
 147, 148, 149, 150, 151, 152, 153, 154, 155,   0,
 101,   0, 178,   0,   0,   0,   0,   0,   0,   0,
   0,   0, 178, 186,   0, 162,   0, 163,   0,   0,
 101,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0, 170,
 171,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0, 179 };
short yypact[]={

-243,-1000,-243,-1000,-1000,-1000,-1000,-1000,-228,-228,
 -56,-1000,  92,-1000, -62,-228,  35,-228,-1000,-242,
  -1,-1000,  33, -29,  77,  61,-102,-1000,-228,-1000,
-228,-274,-1000,-1000,-1000,-1000,  65,  90,-228,  89,
-1000, -18,  43,  88,  86,  85,  80,-1000,-228,-1000,
-1000, -75,-1000,-1000,-1000,-1000,-1000, -18, -18, -18,
 -18,  -5, -41,-253, -41,  57,-269,-228,-1000, -41,
 -41, -41,-1000, -41,-1000,-1000,-228,  69,  69,  64,
  64, -41,  76,   2, -41,  79,-268, -41,  34,-1000,
-1000,  -7,-1000,-228,-1000,  75,  27,  74,  21,  15,
  72,   8,  -2,-1000,  32, -13,-265, -41, -41, -41,
 -41, -41, -41, -41, -41, -41, -41, -41,-239, -41,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-261, -42,
-255, -41,-1000,-1000, -41,-1000, -41,-1000,-1000, -41,
-1000,-228,-274,-1000, -29,  12,  12,-239,-239,-239,
  40,  40,  40,  40,  40,  40,  68, -29, -41, -41,
 -77, -15,  40,  -9,-1000,-1000,-1000,-267,-1000,-1000,
  40,  40,-274,-1000, -41, -29,  -3,-1000,  39,  40,
-1000,-1000,-274, -38,-1000,  65,-1000 };
short yypgo[]={

   0, 184, 138, 183, 182, 178, 174, 173, 172, 104,
  31, 170, 167, 165, 163,  30, 162,  40, 157, 154,
  39, 152, 210, 150, 159, 127,  32, 149, 148, 147,
 146,  37, 134, 144, 142, 140, 139, 133,  88 };
short yyr1[]={

   0,  34,   1,   1,   2,   2,   3,   3,   4,  33,
  33,  32,  30,  30,  31,  35,  36,  36,  37,   7,
   8,   8,   9,   9,  26,  26,  26,  26,  12,  13,
  13,  27,  14,   6,   6,  15,  15,  10,  10,  10,
  10,  10,  10,  10,  11,  29,  29,   5,   5,  28,
  28,  28,  28,  16,  16,  17,  17,  18,  18,  19,
  20,  21,  21,  21,  21,  21,  21,  21,  22,  22,
  22,  22,  22,  22,  22,  22,  22,  23,  23,  23,
  23,  23,  23,  24,  24,  24,  25,  38 };
short yyr2[]={

   0,   1,   2,   1,   1,   1,   1,   1,   5,   2,
   1,   5,   3,   1,   3,   4,   3,   1,   3,   5,
   3,   1,   1,   3,   1,   1,   1,   1,   6,   3,
   3,   8,   8,   3,   1,   3,   3,   1,   3,   3,
   3,   3,   5,   3,   3,   2,   1,   2,   1,   4,
   4,   4,   2,   3,   1,   1,   3,   4,   1,   3,
   5,   1,   1,   1,   1,   1,   1,   1,   3,   3,
   3,   3,   3,   2,   1,   2,   4,   3,   3,   3,
   3,   3,   3,   1,   1,   1,   1,   0 };
short yychk[]={

-1000, -34,  -1,  -2,  -3,  -7,  -4, -35, 268, 267,
 269,  -2, -25, 257, -25, 123,  -8,  40, -38, 123,
 -36, -37, -25,  61,  -9, -25, -33, -32, 270, 125,
  44,  61, -26, -27, -12, -14, -10, 280, 281, 285,
 -11,  40, -28, 271, 272, 273, -25,  41,  44, 125,
 -32, -25, -37, -24, 286, 287, 288, 124,  38,  45,
  43,  42,  40, -25,  40, -10, -29,  58, -38,  40,
  40,  40, -16,  40, -38,  -9, 123, -10, -10, -10,
 -10,  91, -23, -22,  45, -25, -24, 274, -22,  41,
 -18, 284, -38,  -5, -25, -19, -22, -20, -22, -22,
 -17, -22, -30, -31, -25, -20,  41,  43,  45,  42,
  47, 266, 261, 260, 262, 263, 264, 265, -22,  40,
 -21, 274, 275, 276, 277, 278, 288, -38, -13, -22,
  41,  91, -25,  41,  44,  41,  44,  41,  41,  44,
 125,  44,  61,  93, 282, -22, -22, -22, -22, -22,
 -22, -22, -22, -22, -22, -22, -17, 279, 302, 303,
 274, -20, -22, -22, -17, -31, -24, -26,  41, -26,
 -22, -22, 123,  93,  44, 283,  -6, -15, -24, -22,
 -26, 125,  44,  58, -15, -10, -24 };
short yydef[]={

   0,  -2,   1,   3,   4,   5,   6,   7,   0,   0,
   0,   2,  87,  86,   0,   0,   0,   0,  21,   0,
   0,  17,   0,   0,   0,  22,   0,  10,   0,  15,
   0,   0,  19,  24,  25,  26,  27,   0,   0,   0,
  37,   0,  87,   0,   0,   0,  87,  20,   0,   8,
   9,   0,  16,  18,  83,  84,  85,   0,   0,   0,
   0,   0,   0,   0,   0,   0,  87,   0,  46,   0,
   0,   0,  52,   0,  54,  23,   0,  38,  39,  40,
  41,   0,   0,   0,   0,  74,  87,   0,   0,  43,
  44,   0,  58,  45,  48,   0,   0,   0,   0,   0,
   0,  55,   0,  13,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,  73,   0,
  75,  61,  62,  63,  64,  65,  66,  67,   0,   0,
   0,   0,  47,  49,   0,  50,   0,  51,  53,   0,
  11,   0,   0,  42,   0,  68,  69,  70,  71,  72,
  77,  78,  79,  80,  81,  82,   0,   0,   0,   0,
   0,   0,  59,   0,  56,  12,  14,   0,  76,  28,
  29,  30,   0,  57,   0,   0,   0,  34,   0,  60,
  31,  32,   0,   0,  33,  35,  36 };
# ifdef YYDEBUG
# include "y.debug"
# endif

# define YYFLAG -1000
# define YYERROR goto yyerrlab
# define YYACCEPT return(0)
# define YYABORT return(1)

/*	parser for yacc output	*/

#ifdef YYDEBUG
int yydebug = 0; /* 1 for debugging */
#endif
YYSTYPE yyv[YYMAXDEPTH]; /* where the values are stored */
int yychar = -1; /* current input token number */
int yynerrs = 0;  /* number of errors */
short yyerrflag = 0;  /* error recovery flag */

yyparse()
{	short yys[YYMAXDEPTH];
	int yyj, yym;
	register YYSTYPE *yypvt;
	register int yystate, yyn;
	register short *yyps;
	register YYSTYPE *yypv;
	register short *yyxi;

	yystate = 0;
	yychar = -1;
	yynerrs = 0;
	yyerrflag = 0;
	yyps= &yys[-1];
	yypv= &yyv[-1];

yystack:    /* put a state and value onto the stack */
#ifdef YYDEBUG
	if(yydebug >= 3)
		if(yychar < 0 || yytoknames[yychar] == 0)
			printf("char %d in %s", yychar, yystates[yystate]);
		else
			printf("%s in %s", yytoknames[yychar], yystates[yystate]);
#endif
	if( ++yyps >= &yys[YYMAXDEPTH] ) { 
		yyerror( "yacc stack overflow" ); 
		return(1); 
	}
	*yyps = yystate;
	++yypv;
	*yypv = yyval;
yynewstate:
	yyn = yypact[yystate];
	if(yyn <= YYFLAG) goto yydefault; /* simple state */
	if(yychar<0) {
		yychar = yylex();
#ifdef YYDEBUG
		if(yydebug >= 2) {
			if(yychar <= 0)
				printf("lex EOF\n");
			else if(yytoknames[yychar])
				printf("lex %s\n", yytoknames[yychar]);
			else
				printf("lex (%c)\n", yychar);
		}
#endif
		if(yychar < 0)
			yychar = 0;
	}
	if((yyn += yychar) < 0 || yyn >= YYLAST)
		goto yydefault;
	if( yychk[ yyn=yyact[ yyn ] ] == yychar ){ /* valid shift */
		yychar = -1;
		yyval = yylval;
		yystate = yyn;
		if( yyerrflag > 0 ) --yyerrflag;
		goto yystack;
	}
yydefault:
	/* default state action */
	if( (yyn=yydef[yystate]) == -2 ) {
		if(yychar < 0) {
			yychar = yylex();
#ifdef YYDEBUG
			if(yydebug >= 2)
				if(yychar < 0)
					printf("lex EOF\n");
				else
					printf("lex %s\n", yytoknames[yychar]);
#endif
			if(yychar < 0)
				yychar = 0;
		}
		/* look through exception table */
		for(yyxi=yyexca; (*yyxi!= (-1)) || (yyxi[1]!=yystate);
			yyxi += 2 ) ; /* VOID */
		while( *(yyxi+=2) >= 0 ){
			if( *yyxi == yychar ) break;
		}
		if( (yyn = yyxi[1]) < 0 ) return(0);   /* accept */
	}
	if( yyn == 0 ){ /* error */
		/* error ... attempt to resume parsing */
		switch( yyerrflag ){
		case 0:   /* brand new error */
#ifdef YYDEBUG
			yyerror("syntax error\n%s", yystates[yystate]);
			if(yytoknames[yychar])
				yyerror("saw %s\n", yytoknames[yychar]);
			else if(yychar >= ' ' && yychar < '\177')
				yyerror("saw `%c'\n", yychar);
			else if(yychar == 0)
				yyerror("saw EOF\n");
			else
				yyerror("saw char 0%o\n", yychar);
#else
			yyerror( "syntax error" );
#endif
yyerrlab:
			++yynerrs;
		case 1:
		case 2: /* incompletely recovered error ... try again */
			yyerrflag = 3;
			/* find a state where "error" is a legal shift action */
			while ( yyps >= yys ) {
				yyn = yypact[*yyps] + YYERRCODE;
				if( yyn>= 0 && yyn < YYLAST && yychk[yyact[yyn]] == YYERRCODE ){
					yystate = yyact[yyn];  /* simulate a shift of "error" */
					goto yystack;
				}
				yyn = yypact[*yyps];
				/* the current yyps has no shift onn "error", pop stack */
#ifdef YYDEBUG
				if( yydebug ) printf( "error recovery pops state %d, uncovers %d\n", *yyps, yyps[-1] );
#endif
				--yyps;
				--yypv;
			}
			/* there is no state on the stack with an error shift ... abort */
yyabort:
			return(1);
		case 3:  /* no shift yet; clobber input char */
#ifdef YYDEBUG
			if( yydebug ) {
				printf("error recovery discards ");
				if(yytoknames[yychar])
					printf("%s\n", yytoknames[yychar]);
				else if(yychar >= ' ' && yychar < '\177')
					printf("`%c'\n", yychar);
				else if(yychar == 0)
					printf("EOF\n");
				else
					printf("char 0%o\n", yychar);
			}
#endif
			if( yychar == 0 ) goto yyabort; /* don't discard EOF, quit */
			yychar = -1;
			goto yynewstate;   /* try again in the same state */
		}
	}
	/* reduction by production yyn */
#ifdef YYDEBUG
	if(yydebug) {	char *s;
		printf("reduce %d in:\n\t", yyn);
		for(s = yystates[yystate]; *s; s++) {
			putchar(*s);
			if(*s == '\n' && *(s+1))
				putchar('\t');
		}
	}
#endif
	yyps -= yyr2[yyn];
	yypvt = yypv;
	yypv -= yyr2[yyn];
	yyval = yypv[1];
	yym=yyn;
	/* consult goto table to find next state */
	yyn = yyr1[yyn];
	yyj = yypgo[yyn] + *yyps + 1;
	if( yyj>=YYLAST || yychk[ yystate = yyact[yyj] ] != -yyn ) yystate = yyact[yypgo[yyn]];
	switch(yym){
		
case 1:
# line 70 "t2.y"
{ treeRoot = yypvt[-0].node; } break;
case 2:
# line 73 "t2.y"
{ yyval.node = BinaryNode(COMPOUND, yypvt[-1].node, yypvt[-0].node); } break;
case 3:
# line 75 "t2.y"
{ yyval.node = yypvt[-0].node; } break;
case 4:
# line 78 "t2.y"
{ yyval.node = yypvt[-0].node; } break;
case 5:
# line 80 "t2.y"
{ yyval.node = yypvt[-0].node; } break;
case 6:
# line 84 "t2.y"
{ yyval.node = Null_struct(NODE); } break;
case 7:
# line 86 "t2.y"
{ yyval.node = Null_struct(NODE); } break;
case 8:
# line 89 "t2.y"
{ DeclareMaterial(yypvt[-3].node, yypvt[-1].material);  } break;
case 9:
# line 92 "t2.y"
{ yyval.material = PatchProperties(yypvt[-1].material, yypvt[-0].material); } break;
case 10:
# line 94 "t2.y"
{ yyval.material = yypvt[-0].material; } break;
case 11:
# line 97 "t2.y"
{ yyval.material = DeclareProperty(yypvt[-3].node, yypvt[-1].property); } break;
case 12:
# line 100 "t2.y"
{ yyval.property = PatchManifests(yypvt[-2].property, yypvt[-0].property); } break;
case 13:
# line 102 "t2.y"
{ yyval.property = yypvt[-0].property; } break;
case 14:
# line 105 "t2.y"
{ yyval.property = DeclareManifest(yypvt[-2].node -> string, yypvt[-0].node); } break;
case 18:
# line 113 "t2.y"
{ DeclareGlobal(yypvt[-2].node -> string, yypvt[-0].node); } break;
case 19:
# line 117 "t2.y"
{ DeclareObject(yypvt[-3].node, BinaryNode(OBJECT, yypvt[-2].node, yypvt[-0].node)); } break;
case 20:
# line 120 "t2.y"
{ yyval.node = yypvt[-1].node; } break;
case 21:
# line 122 "t2.y"
{ yyval.node = Null_struct(NODE); } break;
case 22:
# line 125 "t2.y"
{ yyval.node = BinaryNode(TUPLE, yypvt[-0].node, Null_struct(NODE)); } break;
case 23:
# line 127 "t2.y"
{ yyval.node = BinaryNode(TUPLE, yypvt[-2].node, yypvt[-0].node); } break;
case 24:
# line 130 "t2.y"
{ yyval.node = yypvt[-0].node; } break;
case 25:
# line 132 "t2.y"
{ yyval.node = yypvt[-0].node; } break;
case 26:
# line 134 "t2.y"
{ yyval.node = yypvt[-0].node; } break;
case 27:
# line 136 "t2.y"
{ yyval.node = yypvt[-0].node; } break;
case 28:
# line 139 "t2.y"
{ yyval.node = BinaryNode(FOR, BinaryNode(BIND, yypvt[-4].node, yypvt[-2].node), yypvt[-0].node); } break;
case 29:
# line 142 "t2.y"
{ yyval.node = BinaryNode(UPTO, yypvt[-2].node, yypvt[-0].node); } break;
case 30:
# line 144 "t2.y"
{ yyval.node = BinaryNode(DOWNTO, yypvt[-2].node, yypvt[-0].node); } break;
case 31:
# line 147 "t2.y"
{ yyval.node = BinaryNode(IF, yypvt[-5].node, BinaryNode(ELSE, yypvt[-2].node, yypvt[-0].node)); } break;
case 32:
# line 150 "t2.y"
{ yyval.node = BinaryNode(SWITCH, yypvt[-5].node, yypvt[-1].node); } break;
case 33:
# line 153 "t2.y"
{ yyval.node = BinaryNode(ALTERNATIVE, yypvt[-2].node, yypvt[-0].node); } break;
case 34:
# line 155 "t2.y"
{ yyval.node = Null_struct(NODE); } break;
case 35:
# line 158 "t2.y"
{ yyval.node = BinaryNode(LABEL, yypvt[-2].node, yypvt[-0].node); } break;
case 36:
# line 160 "t2.y"
{ yyval.node = BinaryNode(LABEL, yypvt[-2].node, yypvt[-0].node); } break;
case 37:
# line 163 "t2.y"
{ yyval.node = yypvt[-0].node; } break;
case 38:
# line 165 "t2.y"
{ yyval.node = BinaryNode(UNION, yypvt[-2].node, yypvt[-0].node); } break;
case 39:
# line 167 "t2.y"
{ yyval.node = BinaryNode(INTERSECT, yypvt[-2].node, yypvt[-0].node); } break;
case 40:
# line 169 "t2.y"
{ yyval.node = BinaryNode(DIFFERENCE, yypvt[-2].node, yypvt[-0].node); } break;
case 41:
# line 171 "t2.y"
{ yyval.node = BinaryNode(ASSEMBLY, yypvt[-2].node, yypvt[-0].node); } break;
case 42:
# line 173 "t2.y"
{ yyval.node = BinaryNode(ROTATE, yypvt[-4].node, yypvt[-1].node); } break;
case 43:
# line 175 "t2.y"
{ yyval.node = yypvt[-1].node; } break;
case 44:
# line 178 "t2.y"
{ yyval.node = BinaryNode(TERMINAL, yypvt[-2].node, BinaryNode(LIST, yypvt[-1].node, yypvt[-0].node)); } break;
case 45:
# line 181 "t2.y"
{ yyval.node = yypvt[-0].node; } break;
case 46:
# line 183 "t2.y"
{ yyval.node = Null_struct(NODE); } break;
case 47:
# line 186 "t2.y"
{ yyval.node = BinaryNode(PROPERTY, yypvt[-0].node, yypvt[-1].node); } break;
case 48:
# line 188 "t2.y"
{ yyval.node = BinaryNode(PROPERTY, yypvt[-0].node, Null_struct(NODE)); } break;
case 49:
# line 191 "t2.y"
{ yyval.node = UnaryNode(CYLINDER, yypvt[-1].node); } break;
case 50:
# line 193 "t2.y"
{ yyval.node = UnaryNode(BLOCK, yypvt[-1].node); } break;
case 51:
# line 195 "t2.y"
{ yyval.node = UnaryNode(SPHERE, yypvt[-1].node); } break;
case 52:
# line 197 "t2.y"
{ yyval.node = BinaryNode(CALL, yypvt[-1].node, yypvt[-0].node); } break;
case 53:
# line 200 "t2.y"
{ yyval.node = yypvt[-1].node; } break;
case 54:
# line 202 "t2.y"
{ yyval.node = Null_struct(NODE); } break;
case 55:
# line 205 "t2.y"
{ yyval.node = BinaryNode(TUPLE, yypvt[-0].node, Null_struct(NODE)); } break;
case 56:
# line 207 "t2.y"
{ yyval.node = BinaryNode(TUPLE, yypvt[-2].node, yypvt[-0].node); } break;
case 57:
# line 210 "t2.y"
{ yyval.node = UnaryNode(AT, yypvt[-1].node); } break;
case 58:
# line 212 "t2.y"
{ yyval.node = Null_struct(NODE); } break;
case 59:
# line 215 "t2.y"
{ yyval.node = BinaryNode(TUPLE, yypvt[-2].node, BinaryNode(TUPLE, yypvt[-0].node, Null_struct(NODE))); } break;
case 60:
# line 218 "t2.y"
{ yyval.node = BinaryNode(TUPLE, yypvt[-4].node, BinaryNode(TUPLE, yypvt[-2].node, BinaryNode(TUPLE, yypvt[-0].node, Null_struct(NODE)))); } break;
case 61:
# line 221 "t2.y"
{ yyval.node = NullaryNode(IN); } break;
case 62:
# line 223 "t2.y"
{ yyval.node = NullaryNode(FT); } break;
case 63:
# line 225 "t2.y"
{ yyval.node = NullaryNode(M); } break;
case 64:
# line 227 "t2.y"
{ yyval.node = NullaryNode(CM); } break;
case 65:
# line 229 "t2.y"
{ yyval.node = NullaryNode(MM); } break;
case 66:
# line 231 "t2.y"
{ yyval.node = UnaryNode(CONSTANT, yypvt[-0].node); } break;
case 67:
# line 233 "t2.y"
{ yyval.node = Null_struct(NODE); } break;
case 68:
# line 236 "t2.y"
{ yyval.node = BinaryNode('+', yypvt[-2].node, yypvt[-0].node); } break;
case 69:
# line 238 "t2.y"
{ yyval.node = BinaryNode('-', yypvt[-2].node, yypvt[-0].node); } break;
case 70:
# line 240 "t2.y"
{ yyval.node = BinaryNode('*', yypvt[-2].node, yypvt[-0].node); } break;
case 71:
# line 242 "t2.y"
{ yyval.node = BinaryNode('/', yypvt[-2].node, yypvt[-0].node); } break;
case 72:
# line 244 "t2.y"
{ yyval.node = BinaryNode(EXP, yypvt[-2].node, yypvt[-0].node); } break;
case 73:
# line 246 "t2.y"
{ yyval.node = UnaryNode(UMINUS, yypvt[-0].node); } break;
case 74:
# line 248 "t2.y"
{ yyval.node = yypvt[-0].node; } break;
case 75:
# line 250 "t2.y"
{ yyval.node = BinaryNode(CONSTANT, yypvt[-1].node, yypvt[-0].node); } break;
case 76:
# line 252 "t2.y"
{ yyval.node = BinaryNode(FUNCTION, yypvt[-3].node, yypvt[-1].node); } break;
case 77:
# line 255 "t2.y"
{ yyval.node = BinaryNode(LE, yypvt[-2].node, yypvt[-0].node); } break;
case 78:
# line 257 "t2.y"
{ yyval.node = BinaryNode(LT, yypvt[-2].node, yypvt[-0].node); } break;
case 79:
# line 259 "t2.y"
{ yyval.node = BinaryNode(EQ, yypvt[-2].node, yypvt[-0].node); } break;
case 80:
# line 261 "t2.y"
{ yyval.node = BinaryNode(GE, yypvt[-2].node, yypvt[-0].node); } break;
case 81:
# line 263 "t2.y"
{ yyval.node = BinaryNode(GT, yypvt[-2].node, yypvt[-0].node); } break;
case 82:
# line 265 "t2.y"
{ yyval.node = BinaryNode(NE, yypvt[-2].node, yypvt[-0].node); } break;
case 83:
# line 268 "t2.y"
{ yyval.node = StringNode(INTEGER, CopyString(yytext)); } break;
case 84:
# line 270 "t2.y"
{ yyval.node = StringNode(FLOAT, CopyString(yytext)); } break;
case 85:
# line 272 "t2.y"
{ quoted = CopyString(yytext+1);
			  quoted[strlen(quoted)-1] = '\0';
			  yyval.node = StringNode(STRING, quoted);
			} break;
case 86:
# line 278 "t2.y"
{ yyval.node = StringNode(ID, CopyString(yytext)); } break;
	}
	goto yystack;  /* stack new state and value */
}
