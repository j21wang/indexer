/*
 * Joyce Wang and Kevin Sung
 * main.c for indexer
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

    char cwd[200];
    getcwd(cwd,200);
	scan_dir(filepath, filepath, words);
    chdir(cwd);

    FILE *outfile;
    printf("Outputting index to: %s\n", argv[1]);
    outfile = fopen(argv[1], "w");

   outputPairsToFile(outfile, words);
   fclose(outfile);
   SLDestroy(words);
   return 0;
}
