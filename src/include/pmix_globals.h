/*
 * Copyright (c) 2004-2005 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2004-2005 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 * Copyright (c) 2004-2005 High Performance Computing Center Stuttgart, 
 *                         University of Stuttgart.  All rights reserved.
 * Copyright (c) 2004-2005 The Regents of the University of California.
 *                         All rights reserved.
 * Copyright (c) 2014      Intel, Inc. All rights reserved.
 * $COPYRIGHT$
 * 
 * Additional copyrights may follow
 * 
 * $HEADER$
 */

#ifndef PMIX_GLOBALS_H
#define PMIX_GLOBALS_H

#include "pmix_config.h"
#include "src/include/types.h"
#include <event.h>

#include "src/api/pmix_common.h"

BEGIN_C_DECLS

typedef enum {
    PMI1,
    PMI2,
    PMIX
} pmix_protocol_t;

#define PMIX_MAX_CRED_SIZE  131072   // set max at 128kbytes

/* define a global construct that includes values that must be shared
 * between various parts of the code library. Both the client
 * and server libraries must instance this structure */
typedef struct {
    char namespace[PMIX_MAX_NSLEN];
    int rank;
    char *credential;
    pmix_event_base_t *evbase;
    int debug_output;
    pmix_errhandler_fn_t errhandler;
    pmix_protocol_t protocol;
} pmix_globals_t;

extern pmix_globals_t pmix_globals;

END_C_DECLS

#endif /* PMIX_GLOBALS_H */
