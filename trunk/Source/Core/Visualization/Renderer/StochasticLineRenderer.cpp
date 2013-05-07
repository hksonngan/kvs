/*****************************************************************************/
/**
 *  @file   StochasticLineRenderer.cpp
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
#include "StochasticLineRenderer.h"
#include "StochasticLineEngine.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticLineRenderer class.
 */
/*===========================================================================*/
StochasticLineRenderer::StochasticLineRenderer()
{
    BaseClass::setRenderingEngine( new kvs::StochasticLineEngine() );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticLineRenderer class.
 *  @param  object [in] pointer to the line object
 */
/*===========================================================================*/
StochasticLineRenderer::StochasticLineRenderer( kvs::LineObject* object )
{
    BaseClass::setRenderingEngine( new kvs::StochasticLineEngine( object ) );
}

/*===========================================================================*/
/**
 *  @brief  Executes the rendering process.
 *  @param  object [in] pointer to the object
 *  @param  camera [in] pointer to the camera
 *  @param  light [in] pointer to the light
 */
/*===========================================================================*/
void StochasticLineRenderer::exec(
    kvs::ObjectBase* object,
    kvs::Camera* camera,
    kvs::Light* light )
{
    kvs::StochasticRenderingEngine* engine = BaseClass::m_rendering_engines[0];
    if ( !engine->object() ) engine->attachObject( object );

    BaseClass::startTimer();
    this->create_image( camera, light );
    BaseClass::stopTimer();
}

/*===========================================================================*/
/**
 *  @brief  Attaches a line object.
 *  @param  object [in] pointer to a line object
 */
/*===========================================================================*/
void StochasticLineRenderer::attachObject( const kvs::LineObject* object )
{
    kvs::StochasticRenderingEngine* engine = BaseClass::m_rendering_engines[0];
    engine->attachObject( object );

    BaseClass::clearEnsembleBuffer();
}

void StochasticLineRenderer::setOpacity( const unsigned char opacity )
{
    kvs::StochasticRenderingEngine* engine = BaseClass::m_rendering_engines[0];
    static_cast<StochasticLineEngine*>(engine)->setOpacity( opacity );
}

} // end of namespace kvs