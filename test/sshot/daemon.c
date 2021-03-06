/*
 * Copyright (c) 2004-2010 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2004-2011 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 * Copyright (c) 2004-2005 High Performance Computing Center Stuttgart,
 *                         University of Stuttgart.  All rights reserved.
 * Copyright (c) 2004-2005 The Regents of the University of California.
 *                         All rights reserved.
 * Copyright (c) 2006-2013 Los Alamos National Security, LLC.
 *                         All rights reserved.
 * Copyright (c) 2009-2012 Cisco Systems, Inc.  All rights reserved.
 * Copyright (c) 2011      Oak Ridge National Labs.  All rights reserved.
 * Copyright (c) 2013-2020 Intel, Inc.  All rights reserved.
 * Copyright (c) 2015-2019 Research Organization for Information Science
 *                         and Technology (RIST).  All rights reserved.
 * Copyright (c) 2016      IBM Corporation.  All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 *
 */

#include "src/include/pmix_config.h"
#include "include/pmix_server.h"
#include "src/include/types.h"
#include "src/include/pmix_globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

#if PMIX_HAVE_HWLOC
#include "src/hwloc/hwloc-internal.h"
#endif

#include "src/class/pmix_list.h"
#include "src/util/pmix_environ.h"
#include "src/util/output.h"
#include "src/util/printf.h"
#include "src/util/argv.h"

static pmix_server_module_t mymodule = {0};


int main(int argc, char **argv)
{
    pmix_info_t *info;
    size_t ninfo;
    pmix_status_t rc;

    fprintf(stderr, "PID: %lu Testing version %s\n", (unsigned long)getpid(), PMIx_Get_version());

    /* set a known network configuration for the pnet/test component */
    putenv("PMIX_MCA_pnet_sshot_scheduler_pipe=./myfifo");
    putenv("PMIX_MCA_pnet_sshot_config_file=./mytopo.json");
    putenv("PMIX_MCA_pnet=sshot");

    ninfo = 1;
    PMIX_INFO_CREATE(info, ninfo);
    PMIX_INFO_LOAD(&info[0], PMIX_SERVER_SCHEDULER, NULL, PMIX_BOOL);
    if (PMIX_SUCCESS != (rc = PMIx_server_init(&mymodule, info, ninfo))) {
        fprintf(stderr, "Init failed with error %d\n", rc);
        return rc;
    }
    PMIX_INFO_FREE(info, ninfo);


    /* finalize the server library */
    if (PMIX_SUCCESS != (rc = PMIx_server_finalize())) {
        fprintf(stderr, "Finalize failed with error %d\n", rc);
    }

    return rc;
}
