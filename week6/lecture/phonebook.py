from cs50 import get_string

people = {
    "Brian": "+1-617-495-1000",
    "David": "+1-496-588-1260",
    "Brian": "+1-736-685-2387"
}

name = get_string("Name: ")
if name in people:
    number = people[name]
    print(f"Number: {number}")