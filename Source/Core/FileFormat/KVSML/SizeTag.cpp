/*****************************************************************************/
/**
 *  @file   SizeTag.cpp
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
#include "SizeTag.h"
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
 *  @brief  Constructs a new size tag class.
 */
/*===========================================================================*/
SizeTag::SizeTag( void ):
    m_node( NULL )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the size tag class.
 */
/*===========================================================================*/
SizeTag::~SizeTag( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node without 'const'.
 *  @return pointer to the node
 */
/*===========================================================================*/
kvs::XMLNode::SuperClass* SizeTag::node( void )
{
    return( m_node );
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node with 'const'.
 *  @return pointer to the node
 */
/*===========================================================================*/
const kvs::XMLNode::SuperClass* SizeTag::node( void ) const
{
    return( m_node );
}

/*===========================================================================*/
/**
 *  @brief  Reads the size tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the reading process is done successfully
 */
/*===========================================================================*/
const bool SizeTag::read( const kvs::XMLNode::SuperClass* parent )
{
    m_node = kvs::XMLNode::FindChildNode( parent, "Size" );
    if ( !m_node )
    {
        kvsMessageError("Cannot find <Size>.");
        return( false );
    }

    return( true );
}

/*===========================================================================*/
/**
 *  @brief  Writes the size tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the writing process is done successfully
 */
/*===========================================================================*/
const bool SizeTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::XMLElement element("Size");

    m_node = parent->InsertEndChild( element );
    if( !m_node )
    {
        kvsMessageError("Cannot insert <Size>.");
        return( false );
    }

    return( true );
}

} // end of namespace kvsml

} // end of namespace kvs
