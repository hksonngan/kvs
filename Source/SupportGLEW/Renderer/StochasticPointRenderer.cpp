/*****************************************************************************/
/**
 *  @file   StochasticPointRenderer.cpp
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
#include "StochasticPointRenderer.h"
#include "StochasticPointEngine.h"


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticPointRenderer class.
 */
/*===========================================================================*/
StochasticPointRenderer::StochasticPointRenderer( void )
{
    BaseClass::setRenderingEngine( new kvs::glew::StochasticPointEngine() );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticPointRenderer class.
 *  @param  object [in] pointer to a point object
 */
/*===========================================================================*/
StochasticPointRenderer::StochasticPointRenderer( kvs::PointObject* object )
{
    BaseClass::setRenderingEngine( new kvs::glew::StochasticPointEngine( object ) );
}

/*===========================================================================*/
/**
 *  @brief  Executes the rendering process.
 *  @param  object [in] pointer to point object
 *  @param  camera [in] pointer to camera
 *  @param  light [in] pointer to light
 */
/*===========================================================================*/
void StochasticPointRenderer::exec(
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
 *  @brief  Attaches a point object.
 *  @param  object [in] pointer to a point object
 */
/*===========================================================================*/
void StochasticPointRenderer::attachObject( const kvs::PointObject* object )
{
    kvs::glew::StochasticRenderingEngine* engine = BaseClass::m_rendering_engines[0];
    engine->attachObject( object );

    BaseClass::clearEnsembleBuffer();
}

/*===========================================================================*/
/**
 *  @brief  Sets a repetition level.
 *  @param  repetition_level [in] repetition level
 */
/*===========================================================================*/
void StochasticPointRenderer::setRepetitionLevel( const size_t repetition_level )
{
    BaseClass::setRepetitionLevel( repetition_level );

    typedef kvs::glew::StochasticPointEngine Engine;
    Engine* engine = static_cast<Engine*>( BaseClass::m_rendering_engines[0] );
    engine->setRepetitionLevel( repetition_level );
}

} // end of namespace glew

} // end of namespace kvs
