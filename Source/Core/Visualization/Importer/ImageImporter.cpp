/****************************************************************************/
/**
 *  @file ImageImporter.cpp
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
#include "ImageImporter.h"
#include <kvs/Message>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <string>


namespace kvs
{

/*==========================================================================*/
/**
 *  Defualt constructor.
 */
/*==========================================================================*/
ImageImporter::ImageImporter( void )
{
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param file_format [in] pointer to the file format class
 */
/*==========================================================================*/
ImageImporter::ImageImporter( const kvs::FileFormatBase* file_format )
{
    this->exec( file_format );
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
ImageImporter::~ImageImporter( void )
{
}

kvs::ObjectBase* ImageImporter::exec( const kvs::FileFormatBase* file_format )
{
    const std::string class_name = file_format->className();
    if ( class_name == "Bmp" )
    {
        this->import( reinterpret_cast<const kvs::Bmp*>( file_format ) );
    }
    else if ( class_name == "Tiff" )
    {
        this->import( reinterpret_cast<const kvs::Tiff*>( file_format ) );
    }
    else if ( class_name == "Ppm" )
    {
        this->import( reinterpret_cast<const kvs::Ppm*>( file_format ) );
    }
    else if ( class_name == "Pgm" )
    {
        this->import( reinterpret_cast<const kvs::Pgm*>( file_format ) );
    }
    else if ( class_name == "Pbm" )
    {
        this->import( reinterpret_cast<const kvs::Pbm*>( file_format ) );
    }
    else if ( class_name == "Dicom" )
    {
        this->import( reinterpret_cast<const kvs::Dicom*>( file_format ) );
    }
    else
    {
        kvsMessageError( "Unsupported class '%s'.", class_name.c_str() );
    }

    return( this );
}

/*==========================================================================*/
/**
 *  Import image data.
 *  @param bmp [in] pointer to a bitmap image
 */
/*==========================================================================*/
void ImageImporter::import( const kvs::Bmp* bmp )
{
    SuperClass::m_width  = bmp->width();
    SuperClass::m_height = bmp->height();
    SuperClass::m_data   = bmp->data(); // shallow copy
    SuperClass::m_type   = static_cast<SuperClass::PixelType>( bmp->bitsPerPixel() );
}

/*==========================================================================*/
/**
 *  Import image data.
 *  @param tiff [in] pointer to a tiff image
 */
/*==========================================================================*/
void ImageImporter::import( const kvs::Tiff* tiff )
{
    kvs::ImageObject::PixelType pixel_type = kvs::ImageObject::Gray8;
    if ( tiff->colorMode() == kvs::Tiff::Gray8 )
    {
        pixel_type = kvs::ImageObject::Gray8;
    }
    else if ( tiff->colorMode() == kvs::Tiff::Gray16 )
    {
        pixel_type = kvs::ImageObject::Gray16;
    }
    else if ( tiff->colorMode() == kvs::Tiff::Color24 )
    {
        pixel_type = kvs::ImageObject::Color24;
    }
    else //  tiff->colorMode() == kvs::Tiff::UnknownColorMode
    {
        kvsMessageError("Unknown TIFF color mode.");
    }

    const kvs::UInt8* raw_data = reinterpret_cast<const kvs::UInt8*>( tiff->rawData().pointer() );
    const size_t      raw_size = tiff->rawData().byteSize();
    kvs::ValueArray<kvs::UInt8> data( raw_data, raw_size ); // deep copy

    SuperClass::m_width  = tiff->width();
    SuperClass::m_height = tiff->height();
    SuperClass::m_data   = data; // shallow copy
    SuperClass::m_type   = pixel_type;
}

/*==========================================================================*/
/**
 *  Import image data.
 *  @param ppm [in] pointer to a ppm image
 */
/*==========================================================================*/
void ImageImporter::import( const kvs::Ppm* ppm )
{
    SuperClass::m_width  = ppm->width();
    SuperClass::m_height = ppm->height();
    SuperClass::m_data   = ppm->data();
    SuperClass::m_type   = kvs::ImageObject::Color24;
}

/*==========================================================================*/
/**
 *  Import image data.
 *  @param pgm [in] pointer to a pgm image
 */
/*==========================================================================*/
void ImageImporter::import( const kvs::Pgm* pgm )
{
    SuperClass::m_width  = pgm->width();
    SuperClass::m_height = pgm->height();
    SuperClass::m_data   = pgm->data();
    SuperClass::m_type   = kvs::ImageObject::Gray8;
}

/*==========================================================================*/
/**
 *  Import image data.
 *  @param pbm [in] pointer to a pbm image
 */
/*==========================================================================*/
void ImageImporter::import( const kvs::Pbm* pbm )
{
    const size_t npixels = pbm->width() * pbm->height();
    kvs::ValueArray<kvs::UInt8> data( npixels );

    for ( size_t i = 0; i < npixels; i++ )
    {
        data[i] = pbm->data().test(i) ? 0 : 255;
    }

    SuperClass::m_width  = pbm->width();
    SuperClass::m_height = pbm->height();
    SuperClass::m_data   = data;
    SuperClass::m_type   = kvs::ImageObject::Gray8;
}

/*==========================================================================*/
/**
 *  Import image data.
 *  @param pbm [in] pointer to a dicom image
 */
/*==========================================================================*/
void ImageImporter::import( const kvs::Dicom* dicom )
{
    SuperClass::m_width  = dicom->column();
    SuperClass::m_height = dicom->row();
    SuperClass::m_data   = dicom->pixelData();
    SuperClass::m_type   = kvs::ImageObject::Gray8;
}

} // end of namespace kvs
