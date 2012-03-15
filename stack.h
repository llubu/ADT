#ifndef STACK_H_INCLUDE
#define STACK_H_INCLUDE

struct node
{
	int data;
	struct node* next;
};

int push(struct node ** topref, int da);
int pop(struct  node** topref);	

#endif




















