/*****************************************************************************/
/**
 *  @file   StochasticUniformGridRenderer.h
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
#ifndef KVS__STOCHASTIC_UNIFORM_GRID_RENDERER_H_INCLUDE
#define KVS__STOCHASTIC_UNIFORM_GRID_RENDERER_H_INCLUDE

#include "StochasticRendererBase.h"
#include "StochasticUniformGridEngine.h"
#include <kvs/StructuredVolumeObject>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Stochastic renderer class for unstructured volume object.
 */
/*===========================================================================*/
class StochasticUniformGridRenderer : public kvs::StochasticRendererBase
{
    kvsModuleName( kvs::StochasticUniformGridRenderer );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::StochasticRendererBase );

public:

    StochasticUniformGridRenderer( void );

    StochasticUniformGridRenderer( kvs::StructuredVolumeObject* object );

public:

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

public:

    void setTransferFunction( const kvs::TransferFunction& transfer_function );

    void attachObject( const kvs::StructuredVolumeObject* object );
};

} // end of namespace kvs

#endif // KVS__STOCHASTIC_UNIFORM_GRID_RENDERER_H_INCLUDE
