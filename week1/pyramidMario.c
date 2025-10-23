#include <stdio.h>
#include <string.h>

// Function Prototype
void printRow(int pyramidHeight, int currentRow);

int main(void)
{
  char buffer[5];
  int height;
  int success;

  // Hardcoded value for now (can be replaced with user input)
  do
  {
    printf("Enter Height (1-100): ");

    if(!fgets(buffer, sizeof(buffer), stdin)){
      printf("Reading Failed!\n");
      return 1;
    }

    if(!strchr(buffer, '\n')){
      printf("Input too long.\n");

      int ch;
      while((ch = getchar()) != '\n' && ch != EOF){}
      continue;
    }

    char extra;
    success = sscanf(buffer, "%d %c", &height, &extra);

  } while (success != 1 || height > 100);

  // Print each row of the pyramid
  for (int i = 0; i < height; i++)
  {
    printRow(height, i + 1);
  }

  return 0;
}

// Prints a single row of the double half-pyramid
void printRow(int pyramidHeight, int currentRow)
{
  // Print leading spaces (left-aligned padding)
  for (int j = 0; j < pyramidHeight - currentRow; j++)
  {
    printf(" ");
  }

  // Print left half of the pyramid
  for (int k = 0; k < currentRow; k++)
  {
    printf("#");
  }

  // Print gap between the two halves
  printf("  ");

  // Print right half of the pyramid
  for (int l = 0; l < currentRow; l++)
  {
    printf("#");
  }

  // Move to the next line
  printf("\n");
}
