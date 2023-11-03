#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct shash_node_s {
    char *key;
    char *value;
    struct shash_node_s *next;
    struct shash_node_s *sprev;
    struct shash_node_s *snext;
} shash_node_t;

typedef struct shash_table_s {
    unsigned long int size;
    shash_node_t **array;
    shash_node_t *shead;
    shash_node_t *stail;
} shash_table_t;

// Create a new sorted hash table with the given size.
shash_table_t *shash_table_create(unsigned long int size) {
    shash_table_t *ht = malloc(sizeof(shash_table_t));
    ht->size = size;
    ht->array = malloc(sizeof(shash_node_t *) * size);
    ht->shead = NULL;
    ht->stail = NULL;
    return ht;
}

// Set the value for the given key in the hash table.
int shash_table_set(shash_table_t *ht, const char *key, const char *value) {
    // Calculate the hash index for the given key.
    unsigned long int index = key_index(key, ht->size);

    // Create a new shash_node_t for the key/value pair.
    shash_node_t *node = malloc(sizeof(shash_node_t));
    node->key = key;
    node->value = value;

    // Insert the new node into the sorted linked list.
    if (ht->shead == NULL) {
        // Empty hash table.
        ht->shead = node;
        ht->stail = node;
    } else {
        // Insert the new node in the correct position in the sorted linked list.
        shash_node_t *prev = NULL;
        shash_node_t *curr = ht->shead;
        while (curr != NULL && strcmp(curr->key, key) < 0) {
            prev = curr;
            curr = curr->snext;
        }

        if (prev == NULL) {
            // Insert the new node at the beginning of the linked list.
            ht->shead = node;
            node->snext = curr;
        } else {
            // Insert the new node after the previous node.
            node->snext = curr;
            prev->snext = node;
        }

        if (curr == NULL) {
            // Insert the new node at the end of the linked list.
            ht->stail = node;
        }
    }

    // Store the new node in the hash table array.
    ht->array[index] = node;

    return 0;
}

// Get the value for the given key from the hash table.
char *shash_table_get(const shash_table_t *ht, const char *key) {
    // Calculate the hash index for the given key.
    unsigned long int index = key_index(key, ht->size);

    // Get the node for the given key from the hash table array.
    shash_node_t *node = ht->array[index];

    // If the node is not found, return NULL.
    if (node == NULL) {
        return NULL;
    }

    // Return the value for the given key.
    return node->value;
}

// Print the hash table to the console.
void shash_table_print(const shash_table_t *ht) {
    // Traverse the sorted linked list and print each key/value pair.
    shash_node_t *node = ht->shead;
    while (nod
