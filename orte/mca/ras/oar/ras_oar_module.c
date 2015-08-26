/*
 * Copyright (c) 2008      The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 * Copyright (c) 2008      Institut National de Recherche en Informatique
 *                         et Automatique. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */
#include "orte_config.h"
#include "orte/constants.h"
#include "orte/types.h"

#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "orte/util/show_help.h"
#include "opal/util/os_path.h"

#include "orte/mca/errmgr/errmgr.h"
#include "orte/runtime/orte_globals.h"
#include "orte/util/name_fns.h"

#include "opal/util/argv.h"

#include "orte/mca/ras/base/ras_private.h"
#include "ras_oar.h"


/*
 * Local functions
 */
static int orte_ras_oar_allocate(orte_job_t *jdata, opal_list_t *nodes);
static int orte_ras_oar_finalize(void);
static char *ras_oar_getline(FILE *fp);

/*
 * Global variable
 */
orte_ras_base_module_t orte_ras_oar_module = {
    NULL,
    orte_ras_oar_allocate,
    NULL,
    orte_ras_oar_finalize
};


static int orte_ras_oar_allocate(orte_job_t *jdata, opal_list_t *nodes)
{
    orte_node_t *node;
    int i, num_nodes;
    FILE* nodefile;
    char* filename;
    int32_t nodeid=0;
    char *hostname;
    opal_list_item_t* item;

    /* get the list of allocated nodes */
    if( NULL == ( filename = getenv( "OAR_NODEFILE" ) ) ) {
        orte_show_help("help-ras-oar.txt", "nodelist-failed", true);
        return ORTE_ERR_NOT_AVAILABLE;
    }

    nodefile = fopen(filename, "r");
    if ( NULL == nodefile ) {
        ORTE_ERROR_LOG( ORTE_ERR_FILE_OPEN_FAILURE );
        free( filename );
        return ORTE_ERR_FILE_OPEN_FAILURE;
    }

    node = NULL;
    nodeid=0;

    while ( NULL != (hostname = ras_oar_getline( nodefile )) ) {

        /* the nodename is inserted by OAR as many times as we
         * have slots on the machine.
         */

        for ( item = opal_list_get_first( nodes );
              opal_list_get_end( nodes ) != item;
              item = opal_list_get_next( item ) ) {
            node = (orte_node_t*) item;
            if (0 == strcmp( node->name, hostname )) {
                ++node->slots;

                OPAL_OUTPUT_VERBOSE((1, orte_ras_base_framework.framework_output,
                                     "%s ras:oar:allocate:discover: found -- bumped slots to %d",
                                     ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), node->slots));

                break;
            }
        }

        /* Did we find it? */

        if ( opal_list_get_end( nodes ) == item ) {

            /* Nope -- didn't find it, so add a new item to the list */

            OPAL_OUTPUT_VERBOSE((1, orte_ras_base_framework.framework_output,
                                 "%s ras:oar:allocate:discover: not found -%s- added to list",
                                 ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), hostname));

            node = OBJ_NEW( orte_node_t );
            if (NULL == node) {
                free( hostname );
                return ORTE_ERR_OUT_OF_RESOURCE;
            }
            node->name = hostname;
            orte_set_attribute(&node->attributes, ORTE_NODE_LAUNCH_ID, ORTE_ATTR_LOCAL, &nodeid, OPAL_INT32);
            node->slots_inuse = 0;
            node->slots_max = 0;
            node->slots = 1;
            node->state = ORTE_NODE_STATE_UP;
           opal_list_append( nodes, &node->super );
        } else {
            /* Yes, so we need to free the hostname that came back */
            free( hostname );
        }

        /* up the nodeid */
        nodeid++;
    }

    return ORTE_SUCCESS;
}

static int orte_ras_oar_finalize(void)
{
    return ORTE_SUCCESS;
}

/* portable getline() function */

#define RAS_BASE_FILE_MAX_LINE_LENGTH   512

static char *ras_oar_getline(FILE *fp)
{
    char *ret, *buff = NULL;
    char input[RAS_BASE_FILE_MAX_LINE_LENGTH];

    ret = fgets(input, RAS_BASE_FILE_MAX_LINE_LENGTH, fp);
    if (NULL != ret) {
        input[strlen(input)-1] = '\0';  /* remove newline */
        buff = strdup(input);
    }

    return buff;
}

