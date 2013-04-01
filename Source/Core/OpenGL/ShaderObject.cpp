/*****************************************************************************/
/**
 *  @file   ShaderObject.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: ShaderObject.cpp 631 2010-10-10 02:15:35Z naohisa.sakamoto $
 */
/*****************************************************************************/
#include "ShaderObject.h"
#include <kvs/DebugNew>
#include <kvs/Message>


namespace kvs
{

ShaderObject::ShaderObject()
{
}

ShaderObject::ShaderObject( const GLenum type ):
    m_id( 0 ),
    m_type( type )
{
}

ShaderObject::~ShaderObject()
{
    this->clear();
}

GLuint ShaderObject::id() const
{
    return m_id;
}

std::string ShaderObject::log()
{
    GLint length = 0;
    glGetShaderiv( m_id, GL_INFO_LOG_LENGTH, &length );
    if ( length == 0 ) return( "" );

    char* buffer = new char [ length ];
    if ( !buffer )
    {
        kvsMessageError("Cannot allocate memory for the log.");
        return( "" );
    }

    GLsizei buffer_size = 0;
    glGetShaderInfoLog( m_id, length, &buffer_size, buffer );

    std::string log( buffer );
    delete [] buffer;

    return log;
}

std::string ShaderObject::source()
{
    GLint length = 0;
    glGetShaderiv( m_id, GL_SHADER_SOURCE_LENGTH, &length );
    if ( length == 0 ) return( "" );

    char* buffer = new char [ length ];
    if ( !buffer )
    {
        kvsMessageError("Cannot allocate memory for the shader source.");
        return( "" );
    }

    GLsizei buffer_size = 0;
    glGetShaderSource( m_id, length, &buffer_size, buffer );

    std::string source( buffer );
    delete [] buffer;

    return( source );
}

void ShaderObject::setSource( const kvs::ShaderSource& source )
{
    const char* code = source.code().c_str();
    glShaderSource( m_id, 1, &code, 0 );
}

void ShaderObject::create()
{
    if( !glIsShader( m_id ) ) m_id = glCreateShader( m_type );
}

bool ShaderObject::create( const kvs::ShaderSource& source )
{
    this->create();

    return( this->compile( source ) );
}

void ShaderObject::clear()
{
    if ( glIsShader( m_id ) ) glDeleteShader( m_id );

    m_id = 0;
    m_type = 0;
}

bool ShaderObject::compile()
{
    glCompileShader( m_id );

    GLint error = 0;
    glGetShaderiv( m_id, GL_COMPILE_STATUS, &error );

    return error == GL_TRUE;
}

bool ShaderObject::compile( const kvs::ShaderSource& source )
{
    this->setSource( source );

    return this->compile();
}

} // end of namespace kvs
