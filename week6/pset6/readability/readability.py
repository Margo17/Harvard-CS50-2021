from cs50 import get_string


def main():
    # Promt user for text
    text = get_string("Text: ")

    # Calculate letters, words and sentences
    words = 1
    letters = sentences = 0

    for i in text:
        if i.isalnum():
            letters += 1
        elif i.isspace():
            words += 1
        elif i == '.' or i == '!' or i == '?':
            sentences += 1

    # Coleman-Liau formula application
    # L is the average number of letters per 100 words in the text
    # S is the average number of sentences per 100 words in the text
    L = letters / words * 100
    S = sentences / words * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Printing out the grade level
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


# Script guard
if __name__ == "__main__":
    main()