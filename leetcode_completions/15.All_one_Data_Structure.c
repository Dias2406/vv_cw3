#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Bucket Bucket;
typedef struct KeyNode KeyNode;

struct KeyNode {
    char *key;
    KeyNode *prev;
    KeyNode *next;
    Bucket *bucket;
};

struct Bucket {
    int count;
    KeyNode *first;
    KeyNode *last;
    Bucket *prev;
    Bucket *next;
};

typedef struct {
    Bucket *head;
    Bucket *tail;
    KeyNode **keyMap;
} AllOne;

unsigned int hashKey(const char *key) {
    unsigned int hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) ^ c;  // hash * 33 ^ c
    }
    return hash;
}

AllOne* allOneCreate() {
    AllOne *obj = malloc(sizeof(AllOne));
    obj->head = obj->tail = NULL;
    obj->keyMap = calloc(10000, sizeof(KeyNode*));
    return obj;
}

void addBucketAfter(AllOne *obj, Bucket *prevBucket, Bucket *newBucket) {
    newBucket->prev = prevBucket;
    if (prevBucket) {
        newBucket->next = prevBucket->next;
        prevBucket->next = newBucket;
    } else {
        newBucket->next = obj->head;
        obj->head = newBucket;
    }
    if (newBucket->next) {
        newBucket->next->prev = newBucket;
    } else {
        obj->tail = newBucket;
    }
}

void removeBucket(AllOne *obj, Bucket *bucket) {
    if (bucket->prev) {
        bucket->prev->next = bucket->next;
    } else {
        obj->head = bucket->next;
    }
    if (bucket->next) {
        bucket->next->prev = bucket->prev;
    } else {
        obj->tail = bucket->prev;
    }
    free(bucket);
}

void addKeyToBucket(KeyNode *keyNode, Bucket *bucket) {
    if (bucket->first) {
        bucket->first->prev = keyNode;
    }
    keyNode->next = bucket->first;
    keyNode->prev = NULL;
    bucket->first = keyNode;
    if (!bucket->last) {
        bucket->last = keyNode;
    }
    keyNode->bucket = bucket;
}

void removeKeyNode(AllOne *obj, KeyNode *keyNode) {
    if (keyNode->prev) {
        keyNode->prev->next = keyNode->next;
    } else {
        keyNode->bucket->first = keyNode->next;
    }
    if (keyNode->next) {
        keyNode->next->prev = keyNode->prev;
    } else {
        keyNode->bucket->last = keyNode->prev;
    }
    if (!keyNode->bucket->first) {
        removeBucket(obj, keyNode->bucket);
    }
}

void allOneInc(AllOne* obj, char* key) {
    unsigned int index = hashKey(key) % 10000;
    KeyNode *keyNode = obj->keyMap[index];
    while (keyNode && strcmp(keyNode->key, key) != 0) {
        keyNode = keyNode->next;
    }
    if (!keyNode) {
        keyNode = malloc(sizeof(KeyNode));
        keyNode->key = strdup(key);
        keyNode->prev = keyNode->next = NULL;
        keyNode->bucket = NULL;
        if (obj->keyMap[index]) {
            obj->keyMap[index]->prev = keyNode;
        }
        keyNode->next = obj->keyMap[index];
        obj->keyMap[index] = keyNode;
        
        Bucket *bucket = obj->head;
        if (!bucket || bucket->count > 1) {
            bucket = malloc(sizeof(Bucket));
            bucket->count = 1;
            bucket->first = bucket->last = NULL;
            addBucketAfter(obj, NULL, bucket);
        }
        addKeyToBucket(keyNode, bucket);
    } else {
        Bucket *currentBucket = keyNode->bucket;
        Bucket *nextBucket = currentBucket->next;
        if (!nextBucket || nextBucket->count > currentBucket->count + 1) {
            nextBucket = malloc(sizeof(Bucket));
            nextBucket->count = currentBucket->count + 1;
            nextBucket->first = nextBucket->last = NULL;
            addBucketAfter(obj, currentBucket, nextBucket);
        }
        removeKeyNode(obj, keyNode);
        addKeyToBucket(keyNode, nextBucket);
    }
}

void allOneDec(AllOne* obj, char* key) {
    unsigned int index = hashKey(key) % 10000;
    KeyNode *keyNode = obj->keyMap[index];
    while (keyNode && strcmp(keyNode->key, key) != 0) {
        keyNode = keyNode->next;
    }
    Bucket *currentBucket = keyNode->bucket;
    if (currentBucket->count == 1) {
        removeKeyNode(obj, keyNode);
        if (keyNode->prev) {
            keyNode->prev->next = keyNode->next;
        }
        if (keyNode->next) {
            keyNode->next->prev = keyNode->prev;
        }
        if (obj->keyMap[index] == keyNode) {
            obj->keyMap[index] = keyNode->next;
        }
        free(keyNode->key);
        free(keyNode);
    } else {
        Bucket *prevBucket = currentBucket->prev;
        if (!prevBucket || prevBucket->count < currentBucket->count - 1) {
            prevBucket = malloc(sizeof(Bucket));
            prevBucket->count = currentBucket->count - 1;
            prevBucket->first = prevBucket->last = NULL;
            addBucketAfter(obj, currentBucket->prev, prevBucket);
        }
        removeKeyNode(obj, keyNode);
        addKeyToBucket(keyNode, prevBucket);
    }
}

char* allOneGetMaxKey(AllOne* obj) {
    if (obj->tail && obj->tail->last) {
        return obj->tail->last->key;
    }
    return "";
}

char* allOneGetMinKey(AllOne* obj) {
    if (obj->head && obj->head->first) {
        return obj->head->first->key;
    }
    return "";
}

void allOneFree(AllOne* obj) {
    while (obj->head) {
        Bucket *temp = obj->head;
        obj->head = obj->head->next;
        while (temp->first) {
            KeyNode *node = temp->first;
            temp->first = node->next;
            free(node->key);
            free(node);
        }
        free(temp);
    }
    free(obj->keyMap);
    free(obj);
}

