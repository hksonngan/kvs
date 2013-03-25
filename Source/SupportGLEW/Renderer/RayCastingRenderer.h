/*****************************************************************************/
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
/*****************************************************************************/
#ifndef KVS__GLEW__RAY_CASTING_RENDERER_H_INCLUDE
#define KVS__GLEW__RAY_CASTING_RENDERER_H_INCLUDE

#include <kvs/Module>
#include <kvs/VolumeRendererBase>
#include <kvs/Texture1D>
#include <kvs/Texture2D>
#include <kvs/Texture3D>
#include <kvs/ObjectBase>
#include <kvs/Camera>
#include <kvs/Light>
#include <kvs/StructuredVolumeObject>
#include <kvs/glew/VertexBufferObject>
#include <kvs/glew/ProgramObject>
#include <kvs/glew/ShaderSource>
#include <kvs/glew/FrameBufferObject>


namespace kvs
{

namespace glew
{

#define KVS_GLEW_RAY_CASTING_RENDERER__EMBEDDED_SHADER

/*===========================================================================*/
/**
 *  @brief  RayCastingRenderer class.
 */
/*===========================================================================*/
class RayCastingRenderer : public kvs::VolumeRendererBase
{
    kvsModuleName( kvs::glew::RayCastingRenderer );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::VolumeRendererBase );

public:

    enum DrawingBuffer
    {
        FrontFace,
        BackFace,
        Volume
    };

protected:

    bool m_draw_front_face; ///< frag for drawing front face
    bool m_draw_back_face; ///< frag for drawing back face
    bool m_draw_volume; ///< frag for drawing volume
    bool m_enable_jittering; ///< frag for stochastic jittering
    float m_step; ///< sampling step
    float m_opaque; ///< opaque value for early ray termination
    kvs::Texture1D m_transfer_function_texture; ///< transfer function texture
    kvs::Texture2D m_jittering_texture; ///< texture for stochastic jittering
    kvs::Texture2D m_entry_points; ///< entry point texture
    kvs::Texture2D m_exit_points; ///< exit point texture
    kvs::glew::FrameBufferObject m_entry_exit_framebuffer; ///< framebuffer object for entry/exit point texture
    kvs::glew::VertexBufferObject m_bounding_cube; ///< bounding cube (VBO)
    kvs::Texture3D m_volume_data; ///< volume data (3D texture)
    kvs::glew::ProgramObject m_ray_caster; ///< ray casting shader
    kvs::glew::ProgramObject m_bounding_cube_shader; ///< bounding cube shader
    kvs::Texture2D m_color_texture;
    kvs::Texture2D m_depth_texture;

public:

    RayCastingRenderer();
    RayCastingRenderer( const kvs::TransferFunction& tfunc );
    template <typename ShadingType>
    RayCastingRenderer( const ShadingType shader );
    virtual ~RayCastingRenderer();

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

    void setSamplingStep( const float step );
    void setOpaqueValue( const float opaque );
    void setDrawingBuffer( const DrawingBuffer drawing_buffer );
    void setTransferFunction( const kvs::TransferFunction& tfunc );
    void enableJittering();
    void disableJittering();

protected:

    void initialize();
    void create_image( const kvs::StructuredVolumeObject* volume, const kvs::Camera* camera, const kvs::Light* light );
    void initialize_shaders( const kvs::StructuredVolumeObject* volume );
    void create_entry_points();
    void create_exit_points();
    void create_jittering_texture();
    void create_bounding_cube( const kvs::StructuredVolumeObject* volume );
    void create_transfer_function( const kvs::StructuredVolumeObject* volume );
    void create_volume_data( const kvs::StructuredVolumeObject* volume );
    void draw_bounding_cube();
    void draw_quad( const float opacity );
};

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__RAY_CASTING_RENDERER_H_INCLUDE
