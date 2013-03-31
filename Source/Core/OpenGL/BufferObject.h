/*****************************************************************************/
/**
 *  @file   BufferObject.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: BufferObject.h 634 2010-10-13 07:04:05Z naohisa.sakamoto $
 */
/*****************************************************************************/
#ifndef KVS__BUFFER_OBJECT_H_INCLUDE
#define KVS__BUFFER_OBJECT_H_INCLUDE

#include <kvs/GL>


namespace kvs
{

/*===========================================================================*/
/**
 *  Buffer object class.
 */
/*===========================================================================*/
class BufferObject
{
public:

    enum AccessType
    {
        ReadOnly  = GL_READ_ONLY_ARB,  ///< reading pixel data from PBO
        WriteOnly = GL_WRITE_ONLY_ARB, ///< writing pixel data to PBO
        ReadWrite = GL_READ_WRITE_ARB  ///< reading and writing
    };

    enum UsageType
    {
        StaticDraw  = GL_STATIC_DRAW_ARB,  ///< data will not be changed and sent to GPU
        StaticRead  = GL_STATIC_READ_ARB,  ///< data will not be changed and read by the application
        StaticCopy  = GL_STATIC_COPY_ARB,  ///< data will not be changed and used both drawing and reading
        DynamicDraw = GL_DYNAMIC_DRAW_ARB, ///< data will be changed frequently and sent to GPU
        DynamicRead = GL_DYNAMIC_READ_ARB, ///< data will be changed frequently and read by the application
        DynamicCopy = GL_DYNAMIC_COPY_ARB, ///< data will be changed frequently and used both drawing and reading
        StreamDraw  = GL_STREAM_DRAW_ARB,  ///< data will be changed every frame and sent to GPU
        StreamRead  = GL_STREAM_READ_ARB,  ///< data will be changed every frame and read by the application
        StreamCopy  = GL_STREAM_COPY_ARB   ///< data will be changed every frame and used both drawing and reading
    };

protected:

    GLuint m_id; ///< buffer ID
    GLenum m_target; ///< target (GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER)
    GLenum m_binding_target; ///< binding target
    GLenum m_usage; ///< usage
    size_t m_size; ///< buffer size [byte]
    bool m_is_downloaded; ///< test whether the memory is allocated on the GPU or not

public:

    BufferObject( const GLenum target, const GLenum binding_target, const GLenum usage );
    virtual ~BufferObject();

    GLuint id() const;
    size_t size() const;

    void setUsage( const GLenum usage );
    void setSize( const size_t size );

    void create( const size_t size );
    void release();
    void bind() const;
    void unbind() const;
    bool isValid() const;
    bool isBinding() const;

    void download( const size_t size, const void* buffer, const size_t offset = 0 );
    void* map( const GLenum access_type = kvs::BufferObject::ReadWrite );
    void unmap();

protected:

    void generateBufferObject();
    void deleteBufferObject();
    bool isBufferObject() const;
    void setBufferData( GLsizei width, const GLvoid* data );
    void setBufferSubData( GLsizei width, const GLvoid* data, GLint xoffset = 0 );
    void* mapBuffer( const GLenum access_type );
    void unmapBuffer();

private:

    BufferObject( const BufferObject& );
    BufferObject& operator =( const BufferObject& );
};

} // end of namespace kvs

#endif // KVS__BUFFER_OBJECT_H_INCLUDE
