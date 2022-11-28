#ifndef DTC_NODE_H
#define DTC_NODE_H

#include <stddef.h>

#include <dtc/status.h>
#include <dtc/dtc.h>

#ifndef DTC
    typedef void dtc_node;
#else
    #include <internal/node.h>
#endif

struct DTC_NODE_INIT_PARAM;
typedef struct DTC_NODE_INIT_PARAM dtc_node_init_param;
struct DTC_NODE_INIT_PARAM
{
    dtc_node *n_prev;
    dtc_node *n_next;
    void *n_obj;
};

status dtc_node_init(dtc_node_init_param *n_init, dtc_node **out_node);

/* Stored element pointed to by data was not copied
 * Calling function should copy it manually
 * ELNCPY stands for ELement Not CoPied(Y)
 */
#define DTC_STATUS_NODE_COPY_ELNCPY (1024)
status dtc_node_copy(dtc_node *src, dtc_node **out_node);
status dtc_node_fini(dtc_node *node);

status dtc_node_next(dtc_node *node, dtc_node **out_node_next);
status dtc_node_prev(dtc_node *node, dtc_node **out_node_prev);
status dtc_node_data(dtc_node *node, void **out_data);

#endif