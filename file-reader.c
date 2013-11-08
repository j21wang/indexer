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
   char line[500];

   fp = fopen(filename,"r");

   while(fgets(line,500,fp) != NULL){
      printf("%s",line);
   }
   fclose(fp);
}

void readWordsFromFile(const char *filepath,const char *filename,SortedListPtr list){

   printf("Entering readWordsFromFile: filepath = %s, filename = %s\n", filepath, filename);

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

   //printf("path: %s\n",filepath);
   if(tokenizer == NULL){
      return;
   }

   while((token = TKGetNextToken(tokenizer)) != NULL){
      //printf("%s\n",token);
      ht_update(hashTable, token, wordlist);
   }

   SortedListIteratorPtr iterator = SLCreateIterator(wordlist);
   while ((token = SLNextItem(iterator)) != NULL) {
      wcp = ht_get(hashTable,token);   
      //printf("Word: %s, Count: %d\n", wcp->word, wcp->count);
   }
   ht_merge(list, filepath, hashTable, wordlist);   //write this function
   destroyHashTable(hashTable);

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

void scan_dir(char *path, const char *dir, SortedListPtr words){

   printf("Entering scan_dir: path = %s, dir = %s\n", path, dir);

   struct dirent *entry;
   DIR *d = opendir(dir);
   struct stat statbuf;

   if(dir_exist(dir)){ //directory
      chdir(dir);
      while((entry = readdir(d))!=0){
         lstat(entry->d_name,&statbuf);
         if(S_ISDIR(statbuf.st_mode)){ //it is directory
            if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0) continue;
            char *filepath = malloc(1024*sizeof(char));
            strcpy(filepath,path);
            strcat(filepath,"/");
            strcat(filepath,entry->d_name);
            scan_dir(filepath,entry->d_name, words);
         }
		  if(!dir_exist(entry->d_name)) {
           char *filepath = malloc(1024*sizeof(char));
           filepath = malloc(1024*sizeof(char));
           strcpy(filepath,path);
           strcat(filepath,"/");
           strcat(filepath,entry->d_name);
           readWordsFromFile(filepath, entry->d_name, words);
        }

      }
      chdir("..");
      closedir(d);
   } else if(file_exist(dir)){ //file
      readWordsFromFile(dir,dir,words);
   } else { //error
      perror(dir);
      return;
   }
}

void outputPairsToFile (FILE *outfile, SortedListPtr wordlist){

   SortedListIteratorPtr mainIterator;
   SortedListIteratorPtr pairIterator;
   WordListPair *wlp;
   FileCountPair *fcp;

   mainIterator = SLCreateIterator(wordlist);

   while((wlp = SLNextItem(mainIterator)) != NULL){
      fprintf(outfile,"<list> %s\n",wlp->word);
      
      pairIterator = SLCreateIterator(wlp->list);
      while((fcp = SLNextItem(pairIterator)) != NULL){
         fprintf(outfile,"%s %d ",fcp->filepath,fcp->count);
      }
      fprintf(outfile,"\n</list>\n");
   }
}
