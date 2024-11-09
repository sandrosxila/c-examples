#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hash-table.h"

void test_hash_table_set_and_get() {
    HashTable *ht = hash_table_create();

    // Insert some key-value pairs
    assert(hash_table_set(ht, "key1", 10));
    assert(hash_table_set(ht, "key2", 20));
    assert(hash_table_set(ht, "key3", 30));

    // Test retrieval of values
    assert(hash_table_get(ht, "key1") == 10);
    assert(hash_table_get(ht, "key2") == 20);
    assert(hash_table_get(ht, "key3") == 30);

    hash_table_destroy(ht);
    printf("test_hash_table_set_and_get passed\n");
}

void test_hash_table_set_and_get_large_numbers() {
    Item entries[36] = {
        {"key0", 0}, {"key1", 1}, {"key2", 2}, {"key3", 3}, {"key4", 4}, {"key5", 5},
        {"key6", 6}, {"key7", 7}, {"key8", 8}, {"key9", 9}, {"key10", 10},
        {"key11", 11}, {"key12", 12}, {"key13", 13}, {"key14", 14}, {"key15", 15},
        {"key16", 16}, {"key17", 17}, {"key18", 18}, {"key19", 19}, {"key20", 20},
        {"key21", 21}, {"key22", 22}, {"key23", 23}, {"key24", 24}, {"key25", 25},
        {"key26", 26}, {"key27", 27}, {"key28", 28}, {"key29", 29}, {"key30", 30},
        {"key31", 31}, {"key32", 32}, {"key33", 33}, {"key34", 34}, {"key35", 35}
    };

    HashTable *ht = hash_table_create();

    for (int i = 0; i < 36; i++) {
        assert(hash_table_set(ht, entries[i].key, entries[i].value));
    }

    for (int i = 0; i < 36; i++) {
        assert(hash_table_get(ht, entries[i].key) == entries[i].value);
    }

    hash_table_destroy(ht);
    printf("test_hash_table_set_and_get_large_numbers passed\n");
}


void test_hash_table_exists() {
    HashTable *ht = hash_table_create();

    hash_table_set(ht, "key1", 10);
    hash_table_set(ht, "key2", 20);

    // Check for existing keys
    assert(hash_table_exists(ht, "key1") == true);
    assert(hash_table_exists(ht, "key2") == true);

    // Check for a non-existing key
    assert(hash_table_exists(ht, "key3") == false);

    hash_table_destroy(ht);
    printf("test_hash_table_exists passed\n");
}

void test_hash_table_erase() {
    HashTable *ht = hash_table_create();

    hash_table_set(ht, "key1", 10);
    hash_table_set(ht, "key2", 20);
    hash_table_set(ht, "key3", 30);

    // Erase an existing key
    assert(hash_table_erase(ht, "key2") == true);
    assert(hash_table_exists(ht, "key2") == false);

    // Try to erase a non-existing key
    assert(hash_table_erase(ht, "key4") == false);

    hash_table_destroy(ht);
    printf("test_hash_table_erase passed\n");
}

void test_hash_table_iterator() {
    HashTable *ht = hash_table_create();

    hash_table_set(ht, "key1", 10);
    hash_table_set(ht, "key2", 20);
    hash_table_set(ht, "key3", 30);

    HashTableIterator *it = hash_table_iterator_create(ht);

    Item *item = hash_table_begin(it);
    while (item != NULL) {
        printf("Key: %s, Value: %d\n", item->key, item->value);
        item = hash_table_next(it);
    }

    free(it);
    hash_table_destroy(ht);
    printf("test_hash_table_iterator passed\n");
}

int main() {
    test_hash_table_set_and_get();
    test_hash_table_set_and_get_large_numbers();
    test_hash_table_exists();
    test_hash_table_erase();
    test_hash_table_iterator();

    printf("All tests passed successfully.\n");
    return 0;
}