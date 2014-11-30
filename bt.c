#include <stdio.h>
#include <stdlib.h>
#include "ds.h"

/* Returns Level of a given node in BST */
int level(Node *root, Node *node, int lev)
{
    int tmp_level = 0;
    if ( !root )
	return 0;
    if ( root == node )
	return lev;

    tmp_level = level(root->left, node, lev+1);
    if ( tmp_level )
	return tmp_level;
    else
	return level(root->right, node, lev+1);
}

Node *find_max(Node *root)
{
    if ( !root->right )
	return root;
    else if ( root->right )
	return find_max(root->right);
}

Node *find_min(Node *root)
{
    if ( !root->left )
	return root;
    else if ( root->left )
	return find_min(root->left);
}


Node *balance_tree(Node *root)
{
    Node *tmp = NULL;

    if ( NULL == root->left 
	    && NULL == root->right ) {
//	free(root);
	return root;
    }

    if ( root->left ) {
	tmp = find_max(root->left);
	root->data = tmp->data;
	return balance_tree(tmp);
    }
    else if ( root->right ) {
	tmp = find_min(root->right);
	root->data = tmp->data;
	return balance_tree(tmp);
    }
}

void finalize(Node *root, Node *freed_node)
{
    if ( !root || !freed_node)
	return;
    if ( root->left == freed_node ) {
	root->left = NULL;
	return;
    }
    else if ( root->right == freed_node ) {
	root->right = NULL;
	return;
    }

    finalize(root->left, freed_node);
    finalize(root->right, freed_node);
}
Node *add_node(Node *root, int data)
{
    Node *tmp = NULL;

    if ( NULL == root ) {
	tmp = malloc(sizeof(Node));
	if ( NULL == tmp )
	    return NULL;
	tmp->data = data;
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
    }

    if ( data < root->data )
	root->left = add_node(root->left, data);
    else if ( data >= root->data )
	root->right = add_node(root->right, data);
   return root;
}
	
Node *del_node(Node *root, int data)
{
    Node *tmp = NULL;

    if ( !root )
	return NULL;

    if ( root->data == data ) 
	return balance_tree(root);

    if ( data < root->data ) {
	tmp = del_node(root->left, data);
	finalize(root, tmp);
    }
    else {
	tmp = del_node(root->right, data);
	finalize(root, tmp);
    }
}

void preorder(Node *root)
{
    if ( !root )
	return;

    printf("%d:%#x:\n", root->data, (unsigned int) root);
    preorder(root->left);
    preorder(root->right);
}
    
void inorder(Node *root)
{
    if ( !root )
	return;

    inorder(root->left);
    printf("%d:%#x:\n", root->data, (unsigned int) root);
    inorder(root->right);
     
}

void postorder(Node *root)
{
    if ( !root )
	return;

    postorder(root->left);
    postorder(root->right);
    printf("%d:%#x:\n", root->data, (unsigned int) root);
}

int tree_height(Node *root)
{
    int lh = 0, rh = 0;

    if ( !root )
	return 0;

    lh = tree_height(root->left);
    rh = tree_height(root->right);
    if ( lh >= rh )
	return (lh+1);
    else 
	return (rh+1);
}

int check_subTree(Node *r1, Node *r2)
{
    if ( !r1 && !r2 )
	return 1;
    else if ( !r1 && r2 )
	return 1;
    else if ( r1 && !r2 )
	return 0;
    else if ( r1->data != r2->data )
	return 0;
    
    if ( !check_subTree(r1->left, r2->left) )
	return 0;
    if ( !check_subTree(r1->right, r2->right) )
	return 0;
}


Node *find_node(Node *root, int data)
{
    if ( !root )
	return NULL;

    if ( root->data == data )
	return root;

    if ( data <= root->data )
	return find_node(root->left, data);
    else 
	return find_node(root->right, data);
}


void iter_preorder(Node *root)
{
    Stack *head = NULL;
    Node *tmp = NULL;

    push(&head, root);
    printf("Print ITER-PRE:%#x:\n", (unsigned int) head);

    while ( head ) {
	tmp = pop(&head);
	printf("%d: %#x, ", tmp->data, (unsigned int) tmp );

	if ( tmp->right )
	    push(&head, tmp->right);
	if ( tmp->left )
	    push(&head, tmp->left);
    }
}

void iter_inorder(Node *root)
{
   Node *current = root, *tmp = NULL;
   Stack *head = NULL;

   if ( !current )
       return;

   push(&head, root);
   current = current->left;

   while ( head || current ) {
       if ( current ) {
	   push(&head, current);
	   current = current->left;
       }
       else {
	   tmp = pop(&head);
	   printf("%d:%#x, ", tmp->data, (unsigned int) tmp);
	   current = tmp->right;
       }
   }
}

void iter_postorder(Node *root)
{
    Stack *head = NULL;
    Node *prev = root, *current = NULL;

    if ( !root )
	return;

    push(&head, root);
    
    while ( head ) {
	current = seek_stack(&head);

	if ( current->left && ( prev->left == current || prev->right == current 
		    || (current == prev && current == root) ) ) {
	    push(&head, current->left);
	    prev = current;
	}
	else if ( current->right  && ( prev->left == current || prev->right == current 
		    || (current == prev && current == root) ) ) {
	    push(&head, current->right);
	    prev = current;
	}
	else if ( !current->left && !current->right ) {
	    printf("%d:%#x, ", current->data, (unsigned int) current);
	    pop(&head);
	    prev = current;
	}
	else if ( current->left == prev ) {
	    if ( current->right ) {
		push(&head, current->right);
		prev = current;
	    }
	    else {
		printf("%d:%#x, ", current->data, (unsigned int) current);
		pop(&head);
		prev = current;
	    }
	}
	else if ( current->right == prev ) { 
	    printf("%d:%#x, ", current->data, (unsigned int) current);
	    pop(&head);
	    prev = current;
	}
    }
}


Node *rightRotation(Node *root)
{
    Node *newRoot = NULL;

    newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    root = newRoot;
    return root;
}


Node *leftRotation(Node *root)
{
    Node *newRoot = NULL;

    newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    root = newRoot;
    return root;
}


Node *balanceTree(Node *root)
{
    Node *Nroot = root;
    int rh = 0, lh = 0, diff = 0;

    if ( !root )
	return NULL;

    if ( !Nroot->left )
	lh = 0;
    else
	lh = tree_height(Nroot->left);
    
    if ( !Nroot->right )
	rh = 0;
    else
	rh = tree_height(Nroot->right);

    while ( (abs(lh - rh) ) > 1 ) {
	if ( lh > rh ) { /* Left Heavy */
	    if ( tree_height(Nroot->left->right) > tree_height(Nroot->left->left) ) { /* Left Subtree Right Heavy */
		/* Double Right Rotation LR */ 
		Nroot->left = leftRotation(Nroot->left);
		Nroot = rightRotation(Nroot);
	    }
	    else /* Single Right */
		Nroot = rightRotation(Nroot);
	}
	else if ( rh > lh ) { /* Right Heavy */
	    if ( tree_height(Nroot->right->left) > tree_height(Nroot->right->right) ) { /* Right SubTree left Heavy */
		/* Double Left Rotation RL */
		Nroot->right = rightRotation(Nroot->right);
		Nroot = leftRotation(Nroot);
	    }
	    else
		Nroot = leftRotation(Nroot);
	}
	rh = tree_height(Nroot->right);
	lh = tree_height(Nroot->left);
    }
    return Nroot;
}


int main()
{
    int i = 0, num, count = 0;
    Node *root = NULL;
    Node *r1 = NULL, *tmp = NULL;

    scanf("%d", &count);

    while ( i<count ) {
	scanf("%d", &num );
	root = add_node(root, num);
	++i;
    }
/*	
    printf("New Tree:\n");
    for (i = 0; i<5; i++)
    {
	scanf("%d", &num);
	r1 = add_node(r1, num);
    }

    if ( r1 ) {
	tmp = find_node(root, r1->data);
	if ( !tmp )
	    printf("R1 is NOT subtree of R2\n");
	else if ( check_subTree(r1, tmp) )
	    printf("R1 is a subtree of R2\n");
	else
	    printf("R1 is NOT subtree of R2\n");
    }
    else
	printf("R1 is NOT subtree of R2\n");
*/
    printf("DATA: ADDR:\n");
/*
    inorder(root);
    del_node(root, 10);
    printf("\n\n");
    inorder(root);
    printf("\n\n"); 
    postorder(root);
    printf("\n\n"); 
    preorder(root);
    printf("Height:%d:\n", tree_height(root)); 
    iter_preorder(root); 
    iter_inorder(root); */
    iter_postorder(root); 
    printf("\n\n"); 
    root = balanceTree(root);
    iter_postorder(root); 

    return 0;
}
