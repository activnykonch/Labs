CC=cl
CFLAGS=-c -Wall

all: magic

magic: lab5.1.obj stack.obj
	$(CC) lab5.1.obj stack.obj -o magic

lab5.1.o: lab5.1.c
	$(CC) $(CFLAGS) lab5.1.c

stack.o: stack.c
	$(CC) $(CFLAGS) stack.c

