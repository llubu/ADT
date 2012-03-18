/* This program refers to http://cslibrary.stanford.edu/109/TreeListRecursion.htm */
/* This file contains the main function which calls recgtr() from the t2l.c file */ 

# include <stdio.h>
# include <stdlib.h>
# include "tree.h"		/* Header file containing tree functions */
# include "t2l.h"		/* Header file for t2l.c file */

int main(void)
{
	struct node* root = NULL;
	struct node* head = NULL;		//head of the DC LL
	struct node* cu = NULL;
	int data,ck = 1;

	printf("\n Creating the BST\n");
	printf("\n Enter 0 to quit\n");
	scanf("%d",&ck);
	while(ck != 0)				//creating the BST
	{
		printf("\n Enter the DATA for the tree(BST) node\n");
		scanf("%d",&data);
		root = tree(root,data);
		printf("\n Enter 0 to quit\n"); 
		scanf("%d",&ck);
	}
	printf("\n Printing INORDER traversal of tree\n");
	print_tree_in(root);
	printf("\n PATHS of tree \n");
	printpath(root);

	printf("\n Calling func to convert BST to DC ll\n");
	
	recgtr(&head,root);

	printf("\n Printing the convert BST in form of list\n");
	printf("\n HEAD: %p\n",head);
	cu = head;
	do{
		printf("\n DATA: %d\t ADD: %p\t ADD_Prv_left: %p \t ADD_next_right: %p \n",cu->data,cu,cu->left,cu->right);
		cu = cu->right;	
	}while(cu != head);	
	


}


