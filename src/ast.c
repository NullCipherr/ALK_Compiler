#include <stdio.h>
#include <stdint.h>
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

// Implementação das funções de criação de nós
NoArvore *criar_no_programa(NoArvore *corpo)
{
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));
    if (no == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para nó programa\n");
        exit(1);
    }

    memset(no, 0, sizeof(NoArvore));
    no->tipo = NO_PROGRAMA;
    no->info.programa.corpo = corpo;
    no->proximo = NULL;

    return no;
}

NoArvore *criar_no_declaracao_var(char *nome, TipoVariavel tipo, NoArvore *valor)
{
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));
    if (no == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para nó declaracao var\n");
        exit(1);
    }

    // Inicializa toda a estrutura com zeros
    memset(no, 0, sizeof(NoArvore));
    no->tipo = NO_DECLARACAO_VAR;
    
    if (nome != NULL) {
        size_t tamanho_nome = strlen(nome) + 1; // +1 para o caractere nulo '\0'
        no->info.declaracao_var.nome = (char *)malloc(tamanho_nome);
        if (no->info.declaracao_var.nome == NULL) {
            fprintf(stderr, "Erro: Falha ao duplicar string.\n");
            free(no);
            exit(1);
        }
    }
    
    no->info.declaracao_var.tipo = tipo;
    no->info.declaracao_var.valor = valor;
    no->proximo = NULL;

    // Verificação adicional
    if (no->tipo != NO_DECLARACAO_VAR) {
        fprintf(stderr, "Erro: Tipo do nó foi corrompido após inicialização (%d)\n", no->tipo);
        liberar_arvore(no);
        exit(1);
    }

    return no;
}

NoArvore *criar_no_declaracao_func(char *nome, TipoVariavel tipo_retorno, NoArvore *params, NoArvore *corpo)
{
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));
    if (no == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para nó declaracao função\n");
        exit(1);
    }

    memset(no, 0, sizeof(NoArvore));
    no->tipo = NO_DECLARACAO_FUNC;
    
    if (nome != NULL) {
        no->info.declaracao_func.nome = strdup(nome);
        if (no->info.declaracao_func.nome == NULL) {
            fprintf(stderr, "Erro: Falha ao duplicar nome da função\n");
            free(no);
            exit(1);
        }
    }

    no->info.declaracao_func.tipo_retorno = tipo_retorno;
    
    // Verifica se os parâmetros são válidos
    if (params != NULL && (uintptr_t)params > 1000) {
        no->info.declaracao_func.parametros = params;
    }
    
    // Verifica se o corpo é válido
    if (corpo != NULL && (uintptr_t)corpo > 1000) {
        no->info.declaracao_func.corpo = corpo;
    }
    
    no->proximo = NULL;
    return no;
}

NoArvore *criar_no_if(NoArvore *condicao, NoArvore *bloco_then, NoArvore *bloco_else)
{
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));
    if (no == NULL) {
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

NoArvore *criar_no_expressao(char *operador, NoArvore *esquerda, NoArvore *direita)
{
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));
    if (no == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para nó expressão\n");
        exit(1);
    }

    // Inicializa toda a estrutura com zeros
    memset(no, 0, sizeof(NoArvore));
    no->tipo = NO_EXPRESSAO;
    
    // Copia o operador se fornecido
    if (operador != NULL) {
        size_t tamanho_operador = strlen(operador) + 1; // +1 para o caractere nulo '\0'
        no->info.expressao.operador = (char *)malloc(tamanho_operador);
        if (no->info.expressao.operador == NULL) {
            fprintf(stderr, "Erro: Falha ao duplicar operador\n");
            free(no);
            exit(1);
        }
        strcpy(no->info.expressao.operador, operador);
    }

    no->info.expressao.esquerda = esquerda;
    no->info.expressao.direita = direita;
    no->proximo = NULL;

    return no;
}

NoArvore *criar_no_chamada_func(char *nome, NoArvore *args)
{
    NoArvore *no = malloc(sizeof(NoArvore));
    if (no == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para nó chamada função\n");
        // Liberar args antes de sair em caso de erro
        if (args) liberar_arvore(args);
        exit(1);
    }

    memset(no, 0, sizeof(NoArvore));
    no->tipo = NO_CHAMADA_FUNC;
    
    if (nome) {
        no->info.chamada_func.nome = strdup(nome);
        if (no->info.chamada_func.nome == NULL) {
            fprintf(stderr, "Erro: Falha ao duplicar nome da função\n");
            free(no);
            if (args) liberar_arvore(args);
            exit(1);
        }
    }else {
        no->info.chamada_func.nome = NULL;
    }
    
    no->info.chamada_func.argumentos = args;
    no->proximo = NULL;
    return no;
}

NoArvore *criar_no_identificador(char *nome, TipoVariavel tipo)
{
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));
    if (no == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para nó identificador\n");
        exit(1);
    }

    // Inicializa toda a estrutura com zeros
    memset(no, 0, sizeof(NoArvore));

    no->tipo = NO_IDENTIFICADOR;
    
    // Copia o nome se fornecido
    if (nome != NULL) {
        no->info.identificador.nome = strdup(nome);
        if (no->info.identificador.nome == NULL) {
            fprintf(stderr, "Erro: Falha ao duplicar nome do identificador\n");
            free(no);
            exit(1);
        }
    }

    // Define o tipo da variável
    no->info.identificador.tipo = tipo;
    no->proximo = NULL;

    return no;
}

NoArvore *criar_no_literal(char *valor, TipoVariavel tipo)
{
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));
    if (no == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para nó literal\n");
        exit(1);
    }

    // Inicializa toda a estrutura com zeros
    memset(no, 0, sizeof(NoArvore));

    no->tipo = NO_LITERAL;
    
    // Copia o valor se fornecido
    if (valor != NULL) {
        no->info.literal.valor = strdup(valor);
        if (no->info.literal.valor == NULL) {
            fprintf(stderr, "Erro: Falha ao duplicar valor literal\n");
            free(no);
            exit(1);
        }
    }

    no->info.literal.tipo = tipo;
    no->proximo = NULL;

    return no;
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

    // Verificar se o tipo do nó é válido antes de acessar
    if (no->tipo < NO_PROGRAMA || no->tipo > NO_ATRIBUICAO) {
        fprintf(arquivo, "Erro: Tipo de nó inválido (%d)\n", no->tipo);
        return;
    }

    // Salva o tipo localmente para evitar acessos inválidos
    TipoNo tipo = no->tipo;

    switch (tipo) {
    case NO_DECLARACAO_VAR:
        fprintf(arquivo, "Declaração Variável: %s (tipo: %s)\n", 
            no->info.declaracao_var.nome ? no->info.declaracao_var.nome : "(null)",
            tipoParaString(no->info.declaracao_var.tipo));
        if (no->info.declaracao_var.valor != NULL) {
            imprimir_arvore(no->info.declaracao_var.valor, arquivo, nivel + 1);
        }
        break;

    case NO_DECLARACAO_FUNC:
        fprintf(arquivo, "Declaração Função: %s (retorno: %s)\n",
            no->info.declaracao_func.nome ? no->info.declaracao_func.nome : "(null)",
            tipoParaString(no->info.declaracao_func.tipo_retorno));
        
        // Verificar ponteiros antes de acessar
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
        fprintf(arquivo, "Tipo de nó desconhecido: %d\n", no->tipo);
        break;
    }

    // Verificar próximo nó antes de tentar acessá-lo
    if (no->proximo != NULL) {
        imprimir_arvore(no->proximo, arquivo, nivel);
    }
}

// Função para liberar a árvore
void liberar_arvore(NoArvore *no)
{
    // Verificação básica de ponteiro nulo
    if (no == NULL) {
        printf("Nó é NULL, nada a liberar.\n");
        return;
    }

    // Guardamos o próximo nó antes de qualquer operação
    NoArvore *proximo = no->proximo;
    
    // Validar o tipo do nó antes de acessar a união
    if (no->tipo < NO_PROGRAMA || no->tipo > NO_ATRIBUICAO) {

        free(no);
        liberar_arvore(proximo);  // Liberar o próximo nó
        return;
    }

    // Agora podemos proceder com a liberação baseada no tipo
    switch (no->tipo) {
        case NO_PROGRAMA:
            // Liberamos primeiro as estruturas filhas
            if (no->info.programa.corpo) {
                printf("Liberando corpo do programa\n");
                liberar_arvore(no->info.programa.corpo);
            }else{
                printf("Corpo do programa é NULL\n");
            }
            break;

        case NO_DECLARACAO_VAR:
            if (no->info.declaracao_var.valor) {
                printf("Liberando valor da declaração de variável\n");
                liberar_arvore(no->info.declaracao_var.valor);
            }
            if (no->info.declaracao_var.nome) {
                printf("Liberando nome da declaração de variável\n");
                free(no->info.declaracao_var.nome); // Removido check de null
            }
            break;

        case NO_DECLARACAO_FUNC:
            if (no->info.declaracao_func.corpo) {
                printf("Liberando corpo da declaração de função\n");
                liberar_arvore(no->info.declaracao_func.corpo);
            }
            if (no->info.declaracao_func.parametros) {
                printf("Liberando parâmetros da declaração de função\n");
                liberar_arvore(no->info.declaracao_func.parametros);
            }
            if (no->info.declaracao_func.nome) {
                printf("Liberando nome da declaração de função\n");
                free(no->info.declaracao_func.nome); // Removido check de null
            }
            break;

        case NO_COMANDO_IF:
            if (no->info.comando_if.bloco_else) {
                printf("Liberando bloco ELSE do comando IF.\n");
                NoArvore *else_bloco = no->info.comando_if.bloco_else;
                no->info.comando_if.bloco_else = NULL;
                liberar_arvore(else_bloco);
            }else {
                printf("Bloco ELSE do comando IF é NULL.\n");
            }
            if (no->info.comando_if.bloco_then) {
                printf("Liberando bloco THEN do comando IF.\n");
                NoArvore *then_bloco = no->info.comando_if.bloco_then;
                no->info.comando_if.bloco_then = NULL;
                liberar_arvore(then_bloco);
            }else {
                printf("Bloco THEN do comando IF é NULL.\n");
            }

            if (no->info.comando_if.condicao) {
                printf("Liberando condição do comando IF.\n");
                NoArvore *cond = no->info.comando_if.condicao;
                no->info.comando_if.condicao = NULL;
                liberar_arvore(cond);
            }else {
                printf("Condição do comando IF é NULL.\n");
            }

            break;

        case NO_COMANDO_WHILE:
            if (no->info.comando_while.bloco) {
                printf("Liberando bloco do comando WHILE.\n");
                NoArvore *bloco = no->info.comando_while.bloco;
                no->info.comando_while.bloco = NULL;
                liberar_arvore(bloco);
            }else {
                printf("Bloco do comando WHILE é NULL.\n");
            }
            if (no->info.comando_while.condicao) {
                printf("Liberando condição do comando WHILE.\n");
                NoArvore *cond = no->info.comando_while.condicao;
                no->info.comando_while.condicao = NULL;
                liberar_arvore(cond);
            }else {
                printf("Condição do comando WHILE é NULL.\n");
            }
            break;

        case NO_EXPRESSAO:
            if (no->info.expressao.direita) {
                printf("Liberando subárvore direita da expressão.\n");
                liberar_arvore(no->info.expressao.direita);
            }else {
                printf("Subárvore direita da expressão é NULL.\n");
            }
            
            if (no->info.expressao.esquerda) {
                printf("Liberando subárvore esquerda da expressão.\n");
                liberar_arvore(no->info.expressao.esquerda);
            }else {
                printf("Subárvore esquerda da expressão é NULL.\n");
            }
            
            if (no->info.expressao.operador) {
                printf("Liberando operador da expressão.\n");
                free(no->info.expressao.operador);
            } else {
                printf("Operador da expressão é NULL.\n");
            }

            break;

        case NO_CHAMADA_FUNC:
            if (no->info.chamada_func.argumentos) {
                printf("Liberando argumentos da chamada de função.\n");
                liberar_arvore(no->info.chamada_func.argumentos);
            }else {
                printf("Argumentos da chamada de função são NULL.\n");
            }

            if (no->info.chamada_func.nome) {
                printf("Liberando nome da função chamada.\n");
                free(no->info.chamada_func.nome);
                no->info.chamada_func.nome = NULL;
            }else {
                printf("Nome da função chamada é NULL.\n");
            }

            break;

        case NO_IDENTIFICADOR:
            if (no->info.identificador.nome) {
                printf("Liberando nome do identificador.\n");
                free(no->info.identificador.nome);
            } else {
                printf("Nome do identificador é NULL.\n");
            }
            break;

         case NO_LITERAL:
            if (no->info.literal.valor) {
                printf("Liberando valor do literal.\n");
                free(no->info.literal.valor);
            } else {
                printf("Valor do literal é NULL.\n");
            }
            break;

        case NO_BLOCO:
            if (no->info.bloco.declaracoes) {
                printf("Liberando declarações do bloco.\n");
                liberar_arvore(no->info.bloco.declaracoes);
            } else {
                printf("Declarações do bloco são NULL.\n");
            }
            break;

        case NO_ATRIBUICAO:
            if (no->info.atribuicao.valor) {
                printf("Liberando valor da atribuição.\n");
                liberar_arvore(no->info.atribuicao.valor);
            } else {
                printf("Valor da atribuição é NULL.\n");
            }
            if (no->info.atribuicao.alvo) {
                printf("Liberando alvo da atribuição.\n");
                liberar_arvore(no->info.atribuicao.alvo);
            } else {
                printf("Alvo da atribuição é NULL.\n");
            }
            break;
    }

    // Liberamos o nó atual
    printf("Liberando o nó atual.\n");
    free(no);

    // Liberamos o próximo nó
    if (proximo) {
        printf("Liberando próximo nó.\n");
        liberar_arvore(proximo);
    }else{
        printf("Proximo é NULL\n") ;
    }
}

// Função para criar um nó de bloco
NoArvore *criar_no_bloco(NoArvore *declaracoes) {
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));
    if (no == NULL) {
        return NULL; // Falha na alocação de memória
    }
    no->tipo = NO_BLOCO;
    no->info.bloco.declaracoes = declaracoes;
    no->proximo = NULL;
    return no;
}

// Função para criar um nó de atribuição
NoArvore *criar_no_atribuicao(NoArvore *alvo, NoArvore *valor) {
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));
    if (no == NULL) {
        return NULL; // Falha na alocação de memória
    }
    no->tipo = NO_ATRIBUICAO;
    no->info.atribuicao.alvo = alvo;
    no->info.atribuicao.valor = valor;
    no->proximo = NULL;
    return no;
}