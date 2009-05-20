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
#include <kvs/IgnoreUnusedVariable>


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

const bool DataValueTag::read( const kvs::XMLNode::SuperClass* parent )
{
    kvs::IgnoreUnusedVariable( parent );
    return( true );
}

const bool DataValueTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::IgnoreUnusedVariable( parent );
    return( true );
}

} // end of namespace kvsml

} // end of namespace kvs
