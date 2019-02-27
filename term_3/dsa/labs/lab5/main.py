import re


def main():
    text = input("text: ")
    words = [word for word in re.split(r'[\s,.:\-!?()"\']', text) if word != ""]
    average_letters_count = len("".join(words)) / len(words)
    print("avg: {:.4}".format(average_letters_count))


if __name__ == "__main__":
    main()
