/*******************************************************************************
 * Analisador Léxico - Compilador
 * 
 * Estrutura do Analisador:
 * 1. CATEGORIAS DE TOKENS:
 *    - Tipos (TYPE):           TYPE_INT, TYPE_FLT, TYPE_CHR, TYPE_STR
 *    - Controle (CTRL):        CTRL_IF, CTRL_ELSE, CTRL_WHILE, CTRL_RETURN, CTRL_VOID
 *    - Operadores (OP):        OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_ASSIGN, OP_EQ, OP_NE, OP_LT, OP_GT
 *    - Delimitadores (DELIM):  DELIM_PAREN_OPEN/CLOSE, DELIM_BRACKET_OPEN/CLOSE, 
 *                              DELIM_BLOCK_OPEN/CLOSE, DELIM_END_STATEMENT, DELIM_SEPARATOR
 *    - Identificadores/Literais: IDENTIFIER, LITERAL_INT, LITERAL_FLT, LITERAL_CHR, LITERAL_STR
 *
 * 2. PADRÕES REGEX:
 *    DIGITO:  [0-9]
 *    LETRA:   [a-zA-Z]
 *    ID:      {LETRA}({LETRA}|{DIGITO}|"_")*
 *    INTEIRO: {DIGITO}+
 *    FLOAT:   {DIGITO}+"."{DIGITO}+
 *    CHAR:    '.'
 *    STRING:  "[^"]*"
 *
 * 3. FORMATO DOS TOKENS:
 *    CATEGORIA_SUBTIPO
 *    Exemplo: TYPE_INT, CTRL_IF, OP_ADD, DELIM_PAREN_OPEN, LITERAL_INT
 ******************************************************************************/

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

void emitToken(const char* token, const char* lexema) {
    total_tokens++;
    if (total_tokens == 1) {
        printf("\n╔════════════════╦═══════╦═══════════════════════════════════════╗\n");
        printf("║ TOKEN          ║ LINHA ║ LEXEMA                                ║\n");
        printf("╠════════════════╬═══════╬═══════════════════════════════════════╣\n");
    }
    
    char lexema_truncado[38];
    strncpy(lexema_truncado, lexema, 37);
    lexema_truncado[37] = '\0';
    
    printf("║ %-14s ║ %-5d ║ %-37s ║\n", 
           token,
           linha,
           lexema_truncado);
}

// Implementação da função analise_lexica
void analise_lexica(void) {
    while (yylex() != 0) {
        // O processamento é feito dentro de emitToken
    }
    if (total_tokens > 0) {
        printf("╠════════════════╩═══════╩═══════════════════════════════════════╣\n");
        printf("║ Total de tokens processados: %-33d ║\n", total_tokens);
        printf("╚════════════════════════════════════════════════════════════════╝\n\n");
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

{ID}        { emitToken("IDENTIFIER", yytext); return IDENTIFIER; }
{INTEIRO}   { emitToken("LITERAL_INT", yytext); return LITERAL_INT; }
{FLOAT}     { emitToken("LITERAL_FLT", yytext); return LITERAL_FLT; }
{CHAR}      { emitToken("LITERAL_CHR", yytext); return LITERAL_CHR; }
{STRING}    { emitToken("LITERAL_STR", yytext); return LITERAL_STR; }

.           { printf("ERRO LEXICO: caractere invalido '%s' na linha %d\n", yytext, linha); }

%%

int yywrap(void) {
    return 1;
}

