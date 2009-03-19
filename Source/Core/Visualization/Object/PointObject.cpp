/****************************************************************************/
/**
 *  @file PointObject.cpp
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
#include "PointObject.h"
#include "LineObject.h"
#include "PolygonObject.h"
#include <kvs/Assert>


namespace kvs
{

PointObject::PointObject( void )
{
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::ValueArray<kvs::UInt8>&  colors,
    const kvs::ValueArray<kvs::Real32>& normals,
    const kvs::ValueArray<kvs::Real32>& sizes ):
    kvs::GeometryObjectBase( coords, colors, normals )
{
    this->setSizes( sizes );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::ValueArray<kvs::UInt8>&  colors,
    const kvs::ValueArray<kvs::Real32>& normals,
    const kvs::Real32                   size ):
    kvs::GeometryObjectBase( coords, colors, normals )
{
    this->setSize( size );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::RGBColor&                color,
    const kvs::ValueArray<kvs::Real32>& normals,
    const kvs::ValueArray<kvs::Real32>& sizes ):
    kvs::GeometryObjectBase( coords, color, normals )
{
    this->setSizes( sizes );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::ValueArray<kvs::Real32>& normals,
    const kvs::ValueArray<kvs::Real32>& sizes ):
    kvs::GeometryObjectBase( coords, normals )
{
    this->setSizes( sizes );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::RGBColor&                color,
    const kvs::ValueArray<kvs::Real32>& normals,
    const kvs::Real32                   size ):
    kvs::GeometryObjectBase( coords, color, normals )
{
    this->setSize( size );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::ValueArray<kvs::UInt8>&  colors,
    const kvs::ValueArray<kvs::Real32>& sizes ):
    kvs::GeometryObjectBase( coords, colors )
{
    this->setSizes( sizes );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::RGBColor&                color,
    const kvs::ValueArray<kvs::Real32>& sizes ):
    kvs::GeometryObjectBase( coords, color )
{
    KVS_ASSERT( coords.size() == sizes.size() * 3 );

    this->setSizes( sizes );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::ValueArray<kvs::UInt8>&  colors,
    const kvs::Real32                   size ):
    kvs::GeometryObjectBase( coords, colors )
{
    this->setSize( size );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::RGBColor&                color,
    const kvs::Real32                   size ):
    kvs::GeometryObjectBase( coords, color )
{
    this->setSize( size );
}

PointObject::PointObject(
    const kvs::ValueArray<kvs::Real32>& coords ):
    kvs::GeometryObjectBase( coords )
{
    this->setSize( 1 );
}

PointObject::PointObject( const kvs::LineObject* line )
{
    BaseClass::setCoords( line->coords() );

    if( line->colorType() == kvs::LineObject::VertexColor )
    {
        BaseClass::setColors( line->colors() );
    }
    else
    {
        BaseClass::setColor( line->color() );
    }

    this->setSize( line->size() );

    BaseClass::setMinMaxObjectCoords(
        line->minObjectCoord(),
        line->maxObjectCoord() );

    BaseClass::setMinMaxExternalCoords(
        line->minExternalCoord(),
        line->maxExternalCoord() );
}

PointObject::PointObject( const kvs::PolygonObject* polygon )
{
    BaseClass::setCoords( polygon->coords() );

    if( polygon->colorType() == kvs::PolygonObject::VertexColor )
    {
        BaseClass::setColors( polygon->colors() );
    }
    else
    {
        BaseClass::setColor( polygon->color() );
    }

    if( polygon->normalType() == kvs::PolygonObject::VertexNormal )
    {
        BaseClass::setNormals( polygon->normals() );
    }

    this->setSize( 1.0f );

    BaseClass::setMinMaxObjectCoords(
        polygon->minObjectCoord(),
        polygon->maxObjectCoord() );

    BaseClass::setMinMaxExternalCoords(
        polygon->minExternalCoord(),
        polygon->maxExternalCoord() );
}

PointObject::~PointObject( void )
{
    this->clear();
}

kvs::PointObject* PointObject::DownCast( kvs::ObjectBase* object )
{
    kvs::GeometryObjectBase* geometry = kvs::GeometryObjectBase::DownCast( object );
    if ( !geometry ) return( NULL );

    const kvs::GeometryObjectBase::GeometryType type = geometry->geometryType();
    if ( type != kvs::GeometryObjectBase::Point )
    {
        kvsMessageError("Input object is not a point object.");
        return( NULL );
    }

    kvs::PointObject* point = static_cast<kvs::PointObject*>( geometry );

    return( point );
}

const kvs::PointObject* PointObject::DownCast( const kvs::ObjectBase* object )
{
    return( PointObject::DownCast( const_cast<kvs::ObjectBase*>( object ) ) );
}

std::ostream& operator << ( std::ostream& os, const PointObject& object )
{
    os << "Object type:  " << "point object" << std::endl;
#ifdef KVS_COMPILER_VC
#if KVS_COMPILER_VERSION_LESS_OR_EQUAL( 8, 0 )
    // @TODO Cannot instance the object that is a abstract class here (error:C2259).
#endif
#else
    os << static_cast<const kvs::GeometryObjectBase&>( object ) << std::endl;
#endif
    os << "Number of sizes:  " << object.nsizes();

    return( os );
}

void PointObject::clear( void )
{
    BaseClass::clear();
    m_sizes.deallocate();
}

void PointObject::setSizes( const kvs::ValueArray<kvs::Real32>& sizes )
{
    m_sizes = sizes;
}

void PointObject::setSize( const kvs::Real32 size )
{
    m_sizes.allocate( 1 );
    m_sizes[0] = size;
}

const PointObject::BaseClass::GeometryType PointObject::geometryType( void ) const
{
    return( BaseClass::Point );
}

const size_t PointObject::nsizes( void ) const
{
    return( m_sizes.size() );
}

const kvs::Real32 PointObject::size( const size_t index ) const
{
    return( m_sizes[index] );
}

const kvs::ValueArray<kvs::Real32>& PointObject::sizes( void ) const
{
    return( m_sizes );
}

} // end of namespace kvs
