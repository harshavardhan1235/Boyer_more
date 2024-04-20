NO_OF_CHARS = 256

def badCharHeuristic(string):
    badchar = [-1] * NO_OF_CHARS
    for i, char in enumerate(string):
        badchar[ord(char)] = i
    return badchar

def preProcessGoodSuffix(pattern):
    m = len(pattern)
    suff = [-1] * m
    j = m - 1
    for i in range(m - 2, -1, -1):
        while j >= 0 and pattern[j] != pattern[i]:
            j = m - 1 - (m - 1 - j)
        j -= 1
        suff[i] = j + 1
    return suff

def search(text, pattern):
    m = len(pattern)
    n = len(text)
    badchar = badCharHeuristic(pattern)
    suff = preProcessGoodSuffix(pattern)

    s = 0
    while s <= (n - m):
        j = m - 1
        while j >= 0 and pattern[j] == text[s + j]:
            j -= 1

        if j < 0:
            print("Pattern occurs at shift =", s)
            s += m - badchar[ord(text[s + m])] if (s + m < n) else 1
        else:
            s += max(1, max(j - badchar[ord(text[s + j])], j - suff[j]))

def main():
    with open("input.txt", "r") as file:
        text, pattern = file.readline().strip(), file.readline().strip()

    search(text, pattern)

if __name__ == "__main__":
    main()
