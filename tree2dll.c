#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    struct node *left;
    struct node *right;
    int data;
} Node;

/* To add new nodes to a BST */
Node *add_node(Node *root, int data)
{
    Node *newNode = NULL;

    if ( !root ) {
	newNode = malloc(sizeof(Node));
	if ( !newNode )
	    return NULL;
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
    }

    if ( data < root->data )
	root->left = add_node(root->left, data);
    else if ( data >= root->data )
	root->right = add_node(root->right, data);

   return root;
}

void inorder(Node *root)
{
    if ( !root )
	return;
    
    inorder(root->left);
    printf("%d ,", root->data);
    inorder(root->right);
}

Node *append(Node *p, Node *n)
{
    Node *tail = NULL;

    if ( !p && n )
	return n;
    if ( p && !n )
	return p;

    p->left->right = n;
    tail = n->left;
    n->left = p;
    
    tail->right = p;
    p->left = tail;

    return p;
}

/* Main function to handle tree2dll */
Node *tree2dll(Node *root)
{
    Node *tmp_head = NULL;
    Node *l_head, *r_head;

    if ( !root )
	return NULL;

    l_head = tree2dll(root->left);
    r_head = tree2dll(root->right);

    root->left = root;
    root->right = root;

    tmp_head = append(l_head, root);
    tmp_head = append(tmp_head, r_head);

    return tmp_head;
}

int main()
{
    Node *root = NULL;
    Node *head = NULL;
    Node *tmp = NULL;
    int i = 0, num;

    while ( i < 11 ) {
	scanf("%d", &num);
	root = add_node(root, num);
	++i;
    }
    inorder(root);
    printf("\n");

    head = tree2dll(root);
    tmp = head->right;
    printf("%d ,", head->data);

    while ( tmp != head ) {
	printf("%d ,", tmp->data);
	tmp = tmp->right;
    }
    return 0;
}
