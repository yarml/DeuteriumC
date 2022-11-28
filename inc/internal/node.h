#ifndef DTC_INTERNAL_NODE_H
#define DTC_INTERNAL_NODE_H

#include <dtc/dtc.h>


struct DTC_NODE;
typedef struct DTC_NODE dtc_node;
struct DTC_NODE
{
    dtc_base base;
    dtc_node *next;
    dtc_node *prev;
    void *obj;
};

#endif