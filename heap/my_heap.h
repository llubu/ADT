#ifndef _MY_HEAP_H
#define _MY_HEAP_H

//Heap for Integer Data Type - TOP HEAVY

typedef struct myheap
{
    int size;	//size of Heap
    int (*compare)(int *data1, int *data2);
    void (*destroy)(int *data);
    int **array;
}HEAP;

void heap_init(HEAP *heap, int (*compare) (int *data1, int *data2), void (*destroy)(int *data));
void destroy(int *data);
int compare(int *data1, int *data2);
int my_insert(HEAP *heap, int *data);
int my_extract(HEAP *heap, int **data);

#define heap_size(heap) ((heap)->size)


#endif
