#include <stdlib.h>
#include <string.h>

#include <conf/list.h>
#include <dtc/list.h>



status dtc_list_init(void *n_api_unused_0, dtc_list **out_list)
{
    DTC_ASSERT_PARAM_PTR_VALID(out_list);

    dtc_list *list = calloc(1, sizeof(dtc_list));

    DTC_ASSERT_ALLOC_VALID(list);

    dtc_base_init_param base_params;

    base_params.name = "dtc_list";
    base_params.f_init = (dtc_type_f_init) dtc_list_init;
    base_params.f_copy = (dtc_type_f_copy) dtc_list_copy;
    base_params.f_fini = (dtc_type_f_fini) dtc_list_fini;

    dtc_base_init(&base_params, &list->base);

    list->len = 0;
    list->allocptr = DTC_LIST_INIT_ALLOC;
    list->ptrbuf = calloc(list->allocptr, sizeof(void *));
#ifdef DTC_SAFE_ALLOC
    if(!list->ptrbuf)
    {
        free(list);
        return DTC_STATUS_ALLOC;
    }
#endif

    *out_list = list;
    return DTC_STATUS_SUCCESS;
}

status dtc_list_copy(dtc_list *src, dtc_list **out_list)
{
    DTC_ASSERT_PARAM_PTR_VALID(src);
    DTC_ASSERT_PARAM_PTR_VALID(out_list);

    dtc_list *list = calloc(1, sizeof(dtc_list));
    DTC_ASSERT_ALLOC_VALID(list);

    dtc_base_init_param base_params;

    base_params.name = "dtc_list";
    base_params.f_init = (dtc_type_f_init) dtc_list_init;
    base_params.f_copy = (dtc_type_f_copy) dtc_list_copy;
    base_params.f_fini = (dtc_type_f_fini) dtc_list_fini;

    dtc_base_init(&base_params, &list->base);

    list->len = src->len;
    list->allocptr = list->len + DTC_LIST_INIT_ALLOC;
    list->ptrbuf = calloc(list->allocptr, sizeof(void *));
#ifdef DTC_SAFE_ALLOC
    if(!list->ptrbuf)
    {
        free(list);
        return DTC_STATUS_PTR_NULL;
    }
#endif

    // If stored objects are DTC compliant, copy them as well
    // Otherwise return a status signaling element objects
    // weren't copied
    if(!dtc_obj_is_dtc(*src->ptrbuf))
    {
        for(size_t i = 0; i < list->len; ++i)
        {
            dtc_base *cbase = src->ptrbuf[i];
            cbase->f_copy(cbase, src->ptrbuf + i);
        }
        return DTC_STATUS_SUCCESS;
    }
    return DTC_STATUS_LIST_COPY_ELNCPY;

}

status dtc_list_fini(dtc_list *list)
{
    DTC_ASSERT_PARAM_PTR_VALID(list);
    free(list->ptrbuf);
    free(list);
    return DTC_STATUS_SUCCESS;
}

status dtc_list_len(dtc_list *list, size_t *out_len)
{
    DTC_ASSERT_PARAM_PTR_VALID(list);
    DTC_ASSERT_PARAM_PTR_VALID(out_len);

    *out_len = list->len;
    return DTC_STATUS_SUCCESS;
}
status dtc_list_arr(dtc_list *list, void ***out_arr)
{
    DTC_ASSERT_PARAM_PTR_VALID(list);
    DTC_ASSERT_PARAM_PTR_VALID(out_arr);

    *out_arr = list->ptrbuf;
    return DTC_STATUS_SUCCESS;
}

status dtc_list_append(dtc_list *list, void ***nout_el)
{
    DTC_ASSERT_PARAM_PTR_VALID(list);
    status status_sub = 0;

    if(list->len >= list->allocptr)
    {
        DTC_CALL(
            status_sub,
            dtc_intenal_list_extend(list, 1 + DTC_LIST_INIT_ALLOC)
        )
            return status_sub;
    }
    DTC_SET_OUT(nout_el, list->ptrbuf + list->len);
    ++list->len;
    return DTC_STATUS_SUCCESS;
}
status dtc_list_insert(dtc_list *list, size_t idx, void ***nout_el)
{
    DTC_ASSERT_PARAM_PTR_VALID(list);
    /* Index can be exactly len */
    DTC_ASSERT_PARAM_IDX_VALID(idx, list->len + 1);

    status status_sub = 0;

    if(list->len >= list->allocptr)
    {
        DTC_CALL(
            status_sub,
            dtc_intenal_list_extend(list, 1 + DTC_LIST_INIT_ALLOC)
        )
            return status_sub;
    }

    memmove(
        list->ptrbuf + idx + 1,
        list->ptrbuf + idx,
        (list->len - idx) * sizeof(void *)
    );
    DTC_SET_OUT(nout_el, list->ptrbuf + idx);
    return DTC_STATUS_SUCCESS;
}
status dtc_list_rem(dtc_list *list, size_t idx, void **nout_ptrel)
{
    DTC_ASSERT_PARAM_PTR_VALID(list);
    DTC_ASSERT_PARAM_IDX_VALID(idx, list->len);

    DTC_SET_OUT(nout_ptrel, *(list->ptrbuf + idx));
    memmove(
        list->ptrbuf + idx,
        list->ptrbuf + idx + 1,
        (list->len - idx - 1) * sizeof(void *)
    );
    --list->len;
    return DTC_STATUS_SUCCESS;
}
status dtc_list_pop(dtc_list *list, void **nout_ptrel)
{
    DTC_ASSERT_PARAM_PTR_VALID(list);
    DTC_ASSERT_CONTAINER_NEMPTY(list->len);

    DTC_SET_OUT(nout_ptrel, (list->ptrbuf + list->len - 1));
    --list->len;
    return DTC_STATUS_SUCCESS;
}
status dtc_list_at(dtc_list *list, size_t idx, void ***out_el)
{
    DTC_ASSERT_PARAM_PTR_VALID(list);
    DTC_ASSERT_PARAM_PTR_VALID(out_el);
    DTC_ASSERT_PARAM_IDX_VALID(idx, list->len);

    *out_el = list->ptrbuf + idx;
    return DTC_STATUS_SUCCESS;
}

status dtc_intenal_list_extend(dtc_list *list, size_t add_allocptr)
{
    DTC_ASSERT_PARAM_PTR_VALID(list);
    DTC_ASSERT_PARAM_VAL(add_allocptr);

    void **nptrbuf = realloc(
        list->ptrbuf,
        (list->allocptr + add_allocptr) * sizeof(void *)
    );
    DTC_ASSERT_ALLOC_VALID(nptrbuf);
    list->ptrbuf = nptrbuf;
    memset(list->ptrbuf + list->allocptr, 0, add_allocptr * sizeof(void *));
    list->allocptr += add_allocptr;
    return DTC_STATUS_SUCCESS;
}
