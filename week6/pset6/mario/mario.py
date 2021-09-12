from cs50 import get_int

# Promting the user for the pyramids height
height = 0
while height < 1 or height > 8:
    height = get_int("Height: ")

# Drawing pyramid
for i in range(height):

    # Spaces
    print(" " * (height - i - 1), end="")

    # Hashtags
    print("#" * (i + 1) + "  " + "#" * (i + 1))