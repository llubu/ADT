#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
unsigned int hash(unsigned int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x);
    return x;
}
*/

uint32_t sax_hash ( uint32_t x, uint32_t c)
{
    uint32_t h = 0;
    int i;

    for ( i = 0; i < (x%c); i++ )
	h ^= ( h << 5 ) + ( h >> 2 ) + x;

    return h;
}

int main()
{
    unsigned int a, b, c, d, ks;
    uint32_t e;
    uint32_t mask = 0xFFFFFFFF;

    printf("Enter Key size:\n");
    scanf("%u", &c);
    ks = 1 << c;

    while (1) {
	printf("ENter key:\n");
	scanf("%u", &a);

//	b = hash(a); 
	d = sax_hash(a, c);
	e = d & (mask >> (32-c));

	if ( e > ks )
	    printf(" HASH IS > 2^20:%d: %d \n", e-ks, ks);
	printf("KEY:%u: ##:%u:::%u::\n", a, d, e);
    }

    return 0;
}





