/****************************************************************************/
/**
 *  @file PointObject.h
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
#ifndef KVS__POINT_OBJECT_H_INCLUDE
#define KVS__POINT_OBJECT_H_INCLUDE

#include <kvs/GeometryObjectBase>
#include <kvs/ClassName>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/Vector3>
#include <kvs/RGBColor>
#include <kvs/Module>
#include <kvs/Deprecated>


namespace kvs
{

class LineObject;
class PolygonObject;

/*==========================================================================*/
/**
 *  Point object class.
 */
/*==========================================================================*/
class PointObject : public kvs::GeometryObjectBase
{
    kvsClassName( kvs::PointObject );
    kvsModuleCategory( Object );
    kvsModuleBaseClass( kvs::GeometryObjectBase );

protected:

    kvs::ValueArray<kvs::Real32> m_sizes; ///< size array

public:

    static kvs::PointObject* DownCast( kvs::ObjectBase* object );
    static const kvs::PointObject* DownCast( const kvs::ObjectBase* object );

public:

    PointObject();
    explicit PointObject( const kvs::LineObject& line );
    explicit PointObject( const kvs::PolygonObject& polygon );

    friend std::ostream& operator << ( std::ostream& os, const PointObject& object );

    void add( const PointObject& other );
    void shallowCopy( const PointObject& other );
    void deepCopy( const PointObject& other );
    void clear();

    void setSizes( const kvs::ValueArray<kvs::Real32>& sizes );
    void setSize( const kvs::Real32 size );

    BaseClass::GeometryType geometryType() const;
    size_t numberOfSizes() const;

    kvs::Real32 size( const size_t index = 0 ) const;
    const kvs::ValueArray<kvs::Real32>& sizes() const;

public:
    KVS_DEPRECATED( PointObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt8>& colors,
                        const kvs::ValueArray<kvs::Real32>& normals,
                        const kvs::ValueArray<kvs::Real32>& sizes ) )
    {
        this->setCoords( coords );
        this->setColors( colors );
        this->setNormals( normals );
        this->setSizes( sizes );
    }

    KVS_DEPRECATED( PointObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt8>& colors,
                        const kvs::ValueArray<kvs::Real32>& normals,
                        const kvs::Real32 size ) )
    {
        this->setCoords( coords );
        this->setColors( colors );
        this->setNormals( normals );
        this->setSize( size );
    }

    KVS_DEPRECATED( PointObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::RGBColor& color,
                        const kvs::ValueArray<kvs::Real32>& normals,
                        const kvs::ValueArray<kvs::Real32>& sizes ) )
    {
        this->setCoords( coords );
        this->setColor( color );
        this->setNormals( normals );
        this->setSizes( sizes );
    }

    KVS_DEPRECATED( PointObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::Real32>& normals,
                        const kvs::ValueArray<kvs::Real32>& sizes ) )
    {
        this->setCoords( coords );
        this->setNormals( normals );
        this->setSizes( sizes );
    }

    KVS_DEPRECATED( PointObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::RGBColor& color,
                        const kvs::ValueArray<kvs::Real32>& normals,
                        const kvs::Real32 size ) )
    {
        this->setCoords( coords );
        this->setColor( color );
        this->setNormals( normals );
        this->setSize( size );
    }

    KVS_DEPRECATED( PointObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt8>& colors,
                        const kvs::ValueArray<kvs::Real32>& sizes ) )
    {
        this->setCoords( coords );
        this->setColors( colors );
        this->setSizes( sizes );
    }

    KVS_DEPRECATED( PointObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::RGBColor& color,
                        const kvs::ValueArray<kvs::Real32>& sizes ) )
    {
        this->setCoords( coords );
        this->setColor( color );
        this->setSizes( sizes );
    }

    KVS_DEPRECATED( PointObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt8>&  colors,
                        const kvs::Real32 size ) )
    {
        this->setCoords( coords );
        this->setColors( colors );
        this->setSize( size );
    }

    KVS_DEPRECATED( PointObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::RGBColor& color,
                        const kvs::Real32 size ) )
    {
        this->setCoords( coords );
        this->setColor( color );
        this->setSize( size );
    }

    KVS_DEPRECATED( PointObject(
                        const kvs::ValueArray<kvs::Real32>& coords ) )
    {
        this->setCoords( coords );
        this->setColor( kvs::RGBColor( 255, 255, 255 ) );
        this->setSize( 1 );
    }

    KVS_DEPRECATED( PointObject& operator += ( const PointObject& other ) )
    {
        this->add( other );
        return( *this );
    }

    KVS_DEPRECATED( size_t nsizes() const ) { return this->numberOfSizes(); }
};

} // end of namespace kvs

#endif // KVS__POINT_OBJECT_H_INCLUDE
