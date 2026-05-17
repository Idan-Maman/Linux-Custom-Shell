# Linux Custom Shell

A custom Linux command-line interpreter (Shell) designed and implemented in C as part of the Operating Systems academic coursework. This project demonstrates core concepts of OS architecture, process lifecycle management, and system-level programming.

## Features
* **Command Execution:** Executes standard Linux system commands in both foreground and background modes.
* **Process Management:** Utilizes low-level system calls for concurrent process creation and management.
* **Signal Handling:** Properly manages and handles system signals (such as `Ctrl+C`).
* **Resource Cleanup:** Features proactive memory management and zombie process prevention.

## System Calls & Concepts Used
* `fork()`: To clone the calling process and create child processes.
* `execvp()`: To replace the child process image with the intended command executable.
* `waitpid()`: To synchronize process execution and collect child process termination status.
* **Pointers & Dynamic Memory:** Rigorous memory management and input parsing in C.

## Getting Started

### Prerequisites
* A Linux environment (Ubuntu, Lubuntu, Debian, etc.)
* GCC Compiler

### Compilation and Running
To compile and run the shell, execute the following commands in your terminal:

```bash
# Compile the shell source code
gcc -Wall shell.c -o custom_shell

# Run the shell
./custom_shell
