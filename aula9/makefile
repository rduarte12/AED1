

CC = gcc
CFLAGS =
OBJ = main.o LSD.o
TARGET = main.exe

# Compilação: apenas o comando de compilação
all:
	$(CC) $(CFLAGS) -o $(TARGET) main.c LSD.c

# Execução: apenas o comando de execução
run:
	./$(TARGET)

clean:
	del /Q *.o *.exe 2>NUL || rm -f *.o $(TARGET)

.PHONY: all run clean
