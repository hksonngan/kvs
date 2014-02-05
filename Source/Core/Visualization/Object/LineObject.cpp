/*****************************************************************************/
/**
 *  @file   LineObject.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include "LineObject.h"
#include <string>
#include <kvs/PolygonObject>
#include <kvs/Assert>
#include <kvs/Type>


namespace
{

/*===========================================================================*/
/**
 *  @brief  Returns the name of line type as string.
 *  @param  type [in] line type
 *  @return name of line type as string
 */
/*===========================================================================*/
const std::string GetLineTypeName( const kvs::LineObject::LineType type )
{
    switch( type )
    {
    case kvs::LineObject::Strip: return "strip";
    case kvs::LineObject::Uniline: return "uniline";
    case kvs::LineObject::Polyline: return "polyline";
    case kvs::LineObject::Segment: return "segment";
    default: return "unknown line type";
    }
}

/*===========================================================================*/
/**
 *  @brief  Returns the name of color type as string.
 *  @param  type [in] color type
 *  @return name of color type as string
 */
/*===========================================================================*/
const std::string GetColorTypeName( const kvs::LineObject::ColorType type )
{
    switch( type )
    {
    case kvs::LineObject::VertexColor: return "vertex color";
    case kvs::LineObject::LineColor: return "line color";
    default: return "unknown color type";
    }
}

} // end of namespace


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new LineObject class.
 */
/*===========================================================================*/
LineObject::LineObject()
{
    this->setSize( 1 );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new LineObject class.
 *  @param  polygon [in] polygon object
 */
/*===========================================================================*/
LineObject::LineObject( const kvs::PolygonObject& polygon )
{
    BaseClass::setCoords( polygon.coords() );

    if( polygon.colorType() == kvs::PolygonObject::VertexColor )
    {
        this->setColorType( LineObject::VertexColor );
        BaseClass::setColors( polygon.colors() );
    }
    else
    {
        this->setColorType( LineObject::LineColor );
        BaseClass::setColor( polygon.color() );
    }

    this->setSize( 1.0f );

    this->setLineType( LineObject::Segment );

    const size_t nconnections = polygon.numberOfConnections();
    const size_t ncorners = size_t( polygon.polygonType() );
    const size_t npolygons = ( nconnections == 0 ) ?
        polygon.numberOfVertices() / ncorners : nconnections;

    kvs::ValueArray<kvs::UInt32> connections( npolygons * ncorners * 2 );
    if ( nconnections > 0 )
    {
        size_t p_index = 0;
        size_t l_index = 0;
        for( size_t i = 0; i < npolygons; i++ )
        {
            for( size_t j = 0; j < ncorners; j++ )
            {
                connections[ l_index++ ] = polygon.connections().at( p_index++ );
                connections[ l_index ] = polygon.connections().at( j == ncorners - 1 ? p_index - ncorners * (i+1) : p_index );
            }
        }
    }
    else
    {
        size_t p_index = 0;
        size_t l_index = 0;
        for( size_t i = 0; i < npolygons; i++ )
        {
            for( size_t j = 0; j < ncorners; j++ )
            {
                connections[ l_index++ ] = p_index++;
                connections[ l_index ] = j == ncorners - 1 ? p_index - ncorners * (i+1) : p_index;
            }
        }
    }

    this->setConnections( connections );

    BaseClass::setMinMaxObjectCoords(
        polygon.minObjectCoord(),
        polygon.maxObjectCoord() );

    BaseClass::setMinMaxExternalCoords(
        polygon.minExternalCoord(),
        polygon.maxExternalCoord() );
}

/*===========================================================================*/
/**
 *  @brief  Shallow copys.
 *  @param  object [in] line object
 */
/*===========================================================================*/
void LineObject::shallowCopy( const LineObject& object )
{
    BaseClass::shallowCopy( object );
    m_line_type = object.lineType();
    m_color_type = object.colorType();
    m_connections = object.connections();
    m_sizes = object.sizes();
}

/*===========================================================================*/
/**
 *  @brief  Deep copys.
 *  @param  object [in] line object
 */
/*===========================================================================*/
void LineObject::deepCopy( const LineObject& object )
{
    BaseClass::deepCopy( object );
    m_line_type = object.lineType();
    m_color_type = object.colorType();
    m_connections = object.connections().clone();
    m_sizes = object.sizes().clone();
}

/*===========================================================================*/
/**
 *  @brief  Clears the data of the line object.
 */
/*===========================================================================*/
void LineObject::clear()
{
    BaseClass::clear();
    m_connections.release();
    m_sizes.release();
}

/*===========================================================================*/
/**
 *  @brief  Prints the information of the line object.
 *  @param  os [in] output stream
 *  @param  indent [in] indent
 */
/*===========================================================================*/
void LineObject::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Object type : " << "line object" << std::endl;
    BaseClass::print( os, indent );
    os << indent << "Number of connections : " << this->numberOfConnections() << std::endl;
    os << indent << "Number of sizes : " << this->numberOfSizes() << std::endl;
    os << indent << "Line type : " << ::GetLineTypeName( this->lineType() ) << std::endl;
    os << indent << "Color type : " << ::GetColorTypeName( this->colorType() ) << std::endl;
}

/*===========================================================================*/
/**
 *  @brief  Sets a line type.
 *  @param  line_type [in] line type
 */
/*===========================================================================*/
void LineObject::setLineType( const LineType line_type )
{
    m_line_type = line_type;
}

/*===========================================================================*/
/**
 *  @brief  Sets a color type.
 *  @param  color_type [in] color type
 */
/*===========================================================================*/
void LineObject::setColorType( const ColorType color_type )
{
    m_color_type = color_type;
}

/*===========================================================================*/
/**
 *  @brief  Sets a connection array.
 *  @param  connections [in] connection array
 */
/*===========================================================================*/
void LineObject::setConnections( const kvs::ValueArray<kvs::UInt32>& connections )
{
    m_connections = connections;
}

/*===========================================================================*/
/**
 *  @brief  Sets a color value.
 *  @param  color [in] color value
 */
/*===========================================================================*/
void LineObject::setColor( const kvs::RGBColor& color )
{
    BaseClass::setColor( color );

    m_color_type = LineObject::LineColor;
}

/*===========================================================================*/
/**
 *  @brief  Sets a size array.
 *  @param  sizes [in] size array
 */
/*===========================================================================*/
void LineObject::setSizes( const kvs::ValueArray<kvs::Real32>& sizes )
{
    m_sizes = sizes;
}

/*===========================================================================*/
/**
 *  @brief  Sets a size value.
 *  @param  size [in] size value
 */
/*===========================================================================*/
void LineObject::setSize( const kvs::Real32 size )
{
    m_sizes.allocate( 1 );
    m_sizes[0] = size;
}

/*===========================================================================*/
/**
 *  @brief  Returns the geometry type.
 *  @return geometry type
 */
/*===========================================================================*/
LineObject::BaseClass::GeometryType LineObject::geometryType() const
{
    return BaseClass::Line;
}

/*===========================================================================*/
/**
 *  @brief  Returns the line type.
 *  @return line type
 */
/*===========================================================================*/
LineObject::LineType LineObject::lineType() const
{
    return m_line_type;
}

/*===========================================================================*/
/**
 *  @brief  Returns the color type.
 *  @return color type
 */
/*===========================================================================*/
LineObject::ColorType LineObject::colorType() const
{
    return m_color_type;
}

/*===========================================================================*/
/**
 *  @brief  Returns the number of connections.
 *  @return number of connections
 */
/*===========================================================================*/
size_t LineObject::numberOfConnections() const
{
    return
        m_line_type == LineObject::Uniline ?
        m_connections.size() :
        m_connections.size() / 2;
}

/*===========================================================================*/
/**
 *  @brief  Returns the number of sizes.
 *  @return number of sizes
 */
/*===========================================================================*/
size_t LineObject::numberOfSizes() const
{
    return m_sizes.size();
}

/*===========================================================================*/
/**
 *  @brief  Returns the connection specified by the index.
 *  @param  index [in] index of connection array
 *  @return connection
 */
/*===========================================================================*/
const kvs::Vector2ui LineObject::connection( const size_t index ) const
{
    return kvs::Vector2ui( (unsigned int*)m_connections.data() + 2 * index );
}

/*===========================================================================*/
/**
 *  @brief  Returns the size.
 *  @param  index [in] index of size array
 *  @return size
 */
/*===========================================================================*/
kvs::Real32 LineObject::size( const size_t index ) const
{
    return m_sizes[index];
}

/*===========================================================================*/
/**
 *  @brief  Returns the connection array
 *  @return connection array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::UInt32>& LineObject::connections() const
{
    return m_connections;
}

/*===========================================================================*/
/**
 *  @brief  Returns the size array.
 *  @return size array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::Real32>& LineObject::sizes() const
{
    return m_sizes;
}

std::ostream& operator << ( std::ostream& os, const LineObject& object )
{
    os << "Object type:  " << "line object" << std::endl;
#ifdef KVS_COMPILER_VC
#if KVS_COMPILER_VERSION_LESS_OR_EQUAL( 8, 0 )
    // @TODO Cannot instance the object that is a abstract class here (error:C2259).
#endif
#else
    os << static_cast<const kvs::GeometryObjectBase&>( object ) << std::endl;
#endif
    os << "Number of connections:  " << object.numberOfConnections() << std::endl;
    os << "Number of sizes:  " << object.numberOfSizes() << std::endl;
    os << "Line type:  " << ::GetLineTypeName( object.lineType() ) << std::endl;
    os << "Color type:  " << ::GetColorTypeName( object.colorType() );

    return os;
}

} // end of namespace kvs
