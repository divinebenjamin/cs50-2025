from cs50 import get_int

while True:
  card = get_int("Enter Credit Card Number: ")
  strCard = str(card)
  lenCard = len(strCard)
  if lenCard > 0:
    print("break")
    break

if lenCard > 13 or lenCard < 18:
  print("Invalid")

