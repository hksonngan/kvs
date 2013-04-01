/*****************************************************************************/
/**
 *  @file   BufferObject.cpp
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: BufferObject.cpp 602 2010-08-19 02:43:34Z naohisa.sakamoto $
 */
/*****************************************************************************/
#include "BufferObject.h"
#include <kvs/Assert>
#include <kvs/OpenGL>


namespace kvs
{

/*===========================================================================*/
/**
 *  Constructs a new BufferObject class.
 *  @param  target [in] bind target
 *  @param  binding_target [in] binding target
 *  @param  usage [in] buffer usage
 */
/*===========================================================================*/
BufferObject::BufferObject( const GLenum target, const GLenum binding_target, const GLenum usage ):
    m_id( 0 ),
    m_target( target ),
    m_binding_target( binding_target ),
    m_usage( usage ),
    m_size( 0 ),
    m_is_downloaded( false )
{
}

/*===========================================================================*/
/**
 *  Destroys the BufferObject class.
 */
/*===========================================================================*/
BufferObject::~BufferObject()
{
    this->release();
}

/*===========================================================================*/
/**
 *  Returns the buffer ID.
 *  @return buffer ID
 */
/*===========================================================================*/
GLuint BufferObject::id() const
{
    return m_id;
}

/*===========================================================================*/
/**
 *  Returns the buffer size.
 *  @return buufer size
 */
/*===========================================================================*/
size_t BufferObject::size() const
{
    return m_size;
}

/*===========================================================================*/
/**
 *  Sets buffer usage.
 *  @param  usage [in] buffer usage
 */
/*===========================================================================*/
void BufferObject::setUsage( const GLenum usage )
{
    m_usage = usage;
}

void BufferObject::setSize( const size_t size )
{
    m_size = size;
}

/*===========================================================================*/
/**
 *  Create buffer.
 *  @param  size [in] buffer size
 */
/*===========================================================================*/
void BufferObject::create( const size_t size )
{
    this->generateBuffer();
    this->bind();
    this->download( size, NULL );
}

/*===========================================================================*/
/**
 *  Release buffer.
 */
/*===========================================================================*/
void BufferObject::release()
{
    this->deleteBuffer();
    m_is_downloaded = false;
}

/*===========================================================================*/
/**
 *  Bind buffer.
 */
/*===========================================================================*/
void BufferObject::bind() const
{
    KVS_ASSERT( this->isCreated() );
    KVS_GL_CALL( glBindBuffer( m_target, m_id ) );
}

/*===========================================================================*/
/**
 *  Unbind buffer.
 */
/*===========================================================================*/
void BufferObject::unbind() const
{
    KVS_ASSERT( this->isBinding() );
    KVS_GL_CALL( glBindBuffer( m_target, 0 ) );
}

bool BufferObject::isCreated() const
{
    return m_id > 0;
}

bool BufferObject::isValid() const
{
    GLboolean result;
    KVS_GL_CALL( result = glIsBuffer( m_id ) );
    return result == GL_TRUE;
}

bool BufferObject::isBinding() const
{
    if ( !this->isCreated() ) return false;

    GLint id = kvs::OpenGL::Integer( m_binding_target );
    return static_cast<GLuint>( id ) == m_id;
}

/*===========================================================================*/
/**
 *  Download buffer data from CPU to GPU.
 *  @param  size [in] buffer data size
 *  @param  buffer [in] pointer to downloaded buffer data
 *  @param  offset [in] texel offset within the existing buffer data array
 */
/*===========================================================================*/
void BufferObject::download( const size_t size, const void* buffer, const size_t offset )
{
    this->setSize( size );

    if ( !m_is_downloaded )
    {
        this->setBufferData( size, buffer );
        m_is_downloaded = true;
    }
    else
    {
        this->setBufferSubData( size, buffer, offset );
    }
}

/*===========================================================================*/
/**
 *  Map buffer data.
 *  @param  access_type [in] access policy
 *  @return NULL if an error is generated
 */
/*===========================================================================*/
void* BufferObject::map( const GLenum access_type )
{
    return this->mapBuffer( access_type );
}

/*===========================================================================*/
/**
 *  Unmap buffer object data.
 */
/*===========================================================================*/
void BufferObject::unmap()
{
    this->unmapBuffer();
}

void BufferObject::generateBuffer()
{
    if ( !this->isValid() )
    {
        KVS_GL_CALL( glGenBuffers( 1, &m_id ) );
    }
}

void BufferObject::deleteBuffer()
{
    if ( this->isValid() )
    {
        KVS_GL_CALL( glDeleteBuffers( 1, &m_id ) );
    }
    m_id = 0;
}

void BufferObject::setBufferData( GLsizei size, const GLvoid* data )
{
    KVS_ASSERT( this->isBinding() );
    KVS_GL_CALL( glBufferData( m_target, size, data, m_usage ) );
}

void BufferObject::setBufferSubData( GLsizei size, const GLvoid* data, GLint offset )
{
    KVS_ASSERT( this->isBinding() );
    KVS_GL_CALL( glBufferSubData( m_target, offset, size, data ) );
}

void* BufferObject::mapBuffer( const GLenum access_type )
{
    KVS_ASSERT( this->isBinding() );
    void* result = 0;
    KVS_GL_CALL( result = glMapBuffer( m_target, access_type ) );
    return result;
}

void BufferObject::unmapBuffer()
{
    KVS_ASSERT( this->isBinding() );
    KVS_GL_CALL( glUnmapBuffer( m_target ) );
}

} // end of namespace kvs
