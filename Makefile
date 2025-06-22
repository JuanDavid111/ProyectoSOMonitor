CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = main.o prueba4.o empaquetador.o

all: programa

programa: $(OBJ)
	$(CC) $(CFLAGS) -o programa $(OBJ)

main.o: main.c prueba4.h
	$(CC) $(CFLAGS) -c main.c

prueba4.o: prueba4.c prueba4.h empaquetador.h
	$(CC) $(CFLAGS) -c prueba4.c

empaquetador.o: empaquetador.c empaquetador.h
	$(CC) $(CFLAGS) -c empaquetador.c

clean:
	rm -f *.o programa
