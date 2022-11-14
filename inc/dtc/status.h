#ifndef DTC_STS_H
#define DTC_STS_H

typedef int status;

/** Common return status */
#define DTC_STATUS_SUCCESS     (0)
#define DTC_STATUS_PTR_NULL    (1)
#define DTC_STATUS_ALLOC       (2)
#define DTC_STATUS_OVERLAP     (3)
#define DTC_STATUS_IDX_INVALID (4)
#define DTC_STATUS_VAL_INVALID (5)

#endif