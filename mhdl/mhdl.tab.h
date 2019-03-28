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
#line 16 "mhdl.y" /* yacc.c:1909  */

	Node	*node;
	Bucket	*bucket;
	Symbol	*symbol;
	Type	*type;
	long	long_value;
	char	char_value;
	double	float_value;
	char	*string_value;

#line 217 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
