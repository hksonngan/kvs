/****************************************************************************/
/**
 *  @file KVSMLObjectImage.cpp
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
#include "KVSMLObjectImage.h"
#include "ImageObjectTag.h"
#include "PixelTag.h"
#include "DataArrayTag.h"
#include <kvs/XMLDocument>
#include <kvs/XMLDeclaration>
#include <kvs/XMLElement>
#include <kvs/XMLComment>
#include <kvs/ValueArray>
#include <kvs/File>
#include <kvs/Type>
#include <kvs/File>
#include <kvs/IgnoreUnusedVariable>
#include <iostream>
#include <fstream>
#include <sstream>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new KVSML image object class.
 */
/*===========================================================================*/
KVSMLObjectImage::KVSMLObjectImage():
    m_width( 0 ),
    m_height( 0 ),
    m_pixel_type( "" ),
    m_writing_type( kvs::KVSMLObjectImage::Ascii )
{
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new KVSML image object class.
 *  @param  filename [in] filename
 */
/*===========================================================================*/
KVSMLObjectImage::KVSMLObjectImage( const std::string& filename ):
    m_width( 0 ),
    m_height( 0 ),
    m_pixel_type( "" ),
    m_writing_type( kvs::KVSMLObjectImage::Ascii )
{
    this->read( filename );
}

/*===========================================================================*/
/**
 *  @brief  Destructs the KVSML image object class.
 */
/*===========================================================================*/
KVSMLObjectImage::~KVSMLObjectImage()
{
}

/*===========================================================================*/
/**
 *  @brief  Returns the KVSML tag.
 *  @return KVSML tag
 */
/*===========================================================================*/
const kvs::kvsml::KVSMLTag& KVSMLObjectImage::KVSMLTag() const
{
    return m_kvsml_tag;
}

/*===========================================================================*/
/**
 *  @brief  Returns the object tag.
 *  @return object tag
 */
/*===========================================================================*/
const kvs::kvsml::ObjectTag& KVSMLObjectImage::objectTag() const
{
    return m_object_tag;
}

/*===========================================================================*/
/**
 *  @brief  Returns a image width.
 *  @return image width
 */
/*===========================================================================*/
size_t KVSMLObjectImage::width() const
{
    return m_width;
}

/*===========================================================================*/
/**
 *  @brief  Returns a image height.
 *  @return image height
 */
/*===========================================================================*/
size_t KVSMLObjectImage::height() const
{
    return m_height;
}

/*===========================================================================*/
/**
 *  @brief  Returns a pixel type.
 *  @return pixel type
 */
/*===========================================================================*/
const std::string& KVSMLObjectImage::pixelType() const
{
    return m_pixel_type;
}

/*===========================================================================*/
/**
 *  @brief  Returns a pixel data array.
 *  @return pixel data array
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::UInt8>& KVSMLObjectImage::data() const
{
    return m_data;
}

/*===========================================================================*/
/**
 *  @brief  Sets a image width.
 *  @param  width [in] image width
 */
/*===========================================================================*/
void KVSMLObjectImage::setWidth( const size_t width )
{
    m_width = width;
}

/*===========================================================================*/
/**
 *  @brief  Sets a image height.
 *  @param  height [in] image height
 */
/*===========================================================================*/
void KVSMLObjectImage::setHeight( const size_t height )
{
    m_height = height;
}

/*===========================================================================*/
/**
 *  @brief  Sets a pixel type.
 *  @param  pixel_type [in] pixel type
 */
/*===========================================================================*/
void KVSMLObjectImage::setPixelType( const std::string& pixel_type )
{
    m_pixel_type = pixel_type;
}

/*===========================================================================*/
/**
 *  @brief  Set a writing type.
 *  @param  writing_type [in] writing type
 */
/*===========================================================================*/
void KVSMLObjectImage::setWritingDataType( const WritingDataType writing_type )
{
    m_writing_type = writing_type;
}

/*===========================================================================*/
/**
 *  @brief  Set a pixel data array.
 *  @param  data [in] pixel data
 */
/*===========================================================================*/
void KVSMLObjectImage::setData( const kvs::ValueArray<kvs::UInt8>& data )
{
    m_data = data;
}

/*===========================================================================*/
/**
 *  @brief  Read a KVSMl point object file.
 *  @param  filename [in] filename
 *  @return true, if the reading process is successfully
 */
/*===========================================================================*/
bool KVSMLObjectImage::read( const std::string& filename )
{
    BaseClass::setFilename( filename );
    BaseClass::setSuccess( true );

    // XML document.
    kvs::XMLDocument document;
    if ( !document.read( filename ) )
    {
        kvsMessageError( "%s", document.ErrorDesc().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }

    // <KVSML>
    if ( !m_kvsml_tag.read( &document ) )
    {
        kvsMessageError( "Cannot read <%s>.", m_kvsml_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }

    // <Object>
    if ( !m_object_tag.read( m_kvsml_tag.node() ) )
    {
        kvsMessageError( "Cannot read <%s>.", m_object_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }

    // <ImageObject>
    kvs::kvsml::ImageObjectTag image_object_tag;
    if ( !image_object_tag.read( m_object_tag.node() ) )
    {
        kvsMessageError( "Cannot read <%s>.", image_object_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }

    if ( !image_object_tag.hasWidth() )
    {
        kvsMessageError( "'width' is not specified in <%s>.", image_object_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }
    m_width = image_object_tag.width();

    if ( !image_object_tag.hasHeight() )
    {
        kvsMessageError( "'height' is not specified in <%s>.", image_object_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }
    m_height = image_object_tag.height();

    // <Pixel>
    kvs::kvsml::PixelTag pixel_tag;
    if ( !pixel_tag.read( image_object_tag.node() ) )
    {
        kvsMessageError( "Cannot read <%s>.", image_object_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }
    else
    {
        if ( !pixel_tag.hasType() )
        {
            kvsMessageError( "'type' is not specified in <%s>.", pixel_tag.name().c_str() );
            BaseClass::setSuccess( false );
            return false;
        }
        m_pixel_type = pixel_tag.type();

        // <DataArray>
        const size_t nchannels =
            ( m_pixel_type == "gray" ) ? 1 :
            ( m_pixel_type == "color" ) ? 3 : 0;
        const size_t npixels = m_width * m_height;
        const size_t nelements = npixels * nchannels;
        kvs::kvsml::DataArrayTag data_tag;
        if ( !data_tag.read( pixel_tag.node(), nelements, &m_data ) )
        {
            kvsMessageError( "Cannot read <%s> for <%s>.",
                             data_tag.name().c_str(),
                             pixel_tag.name().c_str() );
            BaseClass::setSuccess( false );
            return false;
        }
    }

    return true;
}

/*===========================================================================*/
/**
 *  @brief  Writes the KVSML point object.
 *  @param  filename [in] filename
 *  @return true, if the writing process is done successfully
 */
/*===========================================================================*/
bool KVSMLObjectImage::write( const std::string& filename )
{
    BaseClass::setFilename( filename );
    BaseClass::setSuccess( true );

    kvs::XMLDocument document;
    document.InsertEndChild( kvs::XMLDeclaration("1.0") );
    document.InsertEndChild( kvs::XMLComment(" Generated by kvs::KVSMLObjectImage::write() ") );

    // <KVSML>
    kvs::kvsml::KVSMLTag kvsml_tag;
    if ( !kvsml_tag.write( &document ) )
    {
        kvsMessageError( "Cannot write <%s>.", kvsml_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }

    // <Object type="ImageObject">
    kvs::kvsml::ObjectTag object_tag;
    object_tag.setType( "ImageObject" );
    if ( !object_tag.write( kvsml_tag.node() ) )
    {
        kvsMessageError( "Cannot write <%s>.", object_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }

    // <ImageObject width="xxx" height="xxx">
    kvs::kvsml::ImageObjectTag image_object_tag;
    image_object_tag.setWidth( m_width );
    image_object_tag.setHeight( m_height );
    if ( !image_object_tag.write( object_tag.node() ) )
    {
        kvsMessageError( "Cannot write <%s>.", image_object_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }

    // <Pixel>
    kvs::kvsml::PixelTag pixel_tag;
    pixel_tag.setType( m_pixel_type );
    if ( !pixel_tag.write( image_object_tag.node() ) )
    {
        kvsMessageError( "Cannot write <%s>.", pixel_tag.name().c_str() );
        BaseClass::setSuccess( false );
        return false;
    }
    else
    {
        if ( m_data.size() > 0 )
        {
            // <DataArray>
            kvs::kvsml::DataArrayTag data_tag;
            if ( m_writing_type == kvs::KVSMLObjectImage::ExternalAscii )
            {
                data_tag.setFile( kvs::kvsml::DataArray::GetDataFilename( filename, "pixel" ) );
                data_tag.setFormat( "ascii" );
            }
            else if ( m_writing_type == kvs::KVSMLObjectImage::ExternalBinary )
            {
                data_tag.setFile( kvs::kvsml::DataArray::GetDataFilename( filename, "pixel" ) );
                data_tag.setFormat( "binary" );
            }

            const std::string pathname = kvs::File( filename ).pathName();
            if ( !data_tag.write( pixel_tag.node(), m_data, pathname ) )
            {
                kvsMessageError( "Cannot write <%s> for <%s>.",
                                 data_tag.name().c_str(),
                                 pixel_tag.name().c_str() );
                BaseClass::setSuccess( false );
                return false;
            }
        }
    }

    const bool success = document.write( filename );
    BaseClass::setSuccess( success );

    return success;
}

/*===========================================================================*/
/**
 *  @brief  Checks the file extension.
 *  @param  filename [in] filename
 *  @return true, if the given filename has the supported extension
 */
/*===========================================================================*/
bool KVSMLObjectImage::CheckFileExtension( const std::string& filename )
{
    const kvs::File file( filename );
    if ( file.extension() == "kvsml" ||
         file.extension() == "KVSML" ||
         file.extension() == "xml"   ||
         file.extension() == "XML" )
    {
        return true;
    }

    return false;
}

/*===========================================================================*/
/**
 *  @brief  Check the file format.
 *  @param  filename [in] filename
 *  @return true, if the KVSMLObjectImage class can read the given file
 */
/*===========================================================================*/
bool KVSMLObjectImage::CheckFileFormat( const std::string& filename )
{
    kvs::XMLDocument document;
    if ( !document.read( filename ) ) return false;

    // <KVSML>
    kvs::kvsml::KVSMLTag kvsml_tag;
    if ( !kvsml_tag.read( &document ) ) return false;

    // <Object>
    kvs::kvsml::ObjectTag object_tag;
    if ( !object_tag.read( kvsml_tag.node() ) ) return false;
    if ( object_tag.type() != "ImageObject" ) return false;

    // <ImageObject>
    kvs::kvsml::ImageObjectTag image_object_tag;
    if ( !image_object_tag.read( object_tag.node() ) ) return false;

    return true;
}

/*===========================================================================*/
/**
 *  @brief  Output operator.
 *  @param  os [out] output stream
 *  @param  rhs [in] KVSML image object
 */
/*===========================================================================*/
std::ostream& operator <<( std::ostream& os, const KVSMLObjectImage& rhs )
{
    os << "Width: " << rhs.width() << std::endl;
    os << "Height: " << rhs.height() << std::endl;
    os << "Pixel type: " << rhs.pixelType();

    return os;
}

} // end of namespace kvs
