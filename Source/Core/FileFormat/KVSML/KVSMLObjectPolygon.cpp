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
#include "PolygonObjectTag.h"
#include "PolygonTag.h"
#include "VertexTag.h"
#include "CoordTag.h"
#include "ColorTag.h"
#include "ConnectionTag.h"
#include "NormalTag.h"
#include "OpacityTag.h"
#include "DataArrayTag.h"
#include "DataValueTag.h"
#include "DataReader.h"
#include "DataWriter.h"
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

/*===========================================================================*/
/**
 *  @brief  Constructs a new KVSML polygon object class.
 */
/*===========================================================================*/
KVSMLObjectPolygon::KVSMLObjectPolygon( void ):
    m_writing_type( kvs::KVSMLObjectPolygon::Ascii )
{
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new KVSML polygon object class.
 *  @param  filename [in] filename
 */
/*===========================================================================*/
KVSMLObjectPolygon::KVSMLObjectPolygon( const std::string& filename ):
    m_writing_type( kvs::KVSMLObjectPolygon::Ascii )
{
    if ( this->read( filename ) ) { m_is_success = true; }
    else { m_is_success = false; }
}

/*===========================================================================*/
/**
 *  @brief  Destructs the KVSML polygon object class.
 */
/*===========================================================================*/
KVSMLObjectPolygon::~KVSMLObjectPolygon( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns the KVSML tag.
 *  @return KVSML tag
 */
/*===========================================================================*/
const kvs::kvsml::KVSMLTag& KVSMLObjectPolygon::KVSMLTag( void ) const
{
    return( m_kvsml_tag );
}

/*===========================================================================*/
/**
 *  @brief  Returns the object tag.
 *  @return object tag
 */
/*===========================================================================*/
const kvs::kvsml::ObjectTag& KVSMLObjectPolygon::objectTag( void ) const
{
    return( m_object_tag );
}

/*===========================================================================*/
/**
 *  @brief  Returns the polygon type.
 *  @return polygon type
 */
/*===========================================================================*/
const std::string& KVSMLObjectPolygon::polygonType( void ) const
{
    return( m_polygon_type );
}

/*===========================================================================*/
/**
 *  @brief  Returns the color type.
 *  @return color type
 */
/*===========================================================================*/
const std::string& KVSMLObjectPolygon::colorType( void ) const
{
    return( m_color_type );
}

/*===========================================================================*/
/**
 *  @brief  Returns the normal type.
 *  @return normal type
 */
/*===========================================================================*/
const std::string& KVSMLObjectPolygon::normalType( void ) const
{
    return( m_normal_type );
}

/*===========================================================================*/
/**
 *  @brief  Returns the coordinate value array.
 *  @return coordinate value array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::Real32>& KVSMLObjectPolygon::coords( void ) const
{
    return( m_coords );
}

/*===========================================================================*/
/**
 *  @brief  Returns the connection data array.
 *  @return connection data array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::UInt32>& KVSMLObjectPolygon::connections( void ) const
{
    return( m_connections );
}

/*===========================================================================*/
/**
 *  @brief  Returns the color value array.
 *  @return color value array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::UInt8>& KVSMLObjectPolygon::colors( void ) const
{
    return( m_colors );
}

/*===========================================================================*/
/**
 *  @brief  Returns the opacity value array.
 *  @return opacity value array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::UInt8>& KVSMLObjectPolygon::opacities( void ) const
{
    return( m_opacities );
}

/*===========================================================================*/
/**
 *  @brief  Returns the normal vector array.
 *  @return normal vector array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::Real32>& KVSMLObjectPolygon::normals( void ) const
{
    return( m_normals );
}

/*===========================================================================*/
/**
 *  @brief  Sets a writing type.
 *  @param  writing_type [in] writing type
 */
/*===========================================================================*/
void KVSMLObjectPolygon::setWritingDataType( const WritingDataType writing_type )
{
    m_writing_type = writing_type;
}

/*===========================================================================*/
/**
 *  @brief  Sets a polygon type.
 *  @param  polygon_type [in] polygon type (triangle or quadrangle)
 */
/*===========================================================================*/
void KVSMLObjectPolygon::setPolygonType( const std::string& polygon_type )
{
    m_polygon_type = polygon_type;
}

/*===========================================================================*/
/**
 *  @brief  Sets a color type.
 *  @param  color_type [in] color type (vertex or polygon)
 */
/*===========================================================================*/
void KVSMLObjectPolygon::setColorType( const std::string& color_type )
{
    m_color_type = color_type;
}

/*===========================================================================*/
/**
 *  @brief  Sets a normal vector type.
 *  @param  normal_type [in] normal vector type
 */
/*===========================================================================*/
void KVSMLObjectPolygon::setNormalType( const std::string& normal_type )
{
    m_normal_type = normal_type;
}

/*===========================================================================*/
/**
 *  @brief  Set a coordinate value array.
 *  @param  coords [in] coordinate value array
 */
/*===========================================================================*/
void KVSMLObjectPolygon::setCoords( const kvs::ValueArray<kvs::Real32>& coords )
{
    m_coords = coords;
}

/*===========================================================================*/
/**
 *  @brief  Sets a connection data array.
 *  @param  connections [in] connection data array
 */
/*===========================================================================*/
void KVSMLObjectPolygon::setConnections( const kvs::ValueArray<kvs::UInt32>& connections )
{
    m_connections = connections;
}

/*===========================================================================*/
/**
 *  @brief  Sets a color value array.
 *  @param  colors [in] color value array
 */
/*===========================================================================*/
void KVSMLObjectPolygon::setColors( const kvs::ValueArray<kvs::UInt8>& colors )
{
    m_colors = colors;
}

/*===========================================================================*/
/**
 *  @brief  Sets an opacity value array.
 *  @param  opacities [in] opacity value array
 */
/*===========================================================================*/
void KVSMLObjectPolygon::setOpacities( const kvs::ValueArray<kvs::UInt8>& opacities )
{
    m_opacities = opacities;
}

/*===========================================================================*/
/**
 *  @brief  Sets a normal vector array.
 *  @param  normals [in] normal vector array
 */
/*===========================================================================*/
void KVSMLObjectPolygon::setNormals( const kvs::ValueArray<kvs::Real32>& normals )
{
    m_normals = normals;
}

/*===========================================================================*/
/**
 *  @brief  Read a KVSMl polygon object file.
 *  @param  filename [in] filename
 *  @return true, if the reading process is successfully
 */
/*===========================================================================*/
const bool KVSMLObjectPolygon::read( const std::string& filename )
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
        kvsMessageError( "Cannot read <%s>.", m_kvsml_tag.name().c_str() );
        return( false );
    }

    // <Object>
    if ( !m_object_tag.read( m_kvsml_tag.node() ) )
    {
        kvsMessageError( "Cannot read <%s>.", m_object_tag.name().c_str() );
        return( false );
    }

    // <PolygonObject>
    kvs::kvsml::PolygonObjectTag polygon_object_tag;
    if ( !polygon_object_tag.read( m_object_tag.node() ) )
    {
        kvsMessageError( "Cannot read <%s>.", polygon_object_tag.name().c_str() );
        return( false );
    }

    m_polygon_type = "triangle"; // default
    if ( polygon_object_tag.hasPolygonType() )
    {
        // triangle or quadrangle
        m_polygon_type = polygon_object_tag.polygonType();
    }

    m_color_type = "polygon"; // default
    if ( polygon_object_tag.hasColorType() )
    {
        // polygon or vertex
        m_color_type = polygon_object_tag.colorType();
    }

    m_normal_type = "polygon"; // default
    if ( polygon_object_tag.hasNormalType() )
    {
        // polygon or vertex
        m_normal_type = polygon_object_tag.normalType();
    }

    // <Vertex>
    kvs::kvsml::VertexTag vertex_tag;
    if ( !vertex_tag.read( polygon_object_tag.node() ) )
    {
        kvsMessageError( "Cannot read <%s>.", vertex_tag.name().c_str() );
        return( false );
    }
    else
    {
        // Parent node.
        const kvs::XMLNode::SuperClass* parent = vertex_tag.node();

        // <Coord>
        const size_t ncoords = vertex_tag.nvertices();
        if ( !kvs::kvsml::ReadCoordData( parent, ncoords, &m_coords ) ) return( false );
        if ( m_coords.size() == 0 )
        {
            kvsMessageError( "Cannot read the coord data." );
            return( false );
        }

        // <Color>
        if ( m_color_type == "vertex" )
        {
            const size_t ncolors = vertex_tag.nvertices();
            if ( !kvs::kvsml::ReadColorData( parent, ncolors, &m_colors ) ) return( false );
        }
        if ( m_colors.size() == 0 )
        {
            // default value (black).
            m_colors.allocate(3);
            m_colors.at(0) = 0;
            m_colors.at(1) = 0;
            m_colors.at(2) = 0;
        }

        // <Normal>
        if ( m_normal_type == "vertex" )
        {
            const size_t nnormals = vertex_tag.nvertices();
            if ( !kvs::kvsml::ReadNormalData( parent, nnormals, &m_normals ) ) return( false );
        }
    }

    // <Polygon>
    kvs::kvsml::PolygonTag polygon_tag;
    if ( polygon_tag.isExisted( polygon_object_tag.node() ) )
    {
        if ( !polygon_tag.read( polygon_object_tag.node() ) )
        {
            kvsMessageError( "Cannot read <%s>.", polygon_object_tag.name().c_str() );
            return( false );
        }
        else
        {
            // Parent node.
            const kvs::XMLNode::SuperClass* parent = polygon_tag.node();
            const size_t nvertices = vertex_tag.nvertices();
            const size_t npolygons = polygon_tag.npolygons();

            // <Connection>
            const size_t nconnections =
                ( m_polygon_type == "triangle"   ) ? npolygons * 3 :
                ( m_polygon_type == "quadrangle" ) ? npolygons * 4 : 0;
            if ( !kvs::kvsml::ReadConnectionData( parent, nconnections, &m_connections ) ) return( false );

            // <Opacity>
            const size_t nopacities = npolygons;
            if ( !kvs::kvsml::ReadOpacityData( parent, nopacities, &m_opacities ) ) return( false );
            if ( m_opacities.size() == 0 )
            {
                // default value (255).
                m_opacities.allocate(1);
                m_opacities.at(0) = 255;
            }

            // <Color>
            if ( m_color_type == "polygon" )
            {
                const size_t ncolors = npolygons;
                if ( !kvs::kvsml::ReadColorData( parent, ncolors, &m_colors ) ) return( false );
            }
            if ( m_colors.size() == 0 )
            {
                // default value (black).
                m_colors.allocate(3);
                m_colors.at(0) = 0;
                m_colors.at(1) = 0;
                m_colors.at(2) = 0;
            }

            // <Normal>
            if ( m_normal_type == "polygon" )
            {
                const size_t nconnections = m_connections.size();
                const size_t nvertices_per_polygon = m_polygon_type == "triangle" ? 3 : 4;
                const size_t nnormals = ( nconnections > 0 ) ?
                    nconnections / nvertices_per_polygon :
                    nvertices / nvertices_per_polygon;
                if ( !kvs::kvsml::ReadNormalData( parent, nnormals, &m_normals ) ) return( false );
            }
        }
    }

    return( true );
}

/*===========================================================================*/
/**
 *  @brief  Writes the KVSML polygon object.
 *  @param  filename [in] filename
 *  @return true, if the writing process is done successfully
 */
/*===========================================================================*/
const bool KVSMLObjectPolygon::write( const std::string& filename )
{
    m_filename = filename;

    kvs::XMLDocument document;
    document.InsertEndChild( kvs::XMLDeclaration("1.0") );
    document.InsertEndChild( kvs::XMLComment(" Generated by kvs::KVSMLObjectPolygon::write() ") );

    // <KVSML>
    kvs::kvsml::KVSMLTag kvsml_tag;
    if ( !kvsml_tag.write( &document ) )
    {
        kvsMessageError( "Cannot write <%s>.", kvsml_tag.name().c_str() );
        return( false );
    }

    // <Object type="PolygonObject">
    kvs::kvsml::ObjectTag object_tag;
    object_tag.setType( "PolygonObject" );
    if ( !object_tag.write( kvsml_tag.node() ) )
    {
        kvsMessageError( "Cannot write <%s>.", object_tag.name().c_str() );
        return( false );
    }

    // <PolygonObject>
    kvs::kvsml::PolygonObjectTag polygon_object_tag;
    polygon_object_tag.setPolygonType( m_polygon_type );
    polygon_object_tag.setColorType( m_color_type );
    polygon_object_tag.setNormalType( m_normal_type );
    if ( !polygon_object_tag.write( object_tag.node() ) )
    {
        kvsMessageError( "Cannot write <%s>.", polygon_object_tag.name().c_str() );
        return( false );
    }

    const size_t dimension = 3;
    const size_t nvertices = m_coords.size() / dimension;

    // <Vertex nvertices="xxx">
    kvs::kvsml::VertexTag vertex_tag;
    vertex_tag.setNVertices( nvertices );
    if ( !vertex_tag.write( polygon_object_tag.node() ) )
    {
        kvsMessageError( "Cannot write <%s>.", vertex_tag.name().c_str() );
        return( false );
    }
    else
    {
        // Parent node and writing data type.
        kvs::XMLNode::SuperClass* parent = vertex_tag.node();
        const kvs::kvsml::WritingDataType type = static_cast<kvs::kvsml::WritingDataType>(m_writing_type);

        // <Coord>
        if ( !kvs::kvsml::WriteCoordData( parent, type, m_filename, m_coords ) ) return( false );

        // <Color>
        if ( m_color_type == "vertex" )
        {
            if ( !kvs::kvsml::WriteColorData( parent, type, m_filename, m_colors ) ) return( false );
        }

        // <Normal>
        if ( m_normal_type == "vertex" )
        {
            if ( !kvs::kvsml::WriteNormalData( parent, type, m_filename, m_normals ) ) return( false );
        }
    }

    // <Polygon npolygons="xxx">
    if ( m_color_type == "polygon" || m_normal_type == "polygon" ||
         m_opacities.size() > 0 || m_connections.size() > 0 )
    {
        const size_t nconnections = m_connections.size();
        const size_t nvertices_per_polygon = m_polygon_type == "triangle" ? 3 : 4;
        const size_t npolygons = ( nconnections > 0 ) ?
            nconnections / nvertices_per_polygon :
            nvertices / nvertices_per_polygon;

        kvs::kvsml::PolygonTag polygon_tag;
        polygon_tag.setNPolygons( npolygons );
        if ( !polygon_tag.write( polygon_object_tag.node() ) )
        {
            kvsMessageError( "Cannot write <%s>.", polygon_tag.name().c_str() );
            return( false );
        }

        // Parent node and writing data type.
        kvs::XMLNode::SuperClass* parent = polygon_tag.node();
        const kvs::kvsml::WritingDataType type = static_cast<kvs::kvsml::WritingDataType>(m_writing_type);

        // <Connection>
        if ( !kvs::kvsml::WriteConnectionData( parent, type, m_filename, m_connections ) ) return( false );

        // <Opacity>
        if ( !kvs::kvsml::WriteOpacityData( parent, type, m_filename, m_opacities ) ) return( false );

        // <Color>
        if ( m_color_type == "polygon" )
        {
            if ( !kvs::kvsml::WriteColorData( parent, type, m_filename, m_colors ) ) return( false );
        }

        // <Normal>
        if ( m_normal_type == "polygon" )
        {
            if ( !kvs::kvsml::WriteNormalData( parent, type, m_filename, m_normals ) ) return( false );
        }
    }


/*
    // <Vertex nvertices="xxx">
    const size_t dimension = 3;
    kvs::kvsml::VertexTag vertex_tag;
    vertex_tag.setNVertices( m_coords.size() / dimension );
    if ( !vertex_tag.write( polygon_object_tag.node() ) )
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

    if ( m_connections.size() > 0 || m_opacities.size() > 0 )
    {
        // <Polygon npolygons="xxx">
        size_t npolygons = m_opacities.size();
        if ( m_connections.size() > 0 )
        {
            npolygons = m_polygon_type == "triangle" ? m_connections.size() / 3 : m_connections.size() / 4;
        }
        kvs::kvsml::PolygonTag polygon_tag;
        polygon_tag.setNPolygons( npolygons );
        if ( !polygon_tag.write( polygon_object_tag.node() ) )
        {
            kvsMessageError( "Cannot write <Polygon>." );
            return( false );
        }

        if ( m_connections.size() > 0 )
        {
            // <Connection>
            kvs::kvsml::ConnectionTag connection_tag;
            if ( !connection_tag.write( polygon_tag.node() ) )
            {
                kvsMessageError( "Cannot write <Connection>." );
                return( false );
            }

            // <DataArray>
            kvs::kvsml::DataArrayTag connections;
            if ( m_writing_type == ExternalAscii )
            {
                connections.setFile( kvs::kvsml::DataArray::GetDataFilename( m_filename, "connect" ) );
                connections.setFormat( "ascii" );
            }
            else if ( m_writing_type == ExternalBinary )
            {
                connections.setFile( kvs::kvsml::DataArray::GetDataFilename( m_filename, "connect" ) );
                connections.setFormat( "binary" );
            }

            if ( !connections.write( connection_tag.node(), m_connections ) )
            {
                kvsMessageError( "Cannot write <DataArray> for <Connection>." );
                return( false );
            }
        }

        if ( m_opacities.size() > 0 )
        {
            // <Opacity>
            kvs::kvsml::OpacityTag opacity_tag;
            if ( !opacity_tag.write( polygon_tag.node() ) )
            {
                kvsMessageError( "Cannot write <Opacity>." );
                return( false );
            }

            // <DataValue>
            if ( m_opacities.size() == 1 )
            {
                kvs::kvsml::DataValueTag opacities;
                if ( !opacities.write( opacity_tag.node(), m_opacities ) )
                {
                    kvsMessageError("Cannot write <DataValue> for <Opacity>.");
                    return( false );
                }
            }
            // <DataArray>
            else
            {
                kvs::kvsml::DataArrayTag opacities;
                if ( m_writing_type == ExternalAscii )
                {
                    opacities.setFile( kvs::kvsml::DataArray::GetDataFilename( m_filename, "opacity" ) );
                    opacities.setFormat( "ascii" );
                }
                else if ( m_writing_type == ExternalBinary )
                {
                    opacities.setFile( kvs::kvsml::DataArray::GetDataFilename( m_filename, "opacity" ) );
                    opacities.setFormat( "binary" );
                }

                if ( !opacities.write( opacity_tag.node(), m_opacities ) )
                {
                    kvsMessageError( "Cannot write <DataArray> for <Opacity>." );
                    return( false );
                }
            }
        }
    }
*/
    return( document.write( m_filename ) );
}

/*===========================================================================*/
/**
 *  @brief  Checks the file extension.
 *  @param  filename [in] filename
 *  @return true, if the given filename has the supported extension
 */
/*===========================================================================*/
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

/*===========================================================================*/
/**
 *  @brief  Check the file format.
 *  @param  filename [in] filename
 *  @return true, if the KVSMLObjectPolygon class can read the given file
 */
/*===========================================================================*/
const bool KVSMLObjectPolygon::CheckFileFormat( const std::string& filename )
{
    kvs::XMLDocument document;
    if ( !document.read( filename ) ) return( false );

    // <KVSML>
    kvs::kvsml::KVSMLTag kvsml_tag;
    if ( !kvsml_tag.read( &document ) ) return( false );

    // <Object>
    kvs::kvsml::ObjectTag object_tag;
    if ( !object_tag.read( kvsml_tag.node() ) ) return( false );

    if ( object_tag.type() != "PolygonObject" ) return( false );

    // <PolygonObject>
    kvs::kvsml::PolygonObjectTag polygon_tag;
    if ( !polygon_tag.read( object_tag.node() ) ) return( false );

    return( true );
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
