#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"

int main(int argc, char **argv) {

	FILE *file;
	TokenizerT *tokenizer;
	char *token;
	char line[100];
	int i = 0;

	printf("filename is %s\n", argv[1]);

	file = fopen(argv[1], "r");

	for (i = 0; i < 3; i++) {
		if (fgets(line, 100, file) == NULL) {
			printf("NULL");
		}
		printf("Line %d is %s and it has %d characters\n", i, line, strlen(line));
	}

	tokenizer = TKCreate(file);

	while ((token = TKGetNextToken(tokenizer)) != NULL) {
		printf("%s\n", token);
	}

	return 0;
	
}
