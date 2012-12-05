/*****************************************************************************/
/**
 *  @file   StochasticMultivariateRenderer.h
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
#ifndef KVS__GLEW__STOCHASTIC_MULTIVARITE_TETRAHEDRA_RENDERER_H_INCLUDE
#define KVS__GLEW__STOCHASTIC_MULTIVARITE_TETRAHEDRA_RENDERER_H_INCLUDE

#include "StochasticRendererBase.h"
#include <kvs/UnstructuredVolumeObject>
#include <kvs/TransferFunction>


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Stochastic renderer class for unstructured volume object.
 */
/*===========================================================================*/
class StochasticMultivariateTetrahedraRenderer : public kvs::glew::StochasticRendererBase
{
    kvsModuleName( kvs::glew::StochasticMultivariateTetrahedraRenderer );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::glew::StochasticRendererBase );

public:

    StochasticMultivariateTetrahedraRenderer( void );

    StochasticMultivariateTetrahedraRenderer( kvs::UnstructuredVolumeObject* object );

public:

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

public:

    void attachObject( const kvs::UnstructuredVolumeObject* object );

    void setTransferFunction( const kvs::TransferFunction& tfunc, const size_t index );
};

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__STOCHASTIC_MULTIVARIATE_TETRAHEDRA_RENDERER_H_INCLUDE
