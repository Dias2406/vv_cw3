#include <stdlib.h>

typedef struct {
    int *nums;
    int size;
} MedianFinder;

MedianFinder* medianFinderCreate() {
    MedianFinder* obj = (MedianFinder*)malloc(sizeof(MedianFinder));
    obj->nums = NULL;
    obj->size = 0;
    return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    obj->nums = (int*)realloc(obj->nums, (obj->size + 1) * sizeof(int));
    int i = obj->size - 1;
    while (i >= 0 && obj->nums[i] > num) {
        obj->nums[i + 1] = obj->nums[i];
        i--;
    }
    obj->nums[i + 1] = num;
    obj->size++;
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->size % 2 == 0) {
        int mid1 = obj->nums[obj->size / 2 - 1];
        int mid2 = obj->nums[obj->size / 2];
        return (double)(mid1 + mid2) / 2.0;
    } else {
        return (double)obj->nums[obj->size / 2];
    }
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->nums);
    free(obj);
}

/**
 * Your MedianFinder struct will be instantiated and called as such:
 * MedianFinder* obj = medianFinderCreate();
 * medianFinderAddNum(obj, num);
 * double param_2 = medianFinderFindMedian(obj);
 * medianFinderFree(obj);
*/