CFLAGS=-Wall -std=c99 
LIBS=-lm -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_font -lallegro

all: jewels

jewels: main.o lib.o matrix.o
	gcc -o jewels main.o lib.o matrix.o $(CFLAGS) $(LIBS)

main.o: main.c
	gcc -c main.c $(CFLAGS)

lib.o: lib.c
	gcc -c lib.c $(CFLAGS)

matrix.o: matrix.c lib.c
	gcc -c matrix.c lib.c $(CFLAGS)

clean:
	rm -f *~ 

purge: clean
	rm -f *.o *.gch hello