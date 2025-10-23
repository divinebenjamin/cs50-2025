// Libraries
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function Prototypes
int charChecker(char player[]);
int wordScore(const char player[]);

// Main Function
int main(void)
{
  // Declare player word buffers and scores
  char player1[100];
  char player2[100];
  int score1, score2;

  // Prompt Player 1 until valid input is received
  do
  {
    printf("Player 1: ");
    scanf("%99s", player1); // Limit input to avoid buffer overflow
  } while (!charChecker(player1));

  // Prompt Player 2 until valid input is received
  do
  {
    printf("Player 2: ");
    scanf("%99s", player2);
  } while (!charChecker(player2));

  // Calculate scores
  score1 = wordScore(player1);
  score2 = wordScore(player2);

  // Display winner
  if (score1 > score2)
  {
    printf("\nPlayer 1 wins!\n");
  }
  else if (score2 > score1)
  {
    printf("\nPlayer 2 wins!\n");
  }
  else
  {
    printf("\nIt's a tie!\n");
  }

  // Display final score board
  printf("\n+----- SCORE BOARD -----+\n");
  printf("Player 1\tPlayer 2\n");
  printf("   %d\t\t   %d\n", score1, score2);

  return 0;
}

// Function to validate if input contains only alphabetic characters
int charChecker(char player[])
{
  for (int i = 0; i < strlen(player); i++)
  {
    if (!isalpha(player[i]))
    {
      printf("Invalid input! Use letters only.\n");
      return 0;
    }
  }
  return 1;
}

// Function to compute Scrabble score for a word
int wordScore(const char player[])
{
  // Scrabble points for A-Z
  int points[] = {
      1, 3, 3, 2, 1, 4, 2, 4, 1, 8,
      5, 1, 3, 1, 1, 3, 10, 1, 1, 1,
      1, 4, 4, 8, 4, 10};

  int score = 0;

  for (int i = 0; i < strlen(player); i++)
  {
    // Normalize to uppercase index
    int index = toupper(player[i]) - 'A';
    score += points[index];
  }

  return score;
}
