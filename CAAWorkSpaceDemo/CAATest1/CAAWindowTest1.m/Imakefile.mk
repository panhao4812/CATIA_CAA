# COPYRIGHT Dassault Systemes 2016
#======================================================================
# Imakefile for module CAAWindowTest1.m
#======================================================================
#
#  Jan 2016  Creation: Code generated by the CAA wizard  Administrator
#======================================================================
#
# LOAD MODULE 
#
BUILT_OBJECT_TYPE=LOAD MODULE 
 
# DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
WIZARD_LINK_MODULES = JS0GROUP \
DI0PANV2 
# END WIZARD EDITION ZONE

LINK_WITH = JS0GROUP DI0PANV2 JS0FM

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
MKMFC_DEPENDENCY = yes
 LOCAL_LDFLAGS = $(SUB_WIN)