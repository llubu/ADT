//creating doubly lineked list

# include <stdio.h>
# include <stdlib.h>
# include "dll.h"

void create_node(struct node** headref)
{
	struct node* tmp = NULL;
	struct node* newnode = NULL;
	int ch = 1;
	int da;

	while(ch != 0)
	{
		printf("\n ENTER DATA: ");
		scanf("%d",&da);
		
		newnode = malloc(sizeof(struct node));
		if( newnode == NULL)
		{
			printf("\n EXIT NO MEM");
			exit(0);
		}
		newnode->data = da;
		if((*headref) == NULL)
		{
			newnode->next = (*headref);
			newnode->prev = (*headref);
			(*headref) = newnode;
		}
		else
		 if((*headref) != NULL)
		 {
			newnode->next = (*headref);
			(*headref)->prev = newnode;
			newnode->prev = NULL;
			(*headref) = newnode;
		 } 	
		printf("\n ENTER 0 to exit: ");
		scanf("%d",&ch);
	 }
}


void del_node(struct node** headref,int del_data)
{
	struct node* tmp = NULL;
	
	tmp =(*headref);
	while(tmp != NULL && tmp->data != del_data)
	{
		tmp = tmp->next;
	}
	if(tmp == NULL)
	{
		printf("\n ELEMEMT not found cant delete");
		exit(0);
	}
	if(tmp->next == NULL && tmp->prev == NULL)
	{
		(*headref) = NULL;
		free(tmp);
		return ;
	}	
	if(tmp == (*headref))
	{
		tmp->next->prev = NULL;
		(*headref) = tmp->next;
		free(tmp);
	}
	if(tmp->next != NULL)
	{
		tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
                free(tmp);
	}
	if(tmp->next == NULL)
	{
		tmp->prev->next = NULL;
		free(tmp);
	}


}















