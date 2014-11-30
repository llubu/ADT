/* G4G problems */
#include <stdio.h>
#include <stdlib.h>
#include "ds.h"

/* Copy a LL with next and random pt 
   Ret 0 Success -1 Error
 */

int copy_ll_randomPT(Rlist *head)
{
    Rlist *tmp = NULL;
    Rlist *cur = NULL;
    Rlist *clone = NULL;

    if ( !head )
	return -1;

    cur = head;

    while ( cur ) {
	clone = malloc(sizeof(Rlist));
	if ( !clone )
	    return -1;
	clone->data = cur->data;
	clone->next = cur->next; /* Inserting clone node */
	cur->next = clone;

	cur= cur->next->next; /* Moving ahead to next original node */
    }

    clone = cur->next; /* Now clone holds head of cloned list */ 
    cur = head;

    while ( cur ) {
	cur->next->random = cur->random->next;
	cur = cur->next->next;
    }

    cur = head;
    tmp = cur->next;

    while ( cur ) {
	cur->next = cur->next->next;
	tmp->next = tmp->next->next;
	cur = cur->next;
	tmp = tmp->next;
    }
    return 0;
}
