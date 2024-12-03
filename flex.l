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

"int"       { emitToken("T_INT_000", yytext); }
"float"     { emitToken("T_FLT_001", yytext); }
"char"      { emitToken("T_CHR_002", yytext); }
"string"    { emitToken("T_STR_003", yytext); }

"if"        { emitToken("JMP_CND_004", yytext); }
"else"      { emitToken("JMP_ELS_005", yytext); }
"while"     { emitToken("LOOP_006", yytext); }
"return"    { emitToken("RET_007", yytext); }
"void"      { emitToken("VOID_008", yytext); }

"+"         { emitToken("ADD_009", yytext); }
"-"         { emitToken("SUB_010", yytext); }
"*"         { emitToken("MUL_011", yytext); }
"/"         { emitToken("DIV_012", yytext); }
"="         { emitToken("MOV_013", yytext); }
"=="        { emitToken("CMP_EQ_014", yytext); }
"!="        { emitToken("CMP_NE_015", yytext); }
"<"         { emitToken("CMP_LT_016", yytext); }
">"         { emitToken("CMP_GT_017", yytext); }

"("         { emitToken("PAREN_L_018", yytext); }
")"         { emitToken("PAREN_R_019", yytext); }
"["         { emitToken("ARR_L_020", yytext); }
"]"         { emitToken("ARR_R_021", yytext); }
"{"         { emitToken("BLK_L_022", yytext); }
"}"         { emitToken("BLK_R_023", yytext); }
";"         { emitToken("END_024", yytext); }
","         { emitToken("SEP_025", yytext); }

{ID}        { emitToken("ID_026", yytext); }
{INTEIRO}   { emitToken("INT_027", yytext); }
{FLOAT}     { emitToken("FLT_028", yytext); }
{CHAR}      { emitToken("CHR_029", yytext); }
{STRING}    { emitToken("STR_030", yytext); }

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