#include <stdio.h>

#include "hashtable.h"

int main(void)
{
    HashTable ht;
    int value;

    ht_init(&ht);

    ht_insert(&ht, "apple", 10);
    ht_insert(&ht, "banana", 20);
    ht_insert(&ht, "orange", 30);

    /* Updating an existing key */
    ht_insert(&ht, "apple", 100);

    if (ht_get(&ht, "apple", &value))
        printf("apple = %d\n", value);
    else
        printf("apple not found\n");

    if (ht_get(&ht, "banana", &value))
        printf("banana = %d\n", value);
    else
        printf("banana not found\n");

    if (ht_delete(&ht, "banana"))
        printf("banana deleted\n");

    if (!ht_get(&ht, "banana", &value))
        printf("banana not found\n");

    printf("\nHash table:\n");
    ht_print(&ht);

    ht_destroy(&ht);

    return 0;
}