/****************************************************************************/
/**
 *  @file OpenGLChecker.h
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
#ifndef KVS_KVSCHECK_OPENGL_CHECKER_H_INCLUDE
#define KVS_KVSCHECK_OPENGL_CHECKER_H_INCLUDE

#include <string>
#include <kvs/StringList>


namespace kvscheck
{

/*===========================================================================*/
/**
 *  @brief  OpenGL information checker class.
 */
/*===========================================================================*/
class OpenGLChecker
{
protected:

    std::string     m_vendor;         ///< vendor name
    std::string     m_renderer;       ///< renderer (GPU) name
    std::string     m_gl_version;     ///< OpenGL version
    std::string     m_glu_version;    ///< GLU version
    kvs::StringList m_gl_extensions;  ///< OpenGL extensions
    kvs::StringList m_glu_extensions; ///< GLU extensions

public:

    OpenGLChecker( int argc, char** argv );

public:

    const std::string& vendor( void ) const;

    const std::string& renderer( void ) const;

    const std::string& GLVersion( void ) const;

    const std::string& GLUVersion( void ) const;

    const kvs::StringList& GLExtensions( void ) const;

    const kvs::StringList& GLUExtensions( void ) const;

    friend std::ostream& operator << ( std::ostream& os, const OpenGLChecker& checker );
};

} // end of namespace kvscheck

#endif // KVS_KVSCHECK_OPENGL_CHECKER_H_INCLUDE
