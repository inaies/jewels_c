CFLAGS=-Wall -std=c99 
LIBS=-lm -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_font -lallegro

all: hello

hello: hello.o
	gcc -o hello hello.o $(CFLAGS) $(LIBS)

hello.o: hello.c
	gcc -c hello.c $(CFLAGS)

clean:
	rm -f *~ *.o

purge: clean
	rm -f hello