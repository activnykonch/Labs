CC=cl
CFLAGS=-c -Wall

all: magic

magic: lab5.2.obj tree.obj
	$(CC) lab5.2.obj tree.obj -o magic

lab5.2.o: lab5.2.c
	$(CC) $(CFLAGS) lab5.2.c

tree.o: tree.c
	$(CC) $(CFLAGS) tree.c

