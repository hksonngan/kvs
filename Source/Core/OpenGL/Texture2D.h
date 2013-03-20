/****************************************************************************/
/**
 *  @file   Texture2D.h
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
#ifndef KVS__TEXTURE_2D_H_INCLUDE
#define KVS__TEXTURE_2D_H_INCLUDE

#include <kvs/Texture>


namespace kvs
{

/*==========================================================================*/
/**
 *  2D texture class.
 */
/*==========================================================================*/
class Texture2D : public kvs::Texture
{
public:

    typedef kvs::Texture BaseClass;

protected:

    bool m_is_downloaded; ///< if true, the texture is downloaded
    GLenum m_wrap_s; ///< wrap method for s-axis
    GLenum m_wrap_t; ///< wrap method for t-axis
    size_t m_width; ///< texture width
    size_t m_height; ///< texture height
    const void* m_pixels; ///< pointer to the texture data (not allocated)

public:

    Texture2D();
    virtual ~Texture2D();

    GLenum wrapS() const;
    GLenum wrapT() const;
    size_t width() const;
    size_t height() const;
    bool isDownloaded() const;

    void setWrapS( const GLenum wrap_s );
    void setWrapT( const GLenum wrap_t );

    void create( const size_t width, const size_t height );
    void download(
        const size_t width,
        const size_t height,
        const void*  pixels,
        const size_t xoffset = 0,
        const size_t yoffset = 0 );
    void release();

    static unsigned int UsedTextureMemorySize();

private:

    static unsigned int get_texture_memory_size_on_gpu( const GLenum proxy );
};

} // end of namespace kvs

#endif // KVS_CORE_TEXTURE_2D_H_INCLUDE
