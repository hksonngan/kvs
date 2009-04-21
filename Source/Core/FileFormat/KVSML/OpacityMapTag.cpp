/*****************************************************************************/
/**
 *  @file   OpacityMapTag.cpp
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
#include "OpacityMapTag.h"
#include <kvs/Message>
#include <kvs/String>
#include <kvs/XMLNode>
#include <kvs/XMLElement>


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new opacity map tag class.
 */
/*===========================================================================*/
OpacityMapTag::OpacityMapTag( void ):
    m_node( NULL )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the opacity map tag class.
 */
/*===========================================================================*/
OpacityMapTag::~OpacityMapTag( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node without 'const'.
 *  @return pointer to the node
 */
/*===========================================================================*/
kvs::XMLNode::SuperClass* OpacityMapTag::node( void )
{
    return( m_node );
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node with 'const'.
 *  @return pointer to the node
 */
/*===========================================================================*/
const kvs::XMLNode::SuperClass* OpacityMapTag::node( void ) const
{
    return( m_node );
}

/*===========================================================================*/
/**
 *  @brief  Check whether the parent node has the OpacityMap tag or not.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the parent node has the OpacityMap tag
 */
/*===========================================================================*/
const bool OpacityMapTag::check( const kvs::XMLNode::SuperClass* parent ) const
{
    return( kvs::XMLNode::FindChildNode( parent, "OpacityMap" ) != NULL );
}

/*===========================================================================*/
/**
 *  @brief  Reads the coord tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the reading process is done successfully
 */
/*===========================================================================*/
const bool OpacityMapTag::read( const kvs::XMLNode::SuperClass* parent )
{
    m_node = kvs::XMLNode::FindChildNode( parent, "OpacityMap" );
    if ( !m_node )
    {
        kvsMessageError("Cannot find <OpacityMap>.");
        return( false );
    }

    return( true );
}

/*===========================================================================*/
/**
 *  @brief  Writes the coord tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the writing process is done successfully
 */
/*===========================================================================*/
const bool OpacityMapTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::XMLElement element("OpacityMap");

    m_node = parent->InsertEndChild( element );
    if( !m_node )
    {
        kvsMessageError("Cannot insert <OpacityMap>.");
        return( false );
    }

    return( true );
}

} // end of namespace kvsml

} // end of namespace kvs
