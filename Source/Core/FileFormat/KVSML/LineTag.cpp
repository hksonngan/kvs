/*****************************************************************************/
/**
 *  @file   LineTag.cpp
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
#include "LineTag.h"
#include <kvs/Message>
#include <kvs/String>
#include <kvs/XMLNode>
#include <kvs/XMLElement>


namespace kvs
{

namespace kvsml
{

LineTag::LineTag( void ):
    m_node( NULL ),
    m_has_nlines( false ),
    m_nlines( 0 )
{
}

LineTag::~LineTag( void )
{
}

kvs::XMLNode::SuperClass* LineTag::node( void )
{
    return( m_node );
}

const kvs::XMLNode::SuperClass* LineTag::node( void ) const
{
    return( m_node );
}

const bool LineTag::hasNLines( void ) const
{
    return( m_has_nlines );
}

const size_t LineTag::nlines( void ) const
{
    return( m_nlines );
}

void LineTag::setNLines( const size_t nlines )
{
    m_has_nlines = true;
    m_nlines = nlines;
}

const bool LineTag::read( const kvs::XMLNode::SuperClass* parent )
{
    m_node = kvs::XMLNode::FindChildNode( parent, "Line" );
    if ( !m_node )
    {
        kvsMessageError("Cannot find <Line>.");
        return( false );
    }

    // Element
    const kvs::XMLElement::SuperClass* element = kvs::XMLNode::ToElement( m_node );

    // nlines="xxx"
    const std::string nlines = kvs::XMLElement::AttributeValue( element, "nlines" );
    if ( nlines != "" )
    {
        m_has_nlines = true;
        m_nlines = static_cast<size_t>( atoi( nlines.c_str() ) );
    }

    return( true );
}

const bool LineTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::XMLElement element("Line");

    if ( m_has_nlines )
    {
        const std::string name( "nlines" );
        const std::string value( kvs::String( m_nlines ).toStdString() );
        element.setAttribute( name, value );
    }

    m_node = parent->InsertEndChild( element );
    if( !m_node )
    {
        kvsMessageError("Cannot insert <Line>.");
        return( false );
    }

    return( true );
}

} // end of namespace kvsml

} // end of namespace kvs
