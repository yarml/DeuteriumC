#ifndef DTC_INTERNAL_STR_H
#define DTC_INTERNAL_STR_H

#include <dtc/dtc.h>

struct DTC_STR;
typedef struct DTC_STR dtc_str;
struct DTC_STR
{
    dtc_base base;
    char *buf;
    size_t alloc;
    size_t len;
};

#endif