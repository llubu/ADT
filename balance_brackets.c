#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    struct stack *next;
    void *ptr;
} Stack;

void push(Stack **head, void *data)
{
    Stack *tmp = NULL;
    
    tmp = malloc(sizeof(Stack));
    if ( !tmp )
	return;
    tmp->ptr = data;
    tmp->next = *head;
    *head = tmp;
}

void *pop(Stack **head)
{
    Stack *tmp = NULL;
    void *pt;
    
    if ( !(*head) )
	return NULL;

    tmp = *head;
    *head = (*head)->next;
    pt = (char *) tmp->ptr;
    return (void *) pt;
}


int chk_balBK(char *st)
{
    char *tmp = st;
    int oCount = 0, cCount = 0; /* Opening and closing count for brackets in the IP string */ 
    Stack *head = NULL;
    char ch;

    if ( !st )
	return 0;

    while ( *tmp != '\0' ) {
	if ( cCount > oCount )
	    return 0;
	if ( *tmp == '(' || *tmp == '{' || *tmp == '[' ) {
	    ++oCount;
	    printf("Push: %c :\n", *tmp);
	    push(&head, (void *)tmp);
	}
	else if ( *tmp == ')' || *tmp == '}' || *tmp == ']' ) {
	    ++cCount;
	    ch = *(char *) pop(&head);
	    printf("Pop: %c : == : %c : \n", ch, *tmp);
	    switch ( ch ) {
		case '(':
		    if ( *tmp != ')' )
			return 0;
		    break;
		case '{':
		    if ( *tmp != '}' )
			return 0;
		    break;
		case '[':
		    if ( *tmp != ']' )
			return 0;
		    break;
		default:
		    return 0;
	    }
	}
	++tmp;
    }
    if ( oCount != cCount )
	return 1;
}

int main()
{
    char *st = "(bsd{]})";
    if ( chk_balBK(st) )
	printf("Brackets are balanced:\n");
    else
	printf("Brackets are NOT balanced:\n");

    return 0;
}
