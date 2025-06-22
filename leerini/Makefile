CC = gcc

CFLAGS = -Wall -I.

LDFLAGS =

SRCS = main.c utilidades_config.c

OBJS = $(SRCS:.c=.o)

TARGET = proy1_daemon

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean