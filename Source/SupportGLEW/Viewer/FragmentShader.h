/*****************************************************************************/
/**
 *  @file   FragmentShader.h
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
#ifndef KVS__GLEW__FRAGMENT_SHADER_H_INCLUDE
#define KVS__GLEW__FRAGMENT_SHADER_H_INCLUDE

#include "ShaderObject.h"
#include "ShaderSource.h"
#include <kvs/ClassName>


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  Fragment shader class.
 */
/*===========================================================================*/
class FragmentShader : public kvs::glew::ShaderObject
{
    kvsClassName( FragmentShader );

public:

    typedef kvs::glew::ShaderObject SuperClass;

public:

    FragmentShader( void );

    FragmentShader( const kvs::glew::ShaderSource& source );

    virtual ~FragmentShader( void );
};

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__FRAGMENT_SHADER_H_INCLUDE
