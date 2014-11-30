#include <stdio.h>
#include <stdlib.h>
#include "ds.h"

Stack *push(Stack **top, Node *node)
{
    Stack *tmp = NULL;

    tmp = malloc(sizeof(Stack));
    if ( !tmp )
	return NULL;

    tmp->ptr = node;
    tmp->next = *top;
    *top = tmp;
    return tmp;
}

Node *pop(Stack **top)
{
    Stack *tmp = *top;
    Node *pt = NULL;

    if ( !tmp )
	return NULL;

    pt = (Node *) tmp->ptr;
    *top = tmp->next;
    free(tmp);
    return pt;
}

/* Do not pop top.. just returns a pointer to the top node*/
Node *seek_stack(Stack **top)
{
    Stack *tmp =  *top;
    Node *pt = NULL;

    if ( !tmp )
	return NULL;

    pt = (Node *) tmp->ptr;
    return pt;
}

/* Queue Init function */
void que_Init(Que **q)
{
    Que *tmp = NULL;

    tmp = malloc(sizeof(Que));
    if ( !tmp )
	return;
    tmp->head = NULL;
    tmp->tail = NULL;

    *q = tmp;
}
void que_destroy( Que **q)
{
    free(*q);
}
/* Enque operation on stack */
void enque(Que **q, void *data)
{
    Que_node *tmp = NULL;

    tmp = malloc(sizeof(Que_node));
    if ( !tmp )
	return;

   tmp->next = NULL;
   tmp->ptr = data;

   if ( *q->tail == NULL ) {
       *q->tail = tmp;
       *q->head = tmp;
       return;
   }
   *q->tail->next = tmp;
   *q->tail = tmp;
}

/* Deque a node from Queue */
void *deque(Que **q)
{
    Que_node *tmp = NULL;
    unsigned long *pt = NULL;

    if ( *q->head == NULL )
	return NULL;

    /* Last node in the queue */
    if ( *q->head == *q->tail && *q->head != NULL ) {
	tmp = *q->head;
	*q->head = *q->tail = NULL;
    }
    else {
	tmp = *q->head;
	*q->head = *q->head->next;
    }
    pt = (unsigned long *) tmp->ptr;
    free(tmp);
    return (void *) pt;
}

Trie *trie_newNode(void)
{
    Trie *tmp = NULL;
    int i = 0;

    tmp = malloc(sizeof(Trie));
    if ( !tmp )
	return NULL;
    else {
	for ( i = 0; i<26; i++ )
	    tmp->elm[i] = NULL;
	tmp->end = 0;
    }

    return tmp;
}

/* Lower case english alphabets */
void trie_insert(Trie *root, char *arr)
{
    char *tmp = arr;
    Trie *cur = root;
    int index;

    int len = 0, i = 0;

    if ( !arr )
	return;

    while( *tmp != '\0' ) {
	++len;
	++tmp;
    }
    tmp = arr;

    for ( i = 0; i<len; i++ )
    {
	index = tmp[i] - 'a';

	if ( !cur->elm[index] ) 
	    cur->elm[index] = trie_newNode();

	cur = cur->elm[index];
    }
    cur->end = 1;
}

/* Return 0 if not found, 1 if found, -1 if error */
int trie_search(Trie *root, char *arr)
{
    Trie *cur = root;
    char *tmp = arr;
    int i = 0, len = 0, index;

    if ( !cur || !arr )
	return -1;

    while( *tmp != '\0' ) {
	++len;
	++tmp;
    }

    tmp = arr;
    for ( i = 0; i<len; i++ ) 
    {
	index = tmp[i] - 'a';
	if ( !cur->elm[index] )
	    return 0;
	cur = cur->elm[index];
    }

    if ( cur->end )
	return 1;
}

int trie_del(Trie *root, char *arr, int len, int level)
{
    Trie *tmp = NULL;
    int i = 0, index;

    if ( root ) {
	if ( len == level ) {
	    if ( root->end ) {
		root->end = 0;
		/* Check if the current node has any child pointers */
		while ( i < 26 ) {
		    if ( root->elm[i] )
			return 0;
		    ++i;
		}
		return 1;
	    }
	}
	else {

	    index = arr[level] - 'a';
	    if ( trie_del(root->elm[index], arr, len, level+1) ) {

		free(root->elm[index]);
		root->elm[index] = NULL;
		
		if ( !root->end ) {
		    i = 0;
		    while ( i < 26 ) {
			if ( root->elm[i] )
			    return 0;
			++i;
		    }
		    return 1;
		}
	    }
	}
    }
    return 0;
}
