CFLAGS=-Wall -std=c99 
LIBS=-lm -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_font -lallegro

all: jewels

jewels: main.o
	gcc -o jewels main.o $(CFLAGS) $(LIBS)

main.o: main.c
	gcc -c main.c $(CFLAGS)

clean:
	rm -f *~ *.o

purge: clean
	rm -f hello