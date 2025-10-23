// Libraries
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function Prototypes
int charChecker(const char str[]);
int wordScore(const char word[]);

// Data type to hold player's information
typedef struct
{
  char name[20];
  char word[20];
  int points;
  int score;
} player;

// Main Function
int main(void)
{
  player player1 = {"", "", 0, 0};
  player player2 = {"", "", 0, 0};
  int rounds;

  // Get Player 1 name
  do
  {
    printf("Enter name, Player 1: ");
    scanf("%19s", player1.name);
  } while (!charChecker(player1.name));

  // Get Player 2 name
  do
  {
    printf("Enter name, Player 2: ");
    scanf("%19s", player2.name);
  } while (!charChecker(player2.name));

  // Get number of rounds
  do
  {
    printf("Number of rounds? ");
    scanf("%d", &rounds);
  } while (rounds < 1);

  printf("\n+----- %s VS. %s -----+\n", player1.name, player2.name);

  // Game Loop
  for (int i = 1; i <= rounds; i++)
  {
    printf("\n-------------------------\n");
    printf("Round %d/%d\n\n", i, rounds);

    // Get Player 1 word
    do
    {
      printf("%s: ", player1.name);
      scanf("%19s", player1.word);
    } while (!charChecker(player1.word));

    // Get Player 2 word
    do
    {
      printf("%s: ", player2.name);
      scanf("%19s", player2.word);
    } while (!charChecker(player2.word));

    // Calculate scores
    player1.points = wordScore(player1.word);
    player2.points = wordScore(player2.word);

    // Announce round result
    printf("\n");
    if (player1.points > player2.points)
    {
      printf("%s wins this round!\n", player1.name);
      player1.score++;
    }
    else if (player2.points > player1.points)
    {
      printf("%s wins this round!\n", player2.name);
      player2.score++;
    }
    else
    {
      printf("This round is a tie!\n");
    }
  }

  // Final Result
  printf("\n+----- Game Over -----+\n");
  if (player1.score > player2.score)
  {
    printf("%s wins the game!\n", player1.name);
  }
  else if (player2.score > player1.score)
  {
    printf("%s wins the game!\n", player2.name);
  }
  else
  {
    printf("It's a tie overall!\n");
  }

  // Display Scoreboard
  printf("\n+----- Final Score -----+\n");
  printf("%s: %d points\n", player1.name, player1.score);
  printf("%s: %d points\n", player2.name, player2.score);
  printf("-------------------------\n");

  return 0;
}

// Function to check if a string contains only alphabetic characters
int charChecker(const char str[])
{
  for (int i = 0; str[i]; i++)
  {
    if (!isalpha(str[i]))
    {
      printf("Invalid input! Letters only.\n");
      return 0;
    }
  }
  return 1;
}

// Function to calculate the Scrabble score of a word
int wordScore(const char word[])
{
  int points[] = {
      1, 3, 3, 2, 1, 4, 2, 4, 1, 8,
      5, 1, 3, 1, 1, 3, 10, 1, 1, 1,
      1, 4, 4, 8, 4, 10};

  int score = 0;
  for (int i = 0; word[i]; i++)
  {
    int index = toupper(word[i]) - 'A';
    score += points[index];
  }

  return score;
}
