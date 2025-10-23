#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// --- Function Prototypes ---
void validKey(char key[], int keyLen);
void subCipher(char key[], char p_text[]);

// --- Main Program ---
int main(int argc, char *argv[])
{
  // --- Step 1: Validate Command-Line Argument ---
  if (argc != 2)
  {
    printf("Usage: ./substitution key\n");
    return 1;
  }

  // Get the length of the provided key
  int keyLen = strlen(argv[1]);

  // Validate key: length, alphabetic only, uniqueness
  validKey(argv[1], keyLen);

  // --- Step 2: Get Plaintext from User ---
  char p_text[256];                // Buffer for user input
  int bufferSize = sizeof(p_text); // Store the size of buffer

  do
  {
    printf("plaintext: ");

    if (fgets(p_text, bufferSize, stdin) == NULL)
    {
      printf("Reading Failed!\n");
      return 1;
    }

    // Remove trailing newline character
    p_text[strcspn(p_text, "\n")] = '\0';

  } while (strlen(p_text) == 0 || strspn(p_text, " ") == strlen(p_text));

  // --- Step 3: Apply Substitution Cipher ---
  printf("ciphertext: ");
  subCipher(argv[1], p_text);

  printf("Successful\n");

  return 0;
}

// --- Function: validKey ---
// Validates the substitution key according to CS50 spec
// - Must be exactly 26 characters
// - Must only contain alphabetic characters
// - Must not contain duplicate letters
void validKey(char key[], int keyLen)
{
  if (keyLen != 26)
  {
    printf("Invalid: Key must contain 26 characters.\n");
    exit(1);
  }

  for (int i = 0; i < keyLen; i++)
  {
    if (!isalpha(key[i]))
    {
      printf("Invalid: Key must contain only alphabets.\n");
      exit(1);
    }
  }

  // Check for duplicate characters using frequency array
  int seen[26] = {0};

  for (int i = 0; i < 26; i++)
  {
    char c = toupper(key[i]); // Normalize to uppercase
    if (seen[c - 'A'] > 0)
    {
      printf("Invalid: Key must not contain duplicate letters.\n");
      exit(1);
    }
    seen[c - 'A']++;
  }
}

// --- Function: subCipher ---
// Encrypts the plaintext using the provided key
// - Preserves case
// - Leaves non-alphabetic characters unchanged
void subCipher(char key[], char p_text[])
{
  int textLen = strlen(p_text);
  char c_text[256];

  for (int i = 0; i < textLen; i++)
  {
    char p = p_text[i];

    if (isupper(p))
    {
      int index = p - 'A';
      c_text[i] = toupper(key[index]);
    }
    else if (islower(p))
    {
      int index = p - 'a';
      c_text[i] = tolower(key[index]);
    }
    else
    {
      // Leave punctuation, digits, and spaces unchanged
      c_text[i] = p;
    }
  }

  c_text[textLen] = '\0'; // Null-terminate the cipher text
  printf("%s\n", c_text);
}
