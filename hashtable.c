#include "hashtable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long hash(const char *key)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *key++))
        hash = ((hash << 5) + hash) + (unsigned char)c;

    return hash % TABLE_SIZE;
}

static char *string_duplicate(const char *str)
{
    char *copy = malloc(strlen(str) + 1);

    if (copy != NULL)
        strcpy(copy, str);

    return copy;
}

void ht_init(HashTable *ht)
{
    for (size_t i = 0; i < TABLE_SIZE; i++)
        ht->buckets[i] = NULL;
}

int ht_insert(HashTable *ht, const char *key, int value)
{
    unsigned long index = hash(key);
    HashNode *node = ht->buckets[index];

    /* Update existing key */
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            node->value = value;
            return 1;
        }

        node = node->next;
    }

    /* Create new node */
    node = malloc(sizeof(HashNode));
    if (node == NULL)
        return 0;

    node->key = string_duplicate(key);
    if (node->key == NULL) {
        free(node);
        return 0;
    }

    node->value = value;
    node->next = ht->buckets[index];
    ht->buckets[index] = node;

    return 1;
}

int ht_get(const HashTable *ht, const char *key, int *value)
{
    unsigned long index = hash(key);
    HashNode *node = ht->buckets[index];

    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            if (value != NULL)
                *value = node->value;

            return 1;
        }

        node = node->next;
    }

    return 0;
}

int ht_delete(HashTable *ht, const char *key)
{
    unsigned long index = hash(key);
    HashNode *node = ht->buckets[index];
    HashNode *prev = NULL;

    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            if (prev == NULL)
                ht->buckets[index] = node->next;
            else
                prev->next = node->next;

            free(node->key);
            free(node);

            return 1;
        }

        prev = node;
        node = node->next;
    }

    return 0;
}

void ht_destroy(HashTable *ht)
{
    for (size_t i = 0; i < TABLE_SIZE; i++) {
        HashNode *node = ht->buckets[i];

        while (node != NULL) {
            HashNode *next = node->next;

            free(node->key);
            free(node);

            node = next;
        }

        ht->buckets[i] = NULL;
    }
}

void ht_print(const HashTable *ht)
{
    for (size_t i = 0; i < TABLE_SIZE; i++) {
        HashNode *node = ht->buckets[i];

        if (node == NULL)
            continue;

        printf("[%zu] ", i);

        while (node != NULL) {
            printf("(%s, %d)", node->key, node->value);

            if (node->next != NULL)
                printf(" -> ");

            node = node->next;
        }

        printf("\n");
    }
}