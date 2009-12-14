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
#if KVS_COMPILER_VERSION_GREATER_THAN( 8, 0 )
#define KVS_BREAKPOINT { __debugbreak(); }
#else
#define KVS_BREAKPOINT { __asm { int 3 } }
#endif

// GNU GCC
#elif defined ( KVS_COMPILER_GCC )

#if defined ( KVS_PLATFORM_CPU_X86 ) || defined ( KVS_PLATFORM_CPU_I386 )
#define KVS_BREAKPOINT { __asm__( " int $3 " ); }

#elif defined ( KVS_PLATFORM_CPU_X86_64 ) || defined ( KVS_PLATFORM_CPU_AMD64 )
#define KVS_BREAKPOINT { __asm__( " int $3 " ); }

#elif defined ( KVS_PLATFORM_CPU_POWERPC )
#define KVS_BREAKPOINT { __asm__( " .long 0x7d821008 " ); }

#else
#pragma message("Breakpoint.h: Unknown breakpoint code.")
#define KVS_BREAKPOINT { } // Insert breakpoint code for your CPU here.
#endif

// Unknown compiler
#else
#error Unknown compiler. KVS supports GNU C++ compiler and
#error Microsoft Visual C++ compiler only.
#endif

#endif // KVS_CORE_BREAKPOINT_H_INCLUDE
