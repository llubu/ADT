/*** Header file for the t2l.c file which contains the following finctions and global variable ***/

#ifndef T2L_H
#define T2L_H

extern int min_val;	//defined in t2l.c

/** Recursive function to convert a given Binary Search Tree(BST) to a Doubly Circular Linked LIst(DC ll) ***/ 
struct node* recgtr(struct node**, struct node*);		

/** Helper function for the recftr() which takes left & right subtree returned from the last recursive call and the current root node and returns a single DC ll **/

struct node* append(struct node*, struct node*,struct node*);


#endif

