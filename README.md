The Boyer-Moore algorithm is one of the most efficient string searching algorithms developed by Robert S. Boyer and J Strother Moore in 1977. It's designed to find occurrences of a pattern within a text quickly and efficiently.
Preprocessing Phase:
The algorithm preprocesses the pattern to create two tables: the bad character table and the good suffix table.
The bad character table stores the rightmost occurrence of each character in the pattern.
The good suffix table stores information about the alignment of suffixes within the pattern.
Searching Phase:
Starting from the beginning of the text, the algorithm slides the pattern over the text from left to right.
At each position, it compares characters of the pattern with the corresponding characters in the text.
If a mismatch occurs, the algorithm uses information from the bad character and good suffix tables to determine the maximum possible shift that can be made while maintaining alignment with the text.
By using these tables, the algorithm skips more characters in the text, resulting in fewer character comparisons and making the search process faster.
Handling Mismatches:
When a mismatch occurs, the algorithm decides the shift distance based on the bad character and good suffix heuristics. It prioritizes shifting the pattern such that the rightmost occurrence of the mismatched character aligns with the text.
This approach maximizes the skip distance, leading to efficient searching.
Termination:
The algorithm continues sliding the pattern over the text until either the end of the text is reached or a match is found.
If a match is found, the algorithm reports the position where the match starts.
