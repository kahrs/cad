# include "stdio.h"
# define U(x) x
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# define YYLMAX 200
# define output(c) putc(c,yyout)
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
# define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng; extern char yytext[];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;
FILE *yyin = {stdin}, *yyout = {stdout};
extern int yylineno;
struct yysvf { 
	int yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;

#line 2 "t2.l"

#undef input
#undef output
#undef unput

#include "y.tab.h"

yywrap()
{ return(1); }

extern int value;
extern int lineNumber;
extern char *fileName;

# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:

#line 26 "t2.l"
;
break;
case 2:

#line 27 "t2.l"
;
break;
case 3:

#line 28 "t2.l"
;
break;
case 4:

#line 30 "t2.l"
return('^');
break;
case 5:

#line 31 "t2.l"
return(':');
break;
case 6:

#line 32 "t2.l"
return('=');
break;
case 7:

#line 33 "t2.l"
return('[');
break;
case 8:

#line 34 "t2.l"
return(']');
break;
case 9:

#line 35 "t2.l"
return('{');
break;
case 10:

#line 36 "t2.l"
return('}');
break;
case 11:

#line 37 "t2.l"
return(',');
break;
case 12:

#line 38 "t2.l"
return('(');
break;
case 13:

#line 39 "t2.l"
return(')');
break;
case 14:

#line 40 "t2.l"
return(EXP);
break;
case 15:

#line 41 "t2.l"
return('+');
break;
case 16:

#line 42 "t2.l"
return('-');
break;
case 17:

#line 43 "t2.l"
return('*');
break;
case 18:

#line 44 "t2.l"
return(',');
break;
case 19:

#line 45 "t2.l"
return(';');
break;
case 20:

#line 46 "t2.l"
	return(LE);
break;
case 21:

#line 47 "t2.l"
return(LT);
break;
case 22:

#line 48 "t2.l"
return(EQ);
break;
case 23:

#line 49 "t2.l"
return(GE);
break;
case 24:

#line 50 "t2.l"
return(GT);
break;
case 25:

#line 51 "t2.l"
return('|');
break;
case 26:

#line 52 "t2.l"
return('&');
break;
case 27:

#line 54 "t2.l"
return(MATERIAL);
break;
case 28:

#line 55 "t2.l"
return(OBJECT);
break;
case 29:

#line 56 "t2.l"
return(GLOBAL);
break;
case 30:

#line 57 "t2.l"
return(FOR);
break;
case 31:

#line 58 "t2.l"
return(CYLINDER);
break;
case 32:

#line 59 "t2.l"
return(BLOCK);
break;
case 33:

#line 60 "t2.l"
return(SPHERE);
break;
case 34:

#line 61 "t2.l"
return(PROPERTIES);
break;
case 35:

#line 62 "t2.l"
return(IN);
break;
case 36:

#line 63 "t2.l"
return(FT);
break;
case 37:

#line 64 "t2.l"
return(M);
break;
case 38:

#line 65 "t2.l"
return(CM);
break;
case 39:

#line 66 "t2.l"
return(DO);
break;
case 40:

#line 67 "t2.l"
return(IF);
break;
case 41:

#line 68 "t2.l"
return(THEN);
break;
case 42:

#line 69 "t2.l"
return(ELSE);
break;
case 43:

#line 70 "t2.l"
return(AT);
break;
case 44:

#line 71 "t2.l"
return(SWITCH);
break;
case 45:

#line 72 "t2.l"
return(UPTO);
break;
case 46:

#line 73 "t2.l"
return(DOWNTO);
break;
case 47:

#line 75 "t2.l"
return(MATERIAL);
break;
case 48:

#line 76 "t2.l"
return(OBJECT);
break;
case 49:

#line 77 "t2.l"
return(GLOBAL);
break;
case 50:

#line 78 "t2.l"
return(FOR);
break;
case 51:

#line 79 "t2.l"
return(CYLINDER);
break;
case 52:

#line 80 "t2.l"
return(BLOCK);
break;
case 53:

#line 81 "t2.l"
return(SPHERE);
break;
case 54:

#line 82 "t2.l"
return(PROPERTIES);
break;
case 55:

#line 83 "t2.l"
return(IN);
break;
case 56:

#line 84 "t2.l"
return(FT);
break;
case 57:

#line 85 "t2.l"
return(M);
break;
case 58:

#line 86 "t2.l"
return(CM);
break;
case 59:

#line 87 "t2.l"
return(DO);
break;
case 60:

#line 88 "t2.l"
return(IF);
break;
case 61:

#line 89 "t2.l"
return(THEN);
break;
case 62:

#line 90 "t2.l"
return(ELSE);
break;
case 63:

#line 91 "t2.l"
return(AT);
break;
case 64:

#line 92 "t2.l"
return(SWITCH);
break;
case 65:

#line 93 "t2.l"
return(UPTO);
break;
case 66:

#line 94 "t2.l"
return(DOWNTO);
break;
case 67:

#line 96 "t2.l"
{ return(ID); }
break;
case 68:

#line 97 "t2.l"
{ return(FLOAT); }
break;
case 69:

#line 98 "t2.l"
return(INTEGER);
break;
case 70:

#line 99 "t2.l"
return(STRING);
break;
case -1:
break;
default:
fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */

#line 102 "t2.l"
int yyvstop[] = {
0,

3,
0,

3,
0,

3,
0,

-1,
0,

26,
0,

11,
0,

12,
0,

13,
0,

17,
0,

15,
0,

18,
0,

16,
0,

68,
69,
0,

5,
0,

19,
0,

21,
0,

6,
0,

24,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

37,
67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

7,
0,

8,
0,

4,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

57,
67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

9,
0,

25,
0,

10,
0,

70,
0,

1,
0,

14,
0,

-2,
0,

20,
0,

22,
0,

23,
0,

43,
67,
0,

67,
0,

38,
67,
0,

67,
0,

39,
67,
0,

67,
0,

67,
0,

36,
67,
0,

67,
0,

40,
67,
0,

35,
67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

63,
67,
0,

67,
0,

58,
67,
0,

67,
0,

59,
67,
0,

67,
0,

67,
0,

56,
67,
0,

67,
0,

60,
67,
0,

55,
67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

2,
0,

68,
0,

68,
0,

67,
0,

67,
0,

67,
0,

67,
0,

30,
67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

50,
67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

42,
67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

41,
67,
0,

45,
67,
0,

67,
0,

67,
0,

67,
0,

62,
67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

61,
67,
0,

65,
67,
0,

32,
67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

52,
67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

46,
67,
0,

29,
67,
0,

67,
0,

28,
67,
0,

67,
0,

33,
67,
0,

44,
67,
0,

67,
0,

66,
67,
0,

49,
67,
0,

67,
0,

48,
67,
0,

67,
0,

53,
67,
0,

64,
67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

67,
0,

31,
67,
0,

27,
67,
0,

67,
0,

51,
67,
0,

47,
67,
0,

67,
0,

67,
0,

67,
0,

34,
67,
0,

54,
67,
0,
0};
# define YYTYPE int
struct yywork { YYTYPE verify, advance; } yycrank[] = {
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,3,	1,3,	
0,0,	1,3,	3,3,	3,3,	
0,0,	3,3,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	1,3,	0,0,	1,4,	
1,5,	3,3,	0,0,	1,6,	
1,7,	1,8,	1,9,	1,10,	
1,11,	1,12,	1,13,	10,57,	
13,58,	1,14,	1,14,	1,14,	
1,14,	1,14,	1,14,	1,14,	
1,14,	1,14,	1,14,	1,15,	
1,16,	1,17,	1,18,	1,19,	
17,62,	18,63,	1,20,	1,21,	
1,22,	1,23,	1,24,	1,25,	
1,26,	1,27,	1,28,	1,27,	
1,27,	1,27,	1,29,	1,27,	
1,30,	1,31,	1,27,	1,27,	
1,32,	1,33,	1,34,	1,27,	
1,27,	1,27,	1,27,	1,27,	
1,35,	19,64,	1,36,	1,37,	
27,27,	0,0,	1,38,	1,39,	
1,40,	1,41,	1,42,	1,43,	
1,44,	1,27,	1,45,	1,27,	
1,27,	1,27,	1,46,	1,27,	
1,47,	1,48,	1,27,	1,27,	
1,49,	1,50,	1,51,	1,27,	
1,27,	1,27,	1,27,	1,27,	
1,52,	1,53,	1,54,	4,4,	
23,69,	5,5,	47,27,	21,66,	
24,70,	23,27,	26,73,	4,4,	
4,0,	5,5,	5,56,	21,27,	
24,27,	50,27,	26,27,	14,59,	
47,95,	14,14,	14,14,	14,14,	
14,14,	14,14,	14,14,	14,14,	
14,14,	14,14,	14,14,	65,27,	
22,67,	30,77,	29,76,	28,74,	
4,55,	50,99,	4,4,	22,27,	
5,5,	25,71,	14,60,	28,75,	
22,68,	4,4,	25,72,	5,5,	
33,81,	28,27,	4,4,	30,27,	
5,5,	29,27,	31,78,	32,79,	
31,27,	34,82,	38,27,	32,27,	
33,27,	34,27,	32,80,	20,27,	
39,27,	42,27,	67,27,	4,4,	
14,61,	5,5,	72,27,	4,4,	
46,27,	5,5,	14,60,	20,27,	
20,27,	20,27,	20,27,	20,27,	
20,27,	20,27,	20,27,	20,27,	
20,27,	46,94,	70,108,	70,27,	
39,84,	42,88,	38,83,	41,27,	
20,27,	20,27,	20,27,	20,27,	
20,27,	20,27,	20,27,	20,27,	
20,27,	20,27,	20,27,	20,27,	
20,27,	20,27,	20,27,	20,27,	
20,27,	20,27,	20,27,	20,65,	
20,27,	20,27,	20,27,	20,27,	
20,27,	20,27,	41,87,	71,109,	
69,27,	71,27,	20,27,	69,107,	
20,27,	20,27,	20,27,	20,27,	
20,27,	20,27,	20,27,	20,27,	
20,27,	20,27,	20,27,	20,27,	
20,27,	20,27,	20,27,	20,27,	
20,27,	20,27,	20,27,	20,27,	
20,27,	20,27,	20,27,	20,27,	
20,27,	20,27,	40,27,	43,27,	
44,27,	45,27,	48,27,	58,58,	
55,0,	49,27,	51,27,	68,106,	
66,105,	73,110,	74,27,	58,58,	
58,101,	66,27,	73,27,	68,27,	
75,27,	76,111,	80,115,	45,92,	
77,112,	82,117,	83,27,	40,85,	
44,91,	79,114,	43,89,	45,93,	
55,55,	80,27,	77,27,	43,90,	
48,96,	49,97,	51,100,	40,86,	
78,113,	79,27,	58,58,	84,27,	
49,98,	78,27,	85,27,	90,27,	
92,27,	58,58,	81,116,	93,27,	
86,27,	104,132,	58,58,	59,102,	
59,102,	59,102,	59,102,	59,102,	
59,102,	59,102,	59,102,	59,102,	
59,102,	81,27,	87,27,	88,27,	
109,27,	89,27,	84,118,	58,58,	
60,103,	91,27,	60,103,	58,58,	
86,119,	60,104,	60,104,	60,104,	
60,104,	60,104,	60,104,	60,104,	
60,104,	60,104,	60,104,	61,14,	
61,14,	61,14,	61,14,	61,14,	
61,14,	61,14,	61,14,	61,14,	
61,14,	94,27,	88,121,	89,122,	
91,123,	87,120,	95,27,	96,27,	
99,27,	97,27,	98,27,	100,27,	
102,60,	103,104,	103,104,	103,104,	
103,104,	103,104,	103,104,	103,104,	
103,104,	103,104,	103,104,	105,133,	
106,134,	99,129,	107,135,	108,136,	
95,125,	97,127,	110,137,	98,128,	
107,27,	94,124,	96,126,	106,27,	
111,138,	112,139,	102,131,	114,141,	
105,27,	113,140,	108,27,	100,130,	
102,60,	113,27,	115,142,	116,143,	
110,27,	118,27,	117,144,	111,27,	
112,27,	116,27,	114,27,	117,27,	
119,27,	120,27,	121,27,	122,27,	
123,27,	124,27,	125,27,	126,27,	
118,145,	127,27,	128,27,	129,27,	
130,27,	135,159,	134,158,	133,157,	
136,27,	137,160,	123,149,	121,148,	
134,27,	119,146,	124,150,	125,151,	
133,27,	140,163,	127,153,	120,147,	
138,161,	139,162,	138,27,	141,164,	
142,165,	141,27,	143,27,	126,152,	
137,27,	129,155,	144,27,	130,156,	
140,27,	145,27,	128,154,	146,27,	
147,27,	148,27,	139,27,	149,27,	
150,27,	142,27,	151,27,	152,27,	
153,27,	155,27,	156,27,	154,27,	
157,27,	158,175,	159,176,	160,177,	
149,169,	161,178,	162,179,	159,27,	
145,166,	151,171,	164,181,	160,27,	
152,172,	146,167,	154,174,	165,182,	
161,27,	158,27,	166,27,	163,180,	
147,168,	163,27,	150,170,	167,27,	
168,27,	164,27,	153,173,	165,27,	
169,27,	170,27,	171,27,	172,27,	
173,27,	174,27,	176,27,	177,27,	
179,27,	178,192,	180,193,	167,183,	
175,191,	181,27,	182,27,	183,27,	
184,27,	185,27,	186,27,	187,27,	
188,27,	173,189,	170,186,	168,184,	
169,185,	174,190,	189,27,	175,27,	
178,27,	190,27,	192,198,	186,195,	
183,194,	172,188,	171,187,	191,197,	
193,199,	191,27,	192,27,	194,27,	
195,27,	196,27,	197,27,	198,27,	
199,203,	200,27,	201,27,	193,27,	
202,27,	203,205,	203,27,	204,27,	
188,196,	205,27,	206,27,	0,0,	
0,0,	0,0,	0,0,	199,27,	
0,0,	0,0,	196,202,	0,0,	
195,201,	202,204,	0,0,	0,0,	
0,0,	194,200,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	204,206,	0,0,	
0,0};
struct yysvf yysvec[] = {
0,	0,	0,
1,	0,		yyvstop+1,
0,	yysvec+1,	yyvstop+3,
5,	0,		yyvstop+5,
-126,	0,		0,	
-128,	0,		yyvstop+7,
0,	0,		yyvstop+9,
0,	0,		yyvstop+11,
0,	0,		yyvstop+13,
0,	0,		yyvstop+15,
5,	0,		yyvstop+17,
0,	0,		yyvstop+19,
0,	0,		yyvstop+21,
3,	0,		yyvstop+23,
97,	0,		yyvstop+25,
0,	0,		yyvstop+28,
0,	0,		yyvstop+30,
3,	0,		yyvstop+32,
4,	0,		yyvstop+34,
32,	0,		yyvstop+36,
151,	0,		yyvstop+38,
55,	yysvec+20,	yyvstop+40,
79,	yysvec+20,	yyvstop+42,
49,	yysvec+20,	yyvstop+44,
56,	yysvec+20,	yyvstop+46,
86,	yysvec+20,	yyvstop+48,
58,	yysvec+20,	yyvstop+50,
12,	yysvec+20,	yyvstop+52,
89,	yysvec+20,	yyvstop+54,
93,	yysvec+20,	yyvstop+56,
91,	yysvec+20,	yyvstop+59,
96,	yysvec+20,	yyvstop+61,
99,	yysvec+20,	yyvstop+63,
100,	yysvec+20,	yyvstop+65,
101,	yysvec+20,	yyvstop+67,
0,	0,		yyvstop+69,
0,	0,		yyvstop+71,
0,	0,		yyvstop+73,
98,	yysvec+20,	yyvstop+75,
104,	yysvec+20,	yyvstop+77,
190,	yysvec+20,	yyvstop+79,
131,	yysvec+20,	yyvstop+81,
105,	yysvec+20,	yyvstop+83,
191,	yysvec+20,	yyvstop+85,
192,	yysvec+20,	yyvstop+87,
193,	yysvec+20,	yyvstop+89,
112,	yysvec+20,	yyvstop+91,
46,	yysvec+20,	yyvstop+94,
194,	yysvec+20,	yyvstop+96,
197,	yysvec+20,	yyvstop+98,
57,	yysvec+20,	yyvstop+100,
198,	yysvec+20,	yyvstop+102,
0,	0,		yyvstop+104,
0,	0,		yyvstop+106,
0,	0,		yyvstop+108,
-270,	yysvec+4,	yyvstop+110,
0,	0,		yyvstop+112,
0,	0,		yyvstop+114,
-278,	0,		yyvstop+116,
279,	0,		0,	
301,	0,		0,	
311,	0,		0,	
0,	0,		yyvstop+118,
0,	0,		yyvstop+120,
0,	0,		yyvstop+122,
71,	yysvec+20,	yyvstop+124,
205,	yysvec+20,	yyvstop+127,
106,	yysvec+20,	yyvstop+129,
207,	yysvec+20,	yyvstop+132,
160,	yysvec+20,	yyvstop+134,
127,	yysvec+20,	yyvstop+137,
161,	yysvec+20,	yyvstop+139,
110,	yysvec+20,	yyvstop+141,
206,	yysvec+20,	yyvstop+144,
202,	yysvec+20,	yyvstop+146,
208,	yysvec+20,	yyvstop+149,
209,	yysvec+20,	yyvstop+152,
222,	yysvec+20,	yyvstop+154,
233,	yysvec+20,	yyvstop+156,
229,	yysvec+20,	yyvstop+158,
221,	yysvec+20,	yyvstop+160,
253,	yysvec+20,	yyvstop+162,
213,	yysvec+20,	yyvstop+164,
214,	yysvec+20,	yyvstop+166,
231,	yysvec+20,	yyvstop+169,
234,	yysvec+20,	yyvstop+171,
240,	yysvec+20,	yyvstop+174,
254,	yysvec+20,	yyvstop+176,
255,	yysvec+20,	yyvstop+179,
257,	yysvec+20,	yyvstop+181,
235,	yysvec+20,	yyvstop+183,
261,	yysvec+20,	yyvstop+186,
236,	yysvec+20,	yyvstop+188,
239,	yysvec+20,	yyvstop+191,
285,	yysvec+20,	yyvstop+194,
290,	yysvec+20,	yyvstop+196,
291,	yysvec+20,	yyvstop+198,
293,	yysvec+20,	yyvstop+200,
294,	yysvec+20,	yyvstop+202,
292,	yysvec+20,	yyvstop+204,
295,	yysvec+20,	yyvstop+206,
0,	0,		yyvstop+208,
311,	yysvec+59,	yyvstop+210,
333,	0,		0,	
230,	yysvec+103,	yyvstop+212,
324,	yysvec+20,	yyvstop+214,
319,	yysvec+20,	yyvstop+216,
316,	yysvec+20,	yyvstop+218,
326,	yysvec+20,	yyvstop+220,
256,	yysvec+20,	yyvstop+222,
332,	yysvec+20,	yyvstop+225,
335,	yysvec+20,	yyvstop+227,
336,	yysvec+20,	yyvstop+229,
329,	yysvec+20,	yyvstop+231,
338,	yysvec+20,	yyvstop+233,
330,	yysvec+20,	yyvstop+235,
337,	yysvec+20,	yyvstop+237,
339,	yysvec+20,	yyvstop+239,
333,	yysvec+20,	yyvstop+241,
340,	yysvec+20,	yyvstop+243,
341,	yysvec+20,	yyvstop+245,
342,	yysvec+20,	yyvstop+247,
343,	yysvec+20,	yyvstop+249,
344,	yysvec+20,	yyvstop+252,
345,	yysvec+20,	yyvstop+254,
346,	yysvec+20,	yyvstop+256,
347,	yysvec+20,	yyvstop+258,
349,	yysvec+20,	yyvstop+260,
350,	yysvec+20,	yyvstop+262,
351,	yysvec+20,	yyvstop+264,
352,	yysvec+20,	yyvstop+266,
0,	yysvec+59,	0,	
0,	yysvec+103,	0,	
364,	yysvec+20,	yyvstop+268,
360,	yysvec+20,	yyvstop+270,
353,	yysvec+20,	yyvstop+272,
356,	yysvec+20,	yyvstop+274,
376,	yysvec+20,	yyvstop+277,
370,	yysvec+20,	yyvstop+279,
386,	yysvec+20,	yyvstop+281,
380,	yysvec+20,	yyvstop+283,
373,	yysvec+20,	yyvstop+285,
389,	yysvec+20,	yyvstop+287,
374,	yysvec+20,	yyvstop+289,
378,	yysvec+20,	yyvstop+292,
381,	yysvec+20,	yyvstop+295,
383,	yysvec+20,	yyvstop+297,
384,	yysvec+20,	yyvstop+299,
385,	yysvec+20,	yyvstop+301,
387,	yysvec+20,	yyvstop+304,
388,	yysvec+20,	yyvstop+306,
390,	yysvec+20,	yyvstop+308,
391,	yysvec+20,	yyvstop+310,
392,	yysvec+20,	yyvstop+312,
395,	yysvec+20,	yyvstop+314,
393,	yysvec+20,	yyvstop+316,
394,	yysvec+20,	yyvstop+319,
396,	yysvec+20,	yyvstop+322,
413,	yysvec+20,	yyvstop+325,
403,	yysvec+20,	yyvstop+327,
407,	yysvec+20,	yyvstop+329,
412,	yysvec+20,	yyvstop+331,
402,	yysvec+20,	yyvstop+333,
417,	yysvec+20,	yyvstop+335,
421,	yysvec+20,	yyvstop+337,
423,	yysvec+20,	yyvstop+339,
414,	yysvec+20,	yyvstop+341,
419,	yysvec+20,	yyvstop+344,
420,	yysvec+20,	yyvstop+346,
424,	yysvec+20,	yyvstop+348,
425,	yysvec+20,	yyvstop+350,
426,	yysvec+20,	yyvstop+352,
427,	yysvec+20,	yyvstop+354,
428,	yysvec+20,	yyvstop+356,
429,	yysvec+20,	yyvstop+358,
451,	yysvec+20,	yyvstop+360,
430,	yysvec+20,	yyvstop+362,
431,	yysvec+20,	yyvstop+365,
452,	yysvec+20,	yyvstop+368,
432,	yysvec+20,	yyvstop+370,
434,	yysvec+20,	yyvstop+373,
437,	yysvec+20,	yyvstop+375,
438,	yysvec+20,	yyvstop+378,
439,	yysvec+20,	yyvstop+381,
440,	yysvec+20,	yyvstop+383,
441,	yysvec+20,	yyvstop+386,
442,	yysvec+20,	yyvstop+389,
443,	yysvec+20,	yyvstop+391,
444,	yysvec+20,	yyvstop+394,
450,	yysvec+20,	yyvstop+396,
453,	yysvec+20,	yyvstop+399,
461,	yysvec+20,	yyvstop+402,
462,	yysvec+20,	yyvstop+404,
471,	yysvec+20,	yyvstop+406,
463,	yysvec+20,	yyvstop+408,
464,	yysvec+20,	yyvstop+410,
465,	yysvec+20,	yyvstop+412,
466,	yysvec+20,	yyvstop+414,
467,	yysvec+20,	yyvstop+417,
483,	yysvec+20,	yyvstop+420,
469,	yysvec+20,	yyvstop+422,
470,	yysvec+20,	yyvstop+425,
472,	yysvec+20,	yyvstop+428,
474,	yysvec+20,	yyvstop+430,
475,	yysvec+20,	yyvstop+432,
477,	yysvec+20,	yyvstop+434,
478,	yysvec+20,	yyvstop+437,
0,	0,	0};
#define yytop 590
struct yysvf *yybgin = yysvec+1;
char yymatch[] = {
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,011 ,012 ,01  ,011 ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
011 ,01  ,01  ,01  ,'$' ,01  ,01  ,01  ,
01  ,01  ,01  ,'+' ,01  ,'+' ,01  ,01  ,
'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,
'0' ,'0' ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,'A' ,'A' ,'A' ,'A' ,'E' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,01  ,01  ,01  ,01  ,'$' ,
01  ,'A' ,'A' ,'A' ,'A' ,'E' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,01  ,01  ,01  ,01  ,01  ,
0};
char yyextra[] = {
0,1,1,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
char yytext[YYLMAX];
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
yylook(){
	register struct yysvf *yystate, **lsp;
	register int yyt;
	register struct yywork *yyk;
	struct yysvf *yyz;
	int yych;
	int yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == 0){		/* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == 0)break;
				}
			*yylastch++ = yych = input();
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( yyt > 0){
				yyt = yyr + yych;
				yyk = yycrank + yyt;
				if (yyt <= yytop && yyk->verify+yysvec == yystate){
					if(yyk->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyk->advance+yysvec;
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if(yyt < 0) {		/* r < yycrank */
				yyt = yyr = -yyt;
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				yyk = yycrank + yyt;
				if(yyt <= yytop && yyk->verify+yysvec == yystate){
					if(yyk->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyk->advance+yysvec;
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
				yyk = yycrank + yyt;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyk->verify+yysvec == yystate){
					if(yyk->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyk->advance+yysvec;
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != 0){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
#ifdef __cplusplus
yyback(int *p, int m)
#else
yyback(p, m)
	int *p;
#endif
{
if (p==0) return(0);
while (*p)
	{
	if (*p++ == m)
		return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
yyinput(){
	return(input());
	}
#ifdef __cplusplus
yyoutput(int c)
#else
yyoutput(c)
  int c;
#endif
{
	output(c);
	}
#ifdef __cplusplus
yyunput(int c)
#else
yyunput(c)
   int c;
#endif
{
	unput(c);
	}
