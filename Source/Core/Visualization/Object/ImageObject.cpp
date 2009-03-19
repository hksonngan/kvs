/****************************************************************************/
/**
 *  @file ImageObject.cpp
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#include "ImageObject.h"


namespace
{

const std::string GetPixelTypeName( const kvs::ImageObject::PixelType type )
{
    switch( type )
    {
    case kvs::ImageObject::Gray8: return("8 bit gray pixel");
    case kvs::ImageObject::Gray16: return("16 bit gray pixel");
    case kvs::ImageObject::Color24: return("24 bit RGB color pixel (8x8x8 bits)");
    case kvs::ImageObject::Color32: return("32 bit RGBA color pixel (8x8x8x8 bits)");
    default: return("unknown pixel type");
    }
}

} // end of namespace


namespace kvs
{

/*==========================================================================*/
/**
 *  Construct a new ImageObject class.
 */
/*==========================================================================*/
ImageObject::ImageObject( void )
{
}

/*==========================================================================*/
/**
 *  Construct a new ImageObject class.
 *  @param width [in] image width
 *  @param height [in] image height
 *  @param data [in] pixel data array
 *  @param type [in] color type
 */
/*==========================================================================*/
ImageObject::ImageObject(
    const size_t                       width,
    const size_t                       height,
    const kvs::ValueArray<kvs::UInt8>& data,
    const ImageObject::PixelType       type ):
    m_type( type ),
    m_width( width ),
    m_height( height )
{
    m_data = data; // shallow copy
}

/*==========================================================================*/
/**
 *  Destruct a ImageObject class.
 */
/*==========================================================================*/
ImageObject::~ImageObject( void )
{
    m_data.deallocate();
}

/*==========================================================================*/
/**
 *  Substitution operator.
 *  @param image [in] image object
 */
/*==========================================================================*/
ImageObject& ImageObject::operator = ( const ImageObject& image )
{
    m_type   = image.m_type;
    m_width  = image.m_width;
    m_height = image.m_height;
    m_data   = image.m_data; // shallow copy

    return( *this );
}

std::ostream& operator << ( std::ostream& os, const ImageObject& object )
{
    os << "Object type:  " << "image object" << std::endl;
    os << "Width:  " << object.width() << std::endl;
    os << "Height:  " << object.height() << std::endl;
    os << "Bits per pixel:  " << object.bitsPerPixel() << std::endl;
    os << "Bytes per pixel:  " << object.bytesPerPixel() << std::endl;
    os << "Pixel type:  " << ::GetPixelTypeName( object.type() );

    return( os );
}

/*==========================================================================*/
/**
 *  Return a object type.
 *  @return object type
 */
/*==========================================================================*/
const kvs::ObjectBase::ObjectType ImageObject::objectType( void ) const
{
    return( kvs::ObjectBase::Image );
}

/*==========================================================================*/
/**
 *  Return a pixel type.
 *  @return pixel type
 */
/*==========================================================================*/
ImageObject::PixelType ImageObject::type( void ) const
{
    return( m_type );
}

/*==========================================================================*/
/**
 *  Return a image width.
 *  @return image width
 */
/*==========================================================================*/
size_t ImageObject::width( void ) const
{
    return( m_width );
}

/*==========================================================================*/
/**
 *  Return a image height.
 *  @return image height
 */
/*==========================================================================*/
size_t ImageObject::height( void ) const
{
    return( m_height );
}

/*==========================================================================*/
/**
 *  Return a pixel data array.
 *  @return pixel data array
 */
/*==========================================================================*/
const kvs::ValueArray<kvs::UInt8>& ImageObject::data( void ) const
{
    return( m_data );
}

/*==========================================================================*/
/**
 *  Return a number of bits per pixel.
 *  @return number of bits per pixel
 */
/*==========================================================================*/
size_t ImageObject::bitsPerPixel( void ) const
{
    return( m_type );
}

/*==========================================================================*/
/**
 *  Return a number of bytes per pixel.
 *  @return number of bytes per pixel
 */
/*==========================================================================*/
size_t ImageObject::bytesPerPixel( void ) const
{
    return( m_type >> 3 );
}

/*==========================================================================*/
/**
 *  Return a number of color channels.
 *  @return number of color channels
 */
/*==========================================================================*/
size_t ImageObject::nchannels( void ) const
{
    size_t ret = 0;
    switch ( m_type )
    {
    case ImageObject::Gray8:   ret = 1; break;
    case ImageObject::Gray16:  ret = 1; break;
    case ImageObject::Color24: ret = 3; break;
    case ImageObject::Color32: ret = 4; break;
    default: break;
    }

    return( ret );
}

/*==========================================================================*/
/**
 *  Return a number of pixels.
 *  @return number of pixels
 */
/*==========================================================================*/
size_t ImageObject::get_npixels( void ) const
{
    return( ( m_type >> 3 ) * m_width * m_height );
}

} // end of namespace kvs
