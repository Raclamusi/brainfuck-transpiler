#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 300000

int main(int argc, char *argv[]) {
	FILE *ifp = NULL;
	FILE *ofp = NULL;
	int c;
	
	if (argc == 1) {
		puts("ファイルを指定しやがれ。");
		return EXIT_FAILURE;
	}
	if ((ifp = fopen(argv[1], "r")) == NULL) {
		perror("ファイルが開けません。どうして……。");
		return EXIT_FAILURE;
	}
	if ((ofp = fopen(argc >= 3 ? argv[2] : "a.c", "w")) == NULL) {
		fclose(ifp);
		perror("ファイルが作れません。どうして……。");
		return EXIT_FAILURE;
	}
	fputs("#include<stdio.h>\nint main(){", ofp);
	fprintf(ofp, "unsigned char m[%d];unsigned char*p=m;", MEMORY_SIZE);
	while ((c = fgetc(ifp)) != EOF) {
		switch (c) {
			case '+': fputs("++*p;", ofp); break;
			case '-': fputs("--*p;", ofp); break;
			case '>': fputs("++p;", ofp); break;
			case '<': fputs("--p;", ofp); break;
			case '[': fputs("while(*p){", ofp); break;
			case ']': fputs("}", ofp); break;
			case ',': fputs("*p=getchar();", ofp); break;
			case '.': fputs("putchar(*p);", ofp); break;
			default: break;
		}
	}
	fputs("}\n", ofp);
	fclose(ofp);
	fclose(ifp);
	return EXIT_SUCCESS;
}
