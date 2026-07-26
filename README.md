# Linux Custom Shell

A custom Unix-like command-line interpreter (Shell) implemented in C. This project demonstrates core concepts of operating systems, process creation, manual `PATH` resolution, and dynamic memory management in Linux.

## Features

- **Interactive Shell Prompt:** Custom CLI interface (`Idan'sShell`).
- **Command Execution:** Supports both absolute/relative paths (e.g., `/bin/ls`, `./script`) and standard system commands (e.g., `ls`, `pwd`).
- **Manual PATH Parsing:** Parses the system's `PATH` environment variable to dynamically locate executables.
- **Process Management:** Creates isolated child processes for command execution.
- **Dynamic Memory Control:** Safe allocation (`calloc`) and deallocation to prevent memory corruption.

## System Calls & Concepts Used

- `fork()` — Spawns child processes.
- `execv()` — Replaces process image with the target command executable.
- `wait()` — Synchronizes parent process with child termination.
- `getenv()` & `strtok()` — Environment variable retrieval and tokenization.
- Dynamic Memory — Manual memory allocation and memory cleanup in C.

## Technologies

- C
- Linux
- GCC / GDB
- POSIX System Calls

## Getting Started

### Prerequisites

- Linux / POSIX environment
- GCC Compiler

### Compilation and Running

```bash
# Compile the shell
gcc -Wall main.c -o custom_shell

# Run the shell
./custom_shell