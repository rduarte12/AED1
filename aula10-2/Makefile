CC = gcc
CFLAGS = -Wall -Wextra -g3
SRC = main.c Stack.c
OBJ = $(SRC:.c=.o)
EXEC = output/main.exe

all: $(EXEC)

$(EXEC): $(OBJ) | output
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c Stack.h
Stack.o: Stack.c Stack.h

output:
	mkdir -p output

run: $(EXEC)
	$(EXEC)

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all run clean