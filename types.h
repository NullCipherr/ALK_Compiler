#ifndef TYPES_H
#define TYPES_H

// Estrutura para análise de tipos
typedef enum {
    TIPO_INT,
    TIPO_FLOAT,
    TIPO_CHAR,
    TIPO_STRING,
    TIPO_VOID,
    TIPO_ERRO
} TipoVariavel;

// Estrutura para identificadores
typedef struct {
    char* nome;
    TipoVariavel tipo;
} Identificador;

#endif // TYPES_H