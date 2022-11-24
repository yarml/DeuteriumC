#ifndef DTC_INTERNAL_COMMON_H
#define DTC_INTERNAL_COMMON_H
/* This file is included by the build system into EVERY file */

#include <dtc/status.h>

#ifdef DTC_SAFE_ALL
#define DTC_SAFE_ALLOC
#define DTC_SAFE_CONTAINER
#define DTC_SAFE_IO
#define DTC_SAFE_PARAM
#endif

#define DTC_SET_OUT(out, val) if(out) *(out) = (val)

#define DTC_CALL(status_var, call) (status_var) = (call); if((status_var) < 0)

#ifdef DTC_SAFE_PARAM
    #define DTC_ASSERT_PARAM_PTR_VALID(param) if(!(param)) \
                return DTC_STATUS_PTR_NULL
    #define DTC_ASSERT_PARAM_IDX_VALID(idx, len) if((idx) >= (len)) \
                return DTC_STATUS_IDX_INVALID
    #define DTC_ASSERT_PARAM_VAL(cond) if(!(cond)) \
                return DTC_STATUS_VAL_INVALID
#else
    #define DTC_ASSERT_PARAM_PTR_VALID(param) if(0)
    #define DTC_ASSERT_PARAM_IDX_VALID(idx, len) if(0)
    #define DTC_ASSERT_PARAM_VAL(cond) if(0)
#endif

#ifdef DTC_SAFE_CONTAINER
    #define DTC_ASSERT_CONTAINER_NEMPTY(len) if(!(len)) return DTC_STATUS_EMPTY
#else
    #define DTC_ASSERT_CONTAINER_NEMPTY(len) if(0)
#endif

#ifdef DTC_SAFE_ALLOC
    #define DTC_ASSERT_ALLOC_VALID(ptr) if(!(ptr)) return DTC_STATUS_ALLOC
#else
    #define DTC_ASSERT_ALLOC_VALID(ptr) if(0)
#endif

#ifdef DTC_SAFE_IO
    #define DTC_ASSERT_IO_FNOERROR(fstream) if(ferror(fstream)) \
        return DTC_STATUS_IO
#else
    #define DTC_ASSERT_IO_FNOERROR(fstream) if(0)
#endif

#endif