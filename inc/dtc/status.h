#ifndef DTC_STS_H
#define DTC_STS_H

typedef int status;

/** Common return failure status */
#define DTC_STATUS_PTR_NULL    (-1)
#define DTC_STATUS_ALLOC       (-2)
#define DTC_STATUS_OVERLAP     (-3)
#define DTC_STATUS_IDX_INVALID (-4)
#define DTC_STATUS_VAL_INVALID (-5)
#define DTC_STATUS_IO          (-6)
#define DTC_STATUS_EMPTY       (-7)
#define DTC_STATUS_NIMPL       (-8)

/** Common return success status */
#define DTC_STATUS_SUCCESS     (0)

#define STATUS_ERROR(s) (s < 0)

#endif