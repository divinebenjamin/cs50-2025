// displays the number of change
#include <stdio.h>

// Function Prototypes
int convertToCents(float dollars);
int calculateQuarters(int cents);
int calculateDimes(int cents);
int calculateNickels(int cents);
int calculatePennies(int cents);

int main(void)
{
  // Example input: amount of change owed in dollars
  float changeInDollars = 0.99;

  // Validate input
  if (changeInDollars < 0.00)
  {
    printf("Invalid input. Change cannot be negative.\n");
    return 1;
  }

  // Convert dollars to cents
  int cents = convertToCents(changeInDollars);
  printf("Change in cents: %i\n", cents);

  // Calculate quarters
  int quarters = calculateQuarters(cents);
  printf("Quarters needed: %i\n", quarters);
  cents -= quarters * 25;

  // Calculate dimes
  int dimes = calculateDimes(cents);
  printf("Dimes needed: %i\n", dimes);
  cents -= dimes * 10;

  // Calculate nickels
  int nickels = calculateNickels(cents);
  printf("Nickels needed: %i\n", nickels);
  cents -= nickels * 5;

  // Calculate pennies
  int pennies = calculatePennies(cents);
  printf("Pennies needed: %i\n", pennies);

  // Total coins used
  int totalCoins = quarters + dimes + nickels + pennies;
  printf("Total coins needed: %i\n", totalCoins);

  return 0;
}

// Converts a dollar amount to cents (rounded)
int convertToCents(float dollars){
  return (int)(dollars * 100 + 0.5); 
}

// Calculates the number of quarters in given cents
int calculateQuarters(int cents){
  return cents / 25;
}

// Calculates the number of dimes in given cents
int calculateDimes(int cents)
{
  return cents / 10;
}

// Calculates the number of nickels in given cents
int calculateNickels(int cents)
{
  return cents / 5;
}

// Calculates the number of pennies in given cents
int calculatePennies(int cents)
{
  return cents;
}
