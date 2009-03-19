/*****************************************************************************/
/**
 *  @file   GeometryShader.cpp
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
#include "GeometryShader.h"
#include <kvs/Message>


namespace kvs
{

namespace glew
{

GeometryShader::GeometryShader( void ):
    kvs::glew::ShaderObject( GL_GEOMETRY_SHADER_EXT )
{
}

GeometryShader::GeometryShader( const kvs::glew::ShaderSource& source ):
    kvs::glew::ShaderObject( GL_GEOMETRY_SHADER_EXT )
{
    if ( !SuperClass::create( source ) )
    {
        kvsMessageError("Cannot create a geometry shader.");
    }
}

GeometryShader::~GeometryShader( void )
{
}

} // end of namespace glew

} // end of namespace kvs
