/****************************************************************************/
/**
 *  @file StructuredVolumeObjectParser.cpp
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
#include "StructuredVolumeObjectParser.h"
#include "TagParser.h"
#include "ValueTagParser.h"
#include "CoordTagParser.h"
#include <kvs/Tokenizer>


namespace kvs
{

StructuredVolumeObjectParser::StructuredVolumeObjectParser( void ):
    m_volume_object_node( NULL )
{
}

StructuredVolumeObjectParser::StructuredVolumeObjectParser( const kvs::XMLDocument& document )
{
    this->parse( document );
}

StructuredVolumeObjectParser::StructuredVolumeObjectParser( const kvs::XMLDocument* document )
{
    this->parse( document );
}

const kvs::kvsml::KVSMLTag StructuredVolumeObjectParser::KVSMLTag( void ) const
{
    return( m_kvsml_tag );
}

const kvs::kvsml::ObjectTag StructuredVolumeObjectParser::objectTag( void ) const
{
    return( m_object_tag );
}

const std::string& StructuredVolumeObjectParser::gridType( void ) const
{
    return( m_grid_type );
}

const kvs::Vector3ui& StructuredVolumeObjectParser::resolution ( void ) const
{
    return( m_resolution );
}

const size_t StructuredVolumeObjectParser::veclen( void ) const
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

bool StructuredVolumeObjectParser::parse( const kvs::XMLDocument& document )
{
    return( this->parse( &document ) );
}

bool StructuredVolumeObjectParser::parse( const kvs::XMLDocument* document )
{
    // <KVSML>
    if ( !m_kvsml_tag.read( document ) )
    {
        kvsMessageError("Cannot find <KVSML>.");
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
        kvsMessageError("Cannot find <Object>.");
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
    const std::string object_type = m_object_tag.type();
    if( object_type != "StructuredVolumeObject" )
    {
        kvsMessageError("This file type is not a uniform volume object.");
        return( false );
    }
/*
    TiXmlElement* object_element = kvs::TagParser::NodeToElement( object_node );
    std::string object_type = kvs::TagParser::GetAttributeValue( object_element, "type" );
    if( object_type != "StructuredVolumeObject" )
    {
        kvsMessageError("This file type is not a uniform volume object.");
        return( false );
    }
*/

    // <StructuredVolumeObject>
//    m_volume_object_node = kvs::TagParser::FindChildNode( object_node, object_type );
    m_volume_object_node = kvs::XMLNode::FindChildNode( m_object_tag.node(), object_type );
    if( !m_volume_object_node )
    {
        kvsMessageError("Cannot find <%s>.",object_type.c_str());
        return( false );
    }

    // <StructuredVolumeObject resolution="xxx" grid_type="xxx">
//    TiXmlElement* volume_element = kvs::TagParser::NodeToElement( m_volume_object_node );
    TiXmlElement* volume_element = kvs::XMLNode::ToElement( m_volume_object_node );
    if( !this->parse_resolution( volume_element ) ) return( false );
    if( !this->parse_grid_type( volume_element ) )  return( false );

    // <Node>
//    m_node_node = kvs::TagParser::FindChildNode( m_volume_object_node, "Node" );
    m_node_node = kvs::XMLNode::FindChildNode( m_volume_object_node, "Node" );
    if( !m_node_node )
    {
        kvsMessageError("Cannot find <Node>.");
        return( false );
    }

    return( true );
}

void StructuredVolumeObjectParser::setValuesTo( kvs::AnyValueArray* values )
{
    const size_t nnodes = m_resolution.x() * m_resolution.y() * m_resolution.z();
    kvs::ValueTagParser( nnodes ).parse( m_node_node, values );
}

/*==========================================================================*/
/**
 *  Set the coordinate array to the given array.
 *  @param  coords [out] coordinate array
 */
/*==========================================================================*/
void StructuredVolumeObjectParser::setCoordsTo( kvs::ValueArray<kvs::Real32>* coords )
{
    const size_t nnodes = m_resolution.x() * m_resolution.y() * m_resolution.z();
    kvs::CoordTagParser( nnodes ).parse( m_node_node, coords );
}

bool StructuredVolumeObjectParser::parse_resolution( const TiXmlElement* element )
{
    std::string resolution = kvs::TagParser::GetAttributeValue( element, "resolution" );
    if( resolution == "" )
    {
        kvsMessageError("Cannot find 'resolution' in <StructuredVolume>.");
        return( false );
    }

    const std::string delim(" \n");
    kvs::Tokenizer t( resolution, delim );

    m_resolution.set( 1, 1, 1 );
    for( int i = 0; i < 3; i++ )
    {
        m_resolution[i] = atoi( t.token().c_str() );
    }

    return( true );

}

/*==========================================================================*/
/**
 *  Parse the grid type.
 *  @param element [in] pointer to the element
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool StructuredVolumeObjectParser::parse_grid_type( const TiXmlElement* element )
{
    m_grid_type = kvs::TagParser::GetAttributeValue( element, "normal_type" );
    if( m_grid_type == "" ) m_grid_type = "uniform";

    if( m_grid_type == "uniform"     ) return( true );
    if( m_grid_type == "rectilinear" ) return( true );
    if( m_grid_type == "curvilinear" ) return( true );

    return( false );
}

const bool StructuredVolumeObjectParser::Check( const kvs::XMLDocument& document )
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
    if( object_type != "StructuredVolumeObject" ) return( false );

    // <StructuredVolumeObject>
    TiXmlNode* structured_volume_object_node = kvs::TagParser::FindChildNode( object_node, object_type );
    if( !structured_volume_object_node ) return( false );

    return( true );
}

} // end of namesapce kvs
