#ifndef _OGG_OS_TYPES_H
#define _OGG_OS_TYPES_H

//#include "config.h"
#include <stdint.h>

#include "bsp.h"

#define _ogg_malloc  user_malloc
#define _ogg_calloc  user_calloc
#define _ogg_realloc user_realloc
#define _ogg_free    user_free

typedef int16_t ogg_int16_t;
typedef uint16_t ogg_uint16_t;
typedef int32_t ogg_int32_t;
typedef uint32_t ogg_uint32_t;
typedef int64_t ogg_int64_t;

#endif //_OGG_OS_TYPES_H
