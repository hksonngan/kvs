/****************************************************************************/
/**
 *  @file Macro.h
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
#ifndef KVS_CORE_MACRO_H_INCLUDE
#define KVS_CORE_MACRO_H_INCLUDE

#include "Compiler.h"

#define KVS_MACRO_FILE __FILE__

#define KVS_MACRO_LINE __LINE__

#define KVS_MACRO_DATE __DATE__

#define KVS_MACRO_TIME __TIME__

#if defined ( KVS_COMPILER_VC )
#if KVS_COMPILER_VERSION_LESS_THAN( 7, 0 )
#define KVS_MACRO_FUNC "unknown"
#else
#define KVS_MACRO_FUNC __FUNCSIG__
#endif
#elif defined ( KVS_COMPILER_GCC )
#define KVS_MACRO_FUNC __PRETTY_FUNCTION__
#else
#define KVS_MACRO_FUNC __func__
#endif

#endif // KVS_CORE_MACRO_H_INCLUDE
