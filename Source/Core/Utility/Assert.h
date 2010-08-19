/****************************************************************************/
/**
 *  @file Assert.h
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
#ifndef KVS_CORE_ASSERT_H_INCLUDE
#define KVS_CORE_ASSERT_H_INCLUDE

#include "Message.h"

#if defined ( KVS_ENABLE_DEBUG )
#define KVS_ASSERT( exp ) \
    ( kvs::Message( kvs::Message::Assert, KVS_MACRO_FILE, KVS_MACRO_LINE, KVS_MACRO_FUNC, ( exp ) ) ( # exp ) )
#else
#define KVS_ASSERT( exp )
#endif

#endif // KVS_CORE_ASSERT_H_INCLUDE
