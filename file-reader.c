#include "stdio.h"
#include "dirent.h"
#include "unistd.h"
#include "string.h"
#include "sys/stat.h"
#include "stdlib.h"
#include "file-reader.h"

void readFile(const char *filename){
   FILE *fp;
   char line[100];

   fp = fopen(filename,"r");

   while(fgets(line,100,fp) != NULL){
      printf("%s",line);
   }
   fclose(fp);
}

void scan_dir(const char *dir){

   struct dirent *entry;
   DIR *d = opendir(dir);
   struct stat statbuf;

   if(d==0){
      perror("opendir");
      return;
   }

   chdir(dir);
   while((entry = readdir(d))!=0){
      lstat(entry->d_name,&statbuf);
      if(S_ISDIR(statbuf.st_mode)){
         if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0) continue;
         scan_dir(entry->d_name);
      }
       printf("%s\n",entry->d_name);
       readFile(entry->d_name);

   }
   chdir("..");
   closedir(d);
}

void outputToFile (const char *filename){

   FILE *outfile;
   outfile = fopen(filename,"w");
   const char *text = "Write this to the file";
   fprintf(outfile,"this is a test %s\n",text);

}
