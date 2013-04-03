/*****************************************************************************/
/**
 *  @file   StochasticUniformGridRenderer.cpp
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
#include "StochasticUniformGridRenderer.h"
#include "StochasticUniformGridEngine.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticUniformGridRenderer class.
 */
/*===========================================================================*/
StochasticUniformGridRenderer::StochasticUniformGridRenderer( void )
{
    BaseClass::setRenderingEngine( new kvs::StochasticUniformGridEngine() );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticUniformGridRenderer class.
 *  @param  object [in] pointer to the unstructured volume object
 */
/*===========================================================================*/
StochasticUniformGridRenderer::StochasticUniformGridRenderer( kvs::StructuredVolumeObject* object )
{
    BaseClass::setRenderingEngine( new kvs::StochasticUniformGridEngine( object ) );
}

/*===========================================================================*/
/**
 *  @brief  Executes the rendering process.
 *  @param  object [in] pointer to the object
 *  @param  camera [in] pointer to the camera
 *  @param  light [in] pointer to the light
 */
/*===========================================================================*/
void StochasticUniformGridRenderer::exec(
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
 *  @brief  Set a transfer function.
 *  @param  transfer_function [in] transfer function
 */
/*===========================================================================*/
void StochasticUniformGridRenderer::setTransferFunction( const kvs::TransferFunction& transfer_function )
{
    typedef kvs::StochasticUniformGridEngine Engine;
    Engine* engine = static_cast<Engine*>( BaseClass::m_rendering_engines[0] );
    engine->setTransferFunction( transfer_function );
}

/*===========================================================================*/
/**
 *  @brief  Attaches an unstructured volume object.
 *  @param  object [in] pointer to the unstructured volume object
 */
/*===========================================================================*/
void StochasticUniformGridRenderer::attachObject( const kvs::StructuredVolumeObject* object )
{
    kvs::StochasticRenderingEngine* engine = BaseClass::m_rendering_engines[0];
    engine->attachObject( object );

    BaseClass::clearEnsembleBuffer();
}

} // end of namespace kvs
