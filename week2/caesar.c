#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// --- Function Prototypes ---
int digitChecker(const char arr[], int len);
void encryptCaesar(char arr[], int len, int key);

// --- Main Program ---
int main(int argc, char *argv[])
{
  // --- Step 1: Validate Command-Line Arguments ---
  if (argc != 2)
  {
    printf("Usage: ./caesar key\n");
    return 1;
  }

  // Validate if argument is a number
  int argLength = strlen(argv[1]);
  if (!digitChecker(argv[1], argLength))
  {
    printf("Usage: ./caesar key\n");
    return 1;
  }

  // Convert key to integer and normalize to 0–25
  int key = atoi(argv[1]) % 26;

  // --- Step 2: Get Plaintext from User ---
  char p_text[256];

  do
  {
    printf("plaintext: ");
    if (fgets(p_text, sizeof(p_text), stdin) == NULL)
    {
      printf("Reading failed!\n");
      return 1;
    }

    // Remove newline character
    p_text[strcspn(p_text, "\n")] = '\0';

  } while (strlen(p_text) == 0 || strspn(p_text, " ") == strlen(p_text));

  // --- Step 3: Encrypt and Output Ciphertext ---
  printf("ciphertext: ");
  encryptCaesar(p_text, strlen(p_text), key);
  printf("\n");

  return 0;
}

// --- Function: digitChecker ---
// Checks if all characters in input string are numeric digits
// Returns 1 if all characters are digits, 0 otherwise
int digitChecker(const char arr[], int len)
{
  for (int i = 0; i < len; i++)
  {
    if (!isdigit(arr[i]))
    {
      return 0;
    }
  }
  return 1;
}

// --- Function: encryptCaesar ---
// Encrypts the given plaintext using the Caesar cipher
// - Preserves case
// - Leaves non-alphabetic characters unchanged
void encryptCaesar(char arr[], int len, int key)
{
  char cipher[256];

  for (int i = 0; i < len; i++)
  {
    char a = arr[i];

    if (isupper(a))
    {
      cipher[i] = ((a - 'A' + key) % 26) + 'A';
    }
    else if (islower(a))
    {
      cipher[i] = ((a - 'a' + key) % 26) + 'a';
    }
    else
    {
      cipher[i] = a;
    }
  }

  cipher[len] = '\0'; // Null-terminate the encrypted string
  printf("%s", cipher);
}
