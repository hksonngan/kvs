/*****************************************************************************/
/**
 *  @file   StochasticPointRenderer.h
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
#ifndef KVS__GLEW__STOCHASTIC_POINT_RENDERER_H_INCLUDE
#define KVS__GLEW__STOCHASTIC_POINT_RENDERER_H_INCLUDE

#include "StochasticRendererBase.h"
#include "StochasticPointEngine.h"
#include <kvs/PointObject>


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Stochastic renderer class for point object.
 */
/*===========================================================================*/
class StochasticPointRenderer : public kvs::glew::StochasticRendererBase
{
    kvsModuleName( kvs::glew::StochasticPointRenderer );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::glew::StochasticRendererBase );

public:

    StochasticPointRenderer( void );

    StochasticPointRenderer( kvs::PointObject* object );

public:

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

public:

    void attachObject( const kvs::PointObject* object );

    void setRepetitionLevel( const size_t repetition_level );
};

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__STOCHASTIC_POINT_RENDERER_H_INCLUDE
