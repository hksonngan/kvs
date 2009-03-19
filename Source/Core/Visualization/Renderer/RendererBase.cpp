/****************************************************************************/
/**
 *  @file RendererBase.cpp
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
#include "RendererBase.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
RendererBase::RendererBase( void ) :
    m_shading_flag( true )
{
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
RendererBase::~RendererBase( void )
{
}

/*==========================================================================*/
/**
 *  Get the rendering timer.
 */
/*==========================================================================*/
const kvs::Timer& RendererBase::timer( void ) const
{
    return( m_timer );
}

/*==========================================================================*/
/**
 *  Get the rendering timer.
 */
/*==========================================================================*/
kvs::Timer& RendererBase::timer( void )
{
    return( m_timer );
}

/*==========================================================================*/
/**
 *  Test whether the shading is enable or disable.
 *  @return true, if the shading is enable.
 */
/*==========================================================================*/
const bool RendererBase::isShading( void ) const
{
    return( m_shading_flag );
}

/*==========================================================================*/
/**
 *  Enable to shading.
 */
/*==========================================================================*/
void RendererBase::enableShading( void ) const
{
    m_shading_flag = true;
}

/*==========================================================================*/
/**
 *  Disable to shading.
 */
/*==========================================================================*/
void RendererBase::disableShading( void ) const
{
    m_shading_flag = false;
}

/*==========================================================================*/
/**
 *  Initialize the renderer.
 */
/*==========================================================================*/
void RendererBase::initialize( void )
{
    initialize_projection();
    initialize_modelview();
}

/*==========================================================================*/
/**
 *  Initialize the projection information.
 */
/*==========================================================================*/
void RendererBase::initialize_projection( void )
{
}

/*==========================================================================*/
/**
 *  Initialize about the modelview information.
 */
/*==========================================================================*/
void RendererBase::initialize_modelview( void )
{
}

} // end of namespace kvs
