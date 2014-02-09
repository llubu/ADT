/*
* Basic Trie implementation
* @author: dZ0NE
* v1.0: Handles a-z, NOT Case sensitive
*/

#ifndef _TRIE_H
#define _TRIE_H

struct trie_node
{
    struct trie_node *child[27];    // 0th index is placeholder for '/0' then a,b,c .... follows
    int val;
};

typedef struct trie_node node;

int insert_node(node **dir, char *str);	// Inserts a new string in the trie
int pres(node *dir, char str);		// Check for presence of a string in trie
int rem(node *dir, char str);		// Deletes a string from trie
void print_dict(node *dict);		// Prints all strings present in trie

#endif
