# include <stdio.h>
# include <stdlib.h>
# include "stack.h"



int push(struct node** topref, int da)
{
	struct node* newnode = NULL;
	
	newnode = malloc(sizeof(struct node));
	if(newnode == NULL)
	{
		printf("\n Can't allocate memory\n");
		return 0;
	}
	
	newnode->data = da;
	newnode->next = (*topref);
	(*topref) = newnode;
	
	printf("\n EXIT PUSH");
	return 1;
}

int pop(struct node** topref)
{
	struct node* tmp = NULL;		// tmp pointer
	int pop_data;
	
	if((*topref) != NULL)
	{
		tmp = (*topref);
		pop_data = tmp->data;
		(*topref) = (*topref)->next;
		free(tmp);
	}
	return pop_data;		//returning poped elemet frm the stack
}





