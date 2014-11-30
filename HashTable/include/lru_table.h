/*
 * LRU Table
 *
 * A hashtable that can also remove the least recently accessed element.  An
 * access to an element occurs by either an insert or a lookup operation.
 *
 * Insert, Lookup, Remove, RemoveOldest operations are O(1) complexity.
 *
 */
#ifndef LRU_TABLE__LRU_TABLE_H
#define LRU_TABLE__LRU_TABLE_H

#include <stdbool.h>
#include <stdint.h>



enum {
    LRU_TABLE_HASH_KEY_SIZE_MAX = 20,
};

typedef struct LruTable_s LruTable;

/* Hash Table Meta Data
 */
struct LruTable_s {
    uint32_t maxSize;		        /* Max Size of the Hash Table */
    uint32_t currentSize;	        /* Current size of the Hash Table */
    uint32_t keyBits;		        /* Key bits to be used from Key */
    struct __tableEntry *htArray; 	/* Pointer to array of structure */
    struct __LruMeta *lruList;	        /* Poninter to DLL to maintain LRU state */
};

/* An entry in Hash Table */
struct __tableEntry {
    struct __node *chain;
};
/* Actual node in the Hash Table */
struct __node {
    int data;			/* Actual Data value hashed */
    int key;			/* Key for the corresponding value */
    struct __lru *lruPos;	/* Pointer to corresponding node in LRU list */
    struct __node *next;
    struct __node *prev;
};

/* LRU List Meta Data */
struct __LruMeta{
    struct __lru *head;		/* Head pointer to LRU list*/
    struct __lru *tail;         /* Tail pointer to LRU list */
};

/* Doubly Linked List to maintain LRU state.
   Actual node of the LRU list
 */
struct __lru {
    int data;
    struct __lru *prev;
    struct __lru *next;
    struct __node *backPt;	/* Pointer to the Node in the HT chain */
};

/*
 * Create and initialize an empty table.
 *
 * The size of the table is 2^hash_size_bits.
 *
 * @hash_key_size: Number of bits to use from the hash value.  Also sets the
 *      size of the table (2^hash_key_size).  Valid range is
 *      1..LRU_TABLE_HASH_KEY_SIZE_MAX.
 */
LruTable* LruTable_Create (int hash_key_size);

/*
 * Deallocate all memory resources used by table.
 */
void LruTable_Destroy (LruTable *table);

/*
 * Insert mapping from key to value.
 *
 * If key is already present in the table, then update its value.
 */
void LruTable_Insert (LruTable *table, int key, int value);

/* Lookup entry in the table.
 *
 * If there is a mapping from key to a value, then fill out_value with value.
 *
 * Returns: true if entry is found, false otherwise
 */
bool LruTable_Lookup (const LruTable *table, int key, int *out_value);

/*
 * Remove mapping for key, if any.
 */
void LruTable_Remove (LruTable *table, int key);

/*
 * Remove the least recently accessed value in the table.
 *
 * Fill out_value with the value that is removed, and remove the key-value mapping.
 *
 * Returns: false for empty table, true otherwise
 */
bool LruTable_RemoveOldest (LruTable *table, int *out_value);

uint32_t hash_Function (LruTable *table, int key);
void update_LRU (LruTable *table, struct __lru *pos, int value);
void add_LRU_node (LruTable *table, struct __node *node, int value);
void del_LRU_node (LruTable *table, struct __lru *pos);
struct __node *find_collision(struct __tableEntry *tentry, int key);
struct __node *add_new_chainEntry(LruTable *table, struct __tableEntry *tentry, int key, int value);



#endif // LRU_TABLE__LRU_TABLE_H
