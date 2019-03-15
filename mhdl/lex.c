/*
 * Redone lexical analyzer
 */

#include <ctype.h>
#include <stdio.h>
#ifdef PLAN9
#include <u.h>
#include <libc.h>
#endif

#include "mhdl.h"
#include "mhdl.tab.h"

#define SYMBOL_LENGTH 200
char symbol[SYMBOL_LENGTH];
int peekc;
int peekpeekc;
char *symbolp;
long int line_number = 1;
int comment_level = 0;

#define IGNORE '\0'

#ifndef PLAN9
#ifdef BACKTRACE
extern int *yys; /* yacc stack */
extern int *yyps; /* pointer to top of yacc stack */
extern char *yystates[]; /* table of states */
extern int yychar;
#endif
extern char *yytokens[]; /* table of symbol tokens */
#endif
extern YYSTYPE yylval;
FILE *yyin;

extern Bucket *namehashtable[];

void rwinit(void);
int issacred(char c);
long escapedchar(char c);
long numeric(char c);
void eatstring(void);

void
initialize_lexer(FILE *f)     /* Change input file from STDIN to MHDL file */
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
	warn(msg, arg, 0);
#ifndef PLAN9
#ifdef BACKTRACE
	while (yyps >= yys)
		fprintf(stderr, "%s\n", yystates[*yyps--]);
#endif
#endif
#ifdef yychar
	if (yychar <= 0)
		fprintf(stderr, "<EOF>\n");
	else
	if (yychar < 0177)
		fprintf(stderr, "Last token: %c\n", yychar);
	else
	if (yychar <= L_WITH)
		fprintf(stderr, "Last token: %s\n", yytokens[yychar-L_AS]);
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
yylex(void)
{
	int c;
	int floater = 0;
	Bucket *b;
top:	c = yygetc();
	if (isspace(c))
		goto top;
	if (isalpha(c)) {
		symbolp = symbol;
		for(*symbolp++ = c;;) {
			c = yygetc();
			if (!(isalnum(c) || (c == '_'))) break;
			*symbolp++ = c;
		} /* end for */
		peekc = c;
		*symbolp = '\0';
		b = lookup_name(namehashtable, symbol);
		yylval.bucket = b;
		return((b -> token) ? b -> token : L_IDENTIFIER);
	} /* end alpha */
	else
	if (isdigit(c)) 
		return(numeric(c));
	else
	switch (c) {
	case EOF:
		peekc = EOF;
		return 0;
	case '"':
		(void) eatstring();
		return(L_STRING);
	case '\'':
		c = yygetc();
		if (c == '\'') {
			c = yygetc();
			if (c == '\\') c = escapedchar(yygetc());
			peekc = yygetc();
			if (peekc == '\'') {
				peekc = IGNORE;
				peekc = yygetc();
				if (peekc != '\'')
					yyerror("missing closing ''", "");
				else peekc = IGNORE;
			} /* end if '' */
		} /* end '' */
		else {
			peekc = c;
			return('\'');
		} /* end single ' */
		yylval.char_value = c;
		return(L_CHAR);
	case '`':
		c = yygetc();
		if (c == '`') return(L_DOUBLE);
		symbolp = symbol;
		*symbolp++ = '`';
		for(*symbolp++ = c;;) {
			c = yygetc();
			*symbolp++ = c;
			if (c == '`') break;
		} /* end for */
		*symbolp = '\0';
		b = lookup_name(namehashtable, symbol);
		yylval.bucket = b;
		return(L_IDENTIFIER);
	/* sacred tokens */
	case '(':
	case ')':
	case '[':
	case ']':
	case '}':
	case ';':
	case ',':
	case '_': /* wildcard */
		return(c);
	case '{':
		peekc = yygetc();
		if (peekc != '-') return(c);
		comment_level++;
		for(;;) {
			c = yygetc();
			if (c == '{') {
				c = yygetc();
				if (c == '-') comment_level++;
			} /* end if */
			else
			if (c == '-') {
				c = yygetc();
				if (c == '}')
					if (--comment_level == 0) break;
			} /* end if */
		} /* end do */
		goto top;
	case '-':
		peekc = yygetc();
		if (peekc == '-') {
			peekc = IGNORE;
			for (;c != '\n';c = yygetc());
			goto top;
		} /* end comment, fall into operator lookup */
	default:
		symbolp = symbol;
		for(*symbolp++ = c;;) {
			c = yygetc();
			if ((c == EOF) || isalnum(c) || isspace(c) || issacred(c)) break;
			*symbolp++ = c;
		} /* end for */
		peekc = c;
		*symbolp = '\0';
		if (debug['O'])
			fprintf(stderr, "lex operator %s\n", symbol);
		b = lookup_name(namehashtable, symbol);
		yylval.bucket = b;
		return((b -> token) ? b -> token : L_OPERATOR);
	} /* end switch */
} /* end yylex */

long
numeric(char first)
{
	enum { Base, Integer, Hex, HexFraction, Fraction, ExpSign, Exponent } state;
	char c;
	int fractional = 0, exponent = 0;
	char *endp;

	symbol[0] = first;
	symbolp = symbol+1;

	state = Base;

	for(;;) {
		c = yygetc();
		if(c == EOF) {
			yyerror("EOF in numeric", "");
			return(L_INTEGER);
		} /* end EOF */
		if(c == '\n')
			line_number++;
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
	peekc = c;
	*symbolp = '\0';
	switch(state) {
	default:
		yylval.long_value = strtol(symbol, 0, 0);
		return(L_INTEGER);
	case Fraction:
	case ExpSign:
	case Exponent:
		if (!fractional) {
			yylval.long_value = strtol(symbol, &endp, 0);
			endp++;
			exponent = strtol(endp, 0, 0);
			if (exponent > logmaxint)
				warn("integer precision exceeded for constant", symbol);
			else
				yylval.long_value *= (long) pow(10.0, (double) exponent);
			return(L_INTEGER);
		} /* end if */
		yylval.float_value = strtod(symbol, 0);
		return (L_FLOAT);
	} /* end switch */
} /* end numeric */

void
eatstring(void)
{
	char *buffer;
	char *s;
	int escaped, c, count, bsize;

	escaped = 0;
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
			line_number++;
			if (escaped) {
				for(;;) {
					c = yygetc();
					if (c == EOF) {
						buffer[count++] = '\0';
						yyerror("EOF in gapped string constant", buffer);
						return;
					} /* end if EOF */
					if (c == '\\') break;
				} /* end for */
				escaped = 0;
				continue; /* to the top of the scanner */
			} /* end gap */
			else
				yyerror("newline in string constant:", buffer);
			goto done;
		case '\\':
			if (escaped) {
				buffer[count++] = c;
				escaped = 0;
				break;
			} /* end if escaped */
			escaped = 1;
			break;
		case '"':
			if(escaped == 0)
				goto done;
			/* Fall through */
		default:
			if(escaped) {
				c = escapedchar(c);
				escaped = 0;
			} /* end if escaped */
			buffer[count++] = c;
			break;
		} /* end case */
	} /* end for */
	while ((c = yygetc()) != '"');
	buffer[count++] = '\0';
	yyerror("string constant too long:", buffer);
	return;
done:
	buffer[count++] = '\0';
	s = (char *) malloc(count);
	memcpy(s, buffer, count);
	yylval.string_value = s;
} /* end eatstring */

long
escapedchar(char c)
{
	int n;
	char buf[SYMBOL_LENGTH];

	if ((c >= '0') && (c <= '9')) {
		n = 1;
		buf[0] = c;
		for(;;) {
			c = yygetc();
			if(c == EOF)
				yyerror("EOF in escape sequence", "");
			if(strchr("0123456789xX", c) == 0) {
				peekc = c;
				break;
			} /* end if */
			buf[n++] = c;
		} /* end for */
		buf[n] = '\0';
		return strtol(buf, 0, 0);
	} /* end if */

	switch (c) {
	case '\'':
		c = '\'';
		break;
	case '"':
		c = '"';
		break;
	case 'a':
		c = '\a';
		break;
	case 'b':
		c = '\b';
		break;
	case 'f':
		c = '\f';
		break;
	case 'n':
		c = '\n';
		break;
	case 'r':
		c = '\t';
		break;
	case 't':
		c = '\t';
		break;
	case 'v':
		c = '\v';
		break;
	case '\\':
		break;
	case '&':
		peekc = yygetc();
		break;
	default:
		fprintf(stdout, "Seen unknown escape \\%c\n", c);
		yyerror("unknown \\ escape", "");
	} /* end case */
	return(c);
} /* end escapedchar */

int
issacred(char c)
{
	switch(c) {
		case '(':
		case ')':
		case '[':
		case ']':
		case '{':
		case '}':
		case ';':
		case ',':
		case '"':
		case '_':
		return(1);
	default:
		return(0);
	} /* end switch */
}
