CFLAGS=-Wall -std=c99 
LIBS=-lm -lallegro_ttf -lallegro_image -lallegro_primitives -lallegro_acodec -lallegro_audio -lallegro_font -lallegro

all: jewels

jewels: main.o lib.o matrix.o mouse.o pontuacao.o animacao.o
	gcc -o jewels main.o lib.o matrix.o mouse.o pontuacao.o animacao.o $(CFLAGS) $(LIBS)

main.o: main.c
	gcc -c main.c $(CFLAGS)

lib.o: lib.c lib.h
	gcc -c lib.c $(CFLAGS)

matrix.o: matrix.c matrix.h lib.h
	gcc -c matrix.c lib.c $(CFLAGS)

mouse.o: mouse.c mouse.h 
	gcc -c mouse.c $(CFLAGS)

pontuacao.o: pontuacao.c pontuacao.h
	gcc -c pontuacao.c $(CFLAGS)

animacao.o: animacao.c animacao.h
	gcc -c animacao.c $(CFLAGS)

clean:
	rm -f *~ 

purge: clean
	rm -f *.o *.gch hello

debug: CFLAGS += -g
debug: all