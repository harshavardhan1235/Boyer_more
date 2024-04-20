#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_OF_CHARS 256

void badCharHeuristic(char *str, int size, int badchar[NO_OF_CHARS]) {
    int i;
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    for (i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

void preProcessGoodSuffix(char *pat, int m, int *suff) {
    int i, j;
    for (i = 0; i < m; i++)
        suff[i] = -1;

    j = m - 1;
    for (i = m - 2; i >= 0; i--) {
        while (j >= 0 && pat[j] != pat[i])
            j = m - 1 - (m - 1 - j);
        j--;
        suff[i] = j + 1;
    }
}

void search(char *txt, char *pat) {
    int m = strlen(pat);
    int n = strlen(txt);

    int badchar[NO_OF_CHARS];
    badCharHeuristic(pat, m, badchar);

    int *suff = (int *)malloc(m * sizeof(int));
    preProcessGoodSuffix(pat, m, suff);

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0) {
            printf("\n pattern occurs at shift = %d", s);
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        } else
            s += (suff[j] != -1) ? max(1, max(j - badchar[txt[s + j]], j - suff[j])) : max(1, j - badchar[txt[s + j]]);
    }

    free(suff);
}

int main() {
    FILE *fp;
    char txt[1000], pat[1000];
    
    // Open the input file in read mode
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    
    // Read the text and pattern from the file
    fscanf(fp, "%s", txt);
    fscanf(fp, "%s", pat);
    
    fclose(fp); // Close the file after reading
    
    // Perform the search
    search(txt, pat);
    
    return 0;
}
