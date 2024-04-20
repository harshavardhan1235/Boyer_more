#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define NO_OF_CHARS 256

void badCharHeuristic(const std::string& str, int badchar[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    for (size_t i = 0; i < str.size(); i++)
        badchar[static_cast<int>(str[i])] = i;
}

void preProcessGoodSuffix(const std::string& pat, std::vector<int>& suff) {
    suff.assign(pat.size(), -1);
    int m = pat.size(), j = m - 1;
    for (int i = m - 2; i >= 0; i--) {
        while (j >= 0 && pat[j] != pat[i])
            j = m - 1 - (m - 1 - j);
        j--;
        suff[i] = j + 1;
    }
}

void search(const std::string& txt, const std::string& pat) {
    int m = pat.size();
    int n = txt.size();
    int badchar[NO_OF_CHARS];
    badCharHeuristic(pat, badchar);

    std::vector<int> suff;
    preProcessGoodSuffix(pat, suff);

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;
        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0) {
            std::cout << "Pattern occurs at shift = " << s << std::endl;
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        } else
            s += (suff[j] != -1) ? std::max(1, std::max(j - badchar[txt[s + j]], j - suff[j])) : std::max(1, j - badchar[txt[s + j]]);
    }
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    std::string txt, pat;
    file >> txt >> pat;
    file.close();

    search(txt, pat);

    return 0;
}
