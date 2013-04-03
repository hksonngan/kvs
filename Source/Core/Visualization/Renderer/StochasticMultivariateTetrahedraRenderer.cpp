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

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticMultivariateTetrahedraRenderer class.
 */
/*===========================================================================*/
StochasticMultivariateTetrahedraRenderer::StochasticMultivariateTetrahedraRenderer( void )
{
    BaseClass::setRenderingEngine( new kvs::StochasticMultivariateTetrahedraEngine() );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticMultivariateTetrahedraRenderer class.
 *  @param  object [in] pointer to the unstructured volume object
 */
/*===========================================================================*/
StochasticMultivariateTetrahedraRenderer::StochasticMultivariateTetrahedraRenderer( kvs::UnstructuredVolumeObject* object )
{
    BaseClass::setRenderingEngine( new kvs::StochasticMultivariateTetrahedraEngine( object ) );
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
    kvs::StochasticRenderingEngine* engine = BaseClass::m_rendering_engines[0];
    if ( !engine->object() ) engine->attachObject( object );

    BaseClass::startTimer();
    this->create_image( camera, light );
    BaseClass::stopTimer();
}

/*===========================================================================*/
/**
 *  @brief  Attaches an unstructured volume object.
 *  @param  object [in] pointer to the unstructured volume object
 */
/*===========================================================================*/
void StochasticMultivariateTetrahedraRenderer::attachObject( const kvs::UnstructuredVolumeObject* object )
{
    kvs::StochasticRenderingEngine* engine = BaseClass::m_rendering_engines[0];
    engine->attachObject( object );

    BaseClass::clearEnsembleBuffer();
}

void StochasticMultivariateTetrahedraRenderer::setTransferFunction( const kvs::TransferFunction& tfunc, const size_t index )
{
    kvs::StochasticRenderingEngine* engine = BaseClass::m_rendering_engines[0];
    static_cast<kvs::StochasticMultivariateTetrahedraEngine*>(engine)->setTransferFunction( tfunc, index );
}

} // end of namespace kvs
