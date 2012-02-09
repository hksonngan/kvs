/*****************************************************************************/
/**
 *  @file   StochasticRenderingEngine.cpp
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
#include "StochasticRenderingEngine.h"


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticRenderingEngine class.
 */
/*===========================================================================*/
StochasticRenderingEngine::StochasticRenderingEngine( void )
{
    this->initialize();
}

/*===========================================================================*/
/**
 *  @brief  Destroys the StochasticRenderingEngine class.
 */
/*===========================================================================*/
StochasticRenderingEngine::~StochasticRenderingEngine( void )
{
    this->clear();
}

/*===========================================================================*/
/**
 *  @brief  Initializes the member parameters.
 */
/*===========================================================================*/
void StochasticRenderingEngine::initialize( void )
{
    m_width = 0;
    m_height = 0;
    m_repetition_count = 0;
    m_enable_shading = true;
    m_shader = NULL;
    m_enable_updating_vbo = false;
}

/*===========================================================================*/
/**
 *  @brief  Clears the allocated member parameters.
 */
/*===========================================================================*/
void StochasticRenderingEngine::clear( void )
{
    if ( m_shader )
    {
        delete m_shader;
        m_shader = NULL;
    }
}

/*===========================================================================*/
/**
 *  @brief  Enables shading.
 */
/*===========================================================================*/
void StochasticRenderingEngine::enableShading( void )
{
    m_enable_shading = true;
}

/*===========================================================================*/
/**
 *  @brief  Disable shading.
 */
/*===========================================================================*/
void StochasticRenderingEngine::disableShading( void )
{
    m_enable_shading = false;
}

/*===========================================================================*/
/**
 *  @brief  Returns whether or not the shading is enabled.
 *  @return true, if the shading is enabled
 */
/*===========================================================================*/
const bool StochasticRenderingEngine::isEnabledShading( void ) const
{
    return( m_enable_shading );
}

/*===========================================================================*/
/**
 *  @brief  Creates and links the shaders.
 *  @param  program_object [in] program object
 *  @param  vertex_source [in] vertex shader source
 *  @param  fragment_source [in] fragment shader source
 */
/*===========================================================================*/
void StochasticRenderingEngine::create_shaders(
    kvs::glew::ProgramObject& program_object,
    const kvs::glew::ShaderSource& vertex_source,
    const kvs::glew::ShaderSource& fragment_source )
{
    // Vertex shader.
    kvs::glew::VertexShader vertex_shader;
    if ( !vertex_shader.create( vertex_source ) )
    {
        GLenum error = glGetError();
        kvsMessageError( "VertexShader compile failed: %s(%d)\n", gluErrorString(error), error );
        std::cout << "error log:" << std::endl;
        std::cout << vertex_shader.log() << std::endl;
    }

    // Fragment shader.
    kvs::glew::FragmentShader fragment_shader;
    if ( !fragment_shader.create( fragment_source ) )
    {
        GLenum error = glGetError();
        kvsMessageError( "FragmentShader compile failed: %s(%d)\n", gluErrorString(error), error );
        std::cout << "error log:" << std::endl;
        std::cout << fragment_shader.log() << std::endl;
    }

    // Link the shaders.
    if ( !program_object.link( vertex_shader, fragment_shader ) )
    {
        GLenum error = glGetError();
        kvsMessageError( "ShaderProgram link failed: %s(%d)\n", gluErrorString(error), error );
        std::cout << "error log:" << std::endl;
        std::cout << program_object.log() << std::endl;
        return;
    }
}

/*===========================================================================*/
/**
 *  @brief  Sets the rendering screen size.
 *  @param  width [in] rendering screen width
 *  @param  height [in] rendering screen height
 */
/*===========================================================================*/
void StochasticRenderingEngine::set_render_size( const size_t width, const size_t height )
{
    m_width = width;
    m_height = height;
}

/*===========================================================================*/
/**
 *  @brief  Sets the random number texture for the stochastic color assignment.
 *  @param  random_texture [in] random ranumber texture
 */
/*===========================================================================*/
void StochasticRenderingEngine::set_random_texture( const kvs::Texture2D& random_texture )
{
    m_random_texture = random_texture;
}

/*===========================================================================*/
/**
 *  @brief  Enables updating VBO.
 */
/*===========================================================================*/
void StochasticRenderingEngine::enable_updating_vbo( void )
{
    m_enable_updating_vbo = true;
}

/*===========================================================================*/
/**
 *  @brief  Disables updating VBO.
 */
/*===========================================================================*/
void StochasticRenderingEngine::disable_updating_vbo( void )
{
    m_enable_updating_vbo = false;
}

/*===========================================================================*/
/**
 *  @brief  Returns whether or not the updating of VBO is enabled.
 *  @return true, if the updating of VBO is enabled
 */
/*===========================================================================*/
const bool StochasticRenderingEngine::is_enabled_updating_vbo( void ) const
{
    return( m_enable_updating_vbo );
}

} // end of namespace glew

} // end of namespace kvs
