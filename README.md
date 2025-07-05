# -Operating-Systems-project
This repository contains a collection of projects from the operating systems course, implemented in C and Java. Each project focuses on different fundamental concepts and practical tasks related to operating systems.

## Project Overview

### 1. Z.1 — Processes and File Communication (C)

A program that creates `n` child processes. Each child reads a 3x3 matrix from `input<i>.txt`, calculates the sum of non-negative elements, and writes the result to a temporary file. The parent waits for all children to finish, reads all results, sorts them by process execution time, and writes the sorted results to `output.txt`.

**File:**  
- `prvizadatak.c`

---

### 2. Z.2 — Matrix Rotation Using pthread (C)

Reads an `m x m` square matrix from `input.txt` and rotates it 90 degrees clockwise using multiple pthread threads. Each thread processes part of the matrix to achieve parallel rotation.

**File:**  
- `drugizadatak.c`

---

### 3. Z.3 — Vector Addition Using pthread (C)

Adds two `n`-dimensional vectors using `m` pthread threads. Each thread is responsible for adding a segment of the vectors. The program measures and compares execution times of single-threaded and multi-threaded addition.

**File:**  
- `trecizadatak.c`

---

### 4. Bonus — Java Card Game

A multi-class Java program simulating a card game with:

- `Card`: Represents a playing card with unique ID, value, and suit.
- `Deck`: Represents a deck of 52 cards with thread-safe draw and add operations.
- `Player`: Represents a player holding cards, able to draw from and return cards to the deck.
- `Game`: Main class that runs the simulation, deals cards, simulates rounds of drawing and returning cards, and declares the winner based on hand value.

**Files:**  
- `bonus/Card.java`  
- `bonus/Deck.java`  
- `bonus/Player.java`  
- `bonus/Game.java`

---

## How to Build and Run

### C programs:

Compile and run each C program separately (assuming GCC and pthread library):

```bash
gcc -o prvizadatak prvizadatak.c
./prvizadatak n
```

```bash
gcc -o drugizadatak drugizadatak.c -lpthread
./drugizadatak
```

```bash
gcc -o trecizadatak trecizadatak.c -lpthread
./trecizadatak
```
Note: Input files like input1.txt, input.txt etc. should be prepared according to each task specification.


Java program:
Compile and run the Java card game simulation:

```bash
javac bonus/*.java
java bonus.Game
```
License
This project is free to use and modify.

Feel free to open issues or pull requests for improvements!

© 2025 Anita Mijatović
