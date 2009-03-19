/*****************************************************************************/
/**
 *  @file   VertexTag.cpp
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
#include "VertexTag.h"
#include <kvs/Message>
#include <kvs/String>
#include <kvs/XMLNode>
#include <kvs/XMLElement>


namespace kvs
{

namespace kvsml
{

VertexTag::VertexTag( void ):
    m_node( NULL ),
    m_has_nvertices( false ),
    m_nvertices( 0 )
{
}

VertexTag::~VertexTag( void )
{
}

kvs::XMLNode::SuperClass* VertexTag::node( void )
{
    return( m_node );
}

const kvs::XMLNode::SuperClass* VertexTag::node( void ) const
{
    return( m_node );
}

const bool VertexTag::hasNVertices( void ) const
{
    return( m_has_nvertices );
}

const size_t VertexTag::nvertices( void ) const
{
    return( m_nvertices );
}

void VertexTag::setNVertices( const size_t nvertices )
{
    m_has_nvertices = true;
    m_nvertices = nvertices;
}

const bool VertexTag::read( const kvs::XMLNode::SuperClass* parent )
{
    m_node = kvs::XMLNode::FindChildNode( parent, "Vertex" );
    if ( !m_node )
    {
        kvsMessageError("Cannot find <Vertex>.");
        return( false );
    }

    // Element
    const kvs::XMLElement::SuperClass* element = kvs::XMLNode::ToElement( m_node );

    // nvertices="xxx"
    const std::string nvertices = kvs::XMLElement::AttributeValue( element, "nvertices" );
    if ( nvertices != "" )
    {
        m_has_nvertices = true;
        m_nvertices = static_cast<size_t>( atoi( nvertices.c_str() ) );
    }

    return( true );
}

const bool VertexTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::XMLElement element("Vertex");

    if ( m_has_nvertices )
    {
        const std::string name( "nvertices" );
        const std::string value( kvs::String( m_nvertices ).toStdString() );
        element.setAttribute( name, value );
    }

    m_node = parent->InsertEndChild( element );
    if( !m_node )
    {
        kvsMessageError("Cannot insert <Vertex>.");
        return( false );
    }

    return( true );
}

} // end of namespace kvsml

} // end of namespace kvs
