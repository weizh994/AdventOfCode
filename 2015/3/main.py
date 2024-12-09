def move(pos, direction):
    if direction == "^":
        return (pos[0], pos[1] + 1)
    elif direction == "v":
        return (pos[0], pos[1] - 1)
    elif direction == ">":
        return (pos[0] + 1, pos[1])
    elif direction == "<":
        return (pos[0] - 1, pos[1])
    else:
        return pos


if __name__ == "__main__":
    with open("input", "r") as file:
        data = file.read().strip()
    pos = (0, 0)
    presents = set()
    presents.add(pos)
    for c in data:
        pos = move(pos, c)
        presents.add(pos)
    new_present = set()
    pos_x = (0, 0)
    pos_y = (0, 0)
    new_present.add(pos_x)
    for i, c in enumerate(data):
        if i % 2 == 0:
            pos_x = move(pos_x, c)
            new_present.add(pos_x)
        else:
            pos_y = move(pos_y, c)
            new_present.add(pos_y)

    print(f"Question 1: {len(presents)}")
    print(f"Question 2: {len(new_present)}")
