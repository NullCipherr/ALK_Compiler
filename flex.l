/*******************************************************************************
 * Analisador Léxico - Compilador
 * 
 * Estrutura do Analisador:
 * 1. TOKENS (000-030):
 *    - Tipos (000-003):        T_INT, T_FLT, T_CHR, T_STR
 *    - Controle (004-008):     JMP_CND, JMP_ELS, LOOP, RET, VOID
 *    - Operadores (009-017):   ADD, SUB, MUL, DIV, MOV, CMP_EQ, CMP_NE, CMP_LT, CMP_GT
 *    - Delimitadores (018-025): PAREN_L/R, ARR_L/R, BLK_L/R, END, SEP
 *    - Identificadores (026-030): ID, INT, FLT, CHR, STR
 *
 * 2. PADRÕES REGEX:
 *    DIGITO:  [0-9]
 *    LETRA:   [a-zA-Z]
 *    ID:      {LETRA}({LETRA}|{DIGITO})*
 *    INTEIRO: {DIGITO}+
 *    FLOAT:   {DIGITO}+"."{DIGITO}+
 *    CHAR:    '[^']'
 *    STRING:  "[^"]*"
 *
 * 3. FORMATO DOS TOKENS:
 *    CATEGORIA_SUBCATEGORIA_NUM
 *    Exemplo: T_INT_000, JMP_CND_004, ADD_009
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