/****************************************************************************/
/**
 *  @file GLEW.h
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
#ifndef KVS__GLEW__GLEW_H_INCLUDE
#define KVS__GLEW__GLEW_H_INCLUDE

#include <kvs/Message>
#include <kvs/String>
#include <GL/glew.h>


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  Initialize the OpenGL extension entry point.
 *  @return whether the initialization process is successfully or not
 */
/*===========================================================================*/
inline bool Initialize()
{
    GLenum result = glewInit();
    if ( result != GLEW_OK )
    {
        kvsMessageError( "GLEW; %s.", glewGetErrorString( result ) );
        return false;
    }

    return true;
}

/*===========================================================================*/
/**
 *  Returns GLEW description
 *  @return description
 */
/*===========================================================================*/
inline std::string Description()
{
    const std::string description( "GLEW - The OpenGL Extension Wrangler Library" );
    return description;
}

/*===========================================================================*/
/**
 *  Returns GLEW version.
 *  @return version
 */
/*===========================================================================*/
inline std::string Version()
{
    const std::string version( (const char*)( glewGetString( GLEW_VERSION ) ) );
    return version;
}

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__GLEW_H_INCLUDE
