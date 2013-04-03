/*****************************************************************************/
/**
 *  @file   ParticleBasedRenderer.h
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
#ifndef KVS__GPU__KU__PARTICLE_BASED_RENDERER_H_INCLUDE
#define KVS__GPU__KU__PARTICLE_BASED_RENDERER_H_INCLUDE

#include <kvs/VolumeRendererBase>
#include <kvs/PointObject>
#include <kvs/Module>
#include <kvs/Texture2D>
#include <kvs/RenderBuffer>
#include <kvs/VertexBufferObject>
#include <kvs/FrameBufferObject>
#include <kvs/FragmentShader>
#include <kvs/VertexShader>
#include <kvs/ProgramObject>
#include <kvs/EnsembleAverageBuffer>


namespace kvs
{

namespace gpu
{

namespace ku
{

#define KVS_GPU_KU_PARTICLE_VOLUME_RENDERER__NORMAL_TYPE_IS_BYTE // *_BYTE or *_FLOAT

/*===========================================================================*/
/**
 *  @brief  GPU allocation memory type.
 */
/*===========================================================================*/
class ParticleBasedRenderer : public kvs::VolumeRendererBase
{
    kvsModuleName( kvs::gpu::ku::ParticleBasedRenderer );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::VolumeRendererBase );

protected:

    class Particles;
    class Renderer;

protected:

    typedef GLushort IndexType;
    typedef GLubyte ColorType;
    typedef GLfloat CoordType;
#if defined( KVS_GPU_KU_PARTICLE_VOLUME_RENDERER__NORMAL_TYPE_IS_FLOAT )
    typedef GLfloat NormalType;
#elif defined( KVS_GPU_KU_PARTICLE_VOLUME_RENDERER__NORMAL_TYPE_IS_BYTE )
    typedef GLbyte NormalType;
#else
#error "KVS_GPU_KU_PARTICLE_VOLUME_RENDERER_NORMAL_TYPE_IS_* is not defined."
#endif

    // Reference data (NOTE: not allocated in thie class).
    const kvs::PointObject* m_ref_point; ///< pointer to the point data

    size_t m_subpixel_level; ///< subpixel level
    size_t m_repetition_level; ///< repetition level
    size_t m_coarse_level; ///< repetition level for coarse rendering (LOD)
    float m_zooming_factor; ///< zooming factor
    size_t m_random_texture_size; ///< size of the random number texture
    size_t m_circle_threshold; ///< threshold for the shape of the particle
    size_t m_render_width; ///< extended window width for subpixel processing
    size_t m_render_height; ///< extended window height for subpixel processing
    bool m_enable_pre_downloading; ///< flag whether to donwonload the particles first
    bool m_enable_accumulation_buffer; ///< flag whether to use the accumulation buffer
    bool m_enable_random_texture; ///< flag whether to use the random number texture
    kvs::EnsembleAverageBuffer m_ensemble_buffer; ///< ensemble average buffer
    kvs::Texture2D m_random_texture; ///< random number texture
    kvs::ProgramObject m_zoom_shader; ///< shader (program object) for zooming
    kvs::ProgramObject m_resize_shader; ///< shader (program object) for resizing
    GLint m_loc_point_identifier; ///<
    kvs::FrameBufferObject m_resize_framebuffer; ///< RGB buffer for subpixel processing
    kvs::RenderBuffer m_resize_depthbuffer; ///< depth buffer for subpixel processing
    kvs::Texture2D m_resize_texture; ///< texture for subpixel processing
    kvs::VertexBufferObject* m_vbo; ///< vertex buffer object (VBO) for the particles
    Particles* m_particles; ///< particles on GPU
    Renderer* m_renderer; ///< renderer for VBO
    bool m_enable_lod; ///< enable LOD rendering
    bool m_enable_zooming; ///< enable zooming
    float m_modelview_matrix[16]; ///< modelview matrix

public:

    ParticleBasedRenderer();
    ParticleBasedRenderer( kvs::PointObject* point, const size_t subpixel_level = 1, const size_t repeat_level = 1 );
    virtual ~ParticleBasedRenderer();

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

    void initialize();
    void attachPointObject( const kvs::PointObject* point );
    void setSubpixelLevel( const size_t subpixel_level );
    void setRepetitionLevel( const size_t repetition_level );
    void setRandomTextureSize( const size_t random_texture_size );
    void setCircleThreshold( const size_t circle_threshold );
    void enableLODControl( const size_t coarse_level = 1 );
    void disableLODControl();
    void enableZooming();
    void disableZooming();
    void enableCoarseRendering( const size_t coarse_level = 1 );
    void disableCoarseRendering();
    void enableAccumulationBuffer();
    void disableAccumulationBuffer();
    void enableRandomTexture();
    void disableRandomTexture();

    size_t subpixelLevel() const;
    size_t repetitionLevel() const;
    size_t randomTextureSize() const;
    size_t circleThreshold() const;
    bool isEnabledAccumulationBuffer() const;
    bool isEnabledRandomTexture() const;

protected:

    void create_image( const kvs::PointObject* point, const kvs::Camera* camera, const kvs::Light* light );
    void initialize_opengl();
    void initialize_resize_texture();
    void create_random_texture();
    void align_particles();
    void create_vertexbuffer();
    void download_vertexbuffer( Renderer& renderer, kvs::VertexBufferObject& vbo );
    void draw_vertexbuffer( const Renderer& renderer, kvs::VertexBufferObject& vbo, const float modelview_matrix[16] );
    void calculate_zooming_factor( const kvs::PointObject* point, const kvs::Camera* camera );
    void setup_zoom_shader( const float modelview_matrix[16] );
    void setup_resize_shader();

}; // end of class

/*===========================================================================*/
/**
 *  @brief  Particle class for PBVR.
 */
/*===========================================================================*/
class ParticleBasedRenderer::Particles
{
private:

    size_t m_nvertices; ///< number of vertices
    ParticleBasedRenderer::IndexType* m_indices; ///< index array
    ParticleBasedRenderer::CoordType* m_coords; ///< coordinate value array
    ParticleBasedRenderer::NormalType* m_normals; ///< normal vector array
    ParticleBasedRenderer::ColorType* m_colors; ///< color value array

public:

    Particles();
    ~Particles();

    void release();
    void create( const size_t nvertices, const bool has_normal, const bool has_index );

    bool hasIndex() const;
    bool hasNormal() const;
    size_t nvertices() const;
    size_t byteSizePerVertex() const;
    size_t byteSize() const;
    const ParticleBasedRenderer::IndexType* indices() const;
    const ParticleBasedRenderer::CoordType* coords() const;
    const ParticleBasedRenderer::NormalType* normals() const;
    const ParticleBasedRenderer::ColorType* colors() const;
    ParticleBasedRenderer::IndexType* indices();
    ParticleBasedRenderer::CoordType* coords();
    ParticleBasedRenderer::NormalType* normals();
    ParticleBasedRenderer::ColorType* colors();
};

/*===========================================================================*/
/**
 *  @brief  VBO rendering information class
 */
/*===========================================================================*/
class ParticleBasedRenderer::Renderer
{
    const ParticleBasedRenderer::Particles* m_particles; //< pointer to the particles
    size_t m_start; ///< start number of input vertices
    size_t m_count; ///< number of vertices
    size_t m_off_index; ///< offset bytes for the index array
    size_t m_off_coord; ///< offset bytes for the coodinate value array
    size_t m_off_normal; ///< offset bytes for the normal vector array
    size_t m_off_color; ///< offset bytes for the color value array
    size_t m_loc_identifier; ///< 

public:

    Renderer();

    void set( const ParticleBasedRenderer::Particles* particles, const size_t start, const size_t count, const size_t loc_identifier );
    size_t download( kvs::VertexBufferObject& vbo );
    void draw() const;
    size_t nvertices() const;
    size_t byteSizePerVertex() const;
    size_t byteSize() const;
};

} // end of namespace ku

} // end of namespace gpu

} // end of namespace kvs

#endif
