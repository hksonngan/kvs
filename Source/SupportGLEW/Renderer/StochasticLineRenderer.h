/*****************************************************************************/
/**
 *  @file   StochasticLineRenderer.h
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
#ifndef KVS__GLEW__STOCHASTIC_LINE_RENDERER_H_INCLUDE
#define KVS__GLEW__STOCHASTIC_LINE_RENDERER_H_INCLUDE

#include "StochasticRendererBase.h"
#include "StochasticLineEngine.h"
#include <kvs/LineObject>


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Stochastic renderer class for line object.
 */
/*===========================================================================*/
class StochasticLineRenderer : public kvs::glew::StochasticRendererBase
{
    kvsModuleName( kvs::glew::StochasticLineRenderer );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::glew::StochasticRendererBase );

public:

    StochasticLineRenderer( void );

    StochasticLineRenderer( kvs::LineObject* object );

public:

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

public:

    void attachObject( const kvs::LineObject* object );
};

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__STOCHASTIC_LINE_RENDERER_H_INCLUDE
