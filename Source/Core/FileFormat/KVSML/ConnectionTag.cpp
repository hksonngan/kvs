/*****************************************************************************/
/**
 *  @file   ConnectionTag.cpp
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
#include "ConnectionTag.h"
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
 *  @brief  Constructs a new coord tag class.
 */
/*===========================================================================*/
ConnectionTag::ConnectionTag( void ):
    m_node( NULL )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the coord tag class.
 */
/*===========================================================================*/
ConnectionTag::~ConnectionTag( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node without 'const'.
 *  @return pointer to the node
 */
/*===========================================================================*/
kvs::XMLNode::SuperClass* ConnectionTag::node( void )
{
    return( m_node );
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node with 'const'.
 *  @return pointer to the node
 */
/*===========================================================================*/
const kvs::XMLNode::SuperClass* ConnectionTag::node( void ) const
{
    return( m_node );
}

/*===========================================================================*/
/**
 *  @brief  Reads the connection tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the reading process is done successfully
 */
/*===========================================================================*/
const bool ConnectionTag::read( const kvs::XMLNode::SuperClass* parent )
{
    m_node = kvs::XMLNode::FindChildNode( parent, "Connection" );
    if ( !m_node )
    {
        kvsMessageError("Cannot find <Connection>.");
        return( false );
    }

    return( true );
}

/*===========================================================================*/
/**
 *  @brief  Writes the connection tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the writing process is done successfully
 */
/*===========================================================================*/
const bool ConnectionTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::XMLElement element("Connection");

    m_node = parent->InsertEndChild( element );
    if( !m_node )
    {
        kvsMessageError("Cannot insert <Connection>.");
        return( false );
    }

    return( true );
}

} // end of namespace kvsml

} // end of namespace kvs
