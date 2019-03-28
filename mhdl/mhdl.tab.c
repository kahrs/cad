/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "mhdl.y" /* yacc.c:339  */


#include <stdio.h>
#include "mhdl.h"
#include "mhdl.debug"

void yyerror(char *);
int yylex(void);

extern Symbol *name_stack_ptr;

Cell *organelle;


#line 81 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    L_AS = 258,
    L_ASSOCIATE = 259,
    L_ATTRIBUTE = 260,
    L_CASE = 261,
    L_CHAR = 262,
    L_CLASS = 263,
    L_COERCION = 264,
    L_COLONS = 265,
    L_COLUMNS = 266,
    L_COMPONENT = 267,
    L_COMPONENTS = 268,
    L_CONFIGURATION = 269,
    L_CONNECT = 270,
    L_CONNECTOR = 271,
    L_CONNECTORS = 272,
    L_CONNECTION = 273,
    L_CONSTRAINT = 274,
    L_CONVERSION = 275,
    L_DEFAULT = 276,
    L_DEFINITION = 277,
    L_DEFINITIONS = 278,
    L_DERIVATIVE = 279,
    L_DIMENSION = 280,
    L_DOTS = 281,
    L_DOUBLE = 282,
    L_EACH = 283,
    L_ELSE = 284,
    L_END = 285,
    L_EQUATION = 286,
    L_EXCEPT = 287,
    L_FLOAT = 288,
    L_FOR = 289,
    L_FROM = 290,
    L_FUNCTION = 291,
    L_GENERATE = 292,
    L_GRAPHIC = 293,
    L_IDENTIFIER = 294,
    L_IF = 295,
    L_IN = 296,
    L_INCLUDES = 297,
    L_INSTANCE = 298,
    L_INTEGER = 299,
    L_INTEGRAL = 300,
    L_INVERSE = 301,
    L_LARROW = 302,
    L_LEQEQ = 303,
    L_LET = 304,
    L_LIBRARIES = 305,
    L_MEMBER = 306,
    L_MODEL = 307,
    L_MULTIPLIER = 308,
    L_NAMES = 309,
    L_OF = 310,
    L_OPERATOR = 311,
    L_PACKAGE = 312,
    L_PRIMITIVE = 313,
    L_PROPERTY = 314,
    L_RARROW = 315,
    L_REPORT = 316,
    L_ROW = 317,
    L_SET = 318,
    L_SIGNAL = 319,
    L_STRING = 320,
    L_STRUCTURE = 321,
    L_SUBTYPE = 322,
    L_TABLE = 323,
    L_THEN = 324,
    L_TITLE = 325,
    L_TYPE = 326,
    L_UNIT = 327,
    L_USE = 328,
    L_VARIATIONS = 329,
    L_WHERE = 330,
    L_WITH = 331
  };
#endif
/* Tokens.  */
#define L_AS 258
#define L_ASSOCIATE 259
#define L_ATTRIBUTE 260
#define L_CASE 261
#define L_CHAR 262
#define L_CLASS 263
#define L_COERCION 264
#define L_COLONS 265
#define L_COLUMNS 266
#define L_COMPONENT 267
#define L_COMPONENTS 268
#define L_CONFIGURATION 269
#define L_CONNECT 270
#define L_CONNECTOR 271
#define L_CONNECTORS 272
#define L_CONNECTION 273
#define L_CONSTRAINT 274
#define L_CONVERSION 275
#define L_DEFAULT 276
#define L_DEFINITION 277
#define L_DEFINITIONS 278
#define L_DERIVATIVE 279
#define L_DIMENSION 280
#define L_DOTS 281
#define L_DOUBLE 282
#define L_EACH 283
#define L_ELSE 284
#define L_END 285
#define L_EQUATION 286
#define L_EXCEPT 287
#define L_FLOAT 288
#define L_FOR 289
#define L_FROM 290
#define L_FUNCTION 291
#define L_GENERATE 292
#define L_GRAPHIC 293
#define L_IDENTIFIER 294
#define L_IF 295
#define L_IN 296
#define L_INCLUDES 297
#define L_INSTANCE 298
#define L_INTEGER 299
#define L_INTEGRAL 300
#define L_INVERSE 301
#define L_LARROW 302
#define L_LEQEQ 303
#define L_LET 304
#define L_LIBRARIES 305
#define L_MEMBER 306
#define L_MODEL 307
#define L_MULTIPLIER 308
#define L_NAMES 309
#define L_OF 310
#define L_OPERATOR 311
#define L_PACKAGE 312
#define L_PRIMITIVE 313
#define L_PROPERTY 314
#define L_RARROW 315
#define L_REPORT 316
#define L_ROW 317
#define L_SET 318
#define L_SIGNAL 319
#define L_STRING 320
#define L_STRUCTURE 321
#define L_SUBTYPE 322
#define L_TABLE 323
#define L_THEN 324
#define L_TITLE 325
#define L_TYPE 326
#define L_UNIT 327
#define L_USE 328
#define L_VARIATIONS 329
#define L_WHERE 330
#define L_WITH 331

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 16 "mhdl.y" /* yacc.c:355  */

	Node	*node;
	Bucket	*bucket;
	Symbol	*symbol;
	Type	*type;
	long	long_value;
	char	char_value;
	double	float_value;
	char	*string_value;

#line 284 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 301 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  79
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2301

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  98
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  199
/* YYNRULES -- Number of rules.  */
#define YYNRULES  394
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  746

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   331

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    92,
      90,    91,    84,     2,    86,    85,    80,    83,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    78,    87,
       2,    93,     2,     2,    82,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    96,    94,    97,    79,    95,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    88,    77,    89,    81,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    89,    89,    90,    91,    92,    93,    95,   100,   105,
     110,   113,   115,   118,   120,   123,   125,   128,   131,   136,
     142,   145,   147,   150,   153,   155,   158,   165,   168,   171,
     174,   177,   180,   182,   185,   188,   193,   195,   197,   200,
     205,   207,   210,   218,   221,   223,   226,   228,   231,   233,
     236,   238,   241,   244,   248,   251,   252,   254,   257,   260,
     262,   265,   272,   274,   277,   279,   282,   285,   287,   290,
     295,   300,   302,   305,   308,   314,   316,   319,   321,   324,
     326,   329,   331,   334,   336,   339,   341,   344,   349,   351,
     353,   355,   357,   359,   361,   363,   365,   367,   369,   371,
     374,   377,   380,   382,   384,   387,   392,   394,   397,   399,
     402,   404,   407,   411,   413,   416,   418,   422,   425,   429,
     432,   434,   437,   439,   442,   445,   447,   450,   451,   453,
     455,   458,   460,   463,   471,   473,   476,   479,   481,   484,
     486,   489,   491,   494,   497,   499,   502,   507,   509,   511,
     514,   516,   519,   521,   523,   525,   527,   530,   532,   535,
     538,   540,   543,   546,   552,   554,   558,   563,   569,   572,
     573,   575,   577,   580,   582,   585,   587,   590,   597,   603,
     605,   608,   611,   614,   617,   619,   621,   624,   626,   628,
     630,   632,   634,   636,   639,   643,   647,   651,   656,   663,
     666,   668,   671,   672,   674,   675,   677,   679,   682,   684,
     687,   689,   691,   693,   695,   697,   699,   701,   704,   709,
     711,   714,   716,   719,   723,   728,   731,   734,   739,   741,
     744,   747,   749,   752,   755,   757,   762,   767,   772,   778,
     782,   785,   788,   795,   798,   800,   803,   804,   806,   807,
     809,   811,   814,   817,   819,   822,   824,   826,   828,   830,
     832,   834,   836,   838,   840,   842,   844,   846,   848,   851,
     854,   856,   859,   861,   864,   866,   869,   871,   874,   876,
     879,   881,   884,   887,   892,   897,   901,   904,   908,   910,
     912,   914,   916,   918,   920,   922,   924,   927,   932,   934,
     937,   939,   942,   948,   950,   953,   955,   961,   969,   972,
     974,   977,   978,   980,   982,   985,   987,   989,   991,   994,
     997,   999,  1002,  1004,  1006,  1008,  1010,  1012,  1014,  1016,
    1018,  1020,  1023,  1030,  1033,  1035,  1038,  1040,  1043,  1045,
    1048,  1050,  1053,  1055,  1058,  1060,  1063,  1065,  1068,  1072,
    1077,  1080,  1082,  1085,  1089,  1091,  1096,  1097,  1100,  1102,
    1105,  1108,  1110,  1113,  1115,  1118,  1120,  1123,  1126,  1130,
    1132,  1134,  1137,  1142,  1144,  1147,  1152,  1154,  1157,  1159,
    1161,  1164,  1166,  1169,  1172,  1175,  1178,  1180,  1185,  1186,
    1187,  1192,  1195,  1197,  1200
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "L_AS", "L_ASSOCIATE", "L_ATTRIBUTE",
  "L_CASE", "L_CHAR", "L_CLASS", "L_COERCION", "L_COLONS", "L_COLUMNS",
  "L_COMPONENT", "L_COMPONENTS", "L_CONFIGURATION", "L_CONNECT",
  "L_CONNECTOR", "L_CONNECTORS", "L_CONNECTION", "L_CONSTRAINT",
  "L_CONVERSION", "L_DEFAULT", "L_DEFINITION", "L_DEFINITIONS",
  "L_DERIVATIVE", "L_DIMENSION", "L_DOTS", "L_DOUBLE", "L_EACH", "L_ELSE",
  "L_END", "L_EQUATION", "L_EXCEPT", "L_FLOAT", "L_FOR", "L_FROM",
  "L_FUNCTION", "L_GENERATE", "L_GRAPHIC", "L_IDENTIFIER", "L_IF", "L_IN",
  "L_INCLUDES", "L_INSTANCE", "L_INTEGER", "L_INTEGRAL", "L_INVERSE",
  "L_LARROW", "L_LEQEQ", "L_LET", "L_LIBRARIES", "L_MEMBER", "L_MODEL",
  "L_MULTIPLIER", "L_NAMES", "L_OF", "L_OPERATOR", "L_PACKAGE",
  "L_PRIMITIVE", "L_PROPERTY", "L_RARROW", "L_REPORT", "L_ROW", "L_SET",
  "L_SIGNAL", "L_STRING", "L_STRUCTURE", "L_SUBTYPE", "L_TABLE", "L_THEN",
  "L_TITLE", "L_TYPE", "L_UNIT", "L_USE", "L_VARIATIONS", "L_WHERE",
  "L_WITH", "'|'", "':'", "'^'", "'.'", "'~'", "'@'", "'/'", "'*'", "'-'",
  "','", "';'", "'{'", "'}'", "'('", "')'", "'\\''", "'='", "'\\\\'",
  "'_'", "'['", "']'", "$accept", "start", "abs_prop_def",
  "abs_prop_names", "alternative", "alternatives", "alt_rhs",
  "alt_rhs_guard", "associate_def", "associate_defs", "case_expr",
  "class_body", "class_constraint", "class_constraints", "class_def",
  "class_defs", "class_header", "class_types", "column_header",
  "column_names", "comp_alternatives", "comp_alternative",
  "comp_case_clause", "comp_clause", "comp_config", "comp_configs",
  "comp_def", "comp_def_head", "comp_def_opt", "comp_def_tail",
  "comp_defs", "comp_elseif_clause", "comp_if_clause", "comp_name",
  "comp_include", "components", "cond_expr", "config_body", "config_def",
  "config_def_tail", "connections", "conn_clause", "conn_opt_names",
  "conn_names", "conn_specs", "conn_spec", "constraint_def",
  "constraint_report", "constructed_type", "construct_defs",
  "constructors", "context", "conversion_spec", "deferred_type_def",
  "def_designator", "derivative", "designation", "designation_indicators",
  "dim_def", "dim_body", "indicators", "indicator_list", "indicator",
  "indicator_exp", "indicator_post", "eq_designation", "equation_def",
  "exposure_clause", "exposure_item", "exposures", "exprs", "expr",
  "for_generate_header", "for_tail", "function_apply", "function_args",
  "function_def", "function_defs", "generates", "generate_body",
  "generate_def", "generate_header", "generate_item", "generate_obj_kind",
  "guards", "guard", "guard_alts", "guard_alt", "hiding_clause", "hidings",
  "ids", "if_generate_header", "inclusions", "instance_header",
  "instance_spec", "instance_body", "instance_def", "integral",
  "integral_expr", "label", "lambda_abstract", "let_expr", "libraries",
  "library_names", "list", "literal", "model", "model_head", "model_tail",
  "model_inclusions", "model_library", "model_body", "model_items",
  "model_item", "multiplier_spec", "multiplier_tail", "name", "name_def",
  "named_values", "names", "nested_def", "nested_defs", "nested_def_list",
  "null", "op", "operator", "operator_apply", "package", "package_head",
  "package_tail", "package_inclusion", "package_library", "package_models",
  "pattern", "patterns", "physical_value", "prefix_expr",
  "primitive_value", "property_kind", "property_names", "qualifier",
  "qualifiers", "rhs", "rhs_guard", "selected_name", "selected_names",
  "simple_name", "simple_pattern_expr", "specified_type_def",
  "string_exprs", "struct_clause", "struct_config", "struct_config_tail",
  "struct_config_body", "struct_def", "struct_def_head", "struct_def_tail",
  "struct_inclusion", "struct_defs", "struct_comps", "struct_conns",
  "struct_func_create", "struct_items", "struct_item", "table_def",
  "table_head", "table_tail", "table_header", "table_column", "table_data",
  "table_data_rows", "table_entries", "table_entry",
  "table_generate_header", "table_row", "types", "type_component",
  "type_constructor", "type_def", "type_header", "type_item", "type_specs",
  "type_spec", "type_specifier", "type_term", "typed_expr", "unit_convert",
  "unit_def", "unit_variations", "value_def", "value_defs",
  "value_def_target", "variable", "variations", "variation_ids",
  "visibility_item", "where_clause", "where_context", "empty", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   124,    58,    94,
      46,   126,    64,    47,    42,    45,    44,    59,   123,   125,
      40,    41,    39,    61,    92,    95,    91,    93
};
# endif

#define YYPACT_NINF -506

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-506)))

#define YYTABLE_NINF -395

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1569,  2205,  -506,    -6,    -5,  -506,    -8,  2205,  -506,    58,
     -13,    22,  -506,    22,  2205,  -506,  -506,    26,  -506,  -506,
    -506,  1834,    65,  -506,  2205,    73,  -506,  -506,  -506,  -506,
    -506,  -506,  -506,  -506,  -506,  -506,   130,   100,  -506,  2205,
    -506,  -506,  -506,   130,  -506,    87,  -506,   162,  -506,   110,
    -506,   129,  -506,  -506,   118,   184,   204,   122,   220,   182,
     216,  1622,   218,  -506,  -506,  -506,  -506,  1834,  -506,  -506,
     -46,    12,  1887,  2205,  2205,   181,     6,   174,  -506,  -506,
    -506,  -506,    22,  -506,   232,  -506,  -506,  -506,   232,  -506,
      25,  -506,  2205,    -5,    29,  2205,    26,   187,   186,   188,
    -506,  2205,   192,    -5,  2205,   160,  -506,   257,    18,  -506,
     278,   203,   205,  1463,  -506,    57,  2205,    66,   108,  2205,
     242,   605,  2205,   243,  -506,  -506,  -506,   117,   125,  2205,
    2205,  2205,  -506,   143,  -506,    -5,   251,   929,  -506,   251,
     929,  -506,    11,   202,   212,   213,  -506,   217,  -506,   208,
     219,  -506,   181,   214,   210,  -506,  2205,   221,   273,   222,
    -506,   293,    57,  -506,  2205,   605,    -5,  -506,  -506,   223,
    2205,  2205,   230,  -506,  -506,   233,  -506,  -506,  -506,  -506,
    -506,  -506,  -506,  -506,  -506,  -506,  -506,  -506,   605,  -506,
    -506,  -506,   761,   605,  -506,   224,  -506,    84,  -506,  -506,
    2205,  -506,   249,  -506,   266,   270,  -506,   234,   292,    22,
    -506,  -506,  -506,    78,  -506,    21,   235,    -5,    -5,  -506,
      22,    22,    -5,    22,   280,   296,  2205,   112,   282,  -506,
      22,    22,   605,   286,  -506,  -506,  -506,   605,  -506,  -506,
    -506,  -506,  -506,  -506,   239,  -506,  -506,   290,  -506,   605,
    -506,  1675,   299,   929,   244,  -506,  -506,    22,  -506,  -506,
     232,  -506,  -506,   260,  -506,  -506,  -506,  -506,  -506,   929,
     302,  -506,   245,    62,   246,  -506,   102,   103,   142,  2205,
    -506,  -506,   247,  1940,   -34,  2205,  2205,  2205,   248,  -506,
     605,  -506,    57,    84,  -506,  -506,   240,  -506,  -506,   252,
    -506,   275,  -506,   329,   126,  -506,   275,   -37,   605,   605,
     395,   250,  -506,  -506,  2205,  2205,  2205,  -506,  -506,    -5,
      -5,    22,    22,  -506,   255,   261,  -506,  -506,   312,   263,
    -506,  -506,   276,   258,   169,   182,  -506,  -506,   265,  -506,
    -506,   -40,   269,   275,   298,   268,   275,  1223,   271,  -506,
     277,  -506,    -5,  -506,    22,   279,  -506,   281,  -506,    97,
    -506,   251,   348,  -506,  2205,   359,  -506,    22,   287,  -506,
    -506,  -506,  -506,   197,  -506,   197,  -506,   320,   142,  -506,
     333,   151,   171,  -506,  -506,   291,  2205,  2205,  -506,   233,
     303,  -506,   294,  -506,   295,  2205,    84,  -506,  -506,  2205,
    1622,    -3,   605,  -506,  -506,   175,  -506,   605,  -506,  -506,
    -506,  -506,  -506,  -506,  -506,  -506,  -506,   383,  -506,   301,
    -506,  -506,    -5,    -5,   304,   354,   360,   305,    -5,  2205,
     297,   319,  -506,  -506,  -506,   332,  -506,    37,  -506,    22,
      38,  -506,   605,    -5,  1622,   324,  -506,  1027,   313,  -506,
    -506,  1993,   324,  -506,   605,   263,  -506,  -506,  -506,   605,
      22,    22,  -506,   389,  -506,   317,  2205,  -506,   351,  -506,
    -506,  -506,    62,   246,   362,  -506,  -506,   321,   320,  -506,
    -506,  -506,  -506,   350,  -506,  -506,  -506,  2205,   322,  -506,
    -506,   334,  1516,  -506,  -506,  -506,  -506,  -506,  -506,  -506,
     -45,    22,  -506,     8,   343,  -506,    22,   335,    22,  -506,
     263,   366,  -506,   384,  -506,  -506,  -506,  -506,   361,   387,
     391,  -506,  -506,   319,  -506,   193,   122,  -506,   275,   324,
     337,   344,  1622,  -506,   398,   349,  -506,   357,  1728,  -506,
     277,   275,  -506,   358,   355,  -506,  -506,    22,  -506,  1410,
    -506,  -506,   369,   364,   409,   365,  -506,  -506,  -506,  2205,
     346,  -506,  -506,  -506,   370,   605,  -506,   301,    -5,   354,
     419,    15,   343,  -506,  -506,  -506,  -506,  2205,  -506,  -506,
    -506,   372,    -5,   396,  2205,  -506,  -506,  -506,   371,   605,
     605,  -506,   297,   432,  -506,  -506,  -506,  -506,  -506,  -506,
     376,  -506,    22,   378,    -5,     7,   458,   439,  1410,   385,
    -506,  2205,  -506,   393,   390,   388,   441,  -506,  -506,  -506,
     392,  -506,    -5,  2205,  2205,  -506,  -506,  -506,  -506,  -506,
     384,  -506,    -5,  -506,  -506,  1993,  -506,  -506,  -506,  2205,
     319,  -506,  -506,  -506,  -506,   232,  -506,  -506,   468,   400,
    -506,    22,   402,  -506,  -506,   409,  -506,  2046,    22,  -506,
    -506,  -506,  -506,  -506,   435,   423,   372,  -506,  1781,   407,
      -5,   449,  -506,   474,   251,  -506,   411,  -506,  -506,  -506,
    -506,  -506,  -506,   410,  -506,  2099,   -29,  2205,  -506,  -506,
     413,    -5,  -506,   417,  -506,  -506,  2205,  1410,  -506,  -506,
    -506,  -506,   416,  -506,  2205,  -506,  -506,  2205,   473,   480,
    -506,  -506,  1317,  -506,  2205,  2152,  -506,   450,    -5,  -506,
     471,   483,  -506,    22,    -5,  -506,    -5,  2205,    -5,  -506,
    -506,  -506,   426,   427,   446,   486,   428,  -506,    -5,    22,
     490,   480,  -506,    22,  -506,  -506
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,   196,     0,     0,   195,   285,     0,   194,     0,
       0,     0,   239,     0,     0,   197,   237,     0,   235,   236,
     238,     0,     0,   290,   394,     0,   256,   257,   258,     6,
     259,   260,   261,   262,   291,     5,   394,   287,   292,     0,
     234,   263,     4,   394,   264,   131,   265,     0,   222,     0,
     221,   266,   267,   268,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   285,   199,   243,   269,     0,   289,   233,
       0,   252,     0,     0,     0,   189,   188,     0,   187,     1,
       3,     2,     0,   204,   394,   205,   241,   248,   394,   249,
       0,   255,     0,     0,     0,     0,     0,     0,     0,     0,
     240,     0,     0,     0,     0,   285,   383,     0,   287,   228,
       0,   225,     0,     0,   229,     0,     0,     0,   252,     0,
     294,     0,     0,   293,   286,   252,   254,     0,     0,   193,
       0,     0,   296,     0,   186,     0,   202,   394,   203,   246,
     394,   247,     0,     0,   102,   108,   110,   113,   132,     0,
     285,   282,   138,   137,     0,   288,     0,     0,     0,     0,
     227,     0,     0,   181,     0,     0,     0,   231,   230,     0,
       0,     0,   281,   158,   378,   279,   183,   294,   293,   129,
      88,    89,    90,    91,    92,    93,    94,    95,     0,    97,
      98,    99,     0,     0,   355,   368,   366,   394,   354,   130,
       0,   295,     0,   191,   275,     0,   277,   190,   130,     0,
     184,   388,   128,     0,   389,   125,     0,     0,     0,   270,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   271,
       0,     0,     0,     0,   322,   323,   210,     0,   324,   325,
     326,   358,   211,   327,   383,   148,   328,     0,   147,   394,
     212,     0,   394,   206,     0,   213,   329,     0,   359,   215,
     394,   214,   330,   394,   149,   216,   217,   331,   207,   250,
     394,   251,     0,   108,   110,   101,     0,     0,     0,     0,
     319,   136,     0,     0,     0,     0,     0,     0,     0,   180,
       0,   380,     0,   394,   226,   232,     0,   280,   157,     0,
     278,    96,   369,   221,     0,   352,   362,     0,     0,     0,
     394,     0,   393,   253,     0,     0,     0,   192,   185,     0,
       0,     0,     0,   170,     0,    17,    19,    28,     0,    65,
      72,    73,     0,   394,     0,   168,   172,   171,     0,   308,
     333,   221,     0,   360,     0,   394,    29,     0,   394,   364,
     173,   174,     0,   122,     0,     0,   201,     0,   209,     0,
       9,   311,   394,   312,     0,   394,   337,     0,     0,   245,
     104,   109,   114,     0,   103,     0,   111,   394,     0,   112,
       0,     0,     0,    12,    20,     0,     0,     0,    10,    14,
      16,   161,     0,    58,     0,     0,   394,   379,   224,     0,
       0,     0,     0,   370,   371,     0,   365,   394,    83,   392,
      23,   372,   182,   274,   276,   124,   127,   125,   126,   163,
     165,   169,     0,     0,     0,    60,     0,     0,     0,     0,
       0,   394,   107,   152,   154,     0,   155,     0,   156,     0,
       0,    87,     0,     0,     0,   394,    22,     0,     0,   151,
     150,     0,   394,   176,     0,    64,   200,   198,   208,     0,
       0,   394,   317,   394,   318,     0,     0,   338,     0,   339,
     244,   242,     0,     0,     0,   116,   119,     0,   394,   272,
     273,    11,    15,     0,    13,   160,   100,     0,     0,   223,
     159,     0,     0,   139,   140,   368,   361,   351,   353,    25,
       0,     0,    18,     0,   221,    41,     0,     0,   394,    59,
      71,   394,   106,     0,   105,   376,   377,   153,     0,     0,
     394,   220,   219,   394,   367,    77,   366,    82,   357,   394,
     394,     0,    27,    26,     0,     0,   145,     0,     0,   177,
     363,     7,     8,     0,    67,    70,    68,     0,   315,   394,
     316,   336,   299,     0,     0,     0,   118,   117,   115,     0,
       0,   178,   142,   391,     0,   394,    84,   164,     0,   305,
       0,     0,     0,    40,    61,    62,    63,     0,    74,    76,
     387,   385,     0,     0,     0,   133,   135,   218,     0,     0,
       0,   297,     0,   394,   121,    21,   146,   144,   382,   175,
       0,    66,     0,     0,   394,     0,     0,     0,   313,     0,
     314,     0,    30,   167,     0,     0,   394,   162,   179,   141,
      24,   306,   394,     0,     0,    38,    39,    37,    36,    75,
       0,   348,     0,   143,   134,     0,    81,   356,   120,     0,
     394,   374,   381,    69,    49,   394,    53,    54,     0,     0,
      43,   394,     0,   321,   298,     0,    31,     0,     0,   332,
     335,   303,   302,   304,     0,     0,   386,   349,     0,     0,
       0,    85,   375,   394,    55,    56,     0,    48,   309,   307,
     310,   320,   166,     0,   346,     0,     0,   345,   343,   334,
       0,     0,    78,     0,    80,   373,     0,     0,    42,    45,
      57,   341,     0,   342,     0,   350,   347,     0,   300,     0,
      79,    86,     0,   340,   344,     0,    33,     0,     0,   301,
       0,     0,    51,   394,     0,    32,     0,     0,     0,    44,
      46,    47,     0,     0,     0,     0,     0,    34,     0,     0,
       0,     0,    52,     0,    50,    35
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -506,  -506,  -506,  -506,   238,  -506,  -506,  -506,  -506,  -506,
    -506,  -506,   215,   -43,  -506,  -506,  -506,  -506,  -506,  -506,
    -506,  -192,  -506,  -506,  -411,    23,   -81,  -506,  -506,  -506,
    -506,  -214,  -506,  -506,  -506,  -506,  -506,  -506,  -506,  -506,
    -506,  -506,  -506,  -506,  -322,  -506,  -506,  -506,  -506,  -506,
    -506,  -506,  -506,  -506,  -506,  -506,  -415,   394,  -506,  -506,
     253,  -132,  -123,   153,    52,  -506,  -506,  -506,   227,  -506,
     -15,   479,  -506,  -506,  -506,  -506,  -463,    88,  -506,  -506,
    -506,  -506,    86,  -506,  -506,   363,  -506,   144,  -506,    36,
    -117,  -506,   -87,  -506,   300,  -506,  -506,  -506,  -506,  -124,
    -506,  -506,   496,  -506,  -506,  -506,   515,  -506,  -506,  -506,
    -506,  -506,   401,  -113,  -506,  -506,    -4,   -50,   440,  -506,
     429,  -506,  -506,  -506,   -18,  -506,  -506,   519,  -506,  -506,
    -506,  -506,  -506,   -68,   476,  -506,  -506,  -506,  -506,   399,
     241,  -506,  -145,  -506,  -506,  -506,   152,    14,  -506,   -56,
    -470,  -152,  -506,  -506,  -327,  -506,  -506,  -506,  -506,  -506,
    -506,  -506,  -137,  -345,  -506,  -506,  -506,  -506,  -506,  -506,
    -506,  -506,  -142,  -506,  -122,   262,  -305,   -24,  -506,  -506,
    -180,   114,  -114,  -506,   165,  -506,  -506,  -506,  -505,   -36,
    -506,   -38,  -506,  -506,   -61,   367,   183,  -285,   619
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,   234,   359,   282,   283,   388,   389,   235,   325,
      26,   445,   499,   500,   236,   531,   237,   345,   467,   555,
     715,   716,   625,   626,   424,   425,   603,   604,   698,   729,
     605,   721,   627,   645,   673,   548,    27,   426,   238,   574,
     239,   462,   543,   544,   329,   330,   240,   578,   524,   668,
     525,   409,   670,   241,   194,    28,    91,   143,   242,   431,
     144,   145,   146,   379,   475,   593,   243,   211,   212,   213,
      70,   106,   245,   585,    30,   154,   491,   492,   634,   447,
     246,   247,   448,   439,   172,   173,   390,   391,   214,   419,
     614,   248,   136,   249,   410,   452,   250,    31,   288,   107,
      32,    33,    83,   133,    77,    34,    35,    36,   355,   137,
      84,   252,   253,   254,   255,   523,    37,   256,   110,   111,
     112,    62,   113,    38,    39,    40,    41,    42,    43,   368,
     140,    88,   270,    73,   127,    44,    45,    46,   257,    47,
     206,   207,   174,   175,    48,    49,    50,    51,   258,   553,
     709,   427,   662,   570,   259,   260,   679,   362,   607,   549,
     463,    52,   608,   261,   262,   263,   659,   365,   468,   616,
     685,   686,   687,   264,   688,   304,   196,   527,   265,   342,
     349,   350,   306,   529,   198,    53,   640,   266,   514,   267,
     538,   115,    54,   515,   581,   216,   300,   311,   312
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      58,   139,   450,    72,   406,   126,   126,   197,   398,    75,
     273,   109,   305,   251,   507,   512,   251,   291,   587,   274,
     449,   623,   121,   309,   321,   114,   386,    92,  -227,   564,
     455,    68,   129,     2,     6,   310,     6,   648,     4,    99,
     119,   565,   506,   387,   566,   120,    63,  -394,   704,    72,
       6,   293,   117,   322,     6,   624,   441,   108,   705,     5,
     404,    63,   205,   109,     6,     6,   162,    12,   150,   564,
       8,   521,  -284,    79,   301,    61,    63,   114,   518,   307,
     152,   568,   522,   130,    56,    57,   147,   192,   284,   149,
      16,    15,   131,   193,    18,    19,    20,    57,   122,   160,
    -384,   142,   450,   123,  -227,    57,   510,    17,  -390,   108,
     155,   489,    57,   319,     4,   142,    67,   195,   343,    57,
     449,    23,    24,   346,    99,    11,   292,    57,   305,   251,
      13,   215,   313,   108,   170,   672,   108,   526,   147,     4,
     357,     6,     6,    12,   309,   251,   277,   397,    60,     4,
     171,    63,   119,   371,   376,    74,   357,   177,   507,   310,
     533,   195,   294,    64,   320,    65,    16,   539,    12,     4,
      18,    19,    20,   361,    99,   459,   396,   638,    12,    90,
      82,   433,  -384,   460,   195,   434,   377,   435,   195,   195,
      94,    16,   373,   375,   122,    18,    19,    20,    12,   178,
      96,    16,    57,   200,   609,    18,    19,    20,   201,   336,
      93,   200,   402,   215,   326,   284,   202,   403,   331,    95,
     436,    16,   497,   251,     4,    18,    19,    20,   195,   209,
     210,   437,   378,   195,   134,   438,     6,   119,   163,    97,
    -284,   472,   479,    98,   591,   195,   151,   100,   205,   108,
     274,   101,   473,    12,   732,   102,   733,   122,   735,   116,
     380,   402,   480,   652,   381,   108,   498,   119,   741,   588,
     589,   132,   147,   147,   135,   156,    16,   157,   164,   124,
      18,    19,    20,   159,   526,   637,   195,   375,   165,   166,
    -272,  -273,   167,   217,   275,   276,   278,   277,   279,  -283,
     122,   281,   286,   290,   195,   195,   195,   170,   299,   314,
     295,   285,   287,  -252,   308,   415,   417,   315,   317,   333,
     316,   338,   323,   251,   334,   344,  -123,   347,   528,   354,
     364,   358,   367,   399,   383,   309,   370,   372,   395,   401,
     400,   411,   421,   108,   303,   541,   423,   422,   331,   428,
     493,   430,   609,   443,   429,    99,   444,    99,   440,   451,
     380,   318,   442,   454,   494,   461,   457,   652,   458,   147,
     466,   147,   327,   328,   471,   332,   474,   478,   481,   337,
     387,   487,   339,   340,   341,   486,   321,   501,   506,    90,
     508,   505,   509,   513,   493,   517,   108,   495,   195,   310,
     536,   303,   547,   195,   551,   554,   556,   180,   494,   360,
     559,   181,   557,   561,   182,   537,   571,   183,   502,   503,
     184,   562,   573,   580,   331,   251,   185,   577,   583,   582,
     592,   186,   584,   595,     6,   596,   597,   618,   195,   530,
     108,   602,   493,   108,   598,   601,   611,   187,   613,   622,
     195,   612,   639,   615,   188,   195,   494,   619,   630,   635,
     303,   189,   303,   642,   632,   644,   190,   191,   650,   651,
     655,   658,   653,   418,   420,   528,   657,   656,   565,    29,
      55,   676,   493,   407,   251,   192,    59,   677,   108,   681,
     690,   193,   691,    66,   694,   696,   494,   697,   700,   701,
      71,   707,   600,    76,   710,   713,   456,   718,   590,   720,
     726,   727,   728,   736,   737,   738,   739,   740,    86,   470,
     743,   385,   620,   725,   649,   408,   569,   744,   108,   374,
     558,   477,   532,   535,   485,   298,   272,   567,   682,    87,
      80,   269,   169,   161,    81,   108,   118,   416,   280,   348,
     128,    86,   125,   125,   303,   654,   719,   414,   674,   303,
     712,   195,   714,   703,   621,   636,   496,   628,   540,   666,
     405,   148,   484,   251,   153,   504,     0,     0,   631,     0,
     158,     0,     0,     0,   324,   195,   195,     0,   251,   519,
       0,   520,     0,     0,     0,   176,     0,     0,   179,   669,
     646,   199,     0,     0,   108,     0,   303,     0,   203,   204,
     208,     0,   542,   545,     0,     0,   244,   180,   661,   244,
       0,   181,     0,     0,   182,     0,     0,   183,   667,     0,
     184,     0,   693,     0,     0,   125,   185,     0,     0,   717,
       0,   186,     0,    78,     6,     0,     0,   717,     0,   296,
     297,     0,     0,   420,     0,    85,     0,   187,   572,     0,
     575,     0,    89,     0,   188,     0,   695,     0,     0,     0,
       0,   189,     0,     0,     0,     0,   190,   191,     0,   125,
       0,     0,     0,     0,     0,     0,     0,   708,     0,     0,
       0,     0,     0,   108,     0,   192,     0,     0,     0,   606,
       0,   193,     0,   138,     0,   335,     0,   141,   108,     0,
       0,     0,     0,     0,   503,     0,     0,   303,     0,     0,
     708,     0,   708,     0,   708,     0,     0,     0,     0,     0,
     353,     0,   244,     0,   708,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   244,     0,
       0,     0,     0,     0,   643,     0,   268,   606,   382,   271,
       0,     0,   125,     0,   392,   393,   394,     0,     0,     0,
       0,     0,     0,   180,     0,     0,     0,   181,   289,     0,
     182,     0,     0,   183,     0,     0,   184,     0,     4,     0,
       0,     0,   185,   412,   413,   204,     0,   186,     0,     0,
       6,     0,     0,   678,     0,     0,     0,     0,     0,     0,
     689,     0,     0,   187,     0,     0,     0,    12,     0,     0,
     188,     0,     0,     0,     0,     0,   244,   189,     0,     0,
       0,     0,   190,   191,     0,     0,     0,     0,     0,     0,
      16,     0,     0,   465,    18,    19,    20,     0,     0,     0,
       0,   192,   302,     0,     0,     0,     0,   193,     0,     0,
       0,     0,     0,     0,     0,   482,   483,     0,   351,     0,
       0,   356,     0,     0,   488,   730,     0,     0,   490,   363,
       0,     0,   366,     0,     0,     0,     0,     0,     0,   369,
       0,   742,     0,     0,     0,   745,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   511,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   244,     0,     0,   351,
       0,     0,     0,   218,   219,     1,     2,   220,   103,     0,
       0,     0,     0,   221,   222,   552,     0,     0,   223,     0,
     104,     0,   432,     3,   224,     0,     4,     0,     0,     0,
       0,     0,     5,   225,   446,     0,   560,   453,   105,   226,
       0,     0,   227,     8,     9,     0,     0,     0,    10,     0,
       0,   464,   228,     0,   469,    12,     0,    14,     0,     0,
       0,     0,     0,   229,    15,   230,   476,   231,     0,     0,
     232,   233,     0,     0,     0,     0,     0,     0,    16,     0,
      17,     0,    18,    19,    20,     0,     0,     0,     0,    21,
       0,     0,     0,    22,    23,    24,   351,     0,   244,     0,
       0,   218,   219,     1,     2,     0,   103,     0,   617,     0,
       0,   221,   222,     0,     0,     0,   223,     0,   104,     0,
     516,     3,     0,     0,     4,     0,   629,   534,     0,     0,
       5,   225,     0,   633,     0,     0,   105,   226,     0,     0,
       0,     8,     9,     0,     0,     0,    10,     0,     0,     0,
     546,     0,   550,    12,     0,    14,     0,   244,     0,     0,
     552,   229,    15,   230,     0,   231,     0,   476,     0,     0,
       0,     0,   664,   665,     0,     0,    16,     0,    17,     0,
      18,    19,    20,     0,     0,     0,     0,    21,   671,     0,
       0,    22,    23,    24,     0,     0,     0,   576,     0,     0,
     579,     0,     0,     0,     0,     0,   684,     0,     0,   586,
       0,     0,   516,     0,     0,     0,     0,     0,     0,   594,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   684,     0,   706,     0,   610,     0,
       0,     0,     0,     0,     0,   711,   244,     0,     0,     0,
       0,     0,     0,   684,   351,     0,   125,     0,     0,     0,
       0,   244,     0,   706,   125,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   734,     0,     0,     0,
       0,     0,   641,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   647,     0,     0,     0,   218,   219,     1,
       2,     0,   103,     0,     0,   660,     0,   221,   222,     0,
       0,   663,   223,     0,   104,     0,     0,     3,     0,     0,
       4,     0,     0,     0,     0,     0,     5,   225,     0,   516,
       0,     0,   105,   226,   675,     0,     0,     8,     9,     0,
     680,     0,    10,     0,     0,     0,     0,     0,     0,    12,
       0,    14,     0,     0,     0,     0,     0,   229,    15,   230,
       0,   231,   699,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    16,     0,    17,     0,    18,    19,    20,     0,
       0,     0,     0,    21,     0,     0,     0,    22,    23,    24,
       0,   218,   219,     1,     2,     0,   103,     0,   722,     0,
       0,   221,   222,     0,     0,     0,   223,     0,   104,     0,
       0,     3,   731,     0,     4,     0,     0,   723,     0,     0,
       5,   225,     0,     0,     0,     0,   105,   226,     0,     0,
     722,     8,     9,     0,     0,     0,    10,     0,     0,     0,
       0,     0,     0,    12,     0,    14,     0,     0,     0,     0,
       0,   229,    15,     0,     0,   231,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,     0,    17,     0,
      18,    19,    20,     0,     0,     0,     0,    21,     0,     0,
       0,    22,    23,    24,   218,   219,     1,     2,     0,   103,
       0,     0,     0,     0,   221,   222,     0,     0,     0,   223,
       0,   104,     0,     0,     3,     0,     0,     4,     0,     0,
       0,     0,     0,     5,   225,     0,     0,     0,     0,   105,
     226,     0,     0,     0,     8,     9,     0,     0,     0,    10,
       0,     0,     0,     0,     0,     0,    12,     0,    14,     1,
       2,     0,   103,     0,   229,    15,     0,     0,   231,     0,
       0,     0,     0,     0,   104,     0,     0,     3,     0,    16,
       4,    17,     0,    18,    19,    20,     5,     0,     0,     0,
      21,     0,   105,     7,    22,    23,    24,     8,     9,     0,
       0,     0,    10,     0,     0,     0,     0,     0,     0,    12,
       0,    14,     1,     2,     0,   103,     0,     0,    15,     0,
       0,     0,     0,     0,     0,     0,     0,   104,     0,     0,
       3,     0,    16,     4,    17,     0,    18,    19,    20,     5,
       0,     0,   168,    21,     0,   105,     7,    22,    23,    24,
       8,     9,     0,     0,     0,    10,     0,     0,     0,     0,
       0,     0,    12,     0,    14,     1,     2,     0,     0,     0,
       0,    15,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     0,    16,     4,    17,     0,    18,
      19,    20,     5,     0,     0,   563,    21,     0,     6,     7,
      22,    23,    24,     8,     9,     0,     0,     0,    10,     0,
       0,    11,     0,     0,     0,    12,    13,    14,     1,     2,
       0,   103,     0,     0,    15,     0,     0,     0,     0,     0,
       0,     0,     0,   104,     0,     0,     3,     0,    16,     4,
      17,     0,    18,    19,    20,     5,     0,     0,     0,    21,
       0,   105,     7,    22,    23,    24,     8,     9,     0,     0,
       0,    10,     0,     0,     0,     0,     0,     0,    12,     0,
      14,     1,     2,     0,     0,     0,     0,    15,     0,     0,
     352,     0,     0,     0,     0,     0,   164,     0,     0,     3,
       0,    16,     4,    17,     0,    18,    19,    20,     5,     0,
       0,     0,    21,     0,     6,     7,    22,    23,    24,     8,
       9,     0,     0,     0,    10,     0,     0,     0,     0,     0,
       0,    12,     0,    14,     1,     2,     0,     0,     0,     0,
      15,     0,     0,     0,     0,     0,     0,     0,     0,   104,
       0,     0,     3,     0,    16,     4,    17,     0,    18,    19,
      20,     5,     0,     0,     0,    21,     0,   105,     7,    22,
      23,    24,     8,     9,     0,     0,     0,    10,     0,     0,
       0,     0,     0,     0,    12,     0,    14,     1,     2,     0,
       0,     0,     0,    15,     0,     0,     0,     0,     0,     0,
       0,     0,   104,     0,     0,     3,     0,    16,     4,    17,
       0,    18,    19,    20,     5,     0,     0,   599,    21,     0,
     105,     7,    22,    23,    24,     8,     9,     0,     0,     0,
      10,     0,     0,     0,     0,     0,     0,    12,     0,    14,
       1,     2,     0,     0,     0,     0,    15,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,     0,
      16,     4,    17,     0,    18,    19,    20,     5,     0,     0,
     692,    21,     0,     6,     7,    22,    23,    24,     8,     9,
       0,     0,     0,    10,     0,     0,     0,     0,     0,     0,
      12,     0,    14,     1,     2,     0,     0,     0,     0,    15,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     3,     0,    16,     4,    17,     0,    18,    19,    20,
       5,     0,     0,     0,    21,    69,     6,     7,    22,    23,
      24,     8,     9,     0,     0,     0,    10,     0,     0,     0,
       0,     0,     0,    12,     0,    14,     1,     2,     0,     0,
       0,     0,    15,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,     0,    16,     4,    17,     0,
      18,    19,    20,     5,     0,     0,     0,    21,   124,     6,
       7,    22,    23,    24,     8,     9,     0,     0,     0,    10,
       0,     0,     0,     0,     0,     0,    12,     0,    14,     1,
       2,     0,     0,     0,     0,    15,     0,     0,     0,     0,
       0,     0,     0,     0,   104,     0,     0,     3,     0,    16,
       4,    17,     0,    18,    19,    20,     5,     0,     0,   384,
      21,     0,   105,     7,    22,    23,    24,     8,     9,     0,
       0,     0,    10,     0,     0,     0,     0,     0,     0,    12,
       0,    14,     1,     2,     0,     0,     0,     0,    15,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       3,     0,    16,     4,    17,     0,    18,    19,    20,     5,
       0,     0,     0,    21,     0,     6,     7,    22,    23,    24,
       8,     9,     0,     0,     0,    10,     0,     0,     0,     0,
       0,     0,    12,     0,    14,     1,     2,     0,     0,     0,
       0,    15,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     0,    16,     4,    17,     0,    18,
      19,    20,     5,     0,     0,   683,    21,     0,     6,     7,
      22,    23,    24,     8,     9,     0,     0,     0,    10,     0,
       0,     0,     0,     0,     0,    12,     0,    14,     1,     2,
       0,     0,     0,     0,    15,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     0,    16,     4,
      17,   724,    18,    19,    20,     5,     0,     0,   702,    21,
       0,     6,     7,    22,    23,    24,     8,     9,     0,     0,
       0,    10,     0,     0,     0,     0,     0,     0,    12,     0,
      14,     1,     2,     0,     0,     0,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
       0,    16,     4,    17,     0,    18,    19,    20,     5,     0,
       0,     0,    21,     0,     6,     7,    22,    23,    24,     8,
       9,     0,     0,     0,    10,     0,     0,     0,     0,     0,
       0,    12,     0,    14,     0,     0,     0,     0,     0,     0,
      15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    16,     0,    17,     0,    18,    19,
      20,     0,     0,     0,     0,    21,     0,     0,     0,    22,
      23,    24
};

static const yytype_int16 yycheck[] =
{
       4,    88,   347,    21,   309,    73,    74,   121,   293,    24,
     142,    61,   192,   137,   425,   430,   140,   162,   523,   142,
     347,     6,    10,    60,     3,    61,    60,    45,    10,   492,
     352,    17,    26,     7,    39,    75,    39,    30,    27,    57,
      86,    86,    34,    77,    89,    91,    39,    87,    77,    67,
      39,   165,    67,    32,    39,    40,   341,    61,    87,    33,
      97,    39,   130,   113,    39,    39,   104,    56,    39,   532,
      44,    33,    80,     0,   188,    88,    39,   113,    41,   193,
      95,    73,    44,    77,    90,    90,    90,    90,   156,    93,
      79,    65,    86,    96,    83,    84,    85,    90,    86,   103,
      82,    90,   447,    91,    86,    90,   428,    81,    87,   113,
      96,   396,    90,    35,    27,    90,    90,   121,   232,    90,
     447,    95,    96,   237,   142,    52,   164,    90,   308,   253,
      57,   135,   200,   137,    77,   640,   140,   442,   142,    27,
     253,    39,    39,    56,    60,   269,    84,   292,    90,    27,
      93,    39,    86,    91,   277,    90,   269,    91,   569,    75,
     445,   165,   166,    11,    86,    13,    79,   452,    56,    27,
      83,    84,    85,   260,   192,    78,   290,   592,    56,    92,
      50,    12,    82,    86,   188,    16,    44,    18,   192,   193,
      80,    79,    90,    90,    86,    83,    84,    85,    56,    91,
      82,    79,    90,    86,   549,    83,    84,    85,    91,   227,
      48,    86,    86,   217,   218,   283,    91,    91,   222,    90,
      51,    79,   402,   347,    27,    83,    84,    85,   232,    86,
      87,    62,    90,   237,    82,    66,    39,    86,    78,    55,
      80,   373,    91,    39,   529,   249,    94,    27,   316,   253,
     373,    69,   375,    56,   724,    39,   726,    86,   728,    41,
     278,    86,    91,   608,   279,   269,    91,    86,   738,    76,
      77,    97,   276,   277,    42,    88,    79,    91,    21,    91,
      83,    84,    85,    91,   589,   590,   290,    90,    10,    86,
      48,    48,    87,    42,    92,    83,    79,    84,    90,    80,
      86,    91,    29,    10,   308,   309,   310,    77,    75,    60,
      87,    90,    90,    47,    90,   319,   320,    47,    26,    39,
      86,    39,    87,   447,    28,    39,    87,    37,   442,    30,
      70,    87,    30,    93,    87,    60,    91,    91,    90,    10,
      88,    91,    87,   347,   192,   459,    34,    86,   352,    86,
     400,    93,   697,    55,    78,   373,    88,   375,    93,    88,
     378,   209,    93,    86,   400,    17,    87,   712,    87,   373,
      11,   375,   220,   221,    87,   223,    56,    44,    87,   227,
      77,    86,   230,   231,   232,    91,     3,    86,    34,    92,
      30,    87,    87,    74,   444,    63,   400,   401,   402,    75,
      87,   249,    13,   407,    87,    54,    44,    12,   444,   257,
      60,    16,    91,    91,    19,   451,    73,    22,   422,   423,
      25,    87,    87,    39,   428,   549,    31,    61,    41,    68,
      93,    36,    41,    89,    39,    37,    87,    91,   442,   443,
     444,    86,   492,   447,    87,    87,    77,    52,    39,    30,
     454,    87,    20,    88,    59,   459,   492,    87,    86,    88,
     308,    66,   310,    87,    68,    87,    71,    72,    10,    30,
      77,    30,    87,   321,   322,   589,    88,    87,    86,     0,
       1,    13,   532,    88,   608,    90,     7,    87,   492,    87,
      55,    96,    69,    14,    87,    46,   532,    23,    87,    89,
      21,    88,   538,    24,    87,    89,   354,    34,   526,    29,
      60,    40,    29,    87,    87,    69,    30,    89,    39,   367,
      30,   283,   565,   715,   605,   310,   503,   741,   532,   276,
     478,   378,   444,   447,   390,   172,   142,   501,   655,    43,
      25,   140,   113,   103,    25,   549,    67,   320,   149,   249,
      74,    72,    73,    74,   402,   611,   708,   316,   645,   407,
     697,   565,   704,   685,   568,   589,   401,   571,   454,   630,
     308,    92,   389,   697,    95,   423,    -1,    -1,   582,    -1,
     101,    -1,    -1,    -1,   217,   589,   590,    -1,   712,   437,
      -1,   439,    -1,    -1,    -1,   116,    -1,    -1,   119,   635,
     604,   122,    -1,    -1,   608,    -1,   454,    -1,   129,   130,
     131,    -1,   460,   461,    -1,    -1,   137,    12,   622,   140,
      -1,    16,    -1,    -1,    19,    -1,    -1,    22,   632,    -1,
      25,    -1,   668,    -1,    -1,   156,    31,    -1,    -1,   707,
      -1,    36,    -1,    24,    39,    -1,    -1,   715,    -1,   170,
     171,    -1,    -1,   501,    -1,    36,    -1,    52,   506,    -1,
     508,    -1,    43,    -1,    59,    -1,   670,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    -1,    71,    72,    -1,   200,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   691,    -1,    -1,
      -1,    -1,    -1,   697,    -1,    90,    -1,    -1,    -1,   547,
      -1,    96,    -1,    84,    -1,   226,    -1,    88,   712,    -1,
      -1,    -1,    -1,    -1,   718,    -1,    -1,   565,    -1,    -1,
     724,    -1,   726,    -1,   728,    -1,    -1,    -1,    -1,    -1,
     251,    -1,   253,    -1,   738,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   269,    -1,
      -1,    -1,    -1,    -1,   602,    -1,   137,   605,   279,   140,
      -1,    -1,   283,    -1,   285,   286,   287,    -1,    -1,    -1,
      -1,    -1,    -1,    12,    -1,    -1,    -1,    16,   159,    -1,
      19,    -1,    -1,    22,    -1,    -1,    25,    -1,    27,    -1,
      -1,    -1,    31,   314,   315,   316,    -1,    36,    -1,    -1,
      39,    -1,    -1,   651,    -1,    -1,    -1,    -1,    -1,    -1,
     658,    -1,    -1,    52,    -1,    -1,    -1,    56,    -1,    -1,
      59,    -1,    -1,    -1,    -1,    -1,   347,    66,    -1,    -1,
      -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    -1,   364,    83,    84,    85,    -1,    -1,    -1,
      -1,    90,    91,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   386,   387,    -1,   249,    -1,
      -1,   252,    -1,    -1,   395,   723,    -1,    -1,   399,   260,
      -1,    -1,   263,    -1,    -1,    -1,    -1,    -1,    -1,   270,
      -1,   739,    -1,    -1,    -1,   743,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   429,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   447,    -1,    -1,   310,
      -1,    -1,    -1,     4,     5,     6,     7,     8,     9,    -1,
      -1,    -1,    -1,    14,    15,   466,    -1,    -1,    19,    -1,
      21,    -1,   333,    24,    25,    -1,    27,    -1,    -1,    -1,
      -1,    -1,    33,    34,   345,    -1,   487,   348,    39,    40,
      -1,    -1,    43,    44,    45,    -1,    -1,    -1,    49,    -1,
      -1,   362,    53,    -1,   365,    56,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,   377,    68,    -1,    -1,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      81,    -1,    83,    84,    85,    -1,    -1,    -1,    -1,    90,
      -1,    -1,    -1,    94,    95,    96,   407,    -1,   549,    -1,
      -1,     4,     5,     6,     7,    -1,     9,    -1,   559,    -1,
      -1,    14,    15,    -1,    -1,    -1,    19,    -1,    21,    -1,
     431,    24,    -1,    -1,    27,    -1,   577,    30,    -1,    -1,
      33,    34,    -1,   584,    -1,    -1,    39,    40,    -1,    -1,
      -1,    44,    45,    -1,    -1,    -1,    49,    -1,    -1,    -1,
     461,    -1,   463,    56,    -1,    58,    -1,   608,    -1,    -1,
     611,    64,    65,    66,    -1,    68,    -1,   478,    -1,    -1,
      -1,    -1,   623,   624,    -1,    -1,    79,    -1,    81,    -1,
      83,    84,    85,    -1,    -1,    -1,    -1,    90,   639,    -1,
      -1,    94,    95,    96,    -1,    -1,    -1,   508,    -1,    -1,
     511,    -1,    -1,    -1,    -1,    -1,   657,    -1,    -1,   520,
      -1,    -1,   523,    -1,    -1,    -1,    -1,    -1,    -1,   530,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   685,    -1,   687,    -1,   549,    -1,
      -1,    -1,    -1,    -1,    -1,   696,   697,    -1,    -1,    -1,
      -1,    -1,    -1,   704,   565,    -1,   707,    -1,    -1,    -1,
      -1,   712,    -1,   714,   715,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   727,    -1,    -1,    -1,
      -1,    -1,   593,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   604,    -1,    -1,    -1,     4,     5,     6,
       7,    -1,     9,    -1,    -1,   616,    -1,    14,    15,    -1,
      -1,   622,    19,    -1,    21,    -1,    -1,    24,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,   640,
      -1,    -1,    39,    40,   645,    -1,    -1,    44,    45,    -1,
     651,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    58,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      -1,    68,   673,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    81,    -1,    83,    84,    85,    -1,
      -1,    -1,    -1,    90,    -1,    -1,    -1,    94,    95,    96,
      -1,     4,     5,     6,     7,    -1,     9,    -1,   709,    -1,
      -1,    14,    15,    -1,    -1,    -1,    19,    -1,    21,    -1,
      -1,    24,   723,    -1,    27,    -1,    -1,    30,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    39,    40,    -1,    -1,
     741,    44,    45,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    58,    -1,    -1,    -1,    -1,
      -1,    64,    65,    -1,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,
      83,    84,    85,    -1,    -1,    -1,    -1,    90,    -1,    -1,
      -1,    94,    95,    96,     4,     5,     6,     7,    -1,     9,
      -1,    -1,    -1,    -1,    14,    15,    -1,    -1,    -1,    19,
      -1,    21,    -1,    -1,    24,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    39,
      40,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    58,     6,
       7,    -1,     9,    -1,    64,    65,    -1,    -1,    68,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    -1,    24,    -1,    79,
      27,    81,    -1,    83,    84,    85,    33,    -1,    -1,    -1,
      90,    -1,    39,    40,    94,    95,    96,    44,    45,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    58,     6,     7,    -1,     9,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    -1,
      24,    -1,    79,    27,    81,    -1,    83,    84,    85,    33,
      -1,    -1,    89,    90,    -1,    39,    40,    94,    95,    96,
      44,    45,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    58,     6,     7,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    79,    27,    81,    -1,    83,
      84,    85,    33,    -1,    -1,    89,    90,    -1,    39,    40,
      94,    95,    96,    44,    45,    -1,    -1,    -1,    49,    -1,
      -1,    52,    -1,    -1,    -1,    56,    57,    58,     6,     7,
      -1,     9,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    -1,    24,    -1,    79,    27,
      81,    -1,    83,    84,    85,    33,    -1,    -1,    -1,    90,
      -1,    39,    40,    94,    95,    96,    44,    45,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,
      58,     6,     7,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      15,    -1,    -1,    -1,    -1,    -1,    21,    -1,    -1,    24,
      -1,    79,    27,    81,    -1,    83,    84,    85,    33,    -1,
      -1,    -1,    90,    -1,    39,    40,    94,    95,    96,    44,
      45,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    58,     6,     7,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    -1,    24,    -1,    79,    27,    81,    -1,    83,    84,
      85,    33,    -1,    -1,    -1,    90,    -1,    39,    40,    94,
      95,    96,    44,    45,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    58,     6,     7,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    -1,    24,    -1,    79,    27,    81,
      -1,    83,    84,    85,    33,    -1,    -1,    89,    90,    -1,
      39,    40,    94,    95,    96,    44,    45,    -1,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    58,
       6,     7,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      79,    27,    81,    -1,    83,    84,    85,    33,    -1,    -1,
      89,    90,    -1,    39,    40,    94,    95,    96,    44,    45,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    58,     6,     7,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    79,    27,    81,    -1,    83,    84,    85,
      33,    -1,    -1,    -1,    90,    91,    39,    40,    94,    95,
      96,    44,    45,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    58,     6,     7,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    -1,    79,    27,    81,    -1,
      83,    84,    85,    33,    -1,    -1,    -1,    90,    91,    39,
      40,    94,    95,    96,    44,    45,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,    58,     6,
       7,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    -1,    -1,    24,    -1,    79,
      27,    81,    -1,    83,    84,    85,    33,    -1,    -1,    89,
      90,    -1,    39,    40,    94,    95,    96,    44,    45,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    58,     6,     7,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    79,    27,    81,    -1,    83,    84,    85,    33,
      -1,    -1,    -1,    90,    -1,    39,    40,    94,    95,    96,
      44,    45,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    58,     6,     7,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    79,    27,    81,    -1,    83,
      84,    85,    33,    -1,    -1,    89,    90,    -1,    39,    40,
      94,    95,    96,    44,    45,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    58,     6,     7,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    79,    27,
      81,    29,    83,    84,    85,    33,    -1,    -1,    89,    90,
      -1,    39,    40,    94,    95,    96,    44,    45,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,
      58,     6,     7,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      -1,    79,    27,    81,    -1,    83,    84,    85,    33,    -1,
      -1,    -1,    90,    -1,    39,    40,    94,    95,    96,    44,
      45,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    83,    84,
      85,    -1,    -1,    -1,    -1,    90,    -1,    -1,    -1,    94,
      95,    96
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     6,     7,    24,    27,    33,    39,    40,    44,    45,
      49,    52,    56,    57,    58,    65,    79,    81,    83,    84,
      85,    90,    94,    95,    96,    99,   108,   134,   153,   169,
     172,   195,   198,   199,   203,   204,   205,   214,   221,   222,
     223,   224,   225,   226,   233,   234,   235,   237,   242,   243,
     244,   245,   259,   283,   290,   169,    90,    90,   214,   169,
      90,    88,   219,    39,   244,   244,   169,    90,   245,    91,
     168,   169,   222,   231,    90,   168,   169,   202,   296,     0,
     204,   225,    50,   200,   208,   296,   169,   200,   229,   296,
      92,   154,   222,    48,    80,    90,    82,    55,    39,   222,
      27,    69,    39,     9,    21,    39,   169,   197,   214,   215,
     216,   217,   218,   220,   287,   289,    41,   168,   169,    86,
      91,    10,    86,    91,    91,   169,   231,   232,   232,    26,
      77,    86,    97,   201,   244,    42,   190,   207,   296,   190,
     228,   296,    90,   155,   158,   159,   160,   214,   169,   214,
      39,   244,   168,   169,   173,   245,    88,    91,   169,    91,
     214,   216,   289,    78,    21,    10,    86,    87,    89,   218,
      77,    93,   182,   183,   240,   241,   169,    91,    91,   169,
      12,    16,    19,    22,    25,    31,    36,    52,    59,    66,
      71,    72,    90,    96,   152,   214,   274,   280,   282,   169,
      86,    91,    91,   169,   169,   231,   238,   239,   169,    86,
      87,   165,   166,   167,   186,   214,   293,    42,     4,     5,
       8,    14,    15,    19,    25,    34,    40,    43,    53,    64,
      66,    68,    71,    72,   100,   106,   112,   114,   136,   138,
     144,   151,   156,   164,   169,   170,   178,   179,   189,   191,
     194,   197,   209,   210,   211,   212,   215,   236,   246,   252,
     253,   261,   262,   263,   271,   276,   285,   287,   296,   210,
     230,   296,   155,   159,   160,    92,    83,    84,    79,    90,
     237,    91,   102,   103,   231,    90,    29,    90,   196,   296,
      10,   240,   289,   280,   214,    87,   169,   169,   183,    75,
     294,   280,    91,   244,   273,   278,   280,   280,    90,    60,
      75,   295,   296,   231,    60,    47,    86,    26,   244,    35,
      86,     3,    32,    87,   293,   107,   214,   244,   244,   142,
     143,   214,   244,    39,    28,   169,   222,   244,    39,   244,
     244,   244,   277,   280,    39,   115,   280,    37,   192,   278,
     279,   296,    15,   169,    30,   206,   296,   211,    87,   101,
     244,   190,   255,   296,    70,   265,   296,    30,   227,   296,
      91,    91,    91,    90,   158,    90,   160,    44,    90,   161,
     222,   168,   169,    87,    89,   102,    60,    77,   104,   105,
     184,   185,   169,   169,   169,    90,   280,   240,   295,    93,
      88,    10,    86,    91,    97,   273,   274,    88,   110,   149,
     192,    91,   169,   169,   238,   214,   166,   214,   244,   187,
     244,    87,    86,    34,   122,   123,   135,   249,    86,    78,
      93,   157,   296,    12,    16,    18,    51,    62,    66,   181,
      93,   295,    93,    55,    88,   109,   296,   177,   180,   252,
     261,    88,   193,   296,    86,   142,   244,    87,    87,    78,
      86,    17,   139,   258,   296,   169,    11,   116,   266,   296,
     244,    87,   159,   160,    56,   162,   296,   161,    44,    91,
      91,    87,   169,   169,   294,   185,    91,    86,   169,   295,
     169,   174,   175,   215,   287,   214,   282,   278,    91,   110,
     111,    86,   214,   214,   244,    87,    34,   122,    30,    87,
     142,   169,   154,    74,   286,   291,   296,    63,    41,   244,
     244,    33,    44,   213,   146,   148,   274,   275,   280,   281,
     214,   113,   175,   295,    30,   180,    87,   287,   288,   295,
     279,   280,   244,   140,   141,   244,   296,    13,   133,   257,
     296,    87,   169,   247,    54,   117,    44,    91,   162,    60,
     169,    91,    87,    89,   174,    86,    89,   187,    73,   123,
     251,    73,   244,    87,   137,   244,   296,    61,   145,   296,
      39,   292,    68,    41,    41,   171,   296,   286,    76,    77,
     222,   295,    93,   163,   296,    89,    37,    87,    87,    89,
     287,    87,    86,   124,   125,   128,   244,   256,   260,   261,
     296,    77,    87,    39,   188,    88,   267,   169,    91,    87,
     111,   214,    30,     6,    40,   120,   121,   130,   214,   169,
      86,   214,    68,   169,   176,    88,   275,   274,   154,    20,
     284,   296,    87,   244,    87,   131,   214,   296,    30,   124,
      10,    30,   261,    87,   247,    77,    87,    88,    30,   264,
     296,   214,   250,   296,   169,   169,   292,   214,   147,   287,
     150,   169,   286,   132,   190,   296,    13,    87,   244,   254,
     296,    87,   188,    89,   169,   268,   269,   270,   272,   244,
      55,    69,    89,   287,    87,   214,    46,    23,   126,   296,
      87,    89,    89,   272,    77,    87,   169,    88,   214,   248,
      87,   169,   260,    89,   270,   118,   119,   231,    34,   249,
      29,   129,   296,    30,    29,   119,    60,    40,    29,   127,
     244,   296,   248,   248,   169,   248,    87,    87,    69,    30,
      89,   248,   244,    30,   129,   244
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,    98,    99,    99,    99,    99,    99,   100,   101,   101,
     102,   103,   103,   104,   104,   105,   105,   106,   107,   107,
     108,   109,   109,   110,   111,   111,   112,   113,   114,   115,
     116,   117,   118,   118,   119,   120,   121,   121,   121,   122,
     123,   123,   124,   125,   126,   126,   127,   127,   128,   128,
     129,   129,   130,   131,   131,   132,   132,   133,   134,   135,
     135,   136,   137,   137,   138,   138,   139,   140,   140,   141,
     141,   142,   142,   143,   144,   145,   145,   146,   146,   147,
     147,   148,   148,   149,   149,   150,   150,   151,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     153,   154,   155,   155,   155,   156,   157,   157,   158,   158,
     159,   159,   160,   160,   160,   161,   161,   161,   162,   162,
     163,   163,   164,   164,   165,   166,   166,   167,   167,   168,
     168,   169,   169,   170,   171,   171,   172,   173,   173,   174,
     174,   175,   175,   176,   177,   177,   178,   179,   179,   179,
     180,   180,   181,   181,   181,   181,   181,   182,   182,   183,
     184,   184,   185,   186,   187,   187,   188,   188,   189,   190,
     190,   191,   191,   192,   192,   193,   193,   194,   195,   196,
     196,   197,   198,   199,   200,   201,   201,   202,   202,   202,
     202,   202,   202,   202,   203,   203,   203,   203,   204,   205,
     206,   206,   207,   207,   208,   208,   209,   209,   210,   210,
     211,   211,   211,   211,   211,   211,   211,   211,   212,   213,
     213,   214,   214,   215,   215,   216,   217,   217,   218,   218,
     219,   220,   220,   221,   222,   222,   222,   222,   222,   223,
     223,   224,   225,   226,   227,   227,   228,   228,   229,   229,
     230,   230,   231,   232,   232,   233,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   235,
     236,   236,   237,   237,   238,   238,   239,   239,   240,   240,
     241,   241,   242,   243,   243,   244,   244,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   246,   247,   247,
     248,   248,   249,   250,   250,   251,   251,   252,   253,   254,
     254,   255,   255,   256,   256,   257,   257,   258,   258,   259,
     260,   260,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   262,   263,   264,   264,   265,   265,   266,   266,
     267,   267,   268,   268,   269,   269,   270,   270,   271,   271,
     272,   273,   273,   274,   274,   274,   275,   275,   276,   276,
     277,   278,   278,   279,   279,   280,   280,   281,   282,   282,
     282,   282,   283,   284,   284,   285,   286,   286,   287,   287,
     287,   288,   288,   289,   290,   291,   292,   292,   293,   293,
     293,   294,   295,   295,   296
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     4,     3,     1,
       2,     3,     2,     2,     1,     2,     1,     2,     3,     1,
       6,     3,     1,     1,     3,     1,     4,     1,     2,     1,
       3,     3,     2,     1,     4,    11,     1,     1,     1,     4,
       3,     2,     4,     2,     4,     1,     1,     1,     3,     2,
       6,     1,     9,     1,     1,     1,     1,     5,     6,     2,
       1,     5,     1,     1,     3,     2,     3,     1,     1,     3,
       1,     3,     1,     1,     5,     2,     1,     1,     5,     3,
       2,     3,     1,     1,     3,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       7,     3,     1,     3,     3,     4,     2,     1,     1,     3,
       1,     3,     3,     1,     3,     3,     2,     3,     2,     1,
       2,     1,     2,     1,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     5,     2,     1,     4,     1,     1,     1,
       1,     3,     2,     1,     3,     2,     5,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     2,     1,     4,
       2,     1,     4,     3,     3,     1,     3,     1,     2,     4,
       3,     2,     2,     1,     1,     3,     1,     4,     8,     5,
       1,     2,     6,     4,     3,     3,     1,     1,     1,     1,
       3,     3,     4,     2,     1,     1,     1,     1,     6,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     1,
       1,     1,     1,     5,     4,     1,     3,     1,     1,     1,
       3,     2,     3,     2,     1,     1,     1,     1,     1,     1,
       3,     2,     6,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     3,     3,     3,     1,     3,     1,     2,     1,
       2,     1,     3,     3,     1,     1,     3,     1,     3,     2,
       1,     1,     1,     3,     3,     4,     3,     5,     3,     1,
       1,     2,     5,     1,     1,     1,     2,     7,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     6,     2,     2,     1,     3,     1,     1,     1,
       5,     4,     2,     1,     3,     1,     1,     2,     6,     7,
       2,     3,     1,     4,     1,     1,     3,     1,     1,     1,
       1,     3,     1,     3,     1,     3,     1,     1,     1,     2,
       3,     3,     6,     3,     1,     7,     1,     1,     2,     4,
       3,     3,     2,     1,     1,     2,     3,     1,     1,     1,
       1,     4,     2,     1,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 7:
#line 96 "mhdl.y" /* yacc.c:1646  */
    { new_names((yyvsp[-2].node), (yyvsp[-3].long_value), (yyvsp[0].node));
				  (yyval.node) = new_node(O_ABS_DEF, (yyvsp[-2].node), (yyvsp[0].node));
				}
#line 2283 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 101 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_NAME, Nil(Node), Nil(Node));
				  (yyval.node) -> symbol = define_node((yyvsp[0].node), ABS_PROP_NAME);
				  (yyval.node) = new_node(O_PAIR, (yyval.node), (yyvsp[-2].node));
				}
#line 2292 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 106 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_NAME, Nil(Node), Nil(Node));
				  (yyval.node) -> symbol = define_node((yyvsp[0].node), ABS_PROP_NAME);
				}
#line 2300 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 111 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_ALT, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2306 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 114 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 2312 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 116 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-1].node), Nil(Node)); }
#line 2318 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 119 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_RHS, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2324 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 121 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_RHS, (yyvsp[0].node), Nil(Node)); }
#line 2330 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 124 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_GUARD, (yyvsp[0].node), Nil(Node)); }
#line 2336 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 126 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2342 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 129 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_ASSOC, (yyvsp[0].node), Nil(Node)); }
#line 2348 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 132 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_NAME, Nil(Node), Nil(Node));
				  (yyval.node) -> symbol = use_name((yyvsp[0].node));
				  (yyval.node) = new_node(O_PAIR, (yyval.node), (yyvsp[-2].node));
				}
#line 2357 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 137 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_NAME, Nil(Node), Nil(Node));
				  (yyval.node) -> symbol = use_name((yyvsp[0].node));
				}
#line 2365 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 143 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_CASE, (yyvsp[-4].node), (yyvsp[-1].node)); }
#line 2371 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 146 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2377 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 148 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 2383 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 151 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2389 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 154 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2395 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 156 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2401 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 159 "mhdl.y" /* yacc.c:1646  */
    { pop_name();
				  (yyvsp[-3].symbol) -> cell = new_class((yyvsp[-3].symbol), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
				  (yyval.node) = new_node(O_NAME, Nil(Node), Nil(Node));
				  (yyval.node) -> symbol = (yyvsp[-3].symbol);
				}
#line 2411 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 166 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2417 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 169 "mhdl.y" /* yacc.c:1646  */
    { (yyval.symbol) = push_name(define_node((yyvsp[0].node), CLASS_NAME)); }
#line 2423 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 172 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2429 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 175 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2435 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 178 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2441 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 181 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2447 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 183 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[0].node), Nil(Node)); }
#line 2453 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 186 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_ALT, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2459 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 189 "mhdl.y" /* yacc.c:1646  */
    { check_name((yyvsp[0].node), N_STRUCTURE);
				  (yyval.node) = new_node(O_CASE, (yyvsp[-9].node), new_node(O_ELSE, (yyvsp[-6].node), (yyvsp[-4].node)));
				}
#line 2467 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 194 "mhdl.y" /* yacc.c:1646  */
    { check_name((yyvsp[0].node), N_STRUCTURE); (yyval.node) = (yyvsp[0].node); }
#line 2473 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 196 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2479 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 198 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2485 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 201 "mhdl.y" /* yacc.c:1646  */
    { check_name((yyvsp[-2].node), N_COMPONENT);
				  (yyval.node) = new_node(O_CONFIG, (yyvsp[-2].node), (yyvsp[0].node));
				}
#line 2493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 206 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 2499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 208 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-1].node), Nil(Node)); }
#line 2505 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 211 "mhdl.y" /* yacc.c:1646  */
    { pop_name();
				  organelle = new_structure((yyvsp[-3].symbol), F_COMPONENT, (yyvsp[-2].node), Nil(Node), (yyvsp[0].node));
				  (yyvsp[-3].symbol) -> cell = ((yyvsp[-3].symbol) -> cell)? merge_structs((yyvsp[-3].symbol) -> cell, organelle) : organelle;
				  (yyval.node) = new_node(O_NAME, Nil(Node), Nil(Node));
				  (yyval.node) -> symbol = (yyvsp[-3].symbol);
				}
#line 2516 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 219 "mhdl.y" /* yacc.c:1646  */
    { (yyval.symbol) = push_name(define_node((yyvsp[-1].node), COMPONENT_NAME)); }
#line 2522 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 222 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-2].node); }
#line 2528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 224 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 2534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 227 "mhdl.y" /* yacc.c:1646  */
    { (yyval.symbol) = use_name((yyvsp[0].node)); }
#line 2540 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 229 "mhdl.y" /* yacc.c:1646  */
    { (yyval.symbol) = Nil(Symbol); }
#line 2546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 232 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 2552 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 234 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-1].node), Nil(Node)); }
#line 2558 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 237 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_IF, (yyvsp[-3].node), new_node(O_ELSE, (yyvsp[-1].node), (yyvsp[0].node))); }
#line 2564 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 239 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 2570 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 242 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_IF, (yyvsp[-7].node), new_node(O_ELSE, (yyvsp[-5].node), (yyvsp[-2].node))); }
#line 2576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 245 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_NAME, Nil(Node), Nil(Node));
				  (yyval.node) -> symbol = use_name((yyvsp[0].node));
				}
#line 2584 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 249 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 2590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 255 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-3].node); }
#line 2596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 258 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_IF, (yyvsp[-4].node), new_node(O_ELSE, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 2602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 261 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2608 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 263 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2614 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 266 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_NAME, Nil(Node), Nil(Node));
				  (yyval.node) -> symbol = define_node((yyvsp[-3].node), CONFIG_NAME);
				  cmp_name((yyval.node) -> symbol, (yyvsp[0].symbol));
				  new_config((yyvsp[-3].node) -> symbol, (yyvsp[-2].node));
				}
#line 2624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 273 "mhdl.y" /* yacc.c:1646  */
    { (yyval.symbol) = use_name((yyvsp[0].node)); }
#line 2630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 275 "mhdl.y" /* yacc.c:1646  */
    { (yyval.symbol) = Nil(Symbol); }
#line 2636 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 278 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_label((yyvsp[-2].symbol), new_node(O_CONNECT, (yyvsp[0].node), Nil(Node))); }
#line 2642 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 280 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_CONNECT, (yyvsp[0].node), Nil(Node)); }
#line 2648 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 283 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 286 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2660 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 288 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 2666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 291 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_NAME, Nil(Node), Nil(Node));
				  (yyval.node) -> symbol = define_node((yyvsp[0].node), CONNECTOR_NAME);
				  (yyval.node) = new_node(O_PAIR, (yyval.node), (yyvsp[-2].node));
				}
#line 2675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 296 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_NAME, Nil(Node), Nil(Node));
				  (yyval.node) -> symbol = define_node((yyvsp[0].node), CONNECTOR_NAME);
				}
#line 2683 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 301 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2689 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 303 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[0].node), Nil(Node)); }
#line 2695 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 306 "mhdl.y" /* yacc.c:1646  */
    { check_name((yyvsp[0].node), N_CONNECTOR|N_CONNECT_LIST); (yyval.node) = (yyvsp[0].node); }
#line 2701 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 309 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_NAME, Nil(Node), Nil(Node));
				  (yyval.node) -> symbol = define_node((yyvsp[-3].node), CONSTRAINT_NAME);
				  new_constraint((yyvsp[-3].node) -> symbol, (yyvsp[-1].node), (yyvsp[0].node));
				}
#line 2710 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 315 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 317 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 2722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 320 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2728 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 322 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_WITH, (yyvsp[-4].node), (yyvsp[-1].node)); }
#line 2734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 325 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 2740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 327 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-1].node), Nil(Node)); }
#line 2746 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 330 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2752 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 332 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[0].node), Nil(Node)); }
#line 2758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 335 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 337 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 340 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 342 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_INVERSE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 345 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_TYPE, (yyvsp[-1].node),
						new_node(O_PAIR, Nil(Node), (yyvsp[0].node)));
				}
#line 2790 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 350 "mhdl.y" /* yacc.c:1646  */
    { (yyval.long_value) = F_COMPONENT; }
#line 2796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 352 "mhdl.y" /* yacc.c:1646  */
    { (yyval.long_value) = F_CONNECTOR; }
#line 2802 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 354 "mhdl.y" /* yacc.c:1646  */
    { (yyval.long_value) = F_CONSTRAINT; }
#line 2808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 356 "mhdl.y" /* yacc.c:1646  */
    { (yyval.long_value) = F_DEFINITION; }
#line 2814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 358 "mhdl.y" /* yacc.c:1646  */
    { (yyval.long_value) = F_DIMENSION; }
#line 2820 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 360 "mhdl.y" /* yacc.c:1646  */
    { (yyval.long_value) = F_EQUATION; }
#line 2826 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 362 "mhdl.y" /* yacc.c:1646  */
    { (yyval.long_value) = F_FUNCTION; }
#line 2832 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 364 "mhdl.y" /* yacc.c:1646  */
    { (yyval.long_value) = F_MODEL; }
#line 2838 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 366 "mhdl.y" /* yacc.c:1646  */
    { (yyval.long_value) = F_PROPERTY; }
#line 2844 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 368 "mhdl.y" /* yacc.c:1646  */
    { (yyval.long_value) = F_STRUCTURE; }
#line 2850 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 370 "mhdl.y" /* yacc.c:1646  */
    { (yyval.long_value) = F_TYPE; }
#line 2856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 372 "mhdl.y" /* yacc.c:1646  */
    { (yyval.long_value) = F_UNIT; }
#line 2862 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 375 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_DERIV, new_variable((yyvsp[-4].bucket)), (yyvsp[-1].node)); }
#line 2868 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 378 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_DESIGNATOR, (yyvsp[-1].node), Nil(Node)); }
#line 2874 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 381 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2880 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 383 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_DIVIDE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2886 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 385 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2892 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 388 "mhdl.y" /* yacc.c:1646  */
    { new_unit(define_unit((yyvsp[-2].bucket)), (yyvsp[-1].node), (yyvsp[0].node));
				  declare_variations((yyvsp[0].node), (yyvsp[-2].bucket));
				}
#line 2900 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 393 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2906 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 395 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 2912 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 398 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2918 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 400 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2924 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 403 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2930 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 405 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_MULTIPLY, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2936 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 408 "mhdl.y" /* yacc.c:1646  */
    { check_unit((yyvsp[-2].node));
				  (yyval.node) = new_node(O_EXP, (yyvsp[-2].node), (yyvsp[0].node));
				}
#line 2944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 412 "mhdl.y" /* yacc.c:1646  */
    { check_unit((yyvsp[0].node)); (yyval.node) = (yyvsp[0].node); }
#line 2950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 414 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2956 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 417 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PREOP, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2962 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 419 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_SCALE, Nil(Node), Nil(Node));
				  (yyval.node) -> u.iconstant = (yyvsp[-1].long_value);
				}
#line 2970 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 423 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2976 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 426 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_POSTOP, Nil(Node), Nil(Node));
				  (yyval.node) -> u.iconstant = (yyvsp[0].long_value);
				}
#line 2984 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 430 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 2990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 433 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2996 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 435 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 3002 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 438 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_label((yyvsp[-1].symbol), (yyvsp[0].node)); }
#line 3008 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 440 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3014 "y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 443 "mhdl.y" /* yacc.c:1646  */
    { check_name((yyvsp[0].node), N_MODEL|N_PACKAGE); }
#line 3020 "y.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 446 "mhdl.y" /* yacc.c:1646  */
    { open_name(use_name((yyvsp[0].node))); }
#line 3026 "y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 448 "mhdl.y" /* yacc.c:1646  */
    { alias_name(use_name((yyvsp[-2].node)), use_name((yyvsp[0].node))); }
#line 3032 "y.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 454 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3038 "y.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 456 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3044 "y.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 459 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3050 "y.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 461 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_APPLY, (yyvsp[-1].node), new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[0].node))); }
#line 3056 "y.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 464 "mhdl.y" /* yacc.c:1646  */
    { /***check_name($4, N_GENERATE);***/
				  use_name((yyvsp[-1].node));
				  (yyval.node) = new_node(O_PAIR, (yyvsp[-1].node), (yyvsp[0].node));
				  (yyval.node) = new_node(O_FOREACH, (yyval.node), Nil(Node));
				  (yyval.node) -> bucket = (yyvsp[-2].bucket);
				}
#line 3067 "y.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 472 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 474 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 3079 "y.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 477 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_APPLY, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 3085 "y.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 480 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3091 "y.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 482 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3097 "y.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 485 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3103 "y.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 487 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3109 "y.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 490 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_SEMI, (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 3115 "y.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 492 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 3121 "y.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 495 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3127 "y.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 498 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 3133 "y.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 500 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-1].node), Nil(Node)); }
#line 3139 "y.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 503 "mhdl.y" /* yacc.c:1646  */
    { new_generate((yyvsp[-4].node), (yyvsp[-2].node));
				  (yyval.node) = new_node(O_GENERATE, (yyvsp[-4].node), (yyvsp[-2].node));
				}
#line 3147 "y.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 508 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3153 "y.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 510 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3159 "y.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 512 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3165 "y.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 515 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3171 "y.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 517 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3177 "y.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 520 "mhdl.y" /* yacc.c:1646  */
    { (yyval.bucket) = (yyvsp[0].bucket); }
#line 3183 "y.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 522 "mhdl.y" /* yacc.c:1646  */
    { (yyval.bucket) = (yyvsp[-1].bucket); }
#line 3189 "y.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 524 "mhdl.y" /* yacc.c:1646  */
    { (yyval.bucket) = (yyvsp[0].bucket); }
#line 3195 "y.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 526 "mhdl.y" /* yacc.c:1646  */
    { (yyval.bucket) = (yyvsp[0].bucket); }
#line 3201 "y.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 528 "mhdl.y" /* yacc.c:1646  */
    { (yyval.bucket) = (yyvsp[0].bucket); }
#line 3207 "y.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 531 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 3213 "y.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 533 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[0].node), Nil(Node)); }
#line 3219 "y.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 536 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_GUARD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3225 "y.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 539 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 3231 "y.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 541 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[0].node), Nil(Node)); }
#line 3237 "y.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 544 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_ALT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3243 "y.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 547 "mhdl.y" /* yacc.c:1646  */
    { check_name((yyvsp[-2].node), N_PACKAGE|N_MODEL);
				  open_names((yyvsp[-2].node));
				  close_name_list((yyvsp[0].node));
				}
#line 3252 "y.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 553 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3258 "y.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 555 "mhdl.y" /* yacc.c:1646  */
    { use_name((yyvsp[0].node));
				  (yyval.node) = (yyvsp[0].node);
				}
#line 3266 "y.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 559 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_ID, Nil(Node), Nil(Node));
				  (yyval.node) -> bucket = (yyvsp[-2].bucket);
				  (yyval.node) = new_node(O_PAIR, (yyval.node), (yyvsp[0].node));
				}
#line 3275 "y.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 564 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_ID, Nil(Node), Nil(Node));
				  (yyval.node) -> bucket = (yyvsp[0].bucket);
				  (yyval.node) = new_node(O_PAIR, (yyval.node), Nil(Node));
				}
#line 3284 "y.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 570 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_IF, Nil(Node), Nil(Node)); }
#line 3290 "y.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 576 "mhdl.y" /* yacc.c:1646  */
    { (yyval.symbol) = push_name(use_name((yyvsp[0].node))); }
#line 3296 "y.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 578 "mhdl.y" /* yacc.c:1646  */
    { (yyval.symbol) = push_name(use_name((yyvsp[0].node))); }
#line 3302 "y.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 581 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3308 "y.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 583 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 3314 "y.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 586 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 3320 "y.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 588 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 3326 "y.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 591 "mhdl.y" /* yacc.c:1646  */
    {
				  (yyvsp[-3].symbol) -> cell = new_instance((yyvsp[-3].symbol), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
				  (yyval.node) = new_node(O_INSTANCE, Nil(Node), Nil(Node));
				  (yyval.node) -> symbol = (yyvsp[-3].symbol);
				}
#line 3336 "y.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 598 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-3].node), (yyvsp[-1].node));
				  (yyval.node) = new_node(O_INTEGRAL, (yyval.node), Nil(Node));
				  (yyval.node) -> bucket = (yyvsp[-5].bucket);
				}
#line 3345 "y.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 604 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 3351 "y.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 606 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 3357 "y.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 609 "mhdl.y" /* yacc.c:1646  */
    { (yyval.symbol) = define_name((yyvsp[-1].bucket), LABEL_NAME); }
#line 3363 "y.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 612 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_LAMBDA, (yyvsp[-3].node), (yyvsp[0].node)); }
#line 3369 "y.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 615 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_LET, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3375 "y.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 620 "mhdl.y" /* yacc.c:1646  */
    { load_library((yyvsp[0].node)); }
#line 3381 "y.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 622 "mhdl.y" /* yacc.c:1646  */
    { load_library((yyvsp[0].node)); }
#line 3387 "y.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 625 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 3393 "y.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 627 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3399 "y.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 629 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3405 "y.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 631 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_QUALIFIED, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3411 "y.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 633 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_DOTS, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3417 "y.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 635 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_DOTS, new_node(O_PAIR, (yyvsp[-3].node), (yyvsp[-1].node)), (yyvsp[-1].node)); }
#line 3423 "y.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 637 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_DOTS, (yyvsp[-1].node), Nil(Node)); }
#line 3429 "y.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 640 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_INT, Nil(Node), Nil(Node));
				  (yyval.node) -> u.iconstant = (yyvsp[0].long_value);
				}
#line 3437 "y.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 644 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_FLOAT, Nil(Node), Nil(Node));
				  (yyval.node) -> u.fconstant = (yyvsp[0].float_value);
				}
#line 3445 "y.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 648 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_CHAR, Nil(Node), Nil(Node));
				  (yyval.node) -> u.cconstant = (yyvsp[0].char_value);
				}
#line 3453 "y.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 652 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_STRING, Nil(Node), Nil(Node));
				  (yyval.node) -> u.string = (yyvsp[0].string_value);
				}
#line 3461 "y.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 657 "mhdl.y" /* yacc.c:1646  */
    { cmp_name((yyvsp[-5].symbol), (yyvsp[-1].symbol));
				  analyze((yyvsp[-2].node));
				  type_check((yyvsp[-2].node), 0);
				  if (debug['t']) print_tree((yyvsp[-2].node));
				}
#line 3471 "y.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 664 "mhdl.y" /* yacc.c:1646  */
    { (yyval.symbol) = push_name(define_node((yyvsp[0].node), MODEL_NAME)); }
#line 3477 "y.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 667 "mhdl.y" /* yacc.c:1646  */
    { print_undefs(name_stack_ptr); pop_name(); (yyval.symbol) = use_name((yyvsp[0].node)); }
#line 3483 "y.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 669 "mhdl.y" /* yacc.c:1646  */
    { print_undefs(name_stack_ptr); pop_name(); (yyval.symbol) = Nil(Symbol); }
#line 3489 "y.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 678 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3495 "y.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 680 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 3501 "y.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 683 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 3507 "y.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 685 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 3513 "y.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 688 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3519 "y.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 690 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 3525 "y.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 692 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3531 "y.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 694 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 3537 "y.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 696 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 698 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3549 "y.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 700 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3555 "y.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 702 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 3561 "y.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 705 "mhdl.y" /* yacc.c:1646  */
    { new_multiplier(define_unit((yyvsp[-3].bucket)), (yyvsp[-1].float_value));
				  declare_variations((yyvsp[0].node), (yyvsp[-3].bucket));
				}
#line 3569 "y.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 710 "mhdl.y" /* yacc.c:1646  */
    { (yyval.float_value) = (float) (yyvsp[0].long_value); }
#line 3575 "y.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 712 "mhdl.y" /* yacc.c:1646  */
    { (yyval.float_value) = (yyvsp[0].float_value); }
#line 3581 "y.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 715 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3587 "y.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 717 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3593 "y.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 720 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_COERCE, (yyvsp[-3].node),
						new_node(O_PAIR, (yyvsp[-1].node), (yyvsp[0].node)));
				}
#line 3601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 724 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_TYPED, (yyvsp[-3].node),
						new_node(O_PAIR, (yyvsp[-1].node), (yyvsp[0].node)));
				}
#line 3609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 729 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 732 "mhdl.y" /* yacc.c:1646  */
    { define_node((yyvsp[0].node), NAMED_VALUE_NAME);
				  (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 735 "mhdl.y" /* yacc.c:1646  */
    { define_node((yyvsp[0].node), NAMED_VALUE_NAME);
				  (yyval.node) = (yyvsp[0].node);
				}
#line 3630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 740 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3636 "y.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 742 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3642 "y.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 745 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 3648 "y.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 748 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-1].node), Nil(Node)); }
#line 3654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 750 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 3660 "y.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 753 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_NULL, Nil(Node), Nil(Node)); }
#line 3666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 756 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3672 "y.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 758 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_OP, Nil(Node), Nil(Node));
				  (yyval.node) -> bucket = (yyvsp[0].bucket);
				  (yyval.node) -> code = (yyvsp[0].bucket) -> token;
				}
#line 3681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 763 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_OP, Nil(Node), Nil(Node));
				  (yyval.node) -> bucket = (yyvsp[0].bucket);
				  (yyval.node) -> code = (yyvsp[0].bucket) -> token;
				}
#line 3690 "y.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 768 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_OP, Nil(Node), Nil(Node));
				  (yyval.node) -> bucket = (yyvsp[0].bucket);
				  (yyval.node) -> code = (yyvsp[0].bucket) -> token;
				}
#line 3699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 773 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_MINUS, Nil(Node), Nil(Node));
				  (yyval.node) -> bucket = (yyvsp[0].bucket);
				  (yyval.node) -> code = (yyvsp[0].bucket) -> token;
				}
#line 3708 "y.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 779 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_OP, Nil(Node), Nil(Node));
				  (yyval.node) -> bucket = (yyvsp[0].bucket);
				}
#line 3716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 783 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 3722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 786 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_APPLY, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 3728 "y.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 789 "mhdl.y" /* yacc.c:1646  */
    { cmp_name((yyvsp[-5].symbol), (yyvsp[-1].symbol));
				  analyze((yyvsp[-2].node));
				  type_check((yyvsp[-2].node), 0);
				  if (debug['t']) print_tree((yyvsp[-2].node));
				}
#line 3738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 796 "mhdl.y" /* yacc.c:1646  */
    { (yyval.symbol) = push_name(define_node((yyvsp[0].node), PACKAGE_NAME)); }
#line 3744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 799 "mhdl.y" /* yacc.c:1646  */
    { print_undefs(name_stack_ptr); pop_name(); (yyval.symbol) = use_name((yyvsp[0].node)); }
#line 3750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 801 "mhdl.y" /* yacc.c:1646  */
    { print_undefs(name_stack_ptr); pop_name(); (yyval.symbol) = Nil(Symbol); }
#line 3756 "y.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 810 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3762 "y.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 812 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 3768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 815 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PATTERN, (yyvsp[0].node), Nil(Node)); }
#line 3774 "y.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 818 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3780 "y.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 820 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[0].node), Nil(Node)); }
#line 3786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 825 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3792 "y.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 827 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3798 "y.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 829 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 831 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3810 "y.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 833 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3816 "y.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 835 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 837 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 839 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3834 "y.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 841 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3840 "y.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 843 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 845 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 847 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3858 "y.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 849 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3864 "y.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 852 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PRIMITIVE, (yyvsp[0].node), Nil(Node)); }
#line 3870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 855 "mhdl.y" /* yacc.c:1646  */
    { (yyval.long_value) = F_ATTRIBUTE; }
#line 3876 "y.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 857 "mhdl.y" /* yacc.c:1646  */
    { (yyval.long_value) = F_SIGNAL; }
#line 3882 "y.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 860 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 3888 "y.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 862 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 3894 "y.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 865 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_QUALIFIER, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3900 "y.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 867 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3906 "y.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 870 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3912 "y.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 872 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[0].node), Nil(Node)); }
#line 3918 "y.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 875 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_RHS, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 3924 "y.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 877 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_RHS, (yyvsp[0].node), Nil(Node)); }
#line 3930 "y.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 880 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3936 "y.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 882 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 3942 "y.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 885 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_DOT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3948 "y.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 888 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_ID, Nil(Node), Nil(Node));
				  (yyval.node) -> bucket = (yyvsp[0].bucket);
				  (yyval.node) = new_node(O_DOT, (yyvsp[-2].node), (yyval.node));
				}
#line 3957 "y.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 893 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_ID, Nil(Node), Nil(Node));
				  (yyval.node) -> bucket = (yyvsp[0].bucket);
				}
#line 3965 "y.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 898 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_ID, Nil(Node), Nil(Node));
				  (yyval.node) -> bucket = (yyvsp[0].bucket);
				}
#line 3973 "y.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 902 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 3979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 905 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_NAME, Nil(Node), Nil(Node));
				  (yyval.node) -> symbol = use_name((yyvsp[0].node));
				}
#line 3987 "y.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 909 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_AT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 3993 "y.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 911 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_TILDE, (yyvsp[0].node), Nil(Node)); }
#line 3999 "y.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 913 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_WILDCARD, Nil(Node), Nil(Node)); }
#line 4005 "y.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 915 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4011 "y.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 917 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4017 "y.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 919 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 4023 "y.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 921 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 4029 "y.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 923 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 4035 "y.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 925 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_LIST, (yyvsp[-1].node), Nil(Node)); }
#line 4041 "y.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 928 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_TYPE, (yyvsp[-3].node),
						new_node(O_PAIR, (yyvsp[-1].node), (yyvsp[0].node)));
				}
#line 4049 "y.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 933 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4055 "y.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 935 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[0].node), Nil(Node)); }
#line 4061 "y.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 938 "mhdl.y" /* yacc.c:1646  */
    { use_name((yyvsp[0].node)); }
#line 4067 "y.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 940 "mhdl.y" /* yacc.c:1646  */
    { use_name((yyvsp[-1].node)); }
#line 4073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 943 "mhdl.y" /* yacc.c:1646  */
    { full_cmp_name((yyvsp[-3].node), (yyvsp[0].node));
				  use_name((yyvsp[-3].node));
				  (yyval.node) = new_node(O_FOR, (yyvsp[-3].node), (yyvsp[-2].node));
				}
#line 4082 "y.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 949 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4088 "y.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 951 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 4094 "y.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 954 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4100 "y.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 956 "mhdl.y" /* yacc.c:1646  */
    { check_name((yyvsp[0].node), N_CONFIG);
				  use_name((yyvsp[0].node));
				  (yyval.node) = (yyvsp[0].node);
				}
#line 4109 "y.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 962 "mhdl.y" /* yacc.c:1646  */
    { pop_name();
				  cmp_name((yyvsp[-6].symbol), (yyvsp[0].symbol));
				  (yyvsp[-6].symbol) -> cell = new_structure((yyvsp[-6].symbol), F_STRUCTURE, (yyvsp[-3].node), (yyvsp[-4].node),(yyvsp[-2].node));
				  (yyval.node) = new_node(O_NAME, Nil(Node), Nil(Node));
				  (yyval.node) -> symbol = (yyvsp[-6].symbol);
				}
#line 4120 "y.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 970 "mhdl.y" /* yacc.c:1646  */
    { (yyval.symbol) = push_name(define_node((yyvsp[0].node), STRUCTURE_NAME)); }
#line 4126 "y.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 973 "mhdl.y" /* yacc.c:1646  */
    { (yyval.symbol) = use_name((yyvsp[0].node)); }
#line 4132 "y.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 975 "mhdl.y" /* yacc.c:1646  */
    { (yyval.symbol) = Nil(Symbol); }
#line 4138 "y.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 981 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4144 "y.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 983 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 4150 "y.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 986 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4156 "y.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 988 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 4162 "y.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 990 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4168 "y.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 992 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 4174 "y.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 995 "mhdl.y" /* yacc.c:1646  */
    { check_name((yyvsp[-1].node), N_STRUCTURE); }
#line 4180 "y.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 998 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 4186 "y.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 1000 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-1].node), Nil(Node)); }
#line 4192 "y.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 1003 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4198 "y.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 1005 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4204 "y.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 1007 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4210 "y.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 1009 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4216 "y.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 1011 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4222 "y.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 1013 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4228 "y.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 1015 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4234 "y.tab.c" /* yacc.c:1646  */
    break;

  case 329:
#line 1017 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4240 "y.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 1019 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4246 "y.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 1021 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4252 "y.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 1024 "mhdl.y" /* yacc.c:1646  */
    { cmp_name((yyvsp[-5].symbol), (yyvsp[0].symbol));
				  (yyvsp[-5].symbol) -> cell = new_table((yyvsp[-5].symbol), (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node));
				  (yyval.node) = new_node(O_NAME, Nil(Node), Nil(Node));
				  (yyval.node) -> symbol = (yyvsp[-5].symbol);
				}
#line 4262 "y.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 1031 "mhdl.y" /* yacc.c:1646  */
    { (yyval.symbol) = define_node((yyvsp[0].node), TABLE_NAME); }
#line 4268 "y.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 1034 "mhdl.y" /* yacc.c:1646  */
    { (yyval.symbol) = use_name((yyvsp[0].node)); }
#line 4274 "y.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 1036 "mhdl.y" /* yacc.c:1646  */
    { (yyval.symbol) = Nil(Symbol); }
#line 4280 "y.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 1039 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 4286 "y.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 1041 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 4292 "y.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 1044 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4298 "y.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 1046 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 4304 "y.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 1049 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-2].node); }
#line 4310 "y.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 1051 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 4316 "y.tab.c" /* yacc.c:1646  */
    break;

  case 342:
#line 1054 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 4322 "y.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 1056 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[0].node), Nil(Node)); }
#line 4328 "y.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 1059 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4334 "y.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 1061 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4340 "y.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 1064 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[0].node), Nil(Node)); }
#line 4346 "y.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 1066 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 4352 "y.tab.c" /* yacc.c:1646  */
    break;

  case 348:
#line 1069 "mhdl.y" /* yacc.c:1646  */
    { check_name((yyvsp[0].node), N_TABLE);
				  (yyval.node) = (yyvsp[0].node);
				}
#line 4360 "y.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 1073 "mhdl.y" /* yacc.c:1646  */
    { check_name((yyvsp[0].node), N_TABLE);
				  (yyval.node) = (yyvsp[0].node);
				}
#line 4368 "y.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 1078 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 4374 "y.tab.c" /* yacc.c:1646  */
    break;

  case 351:
#line 1081 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4380 "y.tab.c" /* yacc.c:1646  */
    break;

  case 352:
#line 1083 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[0].node), Nil(Node)); }
#line 4386 "y.tab.c" /* yacc.c:1646  */
    break;

  case 353:
#line 1086 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PREDICATE, (yyvsp[-3].node), (yyvsp[-1].node));
				  (yyval.node) -> symbol = use_name((yyvsp[-3].node));
				}
#line 4394 "y.tab.c" /* yacc.c:1646  */
    break;

  case 354:
#line 1090 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4400 "y.tab.c" /* yacc.c:1646  */
    break;

  case 355:
#line 1092 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_INT, Nil(Node), Nil(Node));
				  (yyval.node) -> u.iconstant = (yyvsp[0].long_value);
				}
#line 4408 "y.tab.c" /* yacc.c:1646  */
    break;

  case 357:
#line 1098 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4414 "y.tab.c" /* yacc.c:1646  */
    break;

  case 358:
#line 1101 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4420 "y.tab.c" /* yacc.c:1646  */
    break;

  case 359:
#line 1103 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4426 "y.tab.c" /* yacc.c:1646  */
    break;

  case 360:
#line 1106 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4432 "y.tab.c" /* yacc.c:1646  */
    break;

  case 361:
#line 1109 "mhdl.y" /* yacc.c:1646  */
    { fatal(" type_item "); }
#line 4438 "y.tab.c" /* yacc.c:1646  */
    break;

  case 362:
#line 1111 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4444 "y.tab.c" /* yacc.c:1646  */
    break;

  case 363:
#line 1114 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4450 "y.tab.c" /* yacc.c:1646  */
    break;

  case 364:
#line 1116 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[0].node), Nil(Node)); }
#line 4456 "y.tab.c" /* yacc.c:1646  */
    break;

  case 365:
#line 1119 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_RARROW, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4462 "y.tab.c" /* yacc.c:1646  */
    break;

  case 366:
#line 1121 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4468 "y.tab.c" /* yacc.c:1646  */
    break;

  case 367:
#line 1124 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4474 "y.tab.c" /* yacc.c:1646  */
    break;

  case 368:
#line 1127 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_NAME, Nil(Node), Nil(Node));
				  (yyval.node) -> symbol = use_name((yyvsp[0].node));
				}
#line 4482 "y.tab.c" /* yacc.c:1646  */
    break;

  case 369:
#line 1131 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 4488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 370:
#line 1133 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 4494 "y.tab.c" /* yacc.c:1646  */
    break;

  case 371:
#line 1135 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_LIST, (yyvsp[-1].node), Nil(Node)); }
#line 4500 "y.tab.c" /* yacc.c:1646  */
    break;

  case 372:
#line 1138 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_TYPED, (yyvsp[-4].node),
						new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[-1].node)));
				}
#line 4508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 373:
#line 1143 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 4514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 374:
#line 1145 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 4520 "y.tab.c" /* yacc.c:1646  */
    break;

  case 375:
#line 1148 "mhdl.y" /* yacc.c:1646  */
    { new_unit(define_unit((yyvsp[-5].bucket)), (yyvsp[-2].node), (yyvsp[-1].node));
				  declare_variations((yyvsp[0].node), (yyvsp[-5].bucket));
				}
#line 4528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 376:
#line 1153 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 377:
#line 1155 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 4540 "y.tab.c" /* yacc.c:1646  */
    break;

  case 378:
#line 1158 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_VALUE_DEF, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 4546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 379:
#line 1160 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_label((yyvsp[-3].symbol), new_node(O_DEFAULT, (yyvsp[-1].node), (yyvsp[0].node))); }
#line 4552 "y.tab.c" /* yacc.c:1646  */
    break;

  case 380:
#line 1162 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_DEFAULT, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 4558 "y.tab.c" /* yacc.c:1646  */
    break;

  case 381:
#line 1165 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 4564 "y.tab.c" /* yacc.c:1646  */
    break;

  case 382:
#line 1167 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-1].node), Nil(Node)); }
#line 4570 "y.tab.c" /* yacc.c:1646  */
    break;

  case 383:
#line 1170 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 384:
#line 1173 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 385:
#line 1176 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 4588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 386:
#line 1179 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_PAIR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 387:
#line 1181 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_ID, Nil(Node), Nil(Node));
				  (yyval.node) -> bucket = (yyvsp[0].bucket);
				}
#line 4602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 390:
#line 1188 "mhdl.y" /* yacc.c:1646  */
    { check_name((yyvsp[0].node), N_MODEL|N_PACKAGE);
				  open_names((yyvsp[0].node));
				}
#line 4610 "y.tab.c" /* yacc.c:1646  */
    break;

  case 391:
#line 1193 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_WHERE, (yyvsp[-1].node), Nil(Node)); }
#line 4616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 392:
#line 1196 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = new_node(O_CONTEXT, (yyvsp[0].node), Nil(Node)); }
#line 4622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 393:
#line 1198 "mhdl.y" /* yacc.c:1646  */
    { (yyval.node) = Nil(Node); }
#line 4628 "y.tab.c" /* yacc.c:1646  */
    break;


#line 4632 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
