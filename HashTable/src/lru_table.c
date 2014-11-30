#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lru_table.h>

/*
 * Design:
 *** The Hash Table has a meta data node of type LruTable which 
 * contains all the meta data for the HT state.
 *
 *** HT structure is as shown below in the diagram. The meta node
 * has a array of structure htArrayi of type struct __tableEntry
 * and of size == maxSize of the HT as passed to the LruTable_Create().
 *
 *** This array of structure contains a pointer to a structure of type 
 * struct __node. This pointer is only initialized if an entry is put in
 * this index of the HT.
 * In the case of collisions the same pointer is extended to add another
 * node and form a chain.
 *
 *** The LRU state is maintained by keeping a doubly Linked List where 
 * a new node or recently lookedup node is added at tail. The node at
 * the head is the LRU node in the Hash Table.
 * Each node in LRU list also maintains a back pointer to the chain entry
 * in the HT so that the corresponding entry in the hash table can be removed
 * when the remove oldest function is called to remove the LRU entry in the HT.
 *
 *** The collisions in the HT are resolved using the 'chaining method'.
 * LruTable *
 * ----------------
 * | maxSize      |         struct __tableEntry
 * | currentSize  |      |---------------------------------------------------------------
 * | keyBits      |      |	  |	  |						|
 * |              |      |	  |	  |						|
 * | *htArray  ---|----> | *chain | *chain| ............				|
 * | *lruList     |      |	  |   |	  |						|
 * |_____|________|      |____________|_________________________________________________|      	
 *       |                            |
 *       |                            |
 *       |                            v struct __node
 *       |                         -------------
 *       V struct __LruMeta        | data      |
 *  ___________                    | key       |
 * | *head    |                    | *lruPos   |
 * | *tail    |                    | *next     | ----> 
 * |__________|                    | *prev     |
 *      |                          |___________|
 *      |                                ^ 
 *      v struct __lru                   |
 *  |----------                          |
 *  | data    |                          |
 *  | *prev   |                          |
 *  | *next   |------->                  |    
 *  | *backPt |--------------------------|
 *  |_________|
 *  
 */




/* 
 * @param: hash_key_size: Number of bits to be used from Hash Value
 * @return: LruTable *:   Pointer to Hash Table just initialized
 *
 * Notes: 
 * This is the contructor for the Lru Hash Table. It initializes
 * all the data structures for the table and returns a pointer to
 * table. Initialized size of table is 2^hash_key_size.
 */
LruTable* LruTable_Create (int hash_key_size) 
{
    LruTable *table = NULL;

    if ( (hash_key_size < 1) || (hash_key_size > LRU_TABLE_HASH_KEY_SIZE_MAX) )
	return NULL;

    table = malloc(sizeof(LruTable));
    if ( !table )
	return NULL;
    
    table->maxSize =  1 << hash_key_size;
    table->keyBits = (uint32_t) hash_key_size;
    table->currentSize = 0;

    table->htArray = malloc(sizeof(struct __tableEntry) * table->maxSize);
    if ( !table->htArray ) {
	free(table);
	return NULL;
    }
    memset(table->htArray, 0, sizeof(struct __tableEntry) * table->maxSize);

    table->lruList = malloc(sizeof(struct __LruMeta));
    if ( !table->lruList ) {
	free(table->htArray);
	free(table);
	return NULL;
    }
    table->lruList->head = NULL;
    table->lruList->tail = NULL;

    return table;
}


/* 
 * @param: table: Pointer to LRU Hash Table
 * @return: void
 *
 * Notes:
 * This is a destructor for LRU Hash Table implementaion.
 * Takes the pointer to table and frees all memory.
 *
 */
void LruTable_Destroy (LruTable *table)
{
    int i = 0;
    struct __lru *current = NULL;
    struct __lru *tmp = NULL;
    struct __node *chainPt = NULL, *freeChain = NULL;

    if ( !table )
	return;

    /* Freeing up the memory for LRU list */
    for ( i = 0; i < table->maxSize; i++ ) {
	    chainPt = table->htArray[i].chain;
	    while ( chainPt ) {
		freeChain = chainPt->next;
		free(chainPt);
		chainPt = freeChain;
	    }
    }
    
    /* Now free the array of structure itself */
    free(table->htArray);

    if ( table->lruList ) {
	current = table->lruList->head;
	while ( current ) {
	    tmp = current->next;
	    free(current);
	    current = tmp;
	}
    }
    /* Free the metaNode for LRU list */
    free(table->lruList);
    free(table);
    memset(table, 0, sizeof(LruTable));
}


/*
 * @param: table: LruTable Pointer to HT metadata node.
 * @param: key:   key part of the key-value pair to be inserted.
 * @param: value: Value to be inserted in HT for the corresponding key.
 * @return: void
 *
 * Notes:
 * This function takes a key value pair and inserts it into the HT
 * if the key is already present just update the value.
 * The index in the HT is found by aplying a hash_Function().
 * On account of collision i.e. if the hashed value index for 'key'
 * already has an entry in the table, it makes a new 'chain' node and 
 * saves it at the head of the chain for the corresponding hash value index.
 *
 */
void LruTable_Insert (LruTable *table, int key, int value)
{
    uint32_t index;
    struct __node *collisionPos = NULL, *newNode = NULL;

//    printf("%s:%d\n",__func__, __LINE__);
    if ( !table ) 
	return;

    index = hash_Function(table, key);

//    printf("%s:%d\n",__func__, __LINE__);
    if ( table->htArray[index].chain ) { /* Atleast one Entry present */
	collisionPos = find_collision(&(table->htArray[index]), key);

	if ( collisionPos ) { /* Key Hit - just update value/LRU state */
	    collisionPos->data = value;
	    update_LRU(table, collisionPos->lruPos, value);
	}
    }

  //  printf("%s:%d\n",__func__, __LINE__);
    /* Key Miss or add a new node in chain for the collision  */
    if ( !collisionPos || !table->htArray[index].chain ) {
	newNode = add_new_chainEntry(table, &(table->htArray[index]), key, value);
 //   	printf("%s:%d\n",__func__, __LINE__);
	if ( !newNode )
	    return;
	add_LRU_node(table, newNode, value);
    	table->currentSize += 1;   		/* Increase the current size of HT */
    }
}


/*
 * @param: table: LruTable pointer to the HT meta data node.
 * @param: key:   The key part of key value pair
 * @param: out_value: Address of the int var where value is stored if key is found in HT.
 * @return: True/False: depending on if key is found or not.
 *
 * Notes:
 * This function hashes the key using hash_Function() and then checks if the hashed index is
 * found in HT. If yes returns true & stores corresponding value for the key in out_value else
 * returns false.
 * On account of collision it checks in the chain for the entry having the key value as 'key'.
 *
 */
bool LruTable_Lookup (const LruTable *table, int key, int *out_value)
{
    uint32_t index;
    struct __node *position = NULL;

    if ( !table || !out_value )
	return false;

    index = hash_Function((LruTable *) table, key);

    if ( table->htArray[index].chain ) {
	position = find_collision(&(table->htArray[index]), key);
	if ( position ) {
	    *out_value = position->data;
	    update_LRU((LruTable *) table, position->lruPos, position->data);
	    return true;
	}
    }
    return false;
}


/*
 * @param: table: LruTable pointer to the HT meta data node.
 * @param: key:   Key part of key-value pair to be removed from HT.
 * @return: void:
 *
 * Notes:
 * This function removes an already present entry from the HT corresponding
 * to the key passed. It also removes the corresponding LRU list entry for
 * the node.
 * 
 */
void LruTable_Remove (LruTable *table, int key)
{
    uint32_t index;
    struct __node *position;

    if ( !table ) 
	return;

    index = hash_Function(table, key);

    if ( table->htArray[index].chain ) {
//        printf("%s:%d\n",__func__, __LINE__);
	position = find_collision(&(table->htArray[index]), key);
//        printf("%s:%d\n",__func__, __LINE__);
	if ( !position ) {
	    return;
	}

//        printf("%s:%d\n",__func__, __LINE__);
	del_LRU_node(table, position->lruPos);
//        printf("%s:%d\n",__func__, __LINE__);
	if ( position == table->htArray[index].chain ) { /* Node is at head of chain */
	    table->htArray[index].chain = position->next;
//            printf("%s:%d:%x:\n",__func__, __LINE__, position);
	    if ( position->next )
		position->next->prev = NULL;
 //           printf("%s:%d\n",__func__, __LINE__);
	}
	else { /* Not at head */
//            printf("%s:%d:%x: %x:\n",__func__, __LINE__, position, table->htArray[index].chain);
	    position->prev->next = position->next;
//            printf("%s:%d\n",__func__, __LINE__);
	    if ( position->next )
		position->next->prev = position->prev;
	}
	free(position);
	table->currentSize -= 1;
    }
}

/*
 * @param: table: LruTable pointer to the HT meta node.
 * @param: out_value: The address of the int var where LRU entry
 *                    value is to be stored.
 * @return: True/False: If an LRU entry is present return True, False
 * 			otherwise.
 *
 * Notes: 
 * This function stores the Least recently used entry in the HT in out_value.
 * It also removed the entry in LRU list and from the Hash Table itself.
 *
 */
bool LruTable_RemoveOldest (LruTable *table, int *out_value)
{
    struct __node *position = NULL;
    if ( !table || !out_value ) 
	return false;

    if ( table->lruList->head ) {
	*out_value = table->lruList->head->data;
	position = table->lruList->head->backPt;
//        printf("%s:%d\n",__func__, __LINE__);
	LruTable_Remove(table, position->key);  /* Remove entry in HT & LRU list */
//        printf("%s:%d\n",__func__, __LINE__);
	return true;
    }
    return false;
}

/* Below are the internal function called from within the above API which are available for user use */

/*
 * @param: table: LruTable pointer to HT meta data node.
 * @paramL key:   Key which has to be hashed.
 * @return: Hashed value for the key.
 *
 * Notes:
 * The Hash Function Used is a modified form of
 * "Shift-Add-XOR" hash funtion. It returns a hash 
 * value/index into the HT.
 *
 */


uint32_t hash_Function ( LruTable *table, int key)
{
    uint32_t hash = 0, mask = 0xFFFFFFFF, ret;
    int i;

    for ( i = 0; i < 5; i++ )
	hash ^= ( hash << 5 ) + ( hash >> 2 ) + key;

    ret = hash & (mask >> (32 - table->keyBits));     /* Makes the hash index fall in the size range of HT */
    return ret;
}


/* 
 * @param: table: LruTable pointer to the Hash Table meta data node.  
 * @param: pos:   Pointer to the Hash Table chain node entry.
 * @pram:  value: The value to be updated.
 *
 * Notes:
 * Updates the value in the LRU list node and put it at the tail of LRU list.
 * Thereby maintaing LRU node at the head of the LRU list.
 *
 */
void update_LRU (LruTable *table, struct __lru *pos, int value)
{
    struct __lru *tmp = pos;

    if ( !table || !pos )
	return;

    pos->data = value;     /* Updating the new value */

    if ( table->lruList->head == table->lruList->tail 
	    || pos == table->lruList->tail )  /* Only node in the LRU list */
	return;

    if ( pos == table->lruList->head ) {
	table->lruList->head = table->lruList->head->next;
	table->lruList->head->prev = NULL;
	table->lruList->tail->next = tmp;
	tmp->prev = table->lruList->tail;
	tmp->next = NULL;
	table->lruList->tail = tmp;
    }
    else {
	tmp->next->prev = tmp->prev;
	tmp->prev->next = tmp->next;
	tmp->next = NULL;
	tmp->prev = table->lruList->tail;
	table->lruList->tail->next = tmp;
	table->lruList->tail = tmp;
    }
}

/*
 * @param: table: LruTable pointer to the HT meta data node.
 * @param: node:  Pointer to the HT entry chain node.
 * @param: value: The value to be added in the LRU node.
 * @return: void:
 * 
 * Notes:
 * This function adds a new node in the LRU list at the tail
 * therby maintaing the LRU node at the head. It also stores the
 * value in the node itself so that on Removing the LRU node it 
 * does not have to go look in the HT. 
 * Also contains a back pointer to the Hash Table chain node.
 *
 */
void add_LRU_node (LruTable *table, struct __node *node, int value)
{
    struct __lru *newNode = NULL;

    if ( !table || !node )
	return;

    newNode = malloc(sizeof(struct __lru));
    if ( !newNode )
	return;

    newNode->data = value;
    newNode->backPt = node;
    node->lruPos = newNode;  /* Updated the LRU pointer in node in chain */

    /* Check if LRU list is not initilized */
    if ( !table->lruList->head ) {

	newNode->next = NULL;
	newNode->prev = NULL;
	node->lruPos = newNode;
	table->lruList->head = newNode;
	table->lruList->tail = newNode;
    }
    else { 
	table->lruList->tail->next = newNode;
	newNode->prev = table->lruList->tail;
	newNode->next = NULL;
	table->lruList->tail = newNode;
	node->lruPos = newNode;
    }
}

/* 
 * @param: table: LruTable pointer to the HT meta node.
 * @param: pos:   Pointer to the LRU node in the LRU list.
 * @return: void:
 *
 * Notes:
 * Delete a given node from the LRU list.
 *
 */
void del_LRU_node (LruTable *table, struct __lru *pos)
{
    struct __lru *tmp = pos;

    if ( !table || !pos )
	return;

    if ( table->lruList->head == table->lruList->tail 
	    && table->lruList->head == pos ) { /* Only node in the LRU list */
	free(pos);
	table->lruList->head = NULL;
	table->lruList->tail = NULL;
	return;
    }

    if ( table->lruList->tail == pos ) {
	table->lruList->tail = table->lruList->tail->prev;
	table->lruList->tail->next = NULL;
	free(pos);
	return;
    }

    if ( table->lruList->head == pos ) {
	table->lruList->head = table->lruList->head->next;
	table->lruList->head->prev = NULL;
	free(pos);
	return;
    }

    tmp->next->prev = tmp->prev;
    tmp->prev->next = tmp->next;
    free(tmp);
}


/* 
 * @param: tentry: Pointer to the entry in the array of structure in HT.  
 * @param: key:    Key whose position is to be found in the HT chain.
 * @return: Returns a pointer to the node in chain if found NUll otherwise.
 *
 * Notes:
 * Check for the presence for a key in the HT chain. If a node is found
 * mattching the key return the pointer to the node else return NULL
 *
 */
struct __node *find_collision(struct __tableEntry *tentry, int key)
{
    struct __node *current = NULL;

    if ( !tentry || !tentry->chain )
	return NULL;

    current = tentry->chain;
    while ( current ) {
	if ( current->key == key )
	    return current;
	current = current->next;
    }
    return NULL;
}

/* 
 * @param: table: Pointer to HT meta data node.
 * @param: key:   Key part of the key value pair.
 * @param: value: Value part of the key value pair.
 * @return: Pointer to the new Node added in the chain.
 *
 * Notes:
 * Adds a new entry in the chain - always adds at the head of the chain.
 *
 */
struct __node *add_new_chainEntry(LruTable *table, struct __tableEntry *tentry, int key, int value)
{
    struct __node *newNode = NULL;

    if ( !tentry || table->maxSize == table->currentSize )
	return NULL;

    newNode = malloc(sizeof(struct __node));
    if ( !newNode )
	return NULL;

    newNode->data = value;
    newNode->key = key;
    newNode->prev = NULL;
    newNode->next = NULL;

    /* lruPos pointer is initialized in add_LRU_node()*/
    newNode->lruPos = NULL; /* till that call make it NULL */
    if ( !tentry->chain ) { /* Create the chain */
	newNode->next = NULL;
	tentry->chain = newNode;
    }
    else { /* Add at the head */
	newNode->next = tentry->chain;
	tentry->chain->prev = newNode;
	tentry->chain = newNode;
    }
    return newNode;
}
