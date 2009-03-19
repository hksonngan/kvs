/*****************************************************************************/
/**
 *  @file   FragmentShader.cpp
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
#include "../GLEW.h"
#include "FragmentShader.h"
#include <kvs/Message>


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  Constructs a new FragmentShader class.
 */
/*===========================================================================*/
FragmentShader::FragmentShader( void ):
    kvs::glew::ShaderObject( GL_FRAGMENT_SHADER_ARB )
{
}

/*===========================================================================*/
/**
 *  Constructs a new FragmentShader class.
 *  @param  source [in] shader source
 */
/*===========================================================================*/
FragmentShader::FragmentShader( const kvs::glew::ShaderSource& source ):
    kvs::glew::ShaderObject( GL_FRAGMENT_SHADER_ARB )
{
    if ( !SuperClass::create( source ) )
    {
        kvsMessageError("Cannot create a fragment shader.");
    }
}

/*===========================================================================*/
/**
 *  Destroy the FragmentShader class.
 */
/*===========================================================================*/
FragmentShader::~FragmentShader( void )
{
}

} // end of namespace glew

} // end of namespace kvs
