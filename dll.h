#ifndef DLL_H_INCLUDE
#define DLL_H_INCLUDE

struct node
{
	int data;
	struct node* next;
	struct node* prev;
};


void create_node(struct node** headref);
void del_node(struct node** headref,int del_data);

#endif



















