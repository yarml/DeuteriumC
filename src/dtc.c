#include <dtc/dtc.h>
#include <stddef.h>

status dtc_base_init(dtc_base_init_param *params, dtc_base *out_base)
{
    DTC_ASSERT_PARAM_PTR_VALID(params);
    DTC_ASSERT_PARAM_PTR_VALID(out_base);

    out_base->name = params->name;
    out_base->f_init = params->f_init;
    out_base->f_copy = params->f_copy;
    out_base->f_fini = params->f_fini;
    out_base->magic = DTC_BASE_MAGIC;
    dtc_base_checksum(out_base, &out_base->checksum);

    return DTC_STATUS_SUCCESS;
}

status dtc_base_checksum(dtc_base *base, int *out_checksum)
{
    DTC_ASSERT_PARAM_PTR_VALID(base);
    DTC_ASSERT_PARAM_PTR_VALID(out_checksum);

    int size_ints =
        (sizeof(dtc_base) - offsetof(dtc_base, checksum)) / sizeof(int);
    int *ibase = (int *) base;
    int sum = 0;
    for(int i = 0; i < size_ints; ++i)
        sum += ibase[i];
    *out_checksum = -sum;

    return DTC_STATUS_SUCCESS;
}

status dtc_obj_is_dtc(void *obj)
{
    DTC_ASSERT_PARAM_PTR_VALID(obj);

    dtc_base *dobj = obj;
    if(dobj->magic != DTC_BASE_MAGIC)
        return DTC_STATUS_BASE_NOT_DTC;
    int checksum;
    dtc_base_checksum(dobj, &checksum);
    if(checksum != dobj->checksum)
        return DTC_STATUS_BASE_NOT_DTC;
    return DTC_STATUS_SUCCESS;
}
