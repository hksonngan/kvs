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


namespace
{

std::string GLGetString( GLenum name )
{
    std::string ret;
    const GLubyte* c = NULL;
    KVS_GL_CALL( c = glGetString( name ) );
    while ( *c ) ret += *c++;
    return ret;
}

std::string GLUGetString( GLenum name )
{
    std::string ret;
    const GLubyte* c = NULL;
    KVS_GL_CALL( c = gluGetString( name ) );
    while ( *c ) ret += *c++;
    return ret;
}

std::string GLEWGetString( GLenum name )
{
    std::string ret;
    const GLubyte* c = glewGetString( name );
    while ( *c ) ret += *c++;
    return ret;
}

}

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
    return ::GLGetString( GL_VERSION );
}

/*===========================================================================*/
/**
 *  @brief  Returns GLSL (OpenGL Shading Language) version.
 *  @return GLSL version
 */
/*===========================================================================*/
std::string GLSLVersion()
{
#if defined( GL_SHADING_LANGUAGE_VERSION )
    return ::GLGetString( GL_SHADING_LANGUAGE_VERSION );
#elif defined( GL_SHADING_LANGUAGE_VERSION_ARB )
    return ::GLGetString( GL_SHADING_LANGUAGE_VERSION_ARB );
#else
    return "Unknown";
#endif
}

/*===========================================================================*/
/**
 *  @brief  Returns GLU version.
 *  @return GLU version
 */
/*===========================================================================*/
std::string GLUVersion()
{
    return ::GLUGetString( GLU_VERSION );
}

/*===========================================================================*/
/**
 *  @brief  Returns GLEW version.
 *  @return GLEW version
 */
/*===========================================================================*/
std::string GLEWVersion()
{
    return ::GLEWGetString( GLEW_VERSION );
}

/*===========================================================================*/
/**
 *  @brief  Returns vendor information.
 *  @return vender information
 */
/*===========================================================================*/
std::string Vendor()
{
    return ::GLGetString( GL_VENDOR );
}

/*===========================================================================*/
/**
 *  @brief  Returns renderer (GPU) information.
 *  @return rendere information
 */
/*===========================================================================*/
std::string Renderer()
{
    return ::GLGetString( GL_RENDERER );
}

/*===========================================================================*/
/**
 *  @brief  Returns OpenGL extension name list.
 *  @return extension name list
 */
/*===========================================================================*/
kvs::StringList ExtensionList()
{
    kvs::StringList extensions;
    std::stringstream list( ::GLGetString( GL_EXTENSIONS ) );
    std::string name;
    while ( list >> name )
    {
        extensions.push_back( name );
    }

    return extensions;
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
    std::string error_string;
    const GLubyte* c = gluErrorString( error_code );
    while ( *c ) error_string += *c++;
    return error_string;
}

void GetBooleanv( GLenum pname, GLboolean* params )
{
    KVS_GL_CALL( glGetBooleanv( pname, params ) );
}

void GetDoublev( GLenum pname, GLdouble* params )
{
    KVS_GL_CALL( glGetDoublev( pname, params ) );
}

void GetFloatv( GLenum pname, GLfloat* params )
{
    KVS_GL_CALL( glGetFloatv( pname, params ) );
}

void GetIntegerv( GLenum pname, GLint* params )
{
    KVS_GL_CALL( glGetIntegerv( pname, params ) );
}

GLboolean Boolean( GLenum pname )
{
    GLboolean param;
    kvs::OpenGL::GetBooleanv( pname, &param );
    return param;
}

GLdouble Double( GLenum pname )
{
    GLdouble param;
    kvs::OpenGL::GetDoublev( pname, &param );
    return param;
}

GLfloat Float( GLenum pname )
{
    GLfloat param;
    kvs::OpenGL::GetFloatv( pname, &param );
    return param;
}

GLint Integer( GLenum pname )
{
    GLint param;
    kvs::OpenGL::GetIntegerv( pname, &param );
    return param;
}

} // end of namespace OpenGL

} // end of namespace kvs
