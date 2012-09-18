/****************************************************************************/
/**
 *  @file KVSMLObjectLine.cpp
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
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
#include "DataReader.h"
#include "DataWriter.h"
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
 *  @brief  Checks the file extension.
 *  @param  filename [in] filename
 *  @return true, if the given filename has the supported extension
 */
/*===========================================================================*/
bool KVSMLObjectLine::CheckFileExtension( const std::string& filename )
{
    const kvs::File file( filename );
    if ( file.extension() == "kvsml" ||
         file.extension() == "KVSML" ||
         file.extension() == "xml"   ||
         file.extension() == "XML" )
    {
        return true;
    }

    return false;
}

/*===========================================================================*/
/**
 *  @brief  Check the file format.
 *  @param  filename [in] filename
 *  @return true, if the KVSMLObjectLine class can read the given file
 */
/*===========================================================================*/
bool KVSMLObjectLine::CheckFileFormat( const std::string& filename )
{
    kvs::XMLDocument document;
    if ( !document.read( filename ) ) return false;

    // <KVSML>
    kvs::kvsml::KVSMLTag kvsml_tag;
    if ( !kvsml_tag.read( &document ) ) return false;

    // <Object>
    kvs::kvsml::ObjectTag object_tag;
    if ( !object_tag.read( kvsml_tag.node() ) ) return false;
    if ( object_tag.type() != "LineObject" ) return false;

    // <LineObject>
    kvs::kvsml::LineObjectTag line_object_tag;
    if ( !line_object_tag.read( object_tag.node() ) ) return false;

    return true;
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new KVSML line object class.
 */
/*===========================================================================*/
KVSMLObjectLine::KVSMLObjectLine():
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
    this->read( filename );
}

/*===========================================================================*/
/**
 *  @brief  Destructs the KVSML line object class.
 */
/*===========================================================================*/
KVSMLObjectLine::~KVSMLObjectLine()
{
}

/*===========================================================================*/
/**
 *  @brief  Returns the KVSML tag.
 *  @return KVSML tag
 */
/*===========================================================================*/
const kvs::kvsml::KVSMLTag& KVSMLObjectLine::KVSMLTag() const
{
    return m_kvsml_tag;
}

/*===========================================================================*/
/**
 *  @brief  Returns the object tag.
 *  @return object tag
 */
/*===========================================================================*/
const kvs::kvsml::ObjectTag& KVSMLObjectLine::objectTag() const
{
    return m_object_tag;
}

/*===========================================================================*/
/**
 *  @brief  Returns the line type.
 *  @return line type
 */
/*===========================================================================*/
const std::string& KVSMLObjectLine::lineType() const
{
    return m_line_type;
}

/*===========================================================================*/
/**
 *  @brief  Returns the color type.
 *  @return color type
 */
/*===========================================================================*/
const std::string& KVSMLObjectLine::colorType() const
{
    return m_color_type;
}

/*===========================================================================*/
/**
 *  @brief  Returns the coordinate value array.
 *  @return coordinate value array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::Real32>& KVSMLObjectLine::coords() const
{
    return m_coords;
}

/*===========================================================================*/
/**
 *  @brief  Returns the color value array.
 *  @return color value array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::UInt8>& KVSMLObjectLine::colors() const
{
    return m_colors;
}

/*===========================================================================*/
/**
 *  @brief  Returns the connection data array.
 *  @return connection data array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::UInt32>& KVSMLObjectLine::connections() const
{
    return m_connections;
}

/*===========================================================================*/
/**
 *  @brief  Returns the size value array.
 *  @return size value array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::Real32>& KVSMLObjectLine::sizes() const
{
    return m_sizes;
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

void KVSMLObjectLine::print( std::ostream& os, const size_t indent ) const
{
    const std::string blanks( indent, ' ' );
    os << blanks << "Filename : " << BaseClass::filename() << std::endl;
    os << blanks << "Line type : " << m_line_type << std::endl;
    os << blanks << "Color type : " << m_color_type << std::endl;
    os << blanks << "Number of vertices : " << m_coords.size() / 3 << std::endl;
}

/*===========================================================================*/
/**
 *  @brief  Reads a KVSML line object file.
 *  @param  filename [in] filename
 *  @return true, if the reading process is done successfully
 */
/*===========================================================================*/
bool KVSMLObjectLine::read( const std::string& filename )
{
    BaseClass::setFilename( filename );
    BaseClass::setSuccess( true );

    // XML document.
    kvs::XMLDocument document;
    if ( !document.read( filename ) )
    {
        kvsMessageError( "%s", document.ErrorDesc().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }

    // <KVSML>
    if ( !m_kvsml_tag.read( &document ) )
    {
        kvsMessageError( "Cannot read <%s>.", m_kvsml_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }

    // <Object>
    if ( !m_object_tag.read( m_kvsml_tag.node() ) )
    {
        kvsMessageError( "Cannot read <%s>.", m_object_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }

    // <LineObject>
    kvs::kvsml::LineObjectTag line_object_tag;
    if ( !line_object_tag.read( m_object_tag.node() ) )
    {
        kvsMessageError( "Cannot read <%s>.", line_object_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
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

    // <Vertex>
    kvs::kvsml::VertexTag vertex_tag;
    if ( !vertex_tag.read( line_object_tag.node() ) )
    {
        kvsMessageError( "Cannot read <%s>.", vertex_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }
    else
    {
        // Parent node.
        const kvs::XMLNode::SuperClass* parent = vertex_tag.node();

        // <Coord>
        const size_t ncoords = vertex_tag.nvertices();
        if ( !kvs::kvsml::ReadCoordData( parent, ncoords, &m_coords ) ) 
        {
            BaseClass::setSuccess( false );
            return false;
        }

        if ( m_coords.size() == 0 )
        {
            kvsMessageError( "Cannot read the coord data." );
            return false;
        }

        // <Color>
        if ( m_color_type == "vertex" )
        {
            const size_t ncolors = vertex_tag.nvertices();
            if ( !kvs::kvsml::ReadColorData( parent, ncolors, &m_colors ) )
            {
                BaseClass::setSuccess( false );
                return false;
            }
        }
        if ( m_colors.size() == 0 )
        {
            // default value (black).
            m_colors.allocate(3);
            m_colors[0] = 0;
            m_colors[1] = 0;
            m_colors[2] = 0;
        }

        // <Size>
        // WARNING: This tag should be described under <Line> since the size that is
        // described in <Size> represents the line size not the vertex size. Therefore,
        // we recommend that the size is described under <Line> not under <Vertex>.
        // Current version of KVSML tentative supports both of the descriptions for the
        // size in order to maintain backward compatibility.
        const size_t nsizes = vertex_tag.nvertices();
        if ( !kvs::kvsml::ReadSizeData( parent, nsizes, &m_sizes ) )
        {
            BaseClass::setSuccess( false );
            return false;
        }

        if ( m_sizes.size() == 0 )
        {
            // default value (1).
            m_sizes.allocate(1);
            m_sizes[0] = 1;
        }
    }

    // <Line>
    kvs::kvsml::LineTag line_tag;
    if ( line_tag.isExisted( line_object_tag.node() ) )
    {
        if ( !line_tag.read( line_object_tag.node() ) )
        {
            kvsMessageError( "Cannot read <%s>.", line_tag.name().c_str() );
            BaseClass::setSuccess( false );
            return false;
        }
        else
        {
            // Parent node.
            const kvs::XMLNode::SuperClass* parent = line_tag.node();
            const size_t nvertices = vertex_tag.nvertices();
            const size_t nlines = line_tag.nlines();

            // <Size>
            const size_t nsizes = nlines;
            if ( !kvs::kvsml::ReadSizeData( parent, nsizes, &m_sizes ) )
            {
                BaseClass::setSuccess( false );
                return false;
            }

            if ( m_sizes.size() == 0 )
            {
                // default value (1).
                m_sizes.allocate(1);
                m_sizes[0] = 1;
            }

            // <Color>
            if ( m_color_type == "line" )
            {
                const size_t ncolors =
                    ( m_line_type == "strip"    ) ? nvertices - 1 :
                    ( m_line_type == "uniline"  ) ? nlines - 1 :
                    ( m_line_type == "polyline" ) ? nlines :
                    ( m_line_type == "segment"  ) ? nlines : 0;
                if ( !kvs::kvsml::ReadColorData( parent, ncolors, &m_colors ) )
                {
                    BaseClass::setSuccess( false );
                    return false;
                }
            }

            if ( m_colors.size() == 0 )
            {
                // default value (black).
                m_colors.allocate(3);
                m_colors[0] = 0;
                m_colors[1] = 0;
                m_colors[2] = 0;
            }

            // <Connection>
            if ( m_line_type != "strip" )
            {
                const size_t nconnections =
                    ( m_line_type == "uniline"  ) ? nlines :
                    ( m_line_type == "polyline" ) ? nlines * 2 :
                    ( m_line_type == "segment"  ) ? nlines * 2 : 0;
                if ( !kvs::kvsml::ReadConnectionData( parent, nconnections, &m_connections ) )
                {
                    BaseClass::setSuccess( false );
                    return false;
                }
            }

        }
    }
    else
    {
        if ( m_line_type != "strip" || m_color_type == "line" )
        {
            kvsMessageError( "Cannot find <%s>.", line_tag.name().c_str() );
            BaseClass::setSuccess( false );
            return false;
        }
    }

    return true;
}

/*===========================================================================*/
/**
 *  @brief  Writes the KVSML line object.
 *  @param  filename [in] filename
 *  @return true, if the writing process is done successfully
 */
/*===========================================================================*/
bool KVSMLObjectLine::write( const std::string& filename )
{
    BaseClass::setFilename( filename );
    BaseClass::setSuccess( true );

    kvs::XMLDocument document;
    document.InsertEndChild( kvs::XMLDeclaration("1.0") );
    document.InsertEndChild( kvs::XMLComment(" Generated by kvs::KVSMLObjectLine::write() ") );

    // <KVSML>
    kvs::kvsml::KVSMLTag kvsml_tag;
    if ( !kvsml_tag.write( &document ) )
    {
        kvsMessageError( "Cannot write <%s>.", kvsml_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }

    // <Object type="LineObject">
    kvs::kvsml::ObjectTag object_tag;
    object_tag.setType( "LineObject" );
    if ( !object_tag.write( kvsml_tag.node() ) )
    {
        kvsMessageError( "Cannot write <%s>.", object_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }

    // <LineObject>
    kvs::kvsml::LineObjectTag line_object_tag;
    line_object_tag.setLineType( m_line_type );
    line_object_tag.setColorType( m_color_type );
    if ( !line_object_tag.write( object_tag.node() ) )
    {
        kvsMessageError( "Cannot write <%s>.", line_object_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }

    const size_t dimension = 3;
    const size_t nvertices = m_coords.size() / dimension;

    // <Vertex nvertices="xxx">
    kvs::kvsml::VertexTag vertex_tag;
    vertex_tag.setNVertices( nvertices );
    if ( !vertex_tag.write( line_object_tag.node() ) )
    {
        kvsMessageError( "Cannot write <%s>.", vertex_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }
    else
    {
        // Parent node and writing data type.
        kvs::XMLNode::SuperClass* parent = vertex_tag.node();
        const kvs::kvsml::WritingDataType type = static_cast<kvs::kvsml::WritingDataType>(m_writing_type);

        // <Coord>
        if ( !kvs::kvsml::WriteCoordData( parent, type, filename, m_coords ) )
        {
            BaseClass::setSuccess( false );
            return false;
        }

        // <Color>
        if ( m_color_type == "vertex" )
        {
            if ( !kvs::kvsml::WriteColorData( parent, type, filename, m_colors ) )
            {
                BaseClass::setSuccess( false );
                return false;
            }
        }
    }

    // <Line nlines="xxx">
    if ( m_color_type == "line" || m_sizes.size() > 0 || m_connections.size() > 0 )
    {
        const size_t nconnections = m_connections.size();
        const size_t nlines =
            ( m_line_type == "strip"   ) ? nvertices - 1 :
            ( m_line_type == "uniline" ) ? nconnections : nconnections / 2;

        kvs::kvsml::LineTag line_tag;
        line_tag.setNLines( nlines );
        if ( !line_tag.write( line_object_tag.node() ) )
        {
            kvsMessageError( "Cannot write <%s>.", line_tag.name().c_str() );
            BaseClass::setSuccess( false );
            return false;
        }

        // Parent node and writing data type.
        kvs::XMLNode::SuperClass* parent = line_tag.node();
        const kvs::kvsml::WritingDataType type = static_cast<kvs::kvsml::WritingDataType>(m_writing_type);

        // <Connection>
        if ( !kvs::kvsml::WriteConnectionData( parent, type, filename, m_connections ) )
        {
            BaseClass::setSuccess( false );
            return false;
        }

        // <Size>
        if ( !kvs::kvsml::WriteSizeData( parent, type, filename, m_sizes ) )
        {
            BaseClass::setSuccess( false );
            return false;
        }

        // <Color>
        if ( m_color_type == "line" )
        {
            if ( !kvs::kvsml::WriteColorData( parent, type, filename, m_colors ) )
            {
                BaseClass::setSuccess( false );
                return false;
            }
        }
    }

    const bool success = document.write( filename );
    BaseClass::setSuccess( success );

    return success;
}

} // end of namespace kvs
