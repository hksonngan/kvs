/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program to display GPU information with CUDA API.
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
/*****************************************************************************/
#include <iostream>
#include <kvs/cuda/CUDA>
#include <kvs/cuda/Device>


/*===========================================================================*/
/**
 *  @brief  Main function
 *  @param  argc [in] argument count
 *  @param  argv [in] argumnet values
 */
/*===========================================================================*/
int main( int argc, char** argv )
{
    if ( !kvs::cuda::Initialize( argc, argv ) )
    {
        kvsMessageError( "Cannot initialize CUDA." );
        return 1;
    }

    const size_t ngpus = kvs::cuda::Device::Count();
    std::cout << "Num. of GPUs: " << ngpus << std::endl;

    for ( size_t i = 0; i < ngpus; i++ )
    {
        kvs::cuda::Device device( i );
        std::cout << "ID: " << i << std::endl;
        std::cout << "Name: " << device.name() << std::endl;
        std::cout << "Compute capability: " << device.majorRevision() << "." << device.minorRevision() << std::endl;
        std::cout << "Total memory: " << device.totalMemory() / 1024 / 1024 << " [MB]" << std::endl;
        std::cout << "Free memory: " << device.freeMemory() / 1024 / 1024 << " [MB]" << std::endl;
        std::cout << "Max. number of threads per block: " << device.maxThreadsPerBlock() << std::endl;
        std::cout << "Max. size of each dimension of a block: " << device.maxThreadsDimension() << std::endl;
        std::cout << "Max. size of each dimension of a grid: " << device.maxGridSize() << std::endl;
        std::cout << "Shared memory per block: " << device.sharedMemoryPerBlock() / 1024 << " [KB]" << std::endl;
        std::cout << "Total amount of constant memory: " << device.totalConstantMemory() / 1024 << " [KB]" << std::endl;
        std::cout << "Warp size: " << device.warpSize() << " [B]" << std::endl;
        std::cout << "Memory pitch: " << device.memoryPitch() / 1024 << " [KB]" << std::endl;
        std::cout << "Number of registers per block: " << device.registersPerBlock() << std::endl;
        std::cout << "Clock rate: " << device.clockRate() / 1000 << " [MHz]" << std::endl;
        std::cout << "Texture alignment: " << device.textureAlignment() / 1024 << " [MB]" << std::endl;
    }

    return 0;
}
