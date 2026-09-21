#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>

#define TABLE_SIZE 101

typedef struct HashNode {
    char *key;
    int value;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode *buckets[TABLE_SIZE];
} HashTable;

void ht_init(HashTable *ht);
void ht_destroy(HashTable *ht);

int ht_insert(HashTable *ht, const char *key, int value);
int ht_get(const HashTable *ht, const char *key, int *value);
int ht_delete(HashTable *ht, const char *key);

void ht_print(const HashTable *ht);

#endif