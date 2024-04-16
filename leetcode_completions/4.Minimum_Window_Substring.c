#include <stdio.h>
#include <string.h>
#include <limits.h>

char* minWindow(char* s, char* t) {
    int sLen = strlen(s);
    int tLen = strlen(t);
    
    if (sLen == 0 || tLen == 0 || sLen < tLen) return "";

    // Frequency arrays for characters in t and the current window in s
    int tFreq[128] = {0};
    int sFreq[128] = {0};

    // Initialize the frequency array for t
    for (int i = 0; i < tLen; i++) {
        tFreq[t[i]]++;
    }

    int required = 0;
    for (int i = 0; i < 128; i++) {
        if (tFreq[i] > 0) required++;
    }

    // Sliding window variables
    int l = 0, r = 0;
    int formed = 0;
    int ans[] = {-1, 0, 0};  // length, left, right

    while (r < sLen) {
        char c = s[r];
        sFreq[c]++;
        
        // If the current character's frequency in s matches the required frequency in t
        if (tFreq[c] > 0 && sFreq[c] == tFreq[c]) {
            formed++;
        }
        
        // Try and contract the window till the point it ceases to be 'desirable'
        while (l <= r && formed == required) {
            c = s[l];
            
            // Save the smallest window until now.
            if (ans[0] == -1 || r - l + 1 < ans[0]) {
                ans[0] = r - l + 1;
                ans[1] = l;
                ans[2] = r;
            }
            
            sFreq[c]--;
            if (tFreq[c] > 0 && sFreq[c] < tFreq[c]) {
                formed--;
            }
            
            l++;
        }
        
        r++;
    }
    
    if (ans[0] == -1) return "";
    
    // Need to return a new string that is a substring of s from ans[1] to ans[2]
    char* result = (char*)malloc((ans[0] + 1) * sizeof(char));
    strncpy(result, s + ans[1], ans[0]);
    result[ans[1]] = '\0'; // Null-terminate the string
    
    return result;
}
