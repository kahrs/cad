BEGIN		{ printf("char *yystates[] = {\n"); }
/^state/	{ printf("\t\"");
		  for(;;) {
			getline;
			if (length($0) == 0) break;
		  	printf("%s\\n", $0);
		  }
		  printf("\",\n");
		}
END		{ printf("\t0\n};\n"); }
