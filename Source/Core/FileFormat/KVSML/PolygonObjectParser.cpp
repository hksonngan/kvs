/****************************************************************************/
/**
 *  @file PolygonObjectParser.cpp
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
#include "PolygonObjectParser.h"
#include "TagParser.h"
#include "CoordTagParser.h"
#include "ColorTagParser.h"
#include "NormalTagParser.h"
#include "ConnectionTagParser.h"
#include "OpacityTagParser.h"
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
PolygonObjectParser::PolygonObjectParser( void ):
    m_polygon_type( "" ),
    m_color_type( "" ),
    m_normal_type( "" ),
    m_nvertices( 0 ),
    m_npolygons( 0 ),
    m_polygon_object_node( NULL ),
    m_vertex_node( NULL )
{
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param document [in] reference to the XML document
 */
/*==========================================================================*/
PolygonObjectParser::PolygonObjectParser( const kvs::XMLDocument& document )
{
    this->parse( document );
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param document [in] pointer to the XML document
 */
/*==========================================================================*/
PolygonObjectParser::PolygonObjectParser( const kvs::XMLDocument* document )
{
    this->parse( document );
}

const kvs::kvsml::KVSMLTag PolygonObjectParser::KVSMLTag( void ) const
{
    return( m_kvsml_tag );
}

const kvs::kvsml::ObjectTag PolygonObjectParser::objectTag( void ) const
{
    return( m_object_tag );
}

/*==========================================================================*/
/**
 *  Get the polygon type.
 *  @return polygon type
 */
/*==========================================================================*/
const std::string& PolygonObjectParser::polygonType( void ) const
{
    return( m_polygon_type );
}

/*==========================================================================*/
/**
 *  Get the color type.
 *  @return color type
 */
/*==========================================================================*/
const std::string& PolygonObjectParser::colorType( void ) const
{
    return( m_color_type );
}

/*==========================================================================*/
/**
 *  Get the normal type.
 *  @return normal type
 */
/*==========================================================================*/
const std::string& PolygonObjectParser::normalType( void ) const
{
    return( m_normal_type );
}

/*==========================================================================*/
/**
 *  Get the number of vertices.
 *  @return number of vertices
 */
/*==========================================================================*/
const size_t PolygonObjectParser::nvertices( void ) const
{
    return( m_nvertices );
}

/*==========================================================================*/
/**
 *  Get the number of polygons (connection).
 *  @return number of connection
 */
/*==========================================================================*/
const size_t PolygonObjectParser::npolygons( void ) const
{
    return( m_npolygons );
}

/*==========================================================================*/
/**
 *  Parse the polygon object node.
 *  @param document [in] reference to the XML document
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool PolygonObjectParser::parse( const kvs::XMLDocument& document )
{
    return( this->parse( &document ) );
}

/*==========================================================================*/
/**
 *  Parse the point object.
 *  @param document [in] pointer to the XML document
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool PolygonObjectParser::parse( const kvs::XMLDocument* document )
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
    if( object_type != "PolygonObject" )
    {
        kvsMessageError("This file type is not a polygon object.");
        return( false );
    }
/*
    TiXmlElement* object_element = kvs::TagParser::NodeToElement( object_node );
    std::string object_type = kvs::TagParser::GetAttributeValue( object_element, "type" );
    if( object_type != "PolygonObject" )
    {
        kvsMessageError("This file type is not a polygon object.");
        return( false );
    }
*/

    // <PolygonObject>
//    m_polygon_object_node = kvs::TagParser::FindChildNode( object_node, object_type );
    m_polygon_object_node = kvs::XMLNode::FindChildNode( m_object_tag.node(), object_type );
    if( !m_polygon_object_node )
    {
        kvsMessageError("Cannot find <%s>.",object_type.c_str());
        return( false );
    }

    // <PolygonObject polygon_type="xxx" color_type="xxx" normal_type="xxx">
//    TiXmlElement* polygon_object_element = kvs::TagParser::NodeToElement( m_polygon_object_node );
    TiXmlElement* polygon_object_element = kvs::XMLNode::ToElement( m_polygon_object_node );
    // Firstly, it is necessary to parse the types of polygon.
    if( !this->parse_polygon_type( polygon_object_element ) ) return( false );
    if( !this->parse_color_type( polygon_object_element ) )   return( false );
    if( !this->parse_normal_type( polygon_object_element ) )  return( false );

    // <Vertex>
//    m_vertex_node = kvs::TagParser::FindChildNode( m_polygon_object_node, "Vertex" );
    m_vertex_node = kvs::XMLNode::FindChildNode( m_polygon_object_node, "Vertex" );
    if( !m_vertex_node )
    {
        kvsMessageError("Cannot find <Vertex>.");
        return( false );
    }

    // <Vertex nvertices="xxx">
//    TiXmlElement* vertex_element = kvs::TagParser::NodeToElement( m_vertex_node );
    TiXmlElement* vertex_element = kvs::XMLNode::ToElement( m_vertex_node );
    if( !this->parse_nvertices( vertex_element ) ) return( false );

    // <Polygon>
//    m_polygon_node = kvs::TagParser::FindChildNode( m_polygon_object_node, "Polygon" );
    m_polygon_node = kvs::XMLNode::FindChildNode( m_polygon_object_node, "Polygon" );
    if( !m_polygon_node )
    {
        kvsMessageError("Cannot find <Polygon>.");
        return( false );
    }

    // <Polygon npolygons="x">
//    TiXmlElement* polygon_element = kvs::TagParser::NodeToElement( m_polygon_node );
    TiXmlElement* polygon_element = kvs::XMLNode::ToElement( m_polygon_node );
    if( !polygon_element )
    {
        kvsMessageError("Cannot read <Polygon>.");
        return( false );
    }
    if( !this->parse_npolygons( polygon_element ) ) return( false );

    return( true );
}

/*==========================================================================*/
/**
 *  Set the coordinate array to the given array.
 *  @param  coords [out] coordinate array
 */
/*==========================================================================*/
void PolygonObjectParser::setCoordsTo( kvs::ValueArray<kvs::Real32>* coords )
{
    kvs::CoordTagParser( m_nvertices ).parse( m_vertex_node, coords );
}

/*==========================================================================*/
/**
 *  Set the connection array to the given array.
 *  @param  connections [out] connection array
 */
/*==========================================================================*/
void PolygonObjectParser::setConnectionsTo( kvs::ValueArray<kvs::UInt32>* connections )
{
    size_t nindices = 0;
    if(      m_polygon_type == "triangle"  ) nindices = m_npolygons * 3;
    else if( m_polygon_type == "quadrangle") nindices = m_npolygons * 4;

    kvs::ConnectionTagParser( nindices ).parse( m_polygon_node, connections );
}

/*==========================================================================*/
/**
 *  Set the normal array to the given array.
 *  @param  normals [out] normal array
 */
/*==========================================================================*/
void PolygonObjectParser::setNormalsTo( kvs::ValueArray<kvs::Real32>* normals )
{
    size_t nnormals = m_nvertices; // vertex
    if( m_normal_type == "polygon" )
    {
        nnormals = m_npolygons;
        kvs::NormalTagParser( nnormals ).parse( m_polygon_node, normals );
    }
    else
    {
        kvs::NormalTagParser( nnormals ).parse( m_vertex_node, normals );
    }
}

/*==========================================================================*/
/**
 *  Set the color array to the given array.
 *  @param  colors [out] color array
 */
/*==========================================================================*/
void PolygonObjectParser::setColorsTo( kvs::ValueArray<kvs::UInt8>* colors )
{
    size_t ncolors = m_nvertices; // vertex_color
    if( m_color_type == "polygon" )
    {
        ncolors = m_npolygons;

        kvs::ColorTagParser( ncolors ).parse( m_vertex_node, colors );
    }
    else
    {
        kvs::ColorTagParser( ncolors ).parse( m_vertex_node, colors );
    }
}

/*==========================================================================*/
/**
 *  Set the opacity array to the given array.
 *  @param opacities [in] opacity array
 */
/*==========================================================================*/
void PolygonObjectParser::setOpacitiesTo( kvs::ValueArray<kvs::UInt8>* opacities )
{
    kvs::OpacityTagParser( m_nvertices ).parse( m_vertex_node, opacities );
}

/*==========================================================================*/
/**
 *  Parse the polygon type.
 *  @param element [in] pointer to the element
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool PolygonObjectParser::parse_polygon_type( const TiXmlElement* element )
{
    m_polygon_type = kvs::TagParser::GetAttributeValue( element, "polygon_type" );
    if( m_polygon_type == "" ) m_polygon_type = "triangle";

    if( m_polygon_type == "triangle"   ) return( true );
    if( m_polygon_type == "quadrangle" ) return( true );

    kvsMessageError( "Unknown polygon type '%s'.", m_polygon_type.c_str() );

    return( false );
}

/*==========================================================================*/
/**
 *  Parse the color type.
 *  @param element [in] pointer to the element
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool PolygonObjectParser::parse_color_type( const TiXmlElement* element )
{
    m_color_type = kvs::TagParser::GetAttributeValue( element, "color_type" );
    if( m_color_type == "" ) m_color_type = "polygon";

    if( m_color_type == "polygon"    ) return( true );
    if( m_color_type == "vertex"  ) return( true );

    kvsMessageError( "Unknown color type '%s'.", m_color_type.c_str() );

    return( false );
}

/*==========================================================================*/
/**
 *  Parse the normal type.
 *  @param element [in] pointer to the element
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool PolygonObjectParser::parse_normal_type( const TiXmlElement* element )
{
    m_normal_type = kvs::TagParser::GetAttributeValue( element, "normal_type" );
    if( m_normal_type == "" ) m_normal_type = "polygon";

    if( m_normal_type == "polygon"    ) return( true );
    if( m_normal_type == "vertex"  ) return( true );

    kvsMessageError( "Unknown normal type '%s'.", m_normal_type.c_str() );

    return( false );
}

/*==========================================================================*/
/**
 *  Parse the number of vertices.
 *  @param element [in] pointer to the element
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool PolygonObjectParser::parse_nvertices( const TiXmlElement* element )
{
    std::string nvertices = kvs::TagParser::GetAttributeValue( element, "nvertices" );
    if( nvertices == "" )
    {
        kvsMessageError("Cannot find 'nvertices' in <Point>.");
        return( false );
    }

    m_nvertices = atoi( nvertices.c_str() );

    return( true );
}

/*==========================================================================*/
/**
 *  Parse the number of polygons (connections).
 *  @param element [in] pointer to the element
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool PolygonObjectParser::parse_npolygons( const TiXmlElement* element )
{
    std::string npolygons = kvs::TagParser::GetAttributeValue( element, "npolygons" );
    if( npolygons == "" )
    {
        kvsMessageError("Cannot find 'npolygons' in <Polygon>.");
        return( false );
    }

    m_npolygons = atoi( npolygons.c_str() );

    return( true );
}

const bool PolygonObjectParser::Check( const kvs::XMLDocument& document )
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
    if( object_type != "PolygonObject" ) return( false );

    // <PolygonObject>
    TiXmlNode* polygon_object_node = kvs::TagParser::FindChildNode( object_node, object_type );
    if( !polygon_object_node ) return( false );

    return( true );
}

} // end of namespace kvs
