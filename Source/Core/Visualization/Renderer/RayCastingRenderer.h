/****************************************************************************/
/**
 *  @file   RayCastingRenderer.h
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
/****************************************************************************/
#ifndef KVS__RAY_CASTING_RENDERER_H_INCLUDE
#define KVS__RAY_CASTING_RENDERER_H_INCLUDE

#include <kvs/VolumeRendererBase>
#include <kvs/TransferFunction>
#include <kvs/StructuredVolumeObject>
#include <kvs/Module>


namespace kvs
{

/*==========================================================================*/
/**
 *  Ray casting volume renderer.
 */
/*==========================================================================*/
class RayCastingRenderer : public kvs::VolumeRendererBase
{
    kvsModuleName( kvs::RayCastingRenderer );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::VolumeRendererBase );

private:

    float m_step; ///< sampling step
    float m_opaque; ///< opaque value for early ray termination
    size_t m_ray_width; ///< ray width
    bool m_enable_lod; ///< enable LOD rendering
    float m_modelview_matrix[16]; ///< modelview matrix

public:

    RayCastingRenderer();
    RayCastingRenderer( const kvs::TransferFunction& tfunc );
    template <typename ShadingType>
    RayCastingRenderer( const ShadingType shader );
    virtual ~RayCastingRenderer();

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );
    void setSamplingStep( const float step );
    void setOpaqueValue( const float opaque );
    void enableLODControl( const size_t ray_width = 3 );
    void disableLODControl();
    void enableCoarseRendering( const size_t ray_width = 3 );
    void disableCoarseRendering();

private:

    template <typename T>
    void rasterize(
        const kvs::StructuredVolumeObject* volume,
        const kvs::Camera* camera,
        const kvs::Light* light );
};

} // end of namespace kvs

#include "RayCastingRendererGLSL.h"

#endif // KVS__RAY_CASTING_RENDERER_H_INCLUDE
