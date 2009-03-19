/*****************************************************************************/
/**
 *  @file   NodeTag.cpp
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
#include "NodeTag.h"
#include <kvs/Message>
#include <kvs/String>
#include <kvs/XMLNode>
#include <kvs/XMLElement>


namespace kvs
{

namespace kvsml
{

NodeTag::NodeTag( void ):
    m_node( NULL ),
    m_has_nnodes( false ),
    m_nnodes( 0 )
{
}

NodeTag::~NodeTag( void )
{
}

kvs::XMLNode::SuperClass* NodeTag::node( void )
{
    return( m_node );
}

const kvs::XMLNode::SuperClass* NodeTag::node( void ) const
{
    return( m_node );
}

const bool NodeTag::hasNNodes( void ) const
{
    return( m_has_nnodes );
}

const size_t NodeTag::nnodes( void ) const
{
    return( m_nnodes );
}

void NodeTag::setNNodes( const size_t nnodes )
{
    m_has_nnodes = true;
    m_nnodes = nnodes;
}

const bool NodeTag::read( const kvs::XMLNode::SuperClass* parent )
{
    m_node = kvs::XMLNode::FindChildNode( parent, "Node" );
    if ( !m_node )
    {
        kvsMessageError("Cannot find <Node>.");
        return( false );
    }

    // Element
    const kvs::XMLElement::SuperClass* element = kvs::XMLNode::ToElement( m_node );

    // nnodes="xxx"
    const std::string nnodes = kvs::XMLElement::AttributeValue( element, "nnodes" );
    if ( nnodes != "" )
    {
        m_has_nnodes = true;
        m_nnodes = static_cast<size_t>( atoi( nnodes.c_str() ) );
    }

    return( true );
}

const bool NodeTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::XMLElement element("Node");

    if ( m_has_nnodes )
    {
        const std::string name( "nnodes" );
        const std::string value( kvs::String( m_nnodes ).toStdString() );
        element.setAttribute( name, value );
    }

    m_node = parent->InsertEndChild( element );
    if( !m_node )
    {
        kvsMessageError("Cannot insert <Node>.");
        return( false );
    }

    return( true );
}

} // end of namespace kvsml

} // end of namespace kvs
