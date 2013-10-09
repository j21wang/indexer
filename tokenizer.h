/*
 * Joyce Want and Kevin Sung
 * tokenizer.h
 */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdlib.h>

struct TokenizerT_ {
	FILE* file;
	char current_line[100];
	char* current_position;
};
typedef struct TokenizerT_ TokenizerT;

char is_escape_character(char character);

int char_to_hex(char character);

int char_to_oct(char character);

int is_oct_digit(char oct_digit);

char* unescape_string(char* string);

TokenizerT *TKCreate(FILE *file);

void TKDestroy(TokenizerT *tk);

char is_delimiter(char character, char* delimiters);

char *TKGetNextToken(TokenizerT *tk);

#endif
