CC = gcc
CFLAGS = -c -Wall -g

all: index
index: main.o file-reader.o tokenizer.o sorted-list.o hashtable.o
	 $(CC) main.o file-reader.o tokenizer.o sorted-list.o hashtable.o -o index

main.o: main.c sorted-list.h tokenizer.h
		  $(CC) $(CFLAGS) main.c

file-reader.o: file-reader.c file-reader.h
			$(CC) $(CFLAGS) file-reader.c

tokenizer.o: tokenizer.c tokenizer.h
			$(CC) $(CFLAGS) tokenizer.c

sorted-list.o: sorted-list.c sorted-list.h
			$(CC) $(CFLAGS) sorted-list.c

hashtable.o: hashtable.c hashtable.h
			$(CC) $(CFLAGS) hashtable.c

clean: rm-rf *.o index
		 rm-rf *.o 
