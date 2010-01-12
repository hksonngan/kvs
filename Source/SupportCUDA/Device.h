/*****************************************************************************/
/**
 *  @file   Device.h
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
#ifndef KVS__CUDA__DEVICE_H_INCUDE
#define KVS__CUDA__DEVICE_H_INCUDE

#include "CUDA.h"
#include <string>
#include <kvs/Vector3>


namespace kvs
{

namespace cuda
{

/*===========================================================================*/
/**
 *  @brief  Device class.
 */
/*===========================================================================*/
class Device
{
protected:

    CUdevice     m_handler;      ///< device handler
    CUdevprop    m_property;     ///< cuda device properties
    unsigned int m_free_memory;  ///< free amount of memory on the device
    unsigned int m_total_memory; ///< total amount of memory on the device

public:

    Device( void );

    Device( const int ordinal );

    ~Device( void );

public:

    void update( void );

    const bool create( const int ordinal );

public:

    CUdevice handler( void );

    const int majorRevision( void ) const;

    const int minorRevision( void ) const;

    const std::string name( void ) const;

    const unsigned int totalMemory( void ) const;

    const unsigned int freeMemory( void ) const;

    const int maxThreadsPerBlock( void ) const;

    const kvs::Vector3i maxThreadsDimension( void ) const;

    const kvs::Vector3i maxGridSize( void ) const;

    const int sharedMemoryPerBlock( void ) const;

    const int totalConstantMemory( void ) const;

    const int warpSize( void ) const;

    const int memoryPitch( void ) const;

    const int registersPerBlock( void ) const;

    const int clockRate( void ) const;

    const int textureAlignment( void ) const;

    static const int count( void );
};

} // end of namespace cuda

} // end of namespace kvs

#endif // KVS__CUDA__DEVICE_H_INCUDE
