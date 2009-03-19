/****************************************************************************/
/**
 *  @file KVSMLObjectPolygon.cpp
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
#include "KVSMLObjectPolygon.h"
#include "PolygonObjectParser.h"
#include "TagParser.h"
#include <kvs/File>
#include <kvs/XMLDocument>
#include <kvs/XMLDeclaration>
#include <kvs/XMLElement>
#include <kvs/XMLComment>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/IgnoreUnusedVariable>


namespace kvs
{

KVSMLObjectPolygon::KVSMLObjectPolygon( void ):
    m_has_external_coord( false ),
    m_min_external_coord( -3.0f, -3.0f, -3.0f ),
    m_max_external_coord(  3.0f,  3.0f,  3.0f ),
    m_has_object_coord( false ),
    m_min_object_coord( -3.0f, -3.0f, -3.0f ),
    m_max_object_coord(  3.0f,  3.0f,  3.0f ),
    m_writing_type( kvs::KVSMLObjectPolygon::Ascii )
{
}

KVSMLObjectPolygon::KVSMLObjectPolygon( const std::string& filename ):
    m_has_external_coord( false ),
    m_min_external_coord( -3.0f, -3.0f, -3.0f ),
    m_max_external_coord(  3.0f,  3.0f,  3.0f ),
    m_has_object_coord( false ),
    m_min_object_coord( -3.0f, -3.0f, -3.0f ),
    m_max_object_coord(  3.0f,  3.0f,  3.0f ),
    m_writing_type( kvs::KVSMLObjectPolygon::Ascii )
{
    if( this->read( filename ) ) { m_is_success = true; }
    else { m_is_success = false; }
}

KVSMLObjectPolygon::~KVSMLObjectPolygon( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns a flag to check whether 'external_coord' is specified or not.
 *  @return true, if 'external_coord' is specified
 */
/*===========================================================================*/
const bool KVSMLObjectPolygon::hasExternalCoord( void ) const
{
    return( m_has_external_coord );
}

/*===========================================================================*/
/**
 *  @brief  Returns a min. external coordinate.
 *  @return min. external coordinate
 */
/*===========================================================================*/
const kvs::Vector3f& KVSMLObjectPolygon::minExternalCoord( void ) const
{
    return( m_min_external_coord );
}

/*===========================================================================*/
/**
 *  @brief  Returns a max. external coordinate.
 *  @return max. external coordinate
 */
/*===========================================================================*/
const kvs::Vector3f& KVSMLObjectPolygon::maxExternalCoord( void ) const
{
    return( m_max_external_coord );
}

/*===========================================================================*/
/**
 *  @brief  Returns a flag to check whether 'object_coord' is specified or not.
 *  @return true, if 'object_coord' is specified
 */
/*===========================================================================*/
const bool KVSMLObjectPolygon::hasObjectCoord( void ) const
{
    return( m_has_object_coord );
}

/*===========================================================================*/
/**
 *  @brief  Returns a min. object coordinate.
 *  @return min. object coordinate
 */
/*===========================================================================*/
const kvs::Vector3f& KVSMLObjectPolygon::minObjectCoord( void ) const
{
    return( m_min_object_coord );
}

/*===========================================================================*/
/**
 *  @brief  Returns a max. object coordinate.
 *  @return max. object coordinate
 */
/*===========================================================================*/
const kvs::Vector3f& KVSMLObjectPolygon::maxObjectCoord( void ) const
{
    return( m_max_object_coord );
}

const std::string& KVSMLObjectPolygon::polygonType( void ) const
{
    return( m_polygon_type );
}

const std::string& KVSMLObjectPolygon::colorType( void ) const
{
    return( m_color_type );
}

const std::string& KVSMLObjectPolygon::normalType( void ) const
{
    return( m_normal_type );
}

const kvs::ValueArray<kvs::Real32>& KVSMLObjectPolygon::coords( void ) const
{
    return( m_coords );
}

const kvs::ValueArray<kvs::UInt32>& KVSMLObjectPolygon::connections( void ) const
{
    return( m_connections );
}

const kvs::ValueArray<kvs::UInt8>& KVSMLObjectPolygon::colors( void ) const
{
    return( m_colors );
}

const kvs::ValueArray<kvs::UInt8>& KVSMLObjectPolygon::opacities( void ) const
{
    return( m_opacities );
}

const kvs::ValueArray<kvs::Real32>& KVSMLObjectPolygon::normals( void ) const
{
    return( m_normals );
}

void KVSMLObjectPolygon::setWritingDataType( const WritingDataType writing_type )
{
    m_writing_type = writing_type;
}

void KVSMLObjectPolygon::setPolygonType( const std::string& polygon_type )
{
    m_polygon_type = polygon_type;
}

void KVSMLObjectPolygon::setColorType( const std::string& color_type )
{
    m_color_type = color_type;
}

void KVSMLObjectPolygon::setNormalType( const std::string& normal_type )
{
    m_normal_type = normal_type;
}

void KVSMLObjectPolygon::setCoords( const kvs::ValueArray<kvs::Real32>& coords )
{
    m_coords = coords;
}

void KVSMLObjectPolygon::setConnections( const kvs::ValueArray<kvs::UInt32>& connections )
{
    m_connections = connections;
}

void KVSMLObjectPolygon::setColors( const kvs::ValueArray<kvs::UInt8>& colors )
{
    m_colors = colors;
}

void KVSMLObjectPolygon::setOpacities( const kvs::ValueArray<kvs::UInt8>& opacities )
{
    m_opacities = opacities;
}

void KVSMLObjectPolygon::setNormals( const kvs::ValueArray<kvs::Real32>& normals )
{
    m_normals = normals;
}

const bool KVSMLObjectPolygon::read( const std::string& filename )
{
    m_filename = filename;

    kvs::XMLDocument document;
    if ( !document.read( filename ) )
    {
        kvsMessageError( "%s", document.ErrorDesc().c_str() );
        return( false );
    }

    kvs::PolygonObjectParser parser;
    if ( !parser.parse( document ) )
    {
        kvsMessageError("'%s' is invalid.", filename.c_str());
        return( false );
    }

/*
    m_npoints      = parser.npoints();
    m_nconnections = parser.nconnections();
    m_dimension    = parser.dimension();
*/
    m_polygon_type = parser.polygonType();
    m_color_type   = parser.colorType();
    m_normal_type  = parser.normalType();

    parser.setCoordsTo( &m_coords );
    parser.setConnectionsTo( &m_connections );
    parser.setColorsTo( &m_colors );
    parser.setOpacitiesTo( &m_opacities );
    parser.setNormalsTo( &m_normals );

    return( true );
}

const bool KVSMLObjectPolygon::write( const std::string& filename )
{
    m_filename = filename;

    kvs::XMLDocument doc;
    doc.InsertEndChild( kvs::XMLDeclaration("1.0") );
    doc.InsertEndChild( kvs::XMLComment(" Generated by kvs::KVSMLObjectPolygon::write() ") );

    // <KVSML>
    TiXmlNode* kvs_node = doc.InsertEndChild( kvs::XMLElement("KVSML") );

    // <Object type="PolygonObject">
    kvs::XMLElement obj_elem("Object");
    obj_elem.setAttribute("type","PolygonObject");
    TiXmlNode* obj_node = kvs_node->InsertEndChild( obj_elem );

    // <PolygonObject>
    kvs::XMLElement polygon_elem("PolygonObject");
    polygon_elem.setAttribute("polygon_type",m_polygon_type);
    polygon_elem.setAttribute("color_type",m_color_type);
    polygon_elem.setAttribute("normal_type",m_normal_type);
    TiXmlNode* polygon_node = obj_node->InsertEndChild( polygon_elem );

    // <Vertex nvertices="xxx">
    kvs::XMLElement vertex_elem("Vertex");
    vertex_elem.setAttribute("nvertices", m_coords.size() / 3 );
    TiXmlNode* vertex_node = polygon_node->InsertEndChild( vertex_elem );

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

    // <Normal>
    if ( m_normals.size() > 0 )
    {
        kvs::XMLElement normal_elem("Normal");
        TiXmlNode* normal_node = vertex_node->InsertEndChild( normal_elem );
        const std::string normal_file = kvs::TagParser::GetDataFilename( m_filename, "normal" );
        if ( !kvs::TagParser::ComposeArray( normal_node, writing_type, m_normals, 3, normal_file ) )
        {
            kvsMessageError("Cannot compose the data array for <Normal>.");
            return( false );
        }
    }

    // <Polygon>
    kvs::XMLElement polygon_connect_elem("Polygon");
    const size_t npolygons = m_polygon_type == "triangle" ? m_connections.size() / 3 : m_connections.size() / 4;
    polygon_connect_elem.setAttribute("npolygons", npolygons );
    TiXmlNode* polygon_connect_node = polygon_node->InsertEndChild( polygon_connect_elem );

    // <Connection>
    if ( m_connections.size() > 0 )
    {
        kvs::XMLElement connect_elem("Connection");
        TiXmlNode* connect_node = polygon_connect_node->InsertEndChild( connect_elem );
        const std::string connect_file = kvs::TagParser::GetDataFilename( m_filename, "connect" );
        if ( !kvs::TagParser::ComposeArray( connect_node, writing_type, m_connections, 1, connect_file ) )
        {
            kvsMessageError("Cannot compose the data array for <Connection>.");
            return( false );
        }
    }

    return( doc.write( m_filename ) );
}

const bool KVSMLObjectPolygon::CheckFileExtension( const std::string& filename )
{
    const kvs::File file( filename );
    if ( file.extension() == "kvsml" || file.extension() == "KVSML" ||
         file.extension() == "xml"   || file.extension() == "XML" )
    {
        return( true );
    }

    return( false );
}

const bool KVSMLObjectPolygon::CheckFileFormat( const std::string& filename )
{
    kvs::XMLDocument document;
    if ( document.read( filename ) )
    {
        if ( kvs::PolygonObjectParser::Check( document ) )
        {
            return( true );
        }
    }

    return( false );
}

std::ostream& operator <<( std::ostream& os, const KVSMLObjectPolygon& rhs )
{
    os << "Polygon type:     " << rhs.m_polygon_type << std::endl;
    os << "Color type:       " << rhs.m_color_type << std::endl;
    os << "Normal type:      " << rhs.m_normal_type << std::endl;
    os << "Num. of vertices: " << rhs.m_coords.size() / 3 << std::endl;

    return( os );
}

} // end of namesapce kvs
