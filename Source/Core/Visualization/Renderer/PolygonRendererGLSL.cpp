/*****************************************************************************/
/**
 *  @file   PolygonRendererGLSL.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: PolygonRenderer.cpp 1414 2013-01-21 02:16:48Z naohisa.sakamoto@gmail.com $
 */
/*****************************************************************************/
#include "PolygonRenderer.h"
#include <kvs/ProgramObject>
#include <kvs/ShaderSource>
#include <kvs/VertexShader>
#include <kvs/FragmentShader>


namespace kvs
{

namespace glsl
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new PolygonRenderer class.
 */
/*===========================================================================*/
PolygonRenderer::PolygonRenderer():
    m_shader( NULL )
{
    this->setShader( kvs::Shader::Phong() );
}

/*===========================================================================*/
/**
 *  @brief  Destroys the PolygonRenderer class.
 */
/*===========================================================================*/
PolygonRenderer::~PolygonRenderer()
{
    if ( m_shader ) { delete m_shader; }
}

/*===========================================================================*/
/**
 *  @brief  Main rendering routine.
 *  @param  object [in] pointer to the object
 *  @param  camera [in] pointer to the camera
 *  @param  light [in] pointer to the light
 */
/*===========================================================================*/
void PolygonRenderer::exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light )
{
    // Following process is executed once.
    static bool flag = true;
    if ( flag ) { this->initialize_shaders(); flag = false; }

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
void PolygonRenderer::initialize_shaders()
{
    const std::string vert_code = "shader.vert";
    const std::string frag_code = "shader.frag";

    kvs::ShaderSource vert( vert_code );
    kvs::ShaderSource frag( frag_code );

    if ( BaseClass::isShading() )
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
        m_phong_shader.setUniformValuef( "shading.Ka", Ka );
        m_phong_shader.setUniformValuef( "shading.Kd", Kd );
        break;
    }
    case kvs::Shader::PhongShading:
    {
        const GLfloat Ka = ((kvs::Shader::Phong*)(m_shader))->Ka;
        const GLfloat Kd = ((kvs::Shader::Phong*)(m_shader))->Kd;
        const GLfloat Ks = ((kvs::Shader::Phong*)(m_shader))->Ks;
        const GLfloat S  = ((kvs::Shader::Phong*)(m_shader))->S;
        m_phong_shader.setUniformValuef( "shading.Ka", Ka );
        m_phong_shader.setUniformValuef( "shading.Kd", Kd );
        m_phong_shader.setUniformValuef( "shading.Ks", Ks );
        m_phong_shader.setUniformValuef( "shading.S",  S );
        break;
    }
    case kvs::Shader::BlinnPhongShading:
    {
        const GLfloat Ka = ((kvs::Shader::BlinnPhong*)(m_shader))->Ka;
        const GLfloat Kd = ((kvs::Shader::BlinnPhong*)(m_shader))->Kd;
        const GLfloat Ks = ((kvs::Shader::BlinnPhong*)(m_shader))->Ks;
        const GLfloat S  = ((kvs::Shader::BlinnPhong*)(m_shader))->S;
        m_phong_shader.setUniformValuef( "shading.Ka", Ka );
        m_phong_shader.setUniformValuef( "shading.Kd", Kd );
        m_phong_shader.setUniformValuef( "shading.Ks", Ks );
        m_phong_shader.setUniformValuef( "shading.S",  S );
        break;
    }
    default: /* NO SHADING */ break;
    }
    m_phong_shader.unbind();
}

} // end of namespace glsl

} // end of namespace kvs
