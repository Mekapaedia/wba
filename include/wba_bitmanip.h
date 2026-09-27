#ifndef __WBA_BITMANIP_H__
#define __WBA_BITMANIP_H__

#define bitsof(x) (sizeof(x) << 3)

#define WBA_TO_SIZE(x) (1 << (x))
#define WBA_GET_MASK(x) ((1 << (x)) - 1)
#define WBA_GET_MASK_OFFSET(mask, offset) ((mask) << (offset))
#define WBA_GET_VALUE(src, mask, offset) (((src) >> (offset)) & (mask))
#define WBA_GET_MASKED_OUT_VALUE(src, mask, offset) (((src) & ~WBA_GET_MASK_OFFSET(mask, offset)))
#define WBA_GET_MASKED_OFFSET_VALUE(val, mask, offset) (((val) & (mask)) << (offset))
#define WBA_SET_MASKED_OFFSET_VALUE(src, mask, offset, val) (WBA_GET_MASKED_OUT_VALUE(src, mask, offset) | WBA_GET_MASKED_OFFSET_VALUE(val, mask, offset))
#define WBA_ASSIGN_MASKED_OFFSET_VALUE(src, mask, offset, val) (src = WBA_SET_MASKED_OFFSET_VALUE(src, mask, offset, val))
#define WBA_NEEDS_N(size, type) ((size + bitsof(type) - 1) / bitsof(type))

#endif /* __WBA_BITMANIP_H__ */
