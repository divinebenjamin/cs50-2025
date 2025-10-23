#include <stdio.h>
#include <string.h>

// Function Prototype
void printRow(int blocks);

int main(void)
{
  char buffer[5];
  int height;
  int success;

  // Prompt user until a valid height (≥ 1) is entered
  do
  {
    printf("Enter Height (1-100): ");

    if(!fgets(buffer, sizeof(buffer), stdin)){
      printf("Reading failed!\n");
      return 1;
    }

    if(!strchr(buffer, '\n')) {
      printf("Input too long.\n");

      int ch;
      while((ch = getchar()) != '\n' && ch != EOF) {}
      continue;
    }

    char extra;    
    success = sscanf(buffer, "%d %c", &height, &extra);

  } while(success != 1 || height > 100);

  // Print rows of increasing length
  for (int i = 0; i < height; i++)
  {
    printRow(i + 1);
  }

  return 0;
}

// Prints a single row with the given number of hash blocks
void printRow(int blocks)
{
  for (int i = 0; i < blocks; i++)
  {
    printf("#");
  }
  printf("\n");
}
