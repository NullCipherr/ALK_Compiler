%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

// Definição da estrutura para representar a árvore
typedef struct Nodo {
    char* nome;              // Nome do nó (regra sintática)
    struct Nodo** filhos;    // Array de filhos (subárvores)
    int num_filhos;          // Número de filhos
} Nodo;

// Protótipos de funções
const char* tipoParaString(TipoVariavel tipo);
TipoVariavel verificarTipos(TipoVariavel tipo1, const char* operador, TipoVariavel tipo2);
void mostrarAnaliseGramatical(const char* regra);
void mostrarAnaliseTipos(const char* operacao, TipoVariavel tipo1, TipoVariavel tipo2, TipoVariavel resultado);
extern void analise_lexica(void);  

extern int linha;
extern int total_tokens;
extern char* yytext;
void yyerror(const char *s);
int yylex(void);

// Função para criar um novo nodo
Nodo* criarNodo(char* nome, int num_filhos) {
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->nome = nome;
    nodo->num_filhos = num_filhos;
    nodo->filhos = (Nodo**)malloc(num_filhos * sizeof(Nodo*));  // Alocação para os filhos
    return nodo;
}

// Função para exibir a árvore sintática
void exibirArvore(Nodo* nodo, int nivel) {
    if (nodo == NULL) return;
    
    // Exibe o nome do nodo com indentação
    for (int i = 0; i < nivel; i++) {
        printf("  ");  // Indenta
    }
    printf("%s\n", nodo->nome);
    
    // Recursivamente exibe os filhos do nodo
    for (int i = 0; i < nodo->num_filhos; i++) {
        exibirArvore(nodo->filhos[i], nivel + 1);
    }
}

%}

%union {
    struct Nodo* nodo;
    char* texto;  // Para tipos de texto como identificadores
    TipoVariavel tipo;  // Para tipos de variáveis
}

%token <texto> IDENTIFIER
%token <tipo> TYPE_INT TYPE_FLT TYPE_CHR TYPE_STR TYPE_VOID
%token DECL_CREATE DECL_AS DECL_ARRAY DECL_FUNCTION
%token CTRL_CHECK CTRL_THEN CTRL_OTHERWISE CTRL_REPEAT CTRL_WHILE
%token CTRL_GIVE CTRL_BACK
%token OP_ADD OP_SUB OP_MUL OP_DIV
%token OP_ASSIGN OP_ADD_ASSIGN
%token OP_EQ OP_NE OP_LT OP_GT
%token DELIM_PAREN_OPEN DELIM_PAREN_CLOSE 
%token DELIM_BRACKET_OPEN DELIM_BRACKET_CLOSE
%token DELIM_BLOCK_OPEN DELIM_BLOCK_CLOSE
%token DELIM_END_STATEMENT DELIM_SEPARATOR
%token LITERAL_INT LITERAL_FLT LITERAL_CHR LITERAL_STR

%type <tipo> expressao termo fator tipo

%%

programa
    : declaracoes {
        Nodo* nodo = criarNodo("Programa", 1);
        nodo->filhos[0] = $1;  // Declarações
        exibirArvore(nodo, 0);
        liberarArvore(nodo);
    }
    ;

declaracoes
    : declaracao {
        Nodo* nodo = criarNodo("Declaração", 1);
        nodo->filhos[0] = $1;
        $$ = nodo;
    }
    | declaracoes declaracao {
        Nodo* nodo = criarNodo("Declarações", 2);
        nodo->filhos[0] = $1;
        nodo->filhos[1] = $2;
        $$ = nodo;
    }
    ;

declaracao
    : declaracao_variavel {
        Nodo* nodo = criarNodo("Declaração Variável", 1);
        nodo->filhos[0] = $1;
        $$ = nodo;
    }
    | declaracao_funcao {
        Nodo* nodo = criarNodo("Declaração Função", 1);
        nodo->filhos[0] = $1;
        $$ = nodo;
    }
    | comando {
        Nodo* nodo = criarNodo("Comando", 1);
        nodo->filhos[0] = $1;
        $$ = nodo;
    }
    ;

declaracao_variavel
    : DECL_CREATE tipo IDENTIFIER DECL_AS expressao DELIM_END_STATEMENT {
        Nodo* nodo = criarNodo("Declaração Variável", 3);
        nodo->filhos[0] = $2;  // Tipo
        nodo->filhos[1] = $3;  // Identificador
        nodo->filhos[2] = $5;  // Expressão
        $$ = nodo;
    }
    | DECL_CREATE tipo IDENTIFIER DELIM_BRACKET_OPEN LITERAL_INT DELIM_BRACKET_CLOSE DECL_AS DECL_ARRAY DELIM_END_STATEMENT {
        Nodo* nodo = criarNodo("Declaração Array", 4);
        nodo->filhos[0] = $2;  // Tipo
        nodo->filhos[1] = $3;  // Identificador
        nodo->filhos[2] = $5;  // Tamanho do array
        $$ = nodo;
    }
    ;

declaracao_funcao
    : DECL_FUNCTION tipo IDENTIFIER DELIM_PAREN_OPEN parametros DELIM_PAREN_CLOSE bloco {
        Nodo* nodo = criarNodo("Declaração Função", 4);
        nodo->filhos[0] = $2;  // Tipo
        nodo->filhos[1] = $3;  // Identificador
        nodo->filhos[2] = $4;  // Parâmetros
        nodo->filhos[3] = $6;  // Bloco
        $$ = nodo;
    }
    | DECL_FUNCTION TYPE_VOID IDENTIFIER DELIM_PAREN_OPEN parametros DELIM_PAREN_CLOSE bloco {
        Nodo* nodo = criarNodo("Declaração Função", 4);
        nodo->filhos[0] = $2;  // Tipo
        nodo->filhos[1] = $3;  // Identificador
        nodo->filhos[2] = $4;  // Parâmetros
        nodo->filhos[3] = $6;  // Bloco
        $$ = nodo;
    }
    ;

parametros
    : /* vazio */ {
        Nodo* nodo = criarNodo("Parâmetros", 0);
        $$ = nodo;
    }
    | lista_parametros {
        Nodo* nodo = criarNodo("Lista de Parâmetros", 1);
        nodo->filhos[0] = $1;
        $$ = nodo;
    }
    ;

lista_parametros
    : parametro {
        Nodo* nodo = criarNodo("Parâmetro", 1);
        nodo->filhos[0] = $1;
        $$ = nodo;
    }
    | lista_parametros DELIM_SEPARATOR parametro {
        Nodo* nodo = criarNodo("Lista de Parâmetros", 2);
        nodo->filhos[0] = $1;
        nodo->filhos[1] = $3;
        $$ = nodo;
    }
    ;

parametro
    : tipo IDENTIFIER {
        Nodo* nodo = criarNodo("Parâmetro", 2);
        nodo->filhos[0] = $1;  // Tipo
        nodo->filhos[1] = $2;  // Identificador
        $$ = nodo;
    }
    ;

tipo
    : TYPE_INT {
        Nodo* nodo = criarNodo("Tipo", 0);
        $$ = nodo;
    }
    | TYPE_FLT {
        Nodo* nodo = criarNodo("Tipo", 0);
        $$ = nodo;
    }
    | TYPE_CHR {
        Nodo* nodo = criarNodo("Tipo", 0);
        $$ = nodo;
    }
    | TYPE_STR {
        Nodo* nodo = criarNodo("Tipo", 0);
        $$ = nodo;
    }
    ;

comando
    : comando_check {
        Nodo* nodo = criarNodo("Comando Check", 1);
        nodo->filhos[0] = $1;
        $$ = nodo;
    }
    | comando_repeat {
        Nodo* nodo = criarNodo("Comando Repeat", 1);
        nodo->filhos[0] = $1;
        $$ = nodo;
    }
    | atribuicao {
        Nodo* nodo = criarNodo("Comando Atribuição", 1);
        nodo->filhos[0] = $1;
        $$ = nodo;
    }
    | comando_give {
        Nodo* nodo = criarNodo("Comando Give", 1);
        nodo->filhos[0] = $1;
        $$ = nodo;
    }
    | chamada_funcao DELIM_END_STATEMENT {
        Nodo* nodo = criarNodo("Chamada Função", 1);
        nodo->filhos[0] = $1;
        $$ = nodo;
    }
    ;

comando_check
    : CTRL_CHECK DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE CTRL_THEN bloco {
        Nodo* nodo = criarNodo("Check", 3);
        nodo->filhos[0] = $3;  // Expressão
        nodo->filhos[1] = $5;  // Bloco
        $$ = nodo;
    }
    | CTRL_CHECK DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE CTRL_THEN bloco CTRL_OTHERWISE bloco {
        Nodo* nodo = criarNodo("Check com Else", 4);
        nodo->filhos[0] = $3;  // Expressão
        nodo->filhos[1] = $5;  // Bloco Then
        nodo->filhos[2] = $7;  // Bloco Otherwise
        $$ = nodo;
    }
    ;

comando_repeat
    : CTRL_REPEAT CTRL_WHILE DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE bloco {
        Nodo* nodo = criarNodo("Repeat While", 3);
        nodo->filhos[0] = $3;  // Expressão
        nodo->filhos[1] = $5;  // Bloco
        $$ = nodo;
    }
    ;

comando_give
    : CTRL_GIVE CTRL_BACK expressao DELIM_END_STATEMENT {
        Nodo* nodo = criarNodo("Give Back", 1);
        nodo->filhos[0] = $3;  // Expressão
        $$ = nodo;
    }
    | CTRL_GIVE CTRL_BACK DELIM_END_STATEMENT {
        Nodo* nodo = criarNodo("Give Back (sem expressão)", 0);
        $$ = nodo;
    }
    ;

bloco
    : DELIM_BLOCK_OPEN comandos DELIM_BLOCK_CLOSE {
        Nodo* nodo = criarNodo("Bloco", 1);
        nodo->filhos[0] = $2;  // Comandos dentro do bloco
        $$ = nodo;
    }
    ;

comandos
    : comando {
        Nodo* nodo = criarNodo("Comando", 1);
        nodo->filhos[0] = $1;
        $$ = nodo;
    }
    | comandos comando {
        Nodo* nodo = criarNodo("Comandos", 2);
        nodo->filhos[0] = $1;
        nodo->filhos[1] = $2;
        $$ = nodo;
    }
    ;

atribuicao
    : IDENTIFIER OP_ASSIGN expressao DELIM_END_STATEMENT {
        Nodo* nodo = criarNodo("Atribuição", 2);
        nodo->filhos[0] = $1;  // Identificador
        nodo->filhos[1] = $3;  // Expressão
        $$ = nodo;
    }
    ;

expressao
    : termo {
        $$ = $1;
    }
    | expressao OP_ADD termo {
        $$ = $1;  // Expressão somada ao termo
    }
    | expressao OP_SUB termo {
        $$ = $1;  // Expressão subtraída pelo termo
    }
    ;

termo
    : fator {
        $$ = $1;
    }
    | termo OP_MUL fator {
        $$ = $1;  // Termo multiplicado pelo fator
    }
    | termo OP_DIV fator {
        $$ = $1;  // Termo dividido pelo fator
    }
    ;

fator
    : IDENTIFIER
        { 
            $$ = $1.tipo;
        }
    | LITERAL_INT
        { 
            $$ = TIPO_INT;
        }
    | LITERAL_FLT
        { 
            $$ = TIPO_FLOAT;
        }
    | LITERAL_CHR
        { 
            $$ = TIPO_CHAR;
        }
    | LITERAL_STR
        { 
            $$ = TIPO_STRING;
        }
    | DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE
        { mostrarAnaliseGramatical("Fator → (Expressão)"); }
    | chamada_funcao { mostrarAnaliseGramatical("Fator → Chamada Função"); }
    ;
    
chamada_funcao
    : IDENTIFIER DELIM_PAREN_OPEN argumentos DELIM_PAREN_CLOSE
        { mostrarAnaliseGramatical("Chamada Função → id(Argumentos)"); }
    ;
argumentos
    : /* vazio */   { mostrarAnaliseGramatical("Argumentos → vazio"); }
    | lista_argumentos { mostrarAnaliseGramatical("Argumentos → Lista de Argumentos"); }
    ;
chamada_funcao
    : IDENTIFIER DELIM_PAREN_OPEN argumentos DELIM_PAREN_CLOSE
        { mostrarAnaliseGramatical("Chamada Função → id(Argumentos)"); }
    ;
lista_argumentos
    : expressao     { mostrarAnaliseGramatical("Lista Argumentos → Expressão"); }
    | lista_argumentos DELIM_SEPARATOR expressao
        { mostrarAnaliseGramatical("Lista Argumentos → Lista Argumentos, Expressão"); }
    ;
%%

// Implementação das funções auxiliares
void yyerror(const char *s) {
    fprintf(stderr, "Erro: %s\n", s);
}

int yylex(void) {
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

// Função para liberar memória de uma árvore
void liberarArvore(Nodo* nodo) {
    if (nodo == NULL) return;
    for (int i = 0; i < nodo->num_filhos; i++) {
        liberarArvore(nodo->filhos[i]);
    }
    free(nodo->filhos);
    free(nodo);
}

// Função para exibir a análise gramatical
void mostrarAnaliseGramatical(const char* regra) {
    printf("Analisando a regra: %s\n", regra);
}

// Função para exibir a análise de tipos
void mostrarAnaliseTipos(const char* operacao, TipoVariavel tipo1, TipoVariavel tipo2, TipoVariavel resultado) {
    printf("Operação: %s\n", operacao);
    printf("Tipo 1: %s\n", tipoParaString(tipo1));
    printf("Tipo 2: %s\n", tipoParaString(tipo2));
    printf("Resultado: %s\n", tipoParaString(resultado));
}

// Função para converter tipo para string
const char* tipoParaString(TipoVariavel tipo) {
    switch (tipo) {
        case TIPO_INT: return "Inteiro";
        case TIPO_FLT: return "Flutuante";
        case TIPO_CHR: return "Caractere";
        case TIPO_STR: return "String";
        case TIPO_VOID: return "Vazio";
        default: return "Desconhecido";
    }
}

// Função para verificar se os tipos são compatíveis
TipoVariavel verificarTipos(TipoVariavel tipo1, const char* operador, TipoVariavel tipo2) {
    // Simples exemplo de verificação para operações aritméticas
    if (operador == NULL) return tipo1;  // Se não há operador, retornamos o tipo 1 (atribuição)
    
    if (strcmp(operador, "+") == 0 || strcmp(operador, "-") == 0 || strcmp(operador, "*") == 0 || strcmp(operador, "/") == 0) {
        // Operações aritméticas: só permitem tipos numéricos
        if (tipo1 == TIPO_INT || tipo1 == TIPO_FLT) {
            if (tipo2 == TIPO_INT || tipo2 == TIPO_FLT) {
                // Se ambos os tipos são válidos, podemos realizar a operação
                return (tipo1 == TIPO_FLT || tipo2 == TIPO_FLT) ? TIPO_FLT : TIPO_INT;
            }
        }
    } else if (strcmp(operador, "=") == 0) {
        // Operação de atribuição
        if (tipo1 == tipo2) {
            return tipo1;  // Tipos devem ser compatíveis
        }
    }
    
    // Se nenhum caso for atendido, retorno um tipo desconhecido
    return TIPO_VOID;
}

// Função de erro lexicamente
void yyerror(const char* s) {
    fprintf(stderr, "Erro: %s\n", s);
}

int yylex(void) {
    // Esta função é gerada automaticamente pelo flex.
    return 0;  // Placeholder, já que a análise lexical é feita pelo flex
}

int main() {
    // Exemplo de código que invoca o parser gerado pelo Bison
    printf("Iniciando análise...\n");
    
    yyparse();  // Função gerada pelo Bison para análise sintática

    printf("Análise concluída!\n");
    return 0;
}