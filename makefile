CC=gcc
CFLAGS=-Wall

COMPILER=compilador
BISON_FILE=bison.y
FLEX_FILE=flex.l
SEMANTIC_FILE=semantic.c

# Lista de objetos necessários
OBJS=lex.yy.o bison.tab.o semantic.o

all: $(COMPILER)

# Regra principal para criar o compilador
$(COMPILER): $(OBJS)
	$(CC) $(CFLAGS) -o $(COMPILER) $(OBJS)

# Regra para criar o objeto do analisador léxico
lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

# Regra para criar o objeto do analisador sintático
bison.tab.o: bison.tab.c
	$(CC) $(CFLAGS) -c bison.tab.c

# Regra para criar o objeto do analisador semântico
semantic.o: $(SEMANTIC_FILE) semantic.h
	$(CC) $(CFLAGS) -c $(SEMANTIC_FILE)

# Regra para gerar o código do flex
lex.yy.c: $(FLEX_FILE) bison.tab.h
	flex $(FLEX_FILE)

# Regra para gerar o código do bison
bison.tab.c bison.tab.h: $(BISON_FILE)
	bison -v -d $(BISON_FILE)

# Regras de teste
test-lex: $(COMPILER)
	@echo "\n=== Executando teste léxico ==="
	@echo "Arquivo de entrada: test_code.txt"
	@echo "----------------------------------------"
	ANALISE_LEXICA=1 ./$(COMPILER) < test_code.txt

test-bison: $(COMPILER)
	@echo "\n=== Executando teste sintático ==="
	@echo "Arquivo de entrada: test_code.txt"
	@echo "----------------------------------------"
	./$(COMPILER) < test_code.txt

test-semantic: $(COMPILER)
	@echo "\n=== Executando teste semântico ==="
	@echo "Arquivo de entrada: test_code.txt"
	@echo "----------------------------------------"
	ANALISE_SEMANTICA=1 ./$(COMPILER) < test_code.txt

test-all: $(COMPILER)
	@echo "\n=== Executando todos os testes ==="
	@for teste in testes/teste_*.txt; do \
		echo "\nTestando $$teste:"; \
		echo "----------------------------------------"; \
		./$(COMPILER) < $$teste; \
	done

tree: bison.tab.c
	@echo "\n=== Gerando árvore sintática ==="
	@echo "Árvore gerada em bison.output"
	cat bison.output

# Limpeza
clean:
	rm -f $(COMPILER) $(OBJS) lex.yy.c bison.tab.c bison.tab.h bison.output