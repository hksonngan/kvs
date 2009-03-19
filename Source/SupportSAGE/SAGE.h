/****************************************************************************/
/**
 *  @file SAGE.h
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
#ifndef KVS_SUPPORT_SAGE_SAGE_H_INCLUDE
#define KVS_SUPPORT_SAGE_SAGE_H_INCLUDE

#include <kvs/Platform>
#include <kvs/String>

#if defined( KVS_PLATFORM_MACOSX )
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <sail.h>


namespace kvs
{

namespace sage
{

/*===========================================================================*/
/**
 *  @brief  Returns SAGE description
 *  @return description
 */
/*===========================================================================*/
inline const std::string Description( void )
{
    const std::string description( "SAGE - Scalable Adaptive Graphics Environment" );
    return( description );
}

/*===========================================================================*/
/**
 *  @brief  Returns SAGE version.
 *  @return SAGE version
 */
/*===========================================================================*/
inline const std::string Version( void )
{
    const std::string version( SAGE_VERSION );
    return( version );
}

} // end of namespace sage

} // end of namespace kvs

#endif // KVS_SUPPORT_SAGE_SAGE_H_INCLUDE
