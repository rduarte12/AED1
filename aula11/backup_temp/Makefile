# Detect OS
ifeq ($(OS),Windows_NT)
	EXE = .exe
else
	EXE =
endif

# Find all .c files in the current directory
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
TARGET := main$(EXE)

CC := gcc
CFLAGS := -Wall -O2

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

run:
	./$(TARGET)