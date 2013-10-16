#include "stdio.h"
#include "dirent.h"
#include "unistd.h"
#include "string.h"
#include "sys/stat.h"
#include "stdlib.h"
#include "file-reader.h"
#include "hashtable.h"
#include "sorted-list.h"
#include "tokenizer.h"

void readFile(const char *filename){
   FILE *fp;
   char line[100];

   fp = fopen(filename,"r");

   while(fgets(line,100,fp) != NULL){
      printf("%s",line);
   }
   fclose(fp);
}

void readWordsFromFile(const char *filename,SortedListPtr list){
   FILE *fp;
   TokenizerT* tokenizer;
   HashTable* hashTable;
   char *token = NULL;
   SortedListPtr wordlist;
   WordCountPair *wcp;

   fp = fopen(filename,"r");
   tokenizer = TKCreate(fp);
   hashTable = createHashTable(100);
   wordlist = SLCreate(&compareStrings);

   if(tokenizer == NULL){
      return;
   }

   while((token = TKGetNextToken(tokenizer)) != NULL){
      printf("%s\n",token);
      ht_update(hashTable, token, wordlist);
   }

   SortedListIteratorPtr iterator = SLCreateIterator(wordlist);
   while ((token = SLNextItem(iterator)) != NULL) {
      wcp = ht_get(hashTable,token);   
      printf("Word: %s, Count: %d\n", wcp->word, wcp->count);
   }
   ht_merge(list, filename, hashTable, wordlist);   //write this function

   fclose(fp);
}

int file_exist(const char *filename){
   struct stat buffer;
   return (stat (filename, &buffer) == 0);
}

int dir_exist(const char *path){
   struct stat buffer;
   return stat(path, &buffer) == 0 && S_ISDIR(buffer.st_mode);
}

void scan_dir(const char *dir, SortedListPtr words){

   struct dirent *entry;
   DIR *d = opendir(dir);
   struct stat statbuf;

   if(dir_exist(dir)){
      chdir(dir);
      while((entry = readdir(d))!=0){
         lstat(entry->d_name,&statbuf);
         if(S_ISDIR(statbuf.st_mode)){
            if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0) continue;
            scan_dir(entry->d_name, words);
         }
          printf("%s\n",entry->d_name);
          readWordsFromFile(entry->d_name, words);

      }
      chdir("..");
      closedir(d);
   } else if(file_exist(dir)){
      readWordsFromFile(dir,words);
   } else {
      perror(dir);
      return;
   }
}

void outputToFile (const char *filename){

   FILE *outfile;
   outfile = fopen(filename,"w");
   const char *text = "Write this to the file";
   fprintf(outfile,"this is a test %s\n",text);

}

void outputPairsToFile (const char *filename, SortedListPtr wordlist){

   SortedListIteratorPtr mainIterator;
   SortedListIteratorPtr pairIterator;
   FILE *outfile;
   const char *word;
   WordListPair *wlp;
   FileCountPair *fcp;

   outfile = fopen(filename,"w");

   mainIterator = SLCreateIterator(wordlist);

   while((word = SLNextItem(wordlist)) != NULL){
      fprintf(outfile,"<list> %s\n",word);
      
      pairIterator = SLCreateIterator(word);
      while((wlp = SLNextItem(pairIterator)) != NULL){
         fprintf(outfile,"%s %n ",wlp->word,fcp->count);
      }
      fprintf(outfile,"</list>");
   }
}
