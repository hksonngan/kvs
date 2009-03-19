/****************************************************************************/
/**
 *  @file UnstructuredVolumeObjectParser.cpp
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#include "UnstructuredVolumeObjectParser.h"
#include "TagParser.h"
#include "ValueTagParser.h"
#include "CoordTagParser.h"
#include "ConnectionTagParser.h"
#include <kvs/Tokenizer>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
UnstructuredVolumeObjectParser::UnstructuredVolumeObjectParser( void ):
    m_nnodes( 0 ),
    m_ncells( 0 ),
    m_volume_object_node( NULL )
{
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param document [in] refer to the XML document
 */
/*==========================================================================*/
UnstructuredVolumeObjectParser::UnstructuredVolumeObjectParser( const kvs::XMLDocument& document )
{
    this->parse( document );
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param document [in] pointer to the XML document
 */
/*==========================================================================*/
UnstructuredVolumeObjectParser::UnstructuredVolumeObjectParser( const kvs::XMLDocument* document )
{
    this->parse( document );
}

/*==========================================================================*/
/**
 *  Get the cell type.
 */
/*==========================================================================*/
const std::string& UnstructuredVolumeObjectParser::cellType( void ) const
{
    return( m_cell_type );
}

/*==========================================================================*/
/**
 *  Get the number of nodes.
 *  @return number of nodes
 */
/*==========================================================================*/
const size_t UnstructuredVolumeObjectParser::nnodes( void ) const
{
    return( m_nnodes );
}

/*==========================================================================*/
/**
 *  Get the number of cells.
 *  @return number of cells
 */
/*==========================================================================*/
const size_t UnstructuredVolumeObjectParser::ncells( void ) const
{
    return( m_ncells );
}

/*==========================================================================*/
/**
 *  Get the vector length.
 *  @return vector length
 */
/*==========================================================================*/
const size_t UnstructuredVolumeObjectParser::veclen( void ) const
{
    // <Value>
    TiXmlNode* value_node = kvs::TagParser::FindChildNode( m_node_node, "Value" );
    if( !value_node )
    {
        kvsMessageError("Cannot find <Value>.");
        return( size_t( 0 ) );
    }

    // <Value veclen="xxx">
    TiXmlElement* value_element = kvs::TagParser::NodeToElement( value_node );
    std::string veclen = kvs::TagParser::GetAttributeValue( value_element, "veclen" );
    if( veclen == "" )
    {
        kvsMessageError("Cannot find 'veclen' in <Value>.");
        return( size_t( 0 ) );
    }

    return( size_t( atoi( veclen.c_str() ) ) );
}

/*==========================================================================*/
/**
 *  Parse the XML document.
 *  @param document [in] refer to the XML document
 *  @return true, if the process is done successfully
 */
/*==========================================================================*/
bool UnstructuredVolumeObjectParser::parse( const kvs::XMLDocument& document )
{
    return( this->parse( &document ) );
}

/*==========================================================================*/
/**
 *  Parse the XML document.
 *  @param document [in] pointer to the XML document
 *  @return true, if the process is done successfully
 */
/*==========================================================================*/
bool UnstructuredVolumeObjectParser::parse( const kvs::XMLDocument* document )
{
    // <KVSML>
    if ( !m_kvsml_tag.read( document ) )
    {
        kvsMessageError("Cannot read <KVSML>.");
        return( false );
    }
/*
    TiXmlNode* kvsml_node = kvs::TagParser::FindNode( document, "KVSML" );
    if( !kvsml_node )
    {
        kvsMessageError("Cannot find <KVSML>.");
        return( false );
    }
*/

    // <Object>
    if ( !m_object_tag.read( m_kvsml_tag.node() ) )
    {
        kvsMessageError("Cannot read <Object>.");
        return( false );
    }
/*
    TiXmlNode* object_node = kvs::TagParser::FindChildNode( kvsml_node, "Object" );
    if( !object_node )
    {
        kvsMessageError("Cannot find <Object>.");
        return( false );
    }
*/
    // <Object type="xxx">
    if ( m_object_tag.type() != "UnstructuredVolumeObject" )
    {
        kvsMessageError("This file type is not a uniform volume object.");
        return( false );
    }
/*
    TiXmlElement* object_element = kvs::TagParser::NodeToElement( object_node );
    std::string object_type = kvs::TagParser::GetAttributeValue( object_element, "type" );
    if( object_type != "UnstructuredVolumeObject" )
    {
        kvsMessageError("This file type is not a uniform volume object.");
        return( false );
    }
*/

    // <UnstructuredVolumeObject>
//    m_volume_object_node = kvs::TagParser::FindChildNode( object_node, object_type );
    m_volume_object_node = kvs::TagParser::FindChildNode( m_object_tag.node(), m_object_tag.type() );
    if( !m_volume_object_node )
    {
        kvsMessageError("Cannot find <%s>.",m_object_tag.type().c_str());
        return( false );
    }

    // <UnstructuredVolumeObject cell_type="xxx">
    TiXmlElement* volume_element = kvs::TagParser::NodeToElement( m_volume_object_node );
    if( !this->parse_cell_type( volume_element ) )  return( false );

    // <Node>
    m_node_node = kvs::TagParser::FindChildNode( m_volume_object_node, "Node" );
    if( !m_node_node )
    {
        kvsMessageError("Cannot find <Node>.");
        return( false );
    }

    // <Node nnodes="xxx">
    TiXmlElement* node_element = kvs::TagParser::NodeToElement( m_node_node );
    if( !this->parse_nnodes( node_element ) )  return( false );

    // <Cell>
    m_cell_node = kvs::TagParser::FindChildNode( m_volume_object_node, "Cell" );
    if( !m_cell_node )
    {
        kvsMessageError("Cannot find <Cell>.");
        return( false );
    }

    // <Cell ncells="xxx">
    TiXmlElement* cell_element = kvs::TagParser::NodeToElement( m_cell_node );
    if( !this->parse_ncells( cell_element ) )  return( false );

    return( true );
}

/*==========================================================================*/
/**
 *  Set the value array to the given array.
 *  @param values [in] node value array
 */
/*==========================================================================*/
void UnstructuredVolumeObjectParser::setValuesTo( kvs::AnyValueArray* values )
{
    kvs::ValueTagParser( m_nnodes ).parse( m_node_node, values );
}

/*==========================================================================*/
/**
 *  Set the coordinate array to the given array.
 *  @param  coords [out] coordinate array
 */
/*==========================================================================*/
void UnstructuredVolumeObjectParser::setCoordsTo( kvs::ValueArray<kvs::Real32>* coords )
{
    kvs::CoordTagParser( m_nnodes ).parse( m_node_node, coords );
}

/*==========================================================================*/
/**
 *  Set the connection array to the given array.
 *  @param  connections [out] connection array
 */
/*==========================================================================*/
void UnstructuredVolumeObjectParser::setConnectionsTo( kvs::ValueArray<kvs::UInt32>* connections )
{
    size_t nindices = 0;
    if(      m_cell_type == "tetrahedra" ) nindices = m_ncells * 4;
    else if( m_cell_type == "hexahedra"  ) nindices = m_ncells * 8;

    kvs::ConnectionTagParser( nindices ).parse( m_cell_node, connections );
}

/*==========================================================================*/
/**
 *  Parse the number of nodes.
 *  @param element [in] pointer to the element
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool UnstructuredVolumeObjectParser::parse_nnodes( const TiXmlElement* element )
{
    std::string nnodes = kvs::TagParser::GetAttributeValue( element, "nnodes" );
    if( nnodes == "" )
    {
        kvsMessageError("Cannot find 'nnodes' in <Node>.");
        return( false );
    }

    m_nnodes = static_cast<size_t>( atoi( nnodes.c_str() ) );

    return( true );
}

/*==========================================================================*/
/**
 *  Parse the number of cells.
 *  @param element [in] pointer to the element
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool UnstructuredVolumeObjectParser::parse_ncells( const TiXmlElement* element )
{
    std::string ncells = kvs::TagParser::GetAttributeValue( element, "ncells" );
    if( ncells == "" )
    {
        kvsMessageError("Cannot find 'ncells' in <Node>.");
        return( false );
    }

    m_ncells = static_cast<size_t>( atoi( ncells.c_str() ) );

    return( true );
}

/*==========================================================================*/
/**
 *  Parse the cell type.
 *  @param element [in] pointer to the element
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool UnstructuredVolumeObjectParser::parse_cell_type( const TiXmlElement* element )
{
    m_cell_type = kvs::TagParser::GetAttributeValue( element, "cell_type" );

    return( m_cell_type == "tetrahedra" || m_cell_type == "tet" ||
            m_cell_type == "hexahedra"  || m_cell_type == "hex" ||
            m_cell_type == "quadratic tetrahedra" || m_cell_type == "tet2" ||
            m_cell_type == "quadratic hexahedra"  || m_cell_type == "hex2" );
}

const bool UnstructuredVolumeObjectParser::Check( const kvs::XMLDocument& document )
{
    // <KVSML>
    TiXmlNode* kvsml_node = kvs::TagParser::FindNode( &document, "KVSML" );
    if( !kvsml_node ) return( false );

    // <Object>
    TiXmlNode* object_node = kvs::TagParser::FindChildNode( kvsml_node, "Object" );
    if( !object_node ) return( false );

    // <Object type="xxx">
    TiXmlElement* object_element = kvs::TagParser::NodeToElement( object_node );
    const std::string object_type = kvs::TagParser::GetAttributeValue( object_element, "type" );
    if( object_type != "UnstructuredVolumeObject" ) return( false );

    // <UnstructuredVolumeObject>
    TiXmlNode* unstructured_volume_object_node = kvs::TagParser::FindChildNode( object_node, object_type );
    if( !unstructured_volume_object_node ) return( false );

    return( true );
}

} // end of namesapce kvs
