#ifndef _DS_H
#define _DS_H

typedef struct adt {
    struct adt *next;
    void *ptr;
} l_node;

typedef struct node {
    struct node *left;
    struct node *right;
    int data;
} Node;


typedef struct trie {
    struct trie *elm[26];
    int end;
} Trie;

typedef struct list {
    struct list *next;
    struct list *random;
    int data;
} Rlist;

typedef l_node Stack;

typedef struct que_node {
    struct que_node next;
    void *ptr;
} Que_node;

typedef struct Que {
    l_node *head;
    l_node *tail;
} Que;

Stack *push(Stack **top, Node *node);
Node *pop(Stack **top);
Node *seek_stack(Stack **top);

void trie_insert(Trie *root, char *arr);
int trie_search(Trie *root, char *arr);
int trie_del(Trie *root, char *arr, int len, int level);



#endif
