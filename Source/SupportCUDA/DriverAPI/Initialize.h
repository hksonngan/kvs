/*****************************************************************************/
/**
 *  @file   Initialize.h
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
#ifndef KVS__CUDA__DRIVERAPI__INITIALIZE_H_INCLUDE
#define KVS__CUDA__DRIVERAPI__INITIALIZE_H_INCLUDE

#include <kvs/Message>
#include <cuda.h>
#include "ErrorString.h"


namespace kvs
{

namespace cuda
{

namespace DriverAPI
{

/*===========================================================================*/
/**
 *  @brief  Initializes CUDA.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 *  @return true, if the initialization is done successfully
 */
/*===========================================================================*/
inline bool Initialize( int argc, char** argv )
{
    CUresult result = cuInit( 0 );
    if ( result != CUDA_SUCCESS )
    {
        kvsMessageError( "CUDA; %s.", kvs::cuda::DriverAPI::ErrorString( result ) );
        return false;
    }

    return true;
}

} // end of namespace DriverAPI

} // end of namespace cuda

} // end of namespace kvs

#endif // KVS__CUDA__DRIVERAPI__INITIALIZE_H_INCLUDE
