/*****************************************************************************/
/**
 *  @file   ProgramObject.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: ProgramObject.h 1149 2012-06-02 13:27:56Z s.yamada0808@gmail.com $
 */
/*****************************************************************************/
#ifndef KVS__PROGRAM_OBJECT_H_INCLUDE
#define KVS__PROGRAM_OBJECT_H_INCLUDE

#include <kvs/ShaderObject>
#include <kvs/VertexShader>
#include <kvs/FragmentShader>
#include <kvs/Vector2>
#include <kvs/Vector3>
#include <kvs/Vector4>


namespace kvs
{

/*===========================================================================*/
/**
 *  Program object class.
 */
/*===========================================================================*/
class ProgramObject
{
private:

    GLuint m_id; ///< shader ID

public:

    ProgramObject();
    virtual ~ProgramObject();

    GLuint id() const;
    std::string log();

    void create();
    void create( const kvs::ShaderSource& vertex_source, const kvs::ShaderSource& fragment_source );
    void clear();
    void attach( const kvs::ShaderObject& shader );
    bool link( const kvs::VertexShader& vertex_shader, const kvs::FragmentShader& fragment_shader );
    bool link();
    void bind();
    void unbind();

    GLint uniformLocation( const GLchar* name );
    GLint attributeLocation( const GLchar* name );

    void setUniformValuei( const GLchar* name, const GLint v0 );
    void setUniformValuei( const GLchar* name, const GLint v0, const GLint v1 );
    void setUniformValuei( const GLchar* name, const GLint v0, const GLint v1, const GLint v2 );
    void setUniformValuei( const GLchar* name, const GLint v0, const GLint v1, const GLint v2, const GLint v3 );
    void setUniformValuei( const GLchar* name, const kvs::Vector2i& v );
    void setUniformValuei( const GLchar* name, const kvs::Vector3i& v );
    void setUniformValuei( const GLchar* name, const kvs::Vector4i& v );
    void setUniformValuef( const GLchar* name, const GLfloat v0 );
    void setUniformValuef( const GLchar* name, const GLfloat v0, const GLfloat v1 );
    void setUniformValuef( const GLchar* name, const GLfloat v0, const GLfloat v1, const GLfloat v2 );
    void setUniformValuef( const GLchar* name, const GLfloat v0, const GLfloat v1, const GLfloat v2, const GLfloat v3 );
    void setUniformValuef( const GLchar* name, const kvs::Vector2f& v );
    void setUniformValuef( const GLchar* name, const kvs::Vector3f& v );
    void setUniformValuef( const GLchar* name, const kvs::Vector4f& v );
};

} // end of namespace kvs

#endif // KVS__SHADER_PROGRAM_H_INCLUDE
