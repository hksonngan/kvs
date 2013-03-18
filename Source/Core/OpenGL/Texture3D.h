/****************************************************************************/
/**
 *  @file   Texture3D.h
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
/****************************************************************************/
#ifndef KVS__TEXTURE_3D_H_INCLUDE
#define KVS__TEXTURE_3D_H_INCLUDE

#include <kvs/OpenGL>
#include <kvs/Texture>


namespace kvs
{

/*==========================================================================*/
/**
 *  3D texture class.
 */
/*==========================================================================*/
class Texture3D : public kvs::Texture
{
public:

    typedef kvs::Texture BaseClass;

protected:

    bool m_is_downloaded; ///< if true, the texture is downloaded
    GLenum m_wrap_s; ///< wrap method for s-axis
    GLenum m_wrap_t; ///< wrap method for t-axis
    GLenum m_wrap_r; ///< wrap method for r-axis
    size_t m_width; ///< texture width
    size_t m_height; ///< texture height
    size_t m_depth; ///< texture depth
    const void* m_pixels; ///< pointer to the texture data (not allocated)

public:

    Texture3D();
    Texture3D( const GLenum wrap_s, const GLenum wrap_t, const GLenum wrap_r );
    virtual ~Texture3D();

    GLenum wrapS() const;
    GLenum wrapT() const;
    GLenum wrapR() const;
    size_t width() const;
    size_t height() const;
    size_t depth() const;
    bool isDownloaded() const;

    void setWrapS( const GLenum wrap_s );
    void setWrapT( const GLenum wrap_t );
    void setWrapR( const GLenum wrap_r );

    void create( const size_t width, const size_t height, const size_t depth );
    void download(
        const size_t width,
        const size_t height,
        const size_t depth,
        const void*  pixels,
        const size_t xoffset = 0,
        const size_t yoffset = 0,
        const size_t zoffset = 0 );
    void bind();
    void unbind();
    void release();

    static unsigned int UsedTextureMemorySize();

private:

    static unsigned int get_texture_memory_size_on_gpu( const GLenum proxy );
};

} // end of namespace kvs

#endif // KVS__TEXTURE_3D_H_INCLUDE
