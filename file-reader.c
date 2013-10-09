#include "stdio.h"

main() {
   FILE *fp;
   char line[100];

   fp = fopen("helloworld.txt","r");

   while(fgets(line,100,fp) != NULL){
      printf("%s",line);
   }
   fclose(fp);
}

