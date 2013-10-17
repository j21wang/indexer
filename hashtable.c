#include "hashtable.h"

HashTable *createHashTable(unsigned int capacity) {

	int i;

	HashTable *hashtable;
	hashtable = malloc(sizeof(HashTable));
	if (hashtable == NULL) {
		return NULL;
	}
	hashtable->size = capacity;
	hashtable->table = malloc(hashtable->size * sizeof(LinkedList));
	if (hashtable->table == NULL) {
		free(hashtable);
		return NULL;
	}

	for (i = 0; i < capacity; i++) {
		hashtable->table[i] = NULL;
	}

	return hashtable;

}

/*void destroyHashTable(HashTable *hashtable) {

	unsigned int i, j, n, m;
	LinkedList *list;
	WordListPair *wlp;

	if (hashtable == NULL) {
		return;
	}

	n = hashtable->count;
	table = hashtable->table;
	i = 0;
}
*/

int ht_update(HashTable *hashtable, char *word, SortedListPtr wordlist) {

	unsigned int index;
	LinkedList *bucket;
	LinkedList *prev;
	LinkedList *newnode;
	WordCountPair *wcp;

	if (hashtable == NULL) {
		return 0;
	}
	if (word == NULL) {
		return 0;
	}

	index = hash(word) % hashtable->size;
	bucket = hashtable->table[index];
	prev = bucket;

	while (bucket != NULL && strcmp((bucket->wcp)->word, word) != 0) {
		prev = bucket;
		bucket = bucket->next;
	}
	if (bucket == NULL) {
		newnode = malloc(sizeof(LinkedList));
		wcp = malloc(sizeof(WordCountPair));
		wcp->word = word;
		wcp->count = 1;
		newnode->wcp = wcp;
		newnode->next = NULL;
		if (prev == NULL) {
			hashtable->table[index] = newnode;
		} else {
			prev->next = newnode;
		}
		SLInsert(wordlist, word);
		return 1;
	}

	(bucket->wcp)->count++;
	return 1;

}

WordCountPair *ht_get(HashTable *hashtable, char *word) {

	unsigned int index;
	LinkedList *bucket;
	LinkedList *prev;
	LinkedList *newnode;
	WordCountPair *wcp;

	if (hashtable == NULL) {
		return 0;
	}
	if (word == NULL) {
		return 0;
	}

	index = hash(word) % hashtable->size;
	bucket = hashtable->table[index];
	prev = bucket;

	while (bucket != NULL && strcmp((bucket->wcp)->word, word) != 0) {
		prev = bucket;
		bucket = bucket->next;
	}
	if (bucket == NULL) {
		return NULL;
	}

	return bucket->wcp;

}

void ht_merge(SortedListPtr list, const char* filepath, HashTable *hashtable, SortedListPtr wordlist) {
	FileCountPair *fcp;
	WordCountPair *wcp;
	SortedListIteratorPtr iterator;
	SortedListIteratorPtr mainListIterator;
	char *word;
	WordListPair *wlp;

	iterator = SLCreateIterator(wordlist);
	mainListIterator = SLCreateIterator(list);
	
	while ((word = SLNextItem(iterator)) != NULL) {
		wcp = ht_get(hashtable, word);
		fcp = malloc(sizeof(FileCountPair));
		fcp->filepath = filepath;
		fcp->count = wcp->count;
		while ((wlp = SLNextItem(mainListIterator)) != NULL) {
		}
		if (wlp == NULL) {	//the word is not already in the main list
			SortedListPtr newlist = SLCreate(&compareFileCounts);
			SLInsert(newlist, fcp);
			wlp = malloc(sizeof(WordListPair));
			wlp->word = word;
			wlp->list = newlist;
			SLInsert(list, wlp);
		} else {
			SLInsert(wlp->list, fcp);
		}
	}
}

unsigned long hash(char *string) {

	unsigned long hash = 5381;
	int c;

	while (c = *string++) {
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}
			

int compareFileCounts(void *p1, void *p2) {
	int count1 = ((FileCountPair *) p1)->count;
	int count2 = ((FileCountPair *) p2)->count;
	return count1 - count2;
}

int compareWordListPairs(void *p1, void *p2) {
	char *s1 = ((WordListPair *) p1)->word;
	char *s2 = ((WordListPair *) p2)->word;

	return strcmp(s1, s2);
}
