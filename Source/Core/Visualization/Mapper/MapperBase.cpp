/****************************************************************************/
/**
 *  @file MapperBase.cpp
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
#include "MapperBase.h"
#include <kvs/StructuredVolumeObject>
#include <kvs/UnstructuredVolumeObject>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructs a new empty MapperBase.
 */
/*==========================================================================*/
MapperBase::MapperBase( void )
    : m_transfer_function()
    , m_volume( 0 )
    , m_is_success( false )
{
}

/*==========================================================================*/
/**
 *  Constructs a new MapperBase.
 */
/*==========================================================================*/
MapperBase::MapperBase( const TransferFunction& transfer_function )
    : m_transfer_function( transfer_function )
    , m_volume( 0 )
    , m_is_success( false )
{
}

/*==========================================================================*/
/**
 *  Destroys the MapperBase.
 */
/*==========================================================================*/
MapperBase::~MapperBase( void )
{
}

void MapperBase::setTransferFunction( const kvs::TransferFunction& transfer_function )
{
    m_transfer_function = transfer_function;
}

void MapperBase::setColorMap( const kvs::ColorMap& color_map )
{
    m_transfer_function.setColorMap( color_map );
}

void MapperBase::setOpacityMap( const kvs::OpacityMap& opacity_map )
{
    m_transfer_function.setOpacityMap( opacity_map );
}

const kvs::VolumeObjectBase* const MapperBase::volume( void ) const
{
    return( m_volume );
}

const kvs::TransferFunction& MapperBase::transferFunction( void ) const
{
    return( m_transfer_function );
}

const kvs::ColorMap& MapperBase::colorMap( void ) const
{
    return( m_transfer_function.colorMap() );
}

const kvs::OpacityMap& MapperBase::opacityMap( void ) const
{
    return( m_transfer_function.opacityMap() );
}

/*==========================================================================*/
/**
 *  Returns true if the mapping is success; otherwise returns false.
 *
 *  @return Whether the mapping is success or not.
 */
/*==========================================================================*/
const bool MapperBase::isSuccess( void ) const
{
    return( m_is_success );
}

/*==========================================================================*/
/**
 *  Returns true if the mapping is failure; otherwise returns false.
 *
 *  @return Whether the mapping is failure or not.
 */
/*==========================================================================*/
const bool MapperBase::isFailure( void ) const
{
    return( !m_is_success );
}

void MapperBase::attach_volume( const kvs::VolumeObjectBase* volume )
{
    m_volume = volume;
}

void MapperBase::set_min_max_coords( const kvs::VolumeObjectBase* volume, kvs::ObjectBase* object )
{
    if ( !volume->hasMinMaxObjectCoords() )
    {
        switch ( volume->volumeType() )
        {
        case kvs::VolumeObjectBase::Structured:
        {
            // WARNING: remove constness, but safe in this case.
            kvs::VolumeObjectBase* b = const_cast<kvs::VolumeObjectBase*>( volume );
            reinterpret_cast<kvs::StructuredVolumeObject*>( b )->updateMinMaxCoords();
            break;
        }
        case kvs::VolumeObjectBase::Unstructured:
        {
            // WARNING: remove constness, but safe in this case.
            kvs::VolumeObjectBase* b = const_cast<kvs::VolumeObjectBase*>( volume );
            reinterpret_cast<kvs::UnstructuredVolumeObject*>( b )->updateMinMaxCoords();
            break;
        }
        default: break;
        }
    }

    const kvs::Vector3f min_obj_coord( m_volume->minObjectCoord() );
    const kvs::Vector3f max_obj_coord( m_volume->maxObjectCoord() );
    const kvs::Vector3f min_ext_coord( m_volume->minExternalCoord() );
    const kvs::Vector3f max_ext_coord( m_volume->maxExternalCoord() );
    object->setMinMaxObjectCoords( min_obj_coord, max_obj_coord );
    object->setMinMaxExternalCoords( min_ext_coord, max_ext_coord );
}

} // end of namespace kvs
