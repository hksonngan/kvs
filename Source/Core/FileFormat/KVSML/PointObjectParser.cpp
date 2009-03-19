/****************************************************************************/
/**
 *  @file PointObjectParser.cpp
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
#include "PointObjectParser.h"
#include "TagParser.h"
#include "CoordTagParser.h"
#include "ColorTagParser.h"
#include "NormalTagParser.h"
#include "SizeTagParser.h"
#include <kvs/ValueArray>
#include <kvs/XMLDocument>
#include <kvs/Message>
#include <kvs/Type>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
PointObjectParser::PointObjectParser( void ):
    m_nvertices( 0 ),
    m_point_object_node( NULL )
{
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param document [in] reference to the XML document
 */
/*==========================================================================*/
PointObjectParser::PointObjectParser( const kvs::XMLDocument& document )
{
    this->parse( document );
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param document [in] pointer to the XML document
 */
/*==========================================================================*/
PointObjectParser::PointObjectParser( const kvs::XMLDocument* document )
{
    this->parse( document );
}

const kvs::kvsml::KVSMLTag PointObjectParser::KVSMLTag( void ) const
{
    return( m_kvsml_tag );
}

const kvs::kvsml::ObjectTag PointObjectParser::objectTag( void ) const
{
    return( m_object_tag );
}

/*==========================================================================*/
/**
 *  Get the number of vertices.
 *  @return number of vertices
 */
/*==========================================================================*/
const size_t PointObjectParser::nvertices( void ) const
{
    return( m_nvertices );
}

/*==========================================================================*/
/**
 *  Parse the point object node.
 *  @param document [in] reference to the XML document
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool PointObjectParser::parse( const kvs::XMLDocument& document )
{
    return( this->parse( &document ) );
}

/*==========================================================================*/
/**
 *  Parse the point object node.
 *  @param document [in] pointer to the XML document
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool PointObjectParser::parse( const kvs::XMLDocument* document )
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
    if( object_type != "PointObject" )
    {
        kvsMessageError("This file type is not a point object.");
        return( false );
    }
/*
    TiXmlElement* object_element = kvs::TagParser::NodeToElement( object_node );
    std::string object_type = kvs::TagParser::GetAttributeValue( object_element, "type" );
    if( object_type != "PointObject" )
    {
        kvsMessageError("This file type is not a point object.");
        return( false );
    }
*/

    // <PointObject>
//    m_point_object_node = kvs::TagParser::FindChildNode( object_node, object_type );
    m_point_object_node = kvs::XMLNode::FindChildNode( m_object_tag.node(), object_type );
    if( !m_point_object_node )
    {
        kvsMessageError("Cannot find <%s>.",object_type.c_str());
        return( false );
    }

    // <Vertex>
//    m_vertex_node = kvs::TagParser::FindChildNode( m_point_object_node, "Vertex" );
    m_vertex_node = kvs::XMLNode::FindChildNode( m_point_object_node, "Vertex" );
    if( !m_vertex_node )
    {
        kvsMessageError("Cannot find <Vertex>.");
        return( false );
    }

    // <Vertex nvertices="xxx">
//    TiXmlElement* vertex_element = kvs::TagParser::NodeToElement( m_vertex_node );
    TiXmlElement* vertex_element = kvs::XMLNode::ToElement( m_vertex_node );
    if( !this->parse_nvertices( vertex_element ) ) return( false );

    return( true );
}

/*==========================================================================*/
/**
 *  Set the coordinate array to the given array.
 *  @param  coords [out] pointer to coordinate array
 */
/*==========================================================================*/
void PointObjectParser::setCoordsTo( kvs::ValueArray<kvs::Real32>* coords )
{
    kvs::CoordTagParser( m_nvertices ).parse( m_vertex_node, coords );
}

/*==========================================================================*/
/**
 *  Set the color array to the given array.
 *  @param  colors [out] pointer to color array
 */
/*==========================================================================*/
void PointObjectParser::setColorsTo( kvs::ValueArray<kvs::UInt8>* colors )
{
    kvs::ColorTagParser( m_nvertices ).parse( m_vertex_node, colors );
}

/*==========================================================================*/
/**
 *  Set the normal array to the given array.
 *  @param  normals [out] pointer to normal array
 */
/*==========================================================================*/
void PointObjectParser::setNormalsTo( kvs::ValueArray<kvs::Real32>* normals )
{
    kvs::NormalTagParser( m_nvertices ).parse( m_vertex_node, normals );
}

/*==========================================================================*/
/**
 *  Set the size array to the given array.
 *  @param  colors [out] pointer to size array
 */
/*==========================================================================*/
void PointObjectParser::setSizesTo( kvs::ValueArray<kvs::Real32>* sizes )
{
    kvs::SizeTagParser( m_nvertices ).parse( m_vertex_node, sizes );
}

/*==========================================================================*/
/**
 *  Parse the number of vertices
 *  @param element [in] pointer to the element node
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool PointObjectParser::parse_nvertices( const TiXmlElement* element )
{
    std::string nvertices = kvs::TagParser::GetAttributeValue( element, "nvertices" );
    if( nvertices == "" )
    {
        kvsMessageError("Cannot find 'nvertices' in <Vertex>.");
        return( false );
    }

    m_nvertices = atoi( nvertices.c_str() );

    return( true );
}

const bool PointObjectParser::Check( const kvs::XMLDocument& document )
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
    if( object_type != "PointObject" ) return( false );

    // <PointObject>
    TiXmlNode* point_object_node = kvs::TagParser::FindChildNode( object_node, object_type );
    if( !point_object_node ) return( false );

    return( true );
}

} // end of namespace kvs
