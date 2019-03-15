BEGIN		{ printf("char *yytokens[] = {\n"); }
/^.*define/	{ printf("\t\"");
		  if (NF == 4) printf("%s", $3); else printf("%s", $2);
		  printf("\",\n");
		}
END		{ printf("\t0\n};\n"); }
