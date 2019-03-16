#include "stdarg.h"
#include <stdio.h>

void sub(int count, ...);

void main(int argc, char **argv)
{
	sub(10, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0);
}

void sub(int count, ...)
{
	va_list ap;
	int i;
	va_start(ap, count);
	for (i=0; i<count; i++)
		fprintf(stdout, "%d=%f\n", i, va_arg(ap, double));
	va_end(ap);
}
