#include <stdbool.h>
#include <stdlib.h>

#define MAX_LEVEL 16 // Maximum level for the Skiplist

// Define the Skiplist Node structure
typedef struct SkipListNode {
    int val;
    struct SkipListNode **forward; // Array of pointers to next nodes in different levels
} SkipListNode;

// Define the Skiplist structure
typedef struct {
    SkipListNode *header; // Pointer to the header node of the Skiplist
    int level;            // Current maximum level of the Skiplist
} Skiplist;

// Function to create a new node with a given value and level
SkipListNode *createNode(int val, int level) {
    SkipListNode *node = (SkipListNode *)malloc(sizeof(SkipListNode));
    node->val = val;
    node->forward = (SkipListNode **)malloc(sizeof(SkipListNode *) * level);
    for (int i = 0; i < level; i++) {
        node->forward[i] = NULL; // Initialize forward pointers to NULL
    }
    return node;
}

// Function to initialize the Skiplist
Skiplist *skiplistCreate() {
    Skiplist *obj = (Skiplist *)malloc(sizeof(Skiplist));
    obj->level = 1;
    obj->header = createNode(-1, MAX_LEVEL); // Header node with a very small value
    return obj;
}

// Function to search for a value in the Skiplist
bool skiplistSearch(Skiplist *obj, int target) {
    SkipListNode *curr = obj->header;
    for (int i = obj->level - 1; i >= 0; i--) {
        while (curr->forward[i] && curr->forward[i]->val < target)
            curr = curr->forward[i];
    }
    curr = curr->forward[0]; // Move to the next node in the bottom level
    return curr && curr->val == target; // Check if found
}

// Function to generate a random level for a new node
int randomLevel() {
    int lvl = 1;
    while (rand() % 2 == 0 && lvl < MAX_LEVEL)
        lvl++;
    return lvl;
}

// Function to insert a value into the Skiplist
void skiplistAdd(Skiplist *obj, int num) {
    SkipListNode *update[MAX_LEVEL]; // Array to keep track of nodes to update
    SkipListNode *curr = obj->header;
    for (int i = obj->level - 1; i >= 0; i--) {
        while (curr->forward[i] && curr->forward[i]->val < num)
            curr = curr->forward[i];
        update[i] = curr; // Update the array with the node before the insertion point
    }
    curr = curr->forward[0]; // Move to the next node in the bottom level
    int newNodeLevel = randomLevel(); // Generate a random level for the new node
    if (newNodeLevel > obj->level) { // If the new node's level is greater than the Skiplist's level
        for (int i = obj->level; i < newNodeLevel; i++)
            update[i] = obj->header; // Update the array with the header node
        obj->level = newNodeLevel; // Update the Skiplist's level
    }
    SkipListNode *newNode = createNode(num, newNodeLevel); // Create the new node
    for (int i = 0; i < newNodeLevel; i++) { // Insert the new node into the Skiplist
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
}

// Function to remove a value from the Skiplist
bool skiplistErase(Skiplist *obj, int num) {
    SkipListNode *update[MAX_LEVEL]; // Array to keep track of nodes to update
    SkipListNode *curr = obj->header;
    for (int i = obj->level - 1; i >= 0; i--) {
        while (curr->forward[i] && curr->forward[i]->val < num)
            curr = curr->forward[i];
        update[i] = curr; // Update the array with the node before the target
    }
    curr = curr->forward[0]; // Move to the next node in the bottom level
    if (curr && curr->val == num) { // Check if the target value exists
        for (int i = 0; i < obj->level; i++) { // Remove the target node from each level
            if (update[i]->forward[i] != curr)
                break;
            update[i]->forward[i] = curr->forward[i];
        }
        free(curr->forward); // Free memory allocated for the forward array
        free(curr); // Free memory allocated for the node
        while (obj->level > 1 && !obj->header->forward[obj->level - 1]) // Update the Skiplist's level
            obj->level--;
        return true;
    }
    return false; // If the target value does not exist
}

// Function to free memory allocated for the Skiplist
void skiplistFree(Skiplist *obj) {
    SkipListNode *curr = obj->header->forward[0];
    while (curr) { // Free memory for each node
        SkipListNode *next = curr->forward[0];
        free(curr->forward);
        free(curr);
        curr = next;
    }
    free(obj->header->forward); // Free memory for the forward array of the header node
    free(obj->header); // Free memory for the header node
    free(obj); // Free memory for the Skiplist object
}

