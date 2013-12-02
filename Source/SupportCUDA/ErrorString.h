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
#pragma once
#include <kvs/Deprecated>
#include "RuntimeAPI/ErrorString.h"


namespace kvs
{

namespace cuda
{

// KVS_DEPRECATED
inline const char* ErrorString( const CUresult error ) { return kvs::cuda::RuntimeAPI::ErrorString( error ); }

} // end of namespace cuda

} // end of namespace kvs
