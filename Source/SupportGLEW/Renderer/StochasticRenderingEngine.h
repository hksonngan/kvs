/*****************************************************************************/
/**
 *  @file   StochasticRenderingEngine.h
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
#ifndef KVS__GLEW__STOCHASTIC_RENDERING_ENGINE_H_INCLUDE
#define KVS__GLEW__STOCHASTIC_RENDERING_ENGINE_H_INCLUDE

#include <kvs/ClassName>
#include <kvs/Shader>
#include <kvs/Texture2D>
#include <kvs/ObjectBase>
#include <kvs/glew/VertexShader>
#include <kvs/glew/FragmentShader>
#include <kvs/glew/ProgramObject>


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Stochastic rendering engine class.
 */
/*===========================================================================*/
class StochasticRenderingEngine
{
    friend class StochasticRendererBase;

    // Class name.
    kvsClassName( kvs::glew::StochasticRenderingEngine );

public:

    enum EngineType
    {
        Point = 0,
        Line,
        Polygon,
        StructuredVolume,
        Tetrahedra,
        Unknown
    };

protected:

    size_t m_width; ///< rendering screen width
    size_t m_height; ///< rendering screen height
    size_t m_repetition_count; ///< counter for the repetition process
    bool m_enable_shading; ///< flag to enable shading.
    kvs::Shader::shader_type* m_shader; ///< shading method
    kvs::Texture2D m_random_texture; ///< random number texture for the stochastic color assignment in GPU.
    kvs::glew::ProgramObject m_shader_program; ///< GLSL shader program.
    bool m_enable_updating_vbo; ///< flag to enable updating vertex buffer
    bool m_enable_exact_depth_testing; ///< flag to enable exact depth testing

public:

    StochasticRenderingEngine( void );

    virtual ~StochasticRenderingEngine( void );

public:

    void initialize( void );

    void clear( void );

    template <typename ShadingType>
    void setShader( const ShadingType shader );

    void enableShading( void );

    void disableShading( void );

    const bool isEnabledShading( void ) const;

public:

    virtual const kvs::ObjectBase* object( void ) const = 0;

    virtual const EngineType engineType( void ) const = 0;

    virtual void attachObject( const kvs::ObjectBase* object ) = 0;

    virtual void clearEnsembleBuffer( void ) = 0;

protected:

    void create_shaders(
        kvs::glew::ProgramObject& program_object,
        const kvs::glew::ShaderSource& vertex_source,
        const kvs::glew::ShaderSource& fragment_source );

    void set_render_size( const size_t width, const size_t height );

    void set_random_texture( const kvs::Texture2D& random_texture );

    void enable_updating_vbo( void );

    void disable_updating_vbo( void );

    const bool is_enabled_updating_vbo( void ) const;

    void enable_exact_depth_testing( void );

    void disable_exact_depth_testing( void );

    const bool is_enabled_exact_depth_testing( void ) const;

protected:

    virtual void setup_shader( const float modelview_matrix[16] ) = 0;

    virtual void initialize_shader( void ) = 0;

    virtual void create_vertex_buffer( void ) = 0;

    virtual void download_vertex_buffer( void ) = 0;

    virtual void draw_vertex_buffer( const float modelview_matrix[16] ) = 0;
};

template <typename ShadingType>
inline void StochasticRenderingEngine::setShader( const ShadingType shader )
{
    if ( m_shader )
    {
        delete m_shader;
        m_shader = NULL;
    }

    m_shader = new ShadingType( shader );
    if ( !m_shader )
    {
        kvsMessageError( "Cannot create a specified shader." );
    }
};

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__STOCHASTIC_RENDERING_ENGINE_H_INCLUDE
