#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CODE_LENGTH 4
#define NUM_COLORS 6
#define MAX_GUESSES 1296 // Limit the number of guesses to 1296
#define POPULATION_SIZE 150
#define TOURNAMENT_SIZE 5
#define MAX_GENERATIONS 20
#define MUTATION_RATE 2
#define CROSSOVER_RATE 20
#define rateformod 100
#define INVERSION_RATE 2
#define PERMUTATION_RATE 3
#define ELITISM_RATE 1


// ## decimalToCode -> randomCode : assign 4 random number to array
// code[CODE_LENGTH]
void randomCode(int code[CODE_LENGTH]) {
  for (int i = 0; i < CODE_LENGTH; i++) {
    code[i] = rand() % NUM_COLORS;
  }
}

void checkGuess(int secretCode[CODE_LENGTH], int guess[CODE_LENGTH],int *correctPositions, int *correctColors) {

  *correctPositions = 0;
  *correctColors = 0;

  // Arrays to keep track of colors in the secret code and the guess
  bool secretUsed[CODE_LENGTH] = {false};
  bool guessUsed[CODE_LENGTH] = {false};

  // Check for correct positions
  for (int i = 0; i < CODE_LENGTH; i++) {
    if (guess[i] == secretCode[i]) {
      (*correctPositions)++;
      secretUsed[i] = true;
      guessUsed[i] = true;
    }
  }

  // Check for correct colors (excluding the correct positions)
  for (int i = 0; i < CODE_LENGTH; i++) {
    if (!guessUsed[i]) {
      for (int j = 0; j < CODE_LENGTH; j++) {
        if (!secretUsed[j] && guess[i] == secretCode[j]) {
          (*correctColors)++;
          secretUsed[j] = true;
          break;
        }
      }
    }
  }
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// Crossover two parent codes to produce a child code using multi-point crossover
void crossover(int parent1[CODE_LENGTH], int parent2[CODE_LENGTH], int child1[CODE_LENGTH], int child2[CODE_LENGTH])
{
    int rate = rand() % rateformod;
    if (rate < CROSSOVER_RATE)
    {
        // Select multiple crossover points
        int crossoverPoint1 = rand() % CODE_LENGTH;
        int crossoverPoint2 = (crossoverPoint1 + rand() % (CODE_LENGTH - 1) + 1) % CODE_LENGTH;

        // Ensure crossoverPoint1 is less than crossoverPoint2
        if (crossoverPoint1 > crossoverPoint2)
        {
            int temp = crossoverPoint1;
            crossoverPoint1 = crossoverPoint2;
            crossoverPoint2 = temp;
        }

        // Copy segments from parents to children
        for (int i = 0; i < CODE_LENGTH; i++)
        {
            if (i < crossoverPoint1 || i >= crossoverPoint2)
            {
                child1[i] = parent1[i];
                child2[i] = parent2[i];
            }
            else
            {
                child1[i] = parent2[i];
                child2[i] = parent1[i];
            }
        }
    }
}


//mutate a code by randomly changing one of the positions to a random value with random resetting
void mutation(int code[CODE_LENGTH])
{
    int rate =rand()%rateformod;
    if(rate<PERMUTATION_RATE)
    {
        int mutationPoint1 = rand() % CODE_LENGTH ;
        int mutationPoint2 = rand() % CODE_LENGTH ;
        while(mutationPoint1== mutationPoint2)
        {
            mutationPoint2 = rand() % CODE_LENGTH;
        }
        int i,j ;
        if(mutationPoint1<mutationPoint1)
        {
            i = mutationPoint1;
            j = mutationPoint2;
        }
        else
        {
            i = mutationPoint2;
            j =mutationPoint1;
        }
        for(i ; i<j; i++)
        {
            swap(&code[i],&code[j]);
            j--;
        }
    }
}


// Generate a random population of codes with no duplicates
void generatePopulation(int population[POPULATION_SIZE][CODE_LENGTH]) {
  int generatedCodes[MAX_GUESSES]
                    [CODE_LENGTH]; // Array to store generated codes
  int generatedCount = 0;

  while (generatedCount < POPULATION_SIZE) {
    int newCode[CODE_LENGTH];
    randomCode(newCode);

    // Check if the new code is unique
    bool isUnique = true;
    for (int i = 0; i < generatedCount; i++) {
      bool isEqual = true;
      for (int j = 0; j < CODE_LENGTH; j++) {
        if (newCode[j] != generatedCodes[i][j]) {
          isEqual = false;
          break;
        }
      }
      if (isEqual) {
        isUnique = false;
        break;
      }
    }

    // If the code is unique, add it to the population
    if (isUnique) {
      for (int i = 0; i < CODE_LENGTH; i++) {
        population[generatedCount][i] = newCode[i];
      }
      // Add the new code to the list of generated codes
      for (int i = 0; i < CODE_LENGTH; i++) {
        generatedCodes[generatedCount][i] = newCode[i];
      }
      generatedCount++;
    }
  }
}


void inversion(int code[CODE_LENGTH]) {
  int rate = rand() % rateformod;
  if (rate < INVERSION_RATE) {
    int mutationPoint1 = rand() % CODE_LENGTH;
    int mutationPoint2 = rand() % CODE_LENGTH;
    while (mutationPoint1 == mutationPoint2) {
      mutationPoint2 = rand() % CODE_LENGTH;
    }
    int i, j;
    if (mutationPoint1 < mutationPoint1) {
      i = mutationPoint1;
      j = mutationPoint2;
    } else {
      i = mutationPoint2;
      j = mutationPoint1;
    }
    for (i; i < j; i++) {
      swap(&code[i], &code[j]);
      j--;
    }
  }
}


void permutation(int code[CODE_LENGTH]) {
  int rate = rand() % rateformod;
  if (rate < PERMUTATION_RATE) {
    int mutationPoint1 = rand() % CODE_LENGTH;
    int mutationPoint2 = rand() % CODE_LENGTH;
    while (mutationPoint1 == mutationPoint2) {
      mutationPoint2 = rand() % CODE_LENGTH;
    }
    swap(&code[mutationPoint1], &code[mutationPoint2]);
  }
}

double fitness(int old[10][CODE_LENGTH], int neww[CODE_LENGTH], int black[10],
            int white[10], int count) {
  int score = 0;
  for (int i = 0; i < count - 1; i++) {
    int poblack = 0;
    int powhite = 0;
    checkGuess(old[i], neww, &poblack, &powhite);
    score += abs(black[i] - poblack) + abs(white[i] - powhite);
  }
  return score;
}

void tournamentSelection(int secretCode[CODE_LENGTH], int population[POPULATION_SIZE][CODE_LENGTH], int* parentA, int* parentB, int count, int correctPositions[10], int correctColors[10]) {
    int tempcorrectPos[10], tempcorrectColors[10], tempCount = count+1;
    for(int i = 0; i < count; i++){
        tempcorrectPos[i] = correctPositions[i];
        tempcorrectColors[i] = correctColors[i];
    }
    int tournamentSize = TOURNAMENT_SIZE;
    int tournament[tournamentSize];

    // Randomly select individuals for the tournament
    for (int i = 0; i < tournamentSize; i++) {
        tournament[i] = rand() % POPULATION_SIZE;
    }
    // Find the best individual in the tournament
    int bestIndividual = tournament[0];
    for (int i = 1; i < tournamentSize; i++) {
      checkGuess(secretCode, population[tournament[i]], &tempcorrectPos[count], &tempcorrectColors[count]);

        if (fitness(population, population[tournament[i]], tempcorrectPos, correctColors, tempCount) <
            fitness(population, population[bestIndividual], correctPositions, tempcorrectColors, tempCount)) {
            bestIndividual = tournament[i];
        }
    }

    // Copy the selected individual to parentA
    memcpy(parentA, population[bestIndividual], CODE_LENGTH * sizeof(int));

    // Repeat the process to select the second parent
    for (int i = 0; i < tournamentSize; i++) {
        tournament[i] = rand() % POPULATION_SIZE;
    }

    bestIndividual = tournament[0];
    for (int i = 1; i < tournamentSize; i++) {
      checkGuess(secretCode, population[tournament[i]], &tempcorrectPos[count], &tempcorrectColors[count]);
        if (fitness(population, population[tournament[i]], tempcorrectPos, correctColors, tempCount) <
          fitness(population, population[bestIndividual], correctPositions, tempcorrectColors, tempCount)) {
            bestIndividual = tournament[i];
        }
    }
    // Copy the selected individual to parentB
    memcpy(parentB, population[bestIndividual], CODE_LENGTH * sizeof(int));
}


int main() {

  int secretCode[CODE_LENGTH];
  int availablecolors[6];
  int correctPositions[10], correctColors[10];
  
  srand(time(NULL));
  //int totalTurns = 0;
  
  //for (int game = 1; game <= 100; game++) {

    int guess[10][4];
    int count = 1;

    // Generate a random secret code
    randomCode(secretCode);
    /*secretCode[0] = 1;
    secretCode[1] = 3;
    secretCode[2] = 2;
    secretCode[3] = 4;*/
    // Create all possible guesses
    guess[0][0] = 0;
    guess[0][1] = 0;
    guess[0][2] = 1;
    guess[0][3] = 2; 

    checkGuess(secretCode, guess[0], &correctPositions[0], &correctColors[0]);

    printf("#%d ", count);
    for (int i = 0; i < 4; i++) {
      printf("%d ", guess[0][i]);
    }
    printf("| black: %d | white: %d\n", correctPositions[count - 1],
           correctColors[count - 1]);

    int population[POPULATION_SIZE][CODE_LENGTH];
    int eligible_codes_count = 0;
    generatePopulation(population);

    while (correctPositions[count - 1] != 4) {
      count = count + 1;
      int eligible_codes[POPULATION_SIZE][CODE_LENGTH];
      int generation = 1;
      int eligible_codes_count = 0;
      memset(eligible_codes, 0, sizeof eligible_codes);

      // Elitism ใช้วิธีแบบเลือกจากทั้งหมด แล้วเอามาเทียบกับที่เลือกมาแล้ว
      int elitismCount = (int)(ELITISM_RATE / 100.0 * POPULATION_SIZE); 
      
      for (int i = 0; i < elitismCount; i++) {
        memcpy(population[i], eligible_codes[i], CODE_LENGTH * sizeof(int));
      }

      while ((generation <= MAX_GENERATIONS &&eligible_codes_count <= POPULATION_SIZE) ||(eligible_codes_count == 0)) {
        for (int i = 0; i < 75; i++) {
          int parent1[CODE_LENGTH];
          int parent2[CODE_LENGTH];
          int child1[CODE_LENGTH];
          int child2[CODE_LENGTH];

          //tournament selection
          tournamentSelection(secretCode, population, parent1, parent2, count, correctPositions, correctColors);

          crossover(parent1, parent2, child1, child2);
          mutation(child1);
          mutation(child2);
          inversion(child1);
          inversion(child2);
          permutation(child1);
          permutation(child2);
          bool child1_is_new = true;
          bool child2_is_new = true;

          if (fitness(guess, child1, correctPositions, correctColors, count) !=0) {
            child1_is_new = false;
          }
          if (fitness(guess, child2, correctPositions, correctColors, count) !=0) {
            child2_is_new = false;
          }

          for (int j = 0; j < eligible_codes_count; j++) {
            if (memcmp(child1, eligible_codes[j], CODE_LENGTH * sizeof(int)) ==
                0) {
              child1_is_new = false;
            }
            if (memcmp(child2, eligible_codes[j], CODE_LENGTH * sizeof(int)) ==
                0) {
              child2_is_new = false;
            }
          }

          if (child1_is_new == true) {
            memcpy(eligible_codes[eligible_codes_count], child1,
                   CODE_LENGTH * sizeof(int));
            eligible_codes_count++;
          }
          if (child2_is_new == true) {
            memcpy(eligible_codes[eligible_codes_count], child2,
                   CODE_LENGTH * sizeof(int));
            eligible_codes_count++;
          }
        }
        generation++;
      }

      checkGuess(secretCode, eligible_codes[0], &correctPositions[count - 1],
                 &correctColors[count - 1]);
      printf("#%d ", count);
      for (int i = 0; i < 4; i++) {
        printf("%d ", eligible_codes[0][i]);
        guess[count - 1][i] = eligible_codes[0][i];
      }
      printf("| black: %d | white: %d\n", correctPositions[count - 1],
             correctColors[count - 1]);
    }

    printf("The secret code was: ");
    for (int i = 0; i < CODE_LENGTH; i++) {
      printf("%d ", secretCode[i]);
    }
    printf("\n");
    printf("Computer has cracked the code in %d turns!\n", count);
    printf("\n");

    return 0;
}