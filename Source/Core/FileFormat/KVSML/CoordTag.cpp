/*****************************************************************************/
/**
 *  @file   CoordTag.cpp
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
#include "CoordTag.h"
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
CoordTag::CoordTag( void ):
    m_node( NULL )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the coord tag class.
 */
/*===========================================================================*/
CoordTag::~CoordTag( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node without 'const'.
 *  @return pointer to the node
 */
/*===========================================================================*/
kvs::XMLNode::SuperClass* CoordTag::node( void )
{
    return( m_node );
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node with 'const'.
 *  @return pointer to the node
 */
/*===========================================================================*/
const kvs::XMLNode::SuperClass* CoordTag::node( void ) const
{
    return( m_node );
}

/*===========================================================================*/
/**
 *  @brief  Reads the coord tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the reading process is done successfully
 */
/*===========================================================================*/
const bool CoordTag::read( const kvs::XMLNode::SuperClass* parent )
{
    m_node = kvs::XMLNode::FindChildNode( parent, "Coord" );
    if ( !m_node )
    {
        kvsMessageError("Cannot find <Coord>.");
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
const bool CoordTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::XMLElement element("Coord");

    m_node = parent->InsertEndChild( element );
    if( !m_node )
    {
        kvsMessageError("Cannot insert <Coord>.");
        return( false );
    }

    return( true );
}

} // end of namespace kvsml

} // end of namespace kvs
