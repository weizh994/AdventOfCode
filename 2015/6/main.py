import re
import numpy as np

pattern = re.compile(
    r"^(toggle|turn on|turn off)\s+(\d+),(\d+)\s+through\s+(\d+),(\d+)$"
)


def light(line):
    match = pattern.match(line)
    if match:
        command = match.group(1)
        x1 = int(match.group(2))
        y1 = int(match.group(3))
        x2 = int(match.group(4))
        y2 = int(match.group(5))
    else:
        print(f"无法解析行: {line}")

    x2 += 1
    y2 += 1

    if command == "toggle":
        grid[x1:x2, y1:y2] ^= 1
    elif command == "turn on":
        grid[x1:x2, y1:y2] = 1
    elif command == "turn off":
        grid[x1:x2, y1:y2] = 0
    else:
        print("Wrong Command! ", command)


def light2(line):
    match = pattern.match(line)
    if match:
        command = match.group(1)
        x1 = int(match.group(2))
        y1 = int(match.group(3))
        x2 = int(match.group(4))
        y2 = int(match.group(5))
    else:
        print(f"无法解析行: {line}")

    x2 += 1
    y2 += 1

    if command == "toggle":
        grid[x1:x2, y1:y2] += 2
    elif command == "turn on":
        grid[x1:x2, y1:y2] += 1
    elif command == "turn off":
        grid[x1:x2, y1:y2] -= 1
        grid[x1:x2, y1:y2] = np.clip(grid[x1:x2, y1:y2], 0, None)
    else:
        print("Wrong Command! ", command)


if __name__ == "__main__":
    with open("input", "r") as file:
        data = file.readlines()

    global grid
    grid = np.zeros((1000, 1000), int)
    for line in data:
        light(line)
    print(f"Question 1: {np.sum(grid)}")
    grid = np.zeros((1000, 1000), int)
    for line in data:
        light2(line)
    print(f"Question 2: {np.sum(grid)}")
