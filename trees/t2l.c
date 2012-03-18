/** Function to convert a given BST to DC linked list**/

# include <stdio.h>
# include <stdlib.h>
# include "tree.h"
# include "t2l.h"


int min_val = 99999;		// keep track of the minimum data node of BST and helps to find the head of DC LL, Can also initialize to highest int value(signed) 2147483647

struct node* recgtr(struct node** headref, struct node* r)		//argumenst: headref head pointer for DC LL declared in gtr(), r: root of the tree/subtree passed to recursion
{
	struct node* h1 = NULL;					// h1: keep tracks of the left subtree returned from the last recursive call
	struct node* h2 = NULL;					// h2: same as h1 but ofr the right subtree 
	struct node* tmp = NULL;				// tmp: temporary var , just to catch value returned from append 

	if(r->left == NULL && r->data < min_val)	// this condidions checks for the mim node data and makes that node as head of the DC ll
	{
		(*headref) = r;
		min_val = r->data;
	}
	if((!r->right) && (!r->left))		// BASE CASE of the recusion: if a leaf is found in the BST convert the leaf node into a single node DC ll
	{
		r->left = r;
		r->right = r;
		return r;
	}

	if(r->left)
	{
		h1 = recgtr(headref,r->left);
	}
	if(r->right)
	{
		h2 = recgtr(headref,r->right);
	}
	
	tmp = append(h1,h2,r);
	return tmp;
}


struct node* append(struct node* h11, struct node* h22, struct node* rr)
{
	struct node* tail = NULL;			// temp var to keep track of last node of list
	
	if(h11 && h22) 			// for the case when for the current recursive call both left and right subtree are returned form the last call
	{
		if(rr->data >h11->data) 	// putting the root node in its correct position between left and right subtree returned from the last call
		{
			if((h11->left) && ((h11->left->data) < rr->data))
			{
				h11->left->right = rr;			
				rr->left = h11->left;
			}
		}

		if(rr->data < h22->data)
		{
			rr->right = h22;
			tail = h22->left;
			h22->left = rr;
		}
		h11->left = tail;
		tail->right = h11;
		return h11;
	}
	if((!h11) && h22)		// when last call only returned the right subtree
	{
		if(rr->data < h22->data)
		{
			rr->right = h22;
			rr->left = h22->left;
			h22->left->right = rr;
			h22->left = rr;
		}
		return rr;
	}	
	if(h11 && (!h22))		// when last call only returned the left subtree
	{
		if(rr->data > h11->data)
		{
			if((h11->left) && ((h11->left->data) <rr->data))
			{
				h11->left->right = rr;
				rr->left = h11->left;
				h11->left = rr;
				rr->right = h11;
			}
		}
		return h11;
	}
}

	
