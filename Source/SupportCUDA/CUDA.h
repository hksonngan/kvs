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
#pragma once
#include <cuda.h>
#include <cuda_runtime.h>
#include <kvs/String>


namespace kvs
{

namespace cuda
{

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
