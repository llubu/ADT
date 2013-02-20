# include <stdio.h>
# include <stdlib.h>

# define SIZE 6

void merge(int * arr, int start,int mid, int end);

void merge_sort(int *arr, int start, int end)
{
	int mid = 0, st = 0, en = 0;
	//int *arr_A = NULL, *arr_B = NULL;

	if ((end - start) == 0)		// Base case when array has only 1 element
	{
		return;
	}
	mid = (start + end) / 2;

	merge_sort(arr, start, mid);
	merge_sort(arr, mid+1, end);
	merge(arr, start, mid, end);
}


void merge(int *arr, int start, int mid, int end)
{
	int i = 0, j = 0, k = 0, tmp1 = 0, siz;
	int *pt = NULL;
	j = start, k = mid+1;

	siz = (end - start) + 1;

	if ((pt = malloc(siz * sizeof(int))) == NULL)
	{
		printf("\n ERROR Aloocating mem \n");
		return;
	}

	while (j <= mid && k <= end)
	{
		if (arr[j] <= arr[k])
		{
			pt[tmp1] = arr[j];
			++j;
			++tmp1;
		}
		else
		{
			pt[tmp1] = arr[k];
			++k;
			++tmp1;
		}
		
	}	
	while (j <= mid)
	{
		pt[tmp1] = arr[j];
		++tmp1;
		++j;
	}
	while (k <= end)
	{
		pt[tmp1] = arr[k];
		++k;
		++tmp1;
	}
	
	for (i = 0; i < siz; i++)
	{
		--tmp1;
		arr[end] = pt[tmp1];
		--end;
	}	

	free(pt);	
}	
	


int main()
{
	int in_arr[SIZE];
	int i = 0;

	printf("\n Enter array elements \n");
	for(i = 0; i < SIZE; i++)
	{
		scanf("%d",&in_arr[i]);
	}

	merge_sort(in_arr, 0, SIZE-1);
	
	for(i = 0; i < SIZE; i++)
	{
		printf("\n %d \n", in_arr[i]);
	}
	return 0;
}
