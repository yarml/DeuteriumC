#include <stdlib.h>

#include <dtc/node.h>

status dtc_node_init(dtc_node_init_param *n_init, dtc_node **out_node)
{
    DTC_ASSERT_PARAM_PTR_VALID(out_node);

    dtc_node *node = calloc(1, sizeof(dtc_node));

    DTC_ASSERT_ALLOC_VALID(node);

    dtc_base_init_param base_params;

    base_params.name = "dtc_node";
    base_params.f_init = (dtc_type_f_init) dtc_node_init;
    base_params.f_copy = (dtc_type_f_copy) dtc_node_copy;
    base_params.f_fini = (dtc_type_f_fini) dtc_node_fini;

    dtc_base_init(&base_params, &node->base);

    if(n_init)
    {
        node->next = n_init->n_next;
        node->prev = n_init->n_prev;

        node->next->prev = node;
        node->prev->next = node;

        node->obj = n_init->n_obj;
    }
    else
    {
        node->next = 0;
        node->prev = 0;
        node->obj = 0;
    }

    *out_node = node;

    return DTC_STATUS_SUCCESS;
}
status dtc_node_copy(dtc_node *src, dtc_node **out_node)
{
    DTC_ASSERT_PARAM_PTR_VALID(src);
    DTC_ASSERT_PARAM_PTR_VALID(out_node);

    status status_sub = 0;

    status rs = DTC_STATUS_SUCCESS;
    void *ndata = 0;

    dtc_node_init_param cparam;

    cparam.n_next = src->next;
    cparam.n_prev = src->prev;
    cparam.n_obj = 0;

    DTC_CALL(status_sub, dtc_node_init(&cparam, out_node))
        return status_sub;

    if(dtc_obj_is_dtc(src->obj))
    {
        dtc_base *bobj = src->obj;
        DTC_CALL(status_sub, bobj->f_copy(bobj, &ndata))
            rs = DTC_STATUS_NODE_COPY_ELNCPY;
    }
    else
        rs = DTC_STATUS_NODE_COPY_ELNCPY;

    (*out_node)->obj = ndata;

    return rs;
}
status dtc_node_fini(dtc_node *node)
{
    DTC_ASSERT_PARAM_PTR_VALID(node);

    free(node);

    return DTC_STATUS_SUCCESS;
}

status dtc_node_next(dtc_node *node, dtc_node **out_node_next)
{
    DTC_ASSERT_PARAM_PTR_VALID(node);
    DTC_ASSERT_PARAM_PTR_VALID(out_node_next);

    *out_node_next = node->next;

    return DTC_STATUS_SUCCESS;
}
status dtc_node_prev(dtc_node *node, dtc_node **out_node_prev)
{
    DTC_ASSERT_PARAM_PTR_VALID(node);
    DTC_ASSERT_PARAM_PTR_VALID(out_node_prev);

    *out_node_prev = node->prev;

    return DTC_STATUS_SUCCESS;
}
status dtc_node_data(dtc_node *node, void **out_data)
{
    DTC_ASSERT_PARAM_PTR_VALID(node);
    DTC_ASSERT_PARAM_PTR_VALID(out_data);

    *out_data = node->obj;

    return DTC_STATUS_SUCCESS;
}

