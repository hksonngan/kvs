/*****************************************************************************/
/**
 *  @file   GeometryShader.h
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
#ifndef KVS__GLEW__GEOMETRY_SHADER_H_INCLUDE
#define KVS__GLEW__GEOMETRY_SHADER_H_INCLUDE

#include "ShaderObject.h"
#include "ShaderSource.h"
#include <kvs/ClassName>


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  Geometry shader class.
 */
/*===========================================================================*/
class GeometryShader : public kvs::glew::ShaderObject
{
    kvsClassName( GeometryShader );

public:

    typedef kvs::glew::ShaderObject SuperClass;

public:

    GeometryShader( void );

    GeometryShader( const kvs::glew::ShaderSource& source );

    virtual ~GeometryShader( void );
};

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__GEOMETRY_SHADER_H_INCLUDE
