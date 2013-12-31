/*****************************************************************************/
/**
 *  @file   ParticleBasedRendererGLSL.h
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
#ifndef KVS__GLSL__PARTICLE_BASED_RENDERER_H_INCLUDE
#define KVS__GLSL__PARTICLE_BASED_RENDERER_H_INCLUDE

#include <kvs/RendererBase>
#include <kvs/Module>
#include <kvs/ProgramObject>
#include <kvs/VertexBufferObject>
#include <kvs/Vector4>
#include <kvs/Matrix44>
#include <kvs/Deprecated>
#include "StochasticRendererBase.h"
#include "StochasticRenderingEngine.h"


namespace kvs
{

class PointObject;

namespace glsl
{

/*===========================================================================*/
/**
 *  @brief  Particle-based renderer class.
 */
/*===========================================================================*/
class ParticleBasedRenderer : public kvs::StochasticRendererBase
{
    kvsModuleName( kvs::glsl::ParticleBasedRenderer );
    kvsModuleBaseClass( kvs::StochasticRendererBase );
    kvsModuleCategory( Renderer );

public:

    class Engine;

public:

    ParticleBasedRenderer();
    ParticleBasedRenderer( const kvs::Mat4& m, const kvs::Mat4& p, const kvs::Vec4& v );
    bool isEnabledShuffle() const;
    void setEnabledShuffle( const bool enable );
    void enableShuffle();
    void disableShuffle();
    const kvs::Mat4& initialModelViewMatrix() const;
    const kvs::Mat4& initialProjectionMatrix() const;
    const kvs::Vec4& initialViewport() const;

public:
    // Invalid methods.
    KVS_DEPRECATED( void initialize() ) {}
    KVS_DEPRECATED( void setSubpixelLevel( const size_t level ) ) { setRepetitionLevel( level * level ); }
    KVS_DEPRECATED( void setCircleThreshold( const size_t ) ) {}
    KVS_DEPRECATED( void enableZooming() ) {}
    KVS_DEPRECATED( void disableZooming() ) {}
    KVS_DEPRECATED( void enableCoarseRendering( const size_t level = 1 ) ) {}
    KVS_DEPRECATED( void disableCoarseRendering() ) {}
    KVS_DEPRECATED( void enableAccumulationBuffer() ) {}
    KVS_DEPRECATED( void disableAccumulationBuffer() ) {}
    KVS_DEPRECATED( void enableRandomTexture() ) {}
    KVS_DEPRECATED( void disableRandomTexture() ) {}
    KVS_DEPRECATED( size_t subpixelLevel() const ) { return 1; }
    KVS_DEPRECATED( size_t circleThreshold() const ) { return 3; }
    KVS_DEPRECATED( bool isEnabledAccumulationBuffer() const ) { return false; }
    KVS_DEPRECATED( bool isEnabledRandomTexture() const ) { return true; }

private:
    // Not supported progressive refinement rendering.
    bool isEnabledRefinement() const;
    void enableRefinement();
    void disableRefinement();
};

/*===========================================================================*/
/**
 *  @brief  Engine class for particle-based renderer.
 */
/*===========================================================================*/
class ParticleBasedRenderer::Engine : public kvs::StochasticRenderingEngine
{
private:

    bool m_has_normal; ///< check flag for the normal array
    bool m_enable_shuffle; ///< flag for shuffling particles
    size_t m_random_index; ///< index used for refering the random texture
    kvs::Mat4 m_initial_modelview; ///< initial modelview matrix
    kvs::Mat4 m_initial_projection; ///< initial projection matrix
    kvs::Vec4 m_initial_viewport; ///< initial viewport
    float m_initial_object_depth; ///< initial object depth
    kvs::ProgramObject m_shader_program; ///< zooming shader program
    kvs::VertexBufferObject* m_vbo; ///< vertex buffer objects for each repetition

public:

    Engine();
    Engine( const kvs::Mat4& m, const kvs::Mat4& p, const kvs::Vec4& v );
    virtual ~Engine();
    void release();
    void create( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );
    void update( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );
    void setup( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );
    void draw( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

    bool isEnabledShuffle() const { return m_enable_shuffle; }
    void setEnabledShuffle( const bool enable ) { m_enable_shuffle = enable; }
    void enableShuffle() { this->setEnabledShuffle( true ); }
    void disableShuffle() { this->setEnabledShuffle( false ); }
    const kvs::Mat4& initialModelViewMatrix() const { return m_initial_modelview; }
    const kvs::Mat4& initialProjectionMatrix() const { return m_initial_projection; }
    const kvs::Vec4& initialViewport() const { return m_initial_viewport; }

private:

    void create_shader_program();
    void create_buffer_object( const kvs::PointObject* point );
};

} // end of namespace glsl

} // end of namespace kvs

#include "ParticleBasedRendererRITS.h"

#endif // KVS__GLSL__PARTICLE_BASED_RENDERER_H_INCLUDE
