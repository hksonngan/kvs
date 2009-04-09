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
#include "PointObjectTag.h"
#include "VertexTag.h"
#include "CoordTag.h"
#include "ColorTag.h"
#include "NormalTag.h"
#include "SizeTag.h"
#include "DataArrayTag.h"
#include "DataValueTag.h"
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

/*===========================================================================*/
/**
 *  @brief  Constructs a new KVSML point object class.
 */
/*===========================================================================*/
KVSMLObjectPoint::KVSMLObjectPoint( void ):
    m_writing_type( kvs::KVSMLObjectPoint::Ascii )
{
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new KVSML point object class.
 *  @param  filename [in] filename
 */
/*===========================================================================*/
KVSMLObjectPoint::KVSMLObjectPoint( const std::string& filename ):
    m_writing_type( kvs::KVSMLObjectPoint::Ascii )
{
    if( this->read( filename ) ) { m_is_success = true; }
    else { m_is_success = false; }
}

/*===========================================================================*/
/**
 *  @brief  Destructs the KVSML point object class.
 */
/*===========================================================================*/
KVSMLObjectPoint::~KVSMLObjectPoint( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns the KVSML tag.
 *  @return KVSML tag
 */
/*===========================================================================*/
const kvs::kvsml::KVSMLTag& KVSMLObjectPoint::KVSMLTag( void ) const
{
    return( m_kvsml_tag );
}

/*===========================================================================*/
/**
 *  @brief  Returns the object tag.
 *  @return object tag
 */
/*===========================================================================*/
const kvs::kvsml::ObjectTag& KVSMLObjectPoint::objectTag( void ) const
{
    return( m_object_tag );
}

/*===========================================================================*/
/**
 *  @brief  Returns the coordinate value array.
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::Real32>& KVSMLObjectPoint::coords( void ) const
{
    return( m_coords );
}

/*===========================================================================*/
/**
 *  @brief  Returns the color value array.
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::UInt8>& KVSMLObjectPoint::colors( void ) const
{
    return( m_colors );
}

/*===========================================================================*/
/**
 *  @brief  Returns the normal vector array.
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::Real32>& KVSMLObjectPoint::normals( void ) const
{
    return( m_normals );
}

/*===========================================================================*/
/**
 *  @brief  Returns the size value array.
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::Real32>& KVSMLObjectPoint::sizes( void ) const
{
    return( m_sizes );
}

/*===========================================================================*/
/**
 *  @brief  Set a writing type.
 *  @param  writing_type [in] writing type
 */
/*===========================================================================*/
void KVSMLObjectPoint::setWritingDataType( const WritingDataType writing_type )
{
    m_writing_type = writing_type;
}

/*===========================================================================*/
/**
 *  @brief  Set a coordinate value array.
 *  @param  coords [in] coordinate value array
 */
/*===========================================================================*/
void KVSMLObjectPoint::setCoords( const kvs::ValueArray<kvs::Real32>& coords )
{
    m_coords = coords;
}

/*===========================================================================*/
/**
 *  @brief  Set a color value array.
 *  @param  colors [in] color value array
 */
/*===========================================================================*/
void KVSMLObjectPoint::setColors( const kvs::ValueArray<kvs::UInt8>& colors )
{
    m_colors = colors;
}

/*===========================================================================*/
/**
 *  @brief  Set a normal vector array.
 *  @param  normals [in] normal vector array
 */
/*===========================================================================*/
void KVSMLObjectPoint::setNormals( const kvs::ValueArray<kvs::Real32>& normals )
{
    m_normals = normals;
}

/*===========================================================================*/
/**
 *  @brief  Set a size value array.
 *  @param  sizes [in] size value array
 */
/*===========================================================================*/
void KVSMLObjectPoint::setSizes( const kvs::ValueArray<kvs::Real32>& sizes )
{
    m_sizes = sizes;
}

/*===========================================================================*/
/**
 *  @brief  Read a KVSMl point object file.
 *  @param  filename [in] filename
 *  @return true, if the reading process is successfully
 */
/*===========================================================================*/
const bool KVSMLObjectPoint::read( const std::string& filename )
{
    m_filename = filename;

    // XML document.
    kvs::XMLDocument document;
    if ( !document.read( filename ) )
    {
        kvsMessageError( "%s", document.ErrorDesc().c_str() );
        return( false );
    }

    // <KVSML>
    if ( !m_kvsml_tag.read( &document ) )
    {
        kvsMessageError( "Cannot read <KVSML>." );
        return( false );
    }

    // <Object>
    if ( !m_object_tag.read( m_kvsml_tag.node() ) )
    {
        kvsMessageError( "Cannot read <Object>." );
        return( false );
    }

    // <PointObject>
    kvs::kvsml::PointObjectTag point_tag;
    if ( !point_tag.read( m_object_tag.node() ) )
    {
        kvsMessageError( "Cannot read <PointObject>." );
        return( false );
    }

    // <Vertex>
    kvs::kvsml::VertexTag vertex_tag;
    if ( !vertex_tag.read( point_tag.node() ) )
    {
        kvsMessageError( "Cannot read <Vertex>." );
        return( false );
    }

    // <Coord>
    kvs::kvsml::CoordTag coord_tag;
    if ( !coord_tag.read( vertex_tag.node() ) )
    {
        kvsMessageError( "Cannot read <Coord>." );
        return( false );
    }

    // <DataArray>
    const size_t dimension = 3;
    const size_t coord_nelements = vertex_tag.nvertices() * dimension;
    kvs::kvsml::DataArrayTag coords;
    if ( !coords.read( coord_tag.node(), coord_nelements, &m_coords ) )
    {
        kvsMessageError("Cannot read <DataArray> for <Coord>.");
        return( false );
    }

    // <Color>
    if ( kvs::XMLNode::FindChildNode( vertex_tag.node(), "Color" ) )
    {
        kvs::kvsml::ColorTag color_tag;
        if ( !color_tag.read( vertex_tag.node() ) )
        {
            kvsMessageError( "Cannot read <Color>." );
            return( false );
        }

        // <DataValue>
        if ( kvs::XMLNode::FindChildNode( color_tag.node(), "DataValue" ) )
        {
            const size_t nchannels = 3;
            const size_t ncolors = 1;
            const size_t color_nelements = ncolors * nchannels;
            kvs::kvsml::DataValueTag colors;
            if ( !colors.read( color_tag.node(), color_nelements, &m_colors ) )
            {
                kvsMessageError("Cannot read <DataValue> for <Color>.");
                return( false );
            }
        }
        // <DataArray>
        else
        {
            const size_t nchannels = 3;
            const size_t ncolors = vertex_tag.nvertices();
            const size_t color_nelements = ncolors * nchannels;
            kvs::kvsml::DataArrayTag colors;
            if ( !colors.read( color_tag.node(), color_nelements, &m_colors ) )
            {
                kvsMessageError("Cannot read <DataArray> for <Color>.");
                return( false );
            }
        }
    }

    // <Normal>
    if ( kvs::XMLNode::FindChildNode( vertex_tag.node(), "Normal" ) )
    {
        kvs::kvsml::NormalTag normal_tag;
        if ( !normal_tag.read( vertex_tag.node() ) )
        {
            kvsMessageError( "Cannot read <Normal>." );
            return( false );
        }

        // <DataArray>
        const size_t normal_nelements = vertex_tag.nvertices() * dimension;
        kvs::kvsml::DataArrayTag normals;
        if ( !normals.read( normal_tag.node(), normal_nelements, &m_normals ) )
        {
            kvsMessageError("Cannot read <DataArray> for <Normal>.");
            return( false );
        }
    }

    // <Size>
    if ( kvs::XMLNode::FindChildNode( vertex_tag.node(), "Size" ) )
    {
        kvs::kvsml::SizeTag size_tag;
        if ( !size_tag.read( vertex_tag.node() ) )
        {
            kvsMessageError( "Cannot read <Size>." );
            return( false );
        }

        // <DataValue>
        if ( kvs::XMLNode::FindChildNode( size_tag.node(), "DataValue" ) )
        {
            const size_t size_nelements = 1;
            kvs::kvsml::DataValueTag sizes;
            if ( !sizes.read( size_tag.node(), size_nelements, &m_sizes ) )
            {
                kvsMessageError("Cannot read <DataValue> for <Size>.");
                return( false );
            }
        }
        // <DataArray>
        else
        {
            const size_t size_nelements = vertex_tag.nvertices();
            kvs::kvsml::DataArrayTag sizes;
            if ( !sizes.read( size_tag.node(), size_nelements, &m_sizes ) )
            {
                kvsMessageError("Cannot read <DataArray> for <Size>.");
                return( false );
            }
        }
    }

    return( true );
}

/*===========================================================================*/
/**
 *  @brief  Writes the KVSML point object.
 *  @param  filename [in] filename
 *  @return true, if the writing process is done successfully
 */
/*===========================================================================*/
const bool KVSMLObjectPoint::write( const std::string& filename )
{
    m_filename = filename;

    kvs::XMLDocument document;
    document.InsertEndChild( kvs::XMLDeclaration("1.0") );
    document.InsertEndChild( kvs::XMLComment(" Generated by kvs::KVSMLObjectPoint::write() ") );

    // <KVSML>
    kvs::kvsml::KVSMLTag kvsml_tag;
    if ( !kvsml_tag.write( &document ) )
    {
        kvsMessageError( "Cannot write <KVSML>." );
        return( false );
    }

    // <Object type="PointObject">
    kvs::kvsml::ObjectTag object_tag;
    object_tag.setType( "PointObject" );
    if ( !object_tag.write( kvsml_tag.node() ) )
    {
        kvsMessageError( "Cannot write <Object>." );
        return( false );
    }

    // <PointObject>
    kvs::kvsml::PointObjectTag point_tag;
    if ( !point_tag.write( object_tag.node() ) )
    {
        kvsMessageError( "Cannot write <PointObject>." );
        return( false );
    }

    // <Vertex nvertices="xxx">
    const size_t dimension = 3;
    kvs::kvsml::VertexTag vertex_tag;
    vertex_tag.setNVertices( m_coords.size() / dimension );
    if ( !vertex_tag.write( point_tag.node() ) )
    {
        kvsMessageError( "Cannot write <Vertex>." );
        return( false );
    }

    // <Coord>
    kvs::kvsml::CoordTag coord_tag;
    if ( !coord_tag.write( vertex_tag.node() ) )
    {
        kvsMessageError( "Cannot write <Coord>." );
        return( false );
    }

    // <DataArray>
    kvs::kvsml::DataArrayTag coords;
    if ( m_writing_type == ExternalAscii )
    {
        coords.setFile( kvs::kvsml::DataArray::GetDataFilename( m_filename, "coord" ) );
        coords.setFormat( "ascii" );
    }
    else if ( m_writing_type == ExternalBinary )
    {
        coords.setFile( kvs::kvsml::DataArray::GetDataFilename( m_filename, "coord" ) );
        coords.setFormat( "binary" );
    }

    if ( !coords.write( coord_tag.node(), m_coords ) )
    {
        kvsMessageError( "Cannot write <DataArray> for <Coord>." );
        return( false );
    }

    // <Color>
    if ( m_colors.size() > 0 )
    {
        kvs::kvsml::ColorTag color_tag;
        if ( !color_tag.write( vertex_tag.node() ) )
        {
            kvsMessageError( "Cannot write <Color>." );
            return( false );
        }

        // <DataValue>
        if ( m_colors.size() == 3 )
        {
            kvs::kvsml::DataValueTag colors;
            if ( !colors.write( color_tag.node(), m_colors ) )
            {
                kvsMessageError("Cannot write <DataValue> for <Color>.");
                return( false );
            }
        }
        // <DataArray>
        else
        {
            kvs::kvsml::DataArrayTag colors;
            if ( m_writing_type == ExternalAscii )
            {
                colors.setFile( kvs::kvsml::DataArray::GetDataFilename( m_filename, "color" ) );
                colors.setFormat( "ascii" );
            }
            else if ( m_writing_type == ExternalBinary )
            {
                colors.setFile( kvs::kvsml::DataArray::GetDataFilename( m_filename, "color" ) );
                colors.setFormat( "binary" );
            }

            if ( !colors.write( color_tag.node(), m_colors ) )
            {
                kvsMessageError( "Cannot write <DataArray> for <Color>." );
                return( false );
            }
        }
    }
    else
    {
        // default value (black).
        m_colors.allocate(3);
        m_colors.at(0) = 0;
        m_colors.at(1) = 0;
        m_colors.at(2) = 0;
    }

    // <Normal>
    if ( m_normals.size() > 0 )
    {
        kvs::kvsml::NormalTag normal_tag;
        if ( !normal_tag.write( vertex_tag.node() ) )
        {
            kvsMessageError( "Cannot write <Normal>." );
            return( false );
        }

        // <DataValue>
        if ( m_normals.size() == 3 )
        {
            kvs::kvsml::DataValueTag normals;
            if ( !normals.write( normal_tag.node(), m_normals ) )
            {
                kvsMessageError("Cannot write <DataValue> for <Normal>.");
                return( false );
            }
        }
        // <DataArray>
        else
        {
            kvs::kvsml::DataArrayTag normals;
            if ( m_writing_type == ExternalAscii )
            {
                normals.setFile( kvs::kvsml::DataArray::GetDataFilename( m_filename, "normal" ) );
                normals.setFormat( "ascii" );
            }
            else if ( m_writing_type == ExternalBinary )
            {
                normals.setFile( kvs::kvsml::DataArray::GetDataFilename( m_filename, "normal" ) );
                normals.setFormat( "binary" );
            }

            if ( !normals.write( normal_tag.node(), m_normals ) )
            {
                kvsMessageError( "Cannot write <DataArray> for <Normal>." );
                return( false );
            }
        }
    }

    // <Size>
    if ( m_sizes.size() > 0 )
    {
        kvs::kvsml::SizeTag size_tag;
        if ( !size_tag.write( vertex_tag.node() ) )
        {
            kvsMessageError( "Cannot write <Size>." );
            return( false );
        }

        // <DataValue>
        if ( m_sizes.size() == 1 )
        {
            kvs::kvsml::DataValueTag sizes;
            if ( !sizes.write( size_tag.node(), m_sizes ) )
            {
                kvsMessageError("Cannot write <DataValue> for <Size>.");
                return( false );
            }
        }
        // <DataArray>
        else
        {
            kvs::kvsml::DataArrayTag sizes;
            if ( m_writing_type == ExternalAscii )
            {
                sizes.setFile( kvs::kvsml::DataArray::GetDataFilename( m_filename, "size" ) );
                sizes.setFormat( "ascii" );
            }
            else if ( m_writing_type == ExternalBinary )
            {
                sizes.setFile( kvs::kvsml::DataArray::GetDataFilename( m_filename, "size" ) );
                sizes.setFormat( "binary" );
            }

            if ( !sizes.write( size_tag.node(), m_sizes ) )
            {
                kvsMessageError( "Cannot write <DataArray> for <Size>." );
                return( false );
            }
        }
    }

    return( document.write( m_filename ) );
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
    if ( !document.read( filename ) ) return( false );

    // <KVSML>
    kvs::kvsml::KVSMLTag kvsml_tag;
    if ( !kvsml_tag.read( &document ) ) return( false );

    // <Object>
    kvs::kvsml::ObjectTag object_tag;
    if ( !object_tag.read( kvsml_tag.node() ) ) return( false );

    if ( object_tag.type() != "PointObject" ) return( false );

    // <PointObject>
    kvs::kvsml::PointObjectTag point_tag;
    if ( !point_tag.read( object_tag.node() ) ) return( false );

    return( true );
}

std::ostream& operator <<( std::ostream& os, const KVSMLObjectPoint& rhs )
{
    os << "Num. of vertices: " << rhs.m_coords.size() / 3 << std::endl;

    return( os );
}

} // end of namespace kvs
