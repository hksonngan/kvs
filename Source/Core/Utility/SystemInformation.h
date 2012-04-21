/****************************************************************************/
/**
 *  @file SystemInformation.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#ifndef KVS__SYSTEM_INFORMATION_H_INCLUDE
#define KVS__SYSTEM_INFORMATION_H_INCLUDE

#include <cstdio>


namespace kvs
{

/*==========================================================================*/
/**
 *  System information class.
 */
/*==========================================================================*/
class SystemInformation
{
public:
#if KVS_DEPRECATED
    static size_t nprocessors()
    { return numberOfProcessors(); }
#endif
    static size_t numberOfProcessors();
    static size_t totalMemorySize();
    static size_t freeMemorySize();
};

} // end of namespace kvs

#endif // KVS__SYSTEM_INFORMATION_H_INCLUDE
