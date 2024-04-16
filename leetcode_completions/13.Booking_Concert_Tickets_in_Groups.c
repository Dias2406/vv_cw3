#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int n;                  // number of rows
    long long m;            // number of seats per row (using long long to handle large seat counts)
    long long* nextFreeSeat; // points to the next free seat in each row
    long long* availableSeats; // count of available seats in each row
} BookMyShow;

BookMyShow* bookMyShowCreate(int n, long long m) {
    BookMyShow* obj = (BookMyShow*) malloc(sizeof(BookMyShow));
    obj->n = n;
    obj->m = m;
    obj->nextFreeSeat = (long long*) malloc(n * sizeof(long long));
    obj->availableSeats = (long long*) malloc(n * sizeof(long long));
    memset(obj->nextFreeSeat, 0, n * sizeof(long long));  // initialize all next free seats to 0
    for (int i = 0; i < n; ++i) {
        obj->availableSeats[i] = m;  // all seats are initially available
    }
    return obj;
}

int* bookMyShowGather(BookMyShow* obj, long long k, int maxRow, int* retSize) {
    for (int r = 0; r <= maxRow; ++r) {
        if (obj->availableSeats[r] >= k && obj->m - obj->nextFreeSeat[r] >= k) {  // enough seats available
            int* result = (int*) malloc(2 * sizeof(int));
            result[0] = r;
            result[1] = (int)obj->nextFreeSeat[r];
            obj->nextFreeSeat[r] += k;  // update next free seat pointer
            obj->availableSeats[r] -= k;  // update available seats count
            *retSize = 2;
            return result;
        }
    }
    *retSize = 0;  // no available space
    return NULL;
}

bool bookMyShowScatter(BookMyShow* obj, long long k, int maxRow) {
    long long totalAvailable = 0;
    for (int r = 0; r <= maxRow; ++r) {
        totalAvailable += obj->availableSeats[r];
    }
    if (totalAvailable < k) return false;  // not enough seats overall

    for (int r = 0; r <= maxRow; ++r) {
        if (k <= 0) break;
        long long usedSeats = (k < obj->availableSeats[r]) ? k : obj->availableSeats[r];
        obj->nextFreeSeat[r] += usedSeats;  // advance the next free seat pointer
        obj->availableSeats[r] -= usedSeats;  // decrease the available seats
        k -= usedSeats;  // decrease the remaining number of seats to allocate
    }
    return k == 0;  // successfully allocated all seats
}

void bookMyShowFree(BookMyShow* obj) {
    free(obj->nextFreeSeat);
    free(obj->availableSeats);
    free(obj);
}



