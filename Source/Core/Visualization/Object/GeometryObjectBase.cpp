/****************************************************************************/
/**
 *  @file GeometryObjectBase.cpp
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
#include "GeometryObjectBase.h"
#include <kvs/Assert>


namespace kvs
{

GeometryObjectBase::GeometryObjectBase( void )
{
}

GeometryObjectBase::GeometryObjectBase(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::ValueArray<kvs::UInt8>&  colors,
    const kvs::ValueArray<kvs::Real32>& normals )
{
    KVS_ASSERT( coords.size() == normals.size() );
    KVS_ASSERT( coords.size() == colors.size() );

    this->setCoords( coords );
    this->setColors( colors );
    this->setNormals( normals );
}

GeometryObjectBase::GeometryObjectBase(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::RGBColor&                color,
    const kvs::ValueArray<kvs::Real32>& normals )
{
    KVS_ASSERT( coords.size() == normals.size() );

    this->setCoords( coords );
    this->setColor( color );
    this->setNormals( normals );
}

GeometryObjectBase::GeometryObjectBase(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::ValueArray<kvs::Real32>& normals )
{
    KVS_ASSERT( coords.size() == normals.size() );

    this->setCoords( coords );
    this->setNormals( normals );
}

GeometryObjectBase::GeometryObjectBase(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::ValueArray<kvs::UInt8>&  colors )
{
    KVS_ASSERT( coords.size() == colors.size() );

    this->setCoords( coords );
    this->setColors( colors );
}

GeometryObjectBase::GeometryObjectBase(
    const kvs::ValueArray<kvs::Real32>& coords,
    const kvs::RGBColor&                color )
{
    this->setCoords( coords );
    this->setColor( color );
}

GeometryObjectBase::GeometryObjectBase(
    const kvs::ValueArray<kvs::Real32>& coords )
{
    this->setCoords( coords );
    this->setColor( kvs::RGBColor( 255, 255, 255 ) );
}

GeometryObjectBase::~GeometryObjectBase( void )
{
    this->clear();
}

kvs::GeometryObjectBase* GeometryObjectBase::DownCast( kvs::ObjectBase* object )
{
    const kvs::ObjectBase::ObjectType type = object->objectType();
    if ( type != kvs::ObjectBase::Geometry )
    {
        kvsMessageError("Input object is not a geometry object.");
        return( NULL );
    }

    kvs::GeometryObjectBase* geometry = static_cast<kvs::GeometryObjectBase*>( object );

    return( geometry );
}

const kvs::GeometryObjectBase* GeometryObjectBase::DownCast( const kvs::ObjectBase* object )
{
    return( GeometryObjectBase::DownCast( const_cast<kvs::ObjectBase*>( object ) ) );
}

std::ostream& operator << ( std::ostream& os, const kvs::GeometryObjectBase& object )
{
#ifdef KVS_COMPILER_VC
#if KVS_COMPILER_VERSION_LESS_OR_EQUAL( 8, 0 )
    // @TODO Cannot instance the object that is a abstract class here (error:C2259).
#endif
#else
    os << static_cast<const kvs::ObjectBase&>( object ) << std::endl;
#endif
    os << "Number of vertices:  " << object.nvertices() << std::endl;
    os << "Number of colors:  " << object.ncolors() << std::endl;
    os << "Number of normal vectors:  " << object.nnormals();

    return( os );
}

void GeometryObjectBase::clear( void )
{
    m_coords.deallocate();
    m_colors.deallocate();
    m_normals.deallocate();
}

void GeometryObjectBase::setCoords( const kvs::ValueArray<kvs::Real32>& coords )
{
    m_coords = coords;
}

void GeometryObjectBase::setColors( const kvs::ValueArray<kvs::UInt8>& colors )
{
    m_colors = colors;
}

void GeometryObjectBase::setColor( const kvs::RGBColor& color )
{
    m_colors.allocate( 3 );
    m_colors[0] = color.r();
    m_colors[1] = color.g();
    m_colors[2] = color.b();
}

void GeometryObjectBase::setNormals( const kvs::ValueArray<kvs::Real32>& normals )
{
    m_normals = normals;
}

const kvs::ObjectBase::ObjectType GeometryObjectBase::objectType( void ) const
{
    return( kvs::ObjectBase::Geometry );
}

const size_t GeometryObjectBase::nvertices( void ) const
{
    const size_t dimension = 3;
    return( m_coords.size() / dimension );
}

const size_t GeometryObjectBase::ncolors( void ) const
{
    const size_t nchannels = 3;
    return( m_colors.size() / nchannels );
}

const size_t GeometryObjectBase::nnormals( void ) const
{
    const size_t dimension = 3;
    return( m_normals.size() / dimension );
}

const kvs::Vector3f GeometryObjectBase::coord( const size_t index ) const
{
    const size_t dimension = 3;
    return( kvs::Vector3f( m_coords.pointer() + dimension * index ) );
}

const kvs::RGBColor GeometryObjectBase::color( const size_t index ) const
{
    const size_t nchannels = 3;
    return( kvs::RGBColor( m_colors.pointer() + nchannels * index ) );
}

const kvs::Vector3f GeometryObjectBase::normal( const size_t index ) const
{
    const size_t dimension = 3;
    return( kvs::Vector3f( m_normals.pointer() + dimension * index ) );
}

const kvs::ValueArray<kvs::Real32>& GeometryObjectBase::coords( void ) const
{
    return( m_coords );
}

const kvs::ValueArray<kvs::UInt8>& GeometryObjectBase::colors( void ) const
{
    return( m_colors );
}

const kvs::ValueArray<kvs::Real32>& GeometryObjectBase::normals( void ) const
{
    return( m_normals );
}
/*==========================================================================*/
/**
 *  Update the min/max node coordinates.
 */
/*==========================================================================*/
void GeometryObjectBase::updateMinMaxCoords( void )
{
    this->calculate_min_max_coords();
}

/*==========================================================================*/
/**
 *  Calculate the min/max coordinate values.
 */
/*==========================================================================*/
void GeometryObjectBase::calculate_min_max_coords( void )
{
    kvs::Vector3f min_coord( 0.0f );
    kvs::Vector3f max_coord( 0.0f );

    const kvs::Real32* coord = this->coords().pointer();
    const kvs::Real32* const end = coord + this->coords().size();

    kvs::Real32 x = *( coord++ );
    kvs::Real32 y = *( coord++ );
    kvs::Real32 z = *( coord++ );

    min_coord.set( x, y, z );
    max_coord.set( x, y, z );

    while ( coord < end )
    {
        x = *( coord++ );
        y = *( coord++ );
        z = *( coord++ );

        min_coord.x() = kvs::Math::Min( min_coord.x(), x );
        min_coord.y() = kvs::Math::Min( min_coord.y(), y );
        min_coord.z() = kvs::Math::Min( min_coord.z(), z );

        max_coord.x() = kvs::Math::Max( max_coord.x(), x );
        max_coord.y() = kvs::Math::Max( max_coord.y(), y );
        max_coord.z() = kvs::Math::Max( max_coord.z(), z );
    }

    this->setMinMaxObjectCoords( min_coord, max_coord );

    if ( !( this->hasMinMaxExternalCoords() ) )
    {
        this->setMinMaxExternalCoords(
            this->minObjectCoord(),
            this->maxObjectCoord() );
    }
}

} // end of namespace kvs
