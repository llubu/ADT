# include <stdio.h>
# include <stdlib.h>
# include "dll.h"

int main()
{
//	int ch = 1;
//	int elm;
	int po_el;
	//int chk = 0;
	struct node* head = NULL;
	struct node* cu = NULL;
/*	while(ch != 0)
	{
		printf("\n ENTER THE ELEMENT TO BE PUSH IN STACK: ");
		scanf("%d",&elm);
		chk = push(&top,elm);
		if(chk == 0)
		{
			printf("\n PUSH OPERATIPON FAILED");
			exit(0);
		}
		printf("\n ENTER ) to EXIT");
		scanf("%d",&ch);
	} */
	printf("\n CAlling ll creation");
	create_node(&head);
	
	cu = head;
	while(cu != NULL)
	{
		printf("\n DATA: %d\tADD: %p\tADD_PR: %p\tADD_NE: %p\n",cu->data,cu,cu->prev,cu->next);
		cu = cu->next;
	}
	
	printf("\n Call DEL");
	printf("enter del data: ");
	scanf("%d",&po_el);
	del_node(&head,po_el);

	cu = head;
        while(cu != NULL)
        {
                printf("\n DATA: %d\tADD: %p\tADD_PR: %p\tADD_NE: %p\n",cu->data,cu,cu->prev,cu->next);
                cu = cu->next;
        }

	printf("ecit main");
}





















