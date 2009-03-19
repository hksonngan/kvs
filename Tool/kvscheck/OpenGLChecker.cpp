/****************************************************************************/
/**
 *  @file OpenGLChecker.cpp
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
#include "OpenGLChecker.h"
#include <kvs/OpenGL>
#include <kvs/Message>

#if defined( KVS_SUPPORT_GLUT )
#include <kvs/glut/GLUT>
#endif


namespace kvscheck
{

/*===========================================================================*/
/**
 *  @brief  Constructs.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
OpenGLChecker::OpenGLChecker( int argc, char** argv )
{
#if defined( KVS_SUPPORT_GLUT )
    /* Using OS-dependent Window System API, such as aglCreateContext, glXCreateContext,
     * or wglCreateContext, instead of glutInit and glutCreateWindow, GLUT is not required ???
     */
    glutInit( &argc, argv );
    glutCreateWindow("");

    m_vendor        = kvs::OpenGL::Vendor();
    m_renderer      = kvs::OpenGL::Renderer();
    m_gl_version    = kvs::OpenGL::Version();
    m_gl_extensions = kvs::OpenGL::ExtensionList();
#if defined( GLU_VERSION_1_1 )
    /* The gluGetString function is not used in GLU version 1.0.
     */
    m_glu_version = std::string( (const char*)gluGetString( GLU_VERSION ) );

    std::stringstream glu_extension_list( (char*)gluGetString( GLU_EXTENSIONS ) );
    std::string glu_extension;
    while ( glu_extension_list >> glu_extension )
    {
        m_glu_extensions.push_back( kvs::String( glu_extension ) );
    }
#endif
#else
    kvsMessageError(
        "It seems that KVS_SUPPORT_GLUT option is disabled in the installed KVS. "
        "GLUT is required to check OpenGL information using kvscheck command.");
#endif
}

/*===========================================================================*/
/**
 *  @brief  Returns vendor information.
 */
/*===========================================================================*/
const std::string& OpenGLChecker::vendor( void ) const
{
    return( m_vendor );
}

/*===========================================================================*/
/**
 *  @brief  Returns renderer (GPU) information.
 */
/*===========================================================================*/
const std::string& OpenGLChecker::renderer( void ) const
{
    return( m_renderer );
}

/*===========================================================================*/
/**
 *  @brief  Returns OpenGL version.
 */
/*===========================================================================*/
const std::string& OpenGLChecker::GLVersion( void ) const
{
    return( m_gl_version );
}

/*===========================================================================*/
/**
 *  @brief  Returns GLU version.
 */
/*===========================================================================*/
const std::string& OpenGLChecker::GLUVersion( void ) const
{
    return( m_glu_version );
}

/*===========================================================================*/
/**
 *  @brief  Returns OpenGL extension list.
 */
/*===========================================================================*/
const kvs::StringList& OpenGLChecker::GLExtensions( void ) const
{
    return( m_gl_extensions );
}

/*===========================================================================*/
/**
 *  @brief  Returns GLU extension list.
 */
/*===========================================================================*/
const kvs::StringList& OpenGLChecker::GLUExtensions( void ) const
{
    return( m_glu_extensions );
}

/*==========================================================================*/
/**
 *  @brief Output platform information.
 *  @param os      [in] output stream
 *  @param checker [in] OpenGL information checker
 */
/*==========================================================================*/
std::ostream& operator << ( std::ostream& os, const OpenGLChecker& checker )
{
    os << "Vendor:      " << checker.vendor()    << std::endl;
    os << "Renderer:    " << checker.renderer()  << std::endl;
    os << "GL Version:  " << checker.GLVersion() << std::endl;
    os << "GLU Version: " << checker.GLUVersion() << std::endl;

    os << "GL Extensions (" << checker.GLExtensions().size() << "):" << std::endl;
    kvs::StringList::const_iterator gl_extension = checker.GLExtensions().begin();
    while ( gl_extension != checker.GLExtensions().end() )
    {
        os << "\t" << *gl_extension << std::endl;
        ++gl_extension;
    }

    os << "GLU Extensions (" << checker.GLUExtensions().size() << "):" << std::endl;
    kvs::StringList::const_iterator glu_extension = checker.GLUExtensions().begin();
    while ( glu_extension != checker.GLUExtensions().end() )
    {
        os << "\t" << *glu_extension << std::endl;
        ++glu_extension;
    }

    return( os );
}

} // end of namespace kvscheck
