#include <stdio.h>
#include <string.h>

// Function prototype to print each row of the pyramid
void printRow(int totalHeight, int currentRow);


//main
int main(void)
{
  char buffer[5];
  int height;
  int success;

  // Get user input
 do{
  printf("Enter Height (1-100): ");

  if(!fgets(buffer, sizeof(buffer), stdin)){
    printf("Reading Failed!\n");
    return 1;
  }

  if(!strchr(buffer, '\n')){
    printf("Input too long.\n");

    int ch;
    while((ch = getchar()) != '\n' && ch != EOF) {}
    continue;
  }

  char extra;
  success = sscanf(buffer, "%d %c", &height, &extra);

 } while(success != 1 || height > 100);

  // Print rows of increasing length
  for (int i = 0; i < height; i++){
    printRow(height, i + 1);
  }

  return 0;
}

// Prints a single row of the right-aligned half-pyramid
void printRow(int totalHeight, int currentRow)
{
  // Print leading spaces
  for (int j = 0; j < totalHeight - currentRow; j++)
  {
    printf(" ");
  }

  // Print the hash blocks
  for (int k = 0; k < currentRow; k++)
  {
    printf("#");
  }

  // Move to the next line
  printf("\n");
}
