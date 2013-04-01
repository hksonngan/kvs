/*****************************************************************************/
/**
 *  @file   ShaderObject.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: ShaderObject.h 634 2010-10-13 07:04:05Z naohisa.sakamoto $
 */
/*****************************************************************************/
#ifndef KVS__SHADER_OBJECT_H_INCLUDE
#define KVS__SHADER_OBJECT_H_INCLUDE

#include <kvs/ShaderSource>
#include <kvs/GL>


namespace kvs
{

/*===========================================================================*/
/**
 *  Shader object class.
 */
/*===========================================================================*/
class ShaderObject
{
protected:

    GLuint m_id; ///< shader ID
    GLenum m_type; ///< shader type (GL_VERTEX_SHADER, GL_GEOMETRY_SHADER or GL_FRAGMENT_SHADER)

protected:

    ShaderObject();

public:

    ShaderObject( const GLenum type );
    virtual ~ShaderObject();

public:

    GLuint id() const;
    std::string log();
    std::string source();
    void setSource( const kvs::ShaderSource& source );

    void create();
    bool create( const kvs::ShaderSource& source );
    void clear();
    bool compile();
    bool compile( const kvs::ShaderSource& source );
};

} // end of namespace kvs

#endif // KVS__SHADER_OBJECT_H_INCLUDE
