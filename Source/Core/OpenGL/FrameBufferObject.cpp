/*****************************************************************************/
/**
 *  @file   FrameBufferObject.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: FrameBufferObject.cpp 602 2010-08-19 02:43:34Z naohisa.sakamoto $
 */
/*****************************************************************************/
#include "FrameBufferObject.h"
#include <kvs/Texture2D>
#include <kvs/Assert>
#include <kvs/OpenGL>


namespace
{

class GuardedBinder
{
private:

    const kvs::FrameBufferObject& m_fbo;
    GLint m_id;

public:

    GuardedBinder( const kvs::FrameBufferObject& fbo ):
        m_fbo( fbo ),
        m_id( 0 )
    {
        KVS_ASSERT( fbo.isValid() );
        m_id = kvs::OpenGL::Integer( GL_FRAMEBUFFER_BINDING );
        if ( fbo.id() != static_cast<GLuint>( m_id ) ) { fbo.bind(); }
    }

    ~GuardedBinder()
    {
        KVS_ASSERT( m_fbo.isValid() );
        if ( static_cast<GLuint>( m_id ) != m_fbo.id() )
        {
            KVS_GL_CALL( glBindFramebufferEXT( GL_FRAMEBUFFER, m_id ) );
        }
    }

private:

    GuardedBinder( const GuardedBinder& );
    GuardedBinder& operator =( const GuardedBinder& );
};

}

namespace kvs
{

/*===========================================================================*/
/**
 *  Construct a new FrameBufferObject class.
 */
/*===========================================================================*/
FrameBufferObject::FrameBufferObject():
    m_id( 0 )
{
}

/*===========================================================================*/
/**
 *  Destroy the FrameBufferObject class.
 */
/*===========================================================================*/
FrameBufferObject::~FrameBufferObject()
{
    this->release();
}

/*===========================================================================*/
/**
 *  Return object ID.
 *  @return object ID
 */
/*===========================================================================*/
GLuint FrameBufferObject::id() const
{
    return m_id;
}

/*===========================================================================*/
/**
 *  Create frame buffer object.
 */
/*===========================================================================*/
void FrameBufferObject::create()
{
    KVS_ASSERT( m_id == 0 );
    KVS_GL_CALL( glGenFramebuffers( 1, &m_id ) );
}

/*===========================================================================*/
/**
 *  Release frame buffer object.
 */
/*===========================================================================*/
void FrameBufferObject::release()
{
    KVS_ASSERT( this->isValid() );
    KVS_GL_CALL( glDeleteFramebuffers( 1, &m_id ) );
    m_id = 0;
}

/*===========================================================================*/
/**
 *  Bind frame buffer object.
 */
/*===========================================================================*/
void FrameBufferObject::bind() const
{
    KVS_ASSERT( this->isValid() );
    KVS_GL_CALL( glBindFramebuffer( GL_FRAMEBUFFER, m_id ) );
}

/*===========================================================================*/
/**
 *  Disable frame buffer object.
 */
/*===========================================================================*/
void FrameBufferObject::unbind() const
{
    KVS_ASSERT( this->isBinding() );
    KVS_GL_CALL( glBindFramebuffer( GL_FRAMEBUFFER, 0 ) );
}

bool FrameBufferObject::isValid() const
{
    GLboolean result;
    KVS_GL_CALL( result = glIsFramebuffer( m_id ) );
    return result == GL_TRUE;
}

bool FrameBufferObject::isBinding() const
{
    KVS_ASSERT( this->isValid() );
    GLint id = kvs::OpenGL::Integer( GL_FRAMEBUFFER_BINDING );
    return static_cast<GLuint>( id ) == m_id;
}

void FrameBufferObject::attachColorTexture( const kvs::Texture1D& texture, const size_t color_buffer, const int mip_level )
{
    KVS_ASSERT( static_cast<GLint>( color_buffer ) < kvs::OpenGL::MaxColorAttachments() );
    ::GuardedBinder binder( *this );
    const GLuint id = texture.id();
    const GLenum attachment = GL_COLOR_ATTACHMENT0 + color_buffer;
    const GLenum type = GL_TEXTURE_1D;
    KVS_GL_CALL( glFramebufferTexture1D( GL_FRAMEBUFFER, attachment, type, id, mip_level ) );
}

/*===========================================================================*/
/**
 *  Attach color texture.
 *  @param  texture [in] 2D texture
 *  @param  color_buffer [in] color buffer
 *  @param  mip_level [in] mip level
 */
/*===========================================================================*/
void FrameBufferObject::attachColorTexture( const kvs::Texture2D& texture, const size_t color_buffer, const int mip_level )
{
    KVS_ASSERT( static_cast<GLint>( color_buffer ) < kvs::OpenGL::MaxColorAttachments() );
    ::GuardedBinder binder( *this );
    const GLuint id = texture.id();
    const GLenum attachment = GL_COLOR_ATTACHMENT0 + color_buffer;
    const GLenum type = GL_TEXTURE_2D;
    KVS_GL_CALL( glFramebufferTexture2D( GL_FRAMEBUFFER, attachment, type, id, mip_level ) );
}

/*===========================================================================*/
/**
 *  Attach color texture.
 *  @param  texture [in] 3D texture
 *  @param  color_buffer [in] color buffer
 *  @param  mip_level [in] mip level
 *  @param  zoffset [in] offset
 */
/*===========================================================================*/
void FrameBufferObject::attachColorTexture( const kvs::Texture3D& texture, const size_t color_buffer, const int mip_level, const int zoffset )
{
    KVS_ASSERT( static_cast<GLint>( color_buffer ) < kvs::OpenGL::MaxColorAttachments() );
    ::GuardedBinder binder( *this );
    const GLuint id = texture.id();
    const GLenum attachment = GL_COLOR_ATTACHMENT0 + color_buffer;
    const GLenum type = GL_TEXTURE_3D;
    KVS_GL_CALL( glFramebufferTexture3D( GL_FRAMEBUFFER, attachment, type, id, mip_level, zoffset ) );
}

void FrameBufferObject::attachDepthTexture( const kvs::Texture1D& texture, const int mip_level )
{
    ::GuardedBinder binder( *this );
    const GLuint id = texture.id();
    const GLenum attachment = GL_DEPTH_ATTACHMENT;
    const GLenum type = GL_TEXTURE_1D;
    KVS_GL_CALL( glFramebufferTexture1D( GL_FRAMEBUFFER, attachment, type, id, mip_level ) );
}

void FrameBufferObject::attachDepthTexture( const kvs::Texture2D& texture, const int mip_level )
{
    ::GuardedBinder binder( *this );
    const GLuint id = texture.id();
    const GLenum attachment = GL_DEPTH_ATTACHMENT;
    const GLenum type = GL_TEXTURE_2D;
    KVS_GL_CALL( glFramebufferTexture2D( GL_FRAMEBUFFER, attachment, type, id, mip_level ) );
}

void FrameBufferObject::attachDepthTexture( const kvs::Texture3D& texture, const int mip_level, const int zoffset )
{
    ::GuardedBinder binder( *this );
    const GLuint id = texture.id();
    const GLenum attachment = GL_DEPTH_ATTACHMENT;
    const GLenum type = GL_TEXTURE_3D;
    KVS_GL_CALL( glFramebufferTexture3D( GL_FRAMEBUFFER, attachment, type, id, mip_level, zoffset ) );
}

void FrameBufferObject::attachColorRenderBuffer( const kvs::RenderBuffer& render_buffer, const size_t color_buffer )
{
    KVS_ASSERT( static_cast<GLint>( color_buffer ) < kvs::OpenGL::MaxColorAttachments() );
    ::GuardedBinder binder( *this );
    const GLuint id = render_buffer.id();
    const GLenum attachment = GL_COLOR_ATTACHMENT0 + color_buffer;
    KVS_GL_CALL( glFramebufferRenderbuffer( GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, id ) );
}

void FrameBufferObject::attachDepthRenderBuffer( const kvs::RenderBuffer& render_buffer )
{
    ::GuardedBinder binder( *this );
    const GLuint id = render_buffer.id();
    const GLenum attachment = GL_DEPTH_ATTACHMENT;
    KVS_GL_CALL( glFramebufferRenderbufferEXT( GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, id ) );
}

} // end of namespace kvs
