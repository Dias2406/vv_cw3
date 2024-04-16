// You are given a 0-indexed array nums of non-negative integers, and two integers l and r.

// Return the count of sub-multisets within nums where the sum of elements in each subset falls within the inclusive range of [l, r].

// Since the answer may be large, return it modulo 109 + 7.

// A sub-multiset is an unordered collection of elements of the array in which a given value x can occur 0, 1, ..., occ[x] times, where occ[x] is the number of occurrences of x in the array.

// Note that:
// Two sub-multisets are the same if sorting both sub-multisets results in identical multisets.
// The sum of an empty multiset is 0.
 
// Example 1:
// Input: nums = [1,2,2,3], l = 6, r = 6
// Output: 1
// Explanation: The only subset of nums that has a sum of 6 is {1, 2, 3}.

// Example 2:
// Input: nums = [2,1,4,2,7], l = 1, r = 5
// Output: 7
// Explanation: The subsets of nums that have a sum within the range [1, 5] are {1}, {2}, {4}, {2, 2}, {1, 2}, {1, 4}, and {1, 2, 2}.

int countSubMultisets(int* nums, int numsSize, int l, int r) {
    
}