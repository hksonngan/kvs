/****************************************************************************/
/**
 *  @file GlobalBase.cpp
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#include "GlobalBase.h"
#include "../SAGE.h"


namespace
{

void ShutdownApplication( void )
{
    kvs::sage::GlobalBase::sail->shutdown();
}

} // end of namespace


namespace kvs
{

namespace sage
{

// Parameter instantiation.
kvs::sage::ApplicationInterface* GlobalBase::sail;

/*==========================================================================*/
/**
 *  Constructor.
 *  @param count [in] argument count
 *  @param values [in] argument values
 */
/*==========================================================================*/
GlobalBase::GlobalBase( int count, char** values ):
    kvs::GlobalCore( count, values )
{
    glutInit( &kvs::GlobalCore::argc, kvs::GlobalCore::argv );

    sail = new kvs::sage::ApplicationInterface( count, values );
    if ( !sail )
    {
        kvsMessageError("Cannot allocate memory for the SAIL.");
        exit( EXIT_FAILURE );
    }

    atexit( ::ShutdownApplication );
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
GlobalBase::~GlobalBase( void )
{
    if ( sail ) delete sail;
}

} // end of namespce sage

} // end of namespace kvs
