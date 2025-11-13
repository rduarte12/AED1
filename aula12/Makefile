# Makefile para o projeto LinkedList

# Configurações do compilador
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = programa.exe
SRCDIR = .
OBJDIR = output

# Arquivos fonte e objeto
SOURCES = main.c LinkedList.c
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)

# Regra principal
all: $(OBJDIR) $(TARGET)

# Cria o diretório de saída se não existir (Windows)
$(OBJDIR):
	if not exist $(OBJDIR) mkdir $(OBJDIR)

# Compila o executável
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compila arquivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Executa o programa
run: $(TARGET)
	$(TARGET)

# Limpa arquivos compilados (Windows)
clean:
	if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
	if exist $(TARGET) del $(TARGET)

# Limpa apenas objetos
clean-obj:
	if exist $(OBJDIR) rmdir /s /q $(OBJDIR)

# Recompila tudo do zero
rebuild: clean all

# Mostra informações de debug
debug: CFLAGS += -DDEBUG
debug: $(TARGET)

# Compila com otimizações para release
release: CFLAGS += -O2 -DNDEBUG
release: clean $(TARGET)

# Verifica dependências
$(OBJDIR)/main.o: main.c LinkedList.h
$(OBJDIR)/LinkedList.o: LinkedList.c LinkedList.h

# Phony targets
.PHONY: all clean clean-obj run rebuild debug release

# Ajuda
help:
	@echo "Targets disponíveis:"
	@echo "  all      - Compila o projeto (padrão)"
	@echo "  run      - Executa o programa"
	@echo "  clean    - Remove todos os arquivos compilados"
	@echo "  clean-obj- Remove apenas os arquivos objeto"
	@echo "  rebuild  - Limpa e recompila tudo"
	@echo "  debug    - Compila com símbolos de debug"
	@echo "  release  - Compila otimizado para produção"
	@echo "  help     - Mostra esta ajuda"