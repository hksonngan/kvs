/*****************************************************************************/
/**
 *  @file   StochasticUnstructuredVolumeRenderer.cpp
 *  @author Naohisa Sakamoto
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
#include "StochasticUnstructuredVolumeRenderer.h"
#include "StochasticUnstructuredVolumeEngine.h"


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticUnstructuredVolumeRenderer class.
 */
/*===========================================================================*/
StochasticUnstructuredVolumeRenderer::StochasticUnstructuredVolumeRenderer( void )
{
    BaseClass::setRenderingEngine( new kvs::glew::StochasticUnstructuredVolumeEngine() );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticUnstructuredVolumeRenderer class.
 *  @param  object [in] pointer to the unstructured volume object
 */
/*===========================================================================*/
StochasticUnstructuredVolumeRenderer::StochasticUnstructuredVolumeRenderer( kvs::UnstructuredVolumeObject* object )
{
    BaseClass::setRenderingEngine( new kvs::glew::StochasticUnstructuredVolumeEngine( object ) );
}

/*===========================================================================*/
/**
 *  @brief  Executes the rendering process.
 *  @param  object [in] pointer to the object
 *  @param  camera [in] pointer to the camera
 *  @param  light [in] pointer to the light
 */
/*===========================================================================*/
void StochasticUnstructuredVolumeRenderer::exec(
    kvs::ObjectBase* object,
    kvs::Camera*     camera,
    kvs::Light*      light )
{
    kvs::glew::StochasticRenderingEngine* engine = BaseClass::m_rendering_engines[0];
    if ( !engine->object() ) engine->attachObject( object );

    BaseClass::m_timer.start();
    this->create_image( camera, light );
    BaseClass::m_timer.stop();
}

/*===========================================================================*/
/**
 *  @brief  Attaches an unstructured volume object.
 *  @param  object [in] pointer to the unstructured volume object
 */
/*===========================================================================*/
void StochasticUnstructuredVolumeRenderer::attachObject( const kvs::UnstructuredVolumeObject* object )
{
    kvs::glew::StochasticRenderingEngine* engine = BaseClass::m_rendering_engines[0];
    engine->attachObject( object );

    BaseClass::clearEnsembleBuffer();
}

} // end of namespace glew

} // end of namespace kvs
