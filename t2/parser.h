/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    ID = 258,
    NUMBER = 259,
    UMINUS = 260,
    LT = 261,
    LE = 262,
    EQ = 263,
    GE = 264,
    GT = 265,
    NE = 266,
    EXP = 267,
    MATERIAL = 268,
    OBJECT = 269,
    GLOBAL = 270,
    PROPERTIES = 271,
    CYLINDER = 272,
    BLOCK = 273,
    SPHERE = 274,
    IN = 275,
    FT = 276,
    M = 277,
    CM = 278,
    MM = 279,
    DO = 280,
    IF = 281,
    FOR = 282,
    THEN = 283,
    ELSE = 284,
    AT = 285,
    SWITCH = 286,
    INTEGER = 287,
    FLOAT = 288,
    STRING = 289,
    CONSTANT = 290,
    LIST = 291,
    FUNCTION = 292,
    CALL = 293,
    TERMINAL = 294,
    PROPERTY = 295,
    COMPOUND = 296,
    UNION = 297,
    INTERSECT = 298,
    ROTATE = 299,
    DIFFERENCE = 300,
    ASSEMBLY = 301,
    TUPLE = 302,
    UPTO = 303,
    DOWNTO = 304,
    BIND = 305,
    ALTERNATIVE = 306,
    LABEL = 307
  };
#endif
/* Tokens.  */
#define ID 258
#define NUMBER 259
#define UMINUS 260
#define LT 261
#define LE 262
#define EQ 263
#define GE 264
#define GT 265
#define NE 266
#define EXP 267
#define MATERIAL 268
#define OBJECT 269
#define GLOBAL 270
#define PROPERTIES 271
#define CYLINDER 272
#define BLOCK 273
#define SPHERE 274
#define IN 275
#define FT 276
#define M 277
#define CM 278
#define MM 279
#define DO 280
#define IF 281
#define FOR 282
#define THEN 283
#define ELSE 284
#define AT 285
#define SWITCH 286
#define INTEGER 287
#define FLOAT 288
#define STRING 289
#define CONSTANT 290
#define LIST 291
#define FUNCTION 292
#define CALL 293
#define TERMINAL 294
#define PROPERTY 295
#define COMPOUND 296
#define UNION 297
#define INTERSECT 298
#define ROTATE 299
#define DIFFERENCE 300
#define ASSEMBLY 301
#define TUPLE 302
#define UPTO 303
#define DOWNTO 304
#define BIND 305
#define ALTERNATIVE 306
#define LABEL 307

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 38 "t2.y" /* yacc.c:1909  */

	struct NODE *node;
	struct PROPERTY_VALUE *property;
	struct MATERIAL_VALUES *material;
	int integerConstant;
	float floatingConstant;
	char stringBuffer[128];

#line 167 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
