CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJ = main.o monitor.o empaquetador.o
TARGET = monitor

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c monitor.h empaquetador.h

monitor.o: monitor.c monitor.h empaquetador.h

empaquetador.o: empaquetador.c empaquetador.h

clean:
	rm -f *.o $(TARGET)

