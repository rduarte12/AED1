CC = gcc
CFLAGS = -Wall
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXEC = main

all:
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

run:
	./$(EXEC)

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all run clean