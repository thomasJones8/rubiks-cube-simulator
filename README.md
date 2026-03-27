# Rubik's Cube Simulator

A 3D Rubik's Cube simulator written in C, supporting N x N x N grid sizes. 

The program utilizes complex 3D array transformations to accurately model multi-layer rotations. It features a custom text-based command parser (based on a context-free grammar) to process rotational operations in real-time. Built with a strong focus on memory safety and strict compiler standards.

*Note: For the detailed, original academic requirements and strict evaluation rules (in Polish), see [SPECIFICATION_PL.md](SPECIFICATION_PL.md).*

### Tech Stack
* **Language:** C (C17 standard)
* **Tools:** GCC, Valgrind

### How to Build & Run

**Quick Start (Standard Build):**
```bash
gcc -DN=5 kostka_rubika.c -o cube
./cube
```

**Strict Build (Used for academic evaluation & memory leak checks):**
To verify code quality and memory safety, compile with strict C17 standards and run via Valgrind:
```bash
gcc -std=c17 -pedantic -Wall -Wextra -Werror -O1 -g -DN=5 kostka_rubika.c -o cube
valgrind --leak-check=full -q --error-exitcode=1 ./cube
```

**Running with input files:**
You can also feed the program with predefined command sequences:
```bash
< przyklad.in ./cube
```

