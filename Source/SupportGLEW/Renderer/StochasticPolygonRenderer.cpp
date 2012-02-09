/*****************************************************************************/
/**
 *  @file   StochasticPolygonRenderer.cpp
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
#include "StochasticPolygonRenderer.h"
#include "StochasticPolygonEngine.h"


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticPolygonRenderer class.
 */
/*===========================================================================*/
StochasticPolygonRenderer::StochasticPolygonRenderer( void )
{
    BaseClass::setRenderingEngine( new kvs::glew::StochasticPolygonEngine() );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticPolygonRenderer class.
 *  @param  object [in] pointer to a polygon object
 */
/*===========================================================================*/
StochasticPolygonRenderer::StochasticPolygonRenderer( const kvs::PolygonObject* object )
{
    BaseClass::setRenderingEngine( new kvs::glew::StochasticPolygonEngine( object ) );
}

/*===========================================================================*/
/**
 *  @brief  Executes the rendering process.
 *  @param  object [in] pointer to polygon object
 *  @param  camera [in] pointer to camera
 *  @param  light [in] pointer to light
 */
/*===========================================================================*/
void StochasticPolygonRenderer::exec(
    kvs::ObjectBase* object,
    kvs::Camera*     camera,
    kvs::Light*      light )
{
    kvs::glew::StochasticRenderingEngine* engine = BaseClass::m_rendering_engines[0];
    if ( !engine->object() ) engine->attachObject( object );

    BaseClass::m_timer.start();
    BaseClass::create_image( camera, light );
    BaseClass::m_timer.stop();
}

/*===========================================================================*/
/**
 *  @brief  Attaches a polygon object.
 *  @param  object [in] pointer to a polygon object
 */
/*===========================================================================*/
void StochasticPolygonRenderer::attachObject( const kvs::PolygonObject* object )
{
    kvs::glew::StochasticRenderingEngine* engine = BaseClass::m_rendering_engines[0];
    engine->attachObject( object );

    BaseClass::clearEnsembleBuffer();
}

} // end of namespace glew

} // end of namespace kvs
