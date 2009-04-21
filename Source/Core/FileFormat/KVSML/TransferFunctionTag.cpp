/*****************************************************************************/
/**
 *  @file   TransferFunctionTag.cpp
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
#include "TransferFunctionTag.h"
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
 *  @brief  Constructs a new TransferFunctionTag class.
 */
/*===========================================================================*/
TransferFunctionTag::TransferFunctionTag( void ):
    m_node( NULL ),
    m_has_file( false ),
    m_file( "" ),
    m_has_resolution( false ),
    m_resolution( 0 )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the TransferFunctionTag class.
 */
/*===========================================================================*/
TransferFunctionTag::~TransferFunctionTag( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node.
 *  @return pointer to the node
 */
/*===========================================================================*/
kvs::XMLNode::SuperClass* TransferFunctionTag::node( void )
{
    return( m_node );
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node.
 *  @return pointer to the node
 */
/*===========================================================================*/
const kvs::XMLNode::SuperClass* TransferFunctionTag::node( void ) const
{
    return( m_node );
}

/*===========================================================================*/
/**
 *  @brief  Tests whether the file is specified or not.
 *  @return true, if the file is specified
 */
/*===========================================================================*/
const bool TransferFunctionTag::hasFile( void ) const
{
    return( m_has_file );
}

/*===========================================================================*/
/**
 *  @brief  Returns a name of external file.
 *  @return filename
 */
/*===========================================================================*/
const std::string& TransferFunctionTag::file( void ) const
{
    return( m_file );
}

/*===========================================================================*/
/**
 *  @brief  Tests whether the resolution is specified or not.
 *  @return true, if the resolution is specified
 */
/*===========================================================================*/
const bool TransferFunctionTag::hasResolution( void ) const
{
    return( m_has_resolution );
}

/*===========================================================================*/
/**
 *  @brief  Returns a resolution.
 *  @return resolution
 */
/*===========================================================================*/
const size_t TransferFunctionTag::resolution( void ) const
{
    return( m_resolution );
}

/*===========================================================================*/
/**
 *  @brief  Sets a name of external file for 'argb' data.
 *  @param  file [in] filename
 */
/*===========================================================================*/
void TransferFunctionTag::setFile( const std::string& file )
{
    m_file = file;
}

/*===========================================================================*/
/**
 *  @brief  Sets a resolution.
 *  @param  resolution [in] resolution
 */
/*===========================================================================*/
void TransferFunctionTag::setResolution( const size_t resolution )
{
    m_has_resolution = true;
    m_resolution = resolution;
}

/*===========================================================================*/
/**
 *  @brief  Reads a transfer function tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the reading process is done successfully
 */
/*===========================================================================*/
const bool TransferFunctionTag::read( const kvs::XMLNode::SuperClass* parent )
{
    m_node = kvs::XMLNode::FindChildNode( parent, "TransferFunction" );
    if ( !m_node )
    {
        kvsMessageError("Cannot find <TransferFunction>.");
        return( false );
    }

    // Element
    const kvs::XMLElement::SuperClass* element = kvs::XMLNode::ToElement( m_node );

    // resolution="xxx"
    const std::string resolution = kvs::XMLElement::AttributeValue( element, "resolution" );
    if ( resolution != "" )
    {
        m_has_resolution = true;
        m_resolution = static_cast<size_t>( atoi( resolution.c_str() ) );
    }

    // file="xxx"
    const std::string file = kvs::XMLElement::AttributeValue( element, "file" );
    if ( file != "" )
    {
        m_has_file = true;
        m_file = static_cast<size_t>( atoi( file.c_str() ) );
    }

    return( true );
}

/*===========================================================================*/
/**
 *  @brief  Writes a transfer function tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the writing process is done successfully
 */
/*===========================================================================*/
const bool TransferFunctionTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::XMLElement element("TransferFunction");

    // resolution="xxx"
    if ( m_has_resolution )
    {
        const std::string name( "resolution" );
        const std::string value( kvs::String( m_resolution ).toStdString() );
        element.setAttribute( name, value );
    }

    // file="xxx"
    if ( m_has_file )
    {
        const std::string name( "file" );
        const std::string value( m_file );
        element.setAttribute( name, value );
    }

    m_node = parent->InsertEndChild( element );
    if( !m_node )
    {
        kvsMessageError("Cannot insert <TransferFunction>.");
        return( false );
    }

    return( true );
}

} // end of namespace kvsml

} // end of namespace kvs
