/****************************************************************************/
/**
 *  @file FilterBase.cpp
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
#include "FilterBase.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Default constructor.
 */
/*==========================================================================*/
FilterBase::FilterBase( void ):
    m_good( true )
{
}

FilterBase::~FilterBase( void )
{
}

/*==========================================================================*/
/**
 *  Get the good flag.
 */
/*==========================================================================*/
const bool FilterBase::good( void ) const
{
    return( m_good );
}

/*==========================================================================*/
/**
 *  Get the fail flag.
 */
/*==========================================================================*/
const bool FilterBase::fail( void ) const
{
    return( !this->good() );
}

} // end of namespace kvs
