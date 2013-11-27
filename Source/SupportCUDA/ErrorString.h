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
#ifndef KVS__ERROR_STRING_H_INCLUDE
#define KVS__ERROR_STRING_H_INCLUDE

#include <kvs/Deprecated>
#include "DriverAPI/ErrorString.h"


namespace kvs
{

namespace cuda
{

KVS_DEPRECATED( inline const char* ErrorString( const CUresult error ) ) { return DriverAPI::ErrorString( error ); }

} // end of namespace cuda

} // end of namespace kvs

#endif // KVS__ERROR_STRING_H_INCLUDE
