#include <stdlib.h>
#include <string.h>

#include <internal/str.h>
#include <conf/str.h>
#include <dtc/dtc.h>
#include <dtc/str.h>


status dtc_str_init(char *n_init, dtc_str **out_str)
{
    DTC_ASSERT_PARAM_PTR_VALID(out_str);

    dtc_str *str = calloc(1, sizeof(dtc_str));

    DTC_ASSERT_ALLOC_VALID(str);

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

    dtc_base_init_param base_params;

    base_params.name = "dtc_str";
    base_params.f_init = (dtc_type_f_init) dtc_str_init;
    base_params.f_copy = (dtc_type_f_copy) dtc_str_copy;
    base_params.f_fini = (dtc_type_f_fini) dtc_str_fini;

    dtc_base_init(&base_params, &str->base);

    *out_str = str;
    return DTC_STATUS_SUCCESS;
}

status dtc_str_copy(dtc_str *src, dtc_str **out_str)
{
    DTC_ASSERT_PARAM_PTR_VALID(src);
    DTC_ASSERT_PARAM_PTR_VALID(out_str);

    status status_sub = 0;

    DTC_CALL(status_sub, dtc_str_init(src->buf, out_str))
        return status_sub;

    return DTC_STATUS_SUCCESS;
}

status dtc_str_fini(dtc_str *str)
{
    DTC_ASSERT_PARAM_PTR_VALID(str);

    free(str->buf);
    free(str);
    return DTC_STATUS_SUCCESS;
}

status dtc_str_buf(dtc_str *str, char **out_buf)
{
    DTC_ASSERT_PARAM_PTR_VALID(str);
    DTC_ASSERT_PARAM_PTR_VALID(out_buf);

    *out_buf = str->buf;
    return DTC_STATUS_SUCCESS;
}
status dtc_str_len(dtc_str *str, size_t *out_len)
{
    DTC_ASSERT_PARAM_PTR_VALID(str);
    DTC_ASSERT_PARAM_PTR_VALID(out_len);

    *out_len = str->len;
    return DTC_STATUS_SUCCESS;
}

status dtc_str_appends(dtc_str *str, char const *s)
{
    DTC_ASSERT_PARAM_PTR_VALID(str);
    DTC_ASSERT_PARAM_PTR_VALID(s);
#ifdef DTC_SAFE_PARAM
    /* Check that the string to append isn't a part of str */
    if(str->buf <= s && s < str->buf + str->len)
        return DTC_STATUS_OVERLAP;
#endif
    status status_sub = 0;

    size_t nstrlen;

    nstrlen = strlen(s);

    DTC_CALL(status_sub, dtc_str_trunc(str, str->len + nstrlen))
        return status_sub;

    memcpy(str->buf + str->len - nstrlen, s, nstrlen);
    return DTC_STATUS_SUCCESS;
}
status dtc_str_appendc(dtc_str *str, char c)
{
    DTC_ASSERT_PARAM_PTR_VALID(str);

    status status_sub = 0;

    DTC_CALL(status_sub, dtc_str_trunc(str, str->len + 1))
        return status_sub;

    str->buf[str->len - 1] = c;
    return DTC_STATUS_SUCCESS;
}

status dtc_str_sets(dtc_str *str, char const *s)
{
    DTC_ASSERT_PARAM_PTR_VALID(str);
    DTC_ASSERT_PARAM_PTR_VALID(s);
#ifdef DTC_SAFE_PARAM
    /* Check that the string to append isn't a part of str */
    if(str->buf <= s && s < str->buf + str->len)
        return DTC_STATUS_OVERLAP;
#endif
    status status_sub = 0;
    size_t nstrlen;

    nstrlen = strlen(s);

    DTC_CALL(status_sub, dtc_str_trunc(str, nstrlen))
        return status_sub;

    memcpy(str->buf, s, nstrlen);

    return DTC_STATUS_SUCCESS;
}
status dtc_str_setc(dtc_str *str, char c, size_t idx)
{
    DTC_ASSERT_PARAM_PTR_VALID(str);
    DTC_ASSERT_PARAM_IDX_VALID(idx, str->len);

    str->buf[idx] = c;
    return DTC_STATUS_SUCCESS;
}

status dtc_str_getc(dtc_str *str, size_t idx, int *out_c)
{
    DTC_ASSERT_PARAM_PTR_VALID(str);
    DTC_ASSERT_PARAM_PTR_VALID(out_c);
    DTC_ASSERT_PARAM_IDX_VALID(idx, str->len);

    *out_c = str->buf[idx];

    return DTC_STATUS_SUCCESS;
}
status dtc_str_head(dtc_str *str, char *out_c)
{
    DTC_ASSERT_PARAM_PTR_VALID(str);
    DTC_ASSERT_PARAM_PTR_VALID(out_c);
    DTC_ASSERT_CONTAINER_NEMPTY(str->len);

    *out_c = str->buf[0];
    return DTC_STATUS_SUCCESS;
}
status dtc_str_tail(dtc_str *str, char *out_c)
{
    DTC_ASSERT_PARAM_PTR_VALID(str);
    DTC_ASSERT_PARAM_PTR_VALID(out_c);
    DTC_ASSERT_CONTAINER_NEMPTY(str->len);

    *out_c = str->buf[str->len - 1];
    return DTC_STATUS_SUCCESS;
}

status dtc_str_rem(dtc_str *str, size_t idx, char *nout_c)
{
    DTC_ASSERT_PARAM_PTR_VALID(str);
    DTC_ASSERT_PARAM_IDX_VALID(idx, str->len);

    DTC_SET_OUT(nout_c, str->buf[idx]);
    // move the null termination too(hence the + 1 in the last argument)
    memmove(str->buf + idx, str->buf + idx + 1, str->len - idx + 1);
    --str->len;
    return DTC_STATUS_SUCCESS;
}
status dtc_str_pop(dtc_str *str, char *nout_c)
{
    DTC_ASSERT_PARAM_PTR_VALID(str);
    DTC_ASSERT_CONTAINER_NEMPTY(str->len);

    DTC_SET_OUT(nout_c, str->buf[str->len - 1]);
    --str->len;
    str->buf[str->len] = 0;
    return DTC_STATUS_SUCCESS;
}

status dtc_str_trunc(dtc_str *str, size_t new_size)
{
    DTC_ASSERT_PARAM_PTR_VALID(str);

    if(new_size < str->len)
    {
        str->len = new_size;
        str->buf[str->len] = 0;
        return DTC_STATUS_SUCCESS;
    }
    if(new_size >= str->alloc)
    {
        char *nbuf = realloc(str->buf, new_size + 1 + DTC_STR_INIT_ALLOC);
        DTC_ASSERT_ALLOC_VALID(nbuf);
        str->buf = nbuf;
    }
    str->len = new_size;
    str->buf[str->len] = 0;
    return DTC_STATUS_SUCCESS;
}
