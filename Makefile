#*****************************************************************************
#  $Id$
#*****************************************************************************

#=============================================================================
#  nmake cannot unroll macros in 'include' command.
#  if nmake preprocesses this file, this includes Makefile.$nmake.
#
#  make can unroll macros in 'include' command.
#  if make preprocesses this file, this includes Makefile.$make.
#=============================================================================

n = $$

include Makefile.$nmake
