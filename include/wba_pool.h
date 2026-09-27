#ifndef __WBA_POOL_H__
#define __WBA_POOL_H__

#include "wba_pool_type.h"

void wba_pool_init(WBA_POOL_TYPE* pool, WBA_SIZE_TYPE size, unsigned int max_size, unsigned int sections);
void* wba_pool_malloc(WBA_POOL_TYPE* pool, WBA_SIZE_TYPE size);
void wba_pool_free(WBA_POOL_TYPE* pool, void* addr);

#endif /* __WBA_POOL_H__ */
