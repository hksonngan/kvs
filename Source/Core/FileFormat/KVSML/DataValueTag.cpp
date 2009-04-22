/*****************************************************************************/
/**
 *  @file   DataValueTag.cpp
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include "DataValueTag.h"


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new data value class.
 */
/*===========================================================================*/
DataValueTag::DataValueTag( void ):
    kvs::kvsml::TagBase( "DataValue" )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the data value class.
 */
/*===========================================================================*/
DataValueTag::~DataValueTag( void )
{
}

} // end of namespace kvsml

} // end of namespace kvs
