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

/*===========================================================================*/
/**
 *  @brief  Constructs a new FilterBase class.
 */
/*===========================================================================*/
FilterBase::FilterBase( void )
    : m_is_success( true )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the FilterBase class.
 */
/*===========================================================================*/
FilterBase::~FilterBase( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Check whether the filter process is success or not.
 *  @return true if the filter process is done successfully
 */
/*===========================================================================*/
const bool FilterBase::isSuccess( void ) const
{
    return( m_is_success );
}

/*===========================================================================*/
/**
 *  @brief  Check whether the filter process is success or not.
 *  @return true if the filter process is failed
 */
/*===========================================================================*/
const bool FilterBase::isFailure( void ) const
{
    return( !m_is_success );
}

} // end of namespace kvs
