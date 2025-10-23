// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Function prototypes
int letterCalc(const char arr[], int length);
int wordCalc(const char arr[], int length);
int sentenceCalc(const char arr[], int length);
int isSentenceEnd(char c);

// Main function
int main(void)
{
  // Prompt user for input text
  char userText[1000];
  unsigned int length, letters, words, sentences;
  float L, S, index;

  // Ensure non-empty input
  do
  {
    printf("Text: ");

    if (fgets(userText, sizeof(userText), stdin) == NULL)
    {
      printf("Reading failed!\n");
      return 1;
    }

    userText[strcspn(userText, "\n")] = '\0'; // Remove trailing newline

  } while (userText[0] == '\0');

  // Get the length of the input
  length = strlen(userText);

  // Calculate components for the Coleman-Liau index
  letters = letterCalc(userText, length);
  words = wordCalc(userText, length);
  sentences = sentenceCalc(userText, length);

  // Calculate L and S
  L = ((float)letters / words) * 100;
  S = ((float)sentences / words) * 100;

  // Calculate Coleman-Liau index
  index = (0.0588 * L) - (0.296 * S) - 15.8;

  // Output grade level
  if (index < 1)
  {
    printf("Before Grade 1\n");
  }
  else if (index >= 16)
  {
    printf("Grade 16+\n");
  }
  else
  {
    printf("Grade %d\n", (int)round(index));
  }

  return 0;
}

// Count the number of alphabetic characters in the input
int letterCalc(const char arr[], int length)
{
  int count = 0;

  for (int i = 0; i < length; i++)
  {
    if (isalpha(arr[i]))
    {
      count++;
    }
  }

  return count;
}

// Count the number of words based on space separation
int wordCalc(const char arr[], int length)
{
  int count = 0;
  int i = 0;

  // Skip leading spaces
  while (i < length && arr[i] == ' ')
  {
    i++;
  }

  // Count words
  while (i < length)
  {
    if (arr[i] != ' ')
    {
      count++;

      // Skip until next space
      while (i < length && arr[i] != ' ')
      {
        i++;
      }
    }
    i++;
  }

  return count;
}

// Check if character is a sentence-ending punctuation
int isSentenceEnd(char c)
{
  return (c == '.' || c == '!' || c == '?');
}

// Count the number of sentence-ending punctuation marks
int sentenceCalc(const char arr[], int length)
{
  int count = 0;
  int i = 0;

  // Skip initial sentence punctuation (e.g., "!!!")
  while (i < length && isSentenceEnd(arr[i]))
  {
    i++;
  }

  // Count valid sentence-ending punctuation
  while (i < length)
  {
    if (isSentenceEnd(arr[i]))
    {
      if ((i == length - 1) || (arr[i + 1] == ' '))
      {
        count++;
      }

      // Skip repeated punctuation
      while (i < length && isSentenceEnd(arr[i]))
      {
        i++;
      }
    }
    else
    {
      i++;
    }
  }

  return count;
}