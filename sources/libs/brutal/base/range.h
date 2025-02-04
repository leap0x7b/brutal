#pragma once

#include <brutal/base/std.h>

#define Range(T) \
    struct       \
    {            \
        T base;  \
        T size;  \
    }

#define range$(T, RANGE) (            \
    {                                 \
        typeof(RANGE) _range = RANGE; \
                                      \
        (T){                          \
            _range.base,              \
            _range.size,              \
        };                            \
    })

#define range_empty(RANGE) \
    ((RANGE).size == 0)

#define range_any(RANGE) \
    ((RANGE).size > 0)

#define range_begin(RANGE) \
    ((RANGE).base)

#define range_end(RANGE) \
    ((RANGE).base + (RANGE).size)

#define range_contain(RANGE, ADDR) \
    (((RANGE).base <= (ADDR)) && ((RANGE).size + (RANGE).base >= (ADDR)))

#define range_contiguous(LHS, RHS) \
    ((range_begin(LHS) == range_end(RHS)) || (range_end(LHS) == range_begin(RHS)))

#define range_colide(LHS, RHS) (range_begin(LHS) < range_end(RHS) && range_end(LHS) > range_begin(RHS))

#define range_from_start_and_end(T, START, END) \
    (T) { (START), (END - START) }

#define range_merge(LHS, RHS) (                                 \
    {                                                           \
        auto __start = MIN(range_begin(LHS), range_begin(RHS)); \
        auto __end = MAX(range_end(LHS), range_end(RHS));       \
        range_from_start_and_end(typeof(LHS), __start, __end);  \
    })

#define range_half_under(SELF, SPLIT) (         \
    {                                           \
        typeof(SELF) __self = (SELF);           \
        typeof(SPLIT) __split = (SPLIT);        \
                                                \
        typeof(SELF) result = (typeof(SELF)){}; \
                                                \
        if (range_colide(__self, __split) &&    \
            __self.base < __split.base)         \
        {                                       \
            result = (typeof(SELF)){            \
                __self.base,                    \
                __split.base - __self.base,     \
            };                                  \
        }                                       \
                                                \
        result;                                 \
    })

#define range_half_over(SELF, SPLIT) (                  \
    {                                                   \
        typeof(SELF) __self = (SELF);                   \
        typeof(SPLIT) __split = (SPLIT);                \
                                                        \
        typeof(SELF) result = {};                       \
                                                        \
        if (range_colide(__self, __split) &&            \
            range_end(__self) > range_end(__split))     \
        {                                               \
            result = (typeof(SELF)){                    \
                range_end(__split),                     \
                range_end(__self) - range_end(__split), \
            };                                          \
        }                                               \
                                                        \
        result;                                         \
    })

#define range_eq(LHS, RHS) ((LHS).base == (RHS.base) && (LHS).size == (RHS).size)

typedef Range(uint8_t) U8Range;
typedef Range(uint16_t) U16Range;
typedef Range(uint32_t) U32Range;
typedef Range(uint64_t) U64Range;
typedef Range(size_t) USizeRange;
