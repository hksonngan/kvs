/*****************************************************************************/
/**
 *  @file   StochasticTetrahedraRenderer.cpp
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
#include "StochasticTetrahedraRenderer.h"
#include "StochasticTetrahedraEngine.h"


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticTetrahedraRenderer class.
 */
/*===========================================================================*/
StochasticTetrahedraRenderer::StochasticTetrahedraRenderer( void )
{
    BaseClass::setRenderingEngine( new kvs::glew::StochasticTetrahedraEngine() );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticTetrahedraRenderer class.
 *  @param  object [in] pointer to the unstructured volume object
 */
/*===========================================================================*/
StochasticTetrahedraRenderer::StochasticTetrahedraRenderer( kvs::UnstructuredVolumeObject* object )
{
    BaseClass::setRenderingEngine( new kvs::glew::StochasticTetrahedraEngine( object ) );
}

/*===========================================================================*/
/**
 *  @brief  Executes the rendering process.
 *  @param  object [in] pointer to the object
 *  @param  camera [in] pointer to the camera
 *  @param  light [in] pointer to the light
 */
/*===========================================================================*/
void StochasticTetrahedraRenderer::exec(
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
 *  @brief  Set a transfer function.
 *  @param  transfer_function [in] transfer function
 */
/*===========================================================================*/
void StochasticTetrahedraRenderer::setTransferFunction( const kvs::TransferFunction& transfer_function )
{
    typedef kvs::glew::StochasticTetrahedraEngine Engine;
    Engine* engine = static_cast<Engine*>( BaseClass::m_rendering_engines[0] );
    engine->setTransferFunction( transfer_function );
}

/*===========================================================================*/
/**
 *  @brief  Attaches an unstructured volume object.
 *  @param  object [in] pointer to the unstructured volume object
 */
/*===========================================================================*/
void StochasticTetrahedraRenderer::attachObject( const kvs::UnstructuredVolumeObject* object )
{
    kvs::glew::StochasticRenderingEngine* engine = BaseClass::m_rendering_engines[0];
    engine->attachObject( object );

    BaseClass::clearEnsembleBuffer();
}

} // end of namespace glew

} // end of namespace kvs
