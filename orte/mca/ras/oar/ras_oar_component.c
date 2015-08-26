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

#include "opal/mca/base/base.h"
#include "opal/util/basename.h"

#include "ras_oar.h"

/*
 * Local functions
 */

static int orte_ras_oar_open(void);
static int orte_ras_oar_close(void);
static int orte_ras_oar_component_query(mca_base_module_t **module, int *priority);


orte_ras_base_component_t mca_ras_oar_component = {
    .base_version = {

        /* Indicate that we are a ras v2.0.0 component (which also
           implies a specific MCA version) */
        ORTE_RAS_BASE_VERSION_2_0_0,

        /* Component name and version */
        .mca_component_name = "oar",
        MCA_BASE_MAKE_VERSION(component, ORTE_MAJOR_VERSION, ORTE_MINOR_VERSION,
                              ORTE_RELEASE_VERSION),

        /* Component open and close functions */
        .mca_open_component = orte_ras_oar_open,
        .mca_close_component = orte_ras_oar_close,
        .mca_query_component = orte_ras_oar_component_query,
    },
    .base_data = {
        /* The component is checkpoint ready */
        MCA_BASE_METADATA_PARAM_CHECKPOINT
    },
};


/**
  * component open/close/init function
  */
static int orte_ras_oar_open(void)
{
    return ORTE_SUCCESS;
}


static int orte_ras_oar_component_query(mca_base_module_t **module, int *priority)
{
    /* check if oar is running here */
    if ( NULL == getenv("OAR_JOBID") ) {
        /* nope, not here */
        *module = NULL;
        return ORTE_ERROR;
    }

    *priority = 85;
    *module = (mca_base_module_t *) &orte_ras_oar_module;
    return ORTE_SUCCESS;
}

/**
 *  Close all subsystems.
 */

static int orte_ras_oar_close(void)
{
    return ORTE_SUCCESS;
}


