/*****************************************************************************/
/**
 *  @file   FragmentShader.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: FragmentShader.cpp 602 2010-08-19 02:43:34Z naohisa.sakamoto $
 */
/*****************************************************************************/
#include "FragmentShader.h"
#include <kvs/Message>


namespace kvs
{

/*===========================================================================*/
/**
 *  Constructs a new FragmentShader class.
 */
/*===========================================================================*/
FragmentShader::FragmentShader():
    kvs::ShaderObject( GL_FRAGMENT_SHADER )
{
}

/*===========================================================================*/
/**
 *  Constructs a new FragmentShader class.
 *  @param  source [in] shader source
 */
/*===========================================================================*/
FragmentShader::FragmentShader( const kvs::ShaderSource& source ):
    kvs::ShaderObject( GL_FRAGMENT_SHADER )
{
    if ( !SuperClass::create( source ) )
    {
        kvsMessageError("Cannot create a fragment shader.");
    }
}

} // end of namespace kvs
