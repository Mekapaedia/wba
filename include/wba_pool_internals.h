#ifndef __WBA_POOL_INTERNALS_H__
#define __WBA_POOL_INTERNALS_H__

#include "wba_bitmanip.h"
#include "wba_pool_config.h"
#include "wba_pool_type.h"

#define WBA_INIT_POOL(pool, size, max, sections) (WBA_ASSIGN_MASKED_OFFSET_VALUE(WBA_GET_POOL_CONFIG(pool), WBA_POOL_CONFIG_MASK, WBA_POOL_CONFIG_OFFSET, WBA_GET_POOL_SIZE_MASKED_OFFSET_VALUE(size) | WBA_GET_MAX_SIZE_MASKED_OFFSET_VALUE(max) | WBA_GET_NUM_SECTIONS_MASKED_OFFSET_VALUE(sections)))

#define WBA_GET_POOL_USABLE_SIZE(pool) (WBA_GET_POOL_SIZE(pool) - WBA_POOL_CONFIG_BYTES)
#define WBA_GET_STEP_SIZE(pool) (WBA_GET_MAX_SIZE(pool) / WBA_GET_NUM_SECTIONS(pool))
#define WBA_GET_MIN_SIZE(pool) (WBA_GET_MAX_SIZE(pool) - (WBA_GET_STEP_SIZE(pool) * (WBA_GET_NUM_SECTIONS(pool) - 1)))
#define WBA_GET_MIN_BYTES(pool) (WBA_TO_SIZE(WBA_GET_MIN_SIZE(pool)))
#define WBA_GET_MAX_BYTES(pool) (WBA_TO_SIZE(WBA_GET_MAX_SIZE(pool)))
#define WBA_GET_SECTION_SIZE(pool) (WBA_GET_POOL_USABLE_SIZE(pool) / WBA_GET_NUM_SECTIONS(pool))
#define WBA_GET_BLOCK_SIZE(pool, section) (WBA_TO_SIZE((WBA_GET_MAX_SIZE(pool) - (section * WBA_GET_STEP_SIZE(pool)))))
#define WBA_GET_NUM_BLOCKS(pool, section) ((WBA_GET_SECTION_SIZE(pool) * bitsof(WBA_POOL_TYPE)) / ((WBA_GET_BLOCK_SIZE(pool, section) * bitsof(WBA_POOL_TYPE)) + 1))

#define WBA_GET_TRACKER_SIZE(pool, section) (WBA_NEEDS_N(WBA_GET_NUM_BLOCKS(pool, section), WBA_POOL_TYPE))
#define WBA_GET_SECTION_OFFSET(pool, section) ((WBA_GET_SECTION_SIZE(pool) * section) + WBA_POOL_CONFIG_BYTES)
#define WBA_GET_BLOCKS_OFFSET(pool, section) ((WBA_GET_SECTION_OFFSET(pool, section)) + WBA_GET_TRACKER_SIZE(pool, section))
#define WBA_GET_BLOCK_OFFSET(pool, section, block) (WBA_GET_BLOCKS_OFFSET(pool, section) + (WBA_GET_BLOCK_SIZE(pool, section) * block))
#define WBA_GET_BLOCK_ADDR(pool, section, block) (pool + WBA_GET_BLOCK_OFFSET(pool, section, block))

#define WBA_GET_TRACKER_BYTE_OFFSET(block) (block / bitsof(WBA_POOL_TYPE))
#define WBA_GET_TRACKER_BIT_OFFSET(block) (block % bitsof(WBA_POOL_TYPE))
#define WBA_GET_TRACKER_BYTE(pool, section, block) (*(pool + WBA_GET_SECTION_OFFSET(pool, section) + WBA_GET_TRACKER_BYTE_OFFSET(block)))
#define WBA_GET_USED(pool, section, block) ((WBA_GET_TRACKER_BYTE(pool, section, block) >> WBA_GET_TRACKER_BIT_OFFSET(block)) & 1)
#define WBA_SET_USED(pool, section, block) (WBA_GET_TRACKER_BYTE(pool, section, block) |= (1 << WBA_GET_TRACKER_BIT_OFFSET(block)))
#define WBA_SET_FREE(pool, section, block) (WBA_GET_TRACKER_BYTE(pool, section, block) &= ~(1 << WBA_GET_TRACKER_BIT_OFFSET(block)))

#define WBA_GET_POOL_OFFSET(pool, addr) ((WBA_POOL_TYPE*)addr - pool)
#define WBA_GET_SECTION_FROM_ADDR(pool, addr) (WBA_GET_POOL_OFFSET(pool, addr) / WBA_GET_SECTION_SIZE(pool))
#define WBA_GET_BLOCK_FROM_ADDR(pool, addr) ((WBA_GET_POOL_OFFSET(pool, addr) - WBA_GET_BLOCKS_OFFSET(pool, WBA_GET_SECTION_FROM_ADDR(pool, addr))) / WBA_GET_BLOCK_SIZE(pool, WBA_GET_SECTION_FROM_ADDR(pool, addr)))
#define WBA_GET_POOL_END(pool) (pool + WBA_GET_POOL_SIZE(pool))

#endif /* __WBA_POOL_INTERNALS_H__ */
