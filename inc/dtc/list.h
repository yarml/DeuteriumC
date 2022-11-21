#ifndef DTC_LIST_H
#define DTC_LIST_H

#include <dtc/status.h>
#include <dtc/dtc.h>

#ifndef DTC
    typedef void dtc_list;
#else
    #include <internal/list.h>
#endif

status dtc_list_init(void *n_api_unused_0, dtc_list **out_list);

/* List elements weren't copied, calling function should copy them manually */
/* ELNCPY stands for ELement Not CoPied(Y) */
#define DTC_STATUS_LIST_COPY_ELNCPY (1024)

status dtc_list_copy(dtc_list *src, dtc_list **out_list);
status dtc_list_fini(dtc_list *list);

status dtc_list_len(dtc_list *list, size_t *out_len);
status dtc_list_arr(dtc_list *list, void ***out_arr);

/*
 * n_eldata: if not NULL, initializes new element from data found there(size of data is elsize specified in init)
 * nout_el: if not NULL, should point to a pointer and will be set to point to the newly allocated item's data directly
 */
status dtc_list_append(dtc_list *list, void ***nout_el);
status dtc_list_insert(dtc_list *list, size_t idx, void ***nout_dptrel);
status dtc_list_rem(dtc_list *list, size_t idx, void **nout_ptrel);
status dtc_list_pop(dtc_list *list, void **nout_ptrel);
status dtc_list_at(dtc_list *list, size_t idx, void ***out_el);

#endif