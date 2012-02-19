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
#ifndef KVS__GLEW__STOCHASTIC_MULTIPLE_TETRAHEDRA_RENDERER_H_INCLUDE
#define KVS__GLEW__STOCHASTIC_MULTIPLE_TETRAHEDRA_RENDERER_H_INCLUDE

#include "StochasticRendererBase.h"
#include "StochasticMultipleTetrahedraEngine.h"
#include <kvs/UnstructuredVolumeObject>


namespace kvs
{

namespace glew
{

class StochasticMultipleTetrahedraRenderer : public kvs::glew::StochasticRendererBase
{
    friend class StochasticMultipleTetrahedraCompositor;

    typedef kvs::glew::StochasticRendererBase BaseClass;

protected:

    kvs::glew::StochasticMultipleTetrahedraEngine* m_engine;
    kvs::Texture2D m_extra_texture;

public:

    StochasticMultipleTetrahedraRenderer( void );

    StochasticMultipleTetrahedraRenderer(
        const kvs::UnstructuredVolumeObject* volume1,
        const kvs::UnstructuredVolumeObject* volume2 );

public:

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

    void attachObjects(
        const kvs::UnstructuredVolumeObject* object1,
        const kvs::UnstructuredVolumeObject* object2 );

protected:

    void set_rendering_engine( kvs::glew::StochasticMultipleTetrahedraEngine* rendering_engine );

    void create_image( const kvs::Camera* camera, const kvs::Light* light );

    void initialize_framebuffer_texture( void );
};

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__STOCHASTIC_MULTIPLE_TETRAHEDRA_RENDERER_H_INCLUDE
