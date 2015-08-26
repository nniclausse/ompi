# -*- shell-script -*-
#
# Copyright (c) 2004-2005 The Trustees of Indiana University and Indiana
#                         University Research and Technology
#                         Corporation.  All rights reserved.
# Copyright (c) 2004-2005 The University of Tennessee and The University
#                         of Tennessee Research Foundation.  All rights
#                         reserved.
# Copyright (c) 2004-2005 High Performance Computing Center Stuttgart, 
#                         University of Stuttgart.  All rights reserved.
# Copyright (c) 2004-2005 The Regents of the University of California.
#                         All rights reserved.
# Copyright (c) 2006-2009 Cisco Systems, Inc.  All rights reserved.
# Copyright (c) 2011      IBM Corporation.  All rights reserved.
# $COPYRIGHT$
# 
# Additional copyrights may follow
# 
# $HEADER$
#

# 1. if --with-oar is given, always build
# 2. if --without-oar is given, never build
# 3. if neither is given, build if-and-only-if the OS is Linux or AIX

# ORTE_CHECK_OAR(prefix, [action-if-found], [action-if-not-found])
# --------------------------------------------------------
AC_DEFUN([ORTE_CHECK_OAR],[
    if test -z "$orte_check_oar_happy" ; then
        AC_ARG_WITH([oar],
                    [AC_HELP_STRING([--with-oar],
                                    [Build OAR scheduler component (default: yes)])])

        if test "$with_oar" = "no" ; then
            orte_check_oar_happy="no"
        elif test "$with_oar" = "" ; then
            # unless user asked, only build OAR component on Linux
            case $host in
                *-linux*)
                    orte_check_oar_happy="yes"
                    ;;
                *)
                    orte_check_oar_happy="no"
                    ;;
            esac
        else
            orte_check_oar_happy="yes"
        fi

        OPAL_SUMMARY_ADD([[Resource Managers]],[[OAR]],[$1],[$orte_check_oar_happy])
    fi

    AS_IF([test "$orte_check_oar_happy" = "yes"],
          [$2],
          [$3])
])
