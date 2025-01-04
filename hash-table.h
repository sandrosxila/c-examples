#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct Item
{
    const char *key;
    const int value;
} Item;
typedef struct HashTable HashTable;
typedef struct HashTableIterator HashTableIterator;

HashTable *hash_table_create();
Item *item_create(const char *key, int value);
int hash_table_get(HashTable *hashTable, const char *key);
bool hash_table_set(HashTable *hashTable, const char *key, int value);
bool hash_table_exists(HashTable *hashTable, const char *key);
bool hash_table_erase(HashTable *hashTable, const char *key);
size_t hash_table_size(HashTable* hashTable);
void hash_table_destroy(HashTable *hashTable);
HashTableIterator *hash_table_iterator_create(HashTable *hashTable);
Item *hash_table_begin(HashTableIterator *it);
Item *hash_table_next(HashTableIterator *it);

#endif // HASH_TABLE_H