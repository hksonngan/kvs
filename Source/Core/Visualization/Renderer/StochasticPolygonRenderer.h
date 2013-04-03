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
#ifndef KVS__STOCHASTIC_POLYGON_RENDERER_H_INCLUDE
#define KVS__STOCHASTIC_POLYGON_RENDERER_H_INCLUDE

#include "StochasticRendererBase.h"
#include "StochasticPolygonEngine.h"
#include <kvs/PolygonObject>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Stochastic renderer class for polygon object.
 */
/*===========================================================================*/
class StochasticPolygonRenderer : public kvs::StochasticRendererBase
{
    kvsModuleName( kvs::StochasticPolygonRenderer );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::StochasticRendererBase );

public:

    StochasticPolygonRenderer( void );

    StochasticPolygonRenderer( const kvs::PolygonObject* object );

public:

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

public:

    void attachObject( const kvs::PolygonObject* object );
};

} // end of namespace kvs

#endif // KVS__STOCHASTIC_POLYGON_RENDERER_H_INCLUDE
