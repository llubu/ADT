// this creates the tree node when called by a function
// passes the pointer *value* to the caller which then uses as the new root pointer
// Caller should handel the value returned by tree()

# include <stdio.h>
# include <stdlib.h>
# include "tree.h"


struct node* tree(struct node* c_root,int c_data)
{
	struct node* r = NULL;
	struct node* newnode =NULL;


	r = c_root;
	
	if(r == NULL)			//position to insert the new node found, create a new node and attach at this position
	{
		newnode	= malloc(sizeof(struct node));
		if(newnode == NULL)
		{
			printf("\n FATAL ERROR, CANT ALLOCATE MEM\n");
			exit(1);
		}
		newnode->data = c_data;
		newnode->left = NULL;
		newnode->right = NULL;
		return newnode;
	}
	else  
	if(c_data <= (r->data))		//if data suplied is less the node data traverse through left subtree recursivelly
	{
		r->left = tree((r->left),c_data);
		return r;
	}
	else
	if(c_data > (r->data))		//if data suplied is greater then the node data traverse through the right subtree recursivelly
	{
		r->right = tree((r->right),c_data);
		return r;
	}
	printf("\n EXIT TREE\n");

}

void print_tree_in(struct node* c_root)	//Print tree nodes in INORDER TREE traversal
{
	struct node* r = NULL;
	r = c_root;

	if(c_root == NULL)
	{
		return;
	}
	if(r->left)
	{
		print_tree_in(r->left);
			
	}
	printf("\n :: %d",r->data);
	if(r->right)
	{
		print_tree_in(r->right);
	}
}

void print_tree_po(struct node* c_root)		// print tree nodes in POST ORDER TREE TRAVERSAL
{
	struct node* r = c_root;
	if((r->left == NULL) && (r->right == NULL))
	{
		printf("\n :: %d",r->data);
		return;
	}
	if(r->left)
	{
		print_tree_po(r->left);
	}
	if(r->right)
	{
		print_tree_po(r->right);
	}
	printf("\n :: %d",r->data);
}


int size(struct node* c_root)		//function to calculate the size of the tree
{
        struct node* r = c_root;
        int s= 0;
        if(r == NULL)
        {
                return 0;
        }
        if(r->left)
        {
                s = s + size(r->left);
        }
        if(r->right)
        {
                s = s + size(r->right);
        }
	return ++s;
}

int maxdepth(struct node* c_root)		//this function returns the max depth of the BT
{
	struct node* r = c_root;
	int ri = 0;
	int l = 0;

	if((r->left == NULL) && (r->right == NULL))
	{
		return 0;
	}
	if(r != NULL)
	{
		++l;
		++ri;
	}
	if(r->left)
	{
		l += maxdepth(r->left);
	}
	if(r->right)
	{
		ri += maxdepth(r->right);
	}
	if( ri >= l)
	{
		return ri;
	}
	else
	{
		return l;
	}
}


int minval(struct node* c_root)		//this finds the minimum value in the BT
{
	struct node* r = c_root;
	int val = 0;

	if( (r->left == NULL) || ((r->left == NULL) && (r->right == NULL)))
	{
		return r->data;
	}
	if(r->left)
	{
		val = minval(r->left);
		return val;
	}
}


int haspathsum(struct node* c_root, int sum)	//finds a path having sum supplied by user
{
	struct node* r = c_root;
	int ret1 = 0;
	int ret2 = 0;
	if((r->left) == NULL && (r->right) == NULL)
	{
		sum -= (r->data);
		if(sum == 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	if(r != NULL)
	{
		sum -= (r->data);
	}
	if(r->left)
	{
		ret1 = haspathsum(r->left,sum);
		
	}
	if(r->right)
	{
		ret2 = haspathsum(r->right,sum);
	}
	if(ret1 == 1 || ret2 == 1)
	{
		return 1;
	}
	else
	{	
		return 0;
	}
}

int printpathre(struct node* r, int path [],int len)	//used by printpath() to recursivly print the tree
{
	int n;
	
	if((r->left == NULL) && (r->right == NULL))
	{
		path[len+1] = r->data;
		++len;
		printf("\n The Path is:\n");
		for(n=0;n<=len && path[n] != -3;n++)
		{
			printf("\n :: %d ::",path[n]);
		}
		printf("\n length of path is: %d\n",len);
		path[len] = -3;
		--len;
		return len;
	}
	if(r != NULL)
	{
		path[len+1] = r->data;
		++len;
	}
	if(r->left)
	{
		len = printpathre(r->left,path,len);
	}
	if(r->right)
	{
		len = printpathre(r->right,path,len);
	}
	path[len] = -3;
	--len;
	return len;

}		


void printpath(struct node* c_data)		//Prrints the root to leaf paths of the tree
{
	struct node* r = c_data;
	int path[20];
	int i;
	int len = -1;
	for(i=0;i<=19;i++)
	{
		path[i] = -3; 		//marker to check for end of array
	}
	
	printpathre(r,path,len);
}

void mirror(struct node* c_root)		//creates a mirror tree of the original tree
{
	struct node* r = c_root;
	struct node* tmp = NULL;

	if((r->left == NULL) && (r->right == NULL))
	{
		return;
	}
	if((r->left != NULL) || (r->right != NULL))
	{
		tmp = r->left;
		r->left = r->right;
		r->right = tmp;
	}
	if(r->left)
	{
		mirror(r->left);
	}
	if(r->right)
	{
		mirror(r->right);
	}
}


int sametree(struct node* t1, struct node* t2)
{
	int k = 0;
	if(t1 == NULL && t2 == NULL)
	{
		return 1;
	}
	if(t1 != NULL && t2 != NULL)
	{
		if(t1->data == t2->data)
		{
			k = 1;
		}
	}
	if((t1->left != NULL))
	{
		if(t2->left == NULL)
		{	
			printf("\n TREE ARE NOT SAME\n");
			exit (0);
		}
		else
		if(t2->left)
		{
			k = sametree(t1->left,t2->left);
		}
	}		
	if(t1->right != NULL)
	{
		if(t2->right == NULL)
		{
			printf("\n TREE ARE NOT SAME\n");
			exit(0);
		}
		else
		if(t2->right)
		{
			k = sametree(t1->right,t2->right);
		}
	}
	return k;
}	


int min(struct node* r)
{
	int l = 0;
	int ri = 0;
	if(r->left == NULL && r->right == NULL)
	{
		return (r->data);
	}
	if(r->left)
	{
		l = min(r->left);
	}
	if(r->right)
	{
		ri = min(r->right);
	}
	if(l <= ri)
	{
		if(l < r->data)
		{
			return l;
		}
		else return (r->data);
	}
	else
	if(ri < l)
	{
		if(ri < r->data)
		{
			return ri;
		}
		else return (r->data);
	}
}


int max(struct node* r)
{
	int l = 0;
	int ri = 0;

	if(r->left == NULL && r->right == NULL)
	{
		return (r->data);
	}
	if(r->left)
	{
		l = max(r->left);
	}
	if(r->right)
	{
		ri = max(r->right);
	}
/*    ************************************** */	
	if(l >= ri)
        {
                if(l > r->data)
                {
                        return l;
                }
                else return (r->data);
        }       
        else
        if(ri > l)
        {
                if(ri > r->data)
                {
                        return ri;
                }
                else return (r->data);
        }
}


int isbst(struct node* r)
{
	int ck;
	int min1;
	int max1;

	if(r == NULL)
	{
		printf("\n EMPTY TREE");
		return 0;
	}
	ck = r->data;
	if(r->left)
	{
		max1 = max(r->left);
	}
	if(r->right)
	{
		min1 = min(r->right);
	}
	
	if(min1 >= ck || max1 <= ck)
	{
		return 1;
	}
	else return 0;
}
		
