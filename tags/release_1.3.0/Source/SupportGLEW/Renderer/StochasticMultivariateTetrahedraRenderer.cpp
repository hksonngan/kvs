/*****************************************************************************/
/**
 *  @file   StochasticMultivariateTetrahedraRenderer.cpp
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
#include "StochasticMultivariateTetrahedraRenderer.h"
#include "StochasticMultivariateTetrahedraEngine.h"


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticMultivariateTetrahedraRenderer class.
 */
/*===========================================================================*/
StochasticMultivariateTetrahedraRenderer::StochasticMultivariateTetrahedraRenderer( void )
{
    BaseClass::setRenderingEngine( new kvs::glew::StochasticMultivariateTetrahedraEngine() );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticMultivariateTetrahedraRenderer class.
 *  @param  object [in] pointer to the unstructured volume object
 */
/*===========================================================================*/
StochasticMultivariateTetrahedraRenderer::StochasticMultivariateTetrahedraRenderer( kvs::UnstructuredVolumeObject* object )
{
    BaseClass::setRenderingEngine( new kvs::glew::StochasticMultivariateTetrahedraEngine( object ) );
}

/*===========================================================================*/
/**
 *  @brief  Executes the rendering process.
 *  @param  object [in] pointer to the object
 *  @param  camera [in] pointer to the camera
 *  @param  light [in] pointer to the light
 */
/*===========================================================================*/
void StochasticMultivariateTetrahedraRenderer::exec(
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
void StochasticMultivariateTetrahedraRenderer::attachObject( const kvs::UnstructuredVolumeObject* object )
{
    kvs::glew::StochasticRenderingEngine* engine = BaseClass::m_rendering_engines[0];
    engine->attachObject( object );

    BaseClass::clearEnsembleBuffer();
}

void StochasticMultivariateTetrahedraRenderer::setTransferFunction( const kvs::TransferFunction& tfunc, const size_t index )
{
    kvs::glew::StochasticRenderingEngine* engine = BaseClass::m_rendering_engines[0];
    static_cast<kvs::glew::StochasticMultivariateTetrahedraEngine*>(engine)->setTransferFunction( tfunc, index );
}

} // end of namespace glew

} // end of namespace kvs