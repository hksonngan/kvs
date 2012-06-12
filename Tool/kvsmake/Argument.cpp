/****************************************************************************/
/**
 *  @file Argument.cpp
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#include "Argument.h"
#include "CommandName.h"
#include <kvs/Compiler>


namespace kvsmake
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new Argument class.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Argument::Argument( int argc, char** argv ):
    kvs::CommandLine( argc, argv, kvsmake::CommandName )
{
    addHelpOption();

    addValue( "project_name/make_options", false );

    addOption( "g",      "Generate a makefile.", 1 );
    addOption( "G",      "Generate a makefile and set it's target name to the current directory name", 0 );

#if defined ( KVS_COMPILER_VC )
    addOption( "v",      "generate a project file for VC.", 1 );
    addOption( "vc",     "generate a project file for VC.", 1 );
    addOption( "vcproj", "generate a project file for VC.", 1 );

    addOption( "cuda", "generate a project file for VC and CUDA.", 1 );
#endif

    addOption( "q",      "Generate a project file for Qt.", 1 );
    addOption( "qt",     "Generate a project file for Qt.", 1 );
    addOption( "qtproj", "Generate a project file for Qt.", 1 );
}

} // end of namespace kvsmake
