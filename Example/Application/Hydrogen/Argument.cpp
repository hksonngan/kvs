/*****************************************************************************/
/**
 *  @file   Argument.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include "Argument.h"


/*===========================================================================*/
/**
 *  @brief  Constructs a new Argument class.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Argument::Argument( int argc, char** argv ):
    kvs::CommandLine( argc, argv )
{
    addHelpOption();
    addOption( "r", "Volume resolution. (default: 64 64 64)", 3, false );
    addOption( "a", "External ascii type for KVSML format. (optional)", 0, false );
    addOption( "b", "External binary type for KVSML format. (optional)", 0, false );
    addOption( "verbose", "Verbose mode. (optional)", 0, false );
    addValue( "Output filename [ *.fld | *.kvsml ]. (default: hydrogen.kvsml)", false );
}
