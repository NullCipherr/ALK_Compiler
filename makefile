# Configurações do compilador
CC = gcc
CFLAGS = -Wall -Isrc -pg
FLEX = flex
BISON = bison

# Diretórios
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Diretórios de Testes
TEST_DIR = tests
TEST_FILES = $(wildcard $(TEST_DIR)/*.txt)

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
	@echo "$(VERDE)| make test            | Executa todos os testes do diretório     |$(RESET)"
	@echo "$(VERDE)| make test_single txt | Executa um teste específico              |$(RESET)"
	@echo "$(VERDE)| ./bin/compilador     | Executa o compilador gerado              |$(RESET)"
	@echo "$(VERDE)+----------------------+------------------------------------------+$(RESET)"
	@echo "\n"

run: $(TARGET)
	@echo "\n$(AZUL)$(ARROW)  Executando o compilador...$(RESET)"
	./bin/compilador

test: $(TARGET)
	@echo "\n$(AZUL)$(ARROW) Iniciando testes...$(RESET)"
	@mkdir -p $(TEST_DIR)
	@total=0; passed=0; \
    for test in $(TEST_FILES); do \
        total=$$((total + 1)); \
        echo "\n$(AMARELO)Executando teste: $$test$(RESET)"; \
        if ./$(TARGET) < $$test; then \
            echo "$(VERDE)$(CHECK) Teste passou!$(RESET)"; \
            passed=$$((passed + 1)); \
        else \
            echo "$(VERMELHO)$(CROSS) Teste falhou!$(RESET)"; \
        fi; \
    done; \
    echo "\n$(AZUL)Resumo dos Testes:$(RESET)"; \
    echo "$(VERDE)Testes Passaram: $$passed/$$total$(RESET)"

test_single: $(TARGET)
	@if [ -z "$(FILE)" ]; then \
    	echo "$(VERMELHO)Erro: Especifique o arquivo de teste com FILE=<arquivo>$(RESET)"; \
    	exit 1; \
    fi
	@echo "\n$(AMARELO)Executando teste: $(FILE)$(RESET)"
	@if ./$(TARGET) < $(FILE); then \
        echo "$(VERDE)$(CHECK) Teste passou!$(RESET)"; \
    else \
        echo "$(VERMELHO)$(CROSS) Teste falhou!$(RESET)"; \
    fi

clean:
	@echo "$(VERMELHO)$(CROSS)  Limpando diretórios de build e binários$(RESET)"
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BIN_DIR)
	@echo "$(VERDE)$(CHECK) Limpeza concluída$(RESET)"

.PHONY: all clean guia_uso run test test_single
