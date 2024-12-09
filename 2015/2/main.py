def get_area(l, w, h):
    return 2 * l * w + 2 * w * h + 2 * h * l + min(l * w, w * h, l * h)


def get_ribbon(l, w, h):
    return 2 * (l + w + h - max(l, w, h)) + l * w * h


if __name__ == "__main__":
    file = open("input", "r")
    total_area = 0
    total_ribbon = 0
    for line in file:
        l, w, h = map(int, line.split("x"))
        total_area += get_area(l, w, h)
        total_ribbon += get_ribbon(l, w, h)

    print(f"Question 1: {total_area}")
    print(f"Question 2: {total_ribbon}")
