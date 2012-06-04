/*****************************************************************************/
/**
 *  @file   StochasticRendererBase.cpp
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
#include "StochasticRendererBase.h"
#include "StochasticTetrahedraEngine.h"
#include <algorithm>
#include <cstring>
#include <kvs/MersenneTwister>

namespace
{

/*===========================================================================*/
/**
 *  @brief  Sorting class for rendering engine.
 */
/*===========================================================================*/
struct SortingByEngineType
{
    bool operator () ( const kvs::glew::StochasticRenderingEngine* r1, const kvs::glew::StochasticRenderingEngine* r2 )
    {
        return( r1->engineType() < r2->engineType() );
    }
};

}

namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticRendererBase class
 */
/*===========================================================================*/
StochasticRendererBase::StochasticRendererBase( void )
{
    this->initialize();
}

/*===========================================================================*/
/**
 *  @brief  Destroys the StochasticRendererBase class.
 */
/*===========================================================================*/
StochasticRendererBase::~StochasticRendererBase( void )
{
    this->clear();
}

/*===========================================================================*/
/**
 *  @brief  Renders the object.
 *  @param  object [in] pointer to the object (not used)
 *  @param  camera [in] pointer to the camera
 *  @param  light [in] pointer to the light
 */
/*===========================================================================*/
void StochasticRendererBase::exec(
    kvs::ObjectBase* object,
    kvs::Camera*     camera,
    kvs::Light*      light )
{
    kvs::IgnoreUnusedVariable( object );

    BaseClass::m_timer.start();
    this->create_image( camera, light );
    BaseClass::m_timer.stop();
}

/*===========================================================================*/
/**
 *  @brief  Initializes the member parameters.
 */
/*===========================================================================*/
void StochasticRendererBase::initialize( void )
{
    m_width = 0;
    m_height = 0;

    m_repetition_level = 1;
    m_coarse_level = 1;

    m_random_texture_size = 1024;

    m_enable_lod = false;
    memset( m_modelview_matrix, 0, sizeof( m_modelview_matrix ) );

    m_clear_ensemble_buffer = false;

    m_rendering_engines.clear();

    m_enable_exact_depth_testing = false;
}

/*===========================================================================*/
/**
 *  @brief  Clears the allocated member parameters.
 */
/*===========================================================================*/
void StochasticRendererBase::clear( void )
{
    for ( size_t i = 0; i < m_rendering_engines.size(); i++ )
    {
        kvs::glew::StochasticRenderingEngine* renderer = m_rendering_engines[i];
        if ( renderer )
        {
            delete renderer;
            renderer = NULL;
        }
    }
    m_rendering_engines.clear();
}

/*===========================================================================*/
/**
 *  @brief  Sets a rendering engine.
 *  @param  engine [in] pointer to the rendering engine
 */
/*===========================================================================*/
void StochasticRendererBase::setRenderingEngine( kvs::glew::StochasticRenderingEngine* engine )
{
    bool has_engine = false;
    for ( size_t i = 0; i < m_rendering_engines.size(); i++ )
    {
        if ( m_rendering_engines[i] == engine ) has_engine = true;
    }
    if ( !has_engine ) m_rendering_engines.push_back( engine );

    std::sort( m_rendering_engines.begin(), m_rendering_engines.end(), ::SortingByEngineType() );
}

/*===========================================================================*/
/**
 *  @brief  Clears the ensemble buffer.
 */
/*===========================================================================*/
void StochasticRendererBase::clearEnsembleBuffer( void )
{
    m_clear_ensemble_buffer = true;
}

/*===========================================================================*/
/**
 *  @brief  Sets repetition level.
 *  @param  repetition_level [in] repetition level
 */
/*===========================================================================*/
void StochasticRendererBase::setRepetitionLevel( const size_t repetition_level )
{
    m_repetition_level = repetition_level;
    m_coarse_level = repetition_level;
}

/*===========================================================================*/
/**
 *  @brief  Enables LOD control.
 *  @param  coarse_level [in] coarse rendering level
 */
/*===========================================================================*/
void StochasticRendererBase::enableLODControl( const size_t coarse_level )
{
    m_enable_lod = true;
    m_coarse_level = coarse_level;
}

/*===========================================================================*/
/**
 *  @brief  Disables LOD control.
 */
/*===========================================================================*/
void StochasticRendererBase::disableLODControl( void )
{
    m_enable_lod = false;
}

/*===========================================================================*/
/**
 *  @brief  Creates rendering image.
 *  @param  camera [in] pointer to the camera
 *  @param  light [in] pointer to the light
 */
/*===========================================================================*/
void StochasticRendererBase::create_image( const kvs::Camera* camera, const kvs::Light* light )
{
    glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT );

    RendererBase::initialize();

    bool retain_ensemble_buffer = true;

    // Following processes are executed once.
    if ( m_width == 0 && m_height == 0 )
    {
        m_ensemble_buffer.disableAccumulationBuffer();

        this->initialize_opengl();
        this->initialize_random_texture();

        for ( size_t i = 0; i < m_rendering_engines.size(); i++ )
        {
            if ( m_enable_exact_depth_testing )
            {
                m_rendering_engines[i]->enable_exact_depth_testing();
            }

            m_rendering_engines[i]->set_random_texture( m_random_texture );
            m_rendering_engines[i]->initialize_shader();
            m_rendering_engines[i]->create_vertex_buffer();
        }

        glGetFloatv( GL_MODELVIEW_MATRIX, m_modelview_matrix );
        retain_ensemble_buffer = false;
    }

    // Get the modelview matrix.
    float modelview_matrix[16];
    glGetFloatv( GL_MODELVIEW_MATRIX, modelview_matrix );
    static kvs::Vector3f light_position = light->position();

    // LOD control.
    size_t coarse_level = m_repetition_level;
    {
        if ( light_position != light->position() )
        {
            if ( m_enable_lod ) coarse_level = m_coarse_level;
            retain_ensemble_buffer = false;
        }
        else
        {
            for ( size_t i = 0; i < 16; i++ )
            {
                if ( m_modelview_matrix[i] != modelview_matrix[i] )
                {
                    if ( m_enable_lod ) coarse_level = m_coarse_level;
                    retain_ensemble_buffer = false;
                    break;
                }
            }
        }
        memcpy( m_modelview_matrix, modelview_matrix, sizeof( modelview_matrix ) );
    }

    // Following processes are executed when the window size is changed.
    if ( ( m_width  != camera->windowWidth() ) ||
         ( m_height != camera->windowHeight() ) )

    {
        m_width  = camera->windowWidth();
        m_height = camera->windowHeight();

        for ( size_t i = 0; i < m_rendering_engines.size(); i++ )
        {
            m_rendering_engines[i]->set_render_size( m_width, m_height );
        }

        m_ensemble_buffer.create( m_width, m_height );

        this->initialize_framebuffer_texture();
        retain_ensemble_buffer = false;
    }

    for ( size_t i = 0; i < m_rendering_engines.size(); i++ )
    {
        if ( m_rendering_engines[i]->is_enabled_updating_vbo() )
        {
            m_rendering_engines[i]->create_vertex_buffer();
            m_rendering_engines[i]->disable_updating_vbo();
        }
    }

    const size_t repetition_count = coarse_level;
    if ( !retain_ensemble_buffer || m_clear_ensemble_buffer )
    {
        glClear( GL_ACCUM_BUFFER_BIT );
        m_ensemble_buffer.clear();
        for ( size_t i = 0; i < m_rendering_engines.size(); i++ )
        {
            m_rendering_engines[i]->clearEnsembleBuffer();
        }
    }

    // Draw objects.
    for ( size_t rp = 0; rp < repetition_count; rp++ )
    {
        m_framebuffer.bind();

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glEnable( GL_DEPTH_TEST );

        // draw vertex buffer.
        for ( size_t i = 0; i < m_rendering_engines.size(); i++ )
        {
            if ( m_enable_exact_depth_testing )
            {
                if ( m_rendering_engines[i]->engineType() == kvs::glew::StochasticRenderingEngine::Tetrahedra )
                {
                    kvs::glew::StochasticTetrahedraEngine* engine
                        = static_cast<kvs::glew::StochasticTetrahedraEngine*>( m_rendering_engines[i] );
                    engine->set_depth_texture( m_depth_texture );
                }
            }

            m_rendering_engines[i]->draw_vertex_buffer( modelview_matrix );
        }

        // render to the screen.
        m_framebuffer.disable();
        m_ensemble_buffer.bind();

        glMatrixMode( GL_MODELVIEW );  glPushMatrix(); glLoadIdentity();
        glMatrixMode( GL_PROJECTION ); glPushMatrix(); glLoadIdentity();
        glOrtho( 0, 1, 0, 1, -1, 1 );

        m_color_texture.bind();

        glDisable( GL_DEPTH_TEST );
        glDisable( GL_LIGHTING );
        glBegin( GL_QUADS );
        glColor4f( 1.0, 1.0, 1.0, m_ensemble_buffer.opacity() );
        glTexCoord2f( 1, 1 );  glVertex2f( 1, 1 );
        glTexCoord2f( 0, 1 );  glVertex2f( 0, 1 );
        glTexCoord2f( 0, 0 );  glVertex2f( 0, 0 );
        glTexCoord2f( 1, 0 );  glVertex2f( 1, 0 );
        glEnd();

        m_color_texture.unbind();
        glPopMatrix(); // Pop PROJECTION matrix
        glMatrixMode( GL_MODELVIEW );
        glPopMatrix(); // Pop MODELVIEW matrix

        m_ensemble_buffer.add();
    }
    m_ensemble_buffer.draw();

    m_clear_ensemble_buffer = false;

    light_position = light->position();

    glPopAttrib();
    glFinish();
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer of the rendering engine which is specified by given index.
 *  @param  index [in] index of engine
 *  @return pointer to the rendering engine
 */
/*===========================================================================*/
kvs::glew::StochasticRenderingEngine* StochasticRendererBase::get_engine( const size_t index )
{
    return m_rendering_engines[ index ];
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer of the rendering in which the given object is stored.
 *  @param  object [in] pointer to the object
 *  @return pointer to the rendering engine
 */
/*===========================================================================*/
kvs::glew::StochasticRenderingEngine* StochasticRendererBase::find_engine( const kvs::ObjectBase* object )
{
    RenderingEngineList::iterator engine = m_rendering_engines.begin();
    RenderingEngineList::iterator last = m_rendering_engines.end();
    while ( engine != last )
    {
        if ( (*engine)->object() == object ) return *engine;
        ++engine;
    }

    return NULL;
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the rendering engine in which the specified object by the name is stored.
 *  @param  object_name [in] object name
 *  @return pointer to the rendering engine
 */
/*===========================================================================*/
kvs::glew::StochasticRenderingEngine* StochasticRendererBase::find_engine( const std::string object_name )
{
    RenderingEngineList::iterator engine = m_rendering_engines.begin();
    RenderingEngineList::iterator last = m_rendering_engines.end();
    while ( engine != last )
    {
        if ( (*engine)->object()->name() == object_name ) return *engine;
        ++engine;
    }

    return NULL;
}

/*===========================================================================*/
/**
 *  @brief  Enables exact depth testing.
 */
/*===========================================================================*/
void StochasticRendererBase::enable_exact_depth_testing( void )
{
    m_enable_exact_depth_testing = true;
}

/*===========================================================================*/
/**
 *  @brief  Disables exact depth testing.
 */
/*===========================================================================*/
void StochasticRendererBase::disable_exact_depth_testing( void )
{
    m_enable_exact_depth_testing = false;
}

/*===========================================================================*/
/**
 *  @brief  Initializes several OpenGL state parameters.
 */
/*===========================================================================*/
void StochasticRendererBase::initialize_opengl( void )
{
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );

    glClearAccum( 0.0, 0.0, 0.0, 0.0 );
}

/*===========================================================================*/
/**
 *  @brief  Initializes framebuffer objects and textures.
 */
/*===========================================================================*/
void StochasticRendererBase::initialize_framebuffer_texture( void )
{
    m_framebuffer.create();
    m_framebuffer.bind();

    this->create_texture( m_color_texture, m_framebuffer, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, GL_COLOR_ATTACHMENT0_EXT );
    this->create_texture( m_depth_texture, m_framebuffer, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT, GL_DEPTH_ATTACHMENT_EXT );

    m_framebuffer.disable();

    GLenum error = glGetError();
    if ( error != GL_NO_ERROR )
    {
        kvsMessageError( "framebuffer allocation failed: %s.", gluErrorString(error));
        return;
    }
}

/*===========================================================================*/
/**
 *  @brief  Creates the texture on GPU.
 *  @param  texture [in] texture
 *  @param  framebuffer [in] framebuffer object
 *  @param  internal_format [in] internal texture format
 *  @param  external_format [in] external texture format
 *  @param  external_type [in] external texture type
 *  @param  attachment [in] attachment
 */
/*===========================================================================*/
void StochasticRendererBase::create_texture(
    kvs::Texture2D& texture,
    kvs::glew::FrameBufferObject& framebuffer,
    GLint internal_format,
    GLenum external_format,
    GLenum external_type,
    GLenum attachment )
{
    texture.release();

    texture.setWrapS( GL_CLAMP_TO_EDGE );
    texture.setWrapT( GL_CLAMP_TO_EDGE );
    texture.setMagFilter( GL_LINEAR );
    texture.setMinFilter( GL_LINEAR );

    texture.setPixelFormat( internal_format, external_format, external_type );
    texture.create( m_width, m_height );
    {
        GLenum error = glGetError();
        if ( error != GL_NO_ERROR )
        {
            kvsMessageError( "color buffer allocation failed: %s.", gluErrorString(error));
            return;
        }
    }

    glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, attachment, GL_TEXTURE_2D, texture.id(), 0 );

    texture.unbind();
}

/*===========================================================================*/
/**
 *  @brief  Initializes a random number texture.
 */
/*===========================================================================*/
void StochasticRendererBase::initialize_random_texture( void )
{
    m_random_texture.release();
    m_random_texture.setWrapS( GL_REPEAT );
    m_random_texture.setWrapT( GL_REPEAT );
    m_random_texture.setMagFilter( GL_NEAREST );
    m_random_texture.setMinFilter( GL_NEAREST );
    m_random_texture.setPixelFormat( GL_INTENSITY8,  GL_LUMINANCE, GL_UNSIGNED_BYTE  );

    m_random_texture.create( m_random_texture_size, m_random_texture_size );
    {
        GLenum error = glGetError();
        if ( error != GL_NO_ERROR )
        {
            kvsMessageError( "color buffer allocation failed: %s.", gluErrorString(error) );
            return;
        }
    }

    const size_t npixels = m_random_texture_size * m_random_texture_size;

    kvs::MersenneTwister random;
    GLubyte* pixels = new GLubyte[ npixels ];
    for ( size_t i = 0; i < npixels; i++ )
    {
        pixels[i] = static_cast<GLubyte>( random.randInteger() );
    }
    m_random_texture.download( m_random_texture_size, m_random_texture_size, pixels );
    delete [] pixels;
}

} // end of namespace glew

} // end of namespace kvs
