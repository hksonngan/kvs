/*****************************************************************************/
/**
 *  @file   ValueTag.cpp
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
#include "ValueTag.h"
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
 *  @brief  Constructs a new value tag class.
 */
/*===========================================================================*/
ValueTag::ValueTag( void ):
    m_node( NULL ),
    m_has_veclen( false ),
    m_veclen( 0 )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the value tag class.
 */
/*===========================================================================*/
ValueTag::~ValueTag( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node without 'const'.
 *  @return pointer to the node
 */
/*===========================================================================*/
kvs::XMLNode::SuperClass* ValueTag::node( void )
{
    return( m_node );
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node with 'const'.
 *  @return pointer to the node
 */
/*===========================================================================*/
const kvs::XMLNode::SuperClass* ValueTag::node( void ) const
{
    return( m_node );
}

/*===========================================================================*/
/**
 *  @brief  Tests whether the 'veclen' is specified or not.
 *  @return true, if the 'veclen' is specified
 */
/*===========================================================================*/
const bool ValueTag::hasVeclen( void ) const
{
    return( m_has_veclen );
}

/*===========================================================================*/
/**
 *  @brief  Returns a vector length that is specified by 'veclen'.
 *  @return vector length
 */
/*===========================================================================*/
const size_t ValueTag::veclen( void ) const
{
    return( m_veclen );
}

/*===========================================================================*/
/**
 *  @brief  Sets a vector length.
 *  @param  veclen [in] vector length
 */
/*===========================================================================*/
void ValueTag::setVeclen( const size_t veclen )
{
    m_has_veclen = true;
    m_veclen = veclen;
}

/*===========================================================================*/
/**
 *  @brief  Reads the value tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the reading process is done successfully
 */
/*===========================================================================*/
const bool ValueTag::read( const kvs::XMLNode::SuperClass* parent )
{
    m_node = kvs::XMLNode::FindChildNode( parent, "Value" );
    if ( !m_node )
    {
        kvsMessageError("Cannot find <Value>.");
        return( false );
    }

    // Element
    const kvs::XMLElement::SuperClass* element = kvs::XMLNode::ToElement( m_node );

    // veclen="xxx"
    const std::string veclen = kvs::XMLElement::AttributeValue( element, "veclen" );
    if ( veclen != "" )
    {
        m_has_veclen = true;
        m_veclen = static_cast<size_t>( atoi( veclen.c_str() ) );
    }

    return( true );
}

/*===========================================================================*/
/**
 *  @brief  Writes the value tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the writing process is done successfully
 */
/*===========================================================================*/
const bool ValueTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::XMLElement element("Value");

    if ( m_has_veclen )
    {
        const std::string name( "veclen" );
        const std::string value( kvs::String( m_veclen ).toStdString() );
        element.setAttribute( name, value );
    }
    else
    {
        kvsMessageError( "'veclen' is not specified in <Value>." );
        return( false );
    }

    m_node = parent->InsertEndChild( element );
    if( !m_node )
    {
        kvsMessageError("Cannot insert <Value>.");
        return( false );
    }

    return( true );
}

} // end of namespace kvsml

} // end of namespace kvs
