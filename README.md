# 🐚 Tiny Shell (TinySH) – A Minimalist Shell in C

### 📌 Description

TinySH is a **minimalist shell written in C**, designed to practice **Linux system programming**, focusing on:

- Process management (fork, exec, waitpid)
- Command line parsing
- Basic process execution control
- Standard terminal I/O

This is the **first step** of an incremental project to build a functional shell.

---

### ✅ Features Implemented (Phase 1)

- Execution of external commands like `ls`, `pwd`, `echo`, etc.
- Interactive command reading loop
- Built-in command: `exit` to terminate the shell
- Simple argument parsing (space-split)
- Background execution (`command &`)
- Signal handling (`SIGINT`, `SIGTSTP`, etc.)

---

### 🚧 Upcoming Features (Next Phases)

- Output redirection (`>`)
- Pipelines (`ls | grep foo`)
- Command history

---

### 📂 Project Structure

```
tiny_shell/
├── src/
│   ├── main.c
│   └── executor.c
├── include/
│   └── executor.h
├── Makefile
└── README.md
```
---

### 🛠️ How to Build

Requirements:

- GCC
- Linux or POSIX-compliant environment

Commands:
```
(make)
```
This will generate the `tinysh` executable.

---

### ▶️ How to Use

Run the shell:

```
(./tinysh)

Usage examples:

(tinysh> ls)
(tinysh> echo Hello World)
(tinysh> pwd)
(tinysh> exit)
```
---

### 💡 System Programming Concepts Used

- **Fork/Exec:** Process creation
- **Waitpid:** Process synchronization and control
- **Manual parsing:** Tokenizing input strings using `strtok`
- **File descriptors (indirectly via execvp)**

---

### 📚 Technical Learnings

This project was created to reinforce key **Linux system programming** concepts, including:

- Creating and managing processes in C
- Interacting with the terminal
- Handling user input and arguments
- Basic execution flow between parent and child processes

---

### 🧭 Future Roadmap

| Phase | Feature | Status |
|---|---|---|
| 1 | Basic command execution | ✅ Done |
| 2 | Background jobs (`&`) | 🚧 In progress |
| 3 | Signal handling | ❌ |
| 4 | Output redirection | ❌ |
| 5 | Pipelines | ❌ |

---

### ✅ License

MIT License.
