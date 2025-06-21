# Variables
CC = gcc
CFLAGS = -Wall -Wextra -O2
OBJ = main.o demonio.o
TARGET = proyect

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c demonio.h
demonio.o: demonio.c demonio.h

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean