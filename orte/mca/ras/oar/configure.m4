# -*- shell-script -*-
#
# Copyright (c) 2008      The University of Tennessee and The University
#                         of Tennessee Research Foundation.  All rights
#                         reserved.
# Copyright (c) 2008      Institut National de Recherche en Informatique
#                         et Automatique. All rights reserved.
#
# Additional copyrights may follow
# 
# $HEADER$
#


# MCA_ras_oar_CONFIG([action-if-found], [action-if-not-found])
# -----------------------------------------------------------
AC_DEFUN([MCA_orte_ras_oar_CONFIG],[
    AC_CONFIG_FILES([orte/mca/ras/oar/Makefile])

    ORTE_CHECK_OAR([ras_oar], [ras_oar_good=1], [ras_oar_good=0])

    # if check worked, set wrapper flags if so.  
    # Evaluate succeed / fail
    AS_IF([test "$ras_oar_good" = "1"],
          [$1],
          [$2])

    # set build flags to use in makefile
    AC_SUBST([ras_oar_CPPFLAGS])
    AC_SUBST([ras_oar_LDFLAGS])
    AC_SUBST([ras_oar_LIBS])
])dnl
