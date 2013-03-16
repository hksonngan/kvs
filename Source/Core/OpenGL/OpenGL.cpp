/*****************************************************************************/
/**
 *  @file   OpenGL.cpp
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
#include "OpenGL.h"


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
std::string Description()
{
    const std::string description( "OpenGL - The Industry's Foundation for High Performance Graphics" );
    return description;
}

/*===========================================================================*/
/**
 *  @brief  Returns OpenGL version.
 *  @return OpenGL version
 */
/*===========================================================================*/
std::string Version()
{
    const std::string version( (const char*)glGetString( GL_VERSION ) );
    return version;
}

/*===========================================================================*/
/**
 *  @brief  Returns GLSL (OpenGL Shading Language) version.
 *  @return GLSL version
 */
/*===========================================================================*/
std::string ShaderVersion()
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
    return version;
}

/*===========================================================================*/
/**
 *  @brief  Returns vendor information.
 *  @return vender information
 */
/*===========================================================================*/
std::string Vendor()
{
    const std::string vender( (const char*)glGetString( GL_VENDOR ) );
    return vender;
}

/*===========================================================================*/
/**
 *  @brief  Returns renderer (GPU) information.
 *  @return rendere information
 */
/*===========================================================================*/
std::string Renderer()
{
    const std::string renderer( (const char*)glGetString( GL_RENDERER ) );
    return renderer;
}

/*===========================================================================*/
/**
 *  @brief  Returns OpenGL extension name list.
 *  @return extension name list
 */
/*===========================================================================*/
kvs::StringList ExtensionList()
{
    kvs::StringList extension_list;

    std::stringstream list( (char*)glGetString( GL_EXTENSIONS ) );
    std::string name;
    while ( list >> name )
    {
        extension_list.push_back( name );
    }

    return extension_list;
}

/*===========================================================================*/
/**
 *  @brief  Returns OpenGL error code.
 *  @return error code
 */
/*===========================================================================*/
GLenum ErrorCode()
{
    return glGetError();
}

/*===========================================================================*/
/**
 *  @brief  Checks OpenGL error.
 *  @return true, if no error
 */
/*===========================================================================*/
bool HasError()
{
    const GLenum error_code = kvs::OpenGL::ErrorCode();
    if ( error_code == GL_NO_ERROR ) return false;
    return true;
}

/*===========================================================================*/
/**
 *  @brief  Returns OpenGL error string.
 *  @param  error_code [in] OpenGL error code
 *  @return error string
 */
/*===========================================================================*/
std::string ErrorString( const GLenum error_code )
{
    const std::string error_string( (const char*)gluErrorString( error_code ) );
    return error_string;
}

} // end of namespace OpenGL

} // end of namespace kvs
