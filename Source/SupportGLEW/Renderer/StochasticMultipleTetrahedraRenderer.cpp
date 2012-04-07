/*****************************************************************************/
/**
 *  @file   StochasticMultipleTetrahedraRenderer.cpp
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
#include "StochasticMultipleTetrahedraRenderer.h"


namespace kvs
{

namespace glew
{

StochasticMultipleTetrahedraRenderer::StochasticMultipleTetrahedraRenderer( void ):
    m_engine( NULL )
{
    this->set_rendering_engine( new kvs::glew::StochasticMultipleTetrahedraEngine() );
}

StochasticMultipleTetrahedraRenderer::StochasticMultipleTetrahedraRenderer(
    const kvs::UnstructuredVolumeObject* volume1,
    const kvs::UnstructuredVolumeObject* volume2 ):
    m_engine( NULL )
{
//    this->attachObjects( volume1, volume2 );
    this->set_rendering_engine( new kvs::glew::StochasticMultipleTetrahedraEngine( volume1, volume2 ) );
}

void StochasticMultipleTetrahedraRenderer::exec(
    kvs::ObjectBase* object,
    kvs::Camera*     camera,
    kvs::Light*      light )
{
//    kvs::glew::StochasticRenderingEngine* engine = BaseClass::m_rendering_engines[0];
//    if ( !engine->object() ) engine->attachObject( object );

    BaseClass::m_timer.start();
    this->create_image( camera, light );
    BaseClass::m_timer.stop();
}

void StochasticMultipleTetrahedraRenderer::attachObjects(
    const kvs::UnstructuredVolumeObject* object1,
    const kvs::UnstructuredVolumeObject* object2 )
{
    m_engine->attachObjects( object1, object2 );

    BaseClass::clearEnsembleBuffer();
}

void StochasticMultipleTetrahedraRenderer::setTransferFunction( const kvs::TransferFunction& transfer_function, const size_t index )
{
    typedef kvs::glew::StochasticMultipleTetrahedraEngine Engine;
    Engine* engine = static_cast<Engine*>( BaseClass::m_rendering_engines[0] );
    engine->setTransferFunction( transfer_function, index );
}

void StochasticMultipleTetrahedraRenderer::set_rendering_engine( kvs::glew::StochasticMultipleTetrahedraEngine* rendering_engine )
{
    if ( m_engine ) delete m_engine;
    m_engine = rendering_engine;
}

void StochasticMultipleTetrahedraRenderer::create_image( const kvs::Camera* camera, const kvs::Light* light )
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

        if ( m_enable_exact_depth_testing ) { m_engine->enable_exact_depth_testing(); }

        m_engine->set_random_texture( m_random_texture );
        m_engine->initialize_shader();
        m_engine->create_vertex_buffer();

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

        m_engine->set_render_size( m_width, m_height );

        m_ensemble_buffer.create( m_width, m_height );

        this->initialize_framebuffer_texture();
        retain_ensemble_buffer = false;
    }

    if ( m_engine->is_enabled_updating_vbo() )
    {
        m_engine->create_vertex_buffer();
        m_engine->disable_updating_vbo();
    }

    const size_t repetition_count = coarse_level;
    if ( !retain_ensemble_buffer || m_clear_ensemble_buffer )
    {
        glClear( GL_ACCUM_BUFFER_BIT );
        m_ensemble_buffer.clear();
        m_engine->clearEnsembleBuffer();
    }

    // Draw objects.
    for ( size_t rp = 0; rp < repetition_count; rp++ )
    {
        m_framebuffer.bind();

        // Draw multiple buffers.
        const GLenum buffers[] = {
            GL_COLOR_ATTACHMENT0_EXT,
            GL_COLOR_ATTACHMENT1_EXT,
        };
        glDrawBuffers( 2, buffers );

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glEnable( GL_DEPTH_TEST );

        // draw vertex buffer.
        if ( m_enable_exact_depth_testing )
        {
            m_engine->set_depth_texture( m_depth_texture );
            m_engine->set_extra_texture( m_extra_texture );
        }
        m_engine->draw_vertex_buffer( modelview_matrix );

        // render to the screen.
        m_framebuffer.disable();
        glDrawBuffer( GL_BACK );

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

void StochasticMultipleTetrahedraRenderer::initialize_framebuffer_texture( void )
{
    m_framebuffer.create();
    m_framebuffer.bind();

    BaseClass::create_texture( m_color_texture, m_framebuffer, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, GL_COLOR_ATTACHMENT0_EXT );
    BaseClass::create_texture( m_depth_texture, m_framebuffer, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT, GL_DEPTH_ATTACHMENT_EXT );
    BaseClass::create_texture( m_extra_texture, m_framebuffer, GL_RGBA32F_ARB, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT1_EXT );

    m_framebuffer.disable();

    GLenum error = glGetError();
    if ( error != GL_NO_ERROR )
    {
        kvsMessageError( "framebuffer allocation failed: %s.", gluErrorString(error));
        return;
    }
}

} // end of namespace glew

} // end of namespace kvs
