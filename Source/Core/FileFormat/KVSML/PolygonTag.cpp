/*****************************************************************************/
/**
 *  @file   PolygonTag.cpp
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
#include "PolygonTag.h"
#include <kvs/Message>
#include <kvs/String>
#include <kvs/XMLNode>
#include <kvs/XMLElement>


namespace kvs
{

namespace kvsml
{

PolygonTag::PolygonTag( void ):
    m_node( NULL ),
    m_has_npolygons( false ),
    m_npolygons( 0 )
{
}

PolygonTag::~PolygonTag( void )
{
}

kvs::XMLNode::SuperClass* PolygonTag::node( void )
{
    return( m_node );
}

const kvs::XMLNode::SuperClass* PolygonTag::node( void ) const
{
    return( m_node );
}

const bool PolygonTag::hasNPolygons( void ) const
{
    return( m_has_npolygons );
}

const size_t PolygonTag::npolygons( void ) const
{
    return( m_npolygons );
}

void PolygonTag::setNPolygons( const size_t npolygons )
{
    m_has_npolygons = true;
    m_npolygons = npolygons;
}

const bool PolygonTag::read( const kvs::XMLNode::SuperClass* parent )
{
    m_node = kvs::XMLNode::FindChildNode( parent, "Polygon" );
    if ( !m_node )
    {
        kvsMessageError("Cannot find <Polygon>.");
        return( false );
    }

    // Element
    const kvs::XMLElement::SuperClass* element = kvs::XMLNode::ToElement( m_node );

    // npolygons="xxx"
    const std::string npolygons = kvs::XMLElement::AttributeValue( element, "npolygons" );
    if ( npolygons != "" )
    {
        m_has_npolygons = true;
        m_npolygons = static_cast<size_t>( atoi( npolygons.c_str() ) );
    }

    return( true );
}

const bool PolygonTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::XMLElement element("Polygon");

    if ( m_has_npolygons )
    {
        const std::string name( "npolygons" );
        const std::string value( kvs::String( m_npolygons ).toStdString() );
        element.setAttribute( name, value );
    }

    m_node = parent->InsertEndChild( element );
    if( !m_node )
    {
        kvsMessageError("Cannot insert <Polygon>.");
        return( false );
    }

    return( true );
}

} // end of namespace kvsml

} // end of namespace kvs
