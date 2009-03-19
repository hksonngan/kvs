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
#include <kvs/OpenGL>
#include <kvs/Message>


namespace kvs
{

namespace qt
{

// Instantiation.
QApplication* GlobalBase::application;

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
    application = new QApplication( count, values );
    if ( !application )
    {
        kvsMessageError("Cannot create a Qt application.");
        return;
    }
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
GlobalBase::~GlobalBase( void )
{
    if ( application ) delete application;
}

} // end of namespce qt

} // end of namespace kvs
