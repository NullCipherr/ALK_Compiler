CC=gcc
CFLAGS=-Wall

COMPILER=compilador
BISON_FILE=bison.y
FLEX_FILE=flex.l

all: $(COMPILER)

$(COMPILER): lex.yy.c bison.tab.c types.h
	$(CC) $(CFLAGS) -o $(COMPILER) lex.yy.c bison.tab.c

lex.yy.c: $(FLEX_FILE) bison.tab.h
	flex $(FLEX_FILE)

bison.tab.c bison.tab.h: $(BISON_FILE)
	bison -d $(BISON_FILE)

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

clean:
	rm -f $(COMPILER) lex.yy.c bison.tab.c bison.tab.h