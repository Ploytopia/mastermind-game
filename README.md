# Mastermind: We Love Algorithms

This repository contains implementations of the classic code-breaking game **Mastermind** using a genetic algorithm approach. The project includes two versions of the game with varying parameters for code length and number of selectable colors.

## 📂 Project Files

- **[We love algorithms 64](./We+love+algorithms_64.c)**  
  Implementation for Mastermind with 6 colors and a code length of 4 (**6 select 4**).

- **[We love algorithms 85](./We+love+algorithms_85.c)**  
  Implementation for Mastermind with 8 colors and a code length of 5 (**8 select 5**).

## 🎯 Objective

The goal is to implement an optimized solution for the Mastermind game using:
- **Genetic Algorithms** to efficiently guess the secret code.
- A combination of genetic operations like crossover, mutation, inversion, and permutation to improve the guesses iteratively.

## 🚀 Key Features

- **Mastermind Gameplay**:
  - Randomly generates a secret code based on the selected version.
  - Automatically attempts to guess the code using a genetic algorithm.
- **Genetic Algorithm Operations**:
  - Multi-point crossover for creating new populations.
  - Mutation, inversion, and permutation to introduce diversity and improve solutions.
- **Fitness Evaluation**:
  - Calculates the correctness of guesses based on the number of correctly guessed colors and positions.
- **Tournament Selection**:
  - Selects the fittest individuals as parents for the next generation.

## 🛠️ Tools and Technologies

- **Language**: C
- **Libraries**: 
  - `<math.h>` for mathematical operations.
  - `<stdbool.h>` for boolean logic.
  - `<stdlib.h>` and `<time.h>` for randomness.

## 📈 Project Workflow

1. **Initialization**:
   - Randomly generates a secret code (e.g., 6 colors, 4 positions for the 64 version).
   - Creates an initial population of random guesses.
2. **Genetic Algorithm**:
   - Evolves the population over multiple generations using:
     - **Crossover** for combining parents.
     - **Mutation** for introducing new patterns.
     - **Inversion** and **Permutation** for refining solutions.
   - Evaluates fitness based on proximity to the correct code.
3. **Code Breaking**:
   - Prints each guess and provides feedback on:
     - **Black pegs**: Correct color and correct position.
     - **White pegs**: Correct color but wrong position.
   - Repeats until the secret code is cracked.

## 📝 How to Run

1. Compile the desired version:
   ```bash
   gcc We+love+algorithms_64.c -o mastermind64
## 📊 Example Output
![image](https://github.com/user-attachments/assets/b9e7d24b-dc3b-4daf-8273-39b7587c3637)

