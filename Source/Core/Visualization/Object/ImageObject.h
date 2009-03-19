/****************************************************************************/
/**
 *  @file ImageObject.h
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
#ifndef KVS_CORE_IMAGE_OBJECT_H_INCLUDE
#define KVS_CORE_IMAGE_OBJECT_H_INCLUDE

#include "ObjectBase.h"
#include <kvs/ClassName>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/Module>


namespace kvs
{

/*==========================================================================*/
/**
 *  Image object structure.
 */
/*==========================================================================*/
class ImageObject : public kvs::ObjectBase
{
    // Class name.
    kvsClassName( ImageObject );

    // Module information.
    kvsModuleCategory( Object );
    kvsModuleBaseClass( kvs::ObjectBase );

public:

    enum PixelType
    {
        Gray8   =  8, ///< 8 bit gray pixel
        Gray16  = 16, ///< 16 bit gray pixel
        Color24 = 24, ///< 24 bit RGB color pixel (8x8x8 bits)
        Color32 = 32  ///< 32 bit RGBA color pixel (8x8x8x8 bits)
    };

protected:

    ImageObject::PixelType      m_type;   ///< pixel type
    size_t                      m_width;  ///< image width
    size_t                      m_height; ///< image height
    kvs::ValueArray<kvs::UInt8> m_data;   ///< pixel data

public:

    ImageObject( void );

    ImageObject(
        const size_t                       width,
        const size_t                       height,
        const kvs::ValueArray<kvs::UInt8>& data,
        const ImageObject::PixelType       type = ImageObject::Color24 );

    virtual ~ImageObject( void );

public:

    ImageObject& operator = ( const ImageObject& image );

    friend std::ostream& operator << ( std::ostream& os, const ImageObject& object );

public:

    const ObjectType objectType( void ) const;

    ImageObject::PixelType type( void ) const;

    size_t width( void ) const;

    size_t height( void ) const;

    const kvs::ValueArray<kvs::UInt8>& data( void ) const;

    size_t bitsPerPixel( void ) const;

    size_t bytesPerPixel( void ) const;

    size_t nchannels( void ) const;

protected:

    size_t get_npixels( void ) const;
};

} // end of namespace kvs

#endif // KVS_CORE_IMAGE_OBJECT_H_INCLUDE
