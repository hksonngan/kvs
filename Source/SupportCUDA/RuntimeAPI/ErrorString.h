/*****************************************************************************/
/**
 *  @file   ErrorString.h
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
#ifndef KVS__CUDA__RUNTIMEAPI__ERRORSTRING_H_INCLUDE
#define KVS__CUDA__RUNTIMEAPI__ERRORSTRING_H_INCLUDE

#include <cuda.h>
#include <cuda_runtime.h>


namespace kvs
{

namespace cuda
{

namespace RuntimeAPI
{

/*===========================================================================*/
/**
 *  @brief  Returns the error message from an error code.
 *  @param  error [in] CUDA error code
 *  @return error message
 */
/*===========================================================================*/
inline const char* ErrorString( const cudaError_t error )
{
    return cudaGetErrorString( error );
}

/*===========================================================================*/
/**
 *  @brief  Returns the last error code from a runtime call.
 *  @return error code
 */
/*===========================================================================*/
inline cudaError_t LastError()
{
    return cudaGetLastError();
}

/*===========================================================================*/
/**
 *  @brief  Returns the last error code from a runtime call.
 *  @return error code
 */
/*===========================================================================*/
inline cudaError_t peekAtLastError()
{
    return cudaPeekAtLastError();
}

} // end of namespace DriverAPI

} // end of namespace cuda

} // end of namespace kvs

#endif // KVS__CUDA__DRIVERAPI__ERRORSTRING_H_INCLUDE