/*****************************************************************************/
/**
 *  @file   PointRendererGLSL.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: PointRenderer.cpp 1414 2013-01-21 02:16:48Z naohisa.sakamoto@gmail.com $
 */
/*****************************************************************************/
#include "PointRenderer.h"
#include <kvs/DebugNew>
#include <kvs/ProgramObject>
#include <kvs/ShaderSource>
#include <kvs/VertexShader>
#include <kvs/FragmentShader>


namespace kvs
{

namespace glsl
{

PointRenderer::PointRenderer():
    m_shader( NULL )
{
    this->setShader( kvs::Shader::Phong() );
}

PointRenderer::~PointRenderer()
{
    if ( m_shader ) { delete m_shader; }
}

void PointRenderer::exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light )
{
    // Following process is executed once.
    static bool flag = true;
    if ( flag )
    {
        flag = false;
        this->initialize_shaders();
    }

    BaseClass::startTimer();
    m_phong_shader.bind();
    BaseClass::exec( object, camera, light );
    m_phong_shader.unbind();
    BaseClass::stopTimer();
}

/*==========================================================================*/
/**
 *  @brief  Initialize OpenGL.
 */
/*==========================================================================*/
void PointRenderer::initialize_shaders( void )
{
    const std::string vert_code = "shader.vert";
    const std::string frag_code = "shader.frag";

    kvs::ShaderSource vert( vert_code );
    kvs::ShaderSource frag( frag_code );

    if ( BaseClass::isEnabledShading() )
    {
        switch ( m_shader->type() )
        {
        case kvs::Shader::LambertShading: frag.define("ENABLE_LAMBERT_SHADING"); break;
        case kvs::Shader::PhongShading: frag.define("ENABLE_PHONG_SHADING"); break;
        case kvs::Shader::BlinnPhongShading: frag.define("ENABLE_BLINN_PHONG_SHADING"); break;
        default: /* NO SHADING */ break;
        }
    }

    m_phong_shader.create( vert, frag );

    m_phong_shader.bind();
    switch ( m_shader->type() )
    {
    case kvs::Shader::LambertShading:
    {
        const GLfloat Ka = ((kvs::Shader::Lambert*)(m_shader))->Ka;
        const GLfloat Kd = ((kvs::Shader::Lambert*)(m_shader))->Kd;
        m_phong_shader.setUniform( "shading.Ka", Ka );
        m_phong_shader.setUniform( "shading.Kd", Kd );
        break;
    }
    case kvs::Shader::PhongShading:
    {
        const GLfloat Ka = ((kvs::Shader::Phong*)(m_shader))->Ka;
        const GLfloat Kd = ((kvs::Shader::Phong*)(m_shader))->Kd;
        const GLfloat Ks = ((kvs::Shader::Phong*)(m_shader))->Ks;
        const GLfloat S  = ((kvs::Shader::Phong*)(m_shader))->S;
        m_phong_shader.setUniform( "shading.Ka", Ka );
        m_phong_shader.setUniform( "shading.Kd", Kd );
        m_phong_shader.setUniform( "shading.Ks", Ks );
        m_phong_shader.setUniform( "shading.S",  S );
        break;
    }
    case kvs::Shader::BlinnPhongShading:
    {
        const GLfloat Ka = ((kvs::Shader::BlinnPhong*)(m_shader))->Ka;
        const GLfloat Kd = ((kvs::Shader::BlinnPhong*)(m_shader))->Kd;
        const GLfloat Ks = ((kvs::Shader::BlinnPhong*)(m_shader))->Ks;
        const GLfloat S  = ((kvs::Shader::BlinnPhong*)(m_shader))->S;
        m_phong_shader.setUniform( "shading.Ka", Ka );
        m_phong_shader.setUniform( "shading.Kd", Kd );
        m_phong_shader.setUniform( "shading.Ks", Ks );
        m_phong_shader.setUniform( "shading.S",  S );
        break;
    }
    default: /* NO SHADING */ break;
    }
    m_phong_shader.unbind();
}

/*
PointRenderer::PointRenderer( void ):
    m_vertex_buffer( NULL ),
    m_normal_buffer( NULL ),
    m_color_buffer( NULL ),
    m_ref_point( NULL )
{
}

PointRenderer::~PointRenderer( void )
{
    if ( m_vertex_buffer ) delete m_vertex_buffer;
    if ( m_normal_buffer ) delete m_normal_buffer;
    if ( m_color_buffer ) delete m_color_buffer;
}

void PointRenderer::exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light )
{
    kvs::IgnoreUnusedVariable( light );
    kvs::IgnoreUnusedVariable( camera );

    kvs::PointObject* point = kvs::PointObject::DownCast( object );

    glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT );

    if ( point->normals().size() == 0 ) { BaseClass::disableShading(); }

    BaseClass::BaseClass::initialize();
    point->applyMaterial();

    // Anti-aliasing.
    if ( m_enable_anti_aliasing )
    {
#if defined ( GL_MULTISAMPLE )
        if ( m_enable_multisample_anti_aliasing )
        {
            GLint buffers = 0;
            GLint samples = 0;
            glGetIntegerv( GL_SAMPLE_BUFFERS, &buffers );
            glGetIntegerv( GL_SAMPLES, &samples );
            if ( buffers > 0 && samples > 1 ) glEnable( GL_MULTISAMPLE );
        }
        else
#endif
        {
            glEnable( GL_POINT_SMOOTH );
            glEnable( GL_BLEND );
            glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
            glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );
        }
    }

    if ( !m_ref_point || m_ref_point != point )
    {
        this->create_vertexbuffer( point );
        this->download_vertexbuffer( point );
    }

    glEnable( GL_DEPTH_TEST );
    {
        BaseClass::timer().start();
        this->draw_vertexbuffer( point );
        BaseClass::timer().stop();
    }
    glDisable( GL_DEPTH_TEST );

    glPopAttrib();
}

void PointRenderer::create_vertexbuffer( const kvs::PointObject* point )
{
    const size_t nnormals = point->normals().size() / 3;
    const size_t ncolors = point->colors().size() / 3;

    const size_t vertex_size = point->coords().byteSize();
    const size_t normal_size = point->normals().byteSize();
    const size_t color_size = point->colors().byteSize();

    // Vertex.
    if ( m_vertex_buffer ) delete m_vertex_buffer;
    m_vertex_buffer = new kvs::glew::VertexBufferObject;
    m_vertex_buffer->setUsage( kvs::glew::VertexBufferObject::StaticDraw );
    m_vertex_buffer->create( vertex_size );

    // Normal.
    if ( m_normal_buffer ) delete m_normal_buffer;
    m_normal_buffer = new kvs::glew::VertexBufferObject;
    m_normal_buffer->setUsage( kvs::glew::VertexBufferObject::StaticDraw );
    if ( nnormals > 0 ) m_normal_buffer->create( normal_size );

    // Color.
    if ( m_color_buffer ) delete m_color_buffer;
    m_color_buffer = new kvs::glew::VertexBufferObject;
    m_color_buffer->setUsage( kvs::glew::VertexBufferObject::StaticDraw );
    if ( ncolors > 1 ) m_color_buffer->create( color_size );

    const GLenum error = glGetError();
    if ( error != GL_NO_ERROR )
    {
        kvsMessageError( "Vertex Buffer Object create failed: %s (code: %d).", gluErrorString( error ), error );
    }
}

void PointRenderer::download_vertexbuffer( const kvs::PointObject* point )
{
    const size_t nnormals = point->normals().size() / 3;
    const size_t ncolors = point->colors().size() / 3;

    const size_t vertex_size = point->coords().byteSize();
    const size_t normal_size = point->normals().byteSize();
    const size_t color_size = point->colors().byteSize();

    // Vertex.
    m_vertex_buffer->bind();
    m_vertex_buffer->download( vertex_size, point->coords().pointer(), 0 );
    glVertexPointer( 3, GL_FLOAT, 0, 0 );

    // Normal.
    if ( nnormals > 0 )
    {
        m_normal_buffer->bind();
        m_normal_buffer->download( normal_size, point->normals().pointer(), 0 );
        glNormalPointer( GL_FLOAT, 0, 0 );
    }

    // Color.
    if ( ncolors > 0 )
    {
        m_color_buffer->bind();
        m_color_buffer->download( color_size, point->colors().pointer(), 0 );
        glColorPointer( 3, GL_UNSIGNED_BYTE, 0, 0 );
    }

    const GLenum error = glGetError();
    if ( error != GL_NO_ERROR )
    {
        kvsMessageError( "Vertex Buffer Object download failed: %s(%d).", gluErrorString( error ), error );
    }
    else
    {
        m_ref_point = point;
    }
}

void PointRenderer::draw_vertexbuffer( const kvs::PointObject* point )
{
    const size_t nvertices = point->coords().size() / 3;
    const size_t nnormals = point->normals().size() / 3;
    const size_t ncolors = point->colors().size() / 3;

    // Vertex.
    m_vertex_buffer->bind();
    glEnableClientState( GL_VERTEX_ARRAY );

    // Normal.
    if ( nnormals > 0 )
    {
        m_normal_buffer->bind();
        glEnableClientState( GL_NORMAL_ARRAY );
    }

    // Color.
    if ( ncolors > 1 )
    {
        m_color_buffer->bind();
        glEnableClientState( GL_COLOR_ARRAY );
    }
    else if ( ncolors == 1 )
    {
        const kvs::UInt8* c = point->colors().pointer();
        glColor3ub( c[0], c[1], c[2] );
    }

    // Size.
    {
        const kvs::Real32 s = point->sizes().at(0);
        glPointSize( s );
    }

    glDrawArrays( GL_POINTS, 0, nvertices );

    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );
}
*/

} // end of namespace glsl

} // end of namespace kvs
