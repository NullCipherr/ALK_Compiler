#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

// Função auxiliar para indentação
static void imprimir_indentacao(FILE *arquivo, int nivel)
{
    for (int i = 0; i < nivel; i++)
    {
        fprintf(arquivo, "  ");
    }
}

// Implementação das funções de criação de nós
NoArvore *criar_no_programa(NoArvore *corpo)
{
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));

    if (no == NULL)
    {
        fprintf(stderr, "Erro: Falha na alocação de memória para nó programa\n");
        exit(1);
    }

    memset(no, 0, sizeof(NoArvore)); // Zera a struct

    no->tipo = NO_PROGRAMA;
    no->proximo = NULL;
    no->info.programa.corpo = corpo;
    return no;
}

NoArvore *criar_no_declaracao_var(char *nome, TipoVariavel tipo, NoArvore *valor)
{
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));

    if (no == NULL)
    {
        fprintf(stderr, "Erro: Falha na alocação de memória para nó declaracao var\n");
        exit(1);
    }

    memset(no, 0, sizeof(NoArvore)); // Zera a struct

    no->tipo = NO_DECLARACAO_VAR;
    no->info.declaracao_var.nome = strdup(nome);
    if (no->info.declaracao_var.nome == NULL)
    {
        fprintf(stderr, "Erro: Falha ao duplicar string.\n");
        free(no);
        exit(1);
    }
    no->info.declaracao_var.tipo = tipo;
    no->info.declaracao_var.valor = valor;
    no->proximo = NULL;
    return no;
}

NoArvore *criar_no_declaracao_func(char *nome, TipoVariavel tipo_retorno, NoArvore *params, NoArvore *corpo)
{
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));

    if (no == NULL)
    {
        fprintf(stderr, "Erro: Falha na alocação de memória para nó declaracao função\n");
        exit(1);
    }

    memset(no, 0, sizeof(NoArvore)); // Zera a struct

    no->tipo = NO_DECLARACAO_FUNC;
    no->info.declaracao_func.nome = strdup(nome);
    if (no->info.declaracao_func.nome == NULL)
    {
        fprintf(stderr, "Erro: Falha ao duplicar string.\n");
        free(no);
        exit(1);
    }
    no->info.declaracao_func.tipo_retorno = tipo_retorno;
    no->info.declaracao_func.parametros = params;
    no->info.declaracao_func.corpo = corpo;
    no->proximo = NULL;
    return no;
}

NoArvore *criar_no_if(NoArvore *condicao, NoArvore *bloco_then, NoArvore *bloco_else)
{
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));

    if (no == NULL)
    {
        fprintf(stderr, "Erro: Falha na alocação de memória para nó if\n");
        exit(1);
    }

    memset(no, 0, sizeof(NoArvore)); // Zera a struct

    no->tipo = NO_COMANDO_IF;
    no->info.comando_if.condicao = condicao;
    no->info.comando_if.bloco_then = bloco_then;
    no->info.comando_if.bloco_else = bloco_else;
    no->proximo = NULL;
    return no;
}

NoArvore *criar_no_while(NoArvore *condicao, NoArvore *bloco)
{
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));

    if (no == NULL)
    {
        fprintf(stderr, "Erro: Falha na alocação de memória para nó while\n");
        exit(1);
    }

    memset(no, 0, sizeof(NoArvore)); // Zera a struct

    no->tipo = NO_COMANDO_WHILE;
    no->info.comando_while.condicao = condicao;
    no->info.comando_while.bloco = bloco;
    no->proximo = NULL;
    return no;
}

NoArvore *criar_no_expressao(char *operador, NoArvore *esq, NoArvore *dir)
{
    NoArvore *no = malloc(sizeof(NoArvore));

    if (no == NULL)
    {
        fprintf(stderr, "Erro: Falha na alocação de memória para nó expressao\n");
        exit(1);
    }

    memset(no, 0, sizeof(NoArvore)); // Zera a struct
    no->tipo = NO_EXPRESSAO;

    // Evita strdup em operador nulo:
    if (operador)
    {
        no->info.expressao.operador = strdup(operador);
    }
    else
    {
        no->info.expressao.operador = NULL;
    }

    no->info.expressao.esquerda = esq;
    no->info.expressao.direita = dir;
    no->proximo = NULL;
    return no;
}

NoArvore *criar_no_chamada_func(char *nome, NoArvore *args)
{
    NoArvore *no = malloc(sizeof(NoArvore));

    if (no == NULL)
    {
        fprintf(stderr, "Erro: Falha na alocação de memória para nó chamada função\n");
        exit(1);
    }

    memset(no, 0, sizeof(NoArvore));
    no->tipo = NO_CHAMADA_FUNC;
    if (nome)
    {
        no->info.chamada_func.nome = strdup(nome);
    }
    else
    {
        no->info.chamada_func.nome = NULL;
    }
    no->info.chamada_func.argumentos = args;
    return no;
}

NoArvore *criar_no_identificador(char *nome, TipoVariavel tipo)
{
    NoArvore *no = malloc(sizeof(NoArvore));

    if (no == NULL)
    {
        fprintf(stderr, "Erro: Falha na alocação de memória para nó identificador\n");
        exit(1);
    }

    memset(no, 0, sizeof(NoArvore));
    no->tipo = NO_IDENTIFICADOR;
    if (nome)
    {
        no->info.identificador.nome = strdup(nome);
    }
    else
    {
        no->info.identificador.nome = NULL;
    }
    no->info.identificador.tipo = tipo;
    return no;
}

NoArvore *criar_no_literal(char *valor, TipoVariavel tipo)
{
    NoArvore *no = malloc(sizeof(NoArvore));

    if (no == NULL)
    {
        fprintf(stderr, "Erro: Falha na alocação de memória para nó literal\n");
        exit(1);
    }

    memset(no, 0, sizeof(NoArvore));
    no->tipo = NO_LITERAL;
    if (valor)
    {
        no->info.literal.valor = strdup(valor);
    }
    else
    {
        no->info.literal.valor = NULL;
    }
    no->info.literal.tipo = tipo;
    return no;
}

const char *tipoParaString(TipoVariavel tipo)
{
    switch (tipo)
    {
    case TIPO_INT:
        return "inteiro";
    case TIPO_FLOAT:
        return "real";
    case TIPO_CHAR:
        return "char";
    case TIPO_STRING:
        return "string";
    case TIPO_VETOR:
        return "vetor";
    case TIPO_FUNCAO:
        return "funcao";
    case TIPO_VOID:
        return "void";
    case TIPO_ERRO:
        return "erro";
    default:
        return "desconhecido";
    }
}

// Função para imprimir a árvore
void imprimir_arvore(NoArvore *no, FILE *arquivo, int nivel)
{
    // Verificação inicial de parâmetros
    if (no == NULL || arquivo == NULL || nivel < 0) {
        return;
    }

    // Imprime a indentação
    imprimir_indentacao(arquivo, nivel);

    switch (no->tipo) {
    case NO_PROGRAMA:
        fprintf(arquivo, "Programa\n");
        if (no->info.programa.corpo != NULL) {
            imprimir_arvore(no->info.programa.corpo, arquivo, nivel + 1);
        }
        break;

    case NO_DECLARACAO_VAR:
        fprintf(arquivo, "Declaração Variável: %s (tipo: %s)\n", 
            no->info.declaracao_var.nome ? no->info.declaracao_var.nome : "NULL",
            tipoParaString(no->info.declaracao_var.tipo));
        if (no->info.declaracao_var.valor != NULL) {
            imprimir_arvore(no->info.declaracao_var.valor, arquivo, nivel + 1);
        }
        break;

    case NO_DECLARACAO_FUNC:
        fprintf(arquivo, "Declaração Função: %s (retorno: %s)\n",
            no->info.declaracao_func.nome ? no->info.declaracao_func.nome : "NULL",
            tipoParaString(no->info.declaracao_func.tipo_retorno));
        if (no->info.declaracao_func.parametros != NULL) {
            imprimir_indentacao(arquivo, nivel + 1);
            fprintf(arquivo, "Parâmetros:\n");
            imprimir_arvore(no->info.declaracao_func.parametros, arquivo, nivel + 2);
        }
        if (no->info.declaracao_func.corpo != NULL) {
            imprimir_indentacao(arquivo, nivel + 1);
            fprintf(arquivo, "Corpo:\n");
            imprimir_arvore(no->info.declaracao_func.corpo, arquivo, nivel + 2);
        }
        break;

    case NO_COMANDO_IF:
        fprintf(arquivo, "If\n");
        if (no->info.comando_if.condicao != NULL) {
            imprimir_indentacao(arquivo, nivel + 1);
            fprintf(arquivo, "Condição:\n");
            imprimir_arvore(no->info.comando_if.condicao, arquivo, nivel + 2);
        }
        if (no->info.comando_if.bloco_then != NULL) {
            imprimir_indentacao(arquivo, nivel + 1);
            fprintf(arquivo, "Then:\n");
            imprimir_arvore(no->info.comando_if.bloco_then, arquivo, nivel + 2);
        }
        if (no->info.comando_if.bloco_else != NULL) {
            imprimir_indentacao(arquivo, nivel + 1);
            fprintf(arquivo, "Else:\n");
            imprimir_arvore(no->info.comando_if.bloco_else, arquivo, nivel + 2);
        }
        break;

    case NO_COMANDO_WHILE:
        fprintf(arquivo, "While\n");
        if (no->info.comando_while.condicao != NULL) {
            imprimir_indentacao(arquivo, nivel + 1);
            fprintf(arquivo, "Condição:\n");
            imprimir_arvore(no->info.comando_while.condicao, arquivo, nivel + 2);
        }
        if (no->info.comando_while.bloco != NULL) {
            imprimir_indentacao(arquivo, nivel + 1);
            fprintf(arquivo, "Corpo:\n");
            imprimir_arvore(no->info.comando_while.bloco, arquivo, nivel + 2);
        }
        break;

    case NO_EXPRESSAO:
        fprintf(arquivo, "Expressão: %s\n", 
            no->info.expressao.operador ? no->info.expressao.operador : "NULL");
        if (no->info.expressao.esquerda != NULL) {
            imprimir_arvore(no->info.expressao.esquerda, arquivo, nivel + 1);
        }
        if (no->info.expressao.direita != NULL) {
            imprimir_arvore(no->info.expressao.direita, arquivo, nivel + 1);
        }
        break;

    case NO_CHAMADA_FUNC:
        fprintf(arquivo, "Chamada Função: %s\n",
            no->info.chamada_func.nome ? no->info.chamada_func.nome : "NULL");
        if (no->info.chamada_func.argumentos != NULL) {
            imprimir_indentacao(arquivo, nivel + 1);
            fprintf(arquivo, "Argumentos:\n");
            imprimir_arvore(no->info.chamada_func.argumentos, arquivo, nivel + 2);
        }
        break;

    case NO_IDENTIFICADOR:
        fprintf(arquivo, "Identificador: %s (tipo: %s)\n",
            no->info.identificador.nome ? no->info.identificador.nome : "NULL",
            tipoParaString(no->info.identificador.tipo));
        break;

    case NO_LITERAL:
        fprintf(arquivo, "Literal: %s (tipo: %s)\n",
            no->info.literal.valor ? no->info.literal.valor : "NULL",
            tipoParaString(no->info.literal.tipo));
        break;

    case NO_BLOCO:
        fprintf(arquivo, "Bloco:\n");
        if (no->info.bloco.declaracoes != NULL) {
            imprimir_arvore(no->info.bloco.declaracoes, arquivo, nivel + 1);
        }
        break;

    case NO_ATRIBUICAO:
        fprintf(arquivo, "Atribuição:\n");
        if (no->info.atribuicao.alvo != NULL) {
            imprimir_arvore(no->info.atribuicao.alvo, arquivo, nivel + 1);
        }
        if (no->info.atribuicao.valor != NULL) {
            imprimir_arvore(no->info.atribuicao.valor, arquivo, nivel + 1);
        }
        break;

    default:
        fprintf(arquivo, "Warning: Tipo não reconhecido: %d\n", no->tipo);
        break;
    }

    // Imprime o próximo nó da lista (se houver)
    if (no->proximo != NULL) {
        imprimir_arvore(no->proximo, arquivo, nivel);
    }
}

// Função para liberar a memória da árvore
void liberar_arvore(NoArvore *no)
{
    if (no == NULL) {
        return;
    }

    // Primeiro libera o próximo nó na lista
    if (no->proximo != NULL) {
        liberar_arvore(no->proximo);
        no->proximo = NULL;
    }

    // Depois libera recursivamente todos os nós filhos
    switch (no->tipo) {
    case NO_DECLARACAO_VAR:
        if (no->info.declaracao_var.nome) {
            free(no->info.declaracao_var.nome);
            no->info.declaracao_var.nome = NULL;
        }
        if (no->info.declaracao_var.valor) {
            liberar_arvore(no->info.declaracao_var.valor);
            no->info.declaracao_var.valor = NULL;
        }
        break;

    case NO_DECLARACAO_FUNC:
        if (no->info.declaracao_func.nome) {
            free(no->info.declaracao_func.nome);
            no->info.declaracao_func.nome = NULL;
        }
        if (no->info.declaracao_func.parametros) {
            liberar_arvore(no->info.declaracao_func.parametros);
            no->info.declaracao_func.parametros = NULL;
        }
        if (no->info.declaracao_func.corpo) {
            liberar_arvore(no->info.declaracao_func.corpo);
            no->info.declaracao_func.corpo = NULL;
        }
        break;

    case NO_COMANDO_IF:
        if (no->info.comando_if.condicao) {
            liberar_arvore(no->info.comando_if.condicao);
            no->info.comando_if.condicao = NULL;
        }
        if (no->info.comando_if.bloco_then) {
            liberar_arvore(no->info.comando_if.bloco_then);
            no->info.comando_if.bloco_then = NULL;
        }
        if (no->info.comando_if.bloco_else) {
            liberar_arvore(no->info.comando_if.bloco_else);
            no->info.comando_if.bloco_else = NULL;
        }
        break;

    case NO_COMANDO_WHILE:
        if (no->info.comando_while.condicao) {
            liberar_arvore(no->info.comando_while.condicao);
            no->info.comando_while.condicao = NULL;
        }
        if (no->info.comando_while.bloco) {
            liberar_arvore(no->info.comando_while.bloco);
            no->info.comando_while.bloco = NULL;
        }
        break;

    case NO_EXPRESSAO:
        if (no->info.expressao.operador) {
            free(no->info.expressao.operador);
            no->info.expressao.operador = NULL;
        }
        if (no->info.expressao.esquerda) {
            liberar_arvore(no->info.expressao.esquerda);
            no->info.expressao.esquerda = NULL;
        }
        if (no->info.expressao.direita) {
            liberar_arvore(no->info.expressao.direita);
            no->info.expressao.direita = NULL;
        }
        break;

    case NO_CHAMADA_FUNC:
        if (no->info.chamada_func.nome) {
            free(no->info.chamada_func.nome);
            no->info.chamada_func.nome = NULL;
        }
        if (no->info.chamada_func.argumentos) {
            liberar_arvore(no->info.chamada_func.argumentos);
            no->info.chamada_func.argumentos = NULL;
        }
        break;

    case NO_IDENTIFICADOR:
        if (no->info.identificador.nome) {
            free(no->info.identificador.nome);
            no->info.identificador.nome = NULL;
        }
        break;

    case NO_LITERAL:
        if (no->info.literal.valor) {
            free(no->info.literal.valor);
            no->info.literal.valor = NULL;
        }
        break;

    case NO_PROGRAMA:
        if (no->info.programa.corpo) {
            liberar_arvore(no->info.programa.corpo);
            no->info.programa.corpo = NULL;
        }
        break;

    case NO_BLOCO:
        if (no->info.bloco.declaracoes) {
            liberar_arvore(no->info.bloco.declaracoes);
            no->info.bloco.declaracoes = NULL;
        }
        break;

    case NO_ATRIBUICAO:
        if (no->info.atribuicao.alvo) {
            liberar_arvore(no->info.atribuicao.alvo);
            no->info.atribuicao.alvo = NULL;
        }
        if (no->info.atribuicao.valor) {
            liberar_arvore(no->info.atribuicao.valor);
            no->info.atribuicao.valor = NULL;
        }
        break;
    }

    // Por fim, libera o próprio nó
    free(no);
}