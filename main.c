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

	scan_dir(argv[2], argv[2], words);

   outputPairsToFile(argv[1],words);
   SLDestroy(words);
   return 0;
}
