/*****************************************************************************/
/**
 *  @file   StochasticPolygonRenderer.h
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
#ifndef KVS__GLEW__STOCHASTIC_POLYGON_RENDERER_H_INCLUDE
#define KVS__GLEW__STOCHASTIC_POLYGON_RENDERER_H_INCLUDE

#include "StochasticRendererBase.h"
#include "StochasticPolygonEngine.h"
#include <kvs/PolygonObject>


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Stochastic renderer class for polygon object.
 */
/*===========================================================================*/
class StochasticPolygonRenderer : public kvs::glew::StochasticRendererBase
{
    kvsModuleName( kvs::glew::StochasticPolygonRenderer );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::glew::StochasticRendererBase );

public:

    StochasticPolygonRenderer( void );

    StochasticPolygonRenderer( const kvs::PolygonObject* object );

public:

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

public:

    void attachObject( const kvs::PolygonObject* object );
};

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__STOCHASTIC_POLYGON_RENDERER_H_INCLUDE
