# Configurações do compilador
CC = gcc
CFLAGS = -Wall -Isrc -pg -g
FLEX = flex
BISON = bison

# Diretórios
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
TEST_DIR = tests
TEST_FILES = $(wildcard $(TEST_DIR)/*.txt)

# Configuração do Valgrind
VALGRIND = valgrind
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

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

test: $(TARGET) check_dirs
	@echo "\n$(AZUL)$(ARROW) Iniciando testes...$(RESET)"
	@total=0; passed=0; failed=0; \
	for test in $(TEST_FILES); do \
		if [ ! -f $$test ]; then \
			echo "$(VERMELHO)Arquivo de teste não encontrado: $$test$(RESET)"; \
			continue; \
		fi; \
		total=$$((total + 1)); \
		echo "\n$(AMARELO)Executando teste: $$test$(RESET)"; \
		if $(VALGRIND) $(VALGRIND_FLAGS) ./$(TARGET) < $$test 2>$(BUILD_DIR)/valgrind.log; then \
			if ! grep -q "ERROR SUMMARY: 0 errors" $(BUILD_DIR)/valgrind.log; then \
				echo "$(VERMELHO)$(CROSS) Teste passou mas possui vazamento de memória!$(RESET)"; \
				failed=$$((failed + 1)); \
			else \
				echo "$(VERDE)$(CHECK) Teste passou!$(RESET)"; \
				passed=$$((passed + 1)); \
			fi; \
		else \
			echo "$(VERMELHO)$(CROSS) Teste falhou!$(RESET)"; \
			failed=$$((failed + 1)); \
		fi; \
	done; \
	echo "\n$(AZUL)Resumo dos Testes:$(RESET)"; \
	echo "$(VERDE)Testes Passaram: $$passed/$$total$(RESET)"; \
	echo "$(VERMELHO)Testes Falharam: $$failed/$$total$(RESET)"

test_single: $(TARGET) check_dirs
	@if [ -z "$(FILE)" ]; then \
		echo "$(VERMELHO)Erro: Especifique o arquivo de teste com FILE=<arquivo>$(RESET)"; \
		exit 1; \
	fi
	@if [ ! -f "$(FILE)" ]; then \
		echo "$(VERMELHO)Erro: Arquivo '$(FILE)' não encontrado$(RESET)"; \
		exit 1; \
	fi
	@echo "\n$(AMARELO)Executando teste: $(FILE)$(RESET)"
	@if $(VALGRIND) $(VALGRIND_FLAGS) ./$(TARGET) < $(FILE) 2>$(BUILD_DIR)/valgrind.log; then \
		if ! grep -q "ERROR SUMMARY: 0 errors" $(BUILD_DIR)/valgrind.log; then \
			echo "$(VERMELHO)$(CROSS) Teste passou mas possui vazamento de memória!$(RESET)"; \
			cat $(BUILD_DIR)/valgrind.log; \
		else \
			echo "$(VERDE)$(CHECK) Teste passou!$(RESET)"; \
		fi; \
	else \
		echo "$(VERMELHO)$(CROSS) Teste falhou!$(RESET)"; \
		cat $(BUILD_DIR)/valgrind.log; \
	fi

check_dirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(TEST_DIR)

clean:
	@echo "$(VERMELHO)$(CROSS)  Limpando diretórios de build e binários$(RESET)"
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BIN_DIR)
	@echo "$(VERDE)$(CHECK) Limpeza concluída$(RESET)"

.PHONY: all clean guia_uso run test test_single check_dirs
