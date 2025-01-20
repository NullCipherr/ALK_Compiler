#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

// Estrutura para parâmetros de função
typedef struct FuncParam
{
    char *nome;
    TipoVariavel tipo;
    struct FuncParam *proximo;
} FuncParam;

// Estrutura para entrada na tabela de símbolos
typedef struct SimboloEntrada
{
    char *nome;
    TipoVariavel tipo;
    char *escopo;
    union
    {
        int valor_int;
        float valor_float;
        char valor_char;
        char *valor_string;
        struct
        {
            TipoVariavel tipo_base;
            int tamanho;
        } vetor;
        struct
        {
            TipoVariavel tipo_retorno;
            FuncParam *parametros;
            int num_params;
        } funcao;
    } info;
    struct SimboloEntrada *proximo;
} SimboloEntrada;

// Estrutura principal do analisador semântico
typedef struct
{
    SimboloEntrada *tabela_simbolos;
    char *escopo_atual;
    int num_erros;
} AnalisadorSemantico;

// Funções principais
AnalisadorSemantico *iniciar_analisador_semantico(void);
void finalizar_analisador_semantico(AnalisadorSemantico *analisador);

// Funções de manipulação da tabela de símbolos
int inserir_simbolo(AnalisadorSemantico *analisador, const char *nome, TipoVariavel tipo);
int inserir_funcao(AnalisadorSemantico *analisador, const char *nome, TipoVariavel tipo_retorno);
int inserir_vetor(AnalisadorSemantico *analisador, const char *nome, TipoVariavel tipo_base, int tamanho);
int inserir_parametro(AnalisadorSemantico *analisador, const char *nome, TipoVariavel tipo);
void mudar_escopo(AnalisadorSemantico *analisador, const char *novo_escopo);
SimboloEntrada *buscar_simbolo(AnalisadorSemantico *analisador, const char *nome);
void registrar_parametros_funcao(AnalisadorSemantico *analisador, const char *nome_funcao, int num_params);

// Funções de verificação semântica
int verificar_declaracao(AnalisadorSemantico *analisador, const char *nome);
TipoVariavel verificar_tipos_operacao(AnalisadorSemantico *analisador, TipoVariavel tipo1, TipoVariavel tipo2, const char *operador);
int verificar_chamada_funcao(AnalisadorSemantico *analisador, const char *nome, int num_args);
int verificar_compatibilidade_tipos(AnalisadorSemantico *analisador, TipoVariavel tipo_destino, TipoVariavel tipo_origem, const char *contexto);

#endif // SEMANTIC_H
