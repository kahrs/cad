/*
 * Lex scanner interface
 */

#include "y.tab.h"

#include <ctype.h>
#include <stdio.h>

int value;
extern FILE *asStream;

int lineNumber = 0; /* cpp gives 1 extra */
char savedCharacters[10] =
	{ '\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'} ;
char *savePointer = savedCharacters;
/*
 * stream interface to lex
 */

input()
{
	char newCharacter;

	if (*savePointer == '\0')
	{
		newCharacter = getc(asStream);
		if (newCharacter == -1) return(0); /* EOF */
		if (newCharacter == '\n') lineNumber++;
	} /* end if */
	else
		newCharacter = *savePointer--;
	return(newCharacter);
} /* end input */

unput(c)
char c;
{
	*++savePointer = c;
} /* end unput */

output(c)
char c;
{
	fprintf(stderr, "ch=%c (%o)\n", c, c);
	Bug("output called.");
} /* end output */
