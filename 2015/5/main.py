from collections import defaultdict


def is_nice(line):
    vowels = set("aeiou")
    forbidden = {"ab", "cd", "pq", "xy"}
    has_double = False
    vowel_count = 0
    for i, c in enumerate(line):
        if c in vowels:
            vowel_count += 1
        if i > 0:
            pair = line[i - 1] + c
            if c == line[i - 1]:
                has_double = True
            if pair in forbidden:
                return False

    return vowel_count >= 3 and has_double


def is_nice2(line):
    pair_indices = {}
    has_repeat = False
    has_pair = False

    for i in range(len(line) - 1):
        pair = line[i : i + 2]
        if pair not in pair_indices:
            pair_indices[pair] = [i]
        else:
            for prev_index in pair_indices[pair]:
                if i - prev_index >= 2:
                    has_pair = True
                    break
            if has_pair:
                break

    for i in range(len(line) - 2):
        if line[i] == line[i + 2]:
            has_repeat = True
            break

    return has_repeat and has_pair


if __name__ == "__main__":
    with open("input", "r") as file:
        data = file.readlines()
    answer = 0
    for line in data:
        if is_nice(line):
            answer += 1

    print(f"Question 1: {answer}")

    answer = 0
    for line in data:
        if is_nice2(line):
            answer += 1
    print(f"Question 2: {answer}")
