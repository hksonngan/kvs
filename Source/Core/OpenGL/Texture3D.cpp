/****************************************************************************/
/**
 *  @file   Texture3D.cpp
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
#include "Texture3D.h"
#include <kvs/Math>
#include <kvs/OpenGL>
#include <kvs/Assert>
#include <iostream>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
Texture3D::Texture3D():
    Texture( GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D ),
    m_is_downloaded( false )
{
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
Texture3D::~Texture3D()
{
    this->release();
}

bool Texture3D::isDownloaded() const
{
    return m_is_downloaded;
}

/*==========================================================================*/
/**
 *  Create the texture.
 */
/*==========================================================================*/
void Texture3D::create( const size_t width, const size_t height, const size_t depth, const void* data )
{
    KVS_ASSERT( width > 0 );
    KVS_ASSERT( static_cast<GLint>( width ) <= kvs::OpenGL::MaxTextureSize() );
    KVS_ASSERT( height > 0 );
    KVS_ASSERT( static_cast<GLint>( height ) <= kvs::OpenGL::MaxTextureSize() );
    KVS_ASSERT( depth > 0 );
    KVS_ASSERT( static_cast<GLint>( depth ) <= kvs::OpenGL::MaxTextureSize() );

    BaseClass::generateTexture();
    BaseClass::bind();
    BaseClass::setParameter( GL_TEXTURE_MAG_FILTER, BaseClass::magFilter() );
    BaseClass::setParameter( GL_TEXTURE_MIN_FILTER, BaseClass::minFilter() );
    BaseClass::setParameter( GL_TEXTURE_WRAP_S, BaseClass::wrapS() );
    BaseClass::setParameter( GL_TEXTURE_WRAP_T, BaseClass::wrapT() );
    BaseClass::setParameter( GL_TEXTURE_WRAP_R, BaseClass::wrapR() );
    BaseClass::setSize( width, height, depth );
    this->download( width, height, depth, data );
}

/*==========================================================================*/
/**
 *  Release the texture.
 */
/*==========================================================================*/
void Texture3D::release()
{
    BaseClass::deleteTexture();
    m_is_downloaded = false;
}

/*==========================================================================*/
/**
 *  Download the texture data to the GPU.
 *  @param width  [in] texture width
 *  @param height [in] texture height
 *  @param depth  [in] texture depth
 *  @param data [in] pointer to the pixel data
 *  @param xoffset [in] texel offset in the x direction within the pixel data
 *  @param yoffset [in] texel offset in the y direction within the pixel data
 *  @param zoffset [in] texel offset in the z direction within the pixel data
 */
/*==========================================================================*/
void Texture3D::download(
    const size_t width,
    const size_t height,
    const size_t depth,
    const void*  data,
    const size_t xoffset,
    const size_t yoffset,
    const size_t zoffset )
{
    const GLint swap = kvs::OpenGL::Integer( GL_UNPACK_SWAP_BYTES );
    const GLint alignment = kvs::OpenGL::Integer( GL_UNPACK_ALIGNMENT );
    BaseClass::setPixelStorageMode( GL_UNPACK_SWAP_BYTES, swap ? GL_TRUE : GL_FALSE );
    BaseClass::setPixelStorageMode( GL_UNPACK_ALIGNMENT, 1 );

    if ( !m_is_downloaded )
    {
        BaseClass::setImage3D( width, height, depth, data );
        m_is_downloaded = true;
    }
    else
    {
        BaseClass::setSubImage3D( width, height, depth, data, xoffset, yoffset, zoffset );
    }

    BaseClass::setPixelStorageMode( GL_UNPACK_SWAP_BYTES, swap );
    BaseClass::setPixelStorageMode( GL_UNPACK_ALIGNMENT, alignment );
}

} // end of namespace kvs
