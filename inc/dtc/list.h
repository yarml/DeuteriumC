#ifndef DTC_LIST_H
#define DTC_LIST_H

#include <dtc/status.h>

#ifndef DTC
    typedef void dtc_list;
#else
    #include <internal/list.h>
#endif

status dtc_list_init(dtc_list **out_list);
status dtc_list_fini(dtc_list *list);

status dtc_list_len(dtc_list *list, size_t *out_len);
status dtc_list_arr(dtc_list *list, void ***out_arr);

/*
 * n_eldata: if not NULL, initializes new element from data found there(size of data is elsize specified in init)
 * nout_el: if not NULL, should point to a pointer and will be set to point to the newly allocated item's data directly
 */
status dtc_list_append(dtc_list *list, void ***nout_el);
status dtc_list_insert(dtc_list *list, size_t idx, void ***nout_el);
status dtc_list_remove(dtc_list *list, size_t idx);
status dtc_list_at(dtc_list *list, size_t idx, void ***out_el);

#endif