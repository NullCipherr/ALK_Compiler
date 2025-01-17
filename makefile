CC = gcc
CFLAGS = -Wall -Isrc

# Diretórios
BIN_DIR = bin
SRC_DIR = src
BUILD_DIR = build
TESTS_DIR = tests

# Arquivos principais
COMPILER = $(BIN_DIR)/compilador
BISON_FILE = $(SRC_DIR)/bison.y
FLEX_FILE = $(SRC_DIR)/flex.l
SEMANTIC_FILE = $(SRC_DIR)/semantic.c

# Lista de objetos necessários
OBJS = $(BUILD_DIR)/lex.yy.o $(BUILD_DIR)/bison.tab.o $(BUILD_DIR)/semantic.o

# Regra principal para criar os diretórios e o compilador
all: $(BIN_DIR) $(BUILD_DIR) $(COMPILER)

# Criação do diretório bin
$(BIN_DIR):
	mkdir -p $@

# Criação do diretório build
$(BUILD_DIR):
	mkdir -p $@

# Regra principal para criar o compilador
$(COMPILER): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Regra para criar o objeto do analisador léxico
$(BUILD_DIR)/lex.yy.o: $(BUILD_DIR)/lex.yy.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para criar o objeto do analisador sintático
$(BUILD_DIR)/bison.tab.o: $(BUILD_DIR)/bison.tab.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para criar o objeto do analisador semântico
$(BUILD_DIR)/semantic.o: $(SEMANTIC_FILE) $(SRC_DIR)/semantic.h
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para gerar o código do flex
$(BUILD_DIR)/lex.yy.c: $(FLEX_FILE) $(BUILD_DIR)/bison.tab.h
	flex -o $@ $<

# Regra para gerar o código do bison
$(BUILD_DIR)/bison.tab.c $(BUILD_DIR)/bison.tab.h: $(BISON_FILE)
	bison -v -d -o $(BUILD_DIR)/bison.tab.c $(BISON_FILE)

# Limpeza
clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)
	@echo "Todos os arquivos gerados foram removidos."