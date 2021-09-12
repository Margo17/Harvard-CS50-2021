from cs50 import get_string

checksum = 0


def main():

    # Promt the user for an input
    number = get_string("Number: ")

    # Get first 2 digits for card type identification
    header_digits = int(number[:2])

    # Get number length
    length = len(number)

    # Apply Luhn's algorithm
    algorithm(number, length)

    # Identify card type
    identification(number, length, header_digits)


def algorithm(number, length):

    global checksum

    # Luhn's algorithm
    for i in range(1, length + 1):
        # Take every second digit starting from the end
        digit = int(number[-i])
        """ Odd index is the first digit in the credit card number and even is the second"""
        # If index is even
        if i % 2 == 0:
            # If the number has 2 digits
            if digit * 2 > 9:
                # Substracting 9 is the same as adding two digits together
                checksum += digit * 2 - 9
            else:
                checksum += digit * 2
        # If index is odd
        else:
            checksum += digit


def identification(number, length, header_digits):

    global checksum

    # Check if product after Luhn's algorithm ends with 0, if yes = True, no = False
    if checksum % 10 == 0:
        flag = True
    else:
        flag = False

    # Card identification
    if length == 15 and (header_digits == 34 or header_digits == 37) and flag:
        print("AMEX")
    elif length == 16 and 50 < header_digits < 56 and flag:
        print("MASTERCARD")
    elif int(number[:1]) == 4 and (length == 13 or length == 16) and flag:
        print("VISA")
    else:
        print("INVALID")


# Script guard
if __name__ == "__main__":
    main()