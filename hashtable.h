#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <string.h>
#include "sorted-list.h"

typedef struct FileCountPair {
	const char *filepath;
	unsigned int count;
} FileCountPair;

typedef struct WordCountPair {
	char *word;
	unsigned int count;
} WordCountPair;

typedef struct WordListPair {
	char *word;
	SortedListPtr list;
} WordListPair;

typedef struct LinkedList {
	WordCountPair *wcp;
	struct LinkedList *next;
} LinkedList;

typedef struct HashTable {
	unsigned int size;
	LinkedList **table;
} HashTable;

HashTable *createHashTable(unsigned int capacity); 

WordCountPair *ht_get(HashTable *hashtable, char *word);

int ht_update(HashTable *hashtable, char *word, SortedListPtr wordlist);

void ht_merge(SortedListPtr list, const char* filepath, HashTable *hashtable, SortedListPtr wordlist);

unsigned long hash(char *string); 

int compareFileCounts(void *p1, void *p2);

int compareWordListPairs(void *p1, void *p2);

#endif
