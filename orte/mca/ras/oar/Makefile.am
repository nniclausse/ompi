#
# Copyright (c) 2008      The University of Tennessee and The University
#                         of Tennessee Research Foundation.  All rights
#                         reserved.
# Copyright (c) 2008      Institut National de Recherche en Informatique
#                         et Automatique. All rights reserved.
# $COPYRIGHT$
# 
# Additional copyrights may follow
# 
# $HEADER$
#


# Use the top-level Makefile.options

dist_ompidata_DATA = help-ras-oar.txt


AM_CPPFLAGS = $(ras_oar_CPPFLAGS)

sources = \
        ras_oar.h \
        ras_oar_component.c \
        ras_oar_module.c


# Make the output library in this directory, and name it either
# mca_<type>_<name>.la (for DSO builds) or libmca_<type>_<name>.la
# (for static builds).

if MCA_BUILD_orte_ras_oar_DSO
lib =
lib_sources = 
component = mca_ras_oar.la
component_sources = $(sources)
else
lib = libmca_ras_oar.la
lib_sources = $(sources)
component =
component_sources =
endif

mcacomponentdir = $(ompilibdir)
mcacomponent_LTLIBRARIES = $(component)
mca_ras_oar_la_SOURCES = $(component_sources)
mca_ras_oar_la_LDFLAGS = -module -avoid-version $(ras_oar_LDFLAGS)
mca_ras_oar_la_LIBADD = $(ras_oar_LIBS)

noinst_LTLIBRARIES = $(lib)
libmca_ras_oar_la_SOURCES = $(lib_sources)
libmca_ras_oar_la_LDFLAGS = -module -avoid-version $(ras_oar_LDFLAGS)
libmca_ras_oar_la_LIBADD = $(ras_oar_LIBS)
