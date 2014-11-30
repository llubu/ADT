#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *next;
    int data;
} Node;

Node *add_node(Node *head, int data)
{
    Node *tmp = NULL;

    tmp = malloc(sizeof(Node));
    if ( !tmp )
	return NULL;

    tmp->next = head;
    head = tmp;
    tmp->data = data;

    return head;
}

Node *rev(Node *head)
{
    Node *cur = NULL;
    Node *prev = NULL;
    Node *nxt = NULL;

    if ( !head )
	return;

    cur = head;

    while(cur)
    {
	nxt = cur->next;
	cur->next = prev;
	prev = cur;
	cur = nxt;
    }

    return prev;
}

int main()
{
    Node *head = NULL;
    Node *cur = NULL;
    Node *revHead = NULL;

    int i = 0;

    for (i = 0; i< 5; i++)
    {
	head = add_node(head, i);
    }

    cur = head;

    while(cur)
    {
	printf("0x%x: %d\n", (unsigned int)cur, cur->data);
	cur = cur->next;
    }
    revHead = rev(head);

    cur = revHead;

    printf("\n\n");
    while(cur)
    {
	printf("0x%x: %d\n", (unsigned int)cur, cur->data);
	cur = cur->next;
    }
 

    return 0;
}
