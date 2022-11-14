#ifndef DTC_STR_H
#define DTC_STR_H

#include <stddef.h>

#include <dtc/status.h>

#ifndef DTC
    typedef void dtc_str;
#else
    #include <internal/str.h>
#endif

status dtc_str_init(dtc_str **out_str);
status dtc_str_fini(dtc_str *str);

status dtc_str_buf(dtc_str *str, char **out_buf);
status dtc_str_len(dtc_str *str, size_t *out_len);

/* Append the null terminated string s to the DTC string str */
status dtc_str_appends(dtc_str *str, char const *s);
/* Append the character c to the DTC string str */
status dtc_str_appendc(dtc_str *str, char c);

status dtc_str_sets(dtc_str *str, char const *s);
status dtc_str_setc(dtc_str *str, char c, size_t idx);

status dtc_str_getc(dtc_str *str, size_t idx, char *out_c);

status dtc_str_trunc(dtc_str *str, size_t new_size);

#endif