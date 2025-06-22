CC = gcc

CFLAGS = -Wall -I.

TARGET = comprimir_app

SRCS = main.c comprimir_utilidades.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) *.pak *.gz

.PHONY: all clean