/*****************************************************************************/
/**
 *  @file   DataValueTag.cpp
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
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
DataValueTag::DataValueTag():
    kvs::kvsml::TagBase( "DataValue" )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the data value class.
 */
/*===========================================================================*/
DataValueTag::~DataValueTag()
{
}

bool DataValueTag::read( const kvs::XMLNode::SuperClass* parent )
{
    kvs::IgnoreUnusedVariable( parent );
    return true;
}

bool DataValueTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::IgnoreUnusedVariable( parent );
    return true;
}

} // end of namespace kvsml

} // end of namespace kvs
