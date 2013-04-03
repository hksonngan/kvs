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
#ifndef KVS__STOCHASTIC_LINE_RENDERER_H_INCLUDE
#define KVS__STOCHASTIC_LINE_RENDERER_H_INCLUDE

#include "StochasticRendererBase.h"
#include "StochasticLineEngine.h"
#include <kvs/LineObject>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Stochastic renderer class for line object.
 */
/*===========================================================================*/
class StochasticLineRenderer : public kvs::StochasticRendererBase
{
    kvsModuleName( kvs::StochasticLineRenderer );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::StochasticRendererBase );

public:

    StochasticLineRenderer();
    StochasticLineRenderer( kvs::LineObject* object );

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

    void attachObject( const kvs::LineObject* object );
};

} // end of namespace kvs

#endif // KVS__STOCHASTIC_LINE_RENDERER_H_INCLUDE
