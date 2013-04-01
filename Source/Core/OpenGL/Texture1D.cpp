/****************************************************************************/
/**
 *  @file   Texture1D.cpp
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
#include "Texture1D.h"
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
Texture1D::Texture1D():
    Texture( GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D ),
    m_is_downloaded( false )
{
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
Texture1D::~Texture1D()
{
    this->release();
}

bool Texture1D::isDownloaded() const
{
    return m_is_downloaded;
}

/*==========================================================================*/
/**
 *  Create the texture.
 */
/*==========================================================================*/
void Texture1D::create( const size_t width )
{
    KVS_ASSERT( width > 0 );
    KVS_ASSERT( width <= kvs::OpenGL::MaxTextureSize() );

    BaseClass::generateTexture();
    BaseClass::bind();
    BaseClass::setParameter( GL_TEXTURE_MAG_FILTER, BaseClass::magFilter() );
    BaseClass::setParameter( GL_TEXTURE_MIN_FILTER, BaseClass::minFilter() );
    BaseClass::setParameter( GL_TEXTURE_WRAP_S, BaseClass::wrapS() );
    this->download( width, NULL );
}

/*==========================================================================*/
/**
 *  Release the texture.
 */
/*==========================================================================*/
void Texture1D::release()
{
    BaseClass::deleteTexture();
    m_is_downloaded = false;
}

/*==========================================================================*/
/**
 *  Download the texture data to the GPU.
 *  @param width [in] texture width
 *  @param pixels [in] pointer to the pixel data
 *  @param xoffset [in] texel offset in the x direction within the pixel data
 */
/*==========================================================================*/
void Texture1D::download(
    const size_t width,
    const void* pixels,
    const size_t xoffset )
{
    BaseClass::setSize( width );

    const GLint swap = kvs::OpenGL::Integer( GL_UNPACK_SWAP_BYTES );
    const GLint alignment = kvs::OpenGL::Integer( GL_UNPACK_ALIGNMENT );
    BaseClass::setPixelStorageMode( GL_UNPACK_SWAP_BYTES, swap ? GL_TRUE : GL_FALSE );
    BaseClass::setPixelStorageMode( GL_UNPACK_ALIGNMENT, 1 );

    if ( !m_is_downloaded )
    {
        BaseClass::setImage1D( width, pixels );
        m_is_downloaded = true;
    }
    else
    {
        BaseClass::setSubImage1D( width, pixels, xoffset );
    }

    BaseClass::setPixelStorageMode( GL_UNPACK_SWAP_BYTES, swap );
    BaseClass::setPixelStorageMode( GL_UNPACK_ALIGNMENT, alignment );
}

} // end of namespace kvs
