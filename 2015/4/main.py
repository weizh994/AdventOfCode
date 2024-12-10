import hashlib


def md5(s):
    return hashlib.md5(s.encode()).hexdigest()


def main():
    i = 0
    key = "yzbqklnj"
    while True:
        if md5(key + str(i)).startswith("00000"):
            print(f"Question 1: {i}")
            break
        i += 1
    i = 0
    while True:
        if md5(key + str(i)).startswith("000000"):
            print(f"Question 2: {i}")
            break
        i += 1


if __name__ == "__main__":
    main()
