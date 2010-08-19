/****************************************************************************/
/**
 *  @file GlobalBase.cpp
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
#include "GlobalBase.h"
#include "../GLUT.h"
#include <kvs/Message>


namespace kvs
{

namespace glut
{

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
    glutInit( &GlobalCore::argc, GlobalCore::argv );
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
GlobalBase::~GlobalBase( void )
{
}

} // end of namespce glut

} // end of namespace kvs
