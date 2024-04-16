#include <stdio.h>
#include <string.h>
#include <ctype.h>

int evaluateCorrect(char* s) {
    int values[100], top = 0;  // Stack to store values temporarily
    char operators[100];       // To store operators
    int opTop = 0;
    
    for (int i = 0; i < strlen(s); i++) {
        if (isdigit(s[i])) {
            int num = s[i] - '0';
            // Process the multiplication immediately if the top of the operators stack is '*'
            while (opTop > 0 && operators[opTop - 1] == '*') {
                num = values[--top] * num;
                --opTop;  // Pop the operator stack
            }
            values[top++] = num;  // Push the current value to the stack
        } else if (s[i] == '*' || s[i] == '+') {
            operators[opTop++] = s[i];  // Push the operator to the stack
        }
    }
    
    // Now process all additions, which is straightforward as all multiplications have been resolved
    int total = values[0];
    for (int i = 1; i < top; i++) {
        total += values[i];  // Simply add all remaining numbers
    }
    
    return total;
}

int evaluateStandard(char* s) {
    int current = 0, total = 0;
    char lastOp = '+';

    for (int i = 0; i < strlen(s); i++) {
        if (isdigit(s[i])) {
            current = s[i] - '0';
            while (i + 1 < strlen(s) && isdigit(s[i + 1])) {
                i++;
                current = current * 10 + (s[i] - '0');  // Accumulate number
            }
            
            if (lastOp == '+') {
                total += current;
            } else if (lastOp == '*') {
                total *= current;
            }
            
            current = 0;
        }
        
        if (i < strlen(s) - 1 && (s[i] == '+' || s[i] == '*')) {
            lastOp = s[i];
        }
    }

    return total;
}

int scoreOfStudents(char* s, int* answers, int answersSize) {
    int correctAnswer = evaluateCorrect(s);
    int alternativeAnswer = evaluateStandard(s);
    int score = 0;

    for (int i = 0; i < answersSize; i++) {
        if (answers[i] == correctAnswer) {
            score += 5;
        } else if (answers[i] == alternativeAnswer && answers[i] != correctAnswer) {
            score += 2;
        }
    }

    return score;
}

int main() {
    char s1[] = "7+3*1*2";
    int answers1[] = {20, 13, 42};
    printf("Output: %d\n", scoreOfStudents(s1, answers1, 3));  // Expected: 7

    char s2[] = "3+5*2";
    int answers2[] = {13, 0, 10, 13, 13, 16, 16};
    printf("Output: %d\n", scoreOfStudents(s2, answers2, 7));  // Expected: 19

    return 0;
}
