#pragma once

#include <stdbool.h>

#include "fuzzybool.h"
#include "CONTEXT_utils.h"
#include "memorycache.h"
#include "lisp.h"

typedef struct _bp_address bp_address;
typedef struct _BP BP;
typedef struct _process process;
typedef struct _thread thread;

typedef enum _BPF_state
{
    BPF_state_default=0,
    BPF_state_at_return,
    BPF_state_tracing_inside_function,
    BPF_state_tracing_skipping
} BPF_state;

typedef enum _function_type
{
    TY_UNKNOWN=0,
    TY_VOID,
    TY_UNINTERESTING,
    TY_REG,
    TY_INT,
    TY_PTR,
    TY_TETRABYTE,
    TY_QSTRING
} function_type;

typedef struct _BPF
{
    bool unicode, skip, skip_stdcall, trace, cc;
    // these params may be NULL
    REG rt;
    double rt_probability;
    unsigned args, dump_args, pause;
    bp_address *when_called_from_address, *when_called_from_func;
    // variables filled by is_it_known_function
    TrueFalseUndefined known_function;
    unsigned args_n;
    function_type ret_type, this_type;
    function_type *arg_types;
    // variables filled if when_called_from_func
    bool when_called_from_func_next_func_adr_present;
    address when_called_from_func_next_func_adr;
} BPF;

void BPF_free(BPF*);
void dump_BPF(BPF *b);
void handle_BPF(process *p, thread *t, int DRx_no, CONTEXT *ctx, MemoryCache *mc);
