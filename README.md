# TinySH

TinySH é uma shell simples escrita em C, desenvolvida como exercício prático para explorar programação de sistemas em Linux.

O foco do projeto é entender de forma profunda como funcionam os processos, sinais, redirecionamento de entrada e saída, e execução de comandos em baixo nível, usando apenas chamadas de sistema POSIX.

---

## Funcionalidades

- Execução de comandos externos (como `ls`, `echo`, `pwd`)
- Suporte a execução em segundo plano com `&`
- Tratamento de sinais (`SIGINT`, `SIGTSTP`)
- Redirecionamento de saída com `>` e `>>`

---

## O que está por vir

- Suporte a pipelines (`|`)
- Histórico de comandos
- Redirecionamento de entrada e stderr

---

## Estrutura do Projeto

```
tinysh/
├── src/
│   ├── main.c
│   ├── executor.c
│   ├── parser.c
│   └── redirection.c
├── include/
│   ├── executor.h
│   ├── parser.h
│   └── redirection.h
├── Makefile
└── README.md
```

---

## Compilação e uso

Para compilar:

```bash
make
```

Para rodar:

```bash
./tinysh
```

Exemplos de uso:

```bash
tinysh> echo Hello
tinysh> ls > out.txt
tinysh> sleep 2 &
tinysh> exit
```

---

## Desenvolvimento

O código é modularizado e comentado em inglês.  
Parsing é feito com `strtok`, com limite de até 127 argumentos.  
A função `parser` usa `strdup` internamente e libera a memória automaticamente.

Testes de vazamento de memória podem ser feitos com:

```bash
valgrind ./tinysh
```

---

## Roadmap

| Fase | Funcionalidade         | Status         |
|------|------------------------|----------------|
| 1    | Execução de comandos   | Feito          |
| 2    | Jobs em background     | Feito          |
| 3    | Tratamento de sinais   | Feito          |
| 4    | Redirecionamento de saída | Feito      |
| 5    | Pipelines              | Em andamento   |