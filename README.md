# C_Compiler

Um compilador simples para a linguagem C, desenvolvido para realizar análise léxica e sintática de programas, gerando e exibindo uma árvore sintática representando a estrutura do código. Este projeto é ideal para estudos de compiladores e linguagens formais.

## Funcionalidades
Atualmente, o compilador implementa as seguintes capacidades:

- Tipos de Dados: Reconhece e manipula variáveis dos tipos int, float, char e string.
- Vetores: Suporte ao reconhecimento e manipulação de vetores.
- Estruturas de Decisão: Reconhecimento e manipulação de pelo menos uma estrutura de decisão (if, switch ou equivalente).
- Estruturas de Repetição: Reconhecimento e manipulação de pelo menos uma estrutura de repetição (for, while ou equivalente).
- Palavras Reservadas e Funções Reservadas: Identificação e manipulação de palavras-chave e funções reservadas.
- Sub-rotinas: Suporte para chamadas de sub-rotinas, excluindo a função main.

## Análise Léxica
- Recebe como entrada a sequência de tokens gerada pela análise léxica.
- Reconhece e manipula corretamente os tokens identificados.

## Análise Sintática
- Gera uma Árvore Sintática, lida por meio da análise sintática (descendente ou ascendente).
- Apresenta a árvore sintática como saída do processo.

## Pré-requisitos

Para compilar e executar este projeto, você precisará instalar as seguintes dependências:

```bash
sudo apt install flex bison 
```

## Compilação

Para compilar o projeto, utilize:

```bash
make
```

## Testes

### Teste do Analisador Léxico
Verifica a extração de tokens do código de entrada:

```bash
make test-lex
```

### Teste do Analisador Sintático
Gera e exibe a árvore sintática com base na sequência de tokens:

```bash
make test-bison
```

### Limpeza
Para remover arquivos temporários e binários gerados:

```bash
make clean
```

## Contribuição
Contribuições são bem-vindas! Para contribuir:

1. Fork este repositório.
2. Crie um branch para suas alterações: git checkout -b feature/nova-funcionalidade.
3. Envie suas alterações: git push origin feature/nova-funcionalidade.
4. Abra um Pull Request.

## Licença
Este projeto é licenciado sob a licença MIT. Consulte o arquivo LICENSE para mais detalhes.
