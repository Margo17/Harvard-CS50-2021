import cs50

# Ask the user how much change he is owed
change = -1
while change < 0:
    change = cs50.get_float("Change owed: ")

# Coins and coin_amount variable declaration
coins = [0.25, 0.10, 0.05, 0.01]
coin_amount = 0

# Change calculation
for i in coins:
    if change % i == 0:
        coin_amount += int(change / i)
        break
    else:
        coin_amount += int(change / i)
        change = round(change % i, 2)

# Output line
print(coin_amount)