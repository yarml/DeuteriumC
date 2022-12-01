#ifndef DTC_INTERNAL_ISTREAM_H
#define DTC_INTERNAL_ISTREAM_H

#include <stdio.h>

#include <dtc/istream.h>
#include <dtc/list.h>
#include <dtc/node.h>
#include <dtc/str.h>

struct DTC_ISTREAM;
typedef struct DTC_ISTREAM dtc_istream;
struct DTC_ISTREAM
{
    dtc_base base;
    FILE *fistream;
    dtc_list *saved_heads;
    dtc_str *data;
    dtc_node *top_mode;
    dtc_istream_state *state;
    dtc_istream_head head;
};

#endif