/*****************************************************************************/
/**
 *  @file   Context.h
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
#ifndef KVS__CUDA__CONTEXT_H_INCLUDE
#define KVS__CUDA__CONTEXT_H_INCLUDE

#include "CUDA.h"
#include "Device.h"


namespace kvs
{

namespace cuda
{

/*===========================================================================*/
/**
 *  @brief  Context class.
 */
/*===========================================================================*/
class Context
{
private:

    CUcontext m_handler; ///< context handler

public:

    Context();
    Context( kvs::cuda::Device& device );
    ~Context();

    bool create( kvs::cuda::Device& device );
};

} // end of namespace cuda

} // end of namespace kvs

#endif // KVS__CUDA__CONTEXT_H_INCLUDE
