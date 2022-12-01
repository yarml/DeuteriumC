#ifndef DTC_ISTREAM_H
#define DTC_ISTREAM_H

#include <dtc/str.h>
#include <dtc/status.h>
#include <dtc/dtc.h>

struct DTC_ISTREAM_HEAD;
typedef struct DTC_ISTREAM_HEAD dtc_istream_head;
struct DTC_ISTREAM_HEAD
{
    size_t head_pos; /* If equal to -1, then this head is free */
    size_t line;
    size_t colm;
};

#define DTC_STATUS_ISTREAM_FMODE_SKIP (1024)

#ifndef DTC
    typedef void dtc_istream;
#else
    #include <internal/istream.h>
#endif

typedef void dtc_istream_state;

typedef status(*dtc_istream_f_mode)(
    dtc_istream *istream,
    dtc_istream_state *state,
    int c,
    int *out_c
);

status dtc_istream_init(FILE *istream, dtc_istream **out_stream);
status dtc_istream_copy(dtc_istream *src, dtc_istream **out_stream);
status dtc_istream_fini(dtc_istream *stream);

status dtc_istream_head_slot_init(
    dtc_istream *istream,
    dtc_istream_head **out_head
);
status dtc_istream_head_slot_fini(
    dtc_istream_head *head
);
status dtc_istream_head_slot_save(
    dtc_istream *istream,
    dtc_istream_head *head
);
status dtc_istream_head_slot_load(
    dtc_istream *istream,
    dtc_istream_head *head
);

#define DTC_STATUS_ISTREAM_READC_EOF (1024)
status dtc_istream_readc(dtc_istream *istream, int *nout_c);

status dtc_istream_ghead(dtc_istream *stream, dtc_istream_head *out_head);
status dtc_istream_file(dtc_istream *stream, FILE **out_fistream);
status dtc_istream_data(dtc_istream *istream, dtc_str **out_data);

status dtc_istream_mode_push(dtc_istream *istream, dtc_istream_f_mode f_mode);
status dtc_istream_mode_pop(dtc_istream *istream);

status dtc_istream_sstate(dtc_istream *istream, dtc_istream_state *state);

/* Reads more data to the buffer */
status dtc_istream_read_more(dtc_istream *stream);



#endif