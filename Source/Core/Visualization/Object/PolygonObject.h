/****************************************************************************/
/**
 *  @file   PolygonObject.h
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
/****************************************************************************/
#ifndef KVS__POLYGON_OBJECT_H_INCLUDE
#define KVS__POLYGON_OBJECT_H_INCLUDE

#include <ostream>
#include <kvs/GeometryObjectBase>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/Vector3>
#include <kvs/RGBColor>
#include <kvs/Module>
#include <kvs/Indent>
#include <kvs/Deprecated>


namespace kvs
{

/*==========================================================================*/
/**
 *  Polygon object class.
 */
/*==========================================================================*/
class PolygonObject : public kvs::GeometryObjectBase
{
    kvsModule( Object, kvs::PolygonObject, kvs::GeometryObjectBase );
    kvsModuleBaseClass( kvs::GeometryObjectBase );

public:

    enum PolygonType
    {
        Triangle   = 3,
        Quadrangle = 4,
        Tri        = Triangle,
        Quad       = Quadrangle,
        UnknownPolygonType
    };

    enum ColorType
    {
        VertexColor  = 0,
        PolygonColor = 1,
        UnknownColorType
    };

    enum NormalType
    {
        VertexNormal  = 0,
        PolygonNormal = 1,
        UnknownNormalType
    };

private:

    PolygonType m_polygon_type; ///< polygon type
    ColorType m_color_type; ///< polygon color type
    NormalType m_normal_type; ///< polygon normal type
    kvs::ValueArray<kvs::UInt32> m_connections; ///< connection array
    kvs::ValueArray<kvs::UInt8> m_opacities; ///< opacity array

public:

//    static kvs::PolygonObject* DownCast( kvs::ObjectBase* object );
//    static const kvs::PolygonObject* DownCast( const kvs::ObjectBase* object );

public:

    PolygonObject();

    void shallowCopy( const PolygonObject& object );
    void deepCopy( const PolygonObject& object );
    void clear();
    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;

    void setPolygonType( const PolygonType polygon_type );
    void setColorType( const ColorType color_type );
    void setNormalType( const NormalType normal_type );
    void setConnections( const kvs::ValueArray<kvs::UInt32>& connections );
    void setColor( const kvs::RGBColor& color );
    void setOpacities( const kvs::ValueArray<kvs::UInt8>& opacities );
    void setOpacity( const kvs::UInt8 opacity );

    BaseClass::GeometryType geometryType() const;
    PolygonType polygonType() const;
    ColorType colorType() const;
    NormalType normalType() const;
    size_t numberOfConnections() const;
    size_t numberOfOpacities() const;
    kvs::UInt8 opacity( const size_t index = 0 ) const;

    const kvs::ValueArray<kvs::UInt32>& connections() const;
    const kvs::ValueArray<kvs::UInt8>& opacities() const;

public:
    KVS_DEPRECATED( PolygonObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt32>& connections,
                        const kvs::ValueArray<kvs::UInt8>& colors,
                        const kvs::ValueArray<kvs::UInt8>& opacities,
                        const kvs::ValueArray<kvs::Real32>& normals,
                        const PolygonType polygon_type,
                        const ColorType color_type,
                        const NormalType normal_type ) )
    {
        this->setCoords( coords );
        this->setColors( colors );
        this->setNormals( normals );
        this->setPolygonType( polygon_type );
        this->setColorType( color_type );
        this->setNormalType( normal_type );
        this->setConnections( connections );
        this->setOpacities( opacities );
    }

    KVS_DEPRECATED( PolygonObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt32>& connections,
                        const kvs::ValueArray<kvs::UInt8>& colors,
                        const kvs::UInt8& opacity,
                        const kvs::ValueArray<kvs::Real32>& normals,
                        const PolygonType polygon_type,
                        const ColorType color_type,
                        const NormalType normal_type ) )
    {
        this->setCoords( coords );
        this->setColors( colors );
        this->setNormals( normals );
        this->setPolygonType( polygon_type );
        this->setColorType( color_type );
        this->setNormalType( normal_type );
        this->setConnections( connections );
        this->setOpacity( opacity );
    }

    KVS_DEPRECATED( PolygonObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt32>& connections,
                        const kvs::RGBColor& color,
                        const kvs::ValueArray<kvs::UInt8>& opacities,
                        const kvs::ValueArray<kvs::Real32>& normals,
                        const PolygonType polygon_type,
                        const NormalType normal_type ) )
    {
        this->setCoords( coords );
        this->setColor( color );
        this->setNormals( normals );
        this->setPolygonType( polygon_type );
        this->setColorType( PolygonObject::PolygonColor );
        this->setNormalType( normal_type );
        this->setConnections( connections );
        this->setOpacities( opacities );
    }

    KVS_DEPRECATED( PolygonObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt32>& connections,
                        const kvs::RGBColor& color,
                        const kvs::UInt8& opacity,
                        const kvs::ValueArray<kvs::Real32>& normals,
                        const PolygonType polygon_type,
                        const NormalType normal_type ) )
    {
        this->setCoords( coords );
        this->setColor( color );
        this->setNormals( normals );
        this->setPolygonType( polygon_type );
        this->setColorType( PolygonObject::PolygonColor );
        this->setNormalType( normal_type );
        this->setConnections( connections );
        this->setOpacity( opacity );
    }

    KVS_DEPRECATED( PolygonObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt8>& colors,
                        const kvs::ValueArray<kvs::UInt8>& opacities,
                        const kvs::ValueArray<kvs::Real32>& normals,
                        const PolygonType polygon_type,
                        const ColorType color_type,
                        const NormalType normal_type ) )
    {
        this->setCoords( coords );
        this->setColors( colors );
        this->setNormals( normals );
        this->setPolygonType( polygon_type );
        this->setColorType( color_type );
        this->setNormalType( normal_type );
        this->setOpacities( opacities );
    }

    KVS_DEPRECATED( PolygonObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt8>& colors,
                        const kvs::UInt8& opacity,
                        const kvs::ValueArray<kvs::Real32>& normals,
                        const PolygonType polygon_type,
                        const ColorType color_type,
                        const NormalType normal_type ) )
    {
        this->setCoords( coords );
        this->setColors( colors );
        this->setNormals( normals );
        this->setPolygonType( polygon_type );
        this->setColorType( color_type );
        this->setNormalType( normal_type );
        this->setOpacity( opacity );
    }

    KVS_DEPRECATED( PolygonObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::RGBColor& color,
                        const kvs::ValueArray<kvs::UInt8>& opacities,
                        const kvs::ValueArray<kvs::Real32>& normals,
                        const PolygonType polygon_type,
                        const NormalType normal_type ) )
    {
        this->setCoords( coords );
        this->setColor( color );
        this->setNormals( normals );
        this->setPolygonType( polygon_type );
        this->setColorType( PolygonObject::PolygonColor );
        this->setNormalType( normal_type );
        this->setOpacities( opacities );
    }

    KVS_DEPRECATED( PolygonObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::RGBColor& color,
                        const kvs::UInt8& opacity,
                        const kvs::ValueArray<kvs::Real32>& normals,
                        const PolygonType polygon_type,
                        const NormalType normal_type ) )
    {
        this->setCoords( coords );
        this->setColor( color );
        this->setNormals( normals );
        this->setPolygonType( polygon_type );
        this->setColorType( PolygonObject::PolygonColor );
        this->setNormalType( normal_type );
        this->setOpacity( opacity );
    }

    KVS_DEPRECATED( size_t nconnections() const ) { return this->numberOfConnections(); }
    KVS_DEPRECATED( size_t nopacities() const ) { return this->numberOfOpacities(); }
    KVS_DEPRECATED( friend std::ostream& operator << ( std::ostream& os, const PolygonObject& object ) );
};

} // end of namespace kvs

#endif // KVS__POLYGON_OBJECT_H_INCLUDE
