#include "wba_pool.h"
#include "wba_pool_internals.h"

void wba_pool_init(WBA_POOL_TYPE* pool, WBA_SIZE_TYPE size, unsigned int max_size, unsigned int sections)
{
    unsigned int section = 0;
    unsigned int tracker_byte = 0;

    WBA_INIT_POOL(pool, size, max_size, sections);
    for (section = 0; section < WBA_GET_NUM_SECTIONS(pool); section++)
    {
        for (tracker_byte = 0; tracker_byte < WBA_GET_TRACKER_SIZE(pool, section); tracker_byte++)
        {
            WBA_GET_TRACKER_BYTE(pool, section, tracker_byte) = 0;
        }
    }
}

void* wba_pool_malloc(WBA_POOL_TYPE* pool, WBA_SIZE_TYPE size)
{
    int section = 0;
    unsigned int block = 0;

    if (!pool || !size)
        return WBA_NULL;
    else if (size > WBA_GET_MAX_BYTES(pool))
        return WBA_NULL;

    for (section = WBA_GET_NUM_SECTIONS(pool) - 1; section >= 0; section--)
    {
        if (WBA_GET_BLOCK_SIZE(pool, section) < size)
            continue;

        for (block = 0; block < WBA_GET_NUM_BLOCKS(pool, section); block++)
        {
            if (!WBA_GET_USED(pool, section, block))
            {
                WBA_SET_USED(pool, section, block);
                return WBA_GET_BLOCK_ADDR(pool, section, block);
            }
        }
    }
    return WBA_NULL;
}

void wba_pool_free(WBA_POOL_TYPE* pool, void* addr)
{
    if (!pool || !addr || (addr > ((void*) WBA_GET_POOL_END(pool))))
        return;
    WBA_SET_FREE(pool, WBA_GET_SECTION_FROM_ADDR(pool, addr), WBA_GET_BLOCK_FROM_ADDR(pool, addr));
}

