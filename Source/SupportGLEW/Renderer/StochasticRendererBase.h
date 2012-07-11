/*****************************************************************************/
/**
 *  @file   StochasticRendererBase.h
 *  @author Jun Nishimura
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
#ifndef KVS__GLEW__STOCHASTIC_RENDERER_BASE_H_INCLUDE
#define KVS__GLEW__STOCHASTIC_RENDERER_BASE_H_INCLUDE

#include <kvs/ClassName>
#include <kvs/Module>
#include <kvs/ObjectBase>
#include <kvs/RendererBase>

#include <kvs/glew/FrameBufferObject>
#include <kvs/glew/EnsembleAverageBuffer>

#include "StochasticRenderingEngine.h"

#include <vector>


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Base class of stochastic renderer.
 */
/*===========================================================================*/
class StochasticRendererBase : public kvs::RendererBase
{
    friend class StochasticRenderingCompositor;

    // Class name.
    kvsClassName( kvs::glew::StochasticRendererBase );

    // Module information.
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::RendererBase );

public:

    typedef std::vector<kvs::glew::StochasticRenderingEngine*> RenderingEngineList;

protected:

    size_t m_width; ///< rendering screen width
    size_t m_height; ///< rendering screen height
    size_t m_repetition_level; ///< repetition level
    size_t m_coarse_level; ///< coarse rendering level
    kvs::glew::EnsembleAverageBuffer m_ensemble_buffer; ///< ensemble buffer
    kvs::glew::FrameBufferObject m_framebuffer; ///< framebuffer object
    kvs::Texture2D m_color_texture; ///< color framebuffer
    kvs::Texture2D m_depth_texture; ///< depth framebuffer
    size_t m_random_texture_size; ///< size of random number texture
    kvs::Texture2D m_random_texture; ///< random number texture
    bool m_enable_lod; ///< flag to enable LOD controlling
    float m_modelview_matrix[16]; ///< modelview matrix
    bool m_clear_ensemble_buffer; ///< flag to clear ensemble buffer
    RenderingEngineList m_rendering_engines; ///< rendering engine list
    bool m_enable_exact_depth_testing; ///< flag to enable exact depth testing

public:

    StochasticRendererBase( void );

    virtual ~StochasticRendererBase( void );

public:

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

public:

    void initialize( void );

    void clear( void );

    void setRenderingEngine( kvs::glew::StochasticRenderingEngine* rendering_engine );

    void clearEnsembleBuffer( void );

    void setRepetitionLevel( const size_t repetition_level );

    void enableLODControl( const size_t coarse_level = 1 );

    void disableLODControl( void );

protected:

    void create_image( const kvs::Camera* camera, const kvs::Light* light );

    kvs::glew::StochasticRenderingEngine* get_engine( const size_t index );

    kvs::glew::StochasticRenderingEngine* find_engine( const kvs::ObjectBase* object );

    kvs::glew::StochasticRenderingEngine* find_engine( const std::string object_name );

    bool erase_engine( const kvs::ObjectBase* object );

    bool erase_engine( const std::string object_name );

    void enable_exact_depth_testing( void );

    void disable_exact_depth_testing( void );

protected:

    void initialize_opengl( void );

    void initialize_framebuffer_texture( void );

    void create_texture(
        kvs::Texture2D& texture,
        kvs::glew::FrameBufferObject& framebuffer,
        GLint internal_format,
        GLenum external_format,
        GLenum external_type,
        GLenum attachment );

    void initialize_random_texture( void );
};

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__STOCHASTIC_RENDERER_BASE_H_INCLUDE
