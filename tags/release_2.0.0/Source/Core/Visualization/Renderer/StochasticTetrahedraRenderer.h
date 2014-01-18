/*****************************************************************************/
/**
 *  @file   StochasticTetrahedraRenderer.h
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
#ifndef KVS__STOCHASTIC_TETRAHEDRA_RENDERER_H_INCLUDE
#define KVS__STOCHASTIC_TETRAHEDRA_RENDERER_H_INCLUDE

#include "StochasticRendererBase.h"
#include "StochasticTetrahedraEngine.h"
#include <kvs/UnstructuredVolumeObject>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Stochastic renderer class for unstructured volume object.
 */
/*===========================================================================*/
class StochasticTetrahedraRenderer : public kvs::StochasticRendererBase
{
    kvsModuleName( kvs::StochasticTetrahedraRenderer );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::StochasticRendererBase );

public:

    StochasticTetrahedraRenderer( void );

    StochasticTetrahedraRenderer( kvs::UnstructuredVolumeObject* object );

public:

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

public:

    void setTransferFunction( const kvs::TransferFunction& transfer_function );

    void attachObject( const kvs::UnstructuredVolumeObject* object );
};

} // end of namespace kvs

#endif // KVS__STOCHASTIC_TETRAHEDRA_RENDERER_H_INCLUDE