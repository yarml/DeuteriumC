#ifndef DTC_INTERNAL_LIST_H
#define DTC_INTERNAL_LIST_H

struct DTC_LIST;
typedef struct DTC_LIST dtc_list;
struct DTC_LIST
{
    void **ptrbuf;
    size_t allocptr;
    size_t len;
};

status dtc_intenal_list_extend(dtc_list *list, size_t add_allocptr);

#endif