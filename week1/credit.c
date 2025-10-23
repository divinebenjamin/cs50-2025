#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function Prototypes
int sumOddDigitsFromRight(long long cardNumber);
int sumEvenDigitsFromRight(long long cardNumber);
int getCardLength(long long cardNumber);

int main(void)
{
  long long cardNumber;
  char result[11]; // Result will be "VISA", "MASTERCARD", "AMEX", or "INVALID"

  // Prompt for card number until a positive number is entered
  do
  {
    printf("Enter Credit Card Number: ");
    scanf("%lld", &cardNumber);
  } while (cardNumber <= 0);

  // Calculate card length
  int length = getCardLength(cardNumber);

  // Calculate checksum using Luhn's Algorithm
  int checksum = sumOddDigitsFromRight(cardNumber) + sumEvenDigitsFromRight(cardNumber);

  // Extract first digit and first two digits for card type validation
  long long divisor = 1;
  for (int i = 0; i < length - 1; i++)
  {
    divisor *= 10;
  }

  int firstDigit = cardNumber / divisor;
  int firstTwoDigits = cardNumber / (divisor / 10);

  // Determine card type
  if (checksum % 10 == 0)
  {
    if (firstDigit == 4 && (length == 13 || length == 16))
    {
      strcpy(result, "VISA");
    }
    else if ((firstTwoDigits >= 51 && firstTwoDigits <= 55) && length == 16)
    {
      strcpy(result, "MASTERCARD");
    }
    else if ((firstTwoDigits == 34 || firstTwoDigits == 37) && length == 15)
    {
      strcpy(result, "AMEX");
    }
    else
    {
      strcpy(result, "INVALID");
    }
  }
  else
  {
    strcpy(result, "INVALID");
  }

  // Output the result
  printf("%s\n", result);
}

// Luhn Algorithm Part 1: Sum digits in odd positions from right
int sumOddDigitsFromRight(long long cardNumber)
{
  int sum = 0;

  while (cardNumber > 0)
  {
    int digit = cardNumber % 10;
    sum += digit;
    cardNumber /= 100; // Move two digits back
  }

  return sum;
}

// Luhn Algorithm Part 2: Double and sum digits in even positions from right
int sumEvenDigitsFromRight(long long cardNumber)
{
  int sum = 0;

  cardNumber /= 10; // Skip the last digit

  while (cardNumber > 0)
  {
    int digit = cardNumber % 10;
    int product = digit * 2;

    // If product is two digits, add digits individually
    sum += (product > 9) ? (product / 10 + product % 10) : product;

    cardNumber /= 100; // Move two digits back
  }

  return sum;
}

// Count the number of digits in the card number
int getCardLength(long long cardNumber)
{
  int length = 0;

  while (cardNumber != 0)
  {
    cardNumber /= 10;
    length++;
  }

  return length;
}
