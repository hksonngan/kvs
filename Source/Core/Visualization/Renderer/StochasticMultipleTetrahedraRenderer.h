/*****************************************************************************/
/**
 *  @file   StochasticMultipleTetrahedraRenderer.h
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
#ifndef KVS__STOCHASTIC_MULTIPLE_TETRAHEDRA_RENDERER_H_INCLUDE
#define KVS__STOCHASTIC_MULTIPLE_TETRAHEDRA_RENDERER_H_INCLUDE

#include "StochasticRendererBase.h"
#include "StochasticMultipleTetrahedraEngine.h"
#include <kvs/UnstructuredVolumeObject>


namespace kvs
{

class StochasticMultipleTetrahedraRenderer : public kvs::StochasticRendererBase
{
    friend class StochasticMultipleTetrahedraCompositor;
    typedef kvs::StochasticRendererBase BaseClass;

protected:

    kvs::StochasticMultipleTetrahedraEngine* m_engine;
    kvs::Texture2D m_extra_texture;

public:

    StochasticMultipleTetrahedraRenderer();
    StochasticMultipleTetrahedraRenderer(
        const kvs::UnstructuredVolumeObject* volume1,
        const kvs::UnstructuredVolumeObject* volume2 );

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );
    void attachObjects(
        const kvs::UnstructuredVolumeObject* object1,
        const kvs::UnstructuredVolumeObject* object2 );
    void setTransferFunction( const kvs::TransferFunction& transfer_function, const size_t index );

protected:

    void set_rendering_engine( kvs::StochasticMultipleTetrahedraEngine* rendering_engine );
    void create_image( const kvs::Camera* camera, const kvs::Light* light );
    void initialize_framebuffer_texture();
};

} // end of namespace kvs

#endif // KVS__STOCHASTIC_MULTIPLE_TETRAHEDRA_RENDERER_H_INCLUDE
