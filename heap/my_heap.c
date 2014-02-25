#include "my_heap.h"
#include <stdio.h>
#include <stdlib.h>

#define heap_parent(position) ((int)(((position) - 1) / 2))
#define heap_lchild(position) (((position) * 2) + 1)
#define heap_rchild(position) (((position) * 2) + 2)

/*Initializes the Heap*/
void heap_init(HEAP *heap, int (*compare) (int *data1, int *data2), void (*destroy)(int *data))
{
    heap->size = 0;
    heap->compare = compare;
    heap->destroy = destroy;
    heap->array = NULL;
}

int compare(int *data1, int *data2)
{
    if ((*data1) == (*data2))
	return 0;
    if ((*data1) > (*data2))
	return 1;
    if ((*data1) < (*data2))
	return -1;
}

int my_insert(HEAP *heap, int *data)
{
    int *tmp = NULL;
    int **tmp1 = NULL;
    int cpos = 0;
    int ppos = 0;
    
    if ((tmp1 = (int **) realloc(heap->array, ((heap_size(heap) + 1) * sizeof(int *)))) == NULL)
    {
	printf("\n Error in allocating memory");
	return -1;
    }
    else
    {
	heap->array = tmp1;	// realloc call success
    }
    
    heap->array[heap_size(heap)] = (int *) data;  // adding the new node

    cpos = heap_size(heap);	// current node index
    ppos = heap_parent(cpos);	// Current node Parent node index

    while (cpos > 0  && ((heap->compare(heap->array[cpos], heap->array[ppos])) > 0))  //child is greater then parent
    { /* Heapify */
	tmp = heap->array[ppos];
	heap->array[ppos] = heap->array[cpos];
	heap->array[cpos] = tmp;

	cpos = ppos;
	ppos = heap_parent(cpos);
    }

    heap->size++;		// Incrementing Heap Size
    return 0;
}

// Extract the Maximum Value from Heap - TOP HEAVY

int my_extract(HEAP *heap, int **data)
{
    int *tmp = NULL;
    int **tmp1 = NULL;
    int *node = NULL;
    int cpos = 0;
    int npos = 0;
    int lpos = 0;
    int rpos = 0;

    if (!heap || !(heap_size(heap))) // Empty Heap Check
    {
	return -1;
    }

    (*data) = heap->array[0];	// First element of the array is the max element
    node = heap->array[heap_size(heap) - 1];

    if ((heap_size(heap) - 1) > 0)
    {
	if ((tmp1 = (int **) realloc(heap->array, ((heap_size(heap) - 1) * sizeof(int *)))) == NULL)
	{
	    printf("\n REALLOC ERROR - EXTRACT - ");
	    return -1;
	}
	else
	{
	    heap->array = tmp1;
	}
	heap->size--;	//Decrementing Heap Size
    }
    else // Only 1 node in Heap
    {
	free(heap->array);
	heap->array = NULL;
	heap->size = 0;
	return 0;
    }

    heap->array[0] = node;
    // Heapify 

    cpos = 0;
    lpos = heap_lchild(cpos);
    rpos = heap_rchild(cpos);

    while (1)
    {
	lpos = heap_lchild(cpos);
	rpos = heap_rchild(cpos);

	if (lpos < heap_size(heap) && ((compare(heap->array[lpos], heap->array[cpos])) > 0))
	{
	    npos = lpos;
	}
	else
	{
	    npos = cpos;
	}

	if (rpos < heap_size(heap) && ((compare(heap->array[rpos], heap->array[npos])) > 0))
	{
	    npos = rpos;
	}

	if (npos == cpos)
	{
	    break;
	}
	else
	{
	    tmp = heap->array[npos];
	    heap->array[npos] = heap->array[cpos];
	    heap->array[cpos] = tmp;

	    cpos = npos;
	}
    }
    return 0;
}

	    
void destroy(int *data)
{
    printf("\n IN DESTROY");
}
    


















