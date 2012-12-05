/*****************************************************************************/
/**
 *  @file   PolygonRenderer.h
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
#ifndef KVS__GLEW__POLYGON_RENDERER_H_INCLUDE
#define KVS__GLEW__POLYGON_RENDERER_H_INCLUDE

#include <kvs/DebugNew>
#include <kvs/Module>
#include <kvs/PolygonObject>
#include <kvs/PolygonRenderer>
#include <kvs/Shader>
#include <kvs/glew/ProgramObject>
#include <kvs/glew/ShaderSource>


namespace kvs
{

namespace glew
{

#define KVS_GLEW_POLYGON_RENDERER__EMBEDDED_SHADER

class PolygonRenderer : public kvs::PolygonRenderer
{
    kvsModuleName( kvs::glew::PolygonRenderer );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::PolygonRenderer );

protected:

    kvs::Shader::shader_type* m_shader; ///< shading method
    kvs::glew::ProgramObject m_phong_shader; ///< phong shader

public:

    PolygonRenderer( void );

    virtual ~PolygonRenderer( void );

public:

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

    template <typename ShadingType>
    void setShader( const ShadingType shader );

private:

    void initialize_shaders( void );
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

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__POLYGON_RENDERER_H_INCLUDE
