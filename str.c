#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rev_str_words(void)
{
    char *st = "Abhi roop dab ral.";
    char *tmp = st;
    int len = strlen(st) - 1;
    int start = 0, end = len;

    while ( 1 ) {
	if ( tmp[len] == ' ' ) {
	    start = len + 1;
	    while ( start <= end ) {
		printf("%c", tmp[start]);
		++start;
	    }
	    printf(" ");
	    end = len - 1;
	}
	else if ( !len ) {
	    start = 0;
	    while ( start <= end ) {
		printf("%c", tmp[start]);
		++start;
	    }
	    break;
	}
	--len;
    }
    printf("\n");
}

void swap(char *a, char *b)
{
    char tmp = *b;
    *b = *a;
    *a = tmp;
}

void st_perm(char *st, int i, int n)
{
    int j;
    if ( i == n )
	printf("%s\n ", st);
    else {
	for ( j = i; j < n; j++ ) {
	    swap(st+i, st+j);
	    printf("%s:%d:%d :", st, i, j);
	    st_perm(st, i+1, n);
	    swap(st+i, st+j);
	    printf("%s!%d!%d !", st, i , j);
	}
    }
}

	
int main()
{
    char st[] = "ABC";

    st_perm(st, 0, 3);

    return 0;
}


    


