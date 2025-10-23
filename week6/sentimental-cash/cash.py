from cs50 import get_float

while True:
  change = get_float("Change: ")
  if change > 0.00:
    print(f'{change}')
    break

# CONVERTS FROM DOLLAR TO CENTS
change = int(change * 100)
print(f'{change}')

quaters = int(change / 25)
change -= quaters * 25

dimes = int(change / 10)
change -= dimes * 10

nickels = int(change / 5)
change -= nickels * 5

pennies = change

coins = quaters + dimes + nickels + pennies
print(f'{coins}')