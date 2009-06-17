/*****************************************************************************/
/**
 *  @file   Device.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include "Device.h"
#include "ErrorString.h"
#include "Context.h"
#include <kvs/Message>


namespace kvs
{

namespace cuda
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new Device class.
 */
/*===========================================================================*/
Device::Device( void ):
    m_handler( 0 ),
    m_free_memory( 0 ),
    m_total_memory( 0 )
{
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new Device class.
 *  @param  ordinal [in] ordinal (ID of the compute-capable device)
 */
/*===========================================================================*/
Device::Device( const int ordinal )
{
    if ( this->create( ordinal ) ) this->update();
}

/*===========================================================================*/
/**
 *  @brief  Destructs the Device class.
 */
/*===========================================================================*/
Device::~Device( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Updates device information.
 */
/*===========================================================================*/
void Device::update( void )
{
    kvs::cuda::Context context( *this );

    CUresult result = cuMemGetInfo( &m_free_memory, &m_total_memory );
    if ( result != CUDA_SUCCESS )
    {
        kvsMessageError( "CUDA; %s.", kvs::cuda::ErrorString( result ) );
    }
}

/*===========================================================================*/
/**
 *  @brief  Creates a compute-capable device.
 *  @param  ordinal [in] ordinal (ID of the compute-capable device)
 *  @return true, if the device is created successfully
 */
/*===========================================================================*/
const bool Device::create( const int ordinal )
{
    CUresult result = cuDeviceGet( &m_handler, ordinal );
    if ( result != CUDA_SUCCESS )
    {
        kvsMessageError( "CUDA; %s.", kvs::cuda::ErrorString( result ) );
        return( false );
    }

    return( true );
}

/*===========================================================================*/
/**
 *  @brief  Returns the device handler.
 *  @return device handler
 */
/*===========================================================================*/
CUdevice Device::handler( void )
{
    return( m_handler );
}

/*===========================================================================*/
/**
 *  @brief  Returns the device major revision number.
 *  @return major revision number
 */
/*===========================================================================*/
const int Device::majorRevision( void ) const
{
    int major_revision = 0;
    int minor_revision = 0;
    CUresult result = cuDeviceComputeCapability( &major_revision, &minor_revision, m_handler );
    if ( result != CUDA_SUCCESS )
    {
        kvsMessageError( "CUDA; %s.", kvs::cuda::ErrorString( result ) );
    }

    return( major_revision );
}

/*===========================================================================*/
/**
 *  @brief  Returns the device minor revision number.
 *  @return minor revision number
 */
/*===========================================================================*/
const int Device::minorRevision( void ) const
{
    int major_revision = 0;
    int minor_revision = 0;
    CUresult result = cuDeviceComputeCapability( &major_revision, &minor_revision, m_handler );
    if ( result != CUDA_SUCCESS )
    {
        kvsMessageError( "CUDA; %s.", kvs::cuda::ErrorString( result ) );
    }

    return( minor_revision );
}

/*===========================================================================*/
/**
 *  @brief  Returns the device name.
 *  @return device name
 */
/*===========================================================================*/
const std::string Device::name( void ) const
{
    const int length = 256;
    char name[ length ];
    CUresult result = cuDeviceGetName( name, length, m_handler );
    if ( result != CUDA_SUCCESS )
    {
        kvsMessageError( "CUDA; %s.", kvs::cuda::ErrorString( result ) );
    }

    return( name );
}

/*===========================================================================*/
/**
 *  @brief  Returns the total memory size in byte.
 *  @return total memory size in byte
 */
/*===========================================================================*/
const unsigned int Device::totalMemory( void ) const
{
    return( m_total_memory );
}

/*===========================================================================*/
/**
 *  @brief  Returns the free memory size in byte.
 *  @return free memory size in byte
 */
/*===========================================================================*/
const unsigned int Device::freeMemory( void ) const
{
    return( m_free_memory );
}

/*===========================================================================*/
/**
 *  @brief  Returns a number of compute-capable devices.
 *  @return number of compute-capable devices
 */
/*===========================================================================*/
const int Device::count( void )
{
    int count = 0;
    CUresult result = cuDeviceGetCount( &count );
    if ( result != CUDA_SUCCESS )
    {
        kvsMessageError( "CUDA; %s.", kvs::cuda::ErrorString( result ) );
    }

    return( count );
}

} // end of namespace cuda

} // end of namespace kvs
