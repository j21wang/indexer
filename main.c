/*
 * Joyce Wang and Kevin Sung
 * main.c for indexer
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "sorted-list.h"
#include "file-reader.h"
#include "hashtable.h"

int main(int argc, char **argv) {

   if(argc != 3){
      printf("Error: invalid input\n");
      return -1;
   }

	CompareFuncT cf = &compareWordListPairs;
	SortedListPtr words = SLCreate(cf);
    char *filepath = argv[2];
    if (filepath[strlen(filepath)-1] == '/') {
        filepath[strlen(filepath)-1] = '\0';
    }

	scan_dir(filepath, filepath, words);

   outputPairsToFile(argv[1],words);
   SLDestroy(words);
   return 0;
}
