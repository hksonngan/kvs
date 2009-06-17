/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program to display GPU information with CUDA API.
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
#include <iostream>
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
    kvs::cuda::Initialize( argc, argv );

    const size_t ngpus = kvs::cuda::Device::count();
    std::cout << "Num. of GPUs: " << ngpus << std::endl;

    for ( size_t i = 0; i < ngpus; i++ )
    {
        kvs::cuda::Device device( i );
        std::cout << "ID:           " << i << std::endl;
        std::cout << "Name:         " << device.name() << std::endl;
        std::cout << "Total memory: " << device.totalMemory() / 1024 / 1024 << " [MB]" << std::endl;
        std::cout << "Free memory:  " << device.freeMemory() / 1024 / 1024 << " [MB]" << std::endl;
    }

    return 0;
}
