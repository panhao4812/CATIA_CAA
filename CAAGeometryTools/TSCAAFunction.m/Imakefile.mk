# COPYRIGHT Dassault Systemes 2016
#======================================================================
# Imakefile for module TSCatiaEXE.m
#======================================================================
#
#  Nov 2016  Creation: Code generated by the CAA wizard  Administrator
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES = JS0GROUP
# END WIZARD EDITION ZONE

LINK_WITH = JS0GROUP  \
 CATDraftingInterfaces  \
CATObjectModelerBase \
CATObjectSpecsModeler \
# System dependant variables
#
OS = AIX
#
OS = HP-UX
#
OS = IRIX
#
OS = SunOS
#
OS = Windows_NT