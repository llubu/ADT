# include <stdio.h>
# include <stdlib.h>
# include "tree.h"

int main()
{
	struct node* root = NULL;
	struct node* cur = NULL;
	struct node* root2 = NULL;
	int elm;
	int ch = 1;
	int sum = 0;
	int chk = 0;
	while(ch != 0)
	{
		printf("\n Enter the data for the tree node: ");
	        scanf("%d",&elm);
		root = tree(root,elm);
		printf("\n Enter 0 to terminate node creation: ");
		scanf("%d",&ch);
	}
	printf("\n PRINT TREE PREORDER");
	print_tree_pre(root);
	printf("\n PRINT TREE INORDER: \n");
	print_tree_in(root);
	printf("\n POST ORDER TREE TRAVERSAL: \n");
	print_tree_po(root);
	printf("\n SIZE of tree: %d\n",size(root));
	printf("\n MAX DEPTH of TREE: %d\n",maxdepth(root));
	printf("\n MIN VALUE IN TREE IS: %d\n",minval(root));
	printf("\n Enter the SUM to check for haspathsum: \n");
	scanf("%d",&sum);

	chk = haspathsum(root,sum);
	if(chk ==1)
	{
		printf("\n Tree has a path with sum: %d\n",sum);
	}
	else
	{
		printf("\n Tree does *NOT* have a path with sum: %d\n",sum);
	}
	printf("\n\n **PATH OF TREE**\n");
	printpath(root);
//	printf("\n CREATING MIRROR\n");
//	mirror(root);
  
//	printf("\n Creating double tree\n");
//	doubletree(root);
//      printf("\n PRINT TREE INORDER: \n");
//      print_tree_in(root);
//	printf("\n POST ORDER TREE TRAVERSAL: \n");
//      print_tree_po(root);
/*	printf("\n Enter another tree to chek for similarity\n");
	ch = 1;
	chk = 0;
	while(ch != 0)
        {
                printf("\n Enter the data for the tree node: ");
                scanf("%d",&elm);
                root2 = tree(root2,elm);
                printf("\n Enter 0 to terminate node creation: ");
                scanf("%d",&ch);
        }
	if(chk = sametree(root,root2))
	{
		printf("\n TREE ARE SAME\n");
	} */
	chk = 0;
	chk = isbst(root);
	if(chk)
	{
		printf("\n Tree IS BST\n");
	}
	else printf("\n TREE IS NOT BST\n");

}












	



