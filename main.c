/*
 * Joyce Want and Kevin Sung
 * main.c for indexer
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "sorted-list.h"
#include "file-reader.h"

int main(int argc, char **argv) {

	FILE *index;
	FILE *file;
	
	CompareFuncT cf = &compareStrings;
	SortedListPtr words = SLCreate(cf);

	scan_dir(argv[2]);

}
