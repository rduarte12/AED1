# Makefile para compilar main.c e Ponto.c
CC       := gcc
CFLAGS   := -std=c11 -Wextra -Wpedantic -O2
LDFLAGS  :=
LDLIBS   := -lm          # necessário para sqrt/sqrtf
TARGET   := main
OBJS     := main.o Ponto.o

.PHONY: all clean run

all:
	$(CC) main.c Ponto.c -o main -lm

run:
	./main
