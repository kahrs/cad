/*
 * Lexical analyzer
 */

#include <ctype.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "espectro.h"
#include "espectro.tab.h"

double exp(double x);
double log(double x);
double log10(double x);
double pow(double x, double y);

#define SYMBOL_LENGTH 200
char symbol[SYMBOL_LENGTH];
int peekc;
int peekpeekc;
char *symbolp;
long int line_number = 1;
int char_position = 0;

#define IGNORE '\0'

extern YYSTYPE yylval;
FILE *yyin;

extern Bucket *namehashtable[];

extern void rwinit(void);
extern Bucket *lookup_name(Bucket *[], char *);
extern char debug[];

void eatstring(void);
long numeric(char first);

void
lexer_init(FILE *f)
{
	yyin = f;            /* Change file names */
	peekc = IGNORE;
	peekpeekc = IGNORE;
	line_number = 1;
}

int
yywrap(void)
{
	fclose(yyin);
	return(1); 
}

void
yyerror(char *msg, char *arg)
{
	warn(msg, 0);
#ifdef yychar
	if (yychar <= 0)
		fprintf(stderr, "<EOF>\n");
	else
	if (yychar < 0177)
		fprintf(stderr, "Last token: %c\n", yychar);
#endif
}

int
yygetc(void)
{
	int c;
	if (peekc != IGNORE) {
		c = peekc;
		if (peekpeekc != IGNORE) {
			peekc = peekpeekc;
			peekpeekc = IGNORE;
		} /* end if peek2 */
		else
			peekc = IGNORE;
		if (c == '\n') line_number--;
	} /* peekahead */
	else
		c = fgetc(yyin);
	if (c == '\n') line_number++;
	return(c);
} /* end yygetc */

int
namech(char c)
{
	if (c == '\\') {
		c = yygetc();
		c = '_';
	}
	return(isalnum(c) || (c == '_') || (c == '!'));
}

int
yylex(void)
{

	int c;
	int floater = 0;
	int numeric_token;
	Bucket *b;
top:	c = yygetc();
	while (isspace(c)) {
		char_position++;
		if (c != '\n') {
                        c = yygetc();
			continue;
		}
cr:		c = yygetc();
                if (c == '+') {
			peekc = IGNORE;
                        c = yygetc();
			continue;
		}
		else
		if (c == '*') {
			peekc = IGNORE;
			while (yygetc() != '\n');
			goto cr;
		}
		char_position = 0;
		peekc = c;
		return 0;
	}
	if (((c == '*') || (c == '.')) && (char_position == 0)) {
		peekc = IGNORE;
		while (yygetc() != '\n');
		goto top;
	}
	if ((c == '#') && (char_position == 0)) {
		if (!isspace(yygetc())) fatal("space missing after #");
		line_number = 0;
		while (isdigit(c = yygetc())) { line_number *= 10; line_number += (c-'0'); }
		if (yygetc() == '"') {
			do { c = yygetc();  } while (c != '"');
		} /* end while */
		while (yygetc() != '\n');
		goto top;
	} /* end if */
	char_position++;
	if (isalpha(c)) {
		symbolp = symbol;
		for(*symbolp++ = c;;) {
			c = yygetc();
			if (!namech(c)) break;
			*symbolp++ = c;
		} /* end for */
		peekc = c;
		*symbolp = '\0';
		if (debug['T']) fprintf(stderr, "%s\n", symbol);
		b = lookup_name(namehashtable, symbol);
		yylval.bucket = b;
		return((b -> token) ? b -> token : SYMBOL);
	} /* end alpha */
        else
        if (isdigit(c) || (c == '.')) {
		numeric_token = numeric(c);
		if (debug['T']) 
			if (numeric_token == L_INT) fprintf(stderr, "%ld\n", yylval.long_value);
			else
			if (numeric_token == L_FLOAT) fprintf(stderr, "%f\n", yylval.double_value);
                return(numeric_token);
	} /* end if */
	else
	switch (c) {
	case EOF:
		peekc = EOF;
		return 0;
	case '"':
		(void) eatstring();
		return(L_STRING);
	case '/':
		c = yygetc();
		if (c != '/') {
			peekc = c;
			return('/');
		} /* end comment check */
		while (yygetc() != '\n');
		char_position = 0;
		goto cr;
	case '\\':
		c = yygetc();
		switch (c) {
		default:
			fatal("unknown backslash");
		} /* end switch */
	case '-':
		peekc = yygetc();
/*		if (isdigit(peekc)) {
			numeric_token = numeric(yygetc());
			if (numeric_token == L_INT)
				yylval.long_value *= -1;
			else
			if (numeric_token == L_FLOAT)
				yylval.double_value *= -1;
			else
				fatal("unknown numeric token in case -");
			if (debug['T']) 
				if (numeric_token == L_INT) fprintf(stderr, "%d\n", yylval.long_value);
				else
				if (numeric_token == L_FLOAT) fprintf(stderr, "%f\n", yylval.double_value);
			return(numeric_token);
		} /* end negative number */
		return(c);
	case '+':
	/* sacred tokens */
	case '(':
	case ')':
	case '[':
	case ']':
	case '{':
	case '}':
	case ',':
	case '_':
	case '%':
	case '?':
	case ':':
		return(c);
	case '=':
		c = yygetc();
		if (c == '=') return(L_EQ);
		peekc = c;
		return('=');
	case '<':
		c = yygetc();
		if (c == '=') return(L_LE);
		if (c == '<') return(L_LSHIFT);
		peekc = c;
		return(L_LT);
	case '>':
		c = yygetc();
		if (c == '=') return(L_GE);
		if (c == '>') return(L_RSHIFT);
		peekc = c;
		return(L_GT);
	case '^':
		c = yygetc();
		if (c == '~') return(L_XNOR);
		peekc = c;
		return('^');
	case '*':
		c = yygetc();
		if (c == '*') return(L_EXP);
		peekc = c;
		return('*');
	case '!':
		c = yygetc();
		if (c == '=') return(L_NE);
		peekc = c;
		return('!');
	case '&':
		c = yygetc();
		if (c == '&') return(L_AND);
		peekc = c;
		return('&');
	case '|':
		c = yygetc();
		if (c == '|') return(L_OR);
		peekc = c;
		return('|');
	default:
		fprintf(stderr, "c=%c (%x);", c, c);
		yyerror("unknown character", "");
	} /* end switch */
} /* end yylex */

float
check_unit(char c)
{
	float scale;
	switch(c) {
	case 'T':
		scale = 1e12;
		break;
	case 'G':
		scale = 1e09;
		break;
	case 'M':
		scale = 1e06;
		break;
	case 'K':
	case 'k':
		scale = 1e03;
		break;
	case 'm':
		scale = 1e-03;
		break;
	case 'u':
		scale = 1e-06;
		break;
	case 'n':
		scale = 1e-09;
		break;
	case 'p':
		scale = 1e-12;
		break;
	case 'f':
		scale = 1e-15;
		break;
	case 'a':
		scale = 1e-18;
		break;
	case '?':
		scale = 25.4e-6;
		break;
	default:
		yyerror("unrecognized unit multiplier", "");
		fprintf(stderr, "multiplier = %c\n", c);
	} /* switch */
	while (isalpha(c = yygetc()));
	peekc = c;
	return(scale);
} /* check_unit */

long
numeric(char first)
{
	enum { Base, Integer, Hex, HexFraction, Fraction, ExpSign, Exponent } state;
	char c;
	int fractional = 0, exponent = 0;
	char *endp;
	float scale = 1.0;

	symbol[0] = first;
	symbolp = symbol+1;

	state = Base;

	for(;;) {
		c = yygetc();
		if(c == EOF) {
			yyerror("EOF in numeric", "");
			return(L_INT);
		} /* end EOF */
		switch (state) {
		case Base:
			if (strchr("01234567890", c))
				break;
			switch(c) {
			case '#':
				state = Hex;
				break;
			case '.':
				state = Fraction;
				break;
			case 'e':
			case 'E':
				state = ExpSign;
				break;
			default:
				goto done;
			} /* end base switch */
			break;
		case Integer:
			if (strchr("01234567890", c))
				break;
			switch(c) {
			case 'x':
			case 'X':
				state = Hex;
				break;
			case '.':
				state = Fraction;
				break;
			case 'e':
			case 'E':
				state = ExpSign;
				break;
			case '#':
				break;
			default:
				goto done;
			}
			break;
		case Hex:
			if (strchr("01234567890abcdefABCDEF", c))
				break;
			switch (c) {
			case '#':
				c = yygetc();
				goto done;
			case '.':
				state = HexFraction;
				break;
			default:
				goto done;
			} /* end switch */
			break;
		case HexFraction:
			fractional++;
			if (strchr("01234567890abcdefABCDEF", c))
				break;
			if (c == '#') {
				*symbolp++ = c;
				c = yygetc();
				state = ExpSign;
			} /* end if # */
			else {
				yyerror("missing trailing # in fractional constant", "");
				goto done;
			} /* end else */
			break;
		case Fraction:
			fractional++;
			if (strchr("01234567890", c))
				break;
			if ((c == 'e') || (c == 'E'))
				state = ExpSign;
			else
			if (c == '.') { /* watch out for [0-9]+.. */
				peekpeekc = c;
				fractional = 0;
				symbolp--; /* wind back over . */
				goto done;
			} /* end .. */
			else
				goto done;
			break;
		case ExpSign:
			state = Exponent;
			if ((c == '-') || (c == '+'))
				break;
			/* else fall through */
		case Exponent:
			if (strchr("01234567890", c) == 0)
				goto done;
			break;
		} /* end switch */
		*symbolp++ = c;
	} /* end inf for */
done:
	if (isalpha(c)) {
		scale = check_unit(c);
	} /* end if */
	else peekc = c;
	*symbolp = '\0';
	switch(state) {
	default:
		if (scale == 1.0) {
			yylval.long_value = strtol(symbol, 0, 0);
			return(L_INT);
		} /* only if no scaling */
	case Fraction:
	case ExpSign:
	case Exponent:
		yylval.double_value = strtod(symbol, 0) * scale;
		return (L_FLOAT);
	} /* end switch */
} /* end numeric */

void
eatstring(void)

{
	char *buffer;
	char *s;
	int c, count, bsize;

	bsize = SYMBOL_LENGTH;
	buffer = (char *) malloc(bsize); /* in case of realloc */

	for(count = 0;count<bsize;) {
		c = yygetc();
		switch(c) {
		case EOF:
			buffer[count++] = '\0';
			yyerror("EOF in string constant:", buffer);
			break;
		case '\n':
			yyerror("newline in string constant:", buffer);
			goto done;
		case '\\':
			break;
		case '"':
			goto done;
		default:
			buffer[count++] = c;
			break;
		} /* end case */
	} /* end for */
	while ((c = yygetc()) != '\'');
	buffer[count++] = '\0';
	yyerror("string constant too long:", buffer);
	return;
done:
	buffer[count++] = '\0';
	s = (char *) malloc(count);
	memcpy(s, buffer, count);
	yylval.string_value = s;
} /* end eatstring */

void
skip_line(void)
{
	char c;
	while ((c = yygetc()) != '\n' && (c != -1));	
} /* end skip_line */

