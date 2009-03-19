/****************************************************************************/
/**
 *  @file Breakpoint.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#ifndef KVS_CORE_BREAKPOINT_H_INCLUDE
#define KVS_CORE_BREAKPOINT_H_INCLUDE

#include "Compiler.h"
#include "Platform.h"

// Microsoft Visual C++
#if defined ( KVS_COMPILER_VC )
#define KVS_BREAKPOINT { __asm { int 3 } }

// GNU GCC
#elif defined ( KVS_COMPILER_GCC )

#if defined ( KVS_PLATFORM_CPU_X86 )
#define KVS_BREAKPOINT { __asm__( " int $3 " ); }

#elif defined ( KVS_PLATFORM_CPU_POWERPC )
#define KVS_BREAKPOINT { __asm__( " .long 0x7d821008 " ); }

#else
#warning Breakpoint code unknown for the CPU.
#warning You can add it defining the KVS_BREAKPOINT macro.
#define KVS_BREAKPOINT { } // Insert breakpoint code for your CPU here.
#endif

// Unknown compiler
#else
#error Unknown compiler. KVS supports GNU C++ compiler and
#error Microsoft Visual C++ compiler only.
#endif

#endif // KVS_CORE_BREAKPOINT_H_INCLUDE
