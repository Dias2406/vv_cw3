#include <stdbool.h>
#include <string.h>

bool isMatch(char* s, char* p) {
    int sLen = strlen(s);
    int pLen = strlen(p);
    
    // Create a DP table
    bool dp[sLen + 1][pLen + 1];
    memset(dp, false, sizeof(dp));
    
    // Base case: empty string and empty pattern match
    dp[0][0] = true;
    
    // Handle patterns like "a*", ".*", etc. where '*' can match zero characters
    for (int j = 1; j <= pLen; ++j) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];
        }
    }
    
    // Dynamic programming to fill the DP table
    for (int i = 1; i <= sLen; ++i) {
        for (int j = 1; j <= pLen; ++j) {
            if (s[i - 1] == p[j - 1] || p[j - 1] == '.') {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[j - 1] == '*') {
                // '*' can match zero or more of the preceding element
                dp[i][j] = dp[i][j - 2] || ((s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j]);
            }
        }
    }
    
    // The result will be at the bottom right corner of the DP table
    return dp[sLen][pLen];
}
