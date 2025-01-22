/*
 * Trabalho Prático – Parte 1
 * Disciplina: Compiladores
 * Aluno: Andrei Costa, Kananda Caroline, Leonardo Ribeiro Goulart
 *
 * Especificação: Implementação da análise léxica para um compilador de uma
 * linguagem personalizada. Esta etapa reconhece os seguintes elementos:
 *
 * 1. **Tipos de Variáveis**:
 *    - Implementado: Reconhece os tipos "int", "float", "char" e "string" como palavras reservadas.
 *      Tokens: TYPE_INT, TYPE_FLT, TYPE_CHR, TYPE_STR.
 *    - Implementado: Reconhece literais associados a esses tipos:
 *      - Literais inteiros (e.g., "123") com o token LITERAL_INT.
 *      - Literais float (e.g., "123.45") com o token LITERAL_FLT.
 *      - Literais char (e.g., "'a'") com o token LITERAL_CHR.
 *      - Literais string (e.g., "\"Hello\"") com o token LITERAL_STR.
 *
 * 2. **Vetores**:
 *    - Implementado: Reconhece e manipula vetores utilizando o token "array".
 *      Token: DECL_ARRAY.
 *
 * 3. **Estruturas de Decisão**:
 *    - Implementado: Reconhece estruturas de decisão básicas com os tokens:
 *      - CTRL_CHECK ("check") para a condição.
 *      - CTRL_THEN ("then") para o bloco de execução.
 *
 * 4. **Estruturas de Repetição**:
 *    - Implementado: Reconhece estruturas de repetição com os tokens:
 *      - CTRL_REPEAT ("repeat") para laços do tipo "repita".
 *      - CTRL_WHILE ("while") para laços condicionais.
 *
 * 5. **Palavras e Funções Reservadas**:
 *    - Implementado: Reconhece palavras reservadas associadas à declaração e manipulação de variáveis e funções:
 *      - DECL_CREATE ("create"), DECL_AS ("as"), DECL_FUNCTION ("function").
 *    - Implementado: Reconhece funções nativas como:
 *      - BUILT_IN_PRINT ("print") e BUILT_IN_SCAN ("scan").
 *    - Implementado: Reconhece operadores, delimitadores e outras palavras reservadas para construção do programa:
 *      - Operadores: OP_ADD ("plus"), OP_SUB ("minus"), OP_MUL ("times"), OP_DIV ("divided_by"), OP_ASSIGN ("="), etc.
 *      - Delimitadores: DELIM_PAREN_OPEN ("("), DELIM_PAREN_CLOSE (")"), DELIM_BLOCK_OPEN ("{"), DELIM_BLOCK_CLOSE ("}"), etc.
 *
 * 6. **Chamadas de Sub-rotinas**:
 *    - Implementado: Reconhece funções definidas pelo usuário com o token DECL_FUNCTION.
 *      Exemplo: "function" seguido por um identificador.
 *
 * Observação:
 * Este arquivo implementa apenas a análise léxica. As próximas etapas do compilador (análise sintática e semântica) 
 * deverão expandir esta base para maior funcionalidade.
 */


%{
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "bison.tab.h"

int linha = 1;
int coluna = 1;
int total_tokens = 0;

// Protótipo de yylex
int yylex(void);

void emitToken(const char* token, const char* lexema) 
{
    total_tokens++;
    if (total_tokens == 1) {
        printf("\n╔════════════════════════════════╦════════════════════════════════╦════════════════════════════════╗\n");
        printf("║ TOKEN                          ║ LINHA                          ║ LEXEMA                         ║\n");
        printf("╠════════════════════════════════╬════════════════════════════════╬════════════════════════════════╣\n");
    }
    
    // Trunca os valores de TOKEN e LEXEMA para evitar que ultrapassem os limites
    char token_truncado[31];
    char lexema_truncado[31];
    strncpy(token_truncado, token, 30);
    strncpy(lexema_truncado, lexema, 30);
    token_truncado[30] = '\0';
    lexema_truncado[30] = '\0';

    // Linha da tabela
    printf("║ %-30s ║ %-30d ║ %-30s ║\n", token_truncado, linha, lexema_truncado);
}

// Implementação da função analise_lexica
void analise_lexica(void) {
    while (yylex() != 0) {
        // O processamento é feito dentro de emitToken
    }
    if (total_tokens > 0) {
        printf("╠════════════════════════════════╩════════════════════════════════╩════════════════════════════════╣\n");
        printf("║ Total de tokens processados: %-67d ║\n", total_tokens);
        printf("╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n\n");
    }
}
%}

%option noinput
%option nounput

DIGITO      [0-9]
LETRA       [a-zA-Z]
ID          {LETRA}({LETRA}|{DIGITO}|"_")*
INTEIRO     {DIGITO}+
FLOAT       {DIGITO}+"."{DIGITO}+
CHAR        '.'
STRING      \"[^\"]*\"
ESPACO      [ \t\r]
COMENTARIO  "//".*

%%

{ESPACO}    { coluna += yyleng; }
\n          { linha++; coluna = 1; }
{COMENTARIO} { /* Ignora comentários */ }

"create"    { emitToken("DECL_CREATE", yytext); return DECL_CREATE; }
"as"        { emitToken("DECL_AS", yytext); return DECL_AS; }
"array"     { emitToken("DECL_ARRAY", yytext); return DECL_ARRAY; }
"function"  { emitToken("DECL_FUNCTION", yytext); return DECL_FUNCTION; }

"int"       { emitToken("TYPE_INT", yytext); return TYPE_INT; }
"float"     { emitToken("TYPE_FLT", yytext); return TYPE_FLT; }
"char"      { emitToken("TYPE_CHR", yytext); return TYPE_CHR; }
"string"    { emitToken("TYPE_STR", yytext); return TYPE_STR; }
"void"      { emitToken("TYPE_VOID", yytext); return TYPE_VOID; }

"check"     { emitToken("CTRL_CHECK", yytext); return CTRL_CHECK; }
"then"      { emitToken("CTRL_THEN", yytext); return CTRL_THEN; }
"otherwise" { emitToken("CTRL_OTHERWISE", yytext); return CTRL_OTHERWISE; }
"repeat"    { emitToken("CTRL_REPEAT", yytext); return CTRL_REPEAT; }
"while"     { emitToken("CTRL_WHILE", yytext); return CTRL_WHILE; }
"give"      { emitToken("CTRL_GIVE", yytext); return CTRL_GIVE; }
"back"      { emitToken("CTRL_BACK", yytext); return CTRL_BACK; }

"plus"          { emitToken("OP_ADD", yytext); return OP_ADD; }
"minus"         { emitToken("OP_SUB", yytext); return OP_SUB; }
"times"         { emitToken("OP_MUL", yytext); return OP_MUL; }
"divided_by"    { emitToken("OP_DIV", yytext); return OP_DIV; }
"="             { emitToken("OP_ASSIGN", yytext); return OP_ASSIGN; }
"+="            { emitToken("OP_ADD_ASSIGN", yytext); return OP_ADD_ASSIGN; }
"equals"        { emitToken("OP_EQ", yytext); return OP_EQ; }
"not_equals"    { emitToken("OP_NE", yytext); return OP_NE; }
"is_less_than"  { emitToken("OP_LT", yytext); return OP_LT; }
"is_greater_than" { emitToken("OP_GT", yytext); return OP_GT; }

"("         { emitToken("DELIM_PAREN_OPEN", yytext); return DELIM_PAREN_OPEN; }
")"         { emitToken("DELIM_PAREN_CLOSE", yytext); return DELIM_PAREN_CLOSE; }
"["         { emitToken("DELIM_BRACKET_OPEN", yytext); return DELIM_BRACKET_OPEN; }
"]"         { emitToken("DELIM_BRACKET_CLOSE", yytext); return DELIM_BRACKET_CLOSE; }
"{"         { emitToken("DELIM_BLOCK_OPEN", yytext); return DELIM_BLOCK_OPEN; }
"}"         { emitToken("DELIM_BLOCK_CLOSE", yytext); return DELIM_BLOCK_CLOSE; }
";"         { emitToken("DELIM_END_STATEMENT", yytext); return DELIM_END_STATEMENT; }
","         { emitToken("DELIM_SEPARATOR", yytext); return DELIM_SEPARATOR; }

"print"     { emitToken("BUILT_IN_PRINT", yytext); return BUILT_IN_PRINT; }
"scan"      { emitToken("BUILT_IN_SCAN", yytext); return BUILT_IN_SCAN; }

{ID}        { 
    yylval.id.nome = strdup(yytext);
    if (!yylval.id.nome) {
        fprintf(stderr, "Erro de memória ao alocar IDENTIFIER.\n");
        exit(EXIT_FAILURE);
    }
    yylval.id.tipo = TIPO_ERRO;
    emitToken("IDENTIFIER", yytext); 
    return IDENTIFIER;  
}

{INTEIRO}   { 
    yylval.literal.valor = strdup(yytext);
    if (!yylval.literal.valor) {
        fprintf(stderr, "Erro de memória ao alocar LITERAL_INT.\n");
        exit(EXIT_FAILURE);
    }
    yylval.literal.num = atoi(yytext);
    emitToken("LITERAL_INT", yytext); 
    return LITERAL_INT;
}
{FLOAT}     { 
    yylval.literal.valor = strdup(yytext);
    if (!yylval.literal.valor) {
        fprintf(stderr, "Erro de memória ao alocar LITERAL_FLT.\n");
        exit(EXIT_FAILURE);
    }
    yylval.literal.num = atof(yytext);
    emitToken("LITERAL_FLT", yytext); 
    return LITERAL_FLT; 
}
{CHAR}      { 
    yylval.literal.valor = strdup(yytext);
    if (!yylval.literal.valor) {
        fprintf(stderr, "Erro de memória ao alocar LITERAL_CHR.\n");
        exit(EXIT_FAILURE);
    }
    emitToken("LITERAL_CHR", yytext); 
    return LITERAL_CHR; 
}
{STRING}    { 
    yylval.literal.valor = strdup(yytext);
    if (!yylval.literal.valor) {
        fprintf(stderr, "Erro de memória ao alocar LITERAL_STR.\n");
        exit(EXIT_FAILURE);
    }
    emitToken("LITERAL_STR", yytext); 
    return LITERAL_STR; 
}

.           {
    // Definições de cores ANSI
    const char* GREEN = "\033[1;32m"; // Verde brilhante
    const char* RESET = "\033[0m";    // Reseta para cor padrão

    printf("%s\n╔════════════════════════════════════════════════════════════════╗%s\n", GREEN, RESET);
    printf("%s║                       ERRO LÉXICO                              ║%s\n", GREEN, RESET);
    printf("%s╠════════════════════════════════════════════════════════════════╣%s\n", GREEN, RESET);
    printf("%s║ Caractere inválido encontrado: '%s'                             ║%s\n", GREEN, yytext, RESET);
    printf("%s║ Linha: %d                                                       ║%s\n", GREEN, linha, RESET);
    printf("%s╚════════════════════════════════════════════════════════════════╝%s\n\n", GREEN, RESET);
}



%%

int yywrap(void) {
    return 1;
}

