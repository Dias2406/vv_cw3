#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int countSubMultisets(int* nums, int numsSize, int l, int r) {
    int maxElement = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > maxElement) {
            maxElement = nums[i];
        }
    }

    // Frequency array
    int* freq = (int*)calloc(maxElement + 1, sizeof(int));
    for (int i = 0; i < numsSize; ++i) {
        freq[nums[i]]++;
    }

    // dp[x] will store the number of ways to get sum x
    int maxSum = numsSize * maxElement;
    int* dp = (int*)calloc(maxSum + 1, sizeof(int));
    dp[0] = 1;  // There is one way to make 0 sum, which is to select no elements

    // Process each number according to its frequency
    for (int num = 1; num <= maxElement; ++num) {
        if (freq[num] > 0) {
            for (int sum = maxSum; sum >= 0; --sum) {
                // dp[sum] should add combinations from dp[sum - num], dp[sum - 2*num], ..., dp[sum - freq[num]*num]
                for (int k = 1; k <= freq[num] && sum >= k * num; ++k) {
                    dp[sum] = (dp[sum] + dp[sum - k * num]) % MOD;
                }
            }
        }
    }

    // Calculate the result by summing valid dp entries
    int result = 0;
    for (int sum = l; sum <= r; ++sum) {
        result = (result + dp[sum]) % MOD;
    }

    free(freq);
    free(dp);

    return result;
}

