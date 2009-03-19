/*****************************************************************************/
/**
 *  @file   IndexBufferObject.cpp
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
#include "IndexBufferObject.h"


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  Construct a new IndexBufferObject.
 */
/*===========================================================================*/
IndexBufferObject::IndexBufferObject( void ):
    kvs::glew::BufferObject( GL_ELEMENT_ARRAY_BUFFER_ARB, GL_DYNAMIC_DRAW_ARB )
{
}

/*===========================================================================*/
/**
 *  Destory the IndexBufferObject.
 */
/*===========================================================================*/
IndexBufferObject::~IndexBufferObject( void )
{
}

} // end of namespace glew

} // end of namespace kvs
