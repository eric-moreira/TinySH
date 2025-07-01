# TinySH

TinySH is a simple shell written in C, developed as a practical exercise to explore system programming on Linux.

The project's focus is to deeply understand how processes, signals, input/output redirection, and command execution work at a low level, using only POSIX system calls.

---

## Features

- Execution of external commands (such as `ls`, `echo`, `pwd`)
- Support for background execution with `&`
- Signal handling (`SIGINT`, `SIGTSTP`)
- Output redirection with `>` and `>>`

---

## Upcoming Features

- All done for now.

---

## Project Structure

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

## Compilation and Usage

To compile:

```bash
make
```

To run:

```bash
./tinysh
```

Usage examples:

```bash
tinysh> echo Hello
tinysh> ls > out.txt
tinysh> sleep 2 &
tinysh> exit
```

---

## Development

The code is modularized and commented in English.  
Parsing is done with `strtok`, with a limit of up to 127 arguments.  
The `parser` function uses `strdup` internally and frees memory automatically.



---

## Roadmap

| Phase | Feature                  | Status        |
|-------|--------------------------|---------------|
| 1     | Command execution        | Done          |
| 2     | Background jobs          | Done          |
| 3     | Signal handling          | Done          |
| 4     | Output redirection       | Done          |
| 5     | Pipelines                | Done          |