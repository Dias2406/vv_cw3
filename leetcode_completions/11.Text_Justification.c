#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** fullJustify(char** words, int wordsSize, int maxWidth, int* returnSize) {
    int totalLines = 0;
    int currentLineLength = 0;
    int start = 0;

    char** result = malloc(sizeof(char*) * 1000); // Temporarily assuming we won't exceed 1000 lines
    for (int i = 0; i < wordsSize; i++) {
        int currentWordLength = strlen(words[i]);
        // Check if adding this word would exceed the max width (account for at least one space if it's not the first word)
        if (currentLineLength + currentWordLength + (i - start) > maxWidth) {
            int spacesNeeded = maxWidth - currentLineLength;
            int slots = i - start - 1;
            char* line = malloc(maxWidth + 1);
            int cursor = 0;

            if (slots > 0) {
                int spaceWidth = spacesNeeded / slots;
                int extraSpaces = spacesNeeded % slots;

                for (int j = start; j < i; j++) {
                    int wordLength = strlen(words[j]);
                    memcpy(line + cursor, words[j], wordLength);
                    cursor += wordLength;

                    if (j < i - 1) { // Not the last word in the line
                        int spacesToAppend = spaceWidth + (j - start < extraSpaces ? 1 : 0);
                        memset(line + cursor, ' ', spacesToAppend);
                        cursor += spacesToAppend;
                    }
                }
            } else {
                memcpy(line, words[start], strlen(words[start]));
                cursor = strlen(words[start]);
                memset(line + cursor, ' ', spacesNeeded);
                cursor += spacesNeeded;
            }

            line[maxWidth] = '\0';
            result[totalLines++] = line;
            start = i;
            currentLineLength = 0;
        }

        currentLineLength += currentWordLength + (i > start ? 1 : 0); // Add 1 for space if it's not the first word
    }

    // Handle the last line separately (left-justified)
    int cursor = 0;
    char* line = malloc(maxWidth + 1);
    for (int j = start; j < wordsSize; j++) {
        int wordLength = strlen(words[j]);
        memcpy(line + cursor, words[j], wordLength);
        cursor += wordLength;
        if (j < wordsSize - 1) {
            line[cursor++] = ' ';
        }
    }
    memset(line + cursor, ' ', maxWidth - cursor);
    line[maxWidth] = '\0';
    result[totalLines++] = line;

    *returnSize = totalLines;
    return result;
}

int main() {
    char* words[] = {"This", "is", "an", "example", "of", "text", "justification."};
    int wordsSize = sizeof(words) / sizeof(words[0]);
    int maxWidth = 16;
    int returnSize;

    char** lines = fullJustify(words, wordsSize, maxWidth, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("\"%s\"\n", lines[i]);
        free(lines[i]);  // Free each line's memory
    }
    free(lines);  // Free the array of lines
    return 0;
}
