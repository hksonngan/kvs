/****************************************************************************/
/**
 *  @file ImporterBase.cpp
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
#include "ImporterBase.h"


namespace kvs
{

ImporterBase::ImporterBase( void )
    : m_is_success( false )
{
}

ImporterBase::~ImporterBase( void )
{
}

const bool ImporterBase::isSuccess( void ) const
{
    return( m_is_success );
}

const bool ImporterBase::isFailure( void ) const
{
    return( !m_is_success );
}

} // end of namespace kvs
