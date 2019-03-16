%{

#undef input
#undef output
#undef unput

#include "y.tab.h"

yywrap()
{ return(1); }

extern int value;
extern int lineNumber;
extern char *fileName;

%}

integer		[0-9]("_"?[0-9])*
exponent	[eE][+-]?[0-9]("_"?[0-9])*
dot		\.
slash		"/"
separators	[ \t\n\f]

%%

"#".*$	;
"--".*$	;
{separators}*	;

"^"	return('^');
":"	return(':');
"="	return('=');
"["	return('[');
"]"	return(']');
"{"	return('{');
"}"	return('}');
"'"	return(',');
"("	return('(');
")"	return(')');
"**"	return(EXP);
"+"	return('+');
"-"	return('-');
"*"	return('*');
","	return(',');
";"	return(';');
"<=" 	return(LE);
"<"	return(LT);
"=="	return(EQ);
">="	return(GE);
">"	return(GT);
"|"	return('|');
"&"	return('&');

"MATERIAL" return(MATERIAL);
"OBJECT" return(OBJECT);
"GLOBAL" return(GLOBAL);
"FOR" return(FOR);
"CYLINDER" return(CYLINDER);
"BLOCK"	return(BLOCK);
"SPHERE" return(SPHERE);
"PROPERTIES" return(PROPERTIES);
"IN"	return(IN);
"FT"	return(FT);
"M"	return(M);
"CM"	return(CM);
"DO"	return(DO);
"IF"	return(IF);
"THEN"	return(THEN);
"ELSE"	return(ELSE);
"AT"	return(AT);
"SWITCH" return(SWITCH);
"UPTO"	return(UPTO);
"DOWNTO" return(DOWNTO);

"material" return(MATERIAL);
"object" return(OBJECT);
"global" return(GLOBAL);
"for" return(FOR);
"cylinder" return(CYLINDER);
"block"	return(BLOCK);
"sphere" return(SPHERE);
"properties" return(PROPERTIES);
"in"	return(IN);
"ft"	return(FT);
"m"	return(M);
"cm"	return(CM);
"do"	return(DO);
"if"	return(IF);
"then"	return(THEN);
"else"	return(ELSE);
"at"	return(AT);
"switch" return(SWITCH);
"upto"	return(UPTO);
"downto" return(DOWNTO);

[A-Za-z][_$A-Za-z0-9]* { return(ID); }
{integer}({dot}{integer})?({exponent})? { return(FLOAT); }
{integer}	return(INTEGER);
\".*\"	return(STRING);

%%
