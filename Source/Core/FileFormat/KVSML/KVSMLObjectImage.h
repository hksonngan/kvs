/****************************************************************************/
/**
 *  @file KVSMLObjectImage.h
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
#ifndef KVS__KVSML_OBJECT_IMAGE_H_INCLUDE
#define KVS__KVSML_OBJECT_IMAGE_H_INCLUDE

#include <kvs/FileFormatBase>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/Vector3>
#include <kvs/Indent>
#include <kvs/Deprecated>
#include "KVSMLTag.h"
#include "ObjectTag.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  KVSML image object format.
 */
/*===========================================================================*/
class KVSMLObjectImage : public kvs::FileFormatBase
{
public:

    typedef kvs::FileFormatBase BaseClass;

    enum WritingDataType
    {
        Ascii = 0,     ///< ascii data type
        ExternalAscii, ///< external ascii data type
        ExternalBinary ///< external binary data type
    };

private:

    kvs::kvsml::KVSMLTag m_kvsml_tag; ///< KVSML tag information
    kvs::kvsml::ObjectTag m_object_tag; ///< Object tag information
    size_t m_width; ///< image width
    size_t m_height; ///< image height
    std::string m_pixel_type; ///< pixel type
    WritingDataType m_writing_type; ///< writing data type
    kvs::ValueArray<kvs::UInt8> m_pixels; ///< color(r,g,b) array

public:

    static bool CheckExtension( const std::string& filename );
    static bool CheckFormat( const std::string& filename );

public:

    KVSMLObjectImage();
    KVSMLObjectImage( const std::string& filename );

    const kvs::kvsml::KVSMLTag& KVSMLTag() const;
    const kvs::kvsml::ObjectTag& objectTag() const;
    size_t width() const;
    size_t height() const;
    const std::string& pixelType() const;
    const kvs::ValueArray<kvs::UInt8>& pixels() const;

    void setWidth( const size_t width );
    void setHeight( const size_t height );
    void setPixelType( const std::string& pixel_type );
    void setWritingDataType( const WritingDataType writing_type );
    void setPixels( const kvs::ValueArray<kvs::UInt8>& pixels );

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( const std::string& filename );
    bool write( const std::string& filename );

public:
    KVS_DEPRECATED( const kvs::ValueArray<kvs::UInt8>& data() const ) { return this->pixels(); }
    KVS_DEPRECATED( void setData( const kvs::ValueArray<kvs::UInt8>& data ) ) { this->setPixels( data ); }
};

} // end of namespace kvs

#endif // KVS__KVSML_OBJECT_IMAGE_H_INCLUDE
