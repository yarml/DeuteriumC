#include <dtc/dtc.h>
#include <stddef.h>

status dtc_base_init(dtc_base_init_param *params, dtc_base *out_base)
{
#ifdef DTC_SAFE_PARAM
    if(!out_base)
        return DTC_STATUS_PTR_NULL;
#endif
    out_base->name = params->name;
    out_base->f_init = params->f_init;
    out_base->f_copy = params->f_copy;
    out_base->f_fini = params->f_copy;
    out_base->magic = DTC_BASE_MAGIC;
    dtc_base_checksum(out_base, &out_base->checksum);
}

status dtc_base_checksum(dtc_base *base, int *out_checksum)
{
#ifdef DTC_SAFE_PARAM
    if(!base || !out_checksum)
        return DTC_STATUS_PTR_NULL;
#endif
    int size_ints = (sizeof(dtc_base) - offsetof(dtc_base, checksum)) / sizeof(int);
    int *ibase = base;
    int sum = 0;
    for(int i = 0; i < size_ints; ++i)
        sum += ibase[i];
    *out_checksum = -sum;
}

status dtc_obj_is_dtc(void *obj)
{
#ifdef DTC_SAFE_PARAM
    if(!obj)
        return DTC_STATUS_PTR_NULL;
#endif
    dtc_base *dobj = obj;
    if(dobj->magic != DTC_BASE_MAGIC)
        return DTC_STATUS_BASE_NOT_DTC;
    int checksum;
    dtc_base_checksum(dobj, &checksum);
    if(checksum != dobj->checksum)
        return DTC_STATUS_BASE_NOT_DTC;
    return DTC_STATUS_SUCCESS;
}
