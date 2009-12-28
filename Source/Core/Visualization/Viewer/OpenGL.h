/****************************************************************************/
/**
 *  @file OpenGL.h
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
#ifndef KVS_CORE_OPEN_GL_H_INCLUDE
#define KVS_CORE_OPEN_GL_H_INCLUDE

#include <kvs/Platform>
#include <kvs/StringList>

#if !defined( KVS_PLATFORM_WINDOWS )
#define GL_GLEXT_PROTOTYPES
#endif

#if defined( KVS_PLATFORM_WINDOWS )
#include <windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#endif

/* NOTE: GLEW header file 'glew.h' must be included before the OpenGL header files.
 * The 'glew.h' is formally included in SupportGLEW/GLEW.h. However, the 'glew.h'
 * is included in this header file when 'KVS_SUPPORT_GLEW' is defined since some
 * KVS classes that is compiled into the KVS core library uses the OpenGL functions
 * by including this header file.
 */
#if defined( KVS_SUPPORT_GLEW )
#include <GL/glew.h>
#endif

#if defined( KVS_PLATFORM_MACOSX )
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif


namespace kvs
{

namespace OpenGL
{

/*===========================================================================*/
/**
 *  @brief  Returns OpenGL description.
 *  @return OpenGL description
 */
/*===========================================================================*/
inline const std::string Description( void )
{
    const std::string description( "OpenGL - The Industry's Foundation for High Performance Graphics" );
    return( description );
}

/*===========================================================================*/
/**
 *  @brief  Returns OpenGL version.
 *  @return OpenGL version
 */
/*===========================================================================*/
inline const std::string Version( void )
{
    const std::string version( (const char*)glGetString( GL_VERSION ) );
    return( version );
}

/*===========================================================================*/
/**
 *  @brief  Returns GLSL (OpenGL Shading Language) version.
 *  @return GLSL version
 */
/*===========================================================================*/
inline const std::string ShaderVersion( void )
{
#if defined( GL_SHADING_LANGUAGE_VERSION )
    const std::string version( (const char*)glGetString( GL_SHADING_LANGUAGE_VERSION ) );
#else
#if defined( GL_SHADING_LANGUAGE_VERSION_ARB )
    const std::string version( (const char*)glGetString( GL_SHADING_LANGUAGE_VERSION_ARB ) );
#else
    const std::string version( "unknown" );
#endif
#endif
    return( version );
}

/*===========================================================================*/
/**
 *  @brief  Returns vendor information.
 *  @return vender information
 */
/*===========================================================================*/
inline const std::string Vendor( void )
{
    const std::string vender( (const char*)glGetString( GL_VENDOR ) );
    return( vender );
}

/*===========================================================================*/
/**
 *  @brief  Returns renderer (GPU) information.
 *  @return rendere information
 */
/*===========================================================================*/
inline const std::string Renderer( void )
{
    const std::string renderer( (const char*)glGetString( GL_RENDERER ) );
    return( renderer );
}

/*===========================================================================*/
/**
 *  @brief  Returns OpenGL extension name list.
 *  @return extension name list
 */
/*===========================================================================*/
inline const kvs::StringList ExtensionList( void )
{
    kvs::StringList extension_list;

    std::stringstream list( (char*)glGetString( GL_EXTENSIONS ) );
    std::string name;
    while ( list >> name )
    {
        extension_list.push_back( kvs::String( name ) );
    }

    return( extension_list );
}

/*===========================================================================*/
/**
 *  @brief  Returns OpenGL error code.
 *  @return error code
 */
/*===========================================================================*/
inline const GLenum ErrorCode( void )
{
    return( glGetError() );
}

/*===========================================================================*/
/**
 *  @brief  Checks OpenGL error.
 *  @return true, if no error
 */
/*===========================================================================*/
inline const bool CheckError( void )
{
    const GLenum error_code = kvs::OpenGL::ErrorCode();
    return( error_code == GL_NO_ERROR );
}

/*===========================================================================*/
/**
 *  @brief  Returns OpenGL error string.
 *  @param  error_code [in] OpenGL error code
 *  @return error string
 */
/*===========================================================================*/
inline std::string ErrorString( const GLenum error_code )
{
    const std::string error_string( (const char*)gluErrorString( error_code ) );
    return( error_string );
}

} // end of namespace OpenGL

} // end of namespace kvs

#endif // KVS_CORE_OPEN_GL_H_INCLUDE
