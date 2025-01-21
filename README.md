# Compilador ALK

Um compilador simples desenvolvido para a disciplina de Compiladores da UEM, implementando análise léxica, sintática e semântica.

## Funcionalidades

O compilador implementa as seguintes funcionalidades:

### Tipos de Dados

- Suporte para tipos básicos: int, float, char e string
- Vetores de tipos básicos
- Verificação de tipos em operações e atribuições

### Estruturas de Controle

- Estrutura condicional check/then/otherwise (equivalente ao if/else)
- Estrutura de repetição repeat while (equivalente ao while)

### Funções

- Declaração e chamada de funções
- Parâmetros e retorno de valores
- Verificação de tipos dos argumentos
- Funções built-in: print e scan

### Escopo

- Suporte para escopo global e local
- Verificação de variáveis declaradas
- Controle de visibilidade de variáveis

## Pré-requisitos

ara compilar e executar o projeto, você precisa ter instalado:

```bash
sudo apt install flex bison
```

## Compilação

Para compilar o projeto, utilize:

```bash
make
```

Para executar o compilador:

```bash
make run
```

Ou diretamente:

```bash
./bin/compilador
```

Para limpar os arquivos gerados:

```bash
make clean
```

## Estrutura do projeto

    ├── src/             # Código fonte
    │   ├── ast.c/h      # Implementação da árvore sintática abstrata
    │   ├── bison.y      # Gramática e análise sintática
    │   ├── flex.l       # Análise léxica
    │   ├── semantic.c/h # Análise semântica
    │   └── types.h      # Definições de tipos
    ├── tests/           # Arquivos de teste
    ├── build/           # Arquivos intermediários de compilação
    ├── bin/             # Executável gerado
    └── makefile         # Script de compilação

## Exemplos de Código

### Declaração de Variáveis

    create int x as 10;
    create float pi as 3.14;
    create string msg as "Hello";
    create int vetor[5] as array;

### Estruturas de Controle

    check (x is_greater_than 0) then {
        print("Positivo");
    } otherwise {
        print("Não positivo");
    }

    repeat while (i is_less_than 10) {
        print(i);
        i = i plus 1;
    }

### Funções

    function int soma(int a, int b) {
        give back a plus b;
    }

    function void imprimir(string msg) {
        print(msg);
    }

## Testes

O diretório tests contém diversos arquivos de teste que demonstram as funcionalidades do compilador:

- teste_tipos.txt: Testes de tipos e conversões
- teste_escopo.txt: Testes de escopo de variáveis
- teste_funcoes.txt: Testes de funções e chamadas
- teste_semantico_correto.txt: Exemplos de código semanticamente correto
- teste_semantico_erros.txt: Exemplos de erros semânticos

## Contribuição

Contribuições são bem-vindas! Para contribuir:

1. **Fork** este repositório.
2. Crie um branch para suas alterações: `git checkout -b feature/nova-funcionalidade`.
3. Envie suas alterações: `git push origin feature/nova-funcionalidade`.
4. Abra um **Pull Request**.

## Autores

- Andrei Costa
- Kananda Caroline
- Leonardo Ribeiro Goulart

## Licença

Este projeto é licenciado sob a licença MIT.
