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
 *    LETRA:   [a-zA-Z_]
 *    ID:      {LETRA}({LETRA}|{DIGITO})*
 *    INTEIRO: {DIGITO}+
 *    FLOAT:   {DIGITO}+"."{DIGITO}+
 *    CHAR:    '[^']'
 *    STRING:  "[^"]*"
 *
 * 3. FORMATO DOS TOKENS:
 *    CATEGORIA_SUBTIPO
 *    Exemplo: TYPE_INT, CTRL_IF, OP_ADD, DELIM_PAREN_OPEN, LITERAL_INT
 ******************************************************************************/

%{
#include <stdio.h>
#include <string.h>

int linha = 1;
int coluna = 1;

void emitToken(const char* token, const char* lexema) {
    printf("%-12s | linha: %-4d | lexema: %s\n", token, linha, lexema);
}
%}

DIGITO      [0-9]
LETRA       [a-zA-Z_]
ID          {LETRA}({LETRA}|{DIGITO})*
INTEIRO     {DIGITO}+
FLOAT       {DIGITO}+"."{DIGITO}+
CHAR        \'[^']\'
STRING      \"[^"]*\"
ESPACO      [ \t\r]+
COMENTARIO  "//"[^\n]*  

%%

{ESPACO}    { coluna += yyleng; }
\n          { linha++; coluna = 1; }
{COMENTARIO} { /* Ignora comentários */ }

"int"       { emitToken("TYPE_INT", yytext); }
"float"     { emitToken("TYPE_FLT", yytext); }
"char"      { emitToken("TYPE_CHR", yytext); }
"string"    { emitToken("TYPE_STR", yytext); }

"if"        { emitToken("CTRL_IF", yytext); }
"else"      { emitToken("CTRL_ELSE", yytext); }
"while"     { emitToken("CTRL_WHILE", yytext); }
"return"    { emitToken("CTRL_RETURN", yytext); }
"void"      { emitToken("CTRL_VOID", yytext); }

"+"         { emitToken("OP_ADD", yytext); }
"-"         { emitToken("OP_SUB", yytext); }
"*"         { emitToken("OP_MUL", yytext); }
"/"         { emitToken("OP_DIV", yytext); }
"="         { emitToken("OP_ASSIGN", yytext); }
"=="        { emitToken("OP_EQ", yytext); }
"!="        { emitToken("OP_NE", yytext); }
"<"         { emitToken("OP_LT", yytext); }
">"         { emitToken("OP_GT", yytext); }

"("         { emitToken("DELIM_PAREN_OPEN", yytext); }
")"         { emitToken("DELIM_PAREN_CLOSE", yytext); }
"["         { emitToken("DELIM_BRACKET_OPEN", yytext); }
"]"         { emitToken("DELIM_BRACKET_CLOSE", yytext); }
"{"         { emitToken("DELIM_BLOCK_OPEN", yytext); }
"}"         { emitToken("DELIM_BLOCK_CLOSE", yytext); }
";"         { emitToken("DELIM_END_STATEMENT", yytext); }
","         { emitToken("DELIM_SEPARATOR", yytext); }

{ID}        { emitToken("IDENTIFIER", yytext); }
{INTEIRO}   { emitToken("LITERAL_INT", yytext); }
{FLOAT}     { emitToken("LITERAL_FLT", yytext); }
{CHAR}      { emitToken("LITERAL_CHR", yytext); }
{STRING}    { emitToken("LITERAL_STR", yytext); }

.           { printf("ERRO LEXICO: caractere invalido '%s' na linha %d\n", yytext, linha); }

%%

int yywrap(void) {
    return 1;
}

int main(void) {
    printf("TOKEN        | LINHA     | LEXEMA\n");
    printf("----------------------------------------\n");
    yylex();
    return 0;
}