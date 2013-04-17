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

private:

    bool m_is_downloaded; ///< if true, the texture is downloaded

public:

    static void Unbind();

public:

    Texture3D();
    virtual ~Texture3D();

    bool isDownloaded() const;

    void create( const size_t width, const size_t height, const size_t depth, const void* data = NULL );
    void release();
    void download(
        const size_t width,
        const size_t height,
        const size_t depth,
        const void* data,
        const size_t xoffset = 0,
        const size_t yoffset = 0,
        const size_t zoffset = 0 );
};

} // end of namespace kvs

#endif // KVS__TEXTURE_3D_H_INCLUDE
