/*****************************************************************************/
/**
 *  @file   CellTag.cpp
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
#include "CellTag.h"
#include <kvs/Message>
#include <kvs/String>
#include <kvs/XMLNode>
#include <kvs/XMLElement>


namespace kvs
{

namespace kvsml
{

CellTag::CellTag( void ):
    m_node( NULL ),
    m_has_ncells( false ),
    m_ncells( 0 )
{
}

CellTag::~CellTag( void )
{
}

kvs::XMLNode::SuperClass* CellTag::node( void )
{
    return( m_node );
}

const kvs::XMLNode::SuperClass* CellTag::node( void ) const
{
    return( m_node );
}

const bool CellTag::hasNCells( void ) const
{
    return( m_has_ncells );
}

const size_t CellTag::ncells( void ) const
{
    return( m_ncells );
}

void CellTag::setNCells( const size_t ncells )
{
    m_has_ncells = true;
    m_ncells = ncells;
}

const bool CellTag::read( const kvs::XMLNode::SuperClass* parent )
{
    m_node = kvs::XMLNode::FindChildNode( parent, "Cell" );
    if ( !m_node )
    {
        kvsMessageError("Cannot find <Cell>.");
        return( false );
    }

    // Element
    const kvs::XMLElement::SuperClass* element = kvs::XMLNode::ToElement( m_node );

    // ncells="xxx"
    const std::string ncells = kvs::XMLElement::AttributeValue( element, "ncells" );
    if ( ncells != "" )
    {
        m_has_ncells = true;
        m_ncells = static_cast<size_t>( atoi( ncells.c_str() ) );
    }

    return( true );
}

const bool CellTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::XMLElement element("Cell");

    if ( m_has_ncells )
    {
        const std::string name( "ncells" );
        const std::string value( kvs::String( m_ncells ).toStdString() );
        element.setAttribute( name, value );
    }

    m_node = parent->InsertEndChild( element );
    if( !m_node )
    {
        kvsMessageError("Cannot insert <Cell>.");
        return( false );
    }

    return( true );
}

} // end of namespace kvsml

} // end of namespace kvs
