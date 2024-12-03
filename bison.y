/*******************************************************************************
 * Analisador Sintático - Compilador
 * 
 * Este arquivo implementa a análise sintática de uma linguagem de programação
 * simples usando Bison. A gramática suporta as seguintes estruturas:
 *
 * 1. ESTRUTURAS PRINCIPAIS:
 *    - Declarações de funções
 *    - Declarações de variáveis
 *    - Estruturas de controle (if, while)
 *    - Expressões aritméticas
 *    - Chamadas de função
 *    - Comandos de atribuição
 *
 * 2. REGRAS GRAMATICAIS PRINCIPAIS:
 *    programa        → declaracoes
 *    declaracoes     → declaracao | declaracoes declaracao
 *    declaracao      → declaracao_funcao | declaracao_variavel
 *    bloco           → { comandos }
 *    comando         → declaracao_variavel | atribuicao | comando_if | 
 *                      comando_while | comando_return | chamada_funcao
 *    expressao       → termo | expressao + termo | expressao - termo
 *
 * 3. TIPOS SUPORTADOS:
 *    - int:    números inteiros
 *    - float:  números de ponto flutuante
 *    - char:   caracteres
 *    - string: cadeias de caracteres
 *    - void:   tipo vazio (apenas para funções)
 *
 * 4. OPERADORES:
 *    Aritméticos: +, -, *, /
 *    Relacionais: ==, !=, <, >
 *    Atribuição:  =
 *
 * 5. EXEMPLO DE PROGRAMA VÁLIDO:
 *    int soma(int a, int b) {
 *        return a + b;
 *    }
 *
 *    void main() {
 *        int x = 10;
 *        int y = 20;
 *        int resultado;
 *        resultado = soma(x, y);
 *    }
 *
 * 6. INTEGRAÇÃO:
 *    Este analisador sintático trabalha em conjunto com o analisador léxico
 *    implementado em Flex (flex.l), recebendo os tokens gerados por ele.
 ******************************************************************************/

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

// Protótipos de funções
const char* tipoParaString(TipoVariavel tipo);
TipoVariavel verificarTipos(TipoVariavel tipo1, const char* operador, TipoVariavel tipo2);
void mostrarAnaliseGramatical(const char* regra);
void mostrarAnaliseTipos(const char* operacao, TipoVariavel tipo1, TipoVariavel tipo2, TipoVariavel resultado);
extern void analise_lexica(void);  

extern int linha;
extern int total_tokens;
void yyerror(const char *s);
int yylex(void);

%}

%union {
    struct {
        char* nome;
        TipoVariavel tipo;
    } id;
    TipoVariavel tipo;
}

%token <id> IDENTIFIER
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
    : declaracoes    { mostrarAnaliseGramatical("Programa → Declarações"); }
    ;

declaracoes
    : declaracao     { mostrarAnaliseGramatical("Declarações → Declaração"); }
    | declaracoes declaracao { mostrarAnaliseGramatical("Declarações → Declarações Declaração"); }
    ;

declaracao
    : declaracao_variavel { mostrarAnaliseGramatical("Declaração → Declaração Variável"); }
    | declaracao_funcao   { mostrarAnaliseGramatical("Declaração → Declaração Função"); }
    | comando            { mostrarAnaliseGramatical("Declaração → Comando"); }
    ;

declaracao_variavel
    : DECL_CREATE tipo IDENTIFIER DECL_AS expressao DELIM_END_STATEMENT
        {
            mostrarAnaliseGramatical("Declaração → create tipo id as expressão");
            printf("\n╔═════════════════ VERIFICAÇÃO DE TIPOS ═════════════════╗\n");
            printf("║ Variável: %-10s  Tipo Declarado: %-15s ║\n", 
                   $3.nome, 
                   tipoParaString($2));
            printf("║ Expressão retorna: %-35s ║\n", 
                   tipoParaString($5));
            if ($2 != $5) {
                printf("║ AVISO: Possível perda de precisão na atribuição      ║\n");
            }
            printf("╚═══════════════════════════════════════════════════════════╝\n");
        }
    | DECL_CREATE tipo IDENTIFIER DELIM_BRACKET_OPEN LITERAL_INT DELIM_BRACKET_CLOSE DECL_AS DECL_ARRAY DELIM_END_STATEMENT
        { mostrarAnaliseGramatical("Declaração Array → create tipo id[tamanho] as array;"); }
    ;

declaracao_funcao
    : DECL_FUNCTION tipo IDENTIFIER DELIM_PAREN_OPEN parametros DELIM_PAREN_CLOSE bloco
        { mostrarAnaliseGramatical("Declaração Função → function tipo id(parâmetros) bloco"); }
    | DECL_FUNCTION TYPE_VOID IDENTIFIER DELIM_PAREN_OPEN parametros DELIM_PAREN_CLOSE bloco
        { mostrarAnaliseGramatical("Declaração Função → function void id(parâmetros) bloco"); }
    ;

parametros
    : /* vazio */   { mostrarAnaliseGramatical("Parâmetros → vazio"); }
    | lista_parametros { mostrarAnaliseGramatical("Parâmetros → Lista de Parâmetros"); }
    ;

lista_parametros
    : parametro     { mostrarAnaliseGramatical("Lista Parâmetros → Parâmetro"); }
    | lista_parametros DELIM_SEPARATOR parametro
        { mostrarAnaliseGramatical("Lista Parâmetros → Lista Parâmetros, Parâmetro"); }
    ;

parametro
    : tipo IDENTIFIER { mostrarAnaliseGramatical("Parâmetro → Tipo Identificador"); }
    ;

tipo
    : TYPE_INT   { $$ = TIPO_INT; }
    | TYPE_FLT   { $$ = TIPO_FLOAT; }
    | TYPE_CHR   { $$ = TIPO_CHAR; }
    | TYPE_STR   { $$ = TIPO_STRING; }
    ;

comando
    : comando_check   { mostrarAnaliseGramatical("Comando → Check"); }
    | comando_repeat  { mostrarAnaliseGramatical("Comando → Repeat"); }
    | atribuicao     { mostrarAnaliseGramatical("Comando → Atribuição"); }
    | comando_give   { mostrarAnaliseGramatical("Comando → Give"); }
    | chamada_funcao DELIM_END_STATEMENT { mostrarAnaliseGramatical("Comando → Chamada Função;"); }
    ;

comando_check
    : CTRL_CHECK DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE CTRL_THEN bloco
        { mostrarAnaliseGramatical("Check → check (expressão) then bloco"); }
    | CTRL_CHECK DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE CTRL_THEN bloco CTRL_OTHERWISE bloco
        { mostrarAnaliseGramatical("Check → check (expressão) then bloco otherwise bloco"); }
    ;

comando_repeat
    : CTRL_REPEAT CTRL_WHILE DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE bloco
        { mostrarAnaliseGramatical("Repeat → repeat while (expressão) bloco"); }
    ;

comando_give
    : CTRL_GIVE CTRL_BACK expressao DELIM_END_STATEMENT
        { mostrarAnaliseGramatical("Give → give back expressão;"); }
    | CTRL_GIVE CTRL_BACK DELIM_END_STATEMENT
        { mostrarAnaliseGramatical("Give → give back;"); }
    ;

bloco
    : DELIM_BLOCK_OPEN comandos DELIM_BLOCK_CLOSE
        { mostrarAnaliseGramatical("Bloco → { comandos }"); }
    ;

comandos
    : /* vazio */    { mostrarAnaliseGramatical("Comandos → vazio"); }
    | comandos comando { mostrarAnaliseGramatical("Comandos → Comandos Comando"); }
    ;

atribuicao
    : IDENTIFIER OP_ASSIGN expressao DELIM_END_STATEMENT
        { mostrarAnaliseGramatical("Atribuição → id = expressão;"); }
    | IDENTIFIER OP_ADD_ASSIGN expressao DELIM_END_STATEMENT
        { mostrarAnaliseGramatical("Atribuição → id += expressão;"); }
    ;

expressao
    : termo
        { 
            mostrarAnaliseGramatical("Expressão → Termo");
            $$ = $1;
        }
    | expressao OP_ADD termo
        { 
            mostrarAnaliseGramatical("Expressão → Expressão plus Termo");
            $$ = verificarTipos($1, "plus", $3);
        }
    | expressao OP_SUB termo
        { 
            mostrarAnaliseGramatical("Expressão → Expressão minus Termo");
            $$ = verificarTipos($1, "minus", $3);
        }
    | expressao OP_EQ termo  { mostrarAnaliseGramatical("Expressão → Expressão equals Termo"); }
    | expressao OP_NE termo  { mostrarAnaliseGramatical("Expressão → Expressão not_equals Termo"); }
    | expressao OP_LT termo  { mostrarAnaliseGramatical("Expressão → Expressão is_less_than Termo"); }
    | expressao OP_GT termo  { mostrarAnaliseGramatical("Expressão → Expressão is_greater_than Termo"); }
    ;

termo
    : fator
        { 
            $$ = $1;
        }
    | termo OP_MUL fator
        { 
            $$ = verificarTipos($1, "times", $3);
        }
    | termo OP_DIV fator
        { 
            $$ = verificarTipos($1, "divided_by", $3);
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

lista_argumentos
    : expressao     { mostrarAnaliseGramatical("Lista Argumentos → Expressão"); }
    | lista_argumentos DELIM_SEPARATOR expressao
        { mostrarAnaliseGramatical("Lista Argumentos → Lista Argumentos, Expressão"); }
    ;

%%

// Implementação das funções
const char* tipoParaString(TipoVariavel tipo) {
    switch(tipo) {
        case TIPO_INT: return "int";
        case TIPO_FLOAT: return "float";
        case TIPO_CHAR: return "char";
        case TIPO_STRING: return "string";
        case TIPO_VOID: return "void";
        default: return "erro";
    }
}

void mostrarAnaliseTipos(const char* operacao, TipoVariavel tipo1, TipoVariavel tipo2, TipoVariavel resultado) {
    printf("║ Análise de Tipos: %-15s %-6s %s %-6s = %-6s ║\n",
           operacao,
           tipoParaString(tipo1),
           operacao,
           tipoParaString(tipo2),
           tipoParaString(resultado));
}

TipoVariavel verificarTipos(TipoVariavel tipo1, const char* operador, TipoVariavel tipo2) {
    printf("\n╔════════════════════ ANÁLISE DE TIPOS ════════════════════╗\n");
    
    if (tipo1 == TIPO_INT && tipo2 == TIPO_INT) {
        if (strcmp(operador, "plus") == 0) {
            mostrarAnaliseTipos("Adição", tipo1, tipo2, TIPO_INT);
            return TIPO_INT;
        }
    }
    else if (tipo1 == TIPO_FLOAT || tipo2 == TIPO_FLOAT) {
        if (strcmp(operador, "plus") == 0) {
            mostrarAnaliseTipos("Adição", tipo1, tipo2, TIPO_FLOAT);
            return TIPO_FLOAT;
        }
    }
    
    printf("║ ERRO: Tipos incompatíveis para operação %-20s ║\n", operador);
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    return TIPO_ERRO;
}

void mostrarAnaliseGramatical(const char* regra) {
    printf("║ Regra: %-53s ║\n", regra);
}

void yyerror(const char *s) {
    printf("\n╔══════════════════════ ERRO SINTÁTICO ══════════════════════╗\n");
    printf("║ Linha: %-52d ║\n", linha);
    printf("║ Erro:  %-52s ║\n", s);
    printf("║                                                             ║\n");
    printf("║ Contexto do Erro:                                          ║\n");
    printf("║ - Verificar tipos dos operandos                           ║\n");
    printf("║ - Verificar sintaxe da expressão                          ║\n");
    printf("║ - Verificar declaração de variáveis                       ║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n");
}

int main(void) {
    printf("\n╔════════════════════ COMPILADOR C-2024 ════════════════════╗\n");
    printf("║                                                           ║\n");
    if (getenv("ANALISE_LEXICA")) {
        printf("║              Iniciando Análise Léxica                   ║\n");
        printf("║                                                           ║\n");
        printf("╚═══════════════════════════════════════════════════════════╝\n\n");
        analise_lexica();
        return 0;
    } else {
        printf("║              Iniciando Análise Sintática                 ║\n");
        printf("║                                                           ║\n");
        printf("╚═══════════════════════════════════════════════════════════╝\n\n");
        return yyparse();
    }
}