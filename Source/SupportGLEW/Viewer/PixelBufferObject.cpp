/*****************************************************************************/
/**
 *  @file   PixelBufferObject.cpp
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
#include "PixelBufferObject.h"


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  Construct a new PixelBufferObject.
 */
/*===========================================================================*/
PixelBufferObject::PixelBufferObject( void )
{
}

/*===========================================================================*/
/**
 *  Construct a new PixelBufferObject.
 *  @param  operation_type [in] operation type
 */
/*===========================================================================*/
PixelBufferObject::PixelBufferObject( const GLenum operation_type ):
    kvs::glew::BufferObject( operation_type, GL_DYNAMIC_DRAW_ARB )
{
}

/*===========================================================================*/
/**
 *  Destroy the PixelBufferObject.
 */
/*===========================================================================*/
PixelBufferObject::~PixelBufferObject( void )
{
}

} // end of namespace glew

} // end of namespace kvs
