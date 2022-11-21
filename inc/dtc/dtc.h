#ifndef DTC_H
#define DTC_H

#include <dtc/status.h>

#define DTC_BASE_MAGIC0 (0xDC)
#define DTC_BASE_MAGIC (0xD7CBA5EF)

typedef status (*dtc_type_f_init)(void *params, void **out_obj);
typedef status (*dtc_type_f_copy)(void *src, void **out_dest);
typedef status (*dtc_type_f_fini)(void *obj);

struct DTC_BASE;
typedef struct DTC_BASE dtc_base;
struct DTC_BASE
{
    int magic;
    char const *name;
    dtc_type_f_init f_init;
    dtc_type_f_copy f_copy;
    dtc_type_f_fini f_fini;
    int checksum;
};

struct DTC_BASE_INIT_PARAM;
typedef struct DTC_BASE_INIT_PARAM dtc_base_init_param;
struct DTC_BASE_INIT_PARAM
{
    char const *name;
    dtc_type_f_init f_init;
    dtc_type_f_copy f_copy;
    dtc_type_f_fini f_fini;
};

status dtc_base_init(dtc_base_init_param *params, dtc_base *out_base);

status dtc_base_checksum(dtc_base *base, int *out_checksum);

#define DTC_STATUS_BASE_NOT_DTC (1025)

status dtc_obj_is_dtc(void *obj);

#endif