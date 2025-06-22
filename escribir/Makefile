CC = gcc

CFLAGS = -Wall -I.

TARGET = escribir_PID

SRCS = main.c utilidades_escribir.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) 29615514_29611486_30667176.txt

.PHONY: all clean