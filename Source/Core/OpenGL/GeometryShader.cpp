/*****************************************************************************/
/**
 *  @file   GeometryShader.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: GeometryShader.cpp 602 2010-08-19 02:43:34Z naohisa.sakamoto $
 */
/*****************************************************************************/
#include "GeometryShader.h"
#include <kvs/Message>


namespace kvs
{

GeometryShader::GeometryShader():
    kvs::ShaderObject( GL_GEOMETRY_SHADER )
{
}

GeometryShader::GeometryShader( const kvs::ShaderSource& source ):
    kvs::ShaderObject( GL_GEOMETRY_SHADER )
{
    if ( !SuperClass::create( source ) )
    {
        kvsMessageError("Cannot create a geometry shader.");
    }
}

} // end of namespace kvs
