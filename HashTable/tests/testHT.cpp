#include "CppUTest/TestHarness.h"
#include <iostream>
#include <ctime>

extern "C"
{
    #include <lru_table.h>
}


TEST_GROUP(HashTable)
{
    LruTable *table = NULL;
    static const int size = 20, maxSize = (1 << size);

    void setup()
    {
	table = LruTable_Create(size);
    }

    void teardown()
    {
	LruTable_Destroy(table);
    }
};

/*
 *  This is suit of test , check for the validity of
 *  the function LruTable_Create().
 *  
 */

TEST(HashTable, Test_LruTable_Create)
{
    int i;

    if ( !table )
	FAIL("CAN'T ALLOCATE MEMORY FOR HASH TABLE.");

    if ( table->maxSize != maxSize )
	FAIL("Incorrect Size Allocated!");

    if ( table->keyBits != size )
	FAIL("Incorrect keyBits Initialized!");

    if ( table->currentSize != 0 )
	FAIL("Incorrect current Size initialized!");

    if ( table->htArray == NULL )
	FAIL(" Constructor failed to initialize Hash table Array!");

    for ( i = 0; i < maxSize; i++) {
	if ( table->htArray[i].chain )
	    FAIL(" Constructor failed memset the Hash Table Array to 0s!");
    }

    if ( !table->lruList )
	FAIL(" Constructor failed to Initialize metaNode for LRU list!");

    if ( table->lruList->head || table->lruList->tail )
	FAIL(" Constructor failed to Initialize LRU list Head/Tail to NULL!");
}


/*
 * This test case suit test the validity of the Insert function
 * of the hash Table.
 *
 */
TEST(HashTable, Test_LruTable_Insert)
{
    int i = 0;
    uint32_t hash1, hash2, hash3;
    struct __node *current = NULL, *pt1, *pt2, *pt3;

    int key1 = 971, value1 = 45;
    int key2 = 71, value2 = 97;
    int key3 = 12, value3 = 33;


    if ( table->currentSize != 0 )
	FAIL(" Current Size is not 0!!");

    LruTable_Insert(table, key1, value1);
    if ( table->currentSize != 1 )
	FAIL(" Current Size is not 1 after one insert!!");

    LruTable_Insert(table, key2, value2);
    if ( table->currentSize != 2 )
	FAIL(" Current Size is not 2 after one insert!!");

    LruTable_Insert(table, key3, value3);
    if ( table->currentSize != 3 )
	FAIL(" Current Size is not 3 after one insert!!");

    hash1 = hash_Function(table, key1);
    hash2 = hash_Function(table, key2);
    hash3 = hash_Function(table, key3);

    /* Do a linear walk into HT and check for key value pairs just inserted */
    for ( i = 0; i<maxSize; i++ ) {
	current = table->htArray[i].chain;

	while ( current ) {
	    if ( current->key == key1 ) {
		if ( current->data != value1 ) {
    		    FAIL(" Insert to HT not correct Incorrect Key Value Pair-1!");
		}
	        pt1 = current;
//		std::cout << "KEY VAL-1: " << current->key << " " << current->data 
//		<< " " << std::hex << current << " "<<pt1 <<std::endl;
	    }
	    if ( current->key == key2 ) {
		if ( current->data != value2 ) {
    		    FAIL(" Insert to HT not correct Incorrect Key Value Pair-2!");
		}
	        pt2 = current;
	    }
	    if ( current->key == key3 ) {
		if ( current->data != value3) {
    		    FAIL(" Insert to HT not correct Incorrect Key Value Pair-3!");
		}
		pt3 = current;
	    }
	    current = current->next;
        }
    }

    
    LruTable_Insert(table, key1, 2);

    /* Check if it updated the existing key value pair */

    if ( pt1->key != key1 || pt1->data != 2 ) 
	FAIL(" Failed to update the existing Key's value in HT!");

    if ( !table->htArray[hash1].chain || !table->htArray[hash2].chain ||
	    !table->htArray[hash3].chain ) {
	FAIL(" Hash Function Failure!");
    }
    else {
	current = table->htArray[hash1].chain;
	while ( current ) {
	    if ( current == pt1 )
		break;
	    current = current->next;
	}
	if ( current != pt1 )
	    FAIL(" Hash Function Failure -1a!, hash is different then the actual slot in HT!");

	/* Check for 2nd Key value pair */
	current = table->htArray[hash2].chain;
	while ( current ) {
	    if ( current == pt2 )
		break;
	    current = current->next;
	}
	if ( current != pt2 )
	    FAIL(" Hash Function Failure -1b!, hash is different then the actual slot in HT!");

	/* Check for 2nd Key value pair */
	current = table->htArray[hash3].chain;
	while ( current ) {
	    if ( current == pt3 )
		break;
	    current = current->next;
	}
	if ( current != pt3 )
	    FAIL(" Hash Function Failure -1c!, hash is different then the actual slot in HT!");

    }
}

/*
 * this test check for the validity of the 
 * Lookup function of the Hash Table.
 *
 */

TEST(HashTable, Test_LruTable_Lookup)
{
    int key1 = 971, value1 = 45;
    int key2 = 71, value2 = 97;
    int key3 = 12, value3 = 33;
    int res1, res2, res3;


    LruTable_Insert(table, key1, value1);
    LruTable_Insert(table, key2, value2);
    LruTable_Insert(table, key3, value3);

    if ( !LruTable_Lookup(table, key1, &res1) ) {
	FAIL(" Lookup failed to find the added key value pair-1!");
    }
    else if ( res1 != value1 ) {
	FAIL(" Lookup found incorrect key value pair for key-1!");
    }

    if ( !LruTable_Lookup(table, key2, &res2) ) {
	FAIL(" Lookup failed to find the added key value pair-2!");
    }
    else if ( res2 != value2 ) {
	FAIL(" Lookup found incorrect key value pair for key-2!");
    }

    if ( !LruTable_Lookup(table, key3, &res3) ) {
	FAIL(" Lookup failed to find the added key value pair-3!");
    }
    else if ( res3 != value3 ) {
	FAIL(" Lookup found incorrect key value pair for key-3!");
    }

    LruTable_Insert(table, key1, 23);

    if ( !LruTable_Lookup(table, key1, &res1) ) {
	FAIL(" Lookup failed to find the added key value pair-1!");
    }
    else if ( res1 != 23 ) {
	FAIL(" Lookup found incorrect key value pair for key-1!");
    }

    if ( LruTable_Lookup(table, 77, &res1) )
	FAIL(" Lookup incorrectly got value for invalid key in HT!");

    if ( LruTable_Lookup(table, 77, NULL) )
	FAIL(" Lookup did not checked validity for out_value pointer!");

    if ( LruTable_Lookup(NULL, 77, &res1) )
	FAIL(" Lookup did not checked validity for LruTable pointer!");

}

/*
 * This test check for the validity of the 
 * HT remove function.
 */

TEST(HashTable, Test_LruTable_Remove)
{
    int key1 = 971, value1 = 45;
    int key2 = 71, value2 = 97;
    int key3 = 12, value3 = 33;
    int res1, res2, res3;

    /* Insert 3 key-value pairs in Hash table */
    LruTable_Insert(table, key1, value1);
    LruTable_Insert(table, key2, value2);
    LruTable_Insert(table, key3, value3);
    
    /* Check if they are there */
    if ( !LruTable_Lookup(table, key1, &res1) ) {
	FAIL(" Lookup failed to find the added key value pair-1!");
    }
    else if ( res1 != value1 ) {
	FAIL(" Lookup found incorrect key value pair for key-1!");
    }
    
    /* Check the size */
    if ( table->currentSize != 3 )
	FAIL(" Current Size is not 3 after 3 insert!!");
    /* Now remove 1entry and do a lookup & check size */
    LruTable_Remove(table, key1);
    if ( table->currentSize != 2 )
	FAIL(" Current Size is not 2 after one Remove!!");
    if ( LruTable_Lookup(table, key1, &res1) ) {
	FAIL(" Remove failed for an already inserted key value pair, pair is still present in HT!");
    }

    /* Now remove another and do a lookup & check size */
    LruTable_Remove(table, key2);
    if ( table->currentSize != 1 )
	FAIL(" Current Size is not 1 after two Remove calls!!");
    if ( LruTable_Lookup(table, key2, &res1) ) {
	FAIL(" Remove failed for an already inserted key value pair, pair is still present in HT!");
    }

    /* Now remove another and do a lookup & check size */
    LruTable_Remove(table, key3);
    if ( table->currentSize != 0 )
	FAIL(" Current Size is not 3 after three Remove calls!!");
    if ( LruTable_Lookup(table, key3, &res1) ) {
	FAIL(" Remove failed for an already inserted key value pair, pair is still present in HT!");
    }


    /* Just try again to check remove behavior on empty HT */
    LruTable_Remove(table, key1);
    if ( LruTable_Lookup(table, key1, &res1) ) {
	FAIL(" Remove failed for an already inserted key value pair, pair is still present in HT!");
    }
    if ( table->currentSize != 0 )
	FAIL(" Current Size is not 3 after three Remove calls!!");
 
}

/*
 * this test check for the validity 
 * of the RemoveOldest entry in the HT.
 *
 */

TEST(HashTable, Test_LruTable_RemoveOldest)
{
    int i = 0;
    int key1 = 971, value1 = 45;
    int key2 = 71, value2 = 97;
    int key3 = 12, value3 = 33;
    int res1, res2, res3;
    unsigned int lruLen = 0;
    struct __lru *cur = NULL;

    /* Insert 3 key-value pairs in Hash table */
    LruTable_Insert(table, key1, value1);
    LruTable_Insert(table, key2, value2);
    LruTable_Insert(table, key3, value3);
    
    /* Right Now key1-value1 pair should be LRU */

    if ( !LruTable_RemoveOldest(table, &res1) ) {
	FAIL(" Could not find a LRU entry in aleady setup HT!");
    }
    else if ( res1 != 45 ){
	FAIL(" Returned Incorrecct LRU Value from HT!");
    }

    if ( LruTable_Lookup(table, key1, &res1) ) {
	FAIL(" LRU_Remove failed for an already inserted key value pair, pair is still present in HT!");
    }

    /* Insert Key1-value1 pair again */ 
    LruTable_Insert(table, key1, value1);

    /* Right Now key-val 2 is LRU - lookup it, now key-value 3 should be LRU */
    LruTable_Lookup(table, key2, &res1);

    if ( !LruTable_RemoveOldest(table, &res1) ) {
	FAIL(" Could not find a LRU entry in aleady setup HT!");
    }
    else if ( res1 != value3 ){
	FAIL(" Returned Incorrecct LRU Value from HT!");
    }

    if ( LruTable_Lookup(table, key3, &res1) ) {
	FAIL(" LRU_Remove failed for an already inserted key value pair, pair is still present in HT!");
    }

    /* Now insert lots of entries in Hash Table */
    for ( i = 210; i< 1800; i++) 
	LruTable_Insert(table, i, i+1);

    /* At this point key-val2 should be LRU entry */
    if ( !LruTable_RemoveOldest(table, &res1) ) {
	FAIL(" Could not find a LRU entry in aleady setup HT!");
    }
    else if ( res1 != value2 ){ /* above loop touches key1 917 again making key 2 as LRU */
	FAIL(" Returned Incorrecct LRU Value from HT!");
    }

    if ( LruTable_Lookup(table, key2, &res1) ) {
	FAIL(" LRU_Remove failed for an already inserted key value pair, pair is still present in HT!");
    }

    /* Now check for a subset of LRU list */
    for ( i = 210; i<900 ; i++) {
	res1 = 0;

	if ( !LruTable_RemoveOldest(table, &res1) ) {
	    FAIL(" Could not find a LRU entry in aleady setup HT!");
	}
	else if ( res1 != i+1 ){
	    std::cout << "Remove Oldest Failed for key: " << i << "Value:  " << res1  << std::endl;
	    FAIL(" Returned Incorrecct LRU Value from HT! -BIG LOOP");
        }

	if ( LruTable_Lookup(table, i, &res1) ) {
	    std::cout << "Oldest entry removed above is still present:Key:  " << i << std::endl;
	    FAIL(" LRU_Remove failed for an already inserted key value pair, pair is still present in HT -2!");
        }
    }


    if ( LruTable_RemoveOldest(NULL, &res1) )
	FAIL(" LRU_Remove do not check for validity of LruTable pointer!");

    if ( LruTable_RemoveOldest(table, NULL) )
	FAIL(" LRU_Remove do not check for validity of out_value pointer!");
    
    cur = table->lruList->head;
    while ( cur ) {
	++lruLen;
	cur = cur->next;
    }
//    std::cout << " COLLISION : " << colli << " " << lruLen << std::endl;
    if ( lruLen != 900 || table->currentSize != 900 )
	FAIL(" Incorrect Len of LRU list after removing 900 oldest. Should be 900 now!");

}


/*
 * Test to check the performance of the HT.
 * Basically looks for the Number of collisions
 * and longest chain size in the cases of collisions.
 *
 */
TEST(HashTable, Test_HT_Collosion_Performance)
{
    struct __node *current = NULL, *tmp;
    struct __lru *cur = NULL;
    uint64_t colli = 0, start = 0, lruLen = 0, step = 0, maxchain = 0;
    int i;

    srand (time(NULL));

    if ( table->currentSize != 0 )
	FAIL(" Incorrect current Size. Should be 0 now!!. ");

    for ( i = 1; i <(table->maxSize); i++) {
	LruTable_Insert(table, start+i, start+i+1);
    }
//    std::cout << table->maxSize << " " << table->currentSize << " " << maxSize << std::endl;
    
    if ( table->currentSize != (table->maxSize-1) ) {
	std::cout << table->maxSize << " " << table->currentSize << " " << maxSize << std::endl;
	FAIL(" Incorrect current Size. Should be maxSize-1 now!!. ");
    }

    /* Count the collision manually */
    colli = 0;
    for ( i = 0; i < maxSize; i++) {
	current = table->htArray[i].chain;
	step = 0;

	while ( current ) {
	    ++step;
	    if ( step > 1 )	/* If current chain has more then 1 element => collision */
		colli++;
	    current = current->next;
	}
	if ( step > maxchain )
	    maxchain = step;
    }

    cur = table->lruList->head;
    while ( cur ) {
	++lruLen;
	cur = cur->next;
    }
    std::cout << " Collisions : " << colli << " Total Size: " << lruLen << " " << " Collision % = " 
	<< (colli*100)/lruLen << " MAX Size of CHAIN: " << maxchain << std::endl;
}
