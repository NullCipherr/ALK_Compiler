/*
 * Trabalho Prático – Parte 3
 * Disciplina: Compiladores
 * Aluno: Andrei Costa, Kananda Caroline, Leonardo Ribeiro Goulart
 *
 * Especificação: Implementação da análise semântica para o compilador.
 * Esta etapa realiza a verificação de tipos e escopo das construções da linguagem.
 *
 * 1. **Tipos de Dados**:
 *    - Implementado: Verifica e valida os tipos básicos da linguagem:
 *      - Inteiros (int)
 *      - Reais (float)
 *      - Caracteres (char)
 *      - Strings (string)
 *    - Implementado: Verifica compatibilidade em operações e atribuições
 *
 * 2. **Estruturas de Decisão**:
 *    - Implementado: Verifica expressões condicionais em comandos 'check'
 *    - Implementado: Garante que condições resultem em valores booleanos
 *
 * 3. **Estruturas de Repetição**:
 *    - Implementado: Verifica expressões em laços 'repeat while'
 *    - Implementado: Valida condições de parada
 *
 * 4. **Vetores**:
 *    - Implementado: Verifica declarações de vetores:
 *      - Validação de índices
 *      - Verificação de tipos em acessos
 *      - Controle de limites
 *
 * 5. **Funções**:
 *    - Implementado: Gerencia chamadas de funções:
 *      - Verificação de parâmetros
 *      - Compatibilidade de tipos de retorno
 *      - Controle de escopo
 *    - Implementado: Empilhamento e desempilhamento de contextos
 *
 * 6. **Funções Básicas**:
 *    - Implementado: Suporte a funções built-in:
 *      - print: Saída formatada
 *      - scan: Entrada de dados
 *    - Implementado: Verificação de tipos para argumentos
 *
 * Observações:
 * - A análise semântica trabalha em conjunto com a tabela de símbolos
 * - Erros semânticos são reportados com mensagens detalhadas
 * - O controle de escopo permite variáveis locais e globais
 * - A verificação de tipos previne operações inválidas
 */

#include "semantic.h"

AnalisadorSemantico *iniciar_analisador_semantico(void)
{
    AnalisadorSemantico *analisador = (AnalisadorSemantico *)malloc(sizeof(AnalisadorSemantico));
    if (analisador == NULL)
    {
        fprintf(stderr, "Erro: Falha na alocação do analisador semântico\n");
        exit(1);
    }

    analisador->tabela_simbolos = NULL;
    analisador->escopo_atual = strdup("global");
    analisador->num_erros = 0;

    // Inserir funções built-in
    inserir_funcao(analisador, "print", TIPO_VOID);
    inserir_funcao(analisador, "scan", TIPO_VOID);

    return analisador;
}

void finalizar_analisador_semantico(AnalisadorSemantico *analisador)
{
    if (analisador == NULL)
        return;

    // Liberar tabela de símbolos
    SimboloEntrada *atual = analisador->tabela_simbolos;
    while (atual != NULL)
    {
        SimboloEntrada *proximo = atual->proximo;
        free(atual->nome);
        free(atual->escopo);
        if (atual->tipo == TIPO_STRING)
        {
            free(atual->info.valor_string);
        }
        free(atual);
        atual = proximo;
    }

    free(analisador->escopo_atual);
    free(analisador);
}

int inserir_simbolo(AnalisadorSemantico *analisador, const char *nome, TipoVariavel tipo)
{
    if (buscar_simbolo(analisador, nome) != NULL)
    {
        printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
        printf("║ Símbolo '%s' já declarado no escopo '%s'              ║\n",
               nome, analisador->escopo_atual);
        printf("╚═══════════════════════════════════════════════════════╝\n");
        analisador->num_erros++;
        return 0;
    }

    SimboloEntrada *novo = (SimboloEntrada *)malloc(sizeof(SimboloEntrada));
    novo->nome = strdup(nome);
    novo->tipo = tipo;
    novo->escopo = strdup(analisador->escopo_atual);
    novo->proximo = analisador->tabela_simbolos;
    analisador->tabela_simbolos = novo;

    return 1;
}

TipoVariavel verificar_tipos_operacao(AnalisadorSemantico *analisador, TipoVariavel tipo1, TipoVariavel tipo2, const char *operador)
{
    // Verificação de compatibilidade de tipos
    if (tipo1 == TIPO_STRING || tipo2 == TIPO_STRING)
    {
        if (strcmp(operador, "plus") == 0)
        {
            return TIPO_STRING; // Concatenação de strings
        }
        printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
        printf("║ Operação '%s' inválida para strings                   ║\n", operador);
        printf("╚═══════════════════════════════════════════════════════╝\n");
        analisador->num_erros++;
        return TIPO_ERRO;
    }

    // Regras de coerção de tipos
    if (tipo1 == TIPO_FLOAT || tipo2 == TIPO_FLOAT)
    {
        return TIPO_FLOAT;
    }

    return TIPO_INT;
}

SimboloEntrada *buscar_simbolo(AnalisadorSemantico *analisador, const char *nome)
{
    SimboloEntrada *atual = analisador->tabela_simbolos;

    // Primeiro procura no escopo atual
    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0 &&
            strcmp(atual->escopo, analisador->escopo_atual) == 0)
        {
            return atual;
        }
        atual = atual->proximo;
    }

    // Se não encontrou no escopo atual, procura no escopo global
    atual = analisador->tabela_simbolos;
    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0 &&
            strcmp(atual->escopo, "global") == 0)
        {
            return atual;
        }
        atual = atual->proximo;
    }

    return NULL;
}

int verificar_chamada_funcao(AnalisadorSemantico *analisador, const char *nome, int num_args)
{
    SimboloEntrada *func = buscar_simbolo(analisador, nome);
    if (func == NULL || func->tipo != TIPO_FUNCAO)
    {
        printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
        printf("║ Função '%s' não declarada                             ║\n", nome);
        printf("╚═══════════════════════════════════════════════════════╝\n");
        analisador->num_erros++;
        return 0;
    }

    // Verificar número de argumentos
    if (func->info.funcao.num_params != num_args)
    {
        printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
        printf("║ Número incorreto de argumentos para função '%s'       ║\n", nome);
        printf("║ Esperado: %d, Recebido: %d                           ║\n",
               func->info.funcao.num_params, num_args);
        printf("╚═══════════════════════════════════════════════════════╝\n");
        analisador->num_erros++;
        return 0;
    }

    return 1;
}

int inserir_funcao(AnalisadorSemantico *analisador, const char *nome, TipoVariavel tipo_retorno)
{
    // Primeiro insere a função no escopo global
    SimboloEntrada *novo = (SimboloEntrada *)malloc(sizeof(SimboloEntrada));
    novo->nome = strdup(nome);
    novo->tipo = TIPO_FUNCAO;
    novo->escopo = strdup("global");
    novo->info.funcao.tipo_retorno = tipo_retorno;
    novo->info.funcao.parametros = NULL;
    novo->info.funcao.num_params = 0;
    novo->proximo = analisador->tabela_simbolos;
    analisador->tabela_simbolos = novo;

    // Muda para o escopo da função
    char escopo_funcao[256];
    snprintf(escopo_funcao, sizeof(escopo_funcao), "funcao_%s", nome);
    mudar_escopo(analisador, escopo_funcao);

    return 1;
}

int inserir_vetor(AnalisadorSemantico *analisador, const char *nome, TipoVariavel tipo_base, int tamanho)
{
    // Verificar se o tamanho é válido
    if (tamanho <= 0)
    {
        printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
        printf("║ Tamanho inválido para vetor '%s'                      ║\n", nome);
        printf("║ Tamanho deve ser maior que zero                       ║\n");
        printf("╚═══════════════════════════════════════════════════════╝\n");
        analisador->num_erros++;
        return 0;
    }

    // Verificar se já existe
    if (buscar_simbolo(analisador, nome) != NULL)
    {
        printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
        printf("║ Vetor '%s' já declarado                               ║\n", nome);
        printf("╚═══════════════════════════════════════════════════════╝\n");
        analisador->num_erros++;
        return 0;
    }

    SimboloEntrada *novo = (SimboloEntrada *)malloc(sizeof(SimboloEntrada));
    if (novo == NULL)
    {
        return 0;
    }

    novo->nome = strdup(nome);
    novo->tipo = TIPO_VETOR;
    novo->escopo = strdup(analisador->escopo_atual);
    novo->info.vetor.tipo_base = tipo_base;
    novo->info.vetor.tamanho = tamanho;
    novo->proximo = analisador->tabela_simbolos;
    analisador->tabela_simbolos = novo;

    return 1;
}

// Função para mudar o escopo
void mudar_escopo(AnalisadorSemantico *analisador, const char *novo_escopo)
{
    if (analisador->escopo_atual != NULL)
    {
        free(analisador->escopo_atual);
    }
    analisador->escopo_atual = strdup(novo_escopo);
}

// Função para inserir parâmetro
int inserir_parametro(AnalisadorSemantico *analisador, const char *nome, TipoVariavel tipo)
{
    SimboloEntrada *novo = (SimboloEntrada *)malloc(sizeof(SimboloEntrada));
    if (novo == NULL)
    {
        return 0;
    }

    novo->nome = strdup(nome);
    novo->tipo = tipo;
    novo->escopo = strdup(analisador->escopo_atual);
    novo->proximo = analisador->tabela_simbolos;
    analisador->tabela_simbolos = novo;

    return 1;
}

// Adicionar esta função para registrar os parâmetros da função
void registrar_parametros_funcao(AnalisadorSemantico *analisador, const char *nome_funcao, int num_params)
{
    SimboloEntrada *func = buscar_simbolo(analisador, nome_funcao);
    if (func != NULL && func->tipo == TIPO_FUNCAO)
    {
        func->info.funcao.num_params = num_params;
    }
}

// Função para verificar compatibilidade de tipos em atribuição
int verificar_compatibilidade_tipos(AnalisadorSemantico *analisador, TipoVariavel tipo_destino, TipoVariavel tipo_origem, const char *contexto)
{
    if (analisador == NULL)
    {
        printf("Erro: analisador é NULL\n");
        return 0; // Retorna erro se analisador for NULL
    }

    // Adicionando log para verificar os tipos
    // printf("Verificando compatibilidade: destino = %d, origem = %d, contexto = %s\n", tipo_destino, tipo_origem, contexto);

    if (tipo_destino == tipo_origem)
    {
        return 1; // Tipos iguais, OK
    }

    // Verificações específicas para cada tipo
    switch (tipo_destino)
    {
    case TIPO_CHAR:
        if (tipo_origem == TIPO_STRING)
        {
            printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
            printf("║ Não é possível atribuir string para char              ║\n");
            printf("║ Contexto: %s                                          ║\n", contexto);
            printf("╚═══════════════════════════════════════════════════════╝\n");
            analisador->num_erros++;
            return 0;
        }
        break;

    case TIPO_INT:
        if (tipo_origem == TIPO_STRING)
        {
            printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
            printf("║ Não é possível atribuir string para int               ║\n");
            printf("║ Contexto: %s                                          ║\n", contexto);
            printf("╚═══════════════════════════════════════════════════════╝\n");
            analisador->num_erros++;
            return 0;
        }
        break;

    case TIPO_FLOAT:
        if (tipo_origem == TIPO_STRING)
        {
            printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
            printf("║ Não é possível atribuir string para float             ║\n");
            printf("║ Contexto: %s                                          ║\n", contexto);
            printf("╚═══════════════════════════════════════════════════════╝\n");
            analisador->num_erros++;
            return 0;
        }
        break;

    case TIPO_STRING:
        // String pode receber apenas string
        if (tipo_origem != TIPO_STRING)
        {
            printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
            printf("║ Tipo incompatível na atribuição para string           ║\n");
            printf("║ Contexto: %s                                          ║\n", contexto);
            printf("╚═══════════════════════════════════════════════════════╝\n");
            analisador->num_erros++;
            return 0;
        }
        break;

    case TIPO_VOID:
        printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
        printf("║ Não é possível atribuir valor para tipo void           ║\n");
        printf("║ Contexto: %s                                           ║\n", contexto);
        printf("╚═══════════════════════════════════════════════════════╝\n");
        analisador->num_erros++;
        return 0;

    case TIPO_FUNCAO:
        printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
        printf("║ Não é possível atribuir valor para função              ║\n");
        printf("║ Contexto: %s                                           ║\n", contexto);
        printf("╚═══════════════════════════════════════════════════════╝\n");
        analisador->num_erros++;
        return 0;

    case TIPO_VETOR:
        printf("\n╔═══════════════════ ERRO SEMÂNTICO ═══════════════════╗\n");
        printf("║ Não é possível atribuir valor diretamente para vetor   ║\n");
        printf("║ Contexto: %s                                           ║\n", contexto);
        printf("╚═══════════════════════════════════════════════════════╝\n");
        analisador->num_erros++;
        return 0;

    case TIPO_ERRO:
        return 0; // Já houve erro anterior
    }

    return 0; // Tipos incompatíveis
}
