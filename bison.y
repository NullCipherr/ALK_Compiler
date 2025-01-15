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
#include "semantic.h"

// Protótipos de funções
const char* tipoParaString(TipoVariavel tipo);
const char* nomeVariavel(const char* nome);
TipoVariavel verificarTipos(TipoVariavel tipo1, const char* operador, TipoVariavel tipo2);
void mostrarAnaliseGramatical(const char* regra);
void mostrarAnaliseTipos(const char* operacao, TipoVariavel tipo1, TipoVariavel tipo2, TipoVariavel resultado);
extern void analise_lexica(void);  

extern int linha;
extern int total_tokens;
void yyerror(const char *s);
int yylex(void);

FILE* arvore_arquivo = NULL;
int nivel_arvore = 0;

AnalisadorSemantico* analisador;

int num_argumentos = 0;
int num_parametros = 0;

void iniciar_arquivo_arvore() {
    arvore_arquivo = fopen("arvore_sintatica.txt", "w");
    if (arvore_arquivo == NULL) {
        printf("Erro ao criar arquivo da árvore sintática\n");
        exit(1);
    }
}

void fechar_arquivo_arvore() {
    if (arvore_arquivo != NULL) {
        fclose(arvore_arquivo);
    }
}

void mostrarAnaliseGramatical(const char* regra) {
    printf("║ Regra: %-53s ║\n", regra);
    if (arvore_arquivo != NULL) {
        for (int i = 0; i < nivel_arvore; i++) {
            fprintf(arvore_arquivo, "  ");
        }
        fprintf(arvore_arquivo, "└─ %s\n", regra);
    }
}

%}

%union {
    struct {
        char* nome;
        TipoVariavel tipo;
    } id;
    TipoVariavel tipo;
    struct {
        char* valor;
        int num;
    } literal;
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
%token <literal> LITERAL_INT LITERAL_FLT LITERAL_CHR LITERAL_STR
%token BUILT_IN_PRINT "print"
%token BUILT_IN_SCAN "scan"

%type <tipo> expressao termo fator tipo
%type <id> acesso_variavel
%type <tipo> chamada_funcao

%%

programa
    : { 
        analisador = iniciar_analisador_semantico();
        mudar_escopo(analisador, "global");
      }
      lista_declaracoes
      lista_comandos
    ;

lista_declaracoes
    : /* vazio */
    | lista_declaracoes declaracao
    ;

lista_comandos
    : /* vazio */
    | lista_comandos comando
    ;

declaracao
    : declaracao_variavel
    | declaracao_funcao
    ;

declaracao_variavel
    : DECL_CREATE tipo IDENTIFIER DECL_AS expressao DELIM_END_STATEMENT
        {
            if (!inserir_simbolo(analisador, $3.nome, $2)) {
                YYERROR;
            }
            // Verificar compatibilidade de tipos na atribuição
            if (!verificar_compatibilidade_tipos(analisador, $2, $5, $3.nome)) {
                YYERROR;
            }
        }
    | DECL_CREATE tipo IDENTIFIER DELIM_BRACKET_OPEN LITERAL_INT DELIM_BRACKET_CLOSE 
      DECL_AS DECL_ARRAY DELIM_END_STATEMENT
        {
            int tamanho = atoi($5.valor);
            if (!inserir_vetor(analisador, $3.nome, $2, tamanho)) {
                YYERROR;
            }
        }
    ;

declaracao_funcao
    : DECL_FUNCTION tipo IDENTIFIER 
        {
            // Criar novo escopo para a função
            char escopo_funcao[256];
            snprintf(escopo_funcao, sizeof(escopo_funcao), "funcao_%s", $3.nome);
            mudar_escopo(analisador, escopo_funcao);
            inserir_funcao(analisador, $3.nome, $2);
        }
      DELIM_PAREN_OPEN parametros 
        {
            // Registrar o número de parâmetros
            registrar_parametros_funcao(analisador, $3.nome, num_parametros);
        }
      DELIM_PAREN_CLOSE bloco
        {
            // Voltar ao escopo global após a função
            mudar_escopo(analisador, "global");
        }
    ;

parametros
    : /* vazio */
        { 
            mostrarAnaliseGramatical("Parâmetros → vazio");
            num_parametros = 0;
        }
    | lista_parametros
        { 
            mostrarAnaliseGramatical("Parâmetros → Lista Parâmetros");
        }
    ;

lista_parametros
    : parametro
        { 
            mostrarAnaliseGramatical("Lista Parâmetros → Parâmetro");
            num_parametros = 1;
        }
    | lista_parametros DELIM_SEPARATOR parametro
        { 
            mostrarAnaliseGramatical("Lista Parâmetros → Lista Parâmetros , Parâmetro");
            num_parametros++;
        }
    ;

parametro
    : tipo IDENTIFIER
        {
            mostrarAnaliseGramatical("Parâmetro → Tipo Identificador");
            inserir_parametro(analisador, $2.nome, $1);
        }
    ;

tipo
    : TYPE_INT   { $$ = TIPO_INT; }
    | TYPE_FLT   { $$ = TIPO_FLOAT; }
    | TYPE_CHR   { $$ = TIPO_CHAR; }
    | TYPE_STR   { $$ = TIPO_STRING; }
    | TYPE_VOID  { $$ = TIPO_VOID; }
    ;

comando
    : comando_check
    | comando_repeat
    | atribuicao DELIM_END_STATEMENT
    | chamada_funcao DELIM_END_STATEMENT
    | comando_give
    | declaracao_variavel
    ;

comando_check
    : CTRL_CHECK DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE CTRL_THEN bloco
        {
            mostrarAnaliseGramatical("Check → check ( Expressão ) then Bloco");
        }
    | CTRL_CHECK DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE CTRL_THEN bloco CTRL_OTHERWISE bloco
        {
            mostrarAnaliseGramatical("Check → check ( Expressão ) then Bloco otherwise Bloco");
        }
    ;

comando_repeat
    : CTRL_REPEAT CTRL_WHILE DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE bloco
        { mostrarAnaliseGramatical("Repeat → repeat while (expressão) bloco"); }
    ;

comando_give
    : CTRL_GIVE CTRL_BACK expressao DELIM_END_STATEMENT
        {
            mostrarAnaliseGramatical("Give → give back expressão;");
            // Verificar se o tipo de retorno corresponde ao tipo da função
            if (analisador->escopo_atual != NULL && 
                strncmp(analisador->escopo_atual, "funcao_", 7) == 0) {
                // Lógica de verificação do tipo de retorno
            }
        }
    | CTRL_GIVE CTRL_BACK DELIM_END_STATEMENT  // Para funções void
        {
            mostrarAnaliseGramatical("Give → give back;");
        }
    ;

bloco
    : DELIM_BLOCK_OPEN lista_comandos DELIM_BLOCK_CLOSE
        {
            mostrarAnaliseGramatical("Bloco → { Lista Comandos }");
        }
    ;

atribuicao
    : IDENTIFIER OP_ASSIGN expressao
        {
            mostrarAnaliseGramatical("Atribuição → Identificador = Expressão");
            SimboloEntrada* simbolo = buscar_simbolo(analisador, $1.nome);
            if (simbolo == NULL) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não declarada                          ║\n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n");
                analisador->num_erros++;
            }
        }
    | IDENTIFIER DELIM_BRACKET_OPEN expressao DELIM_BRACKET_CLOSE OP_ASSIGN expressao
        {
            mostrarAnaliseGramatical("Atribuição → Identificador[Expressão] = Expressão");
            SimboloEntrada* simbolo = buscar_simbolo(analisador, $1.nome);
            if (simbolo == NULL) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não declarada                          ║\n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n");
                analisador->num_erros++;
            } else if (simbolo->tipo != TIPO_VETOR) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não é um vetor                         ║\n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n");
                analisador->num_erros++;
            }
        }
    | IDENTIFIER OP_ADD_ASSIGN expressao
        {
            mostrarAnaliseGramatical("Atribuição → Identificador += Expressão");
            SimboloEntrada* simbolo = buscar_simbolo(analisador, $1.nome);
            if (simbolo == NULL) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não declarada                          ║\n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n");
                analisador->num_erros++;
            }
        }
    ;

expressao
    : termo
        { 
            mostrarAnaliseGramatical("Expressão → Termo");
            $$ = $1;
        }
    | LITERAL_STR
        {
            mostrarAnaliseGramatical("Expressão → String Literal");
            $$ = TIPO_STRING;
        }
    | expressao OP_ADD termo
        { 
            mostrarAnaliseGramatical("Expressão → Expressão plus Termo");
            $$ = verificar_tipos_operacao(analisador, $1, $3, "plus");
        }
    | expressao OP_SUB termo
        { 
            mostrarAnaliseGramatical("Expressão → Expressão minus Termo");
            $$ = verificar_tipos_operacao(analisador, $1, $3, "minus");
        }
    | expressao OP_GT termo
        { 
            mostrarAnaliseGramatical("Expressão → Expressão is_greater_than Termo");
            $$ = TIPO_INT;  // Operações relacionais retornam tipo booleano (int)
        }
    | expressao OP_LT termo
        { 
            mostrarAnaliseGramatical("Expressão → Expressão is_less_than Termo");
            $$ = TIPO_INT;
        }
    | expressao OP_EQ termo
        { 
            mostrarAnaliseGramatical("Expressão → Expressão equals Termo");
            $$ = TIPO_INT;
        }
    | expressao OP_NE termo
        { 
            mostrarAnaliseGramatical("Expressão → Expressão not_equals Termo");
            $$ = TIPO_INT;
        }
    ;

termo
    : fator
        { 
            $$ = $1;
        }
    | termo OP_MUL fator
        { 
            $$ = verificar_tipos_operacao(analisador, $1, $3, "times");
        }
    | termo OP_DIV fator
        { 
            $$ = verificar_tipos_operacao(analisador, $1, $3, "divided_by");
        }
    ;

fator
    : IDENTIFIER
        { 
            SimboloEntrada* simbolo = buscar_simbolo(analisador, $1.nome);
            if (simbolo == NULL) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não declarada                          ║\n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n");
                analisador->num_erros++;
                $$ = TIPO_ERRO;
            } else {
                $$ = simbolo->tipo;
            }
        }
    | IDENTIFIER DELIM_BRACKET_OPEN expressao DELIM_BRACKET_CLOSE
        {
            SimboloEntrada* simbolo = buscar_simbolo(analisador, $1.nome);
            if (simbolo == NULL) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não declarada                          ║\n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n");
                analisador->num_erros++;
                $$ = TIPO_ERRO;
            } else if (simbolo->tipo != TIPO_VETOR) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não é um vetor                         ║\n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n");
                analisador->num_erros++;
                $$ = TIPO_ERRO;
            } else {
                $$ = simbolo->info.vetor.tipo_base;
            }
        }
    | LITERAL_INT   { $$ = TIPO_INT; }
    | LITERAL_FLT   { $$ = TIPO_FLOAT; }
    | LITERAL_CHR   { $$ = TIPO_CHAR; }
    | LITERAL_STR   { $$ = TIPO_STRING; }
    | DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE { $$ = $2; }
    | IDENTIFIER DELIM_PAREN_OPEN argumentos DELIM_PAREN_CLOSE
        {
            SimboloEntrada* func = buscar_simbolo(analisador, $1.nome);
            if (func == NULL || func->tipo != TIPO_FUNCAO) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Função '%s' não declarada                             ║\n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n");
                analisador->num_erros++;
                $$ = TIPO_ERRO;
            } else {
                verificar_chamada_funcao(analisador, $1.nome, num_argumentos);
                $$ = func->info.funcao.tipo_retorno;
            }
        }
    ;

chamada_funcao
    : IDENTIFIER DELIM_PAREN_OPEN argumentos DELIM_PAREN_CLOSE
        {
            mostrarAnaliseGramatical("Chamada Função → Identificador ( Argumentos )");
            SimboloEntrada* func = buscar_simbolo(analisador, $1.nome);
            if (func == NULL || func->tipo != TIPO_FUNCAO) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Função '%s' não declarada                             ║\n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n");
                analisador->num_erros++;
                $$ = TIPO_ERRO;
            } else {
                verificar_chamada_funcao(analisador, $1.nome, num_argumentos);
                $$ = func->info.funcao.tipo_retorno;
            }
        }
    | BUILT_IN_PRINT DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE
        {
            mostrarAnaliseGramatical("Chamada Função → print ( Expressão )");
            $$ = TIPO_VOID;
        }
    | BUILT_IN_SCAN DELIM_PAREN_OPEN acesso_variavel DELIM_PAREN_CLOSE
        {
            mostrarAnaliseGramatical("Chamada Função → scan ( Acesso Variável )");
            $$ = TIPO_VOID;
        }
    ;

acesso_variavel
    : IDENTIFIER
        {
            mostrarAnaliseGramatical("Acesso Variável → Identificador");
            SimboloEntrada* simbolo = buscar_simbolo(analisador, $1.nome);
            if (simbolo == NULL) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não declarada                          ║\n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n");
                analisador->num_erros++;
            }
        }
    | IDENTIFIER DELIM_BRACKET_OPEN expressao DELIM_BRACKET_CLOSE
        {
            mostrarAnaliseGramatical("Acesso Variável → Identificador [ Expressão ]");
            SimboloEntrada* simbolo = buscar_simbolo(analisador, $1.nome);
            if (simbolo == NULL) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não declarada                          ║\n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n");
                analisador->num_erros++;
            } else if (simbolo->tipo != TIPO_VETOR) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não é um vetor                         ║\n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n");
                analisador->num_erros++;
            }
        }
    ;

argumentos
    : /* vazio */
        { 
            mostrarAnaliseGramatical("Argumentos → vazio");
            num_argumentos = 0;
        }
    | lista_argumentos
        { 
            mostrarAnaliseGramatical("Argumentos → Lista Argumentos");
        }
    ;

lista_argumentos
    : expressao
        { 
            mostrarAnaliseGramatical("Lista Argumentos → Expressão");
            num_argumentos = 1;
        }
    | lista_argumentos DELIM_SEPARATOR expressao
        { 
            mostrarAnaliseGramatical("Lista Argumentos → Lista Argumentos , Expressão");
            num_argumentos++;
        }
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

const char* nomeVariavel(const char* nome) {
    if (nome == NULL) {
        return "<<sem nome>>";
    }
    return nome;
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
    
    if (getenv("GERAR_ARVORE")) {
        iniciar_arquivo_arvore();
    }
    
    int resultado = yyparse();
    
    if (analisador != NULL) {
        finalizar_analisador_semantico(analisador);
    }
    
    if (getenv("GERAR_ARVORE")) {
        fechar_arquivo_arvore();
    }
    
    return resultado;
}