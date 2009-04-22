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
#include "LineObjectTag.h"
#include "LineTag.h"
#include "VertexTag.h"
#include "CoordTag.h"
#include "ColorTag.h"
#include "ConnectionTag.h"
#include "SizeTag.h"
#include "DataArrayTag.h"
#include "DataValueTag.h"
#include <kvs/File>
#include <kvs/XMLDocument>
#include <kvs/XMLDeclaration>
#include <kvs/XMLElement>
#include <kvs/XMLComment>
#include <kvs/IgnoreUnusedVariable>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new KVSML line object class.
 */
/*===========================================================================*/
KVSMLObjectLine::KVSMLObjectLine( void ):
    m_writing_type( kvs::KVSMLObjectLine::Ascii )
{
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new KVSML line object class.
 *  @param  filename [in] filename
 */
/*===========================================================================*/
KVSMLObjectLine::KVSMLObjectLine( const std::string& filename ):
    m_writing_type( kvs::KVSMLObjectLine::Ascii )
{
    if ( this->read( filename ) ) { m_is_success = true; }
    else { m_is_success = false; }
}

/*===========================================================================*/
/**
 *  @brief  Destructs the KVSML line object class.
 */
/*===========================================================================*/
KVSMLObjectLine::~KVSMLObjectLine( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns the KVSML tag.
 *  @return KVSML tag
 */
/*===========================================================================*/
const kvs::kvsml::KVSMLTag& KVSMLObjectLine::KVSMLTag( void ) const
{
    return( m_kvsml_tag );
}

/*===========================================================================*/
/**
 *  @brief  Returns the object tag.
 *  @return object tag
 */
/*===========================================================================*/
const kvs::kvsml::ObjectTag& KVSMLObjectLine::objectTag( void ) const
{
    return( m_object_tag );
}

/*===========================================================================*/
/**
 *  @brief  Returns the line type.
 *  @return line type
 */
/*===========================================================================*/
const std::string& KVSMLObjectLine::lineType( void ) const
{
    return( m_line_type );
}

/*===========================================================================*/
/**
 *  @brief  Returns the color type.
 *  @return color type
 */
/*===========================================================================*/
const std::string& KVSMLObjectLine::colorType( void ) const
{
    return( m_color_type );
}

/*===========================================================================*/
/**
 *  @brief  Returns the coordinate value array.
 *  @return coordinate value array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::Real32>& KVSMLObjectLine::coords( void ) const
{
    return( m_coords );
}

/*===========================================================================*/
/**
 *  @brief  Returns the color value array.
 *  @return color value array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::UInt8>& KVSMLObjectLine::colors( void ) const
{
    return( m_colors );
}

/*===========================================================================*/
/**
 *  @brief  Returns the connection data array.
 *  @return connection data array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::UInt32>& KVSMLObjectLine::connections( void ) const
{
    return( m_connections );
}

/*===========================================================================*/
/**
 *  @brief  Returns the size value array.
 *  @return size value array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::Real32>& KVSMLObjectLine::sizes( void ) const
{
    return( m_sizes );
}

/*===========================================================================*/
/**
 *  @brief  Sets a writing type.
 *  @param  writing_type [in] writing type
 */
/*===========================================================================*/
void KVSMLObjectLine::setWritingDataType( const WritingDataType writing_type )
{
    m_writing_type = writing_type;
}

/*===========================================================================*/
/**
 *  @brief  Sets a line type.
 *  @param  line_type [in] line type (strip, uniline, polyline or segment)
 */
/*===========================================================================*/
void KVSMLObjectLine::setLineType( const std::string& line_type )
{
    m_line_type = line_type;
}

/*===========================================================================*/
/**
 *  @brief  Sets a color type.
 *  @param  color_type [in] color type (vertex or line)
 */
/*===========================================================================*/
void KVSMLObjectLine::setColorType( const std::string& color_type )
{
    m_color_type = color_type;
}

/*===========================================================================*/
/**
 *  @brief  Sets a coordinate value array.
 *  @param  coords [in] coordinate value array
 */
/*===========================================================================*/
void KVSMLObjectLine::setCoords( const kvs::ValueArray<kvs::Real32>& coords )
{
    m_coords = coords;
}

/*===========================================================================*/
/**
 *  @brief  Sets a color value array.
 *  @param  colors [in] color value array
 */
/*===========================================================================*/
void KVSMLObjectLine::setColors( const kvs::ValueArray<kvs::UInt8>& colors )
{
    m_colors = colors;
}

/*===========================================================================*/
/**
 *  @brief  Sets a connection data array.
 *  @param  connections [in] connection data array
 */
/*===========================================================================*/
void KVSMLObjectLine::setConnections( const kvs::ValueArray<kvs::UInt32>& connections )
{
    m_connections = connections;
}

/*===========================================================================*/
/**
 *  @brief  Sets a size value array.
 *  @param  sizes [in] size value array
 */
/*===========================================================================*/
void KVSMLObjectLine::setSizes( const kvs::ValueArray<kvs::Real32>& sizes )
{
    m_sizes = sizes;
}

/*===========================================================================*/
/**
 *  @brief  Reads a KVSML line object file.
 *  @param  filename [in] filename
 *  @return true, if the reading process is done successfully
 */
/*===========================================================================*/
const bool KVSMLObjectLine::read( const std::string& filename )
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

    // <LineObject>
    kvs::kvsml::LineObjectTag line_object_tag;
    if ( !line_object_tag.read( m_object_tag.node() ) )
    {
        kvsMessageError( "Cannot read <LineObject>." );
        return( false );
    }

    m_line_type = "strip"; // default
    if ( line_object_tag.hasLineType() )
    {
        // strip, uniline, polyline or segment
        m_line_type = line_object_tag.lineType();
    }

    m_color_type = "line"; // default
    if ( line_object_tag.hasColorType() )
    {
        // line or vertex
        m_color_type = line_object_tag.colorType();
    }

    // <Line>
    kvs::kvsml::LineTag line_tag;
    if ( m_line_type != "strip" )
    {
        if ( !line_tag.read( line_object_tag.node() ) )
        {
            kvsMessageError( "Cannot read <Line>." );
            return( false );
        }

        // <Connection>
        if ( kvs::XMLNode::FindChildNode( line_tag.node(), "Connection" ) )
        {
            kvs::kvsml::ConnectionTag connection_tag;
            if ( !connection_tag.read( line_tag.node() ) )
            {
                kvsMessageError( "Cannot read <Connection>." );
                return( false );
            }

            // <DataArray>
            size_t connection_nelements = 0;
            if (      m_line_type == "uniline"  ) connection_nelements = line_tag.nlines();
            else if ( m_line_type == "polyline" ) connection_nelements = line_tag.nlines() * 2;
            else if ( m_line_type == "segment"  ) connection_nelements = line_tag.nlines() * 2;
            kvs::kvsml::DataArrayTag connections;
            if ( !connections.read( connection_tag.node(), connection_nelements, &m_connections ) )
            {
                kvsMessageError("Cannot read <DataArray> for <Connection>.");
                return( false );
            }
        }
    }

    // <Vertex>
    kvs::kvsml::VertexTag vertex_tag;
    if ( !vertex_tag.read( line_object_tag.node() ) )
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
            size_t ncolors = vertex_tag.nvertices();
            if ( m_color_type == "line" )
            {
                if ( m_line_type == "strip" ) ncolors = vertex_tag.nvertices() - 1;
                else if ( m_line_type == "uniline" ) ncolors = line_tag.nlines() - 1;
                else if ( m_line_type == "polyline" ) ncolors = line_tag.nlines();
                else if ( m_line_type == "segment" ) ncolors = line_tag.nlines();
            }
            const size_t nchannels = 3;
            const size_t color_nelements = ncolors * nchannels;
            kvs::kvsml::DataArrayTag colors;
            if ( !colors.read( color_tag.node(), color_nelements, &m_colors ) )
            {
                kvsMessageError("Cannot read <DataArray> for <Color>.");
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
 *  @brief  Writes the KVSML line object.
 *  @param  filename [in] filename
 *  @return true, if the writing process is done successfully
 */
/*===========================================================================*/
const bool KVSMLObjectLine::write( const std::string& filename )
{
    m_filename = filename;

    kvs::XMLDocument document;
    document.InsertEndChild( kvs::XMLDeclaration("1.0") );
    document.InsertEndChild( kvs::XMLComment(" Generated by kvs::KVSMLObjectLine::write() ") );

    // <KVSML>
    kvs::kvsml::KVSMLTag kvsml_tag;
    if ( !kvsml_tag.write( &document ) )
    {
        kvsMessageError( "Cannot write <KVSML>." );
        return( false );
    }

    // <Object type="LineObject">
    kvs::kvsml::ObjectTag object_tag;
    object_tag.setType( "LineObject" );
    if ( !object_tag.write( kvsml_tag.node() ) )
    {
        kvsMessageError( "Cannot write <Object>." );
        return( false );
    }

    // <LineObject>
    kvs::kvsml::LineObjectTag line_object_tag;
    line_object_tag.setLineType( m_line_type );
    line_object_tag.setColorType( m_color_type );
    if ( !line_object_tag.write( object_tag.node() ) )
    {
        kvsMessageError( "Cannot write <LineObject>." );
        return( false );
    }

    // <Vertex nvertices="xxx">
    const size_t dimension = 3;
    kvs::kvsml::VertexTag vertex_tag;
    vertex_tag.setNVertices( m_coords.size() / dimension );
    if ( !vertex_tag.write( line_object_tag.node() ) )
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

    if ( m_connections.size() > 0 )
    {
        // <Line nlines="xxx">
        kvs::kvsml::LineTag line_tag;
        const size_t nlines = m_line_type == "uniline" ? m_connections.size() : m_connections.size() / 2;
        line_tag.setNLines( nlines );
        if ( !line_tag.write( line_object_tag.node() ) )
        {
            kvsMessageError( "Cannot write <Line>." );
            return( false );
        }

        // <Connection>
        kvs::kvsml::ConnectionTag connection_tag;
        if ( !connection_tag.write( line_tag.node() ) )
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

    return( document.write( m_filename ) );
}

/*===========================================================================*/
/**
 *  @brief  Checks the file extension.
 *  @param  filename [in] filename
 *  @return true, if the given filename has the supported extension
 */
/*===========================================================================*/
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

/*===========================================================================*/
/**
 *  @brief  Check the file format.
 *  @param  filename [in] filename
 *  @return true, if the KVSMLObjectLine class can read the given file
 */
/*===========================================================================*/
const bool KVSMLObjectLine::CheckFileFormat( const std::string& filename )
{
    kvs::XMLDocument document;
    if ( !document.read( filename ) ) return( false );

    // <KVSML>
    kvs::kvsml::KVSMLTag kvsml_tag;
    if ( !kvsml_tag.read( &document ) ) return( false );

    // <Object>
    kvs::kvsml::ObjectTag object_tag;
    if ( !object_tag.read( kvsml_tag.node() ) ) return( false );

    if ( object_tag.type() != "LineObject" ) return( false );

    // <LineObject>
    kvs::kvsml::LineObjectTag line_object_tag;
    if ( !line_object_tag.read( object_tag.node() ) ) return( false );

    return( true );
}

std::ostream& operator <<( std::ostream& os, const KVSMLObjectLine& rhs )
{
    os << "Line type:  "       << rhs.m_line_type << std::endl;
    os << "Color type: "       << rhs.m_color_type << std::endl;
    os << "Num. of vertices: " << rhs.m_coords.size() / 3 << std::endl;

    return( os );
}

} // end of namespace kvs
