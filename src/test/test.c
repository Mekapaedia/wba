#include <stdio.h>
#include <string.h>

#include "wba_pool.h"

int main(void)
{
    WBA_POOL_TYPE pool[1024];
    char* a;
    char* b;

    wba_pool_init(pool, sizeof(pool), 8, 8);
    a = wba_pool_malloc(pool, 15);
    b = wba_pool_malloc(pool, 5);

    strcpy(a, "cheese");
    strcpy(b, "ab");

    printf("%s, %s\n", a, b);

    return 0;
}
