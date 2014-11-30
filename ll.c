#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *next;
    int data;
} Node;

/* Adds a new node at the current head
 * & return new head pointer.  
 */
Node* add_node(Node *head, int data)
{
    Node *tmp = NULL;

    tmp = malloc(sizeof(Node));
    if ( NULL == tmp )
	return NULL;
    tmp->data = data;
    tmp->next = head;
    return tmp;
}

/* Deletes a node from LL. */
Node* del_node(Node *node, Node *head)
{
    Node *tmp = NULL;

    if ( NULL == node || NULL == head )
	return NULL;
    if ( node == head ) {
	tmp = head;
	head = tmp->next;
	free(tmp);
    }
    else {
	tmp = head;
	while ( tmp->next != node ){
	    tmp = tmp->next;
	}
	tmp->next = node->next;
	free(node);
    }
    return head;
}
	

int main()
{
    Node *head = NULL, *tmp = NULL;
    int i = 0;

    for ( i = 0; i<5; i++ )
    {
	head = add_node(head, i);
    }

    tmp = head;
    printf("Data: Addr:\n");
    while ( tmp != NULL )
    {
	printf("%d, %#x\n", tmp->data, tmp);
	tmp = tmp->next;
    }


    head = del_node(head->next->next->next, head);
    tmp = head;
    
    printf("Data: Addr:\n");
    while ( tmp != NULL )
    {
	printf("%d, %#x\n", tmp->data, tmp);
	tmp = tmp->next;
    }
    return 0;
}
 

