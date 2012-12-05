/*****************************************************************************/
/**
 *  @file   ImageObject.cpp
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
/*****************************************************************************/
#include "ImageObject.h"
#include <string>


namespace
{

/*===========================================================================*/
/**
 *  @brief  Returns the pixel type name.
 *  @param  type [in] pixel type
 *  @return pixel type name
 */
/*===========================================================================*/
const std::string GetPixelTypeName( const kvs::ImageObject::PixelType type )
{
    switch( type )
    {
    case kvs::ImageObject::Gray8: return "8 bit gray pixel";
    case kvs::ImageObject::Gray16: return "16 bit gray pixel";
    case kvs::ImageObject::Color24: return "24 bit RGB color pixel (8x8x8 bits)";
    case kvs::ImageObject::Color32: return "32 bit RGBA color pixel (8x8x8x8 bits)";
    default: return "unknown pixel type";
    }
}

} // end of namespace


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new ImageObject class.
 */
/*===========================================================================*/
ImageObject::ImageObject()
{
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new ImageObject class.
 *  @param  width [in] image width
 *  @param  height [in] image height
 *  @param  data [in] pixel data array
 *  @param  type [in] color type
 */
/*==========================================================================*/
ImageObject::ImageObject(
    const size_t width,
    const size_t height,
    const kvs::ValueArray<kvs::UInt8>& data,
    const ImageObject::PixelType type ):
    m_type( type ),
    m_width( width ),
    m_height( height ),
    m_data( data )
{
}

/*===========================================================================*/
/**
 *  @brief  '<<' operator.
 */
/*===========================================================================*/
std::ostream& operator << ( std::ostream& os, const ImageObject& object )
{
    os << "Object type:  " << "image object" << std::endl;
    os << "Width:  " << object.width() << std::endl;
    os << "Height:  " << object.height() << std::endl;
    os << "Bits per pixel:  " << object.bitsPerPixel() << std::endl;
    os << "Bytes per pixel:  " << object.bytesPerPixel() << std::endl;
    os << "Pixel type:  " << ::GetPixelTypeName( object.type() );

    return os;
}

/*===========================================================================*/
/**
 *  @brief  Shallow copy.
 *  @param  other [in] image object
 */
/*===========================================================================*/
void ImageObject::shallowCopy( const ImageObject& other )
{
    BaseClass::operator=( other );
    this->m_type = other.type();
    this->m_width = other.width();
    this->m_height = other.height();
    this->m_data = other.data();
}

/*===========================================================================*/
/**
 *  @brief  Deep copy.
 *  @param  other [in] image object
 */
/*===========================================================================*/
void ImageObject::deepCopy( const ImageObject& other )
{
    BaseClass::operator=( other );
    this->m_type = other.type();
    this->m_width = other.width();
    this->m_height = other.height();
    this->m_data = other.data().clone();
}

/*===========================================================================*/
/**
 *  @brief  Prints information of the image object.
 *  @param  os [in] output stream
 *  @param  indent [in] indent
 */
/*===========================================================================*/
void ImageObject::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Object type : " << "image object" << std::endl;
    os << indent << "Width : " << this->width() << std::endl;
    os << indent << "Height : " << this->height() << std::endl;
    os << indent << "Bits per pixel : " << this->bitsPerPixel() << std::endl;
    os << indent << "Bytes per pixel : " << this->bytesPerPixel() << std::endl;
    os << indent << "Pixel type : " << ::GetPixelTypeName( this->type() ) << std::endl;
}

/*==========================================================================*/
/**
 *  @brief  Returns the object type.
 *  @return object type
 */
/*==========================================================================*/
kvs::ObjectBase::ObjectType ImageObject::objectType() const
{
    return kvs::ObjectBase::Image;
}

/*==========================================================================*/
/**
 *  @brief  Returns the pixel type.
 *  @return pixel type
 */
/*==========================================================================*/
ImageObject::PixelType ImageObject::type() const
{
    return m_type;
}

/*==========================================================================*/
/**
 *  @brief  Returns the image width.
 *  @return image width
 */
/*==========================================================================*/
size_t ImageObject::width() const
{
    return m_width;
}

/*==========================================================================*/
/**
 *  @brief  Returns the image height.
 *  @return image height
 */
/*==========================================================================*/
size_t ImageObject::height() const
{
    return m_height;
}

/*==========================================================================*/
/**
 *  @brief  Returns the pixel data array.
 *  @return pixel data array
 */
/*==========================================================================*/
const kvs::ValueArray<kvs::UInt8>& ImageObject::data() const
{
    return m_data;
}

/*==========================================================================*/
/**
 *  @brief  Returns the number of bits per pixel.
 *  @return number of bits per pixel
 */
/*==========================================================================*/
size_t ImageObject::bitsPerPixel() const
{
    return m_type;
}

/*==========================================================================*/
/**
 *  @brief  Returns the number of bytes per pixel.
 *  @return number of bytes per pixel
 */
/*==========================================================================*/
size_t ImageObject::bytesPerPixel() const
{
    return m_type >> 3;
}

/*==========================================================================*/
/**
 *  @brief  Returns the number of color channels.
 *  @return number of color channels
 */
/*==========================================================================*/
size_t ImageObject::numberOfChannels() const
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

    return ret;
}

/*==========================================================================*/
/**
 *  @brief  Returns the number of pixels.
 *  @return number of pixels
 */
/*==========================================================================*/
size_t ImageObject::get_number_of_pixels() const
{
    return ( m_type >> 3 ) * m_width * m_height;
}

} // end of namespace kvs
