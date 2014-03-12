/*****************************************************************************/
/**
 *  @file   PolygonRendererGLSL.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: PolygonRenderer.h 1398 2012-12-05 09:33:35Z naohisa.sakamoto@gmail.com $
 */
/*****************************************************************************/
#ifndef KVS__GLSL__POLYGON_RENDERER_H_INCLUDE
#define KVS__GLSL__POLYGON_RENDERER_H_INCLUDE

#include <kvs/DebugNew>
#include <kvs/Module>
#include <kvs/PolygonObject>
#include <kvs/Shader>
#include <kvs/ProgramObject>
#include <kvs/ShaderSource>


namespace kvs
{

namespace glsl
{

class PolygonRenderer : public kvs::PolygonRenderer
{
    kvsModule( kvs::glsl::PolygonRenderer, Renderer );
    kvsModuleBaseClass( kvs::PolygonRenderer );

protected:

    kvs::Shader::ShadingModel* m_shader; ///< shading method
    kvs::ProgramObject m_phong_shader; ///< phong shader

public:

    PolygonRenderer();
    virtual ~PolygonRenderer();

public:

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

    template <typename ShadingType>
    void setShader( const ShadingType shader );

private:

    void initialize_shaders();
};

template <typename ShadingType>
inline void PolygonRenderer::setShader( const ShadingType shader )
{
    if ( m_shader )
    {
        delete m_shader;
        m_shader = NULL;
    }

    m_shader = new ShadingType( shader );
    if ( !m_shader )
    {
        kvsMessageError("Cannot create a specified shader.");
    }
};

} // end of namespace glsl

} // end of namespace kvs

#endif // KVS__GLSL__POLYGON_RENDERER_H_INCLUDE
