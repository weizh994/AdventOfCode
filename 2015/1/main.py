if __name__ == "__main__":
    file = open("input", "r")
    floor = 0
    for c in file.read():
        if c == "(":
            floor += 1
        elif c == ")":
            floor -= 1
    print(f"Question 1: {floor}")
    floor = 0
    for i, c in enumerate(open("input", "r").read()):
        floor += 1 if c == "(" else -1
        if floor == -1:
            print(f"Question 2: {i + 1}")
            break
