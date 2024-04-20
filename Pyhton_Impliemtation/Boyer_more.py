NO_OF_CHARS = 256

# A utility function to get maximum of two integers
def max(a, b):
    return a if a > b else b

# The preprocessing function for Boyer Moore's bad character heuristic
def badCharHeuristic(string, size):
    badchar = [-1] * NO_OF_CHARS
    for i in range(size):
        badchar[ord(string[i])] = i
    return badchar

def search(txt, pat):
    m = len(pat)
    n = len(txt)
    badchar = badCharHeuristic(pat, m)
    s = 0  # s is shift of the pattern with respect to text
    while s <= (n - m):
        j = m - 1
        while j >= 0 and pat[j] == txt[s + j]:
            j -= 1
        if j < 0:
            print("\n pattern occurs at shift =", s)
            s += m - badchar[ord(txt[s + m])] if (s + m < n) else 1
        else:
            s += max(1, j - badchar[ord(txt[s + j])])

txt = input("Enter the text: ")
pat = input("Enter the pattern to search: ")
search(txt, pat)
