/****************************************************************************/
/**
 *  @file StringList.h
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
#ifndef KVS__STRING_LIST_H_INCLUDE
#define KVS__STRING_LIST_H_INCLUDE

#include <vector>
#if KVS_ENABLE_DEPRECATED
#include <kvs/String>
#endif


namespace kvs
{

typedef std::vector<std::string> StringList;

} // end of namespace kvs

#endif // KVS__STRING_LIST_H_INCLUDE
