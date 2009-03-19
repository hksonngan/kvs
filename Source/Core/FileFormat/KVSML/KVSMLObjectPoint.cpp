/****************************************************************************/
/**
 *  @file KVSMLObjectPoint.cpp
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
#include "KVSMLObjectPoint.h"
#include "PointObjectParser.h"
#include "TagParser.h"
#include <kvs/XMLDocument>
#include <kvs/XMLDeclaration>
#include <kvs/XMLElement>
#include <kvs/XMLComment>
#include <kvs/ValueArray>
#include <kvs/File>
#include <kvs/Type>
#include <kvs/File>
#include <kvs/IgnoreUnusedVariable>
#include <iostream>
#include <fstream>
#include <sstream>


namespace kvs
{

KVSMLObjectPoint::KVSMLObjectPoint( void ):
    m_has_external_coord( false ),
    m_min_external_coord( -3.0f, -3.0f, -3.0f ),
    m_max_external_coord(  3.0f,  3.0f,  3.0f ),
    m_has_object_coord( false ),
    m_min_object_coord( -3.0f, -3.0f, -3.0f ),
    m_max_object_coord(  3.0f,  3.0f,  3.0f ),
    m_writing_type( kvs::KVSMLObjectPoint::Ascii )
{
}

KVSMLObjectPoint::KVSMLObjectPoint( const std::string& filename ):
    m_has_external_coord( false ),
    m_min_external_coord( -3.0f, -3.0f, -3.0f ),
    m_max_external_coord(  3.0f,  3.0f,  3.0f ),
    m_has_object_coord( false ),
    m_min_object_coord( -3.0f, -3.0f, -3.0f ),
    m_max_object_coord(  3.0f,  3.0f,  3.0f ),
    m_writing_type( kvs::KVSMLObjectPoint::Ascii )
{
    if( this->read( filename ) ) { m_is_success = true; }
    else { m_is_success = false; }
}

KVSMLObjectPoint::~KVSMLObjectPoint( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns a flag to check whether 'external_coord' is specified or not.
 *  @return true, if 'external_coord' is specified
 */
/*===========================================================================*/
const bool KVSMLObjectPoint::hasExternalCoord( void ) const
{
    return( m_has_external_coord );
}

/*===========================================================================*/
/**
 *  @brief  Returns a min. external coordinate.
 *  @return min. external coordinate
 */
/*===========================================================================*/
const kvs::Vector3f& KVSMLObjectPoint::minExternalCoord( void ) const
{
    return( m_min_external_coord );
}

/*===========================================================================*/
/**
 *  @brief  Returns a max. external coordinate.
 *  @return max. external coordinate
 */
/*===========================================================================*/
const kvs::Vector3f& KVSMLObjectPoint::maxExternalCoord( void ) const
{
    return( m_max_external_coord );
}

/*===========================================================================*/
/**
 *  @brief  Returns a flag to check whether 'object_coord' is specified or not.
 *  @return true, if 'object_coord' is specified
 */
/*===========================================================================*/
const bool KVSMLObjectPoint::hasObjectCoord( void ) const
{
    return( m_has_object_coord );
}

/*===========================================================================*/
/**
 *  @brief  Returns a min. object coordinate.
 *  @return min. object coordinate
 */
/*===========================================================================*/
const kvs::Vector3f& KVSMLObjectPoint::minObjectCoord( void ) const
{
    return( m_min_object_coord );
}

/*===========================================================================*/
/**
 *  @brief  Returns a max. object coordinate.
 *  @return max. object coordinate
 */
/*===========================================================================*/
const kvs::Vector3f& KVSMLObjectPoint::maxObjectCoord( void ) const
{
    return( m_max_object_coord );
}

const kvs::ValueArray<kvs::Real32>& KVSMLObjectPoint::coords( void ) const
{
    return( m_coords );
}

const kvs::ValueArray<kvs::UInt8>& KVSMLObjectPoint::colors( void ) const
{
    return( m_colors );
}

const kvs::ValueArray<kvs::Real32>& KVSMLObjectPoint::normals( void ) const
{
    return( m_normals );
}

const kvs::ValueArray<kvs::Real32>& KVSMLObjectPoint::sizes( void ) const
{
    return( m_sizes );
}

void KVSMLObjectPoint::setWritingDataType( const WritingDataType writing_type )
{
    m_writing_type = writing_type;
}

void KVSMLObjectPoint::setCoords( const kvs::ValueArray<kvs::Real32>& coords )
{
    m_coords = coords;
}

void KVSMLObjectPoint::setColors( const kvs::ValueArray<kvs::UInt8>& colors )
{
    m_colors = colors;
}

void KVSMLObjectPoint::setNormals( const kvs::ValueArray<kvs::Real32>& normals )
{
    m_normals = normals;
}

void KVSMLObjectPoint::setSizes( const kvs::ValueArray<kvs::Real32>& sizes )
{
    m_sizes = sizes;
}

const bool KVSMLObjectPoint::read( const std::string& filename )
{
    m_filename = filename;

    kvs::XMLDocument document;
    if ( !document.read( filename ) )
    {
        kvsMessageError( "%s", document.ErrorDesc().c_str() );
        return( false );
    }

    kvs::PointObjectParser parser;
    if ( !parser.parse( document ) )
    {
        kvsMessageError("'%s' is invalid.", filename.c_str());
        return( false );
    }

    parser.setCoordsTo( &m_coords );

    parser.setColorsTo( &m_colors );

    parser.setNormalsTo( &m_normals );

    parser.setSizesTo( &m_sizes );

    return( true );
}

const bool KVSMLObjectPoint::write( const std::string& filename )
{
    m_filename = filename;

    kvs::XMLDocument doc;
    doc.InsertEndChild( kvs::XMLDeclaration("1.0") );
    doc.InsertEndChild( kvs::XMLComment(" Generated by kvs::KVSMLObjectPoint::write() ") );

    // <KVSML>
    TiXmlNode* kvs_node = doc.InsertEndChild( kvs::XMLElement("KVSML") );

    // <Object type="PointObject">
    kvs::XMLElement obj_elem("Object");
    obj_elem.setAttribute("type","PointObject");
    TiXmlNode* obj_node = kvs_node->InsertEndChild( obj_elem );

    // <PointObject>
    kvs::XMLElement point_elem("PointObject");
    TiXmlNode* point_node = obj_node->InsertEndChild( point_elem );

    // <Vertex nvertices="xxx">
    kvs::XMLElement vertex_elem("Vertex");
    vertex_elem.setAttribute("nvertices", m_coords.size() / 3 );
    TiXmlNode* vertex_node = point_node->InsertEndChild( vertex_elem );

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

    return( doc.write( m_filename ) );
}

const bool KVSMLObjectPoint::CheckFileExtension( const std::string& filename )
{
    const kvs::File file( filename );
    if ( file.extension() == "kvsml" || file.extension() == "KVSML" ||
         file.extension() == "xml"   || file.extension() == "XML" )
    {
        return( true );
    }

    return( false );
}

const bool KVSMLObjectPoint::CheckFileFormat( const std::string& filename )
{
    kvs::XMLDocument document;
    if ( document.read( filename ) )
    {
        if ( kvs::PointObjectParser::Check( document ) )
        {
            return( true );
        }
    }

    return( false );
}

std::ostream& operator <<( std::ostream& os, const KVSMLObjectPoint& rhs )
{
    os << "Num. of vertices: " << rhs.m_coords.size() / 3 << std::endl;

    return( os );
}

} // end of namespace kvs
