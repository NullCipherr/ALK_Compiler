/*
 * Trabalho Prático – Parte 2
 * Disciplina: Compiladores
 * Aluno: Andrei Costa, Kananda Caroline, Leonardo Ribeiro Goulart
 *
 * Especificação: Implementação da análise sintática para um compilador de uma
 * linguagem personalizada. Esta etapa realiza:
 *
 * 1. **Análise Sintática Ascendente**:
 *    - Implementado: Recebe os tokens gerados pela análise léxica (flex.l)
 *    - Implementado: Utiliza gramática livre de contexto para reconhecer a estrutura do programa
 *    - Implementado: Gera árvore sintática durante a análise
 *    - Implementado: Apresenta a árvore sintática em arquivo de saída (arvore_sintatica.txt)
 *
 * 2. **Regras Gramaticais Principais**:
 *    programa        → declaracoes
 *    declaracoes     → declaracao | declaracoes declaracao
 *    declaracao      → declaracao_funcao | declaracao_variavel
 *    bloco           → { comandos }
 *    comando         → declaracao_variavel | atribuicao | comando_if | 
 *                      comando_while | comando_return | chamada_funcao
 *    expressao       → termo | expressao + termo | expressao - termo
 *
 * 3. **Estruturas Reconhecidas**:
 *    - Implementado: Declarações de variáveis e funções
 *      Exemplo: "create int x as 10;"
 *              "function int soma(int a, int b) { ... }"
 *    
 *    - Implementado: Estruturas de controle
 *      Exemplo: "check (x equals 10) then { ... }"
 *              "repeat while (x is_less_than 10) { ... }"
 *    
 *    - Implementado: Expressões e operações
 *      Exemplo: "x = a plus b times c"
 *              "y = (a minus b) divided_by 2"
 *
 * 4. **Integração com Análise Léxica**:
 *    - Implementado: Recebe e processa todos os tokens definidos em flex.l
 *    - Implementado: Mantém consistência com tipos, operadores e estruturas da etapa léxica
 *
 * 5. **Saída e Depuração**:
 *    - Implementado: Gera árvore sintática em formato visual
 *    - Implementado: Apresenta mensagens de erro sintático detalhadas
 *    - Implementado: Mantém rastreamento de linha/coluna para erros
 *
 * Observação:
 * Este arquivo implementa a análise sintática ascendente usando Bison, gerando
 * uma árvore sintática que será utilizada nas próximas etapas do compilador.
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "types.h"
#include "semantic.h"
#include "ast.h"

// Protótipos de funções
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

NoArvore* raiz_ast = NULL;  // Raiz da árvore sintática

void iniciar_arquivo_arvore() {
    if (arvore_arquivo != NULL) {
        fclose(arvore_arquivo);
    }
    arvore_arquivo = fopen("arvore_sintatica.txt", "w");
    if (arvore_arquivo == NULL) {
        fprintf(stderr, "Erro ao criar arquivo da árvore sintática: %s\n", 
                strerror(errno));
        exit(1);
    }
}

void fechar_arquivo_arvore() {
    if (arvore_arquivo != NULL) {
        fclose(arvore_arquivo);
        arvore_arquivo = NULL;  // Reseta ponteiro depois de fechar.
    }
}

// Definindo códigos ANSI para cores
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

// Função para mostrar a análise gramatical
void mostrarAnaliseGramatical(const char* regra) {
    // Exibindo a regra com destaque em verde
    printf(YELLOW "╔══════════════════════════════════════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(YELLOW "║ Regra: %-91s \n" RESET, regra);
    printf(YELLOW "╚══════════════════════════════════════════════════════════════════════════════════════════════════╝\n" RESET);

    // Verificando se a árvore de arquivo está configurada
    if (arvore_arquivo != NULL) {
        // Imprime espaços dependendo do nível da árvore
        for (int i = 0; i < nivel_arvore; i++) {
            fprintf(arvore_arquivo, "  ");
        }

        // Imprime a regra no arquivo com destaque
        fprintf(arvore_arquivo, BLUE "└─ %s\n" RESET, regra);
    } else {
        // Caso a árvore de arquivo seja nula, exibe uma mensagem de erro
        fprintf(stderr, RED "Erro: árvore de arquivo não inicializada.\n" RESET);
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
    struct NoArvore* no;  // Novo campo para nós da árvore
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

%type <no> programa
%type <no> lista_declaracoes
%type <no> lista_comandos
%type <no> declaracao
%type <no> declaracao_variavel
%type <no> declaracao_funcao
%type <no> comando
%type <no> comando_check
%type <no> comando_repeat
%type <no> comando_give
%type <no> atribuicao
%type <no> bloco
%type <no> expressao
%type <no> termo
%type <no> fator
%type <no> argumentos
%type <no> lista_argumentos
%type <no> parametros
%type <no> lista_parametros
%type <no> parametro
%type <tipo> tipo
%type <no> chamada_funcao
%type <id> acesso_variavel

%%

programa
    : { 
        analisador = iniciar_analisador_semantico();
        mudar_escopo(analisador, "global");
      }
      lista_declaracoes
      lista_comandos
      {
          // Combina declarações e comandos em uma única lista
          NoArvore* lista_completa = $2;
          if (lista_completa != NULL) {
              NoArvore* ultimo = lista_completa;
              while (ultimo->proximo != NULL) {
                  ultimo = ultimo->proximo;
              }
              ultimo->proximo = $3;
          } else {
              lista_completa = $3;
          }
          raiz_ast = criar_no_programa(lista_completa);
          if (arvore_arquivo != NULL) {
              // imprimir_arvore(raiz_ast, arvore_arquivo, 0);
          }
      }
    ;

lista_declaracoes
    : /* vazio */
        { $$ = NULL; }
    | lista_declaracoes declaracao
        { 
            if ($1 == NULL) {
                $$ = $2;
            } else {
                NoArvore* ultimo = $1;
                while (ultimo->proximo != NULL) {
                    ultimo = ultimo->proximo;
                }
                ultimo->proximo = $2;
                $$ = $1;
            }
        }
    ;

lista_comandos
    : /* vazio */
        { $$ = NULL; }
    | lista_comandos comando
        {
            if ($1 == NULL) {
                $$ = $2;
            } else {
                NoArvore* ultimo = $1;
                while (ultimo->proximo != NULL) {
                    ultimo = ultimo->proximo;
                }
                ultimo->proximo = $2;
                $$ = $1;
            }
        }
    ;

declaracao
    : declaracao_variavel
        { $$ = $1; }
    | declaracao_funcao
        { $$ = $1; }
    ;

declaracao_variavel
    : DECL_CREATE tipo IDENTIFIER DECL_AS expressao DELIM_END_STATEMENT
        {
            if (!inserir_simbolo(analisador, $3.nome, $2)) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' já declarada                           ║\n", $3.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n\n");
                YYERROR;
            }
            // Verificar o tipo da expressão através do analisador semântico
            SimboloEntrada* simbolo = buscar_simbolo(analisador, $3.nome);
            if (!verificar_compatibilidade_tipos(analisador, $2, simbolo->tipo, $3.nome)) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Tipo incompatível na inicialização da variável '%s'  ║\n", $3.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n\n");
                YYERROR;
            }
            $$ = criar_no_declaracao_var($3.nome, $2, $5);
        }
    | DECL_CREATE tipo IDENTIFIER DELIM_BRACKET_OPEN LITERAL_INT DELIM_BRACKET_CLOSE 
      DECL_AS DECL_ARRAY DELIM_END_STATEMENT
        {
            int tamanho = atoi($5.valor);
            if (tamanho <= 0) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Tamanho inválido para o vetor '%s'                   ║\n", $3.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n\n");
                YYERROR;
            }
            if (!inserir_vetor(analisador, $3.nome, $2, tamanho)) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' já declarada                           ║\n", $3.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n\n");
                YYERROR;
            }
            NoArvore* literal = criar_no_literal($5.valor, TIPO_INT);
            $$ = criar_no_declaracao_var($3.nome, TIPO_VETOR, literal);
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
            $$ = criar_no_declaracao_func($3.nome, $2, $6, $9);
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
    : declaracao_variavel
        { $$ = $1; }
    | atribuicao DELIM_END_STATEMENT
        { $$ = $1; }
    | chamada_funcao DELIM_END_STATEMENT
        { $$ = $1; }
    | comando_give
        { $$ = $1; }
    | comando_check
        { $$ = $1; }
    | comando_repeat
        { $$ = $1; }
    ;

comando_check
    : CTRL_CHECK DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE CTRL_THEN bloco
        {
            $$ = criar_no_if($3, $6, NULL);
        }
    | CTRL_CHECK DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE CTRL_THEN bloco CTRL_OTHERWISE bloco
        {
            $$ = criar_no_if($3, $6, $8);
        }
    ;

comando_repeat
    : CTRL_REPEAT CTRL_WHILE DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE bloco
        {
            $$ = criar_no_while($4, $6);
        }
    ;

comando_give
    : CTRL_GIVE CTRL_BACK expressao DELIM_END_STATEMENT
        {
            mostrarAnaliseGramatical("Give → give back expressão;");
            // Verificar se o tipo de retorno corresponde ao tipo da função
            if (analisador->escopo_atual != NULL && 
                strncmp(analisador->escopo_atual, "funcao_", 7) == 0) {
                SimboloEntrada* func = buscar_simbolo(analisador, analisador->escopo_atual + 7);
                if (func && func->info.funcao.tipo_retorno != $3->info.literal.tipo) {
                    printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                    printf("║ Tipo de retorno incompatível na função '%s'          ║\n", analisador->escopo_atual + 7);
                    printf("╚═══════════════════════════════════════════════════════╝\n\n");
                    analisador->num_erros++;
                }
            }
        }
    | CTRL_GIVE CTRL_BACK DELIM_END_STATEMENT  // Para funções void
        {
            mostrarAnaliseGramatical("Give → give back;");
            if (analisador->escopo_atual != NULL && 
                strncmp(analisador->escopo_atual, "funcao_", 7) == 0) {
                SimboloEntrada* func = buscar_simbolo(analisador, analisador->escopo_atual + 7);
                if (func && func->info.funcao.tipo_retorno != TIPO_VOID) {
                    printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                    printf("║ Função '%s' deve retornar um valor                   \n", analisador->escopo_atual + 7);
                    printf("╚═══════════════════════════════════════════════════════╝\n\n");
                    analisador->num_erros++;
                }
            }
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
                printf("║ Variável '%s' não declarada                          \n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n\n");
                analisador->num_erros++;
            } else if (!verificar_compatibilidade_tipos(analisador, simbolo->tipo, $3->info.literal.tipo, $1.nome)) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Tipo incompatível na atribuição para '%s'            \n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n\n");
                analisador->num_erros++;
            }
        }
    | IDENTIFIER DELIM_BRACKET_OPEN expressao DELIM_BRACKET_CLOSE OP_ASSIGN expressao
        {
            mostrarAnaliseGramatical("Atribuição → Identificador[Expressão] = Expressão");
            SimboloEntrada* simbolo = buscar_simbolo(analisador, $1.nome);
            if (simbolo == NULL) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não declarada                          \n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n\n");
                analisador->num_erros++;
            } else if (simbolo->tipo != TIPO_VETOR) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não é um vetor                         \n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n\n");
                analisador->num_erros++;
            } else if (!verificar_compatibilidade_tipos(analisador, simbolo->info.vetor.tipo_base, $6->info.literal.tipo, $1.nome)) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Tipo incompatível na atribuição para '%s'            \n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n\n");
                analisador->num_erros++;
            }
        }
    | IDENTIFIER OP_ADD_ASSIGN expressao
        {
            mostrarAnaliseGramatical("Atribuição → Identificador += Expressão");
            SimboloEntrada* simbolo = buscar_simbolo(analisador, $1.nome);
            if (simbolo == NULL) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não declarada                          \n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n\n");
                analisador->num_erros++;
            } else if (!verificar_compatibilidade_tipos(analisador, simbolo->tipo, $3->info.literal.tipo, $1.nome)) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Tipo incompatível na operação += para '%s'           \n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n\n");
                analisador->num_erros++;
            }
        }
    ;

expressao
    : termo
        { $$ = $1; }
    | expressao OP_ADD termo
        { 
            $$ = criar_no_expressao("plus", $1, $3);
        }
    | expressao OP_SUB termo
        { 
            $$ = criar_no_expressao("minus", $1, $3);
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
        { $$ = $1; }
    | termo OP_MUL fator
        { 
            $$ = criar_no_expressao("times", $1, $3);
        }
    | termo OP_DIV fator
        { 
            $$ = criar_no_expressao("divided_by", $1, $3);
        }
    ;

fator
    : IDENTIFIER
        { 
            SimboloEntrada* simbolo = buscar_simbolo(analisador, $1.nome);
            if (simbolo == NULL) {
                printf("\n╔════════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não declarada                          \n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n\n");
                analisador->num_erros++;
                $$ = criar_no_identificador($1.nome, TIPO_ERRO);
            } else {
                $$ = criar_no_identificador($1.nome, simbolo->tipo);
            }
        }
    | IDENTIFIER DELIM_BRACKET_OPEN expressao DELIM_BRACKET_CLOSE
        {
            SimboloEntrada* simbolo = buscar_simbolo(analisador, $1.nome);
            if (simbolo == NULL) {
                printf("\n╔════════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não declarada                          \n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n");
                analisador->num_erros++;
                $$ = criar_no_identificador($1.nome, TIPO_ERRO);
            } else if (simbolo->tipo != TIPO_VETOR) {
                printf("\n╔════════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não é um vetor                         \n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n");
                analisador->num_erros++;
                $$ = criar_no_identificador($1.nome, TIPO_ERRO);
            } else {
                $$ = criar_no_identificador($1.nome, simbolo->info.vetor.tipo_base);
            }
        }
    | LITERAL_INT
        { $$ = criar_no_literal($1.valor, TIPO_INT); }
    | LITERAL_FLT
        { $$ = criar_no_literal($1.valor, TIPO_FLOAT); }
    | LITERAL_CHR
        { $$ = criar_no_literal($1.valor, TIPO_CHAR); }
    | LITERAL_STR
        { $$ = criar_no_literal($1.valor, TIPO_STRING); }
    | DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE
        { $$ = $2; }
    | IDENTIFIER DELIM_PAREN_OPEN argumentos DELIM_PAREN_CLOSE
        {
            SimboloEntrada* func = buscar_simbolo(analisador, $1.nome);
            if (func == NULL || func->tipo != TIPO_FUNCAO) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Função '%s' não declarada                             ║\n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n");
                analisador->num_erros++;
                $$ = NULL;
            } else {
                verificar_chamada_funcao(analisador, $1.nome, num_argumentos);
                $$ = criar_no_chamada_func($1.nome, $3);
            }
        }
    ;

chamada_funcao
    : IDENTIFIER DELIM_PAREN_OPEN argumentos DELIM_PAREN_CLOSE
        {
            SimboloEntrada* func = buscar_simbolo(analisador, $1.nome);
            if (func == NULL || func->tipo != TIPO_FUNCAO) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Função '%s' não declarada                             ║\n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n");
                analisador->num_erros++;
                $$ = NULL;
            } else {
                verificar_chamada_funcao(analisador, $1.nome, num_argumentos);
                $$ = criar_no_chamada_func($1.nome, $3);
            }
        }
    | BUILT_IN_PRINT DELIM_PAREN_OPEN expressao DELIM_PAREN_CLOSE
        {
            mostrarAnaliseGramatical("Chamada Função → print ( Expressão )");
            $$ = criar_no_chamada_func("print", $3);
        }
    | BUILT_IN_SCAN DELIM_PAREN_OPEN acesso_variavel DELIM_PAREN_CLOSE
        {
            mostrarAnaliseGramatical("Chamada Função → scan ( Acesso Variável )");
            if ($3.tipo == TIPO_INT || $3.tipo == TIPO_FLOAT || $3.tipo == TIPO_CHAR || $3.tipo == TIPO_STRING) {
                $$ = criar_no_chamada_func("scan", criar_no_identificador($3.nome, $3.tipo));
            } else {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Tipo inválido para scan: '%s'                        ║\n", tipoParaString($3.tipo));
                printf("╚═══════════════════════════════════════════════════════╝\n\n");
                analisador->num_erros++;
                $$ = NULL;
            }
        }
    ;

acesso_variavel
    : IDENTIFIER
        {
            mostrarAnaliseGramatical("Acesso Variável → Identificador");
            SimboloEntrada* simbolo = buscar_simbolo(analisador, $1.nome);
            if (simbolo == NULL) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não declarada                          \n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n\n");
                analisador->num_erros++;
            }
        }
    | IDENTIFIER DELIM_BRACKET_OPEN expressao DELIM_BRACKET_CLOSE
        {
            mostrarAnaliseGramatical("Acesso Variável → Identificador [ Expressão ]");
            SimboloEntrada* simbolo = buscar_simbolo(analisador, $1.nome);
            if (simbolo == NULL) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não declarada                          \n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n\n");
                analisador->num_erros++;
            } else if (simbolo->tipo != TIPO_VETOR) {
                printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
                printf("║ Variável '%s' não é um vetor                         \n", $1.nome);
                printf("╚═══════════════════════════════════════════════════════╝\n\n");
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
    printf("╚═══════════════════════════════════════════════════════════╝\n\n");
    return TIPO_ERRO;
}

void yyerror(const char *s) {
    printf(RED"\n╔══════════════════════ ERRO SINTÁTICO ══════════════════════╗\n");
    printf("║ Linha: %-51d ║\n", linha);
    printf("║ Erro:  %-51s ║\n", s);
    printf("║                                                            ║\n");
    printf("║ Contexto do Erro:                                          ║\n");
    printf("║ - Verificar tipos dos operandos                            ║\n");
    printf("║ - Verificar sintaxe da expressão                           ║\n");
    printf("║ - Verificar declaração de variáveis                        ║\n");
    printf("╚════════════════════════════════════════════════════════════╝ \n\n"RESET);
}

void exibir_cabecalho() {
    printf("\033[1;32m"); // Define a cor do texto para verde brilhante
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║                COMPILADOR ALK - v1.0                   ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║     Desenvolvido para a disciplina de compiladores     ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n\n");
    printf("\033[0m"); // Reseta as cores para o padrão
}

void exibir_rodape() {
    printf("\033[1;34m"); // Define a cor do texto para azul brilhante
    printf("\n╔════════════════════════════════════════════════════════╗\n");
    printf("║      Obrigado por utilizar o Compilador ALK!           ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n\n");
    printf("\033[0m"); // Reseta as cores para o padrão
}

int main(void) 
{
    // Exibe o cabeçalho do compilador
    exibir_cabecalho();
    
    // Inicializa o processo de criação da árvore de sintaxe abstrata 
    iniciar_arquivo_arvore();

    // Realiza a análise léxica primeiro
    // analise_lexica();
    
    // Realiza a análise sintática do código fonte
    int resultado = yyparse();
    
    // Se a árvore de sintaxe abstrata foi criada, realiza o processamento
    if (raiz_ast != NULL) {
        if (arvore_arquivo != NULL) {
            imprimir_arvore(raiz_ast, arvore_arquivo, 0);
        }
        liberar_arvore(raiz_ast);
        raiz_ast = NULL;
    }
    
    // Se o analisador semântico foi inicializado, finaliza o processo
    if (analisador != NULL) {
        finalizar_analisador_semantico(analisador);
        analisador = NULL;
    }
    
    // Fecha o arquivo de saída da árvore
    fechar_arquivo_arvore();
    
    // Exibe o rodapé
    exibir_rodape();
    
    return resultado;
}