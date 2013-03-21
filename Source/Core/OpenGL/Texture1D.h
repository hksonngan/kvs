/****************************************************************************/
/**
 *  @file Texture1D.h
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
#ifndef KVS__TEXTURE_1D_H_INCLUDE
#define KVS__TEXTURE_1D_H_INCLUDE

#include <kvs/Texture>


namespace kvs
{

/*==========================================================================*/
/**
 *  1D texture class.
 */
/*==========================================================================*/
class Texture1D : public kvs::Texture
{
public:

    typedef kvs::Texture BaseClass;

protected:

    bool m_is_downloaded; ///< if true, the texture is downloaded
    const void* m_pixels; ///< pointer to the texture data (not allocated)

public:

    Texture1D();
    virtual ~Texture1D();

    bool isDownloaded() const;

    void create( const size_t width );
    void release();
    void download( const size_t width, const void* pixels, const size_t xoffset = 0 );

    static unsigned int UsedTextureMemorySize();

private:

    static unsigned int get_texture_memory_size_on_gpu( const GLenum proxy );
};

} // end of namespace kvs

#endif // KVS__TEXTURE_1D_H_INCLUDE
