/****************************************************************************/
/**
 *  @file PolygonObject.cpp
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
#include "PolygonObject.h"
#include <string>
#include <kvs/Assert>
#include <kvs/Type>


namespace
{

/*===========================================================================*/
/**
 *  @brief  Returns the name of the polygon type as string.
 *  @param  type [in] polygon type
 *  @return name of the polygon type
 */
/*===========================================================================*/
const std::string GetPolygonTypeName( const kvs::PolygonObject::PolygonType type )
{
    switch( type )
    {
    case kvs::PolygonObject::Triangle: return "triangle";
    case kvs::PolygonObject::Quadrangle: return "quadrangle";
    default: return "unknown polygon type";
    }
}

/*===========================================================================*/
/**
 *  @brief  Returns the name of the color type as string.
 *  @param  type [in] color type
 *  @return name of the color type
 */
/*===========================================================================*/
const std::string GetColorTypeName( const kvs::PolygonObject::ColorType type )
{
    switch( type )
    {
    case kvs::PolygonObject::VertexColor: return "vertex color";
    case kvs::PolygonObject::PolygonColor: return "polygon color";
    default: return "unknown color type";
    }
}

/*===========================================================================*/
/**
 *  @brief  Returns the name of the normal type as string.
 *  @param  type [in] normal type
 *  @return name of the normal type
 */
/*===========================================================================*/
const std::string GetNormalTypeName( const kvs::PolygonObject::NormalType type )
{
    switch( type )
    {
    case kvs::PolygonObject::VertexNormal: return "vertex normal";
    case kvs::PolygonObject::PolygonNormal: return "polygon normal";
    default: return "unknown normal type";
    }
}

} // end of namespace

namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Downcasts the object base to the polygon object.
 *  @param  object [in] pointer to the object base
 *  @return pointer to the polygon object
 */
/*===========================================================================*/
kvs::PolygonObject* PolygonObject::DownCast( kvs::ObjectBase* object )
{
    kvs::GeometryObjectBase* geometry = kvs::GeometryObjectBase::DownCast( object );
    if ( !geometry ) return NULL;

    const kvs::GeometryObjectBase::GeometryType type = geometry->geometryType();
    if ( type != kvs::GeometryObjectBase::Polygon )
    {
        kvsMessageError("Input object is not a polygon object.");
        return NULL;
    }

    kvs::PolygonObject* polygon = static_cast<kvs::PolygonObject*>( geometry );

    return polygon;
}

/*===========================================================================*/
/**
 *  @brief  Downcasts the object base to the polygon object with 'const'.
 *  @param  object [in] pointer to the object base
 *  @return pointer to the polygon object
 */
/*===========================================================================*/
const kvs::PolygonObject* PolygonObject::DownCast( const kvs::ObjectBase* object )
{
    return PolygonObject::DownCast( const_cast<kvs::ObjectBase*>( object ) );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new PolygonObject class.
 */
/*===========================================================================*/
PolygonObject::PolygonObject()
{
    this->setOpacity( 255 );
}

/*===========================================================================*/
/**
 *  @brief  Shallow copys.
 *  @param  object [in] polygon object
 */
/*===========================================================================*/
void PolygonObject::shallowCopy( const PolygonObject& object )
{
    BaseClass::shallowCopy( object );
    m_polygon_type = object.polygonType();
    m_color_type = object.colorType();
    m_normal_type = object.normalType();
    m_connections = object.connections();
    m_opacities = object.opacities();
}

/*===========================================================================*/
/**
 *  @brief  Deep copys.
 *  @param  object [in] polygon object
 */
/*===========================================================================*/
void PolygonObject::deepCopy( const PolygonObject& object )
{
    BaseClass::deepCopy( object );
    m_polygon_type = object.polygonType();
    m_color_type = object.colorType();
    m_normal_type = object.normalType();
    m_connections = object.connections().clone();
    m_opacities = object.opacities().clone();
}

/*===========================================================================*/
/**
 *  @brief  Clears the data of the polygon object.
 */
/*===========================================================================*/
void PolygonObject::clear()
{
    BaseClass::clear();
    m_connections.release();
    m_opacities.release();
}

/*===========================================================================*/
/**
 *  @brief  Prints information of the polygon object.
 *  @param  os [in] output stream
 *  @param  indent [in] indent
 */
/*===========================================================================*/
void PolygonObject::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Object type : " << "polygon object" << std::endl;
    BaseClass::print( os, indent );
    os << indent << "Number of connections : " << this->numberOfConnections() << std::endl;
    os << indent << "Number of opacities : " << this->numberOfOpacities() << std::endl;
    os << indent << "Polygon type : " << ::GetPolygonTypeName( this->polygonType() ) << std::endl;
    os << indent << "Color type : " << ::GetColorTypeName( this->colorType() ) << std::endl;
    os << indent << "Normal type : " << ::GetNormalTypeName( this->normalType() ) << std::endl;
}

/*===========================================================================*/
/**
 *  @brief  Sets a polygon type.
 *  @param  polygon_type [in] polygon type
 */
/*===========================================================================*/
void PolygonObject::setPolygonType( const PolygonType polygon_type )
{
    m_polygon_type = polygon_type;
}

/*===========================================================================*/
/**
 *  @brief  Sets a color type
 *  @param  color_type [in] color type
 */
/*===========================================================================*/
void PolygonObject::setColorType( const ColorType color_type )
{
    m_color_type = color_type;
}

/*===========================================================================*/
/**
 *  @brief  Sets a normal type.
 *  @param  normal_type [in] normal type
 */
/*===========================================================================*/
void PolygonObject::setNormalType( const NormalType normal_type )
{
    m_normal_type = normal_type;
}

/*===========================================================================*/
/**
 *  @brief  Sets a connection array.
 *  @param  connections [in] connection array
 */
/*===========================================================================*/
void PolygonObject::setConnections( const kvs::ValueArray<kvs::UInt32>& connections )
{
    m_connections = connections;
}

/*===========================================================================*/
/**
 *  @brief  Sets a color value.
 *  @param  color [in] color value
 */
/*===========================================================================*/
void PolygonObject::setColor( const kvs::RGBColor& color )
{
    BaseClass::setColor( color );

    m_color_type = PolygonObject::PolygonColor;
}

/*===========================================================================*/
/**
 *  @brief  Sets an opacity array.
 *  @param  opacities [in] opacity array
 */
/*===========================================================================*/
void PolygonObject::setOpacities( const kvs::ValueArray<kvs::UInt8>& opacities )
{
    m_opacities = opacities;
}

/*===========================================================================*/
/**
 *  @brief  Sets an opacity value.
 *  @param  opacity [in] opacity value
 */
/*===========================================================================*/
void PolygonObject::setOpacity( const kvs::UInt8 opacity )
{
    m_opacities.allocate( 1 );
    m_opacities[0] = opacity;
}

/*===========================================================================*/
/**
 *  @brief  Returns the geometry type.
 *  @return geometry type
 */
/*===========================================================================*/
PolygonObject::BaseClass::GeometryType PolygonObject::geometryType() const
{
    return BaseClass::Polygon;
}

/*===========================================================================*/
/**
 *  @brief  Returns the polygon type.
 *  @return polygon type
 */
/*===========================================================================*/
PolygonObject::PolygonType PolygonObject::polygonType() const
{
    return m_polygon_type;
}

/*===========================================================================*/
/**
 *  @brief  Returns the color type.
 *  @return color type
 */
/*===========================================================================*/
PolygonObject::ColorType PolygonObject::colorType() const
{
    return m_color_type;
}

/*===========================================================================*/
/**
 *  @brief  Returns the normal type.
 *  @return normal type
 */
/*===========================================================================*/
PolygonObject::NormalType PolygonObject::normalType() const
{
    return m_normal_type;
}

/*===========================================================================*/
/**
 *  @brief  Returns the number of connections.
 *  @return number of connections
 */
/*===========================================================================*/
size_t PolygonObject::numberOfConnections() const
{
    const size_t nvertices_per_face = m_polygon_type;
    return m_connections.size() / nvertices_per_face;
}

/*===========================================================================*/
/**
 *  @brief  Returns the number of opacity values.
 *  @return number of opacity values
 */
/*===========================================================================*/
size_t PolygonObject::numberOfOpacities() const
{
    return m_opacities.size();
}

/*===========================================================================*/
/**
 *  @brief  Returns the opacity specified by the index.
 *  @param  index [in] index of the opacity array
 *  @return opacity value
 */
/*===========================================================================*/
kvs::UInt8 PolygonObject::opacity( const size_t index ) const
{
    return m_opacities[index];
}

/*===========================================================================*/
/**
 *  @brief  Returns the connection array.
 *  @return connection array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::UInt32>& PolygonObject::connections() const
{
    return m_connections;
}

/*===========================================================================*/
/**
 *  @brief  Returns the opacity array.
 *  @return opacity array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::UInt8>& PolygonObject::opacities() const
{
    return m_opacities;
}

std::ostream& operator << ( std::ostream& os, const PolygonObject& object )
{
    os << "Object type:  " << "polygon object" << std::endl;
#ifdef KVS_COMPILER_VC
#if KVS_COMPILER_VERSION_LESS_OR_EQUAL( 8, 0 )
    // @TODO Cannot instance the object that is a abstract class here (error:C2259).
#endif
#else
    os << static_cast<const kvs::GeometryObjectBase&>( object ) << std::endl;
#endif
    os << "Number of connections:  " << object.numberOfConnections() << std::endl;
    os << "Number of opacities:  " << object.numberOfOpacities() << std::endl;
    os << "Polygon type:  " << ::GetPolygonTypeName( object.polygonType() ) << std::endl;
    os << "Color type:  " << ::GetColorTypeName( object.colorType() ) << std::endl;
    os << "Normal type:  " << ::GetNormalTypeName( object.normalType() );

    return os;
}

} // end of namespace kvs
