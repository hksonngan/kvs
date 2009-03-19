/****************************************************************************/
/**
 *  @file LineObjectParser.cpp
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
#include "LineObjectParser.h"
#include "TagParser.h"
#include "CoordTagParser.h"
#include "ColorTagParser.h"
#include "ConnectionTagParser.h"
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
LineObjectParser::LineObjectParser( void ):
    m_line_type( "" ),
    m_color_type( "" ),
    m_nvertices( 0 ),
    m_nlines( 0 ),
    m_line_object_node( NULL ),
    m_vertex_node( NULL )
{
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param document [in] reference to the XML document
 */
/*==========================================================================*/
LineObjectParser::LineObjectParser( const kvs::XMLDocument& document )
{
    this->parse( document );
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param document [in] pointer to the XML document
 */
/*==========================================================================*/
LineObjectParser::LineObjectParser( const kvs::XMLDocument* document )
{
    this->parse( document );
}

const kvs::kvsml::KVSMLTag LineObjectParser::KVSMLTag( void ) const
{
    return( m_kvsml_tag );
}

const kvs::kvsml::ObjectTag LineObjectParser::objectTag( void ) const
{
    return( m_object_tag );
}

/*==========================================================================*/
/**
 *  Get the name of the line type.
 */
/*==========================================================================*/
const std::string& LineObjectParser::lineType( void ) const
{
    return( m_line_type );
}

/*==========================================================================*/
/**
 *  Get the name of the color type.
 */
/*==========================================================================*/
const std::string& LineObjectParser::colorType( void ) const
{
    return( m_color_type );
}

/*==========================================================================*/
/**
 *  Get the number of vertices.
 *  @return number of vertices
 */
/*==========================================================================*/
const size_t LineObjectParser::nvertices( void ) const
{
    return( m_nvertices );
}

/*==========================================================================*/
/**
 *  Get the number of lines (connections).
 *  @return number of connections
 */
/*==========================================================================*/
const size_t LineObjectParser::nlines( void ) const
{
    return( m_nlines );
}

/*==========================================================================*/
/**
 *  Parse the line object node.
 *  @param document [in] reference to the XML document
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool LineObjectParser::parse( const kvs::XMLDocument& document )
{
    return( this->parse( &document ) );
}

/*==========================================================================*/
/**
 *  Parse the line object.
 *  @param document [in] pointer to the XML document
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool LineObjectParser::parse( const kvs::XMLDocument* document )
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
    if( object_type != "LineObject" )
    {
        kvsMessageError("This file type is not a line object.");
        return( false );
    }
/*
    TiXmlElement* object_element = kvs::TagParser::NodeToElement( object_node );
    std::string object_type = kvs::TagParser::GetAttributeValue( object_element, "type" );
    if( object_type != "LineObject" )
    {
        kvsMessageError("This file type is not a line object.");
        return( false );
    }
*/

    // <LineObject>
//    m_line_object_node = kvs::TagParser::FindChildNode( object_node, object_type );
    m_line_object_node = kvs::XMLNode::FindChildNode( m_object_tag.node(), object_type );
    if( !m_line_object_node )
    {
        kvsMessageError("Cannot find <%s>.",object_type.c_str());
        return( false );
    }

    // <LineObject line_type="xxx" color_type="xxx">
//    TiXmlElement* line_object_element = kvs::TagParser::NodeToElement( m_line_object_node );
    TiXmlElement* line_object_element = kvs::XMLNode::ToElement( m_line_object_node );
    // Firstly, it is necessary to parse the types of line.
    if( !this->parse_line_type( line_object_element ) )  return( false );
    if( !this->parse_color_type( line_object_element ) ) return( false );

    // <Vertex>
//    m_vertex_node = kvs::TagParser::FindChildNode( m_line_object_node, "Vertex" );
    m_vertex_node = kvs::XMLNode::FindChildNode( m_line_object_node, "Vertex" );
    if( !m_vertex_node )
    {
        kvsMessageError("Cannot find <Vertex>.");
        return( false );
    }

    // <Vertex nvertices="xxx">
//    TiXmlElement* vertex_element = kvs::TagParser::NodeToElement( m_vertex_node );
    TiXmlElement* vertex_element = kvs::XMLNode::ToElement( m_vertex_node );
    if( !this->parse_nvertices( vertex_element ) ) return( false );

    // <Line>
//    m_line_node = kvs::TagParser::FindChildNode( m_line_object_node, "Line" );
    m_line_node = kvs::XMLNode::FindChildNode( m_line_object_node, "Line" );
    if( !m_line_node )
    {
        kvsMessageError("Cannot find <Line>.");
        return( false );
    }

    // <Line nlines="x">
//    TiXmlElement* line_element = kvs::TagParser::NodeToElement( m_line_node );
    TiXmlElement* line_element = kvs::XMLNode::ToElement( m_line_node );
    if( !line_element )
    {
        kvsMessageError("Cannot read <Line>.");
        return( false );
    }

    if( !this->parse_nlines( line_element ) ) return( false );

    return( true );
}

/*==========================================================================*/
/**
 *  Set the coordinate array to the given array.
 *  @param coords [in] coordinate array
 */
/*==========================================================================*/
void LineObjectParser::setCoordsTo( kvs::ValueArray<kvs::Real32>* coords )
{
    kvs::CoordTagParser( m_nvertices ).parse( m_vertex_node, coords );
}

/*==========================================================================*/
/**
 *  Set the connection array to the given array.
 *  @param connections [in] connection array
 */
/*==========================================================================*/
void LineObjectParser::setConnectionsTo( kvs::ValueArray<kvs::UInt32>* connections )
{
    size_t nindices = 0;
    if(      m_line_type == "uniline" ) nindices = m_nlines;
    else if( m_line_type == "polyline") nindices = m_nlines * 2;
    else if( m_line_type == "segment" ) nindices = m_nlines * 2;

    kvs::ConnectionTagParser( nindices ).parse( m_line_node, connections );
}

/*==========================================================================*/
/**
 *  Set the color array to the given array.
 *  @param colors [in] color array
 */
/*==========================================================================*/
void LineObjectParser::setColorsTo( kvs::ValueArray<kvs::UInt8>* colors )
{
    size_t ncolors = m_nvertices;
    if( m_color_type == "line_color" )
    {
        if(      m_line_type == "strip"   ) ncolors = m_nvertices - 1;
        else if( m_line_type == "uniline" ) ncolors = m_nlines - 1;
        else if( m_line_type == "polyline") ncolors = m_nlines;
        else if( m_line_type == "segment" ) ncolors = m_nlines;

        kvs::ColorTagParser( ncolors ).parse( m_line_node, colors );
    }
    else
    {
        kvs::ColorTagParser( ncolors ).parse( m_vertex_node, colors );
    }
}

/*==========================================================================*/
/**
 *  Set the size array to the given array.
 *  @param sizes [in] size array
 */
/*==========================================================================*/
void LineObjectParser::setSizesTo( kvs::ValueArray<kvs::Real32>* sizes )
{
    kvs::SizeTagParser( m_nvertices ).parse( m_vertex_node, sizes );
}

/*==========================================================================*/
/**
 *  Parse the line type.
 *  @param element [in] pointer to the element
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool LineObjectParser::parse_line_type( const TiXmlElement* element )
{
    m_line_type = kvs::TagParser::GetAttributeValue( element, "line_type" );
    if( m_line_type == "" ) m_line_type = "strip";

    if( m_line_type == "strip"    ) return( true );
    if( m_line_type == "uniline"  ) return( true );
    if( m_line_type == "polyline" ) return( true );
    if( m_line_type == "segment"  ) return( true );

    kvsMessageError( "Unknown line type '%s'.", m_line_type.c_str() );

    return( false );
}

/*==========================================================================*/
/**
 *  Parse the color type.
 *  @param element [in] pointer to the element
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool LineObjectParser::parse_color_type( const TiXmlElement* element )
{
    m_color_type = kvs::TagParser::GetAttributeValue( element, "color_type" );
    if( m_color_type == "" ) m_color_type = "line";

    if( m_color_type == "line"    ) return( true );
    if( m_color_type == "vertex"  ) return( true );

    kvsMessageError( "Unknown color type '%s'.", m_color_type.c_str() );

    return( false );
}

/*==========================================================================*/
/**
 *  Parse the number of vertices.
 *  @param element [in] pointer to the element
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool LineObjectParser::parse_nvertices( const TiXmlElement* element )
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

/*==========================================================================*/
/**
 *  Parse the number of lines (connections).
 *  @param element [in] pointer to the element
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool LineObjectParser::parse_nlines( const TiXmlElement* element )
{
    std::string nlines = kvs::TagParser::GetAttributeValue( element, "nlines" );
    if( nlines == "" )
    {
        m_nlines = 0; // in the case of 'strip'

        if( m_line_type != "strip" ) return( false );
    }
    else
    {
        m_nlines = atoi( nlines.c_str() );
    }

    return( true );
}

const bool LineObjectParser::Check( const kvs::XMLDocument& document )
{
    // <KVSML>
    TiXmlNode* kvsml_node = kvs::TagParser::FindNode( &document, "KVSML" );
    if( !kvsml_node ) return( false );

    // <Object>
    TiXmlNode* object_node = kvs::TagParser::FindChildNode( kvsml_node, "Object" );
    if( !object_node ) return( false );

    // <Object type="xxx">
    TiXmlElement* object_element = kvs::TagParser::NodeToElement( object_node );
    std::string object_type = kvs::TagParser::GetAttributeValue( object_element, "type" );
    if( object_type != "LineObject" ) return( false );

    // <LineObject>
    TiXmlNode* line_object_node = kvs::TagParser::FindChildNode( object_node, object_type );
    if( !line_object_node ) return( false );

    return( true );
}

} // end of namespace kvs
