/*****************************************************************************/
/**
 *  @file   ImageObject.h
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
#ifndef KVS__IMAGE_OBJECT_H_INCLUDE
#define KVS__IMAGE_OBJECT_H_INCLUDE

#include <ostream>
#include <kvs/ObjectBase>
#include <kvs/ClassName>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/Module>
#include <kvs/Indent>
#include <kvs/Deprecated>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Image object class.
 */
/*===========================================================================*/
class ImageObject : public kvs::ObjectBase
{
    kvsModule( kvs::ImageObject, Object );
    kvsModuleBaseClass( kvs::ObjectBase );

public:

    enum PixelType
    {
        Gray8   =  8, ///< 8 bit gray pixel
        Gray16  = 16, ///< 16 bit gray pixel
        Color24 = 24, ///< 24 bit RGB color pixel (8x8x8 bits)
        Color32 = 32  ///< 32 bit RGBA color pixel (8x8x8x8 bits)
    };

private:

    ImageObject::PixelType m_type; ///< pixel type
    size_t m_width; ///< image width
    size_t m_height; ///< image height
    kvs::ValueArray<kvs::UInt8> m_pixels; ///< pixel data

public:

    ImageObject();
    ImageObject(
        const size_t width,
        const size_t height,
        const kvs::ValueArray<kvs::UInt8>& pixels,
        const ImageObject::PixelType type = ImageObject::Color24 );

    void shallowCopy( const ImageObject& object );
    void deepCopy( const ImageObject& object );
    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;

    ObjectType objectType() const;
    ImageObject::PixelType type() const;
    size_t width() const;
    size_t height() const;
    const kvs::ValueArray<kvs::UInt8>& pixels() const;
    size_t bitsPerPixel() const;
    size_t bytesPerPixel() const;
    size_t numberOfChannels() const;

    void setSize( const size_t width, const size_t height );
    void setPixels( const kvs::ValueArray<kvs::UInt8>& pixels, const ImageObject::PixelType type = ImageObject::Color24 );

private:

    size_t get_number_of_pixels() const;

public:
    KVS_DEPRECATED( const kvs::ValueArray<kvs::UInt8>& data() const ) { return this->pixels(); }
    KVS_DEPRECATED( size_t nchannels() const ) { return this->numberOfChannels(); }
    KVS_DEPRECATED( friend std::ostream& operator << ( std::ostream& os, const ImageObject& object ) );
};

} // end of namespace kvs

#endif // KVS__IMAGE_OBJECT_H_INCLUDE
