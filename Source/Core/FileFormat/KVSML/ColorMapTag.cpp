/*****************************************************************************/
/**
 *  @file   ColorMapTag.cpp
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
#include "ColorMapTag.h"
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
 *  @brief  Constructs a new color tag class.
 */
/*===========================================================================*/
ColorMapTag::ColorMapTag( void ):
    m_node( NULL )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the color tag class.
 */
/*===========================================================================*/
ColorMapTag::~ColorMapTag( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node without 'const'.
 *  @return pointer to the node
 */
/*===========================================================================*/
kvs::XMLNode::SuperClass* ColorMapTag::node( void )
{
    return( m_node );
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node with 'const'.
 *  @return pointer to the node
 */
/*===========================================================================*/
const kvs::XMLNode::SuperClass* ColorMapTag::node( void ) const
{
    return( m_node );
}

/*===========================================================================*/
/**
 *  @brief  Check whether the parent node has the ColorMap tag or not.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the parent node has the ColorMap tag
 */
/*===========================================================================*/
const bool ColorMapTag::check( const kvs::XMLNode::SuperClass* parent ) const
{
    return( kvs::XMLNode::FindChildNode( parent, "ColorMap" ) != NULL );
}

/*===========================================================================*/
/**
 *  @brief  Reads the coord tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the reading process is done successfully
 */
/*===========================================================================*/
const bool ColorMapTag::read( const kvs::XMLNode::SuperClass* parent )
{
    m_node = kvs::XMLNode::FindChildNode( parent, "ColorMap" );
    if ( !m_node )
    {
        kvsMessageError("Cannot find <ColorMap>.");
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
const bool ColorMapTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::XMLElement element("ColorMap");

    m_node = parent->InsertEndChild( element );
    if( !m_node )
    {
        kvsMessageError("Cannot insert <ColorMap>.");
        return( false );
    }

    return( true );
}

} // end of namespace kvsml

} // end of namespace kvs
