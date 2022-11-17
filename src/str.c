#include <stdlib.h>
#include <string.h>

#include <internal/utils.h>
#include <internal/str.h>
#include <conf/str.h>
#include <dtc/str.h>


status dtc_str_init(char *n_init, dtc_str **out_str)
{
#ifdef DTC_SAFE_PARAM
    if(!out_str)
        return DTC_STATUS_PTR_NULL;
#endif
    dtc_str *str = calloc(1, sizeof(dtc_str));

#ifdef DTC_SAFE_ALLOC
    if(!str)
        return DTC_STATUS_ALLOC;
#endif
    if(!n_init)
    {
        str->len = 0;
        str->alloc = DTC_STR_INIT_ALLOC;
    }
    else
    {
        size_t init_len = strlen(n_init);
        str->len = init_len;
        str->alloc = init_len + 1 + DTC_STR_INIT_ALLOC;
    }
    str->buf = calloc(str->alloc, 1);
#ifdef DTC_SAFE_ALLOC
    if(!str->buf)
    {
        free(str);
        return DTC_STATUS_ALLOC;
    }
#endif
    if(n_init)
        strcpy(str->buf, n_init);

    *out_str = str;
    return DTC_STATUS_SUCCESS;
}
status dtc_str_fini(dtc_str *str)
{
#ifdef DTC_SAFE_PARAM
    if(!str)
        return DTC_STATUS_PTR_NULL;
#endif
    free(str->buf);
    free(str);
    return DTC_STATUS_SUCCESS;
}

status dtc_str_buf(dtc_str *str, char **out_buf)
{
#ifdef DTC_SAFE_PARAM
    if(!str || !out_buf)
        return DTC_STATUS_PTR_NULL;
#endif
    *out_buf = str->buf;
    return DTC_STATUS_SUCCESS;
}
status dtc_str_len(dtc_str *str, size_t *out_len)
{
#ifdef DTC_SAFE_PARAM
    if(!str || !out_len)
        return DTC_STATUS_PTR_NULL;
#endif
    *out_len = str->len;
    return DTC_STATUS_SUCCESS;
}

status dtc_str_appends(dtc_str *str, char const *s)
{
#ifdef DTC_SAFE_PARAM
    if(!str || !s)
        return DTC_STATUS_PTR_NULL;
    /* Check that the string to append isn't a part of str */
    if(str->buf <= s && s < str->buf + str->len)
        return DTC_STATUS_OVERLAP;
#endif
    status status_sub;

    size_t nstrlen;

    nstrlen = strlen(s);

    DTC_CALL(status_sub, dtc_str_trunc(str, str->len + nstrlen))
        return status_sub;

    memcpy(str->buf + str->len - nstrlen, s, nstrlen);
    return DTC_STATUS_SUCCESS;
}
status dtc_str_appendc(dtc_str *str, char c)
{
#ifdef DTC_SAFE_PARAM
    if(!str)
        return DTC_STATUS_PTR_NULL;
#endif
    status status_sub;

    DTC_CALL(status_sub, dtc_str_trunc(str, str->len + 1))
        return status_sub;
    
    str->buf[str->len - 1] = c;
    return DTC_STATUS_SUCCESS;
}

status dtc_str_sets(dtc_str *str, char const *s)
{
#ifdef DTC_SAFE_PARAM
    if(!str || !s)
        return DTC_STATUS_PTR_NULL;
    /* Check that the string to append isn't a part of str */
    if(str->buf <= s && s < str->buf + str->len)
        return DTC_STATUS_OVERLAP;
#endif
    status status_sub;
    size_t nstrlen;

    nstrlen = strlen(s);

    DTC_CALL(status_sub, dtc_str_trunc(str, nstrlen))
        return status_sub;
    
    memcpy(str->buf, s, nstrlen);
    
    return DTC_STATUS_SUCCESS;
}
status dtc_str_setc(dtc_str *str, char c, size_t idx)
{
#ifdef DTC_SAFE_PARAM
    if(!str)
        return DTC_STATUS_PTR_NULL;
    if(idx >= str->len)
        return DTC_STATUS_IDX_INVALID;
#endif
    str->buf[idx] = c;
    return DTC_STATUS_SUCCESS;
}

status dtc_str_getc(dtc_str *str, size_t idx, char *out_c)
{
#ifdef DTC_SAFE_PARAM
    if(!str || !out_c)
        return DTC_STATUS_PTR_NULL;
    if(idx >= str->len)
        return DTC_STATUS_IDX_INVALID;
#endif
    *out_c = str->buf[idx];
    return DTC_STATUS_SUCCESS;
}

status dtc_str_rem(dtc_str *str, size_t idx, char *nout_c)
{
#ifdef DTC_SAFE_PARAM
    if(!str)
        return DTC_STATUS_PTR_NULL;
    if(idx >= str->len)
        return DTC_STATUS_IDX_INVALID;
#endif
    DTC_SET_OUT(nout_c, str->buf[idx]);
    // move the null termination too(hence the + 1 in the last argument)
    memmove(str->buf + idx, str->buf + idx + 1, str->len - idx + 1);
    --str->len;
    return DTC_STATUS_SUCCESS;
}
status dtc_str_pop(dtc_str *str, char *nout_c)
{
#ifdef DTC_SAFE_PARAM
    if(!str)
        return DTC_STATUS_PTR_NULL;
#endif

#ifdef DTC_SAFE_CONTAINER
    if(!str->len)
        return DTC_STATUS_EMPTY;
#endif
    DTC_SET_OUT(nout_c, str->buf[str->len - 1]);
    --str->len;
    str->buf[str->len] = 0;
    return DTC_STATUS_SUCCESS;
}

status dtc_str_trunc(dtc_str *str, size_t new_size)
{
#ifdef DTC_SAFE_PARAM
    if(!str)
        return DTC_STATUS_PTR_NULL;
#endif
    if(new_size < str->len)
    {
        str->len = new_size;
        str->buf[str->len] = 0;
        return DTC_STATUS_SUCCESS;
    }
    if(new_size >= str->alloc)
    {
        char *nbuf = realloc(str->buf, new_size + 1 + DTC_STR_INIT_ALLOC);
#ifdef DTC_SAFE_ALLOC
        if(!nbuf)
            return DTC_STATUS_ALLOC;
#endif
        str->buf = nbuf;
    }
    str->len = new_size;
    str->buf[str->len] = 0;
    return DTC_STATUS_SUCCESS;
}
