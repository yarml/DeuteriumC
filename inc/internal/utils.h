#ifndef DTC_INTERNAL_UTILS_H
#define DTC_INTERNAL_UTILS_H

#include <dtc/status.h>

#define DTC_SET_OUT(out, val) if(out) *out = val

#ifdef DTC_SAFE_CALL
#define DTC_CALL(status_var, call) status_var = call; if(status_var)
#else
#define DTC_CALL(status_var, call) status_var = call; if(0)
#endif

#endif