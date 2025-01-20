# Configurações do compilador
CC = gcc
CFLAGS = -Wall -Isrc -pg
FLEX = flex
BISON = bison

# Diretórios
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Arquivos fonte
FLEX_SRC = $(SRC_DIR)/flex.l
BISON_SRC = $(SRC_DIR)/bison.y
C_SRCS = $(SRC_DIR)/semantic.c $(SRC_DIR)/ast.c

# Arquivos gerados pelo Flex e Bison
FLEX_C = $(BUILD_DIR)/lex.yy.c
BISON_C = $(BUILD_DIR)/bison.tab.c
BISON_H = $(BUILD_DIR)/bison.tab.h

# Arquivos objeto
OBJS = $(FLEX_C:.c=.o) $(BISON_C:.c=.o) $(C_SRCS:.c=.o)

# Executável final
TARGET = $(BIN_DIR)/compilador

# Cores e ícones
VERDE = \033[1;32m
AZUL = \033[1;34m
AMARELO = \033[1;33m
VERMELHO = \033[1;31m
RESET = \033[0m
ARROW = ➤
CHECK = ✔
CROSS = ✘

all: $(TARGET) guia_uso

$(TARGET): $(OBJS)
	@echo "\n"
	@echo "$(VERDE)$(CHECK)  Ligando o executável: $(TARGET)$(RESET)"
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/lex.yy.o: $(FLEX_C)
	@echo "\n"
	@echo "$(AZUL)$(ARROW)  Compilando arquivo Flex: $<$(RESET)"
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/bison.tab.o: $(BISON_C)
	@echo "\n"
	@echo "$(AZUL)$(ARROW)  Compilando arquivo Bison: $<$(RESET)"
	$(CC) $(CFLAGS) -c -o $@ $<

$(FLEX_C): $(FLEX_SRC) $(BISON_H)
	@echo "\n"
	@echo "$(AMARELO)$(ARROW)  Gerando arquivo Flex: $@$(RESET)"
	@mkdir -p $(BUILD_DIR)
	$(FLEX) -o $@ $<

$(BISON_C) $(BISON_H): $(BISON_SRC)
	@echo "\n"
	@echo "$(AMARELO)$(ARROW)  Gerando arquivos Bison: $@ e $(BISON_H)$(RESET)"
	@mkdir -p $(BUILD_DIR)
	$(BISON) -d -o $(BISON_C) $<

%.o: %.c
	@echo "\n"
	@echo "$(AZUL)$(ARROW)  Compilando código C: $<$(RESET)"
	$(CC) $(CFLAGS) -c -o $@ $<

guia_uso:
	@echo "\n"
	@echo "$(AZUL)$(ARROW)  Tabela de Guia de Uso$(RESET)"
	@echo "$(VERDE)+----------------------+------------------------------------------+$(RESET)"
	@echo "$(VERDE)| Comando              | Descrição                                |$(RESET)"
	@echo "$(VERDE)+----------------------+------------------------------------------+$(RESET)"
	@echo "$(VERDE)| make                 | Compila o projeto e gera o executável    |$(RESET)"
	@echo "$(VERDE)| make clean           | Limpa os diretórios de build e binários  |$(RESET)"
	@echo "$(VERDE)| make run             | Executa o compilador após compilação     |$(RESET)"
	@echo "$(VERDE)| ./bin/compilador     | Executa o compilador gerado              |$(RESET)"
	@echo "$(VERDE)+----------------------+------------------------------------------+$(RESET)"
	@echo "\n"

run: $(TARGET)
	@echo "\n$(AZUL)$(ARROW)  Executando o compilador...$(RESET)"
	./bin/compilador
	
clean:
	@echo "$(VERMELHO)$(CROSS)  Limpando diretórios de build e binários$(RESET)"
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean guia_uso run 
