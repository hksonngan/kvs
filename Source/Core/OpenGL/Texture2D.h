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

private:

    bool m_is_downloaded; ///< if true, the texture is downloaded

public:

    Texture2D();
    virtual ~Texture2D();

    bool isDownloaded() const;

    void create( const size_t width, const size_t height, const void* data = NULL );
    void release();
    void download( const size_t width, const size_t height, const void* data, const size_t xoffset = 0, const size_t yoffset = 0 );
};

} // end of namespace kvs

#endif // KVS_CORE_TEXTURE_2D_H_INCLUDE
