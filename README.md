# Linux Custom Shell

A custom Unix-like command-line interpreter (Shell) designed and implemented in C as part of an Operating Systems academic project. This project demonstrates core concepts of OS architecture, process lifecycle management, and low-level systems programming in Linux environments.

## Features

- Command execution in both foreground and background modes
- Process creation and management using low-level POSIX system calls
- Background process execution using '&'
- Signal handling using SIGINT (Ctrl+C)
- Zombie process prevention and proper child process cleanup
- Dynamic memory management and command input parsing
- Robust error handling and process synchronization

## System Calls & Concepts Used

- `fork()` — Creates child processes
- `execvp()` — Replaces process image with executable commands
- `waitpid()` — Synchronizes process execution and handles child termination
- `signal()` / `sigaction()` — Signal handling and process control
- Pointers & Dynamic Memory — Manual memory management in C
- Process Management — Foreground/background execution and lifecycle handling

## Technologies

- C
- Linux
- GCC
- GDB
- POSIX System Calls

## Getting Started

### Prerequisites

- Linux environment (Ubuntu, Lubuntu, Debian, etc.)
- GCC Compiler

### Compilation and Running

```bash
# Compile the shell source code
gcc -Wall shell.c -o custom_shell

# Run the shell
./custom_shell
