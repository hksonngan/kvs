/*****************************************************************************/
/**
 *  @file   ShaderSource.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#ifndef KVS__GLEW__SHADER_SOURCE_H_INCLUDE
#define KVS__GLEW__SHADER_SOURCE_H_INCLUDE

#include <string>
#include <kvs/ClassName>


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  Shader source class.
 */
/*===========================================================================*/
class ShaderSource
{
    kvsClassName( ShaderSource );

protected:

    std::string m_code; ///< shader source code

public:

    ShaderSource( void );

    ShaderSource( const std::string& source );

    virtual ~ShaderSource( void );

public:

    const std::string& code( void ) const;

    void setCode( const std::string& code );

    const bool read( const std::string& filename );
};

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__SHADER_SOURCE_H_INCLUDE
