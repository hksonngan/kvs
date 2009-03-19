/*****************************************************************************/
/**
 *  @file   UnstructuredVolumeObjectTag.cpp
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
#include "UnstructuredVolumeObjectTag.h"
#include <kvs/XMLNode>
#include <kvs/XMLElement>
#include <kvs/Tokenizer>
#include <kvs/String>


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new unstructured volume object tag class.
 */
/*===========================================================================*/
UnstructuredVolumeObjectTag::UnstructuredVolumeObjectTag( void ):
    m_node( NULL ),
    m_has_cell_type( false ),
    m_cell_type( "" )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the unstructured volume object class.
 */
/*===========================================================================*/
UnstructuredVolumeObjectTag::~UnstructuredVolumeObjectTag( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node without 'const'.
 *  @return pointer to the node
 */
/*===========================================================================*/
kvs::XMLNode::SuperClass* UnstructuredVolumeObjectTag::node( void )
{
    return( m_node );
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node with 'const'.
 *  @return pointer to the node
 */
/*===========================================================================*/
const kvs::XMLNode::SuperClass* UnstructuredVolumeObjectTag::node( void ) const
{
    return( m_node );
}

/*===========================================================================*/
/**
 *  @brief  Tests whether the 'cell_type' is specified or not.
 *  @return true, if the 'cell_type' is specified
 */
/*===========================================================================*/
const bool UnstructuredVolumeObjectTag::hasCellType( void ) const
{
    return( m_has_cell_type );
}

/*===========================================================================*/
/**
 *  @brief  Returns a cell type as string.
 *  @return cell type
 */
/*===========================================================================*/
const std::string& UnstructuredVolumeObjectTag::cellType( void ) const
{
    return( m_cell_type );
}

/*===========================================================================*/
/**
 *  @brief  Sets a cell type as string.
 *  @param  cell_type [in] cell type
 */
/*===========================================================================*/
void UnstructuredVolumeObjectTag::setCellType( const std::string& cell_type )
{
    m_has_cell_type = true;
    m_cell_type = cell_type;
}

/*===========================================================================*/
/**
 *  @brief  Reads the unstructured volume object tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the reading process is done successfully
 */
/*===========================================================================*/
const bool UnstructuredVolumeObjectTag::read( const kvs::XMLNode::SuperClass* parent )
{
    m_node = kvs::XMLNode::FindChildNode( parent, "UnstructuredVolumeObject" );
    if ( !m_node )
    {
        kvsMessageError("Cannot find <UnstructuredVolumeObject>.");
        return( false );
    }

    // Element
    const kvs::XMLElement::SuperClass* element = kvs::XMLNode::ToElement( m_node );

    // cell_type="xxx"
    const std::string cell_type = kvs::XMLElement::AttributeValue( element, "cell_type" );
    if ( cell_type != "" )
    {
        m_has_cell_type = true;
        m_cell_type = cell_type;
    }

    return( true );
}

/*===========================================================================*/
/**
 *  @brief  Writes the unstructured volume object tag.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the writing process is done successfully
 */
/*===========================================================================*/
const bool UnstructuredVolumeObjectTag::write( kvs::XMLNode::SuperClass* parent )
{
    kvs::XMLElement element("UnstructuredVolumeObject");

    if ( m_has_cell_type )
    {
        const std::string name( "cell_type" );
        const std::string value( m_cell_type );
        element.setAttribute( name, value );
    }
    else
    {
        kvsMessageError( "'cell_type' is not specified in <UnstructuredVolumeObject>." );
        return( false );
    }

    m_node = parent->InsertEndChild( element );
    if( !m_node )
    {
        kvsMessageError("Cannot insert <UnstructuredVolumeObject>.");
        return( false );
    }

    return( true );
}

} // end of namespace kvsml

} // end of namespace kvs
