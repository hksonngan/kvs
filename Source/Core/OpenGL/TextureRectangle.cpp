/****************************************************************************/
/**
 *  @file   TextureRectangle.cpp
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
#include "TextureRectangle.h"
#include <kvs/Math>
#include <kvs/Assert>
#include <iostream>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
TextureRectangle::TextureRectangle():
    Texture( GL_TEXTURE_RECTANGLE, GL_TEXTURE_BINDING_RECTANGLE ),
    m_is_downloaded( false )
{
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
TextureRectangle::~TextureRectangle()
{
    this->release();
}

bool TextureRectangle::isDownloaded() const
{
    return m_is_downloaded;
}

/*==========================================================================*/
/**
 *  Create the texture.
 */
/*==========================================================================*/
void TextureRectangle::create( const size_t width, const size_t height, const void* data )
{
    KVS_ASSERT( width > 0 );
    KVS_ASSERT( width <= kvs::OpenGL::MaxTextureSize() );
    KVS_ASSERT( height > 0 );
    KVS_ASSERT( height <= kvs::OpenGL::MaxTextureSize() );

    BaseClass::generateTexture();
    BaseClass::bind();
    BaseClass::setParameter( GL_TEXTURE_MAG_FILTER, BaseClass::magFilter() );
    BaseClass::setParameter( GL_TEXTURE_MIN_FILTER, BaseClass::minFilter() );
    BaseClass::setParameter( GL_TEXTURE_WRAP_S, BaseClass::wrapS() );
    BaseClass::setParameter( GL_TEXTURE_WRAP_T, BaseClass::wrapT() );
    BaseClass::setSize( width, height );
    this->download( width, height, data );
}

/*==========================================================================*/
/**
 *  Release the texture.
 */
/*==========================================================================*/
void TextureRectangle::release()
{
    BaseClass::deleteTexture();
    m_is_downloaded = false;
}

/*==========================================================================*/
/**
 *  Download the texture data to the GPU.
 *  @param width [in] texture width
 *  @param height [in] texture height
 *  @param pixels [in] pointer to the pixel data
 *  @param xoffset [in] texel offset in the x direction within the pixel data
 *  @param yoffset [in] texel offset in the y direction within the pixel data
 */
/*==========================================================================*/
void TextureRectangle::download(
    const size_t width,
    const size_t height,
    const void*  data,
    const size_t xoffset,
    const size_t yoffset )
{
    const GLint swap = kvs::OpenGL::Integer( GL_UNPACK_SWAP_BYTES );
    const GLint alignment = kvs::OpenGL::Integer( GL_UNPACK_ALIGNMENT );
    BaseClass::setPixelStorageMode( GL_UNPACK_SWAP_BYTES, swap ? GL_TRUE : GL_FALSE );
    BaseClass::setPixelStorageMode( GL_UNPACK_ALIGNMENT, 1 );

    if ( !m_is_downloaded )
    {
        BaseClass::setImageRectangle( width, height, data );
        m_is_downloaded = true;
    }
    else
    {
        BaseClass::setSubImageRectangle( width, height, data, xoffset, yoffset );
    }

    BaseClass::setPixelStorageMode( GL_UNPACK_SWAP_BYTES, swap );
    BaseClass::setPixelStorageMode( GL_UNPACK_ALIGNMENT, alignment );
}

} // end of namespace kvs
