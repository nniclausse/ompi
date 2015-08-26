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
/**
 * @file
 *
 * Resource Allocation (OAR)
 */
#ifndef ORTE_RAS_OAR_H
#define ORTE_RAS_OAR_H

#include "orte_config.h"
#include "orte/mca/ras/ras.h"

BEGIN_C_DECLS

/**
 * RAS Component 
 */
ORTE_DECLSPEC extern orte_ras_base_component_t mca_ras_oar_component;
ORTE_DECLSPEC extern orte_ras_base_module_t orte_ras_oar_module;

END_C_DECLS

#endif
