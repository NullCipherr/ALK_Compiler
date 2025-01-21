#ifndef AST_H
#define AST_H

#include "types.h"

// Tipos de nós da árvore
typedef enum
{
    NO_PROGRAMA,
    NO_DECLARACAO_VAR,
    NO_DECLARACAO_FUNC,
    NO_BLOCO,
    NO_COMANDO_IF,
    NO_COMANDO_WHILE,
    NO_ATRIBUICAO,
    NO_EXPRESSAO,
    NO_CHAMADA_FUNC,
    NO_IDENTIFICADOR,
    NO_LITERAL
} TipoNo;

// Declaração proxima para permitir recursividade
struct NoArvore;
typedef struct NoArvore NoArvore;

// Estrutura do nó da árvore
typedef struct NoArvore
{
    TipoNo tipo;
    NoArvore *proximo;

    union
    {
        struct
        {
            NoArvore *corpo;
        } programa;

        struct
        {
            char *nome;
            TipoVariavel tipo;
            NoArvore *valor;
        } declaracao_var;

        struct
        {
            char *nome;
            TipoVariavel tipo_retorno;
            struct NoArvore *parametros;
            struct NoArvore *corpo;
        } declaracao_func;

        struct
        {
            struct NoArvore *condicao;
            struct NoArvore *bloco_then;
            struct NoArvore *bloco_else;
        } comando_if;

        struct
        {
            struct NoArvore *condicao;
            struct NoArvore *bloco;
        } comando_while;

        struct
        {
            char *operador;
            struct NoArvore *esquerda;
            struct NoArvore *direita;
        } expressao;

        struct
        {
            char *nome;
            struct NoArvore *argumentos;
        } chamada_func;

        struct
        {
            char *valor;
            TipoVariavel tipo;
        } literal;

        struct
        {
            char *nome;
            TipoVariavel tipo;
        } identificador;

        struct
        {
            NoArvore *declaracoes; // Lista encadeada de declarações
        } bloco;

        struct
        {
            NoArvore *alvo;  // Target of assignment
            NoArvore *valor; // Value being assigned
        } atribuicao;
    } info;
} NoArvore;

// Funções para criar nós
NoArvore *criar_no_programa(NoArvore *declaracoes);
NoArvore *criar_no_declaracao_var(char *nome, TipoVariavel tipo, NoArvore *valor);
NoArvore *criar_no_declaracao_func(char *nome, TipoVariavel tipo_retorno, NoArvore *params, NoArvore *corpo);
NoArvore *criar_no_if(NoArvore *condicao, NoArvore *bloco_then, NoArvore *bloco_else);
NoArvore *criar_no_while(NoArvore *condicao, NoArvore *bloco);
NoArvore *criar_no_expressao(char *operador, NoArvore *esq, NoArvore *dir);
NoArvore *criar_no_chamada_func(char *nome, NoArvore *args);
NoArvore *criar_no_identificador(char *nome, TipoVariavel tipo);
NoArvore *criar_no_literal(char *valor, TipoVariavel tipo);

// Funções para manipular a árvore
void imprimir_arvore(NoArvore *no, FILE *arquivo, int nivel);
void liberar_arvore(NoArvore *no);

const char *tipoParaString(TipoVariavel tipo);

#endif // AST_H