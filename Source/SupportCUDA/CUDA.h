/*****************************************************************************/
/**
 *  @file   CUDA.h
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
#ifndef KVS_SUPPORT_CUDA_CUDA_H_INCLUDE
#define KVS_SUPPORT_CUDA_CUDA_H_INCLUDE

#include <kvs/Message>
#include <kvs/String>
#include <kvs/Deprecated>
#include <cuda.h>
#include "DriverAPI/Initialize.h"


namespace kvs
{

namespace cuda
{

// KVS_DEPRECATED
inline bool Initialize( int argc, char** argv ) { return kvs::cuda::DriverAPI::Initialize( argc, argv ); }

/*===========================================================================*/
/**
 *  @brief  Returns CUDA description.
 *  @return description
 */
/*===========================================================================*/
inline std::string Description()
{
    const std::string description( "CUDA - Compute Unified Device Architecture" );
    return description;
}

/*===========================================================================*/
/**
 *  @brief  Returns CUDA version.
 *  @return CUDA version
 */
/*===========================================================================*/
inline std::string Version()
{
    const int major_version = CUDA_VERSION / 1000;
    const int minor_version = ( CUDA_VERSION - major_version * 1000 ) / 10;

    const std::string version(
        kvs::String::ToString( major_version ) + "." +
        kvs::String::ToString( minor_version ) );
    return version;
}

} // end of namespace cuda

} // end of namespace kvs

#endif // KVS_SUPPORT_CUDA_CUDA_H_INCLUDE
