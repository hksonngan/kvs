/****************************************************************************/
/**
 *  @file ExtractVertices.cpp
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
#include "ExtractVertices.h"

#include <kvs/VolumeObjectBase>
#include <kvs/StructuredVolumeObject>

namespace kvs
{

/*==========================================================================*/
/**
 *  Constructs a new empty ExtractVertices.
 */
/*==========================================================================*/
ExtractVertices::ExtractVertices( void )
    : MapperBase()
    , PointObject()
{
}

/*==========================================================================*/
/**
 *  Constructs a new ExtractVertices.
 *
 *  @param [in] volume     Structured Volume data.
 */
/*==========================================================================*/
ExtractVertices::ExtractVertices(
    const kvs::VolumeObjectBase* volume )
    : MapperBase()
    , PointObject()
{
    this->exec( volume );
}

/*==========================================================================*/
/**
 *  Constructs a new ExtractVertices.
 *
 *  @param [in] volume            Structured Volume data.
 *  @param [in] transfer_function Transfer function.
 */
/*==========================================================================*/
ExtractVertices::ExtractVertices(
    const kvs::VolumeObjectBase* volume,
    const kvs::TransferFunction& transfer_function )
    : MapperBase( transfer_function )
    , PointObject()
{
    this->exec( volume );
}

/*==========================================================================*/
/**
 *  Destroys the ExtractVertices.
 */
/*==========================================================================*/
ExtractVertices::~ExtractVertices( void )
{
}

kvs::ObjectBase* ExtractVertices::exec( const kvs::ObjectBase* object )
{
    const kvs::ObjectBase::ObjectType type = object->objectType();
    if ( type == kvs::ObjectBase::Volume )
    {
        this->mapping( reinterpret_cast<const kvs::VolumeObjectBase*>( object ) );
    }
    else
    {
        kvsMessageError("Geometry object is not supported.");
    }

    return( this );
}

void ExtractVertices::mapping(
    const kvs::VolumeObjectBase* volume )
{
//    m_volume = volume;
    BaseClass::attach_volume( volume );

//    this->pre_process();
    BaseClass::set_min_max_coords( volume, this );

    this->calculate_coords();

    const std::type_info& type = volume->values().typeInfo()->type();
    if (      type == typeid( kvs::Int8   ) ) { this->calculate_colors<kvs::Int8  >(); }
    else if ( type == typeid( kvs::Int16  ) ) { this->calculate_colors<kvs::Int16 >(); }
    else if ( type == typeid( kvs::Int32  ) ) { this->calculate_colors<kvs::Int32 >(); }
    else if ( type == typeid( kvs::Int64  ) ) { this->calculate_colors<kvs::Int64 >(); }
    else if ( type == typeid( kvs::UInt8  ) ) { this->calculate_colors<kvs::UInt8 >(); }
    else if ( type == typeid( kvs::UInt16 ) ) { this->calculate_colors<kvs::UInt16>(); }
    else if ( type == typeid( kvs::UInt32 ) ) { this->calculate_colors<kvs::UInt32>(); }
    else if ( type == typeid( kvs::UInt64 ) ) { this->calculate_colors<kvs::UInt64>(); }
    else if ( type == typeid( kvs::Real32 ) ) { this->calculate_colors<kvs::Real32>(); }
    else if ( type == typeid( kvs::Real64 ) ) { this->calculate_colors<kvs::Real64>(); }
}

/*
void ExtractVertices::pre_process( void )
{
    const Vector3f min_coord( m_volume->minExternalCoord() );
    const Vector3f max_coord( m_volume->maxExternalCoord() );

    SuperClass::setMinMaxObjectCoords  ( min_coord, max_coord );
    SuperClass::setMinMaxExternalCoords( min_coord, max_coord );
}
*/

void ExtractVertices::calculate_coords( void )
{
    const VolumeObjectBase::GridType& type = m_volume->gridType();

    if ( type == VolumeObjectBase::Uniform )
    {
       this->calculate_uniform_coords();
    }
    else if ( type == VolumeObjectBase::Rectilinear )
    {
        this->calculate_rectiliner_coords();
    }
    else
    {
        SuperClass::setCoords( m_volume->coords() );
    }
}

void ExtractVertices::calculate_uniform_coords( void )
{
    const kvs::StructuredVolumeObject* volume
        = dynamic_cast<const kvs::StructuredVolumeObject*>( m_volume );

    kvs::ValueArray<float> coords( 3 * volume->nnodes() );
    float*                 coord = coords.pointer();

    const kvs::Vector3ui resolution( volume->resolution() );

    const kvs::Vector3f  volume_size( volume->maxExternalCoord() - volume->minExternalCoord() );
    const kvs::Vector3ui ngrids( resolution - kvs::Vector3ui( 1, 1, 1 ) );
    const kvs::Vector3f  grid_size(
        volume_size.x() / static_cast<float>( ngrids.x() ),
        volume_size.y() / static_cast<float>( ngrids.y() ),
        volume_size.z() / static_cast<float>( ngrids.z() ) );

    for ( size_t k = 0; k < resolution.z(); ++k )
    {
        const float z =
            grid_size.z() * static_cast<float>( k );
        for ( size_t j = 0; j < resolution.y(); ++j )
        {
            const float y =
                grid_size.y() * static_cast<float>( j );
            for ( size_t i = 0; i < resolution.x(); ++i )
            {
                const float x =
                    grid_size.x() * static_cast<float>( i );

                *( coord++ ) = x;
                *( coord++ ) = y;
                *( coord++ ) = z;
            }
        }
    }

    SuperClass::setCoords( coords );
}

void ExtractVertices::calculate_rectiliner_coords( void )
{
}

template <typename T>
void ExtractVertices::calculate_colors( void )
{
    const kvs::VolumeObjectBase* volume = m_volume;

    const T*       value = reinterpret_cast<const T*>( volume->values().pointer() );
    const T* const end   = value + volume->values().size();

    kvs::ValueArray<kvs::UInt8> colors( 3 * volume->nnodes() );
    kvs::UInt8*                 color = colors.pointer();

    kvs::ColorMap cmap( BaseClass::colorMap() );

    if ( !volume->hasMinMaxValues() ) { volume->updateMinMaxValues(); }

    const kvs::Real64 min_value = volume->minValue();
    const kvs::Real64 max_value = volume->maxValue();

    const kvs::Real64 normalize_factor =
        static_cast<kvs::Real64>( cmap.resolution() - 1 ) / ( max_value - min_value );

    const size_t veclen = m_volume->veclen();

    if ( veclen == 1 )
    {
        while( value < end )
        {
            const kvs::UInt32 color_level =
                static_cast<kvs::UInt32>( normalize_factor * ( static_cast<kvs::Real64>( *( value++ ) ) - min_value ) );

            *( color++ ) = cmap[ color_level ].red();
            *( color++ ) = cmap[ color_level ].green();
            *( color++ ) = cmap[ color_level ].blue();
        }
    }
    else
    {
        while( value < end )
        {
            kvs::Real64 magnitude = 0.0;
            for ( size_t i = 0; i < veclen; ++i )
            {
                magnitude += kvs::Math::Square( static_cast<kvs::Real64>( *value ) );
                ++value;
            }
            magnitude = kvs::Math::SquareRoot( magnitude );

            const kvs::UInt32 color_level =
                static_cast<kvs::UInt32>( normalize_factor * ( magnitude - min_value ) );

            *( color++ ) = cmap[ color_level ].red();
            *( color++ ) = cmap[ color_level ].green();
            *( color++ ) = cmap[ color_level ].blue();
        }
    }

    SuperClass::setColors( colors );
}

}
