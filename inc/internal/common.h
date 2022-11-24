#ifndef DTC_INTERNAL_COMMON_H
#define DTC_INTERNAL_COMMON_H
/* This file is included by the build system into EVERY file */

#ifdef DTC_SAFE_ALL
#define DTC_SAFE_ALLOC
#define DTC_SAFE_CONTAINER
#define DTC_SAFE_IO
#define DTC_SAFE_PARAM
#endif

#endif