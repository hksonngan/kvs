/****************************************************************************/
/**
 *  @file ImporterBase.cpp
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
#include "ImporterBase.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new ImporterBase class.
 */
/*===========================================================================*/
ImporterBase::ImporterBase( void )
    : m_is_success( true )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the ImageBase class.
 */
/*===========================================================================*/
ImporterBase::~ImporterBase( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Check whether the object is imported or not.
 *  @return true if the import process is done successfully
 */
/*===========================================================================*/
const bool ImporterBase::isSuccess( void ) const
{
    return( m_is_success );
}

/*===========================================================================*/
/**
 *  @brief  Check whether the object is imported or not.
 *  @return true if the object is not imported
 */
/*===========================================================================*/
const bool ImporterBase::isFailure( void ) const
{
    return( !m_is_success );
}

} // end of namespace kvs
