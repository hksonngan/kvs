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

DataValueTag::DataValueTag( void ):
    m_node( NULL )
{
}

DataValueTag::~DataValueTag( void )
{
}

kvs::XMLNode::SuperClass* DataValueTag::node( void )
{
    return( m_node );
}

const kvs::XMLNode::SuperClass* DataValueTag::node( void ) const
{
    return( m_node );
}

} // end of namespace kvsml

} // end of namespace kvs
