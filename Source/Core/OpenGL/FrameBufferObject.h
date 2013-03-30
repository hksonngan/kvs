/****************************************************************************/
/**
 *  @file   FrameBufferObject.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: FrameBufferObject.h 634 2010-10-13 07:04:05Z naohisa.sakamoto $
 */
/****************************************************************************/
#ifndef KVS__FRAME_BUFFER_OBJECT_H_INCLUDE
#define KVS__FRAME_BUFFER_OBJECT_H_INCLUDE

#include <kvs/Texture1D>
#include <kvs/Texture2D>
#include <kvs/Texture3D>
#include <kvs/RenderBuffer>
#include <kvs/Deprecated>


namespace kvs
{

/*===========================================================================*/
/**
 *  Frame buffer object class.
 */
/*===========================================================================*/
class FrameBufferObject
{
private:

    GLuint m_id; ///< object ID

public:

    FrameBufferObject();
    virtual ~FrameBufferObject();

    GLuint id() const;

    void create();
    void release();
    void bind() const;
    void unbind() const;
    bool isValid() const;
    bool isBinding() const;

    void attachColorTexture( const kvs::Texture1D& texture, const size_t color_buffer = 0, const int mip_level = 0 );
    void attachColorTexture( const kvs::Texture2D& texture, const size_t color_buffer = 0, const int mip_level = 0 );
    void attachColorTexture( const kvs::Texture3D& texture, const size_t color_buffer = 0, const int mip_level = 0, const int zoffset = 0 );
    void attachDepthTexture( const kvs::Texture1D& texture, const int mip_level = 0 );
    void attachDepthTexture( const kvs::Texture2D& texture, const int mip_level = 0 );
    void attachDepthTexture( const kvs::Texture3D& texture, const int mip_level = 0, const int zoffset = 0 );
    void attachColorRenderBuffer( const kvs::RenderBuffer& render_buffer, const size_t color_buffer = 0 );
    void attachDepthRenderBuffer( const kvs::RenderBuffer& render_buffer );

public:

    KVS_DEPRECATED( void disable() const ) { this->unbind(); }
};

} // end of namespace kvs

#endif // KVS__FRAME_BUFFER_OBJECT_H_INCLUDE
