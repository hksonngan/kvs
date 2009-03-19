/****************************************************************************/
/**
 *  @file ColorImage.cpp
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
#include "ColorImage.h"
#include "GrayImage.h"
#include "BitImage.h"
#include <kvs/IgnoreUnusedVariable>
#include <kvs/RGBColor>
#include <kvs/File>
#include <kvs/Bmp>
#include <kvs/Ppm>
#include <kvs/Pgm>
#include <kvs/Pbm>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructs a new color image.
 */
/*==========================================================================*/
ColorImage::ColorImage( void )
{
}

/*==========================================================================*/
/**
 *  Constructs a new color image.
 *  @param width [in] image width
 *  @param height [in] image height
 */
/*==========================================================================*/
ColorImage::ColorImage( const size_t width, const size_t height ):
    kvs::ImageBase( width, height, kvs::ImageBase::Color )
{
}

/*==========================================================================*/
/**
 *  Constructs a new color image from the given pixel data.
 *  @param width [in] image width
 *  @param height [in] image height
 *  @param data [in] pointer to pixel data
 */
/*==========================================================================*/
ColorImage::ColorImage(
    const size_t width,
    const size_t height,
    const kvs::UInt8* data ):
    kvs::ImageBase( width, height, kvs::ImageBase::Color, data )
{
}

/*==========================================================================*/
/**
 *  Constructs a new color image from the given pixel data.
 *  @param width [in] image width
 *  @param height [in] image height
 *  @param data [in] pixel data array
 */
/*==========================================================================*/
ColorImage::ColorImage(
    const size_t width,
    const size_t height,
    const kvs::ValueArray<kvs::UInt8>& data ):
    kvs::ImageBase( width, height, kvs::ImageBase::Color, data )
{
}

/*===========================================================================*/
/**
 *  @brief  Constructs a copy of other color image.
 *  @param  image [in] color image
 */
/*===========================================================================*/
ColorImage::ColorImage( const kvs::ColorImage& image )
{
    BaseClass::copy( image );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a copy of other gray image.
 *  @param  image [in] gray image
 */
/*===========================================================================*/
ColorImage::ColorImage( const kvs::GrayImage& image )
{
    this->read_image( image );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a copy of other bit image.
 *  @param  image [in] bit image
 */
/*===========================================================================*/
ColorImage::ColorImage( const kvs::BitImage& image )
{
    this->read_image( image );
}

/*==========================================================================*/
/**
 *  Destroys the color image.
 */
/*==========================================================================*/
ColorImage::~ColorImage( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Copys other color image.
 *  @param  image [in] color image
 */
/*===========================================================================*/
kvs::ColorImage& ColorImage::operator = ( const kvs::ColorImage& image )
{
    BaseClass::copy( image );
    return( *this );
}

/*==========================================================================*/
/**
 *  Returns the red component.
 *  @param index [in] pixel index
 *  @return red component
 */
/*==========================================================================*/
const kvs::UInt8 ColorImage::r( const size_t index ) const
{
    return( m_data[ 3 * index ] );
}

/*==========================================================================*/
/**
 *  Returns the red component.
 *  @param i [in] pixel index along the horizontal axis
 *  @param j [in] pixel index along the vertical axis
 *  @return red component
 */
/*==========================================================================*/
const kvs::UInt8 ColorImage::r( const size_t i, const size_t j ) const
{
    return( m_data[ 3 * ( m_width * j + i ) ] );
}

/*==========================================================================*/
/**
 *  Returns the green component.
 *  @param index [in] pixel index
 *  @return green component
 */
/*==========================================================================*/
const kvs::UInt8 ColorImage::g( const size_t index ) const
{
    return( m_data[ 3 * index + 1 ] );
}

/*==========================================================================*/
/**
 *  Returns the green component.
 *  @param i [in] pixel index along the horizontal axis
 *  @param j [in] pixel index along the vertical axis
 *  @return green component
 */
/*==========================================================================*/
const kvs::UInt8 ColorImage::g( const size_t i, const size_t j ) const
{
    return( m_data[ 3 * ( m_width * j + i ) + 1 ] );
}

/*==========================================================================*/
/**
 *  Returns the blue component.
 *  @param index [in] pixel index
 *  @return blue component
 */
/*==========================================================================*/
const kvs::UInt8 ColorImage::b( const size_t index ) const
{
    return( m_data[ 3 * index + 2 ] );
}

/*==========================================================================*/
/**
 *  Returns the blue component.
 *  @param i [in] pixel index along the horizontal axis
 *  @param j [in] pixel index along the vertical axis
 *  @return blue component
 */
/*==========================================================================*/
const kvs::UInt8 ColorImage::b( const size_t i, const size_t j ) const
{
    return( m_data[ 3 * ( m_width * j + i ) + 2 ] );
}

/*==========================================================================*/
/**
 *  Returns the pixel color.
 *  @param index [in] pixel index
 *  @return pixel color
 */
/*==========================================================================*/
const kvs::RGBColor ColorImage::pixel( const size_t index ) const
{
    const int index3 = index * 3;
    return( kvs::RGBColor( m_data[index3], m_data[index3+1], m_data[index3+2] ) );
}

/*==========================================================================*/
/**
 *  Returns the pixel color.
 *  @param i [in] pixel index along the horizontal axis
 *  @param j [in] pixel index along the vertical axis
 *  @return pixel color
 */
/*==========================================================================*/
const kvs::RGBColor ColorImage::pixel( const size_t i, const size_t j ) const
{
    const size_t index3 = ( m_width * j + i ) * 3;
    return( kvs::RGBColor( m_data[index3], m_data[index3+1], m_data[index3+2] ) );
}

/*==========================================================================*/
/**
 *  Set the pixel color.
 *  @param index [in] pixel index
 *  @param pixel [in] pixel color
 */
/*==========================================================================*/
void ColorImage::set( const size_t index, const kvs::RGBColor& pixel )
{
    const size_t index3 = index * 3;
    m_data[ index3 + 0 ] = pixel.r();
    m_data[ index3 + 1 ] = pixel.g();
    m_data[ index3 + 2 ] = pixel.b();
}

/*==========================================================================*/
/**
 *  Set the pixel color.
 *  @param i [in] pixel index along the horizontal axis
 *  @param j [in] pixel index along the vertical axis
 *  @param pixel [in] pixel color
 */
/*==========================================================================*/
void ColorImage::set( const size_t i, const size_t j, const kvs::RGBColor& pixel )
{
    const size_t index3 = ( m_width * j + i ) * 3;
    m_data[ index3 + 0 ] = pixel.r();
    m_data[ index3 + 1 ] = pixel.g();
    m_data[ index3 + 2 ] = pixel.b();
}

/*===========================================================================*/
/**
 *  @brief  Scales the image data.
 *  @param  ratio [in] scaling ratio
 */
/*===========================================================================*/
void ColorImage::scale( const double ratio )
{
    const size_t width = static_cast<size_t>( this->width() * ratio );
    const size_t height = static_cast<size_t>( this->height() * ratio );
    BaseClass::resize<ColorImage,ColorImage::Bilinear>( width, height, this );
}

/*===========================================================================*/
/**
 *  @brief  Scales the image data.
 *  @param  ratio [in] scaling ratio
 *  @param  method [in] Interpolation method
 */
/*===========================================================================*/
template <typename InterpolationMethod>
void ColorImage::scale( const double ratio, InterpolationMethod method )
{
    kvs::IgnoreUnusedVariable( method );

    const size_t width = static_cast<size_t>( this->width() * ratio );
    const size_t height = static_cast<size_t>( this->height() * ratio );
    BaseClass::resize<ColorImage,InterpolationMethod>( width, height, this );
}

// Specialization.
template
void ColorImage::scale( const double ratio, ColorImage::NearestNeighbor method );

template
void ColorImage::scale( const double ratio, ColorImage::Bilinear method );

/*===========================================================================*/
/**
 *  @brief  Resizes the image data.
 *  @param  width  [in] resized width
 *  @param  height [in] resized height
 */
/*===========================================================================*/
void ColorImage::resize( const size_t width, const size_t height )
{
    BaseClass::resize<ColorImage,ColorImage::Bilinear>( width, height, this );
}

/*===========================================================================*/
/**
 *  @brief  Resizes the image data.
 *  @param  width [in] resized width
 *  @param  height [in] resized height
 *  @param  method [in] Interpolation method
 */
/*===========================================================================*/
template <typename InterpolationMethod>
void ColorImage::resize( const size_t width, const size_t height, InterpolationMethod method )
{
    kvs::IgnoreUnusedVariable( method );

    BaseClass::resize<ColorImage,InterpolationMethod>( width, height, this );
}

// Specialization.
template
void ColorImage::resize( const size_t width, const size_t height, ColorImage::NearestNeighbor method );

template
void ColorImage::resize( const size_t width, const size_t height, ColorImage::Bilinear method );

/*==========================================================================*/
/**
 *  Read a image file.
 *  @param filename [in] filename
 *  @return true, if the reading process is done successfully
 */
/*==========================================================================*/
const bool ColorImage::read( const std::string& filename )
{
    const kvs::File file( filename );
    const std::string extension = file.extension();

    // Color image.
    if ( extension == "bmp" )
    {
        const kvs::Bmp bmp( filename );
        return( BaseClass::create( bmp.width(), bmp.height(), BaseClass::Color, bmp.data() ) );
    }
    else if ( extension == "ppm" )
    {
        const kvs::Ppm ppm( filename );
        return( BaseClass::create( ppm.width(), ppm.height(), BaseClass::Color, ppm.data() ) );
    }
    // Gray image.
    else if ( extension == "pgb" )
    {
        kvs::GrayImage image; image.read( filename );
        return( this->read_image( image ) );
    }
    // Bit image.
    else if ( extension == "pbm" )
    {
        kvs::BitImage image; image.read( filename );
        return( this->read_image( image ) );
    }
    // Not supported.
    else
    {
        kvsMessageError("Unsupported image format '%s'.",extension.c_str());
        return( false );
    }
}

/*==========================================================================*/
/**
 *  Write a image file.
 *  @param filename [in] filename
 *  @return true, if the writing process is done successfully
 */
/*==========================================================================*/
const bool ColorImage::write( const std::string& filename )
{
    const kvs::File file( filename );
    const std::string extension = file.extension();

    // Color image.
    if ( extension == "bmp" )
    {
        kvs::Bmp bmp( m_width, m_height, m_data );
        return( bmp.write( filename ) );
    }
    else if ( extension == "ppm" )
    {
        kvs::Ppm ppm( m_width, m_height, m_data );
        return( ppm.write( filename ) );
    }
    // Gray image.
    else if ( extension == "pgm" )
    {
        kvs::GrayImage image( *this );
        return( image.write( filename ) );
    }
    // Bit image.
    else if ( extension == "pbm" )
    {
        kvs::BitImage image( kvs::GrayImage( *this ) );
        return( image.write( filename ) );
    }
    else
    {
        kvsMessageError("Unsupported image format '%s'.",extension.c_str());
        return( false );
    }
}

/*===========================================================================*/
/**
 *  @brief  Reads the gray image.
 *  @param  image [in] gray image
 *  @return true, if the reading process is done successfully.
 */
/*===========================================================================*/
const bool ColorImage::read_image( const kvs::GrayImage& image )
{
    if ( !BaseClass::create( image.width(), image.height(), kvs::ImageBase::Color ) )
    {
        return( false );
    }

    const kvs::UInt8* data = image.data().pointer();
    for ( size_t index = 0, index3 = 0; index < m_npixels; index++, index3 += 3 )
    {
        const kvs::UInt8 pixel = data[ index ];
        m_data[ index3 + 0 ] = pixel;
        m_data[ index3 + 1 ] = pixel;
        m_data[ index3 + 2 ] = pixel;
    }

    return( true );
}

/*===========================================================================*/
/**
 *  @brief  Reads the bit image.
 *  @param  image [in] bit image
 *  @return true, if the reading process is done successfully.
 */
/*===========================================================================*/
const bool ColorImage::read_image( const kvs::BitImage& image )
{
    if ( !BaseClass::create( image.width(), image.height(), kvs::ImageBase::Color ) )
    {
        return( false );
    }

    const size_t width = image.width();
    const size_t height = image.height();
    size_t index3 = 0;
    for ( size_t j = 0; j < height; j++ )
    {
        for ( size_t i = 0; i < width; i++, index3 += 3 )
        {
            const kvs::UInt8 pixel = image.pixel( i, j ) ? 255 : 0;
            m_data[ index3 + 0 ] = pixel;
            m_data[ index3 + 1 ] = pixel;
            m_data[ index3 + 2 ] = pixel;
        }
    }

    return( true );
}

} // end of namespace kvs
