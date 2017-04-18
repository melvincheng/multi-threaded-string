.PHONY: all clean

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -fopenmp
SOURCES = char_count.c
OBJECTS = $(subst .c,.o,$(SOURCES))
BIN = char_count

char_count: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

all: $(BIN)

clean:
	rm -f $(OBJECTS) $(BIN) 