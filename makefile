# Compilador e flags
CC = gcc
CFLAGS = -Wall

# Arquivos
FLEX_SOURCE = flex.l
COMPILER = compilador
GENERATED_C = lex.yy.c

# Regras
all: $(COMPILER)

$(COMPILER): $(GENERATED_C)
	$(CC) $(CFLAGS) -o $(COMPILER) $(GENERATED_C)

$(GENERATED_C): $(FLEX_SOURCE)
	flex $(FLEX_SOURCE)

clean:
	rm -f $(COMPILER) $(GENERATED_C)

test: $(COMPILER)
	./$(COMPILER) < test_compilador.txt

.PHONY: all clean test