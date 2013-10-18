#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdlib.h>
#include "sorted-list.h"

void readFile(const char *filename);

void scan_dir(char *path, const char *dir, SortedListPtr words);

void outputToFile(const char *filename);
void outputPairsToFile(const char *filename,SortedListPtr words);
void readWordsFromFile(const char *filepath,const char *filename,SortedListPtr words);

#endif
