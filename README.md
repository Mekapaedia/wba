# WBA

Widdle block allocator.

Super stupid fixed size block allocator.

## Usage

```
#include "wba_pool.h"
#define MAX_BLOCK_SIZE 8 // size in bytes == 1 << BLOCK_SIZE
#define NUM_SECTIONS 8 // number of block sections - each section is linearly smaller than MAX_BLOCK_SIZE

WBA_POOL_TYPE pool[SIZE];
wba_pool_init(pool, SIZE, MAX_BLOCK_SIZE, NUM_SECTIONS);

char* a = wba_pool_malloc(pool, SOME_SIZE);

...

wba_pool_free(pool, a);

```

## Building

`make`

Creates "wba.a"
