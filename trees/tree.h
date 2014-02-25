// header file for tree which creates a new tree node and attaches it to the correct position in the tree
// Bases on *BINARY SEARCH TREE*

#ifndef TREE_H
#define TREE_H

struct node
{
	int data;
	struct node* left;
	struct node* right;
};

struct node* tree(struct node* c_root, int da);	//Callee passes the copy of current root & data to tree()
int size(struct node* c_root);
void iter_inorder(struct node* c_root);	//Iterative Inorder traversal
void print_tree_in(struct node* c_root);
void print_tree_po(struct node* c_root);
void print_tree_pre(struct node* c_root);
int maxdepth(struct node* c_root);
int minval(struct node* c_root);
int haspathsum(struct node* c_root,int sum);
int printpathre(struct node* , int path [],int);
void printpath(struct node*);
void mirror(struct node*);
void doubletree(struct node*);
int sametree(struct node* , struct node*);
int min(struct node*);
int max(struct node*);
int isbst(struct node*);

#endif
