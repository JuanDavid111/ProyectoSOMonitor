# Variables
CC = gcc
CFLAGS = -Wall -Wextra -O2

OBJ = main.o demonio.o
TARGET = proyect
MONITOR = monitor

.PHONY: all clean run_all stop_all

all: $(TARGET) $(MONITOR)

# Compilar binario principal
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c demonio.h
demonio.o: demonio.c demonio.h

# Compilar prueba3 como ejecutable separado
$(MONITOR): monitor.c monitor.h
	$(CC) $(CFLAGS) -o $@ monitor.c

# Ejecutar ambos en paralelo
run_all: all
	@echo "Iniciando $(TARGET)..."
	./$(TARGET) &

	@echo "Iniciando $(MONITOR)..."
	./$(MONITOR) &

# Detener ambos si están corriendo
stop_all:
	@echo "Deteniendo $(TARGET) y $(MONITOR)..."
	-pkill -x $(TARGET)
	-pkill -x $(MONITOR)

clean:
	rm -f $(OBJ) $(TARGET) $(MONITOR)
