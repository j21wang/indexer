#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"

void main(int argc, char **argv) {

	FILE *file;
	TokenizerT *tokenizer;
	char *token;
	char line[100];
	int i = 0;

	printf("filename is %s\n", argv[1]);

	file = fopen(argv[1], "r");
/*
	i = 1;
	while (fgets(line, 500, file) != NULL) {
		printf("Line %d is %s\n", i, line);
		i++;
	}
*/
	tokenizer = TKCreate(file);

	//printf("About to tokenize:\n");
	while ((token = TKGetNextToken(tokenizer)) != NULL) {
		printf("%s\n", token);
	}

}
