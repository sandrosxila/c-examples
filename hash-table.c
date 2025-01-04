#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

typedef struct Item
{
    char *key;
    int value;
    struct Item *next;
} Item;

typedef struct
{
    size_t capacity;
    size_t size;
    Item **items;
} HashTable;

typedef struct
{
    size_t index;
    Item *item;
    HashTable *hashTable;
} HashTableIterator;

static uint64_t hash_key(const char *key)
{
    uint64_t hash = FNV_OFFSET;
    for (const char *p = key; *p; p++)
    {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

HashTable *hash_table_create()
{
    HashTable *hashTable = malloc(sizeof(HashTable));

    hashTable->capacity = 16;
    hashTable->size = 0;
    hashTable->items = calloc(hashTable->capacity, sizeof(Item));

    return hashTable;
}

Item *item_create(const char *key, int value)
{
    Item *item = malloc(sizeof(Item));

    if (item == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    item->key = malloc(strlen(key) + 1);
    strcpy(item->key, key);
    item->value = value;
    item->next = NULL;

    return item;
}

static void hash_table_rehash(HashTable *hashTable)
{
    hashTable->items = realloc(hashTable->items, 2 * hashTable->capacity * sizeof(Item));

    for (size_t i = hashTable->capacity; i < 2 * hashTable->capacity; i++)
    {
        hashTable->items[i] = NULL;
    }

    for (size_t i = 0; i < hashTable->capacity; i++)
    {
        for (Item *current = hashTable->items[i], *previous = NULL, *nextNode; current != NULL; current = nextNode)
        {
            uint64_t hash = hash_key(current->key);
            size_t index = hash % (hashTable->capacity * 2);

            nextNode = current->next;

            if (index != i)
            {
                if (previous == NULL)
                {
                    hashTable->items[i] = hashTable->items[i]->next;
                }
                else
                {
                    previous->next = current->next;
                }

                current->next = NULL;

                if (hashTable->items[index] == NULL)
                {
                    hashTable->items[index] = current;
                }
                else
                {
                    for (Item *item = hashTable->items[index]; item != NULL; item = item->next)
                    {
                        if (item->next == NULL)
                        {
                            item->next = current;
                            break;
                        }
                    }
                }
            }
            else
            {
                previous = current;
            }
        }
    }

    hashTable->capacity *= 2;
}

int hash_table_get(HashTable *hashTable, const char *key)
{
    uint64_t hash = hash_key(key);
    size_t index = hash % hashTable->capacity;

    for (Item *current = hashTable->items[index]; current != NULL; current = current->next)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }
    }

    return 0;
}

bool hash_table_set(HashTable *hashTable, const char *key, int value)
{
    uint64_t hash = hash_key(key);
    size_t index = hash % hashTable->capacity;

    if (hashTable->items[index] == NULL)
    {
        hashTable->items[index] = item_create(key, value);
    }
    else
    {
        for (Item *current = hashTable->items[index]; current != NULL; current = current->next)
        {
            if (strcmp(current->key, key) == 0)
            {
                current->value = value;
                break;
            }

            if (current->next == NULL)
            {
                current->next = item_create(key, value);
                break;
            }
        }
    }

    hashTable->size++;

    if (hashTable->size == hashTable->capacity)
    {
        hash_table_rehash(hashTable);
    }

    return true;
}

bool hash_table_exists(HashTable *hashTable, const char *key)
{
    uint64_t hash = hash_key(key);
    size_t index = hash % hashTable->capacity;

    for (Item *current = hashTable->items[index]; current != NULL; current = current->next)
    {
        if (strcmp(current->key, key) == 0)
        {
            return true;
        }
    }

    return false;
}

bool hash_table_erase(HashTable *hashTable, const char *key)
{
    uint64_t hash = hash_key(key);
    size_t index = hash % hashTable->capacity;

    for (Item *current = hashTable->items[index], *previous = NULL; current != NULL; previous = current, current = current->next)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (previous == NULL)
            {
                hashTable->items[index] = hashTable->items[index]->next;
            }
            else
            {
                previous->next = current->next;
            }

            current->next = NULL;
            free(current);
            hashTable->size--;

            return true;
        }
    }

    return false;
}

size_t hash_table_size(HashTable *hashTable)
{
    return hashTable->size;
}

void hash_table_destroy(HashTable *hashTable)
{
    for (size_t i = 0; i < hashTable->capacity; i++)
    {
        for (Item *current = hashTable->items[i], *nextNode; current != NULL; current = nextNode)
        {
            nextNode = current->next;
            free(current->key);
            free(current);
        }
    }

    free(hashTable->items);
    free(hashTable);
}

HashTableIterator *hash_table_iterator_create(HashTable *hashTable)
{
    HashTableIterator *it = malloc(sizeof(HashTableIterator));

    if (it == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    it->index = 0;
    it->item = NULL;
    it->hashTable = hashTable;

    return it;
}

Item *hash_table_begin(HashTableIterator *it)
{
    for (size_t i = 0; i < it->hashTable->capacity; i++)
    {
        if (it->hashTable->items[i] != NULL)
        {
            it->index = i;
            it->item = it->hashTable->items[i];

            return it->item;
        }
    }

    return NULL;
}

Item *hash_table_next(HashTableIterator *it)
{
    if (it->item->next != NULL)
    {
        it->item = it->item->next;
        return it->item;
    }

    for (size_t i = it->index + 1; i < it->hashTable->capacity; i++)
    {
        for (Item *current = it->hashTable->items[i]; current != NULL; current = current->next)
        {
            it->index = i;
            it->item = current;
            return current;
        }
    }

    return NULL;
}