#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int shop;
    int movie;
    int price;
    int rented;  // Using int to store boolean for rented status: 0 for false, 1 for true
} MovieEntry;

typedef struct {
    int numEntries;
    MovieEntry* entries;
    MovieEntry** unrentedMovies;  // Pointers to entries sorted by price for unrented movies
    MovieEntry** rentedMovies;    // Pointers to entries sorted by price for rented movies
    int unrentedSize;  // Number of unrented movies
    int rentedSize;    // Number of rented movies
} MovieRentingSystem;

int cmp(const void* a, const void* b) {
    MovieEntry* entry1 = *(MovieEntry**)a;
    MovieEntry* entry2 = *(MovieEntry**)b;
    if (entry1->price != entry2->price) return entry1->price - entry2->price;
    return entry1->shop - entry2->shop;
}

MovieRentingSystem* movieRentingSystemCreate(int n, int** entries, int entriesSize, int* entriesColSize) {
    MovieRentingSystem* obj = malloc(sizeof(MovieRentingSystem));
    obj->numEntries = entriesSize;
    obj->entries = malloc(sizeof(MovieEntry) * entriesSize);
    obj->unrentedMovies = malloc(sizeof(MovieEntry*) * entriesSize);
    obj->rentedMovies = malloc(sizeof(MovieEntry*) * entriesSize);
    obj->unrentedSize = entriesSize;
    obj->rentedSize = 0;

    for (int i = 0; i < entriesSize; i++) {
        obj->entries[i] = (MovieEntry){entries[i][0], entries[i][1], entries[i][2], 0};
        obj->unrentedMovies[i] = &obj->entries[i];
    }

    qsort(obj->unrentedMovies, entriesSize, sizeof(MovieEntry*), cmp);
    return obj;
}

int* movieRentingSystemSearch(MovieRentingSystem* obj, int movie, int* retSize) {
    int* result = malloc(sizeof(int) * 5);
    int count = 0; // Initialize count here
    *retSize = 0;
    for (int i = 0; i < obj->unrentedSize && count < 5; i++) {
        if (obj->unrentedMovies[i]->movie == movie && !obj->unrentedMovies[i]->rented) {
            result[count++] = obj->unrentedMovies[i]->shop;
        }
    }
    *retSize = count;
    return result;
}

void movieRentingSystemRent(MovieRentingSystem* obj, int shop, int movie) {
    for (int i = 0; i < obj->unrentedSize; i++) {
        if (obj->unrentedMovies[i]->shop == shop && obj->unrentedMovies[i]->movie == movie) {
            obj->unrentedMovies[i]->rented = 1;
            obj->rentedMovies[obj->rentedSize++] = obj->unrentedMovies[i];
            // Move the last unrented in current position to fill the gap
            obj->unrentedMovies[i] = obj->unrentedMovies[--obj->unrentedSize];
            qsort(obj->unrentedMovies, obj->unrentedSize, sizeof(MovieEntry*), cmp);
            qsort(obj->rentedMovies, obj->rentedSize, sizeof(MovieEntry*), cmp);
            break;
        }
    }
}

void movieRentingSystemDrop(MovieRentingSystem* obj, int shop, int movie) {
    for (int i = 0; i < obj->rentedSize; i++) {
        if (obj->rentedMovies[i]->shop == shop && obj->rentedMovies[i]->movie == movie) {
            obj->rentedMovies[i]->rented = 0;
            obj->unrentedMovies[obj->unrentedSize++] = obj->rentedMovies[i];
            // Move the last rented in current position to fill the gap
            obj->rentedMovies[i] = obj->rentedMovies[--obj->rentedSize];
            qsort(obj->unrentedMovies, obj->unrentedSize, sizeof(MovieEntry*), cmp);
            qsort(obj->rentedMovies, obj->rentedSize, sizeof(MovieEntry*), cmp);
            break;
        }
    }
}

int** movieRentingSystemReport(MovieRentingSystem* obj, int* retSize, int** retColSize) {
    int limit = obj->rentedSize < 5 ? obj->rentedSize : 5;
    int** report = malloc(sizeof(int*) * limit);
    *retColSize = malloc(sizeof(int) * limit);
    *retSize = limit;
    for (int i = 0; i < limit; i++) {
        report[i] = malloc(sizeof(int) * 2);
        report[i][0] = obj->rentedMovies[i]->shop;
        report[i][1] = obj->rentedMovies[i]->movie;
        (*retColSize)[i] = 2;
    }
    return report;
}

void movieRentingSystemFree(MovieRentingSystem* obj) {
    free(obj->entries);
    free(obj->unrentedMovies);
    free(obj->rentedMovies);
    free(obj);
}
