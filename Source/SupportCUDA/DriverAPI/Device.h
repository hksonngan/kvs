/*****************************************************************************/
/**
 *  @file   Device.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: Device.h 1652 2013-11-26 04:44:15Z naohisa.sakamoto@gmail.com $
 */
/*****************************************************************************/
#ifndef KVS__CUDA__DRIVERAPI__DEVICE_H_INCUDE
#define KVS__CUDA__DRIVERAPI__DEVICE_H_INCUDE

#include <cuda.h>
#include <string>
#include <kvs/Vector3>
#include <kvs/Deprecated>


namespace kvs
{

namespace cuda
{

namespace DriverAPI
{

/*===========================================================================*/
/**
 *  @brief  Device class.
 */
/*===========================================================================*/
class Device
{
private:

    CUdevice m_handler; ///< device handler
    CUdevprop m_property; ///< cuda device properties
    size_t m_free_memory; ///< free amount of memory on the device
    size_t m_total_memory; ///< total amount of memory on the device

public:

    static int Count();

public:

    Device();
    Device( const int ordinal );
    ~Device();

    void update();
    bool create( const int ordinal );

    CUdevice handler();
    int majorRevision() const;
    int minorRevision() const;
    std::string name() const;
    size_t totalMemory() const;
    size_t freeMemory() const;
    int maxThreadsPerBlock() const;
    kvs::Vector3i maxThreadsDimension() const;
    kvs::Vector3i maxGridSize() const;
    int sharedMemoryPerBlock() const;
    int totalConstantMemory() const;
    int warpSize() const;
    int memoryPitch() const;
    int registersPerBlock() const;
    int clockRate() const;
    int textureAlignment() const;

public:
    KVS_DEPRECATED( static int count() ) { return Count(); }
};

} // end of namespace cuda

} // end of namespace kvs

} // end of namespace DriverAPI

#endif // KVS__CUDA__DRIVERAPI__DEVICE_H_INCUDE
