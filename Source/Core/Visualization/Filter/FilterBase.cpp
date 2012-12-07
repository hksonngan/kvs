/****************************************************************************/
/**
 *  @file FilterBase.cpp
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
#include "FilterBase.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new FilterBase class.
 */
/*===========================================================================*/
FilterBase::FilterBase():
    m_is_success( true )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the FilterBase class.
 */
/*===========================================================================*/
FilterBase::~FilterBase()
{
}

/*===========================================================================*/
/**
 *  @brief  Check whether the filter process is success or not.
 *  @return true if the filter process is done successfully
 */
/*===========================================================================*/
bool FilterBase::isSuccess() const
{
    return m_is_success;
}

/*===========================================================================*/
/**
 *  @brief  Check whether the filter process is success or not.
 *  @return true if the filter process is failed
 */
/*===========================================================================*/
bool FilterBase::isFailure() const
{
    return !m_is_success;
}

/*===========================================================================*/
/**
 *  @brief  Sets a status of the filtering process.
 *  @param  success [in] status of filtering process
 */
/*===========================================================================*/
void FilterBase::setSuccess( const bool success )
{
    m_is_success = success;
}

} // end of namespace kvs
