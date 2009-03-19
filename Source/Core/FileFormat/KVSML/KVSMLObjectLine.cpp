/****************************************************************************/
/**
 *  @file KVSMLObjectLine.cpp
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
#include "KVSMLObjectLine.h"
#include "LineObjectParser.h"
#include "TagParser.h"
#include <kvs/File>
#include <kvs/XMLDocument>
#include <kvs/XMLDeclaration>
#include <kvs/XMLElement>
#include <kvs/XMLComment>
#include <kvs/IgnoreUnusedVariable>


namespace kvs
{

KVSMLObjectLine::KVSMLObjectLine( void ):
    m_has_external_coord( false ),
    m_min_external_coord( -3.0f, -3.0f, -3.0f ),
    m_max_external_coord(  3.0f,  3.0f,  3.0f ),
    m_has_object_coord( false ),
    m_min_object_coord( -3.0f, -3.0f, -3.0f ),
    m_max_object_coord(  3.0f,  3.0f,  3.0f ),
    m_writing_type( kvs::KVSMLObjectLine::Ascii )
{
}

KVSMLObjectLine::KVSMLObjectLine( const std::string& filename ):
    m_has_external_coord( false ),
    m_min_external_coord( -3.0f, -3.0f, -3.0f ),
    m_max_external_coord(  3.0f,  3.0f,  3.0f ),
    m_has_object_coord( false ),
    m_min_object_coord( -3.0f, -3.0f, -3.0f ),
    m_max_object_coord(  3.0f,  3.0f,  3.0f ),
    m_writing_type( kvs::KVSMLObjectLine::Ascii )
{
    if( this->read( filename ) )
    {
        m_is_success = true;
    }
    else
    {
        m_is_success = false;
    }
}

KVSMLObjectLine::~KVSMLObjectLine( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns a flag to check whether 'external_coord' is specified or not.
 *  @return true, if 'external_coord' is specified
 */
/*===========================================================================*/
const bool KVSMLObjectLine::hasExternalCoord( void ) const
{
    return( m_has_external_coord );
}

/*===========================================================================*/
/**
 *  @brief  Returns a min. external coordinate.
 *  @return min. external coordinate
 */
/*===========================================================================*/
const kvs::Vector3f& KVSMLObjectLine::minExternalCoord( void ) const
{
    return( m_min_external_coord );
}

/*===========================================================================*/
/**
 *  @brief  Returns a max. external coordinate.
 *  @return max. external coordinate
 */
/*===========================================================================*/
const kvs::Vector3f& KVSMLObjectLine::maxExternalCoord( void ) const
{
    return( m_max_external_coord );
}

/*===========================================================================*/
/**
 *  @brief  Returns a flag to check whether 'object_coord' is specified or not.
 *  @return true, if 'object_coord' is specified
 */
/*===========================================================================*/
const bool KVSMLObjectLine::hasObjectCoord( void ) const
{
    return( m_has_object_coord );
}

/*===========================================================================*/
/**
 *  @brief  Returns a min. object coordinate.
 *  @return min. object coordinate
 */
/*===========================================================================*/
const kvs::Vector3f& KVSMLObjectLine::minObjectCoord( void ) const
{
    return( m_min_object_coord );
}

/*===========================================================================*/
/**
 *  @brief  Returns a max. object coordinate.
 *  @return max. object coordinate
 */
/*===========================================================================*/
const kvs::Vector3f& KVSMLObjectLine::maxObjectCoord( void ) const
{
    return( m_max_object_coord );
}

const std::string& KVSMLObjectLine::lineType( void ) const
{
    return( m_line_type );
}

const std::string& KVSMLObjectLine::colorType( void ) const
{
    return( m_color_type );
}

const kvs::ValueArray<kvs::Real32>& KVSMLObjectLine::coords( void ) const
{
    return( m_coords );
}

const kvs::ValueArray<kvs::UInt8>& KVSMLObjectLine::colors( void ) const
{
    return( m_colors );
}

const kvs::ValueArray<kvs::UInt32>& KVSMLObjectLine::connections( void ) const
{
    return( m_connections );
}

const kvs::ValueArray<kvs::Real32>& KVSMLObjectLine::sizes( void ) const
{
    return( m_sizes );
}

void KVSMLObjectLine::setWritingDataType( const WritingDataType writing_type )
{
    m_writing_type = writing_type;
}

void KVSMLObjectLine::setLineType( const std::string& line_type )
{
    m_line_type = line_type;
}

void KVSMLObjectLine::setColorType( const std::string& color_type )
{
    m_color_type = color_type;
}

void KVSMLObjectLine::setCoords( const kvs::ValueArray<kvs::Real32>& coords )
{
    m_coords = coords;
}

void KVSMLObjectLine::setColors( const kvs::ValueArray<kvs::UInt8>& colors )
{
    m_colors = colors;
}

void KVSMLObjectLine::setConnections( const kvs::ValueArray<kvs::UInt32>& connections )
{
    m_connections = connections;
}

void KVSMLObjectLine::setSizes( const kvs::ValueArray<kvs::Real32>& sizes )
{
    m_sizes = sizes;
}

const bool KVSMLObjectLine::read( const std::string& filename )
{
    m_filename = filename;

    kvs::XMLDocument document;
    if ( !document.read( filename ) )
    {
        kvsMessageError( "%s", document.ErrorDesc().c_str() );
        return( false );
    }

    kvs::LineObjectParser parser;
    if ( !parser.parse( document ) )
    {
        kvsMessageError("'%s' is invalid KVSML document.", filename.c_str());
        return( false );
    }

    m_line_type  = parser.lineType();
    m_color_type = parser.colorType();

    parser.setCoordsTo( &m_coords );
    parser.setColorsTo( &m_colors );
    parser.setConnectionsTo( &m_connections );
    parser.setSizesTo( &m_sizes );

    return( true );
}

const bool KVSMLObjectLine::write( const std::string& filename )
{
    m_filename = filename;

    kvs::XMLDocument doc;
    doc.InsertEndChild( kvs::XMLDeclaration("1.0") );
    doc.InsertEndChild( kvs::XMLComment(" Generated by kvs::KVSMLObjectLine::write() ") );

    // <KVSML>
    TiXmlNode* kvs_node = doc.InsertEndChild( kvs::XMLElement("KVSML") );

    // <Object type="LineObject">
    kvs::XMLElement obj_elem("Object");
    obj_elem.setAttribute("type","LineObject");
    TiXmlNode* obj_node = kvs_node->InsertEndChild( obj_elem );

    // <LineObject>
    kvs::XMLElement line_elem("LineObject");
    line_elem.setAttribute("line_type",m_line_type);
    line_elem.setAttribute("color_type",m_color_type);
    TiXmlNode* line_node = obj_node->InsertEndChild( line_elem );

    // <Vertex nvertices="xxx">
    kvs::XMLElement vertex_elem("Vertex");
    vertex_elem.setAttribute("nvertices", m_coords.size() / 3 );
    TiXmlNode* vertex_node = line_node->InsertEndChild( vertex_elem );

    // Writing data type.
    const kvs::TagParser::WritingDataType writing_type =
        static_cast<kvs::TagParser::WritingDataType>( m_writing_type );

    // <Coord>
    if ( m_coords.size() > 0 )
    {
        kvs::XMLElement coord_elem("Coord");
        TiXmlNode* coord_node = vertex_node->InsertEndChild( coord_elem );
        const std::string coord_file = kvs::TagParser::GetDataFilename( m_filename, "coord" );
        if ( !kvs::TagParser::ComposeArray( coord_node, writing_type, m_coords, 3, coord_file ) )
        {
            kvsMessageError("Cannot compose the data array for <Coord>.");
            return( false );
        }
    }

    // <Color>
    if ( m_colors.size() > 0 )
    {
        kvs::XMLElement color_elem("Color");
        TiXmlNode* color_node = vertex_node->InsertEndChild( color_elem );
        const std::string color_file = kvs::TagParser::GetDataFilename( m_filename, "color" );
        if ( !kvs::TagParser::ComposeArray( color_node, writing_type, m_colors, 3, color_file ) )
        {
            kvsMessageError("Cannot compose the data array for <Color>.");
            return( false );
        }
    }

    // <Size>
    if ( m_sizes.size() > 0 )
    {
        kvs::XMLElement size_elem("Size");
        TiXmlNode* size_node = vertex_node->InsertEndChild( size_elem );
        const std::string size_file = kvs::TagParser::GetDataFilename( m_filename, "size" );
        if ( !kvs::TagParser::ComposeArray( size_node, writing_type, m_sizes, 1, size_file ) )
        {
            kvsMessageError("Cannot compose the data array for <Size>.");
            return( false );
        }
    }

    // <Line>
    kvs::XMLElement line_connect_elem("Line");
    const size_t nlines = m_line_type == "uniline" ? m_connections.size() : m_connections.size() / 2;
    line_connect_elem.setAttribute("nlines", nlines );
    TiXmlNode* line_connect_node = line_node->InsertEndChild( line_connect_elem );

    // <Connection>
    if ( m_connections.size() > 0 )
    {
        kvs::XMLElement connect_elem("Connection");
        TiXmlNode* connect_node = line_connect_node->InsertEndChild( connect_elem );
        const std::string connect_file = kvs::TagParser::GetDataFilename( m_filename, "connect" );
        if ( !kvs::TagParser::ComposeArray( connect_node, writing_type, m_connections, 1, connect_file ) )
        {
            kvsMessageError("Cannot compose the data array for <Connection>.");
            return( false );
        }
    }

    return( doc.write( m_filename ) );
}

const bool KVSMLObjectLine::CheckFileExtension( const std::string& filename )
{
    const kvs::File file( filename );
    if ( file.extension() == "kvsml" || file.extension() == "KVSML" ||
         file.extension() == "xml"   || file.extension() == "XML" )
    {
        return( true );
    }

    return( false );
}

const bool KVSMLObjectLine::CheckFileFormat( const std::string& filename )
{
    kvs::XMLDocument document;
    if ( document.read( filename ) )
    {
        if ( kvs::LineObjectParser::Check( document ) )
        {
            return( true );
        }
    }

    return( false );
}

std::ostream& operator <<( std::ostream& os, const KVSMLObjectLine& rhs )
{
    os << "Line type:  "       << rhs.m_line_type << std::endl;
    os << "Color type: "       << rhs.m_color_type << std::endl;
    os << "Num. of vertices: " << rhs.m_coords.size() / 3 << std::endl;

    return( os );
}

} // end of namespace kvs
