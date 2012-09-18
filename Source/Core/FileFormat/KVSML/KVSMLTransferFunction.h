/****************************************************************************/
/**
 *  @file KVSMLTransferFunction.h
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
#ifndef KVS__KVSML_TRANSFER_FUNCTION_H_INCLUDE
#define KVS__KVSML_TRANSFER_FUNCTION_H_INCLUDE

#include <list>
#include <iostream>
#include <kvs/FileFormatBase>
#include <kvs/RGBColor>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/Indent>
#include "KVSMLTag.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  KVSMLTransferFunction file format class.
 */
/*===========================================================================*/
class KVSMLTransferFunction : public kvs::FileFormatBase
{
public:

    typedef kvs::FileFormatBase BaseClass;
    typedef std::pair<float,kvs::Real32> OpacityPoint;
    typedef std::list<OpacityPoint> OpacityPointList;
    typedef std::pair<float,kvs::RGBColor> ColorPoint;
    typedef std::list<ColorPoint> ColorPointList;

    enum WritingDataType
    {
        Ascii = 0,
        ExternalAscii,
        ExternalBinary
    };

private:

    kvs::kvsml::KVSMLTag m_kvsml_tag; ///< KVSML tag information
    WritingDataType m_writing_type; ///< writing data type
    size_t m_resolution; ///< resolution
    float m_min_value; ///< min. scalar value
    float m_max_value; ///< max. scalar value
    OpacityPointList m_opacity_point_list; ///< opacity point list
    ColorPointList m_color_point_list; ///< color point list
    kvs::ValueArray<kvs::Real32> m_opacities; ///< opacity array
    kvs::ValueArray<kvs::UInt8> m_colors; ///< color (r,g,b) array

public:

    static bool CheckFileExtension( const std::string& filename );
    static bool CheckFileFormat( const std::string& filename );

public:

    KVSMLTransferFunction();
    KVSMLTransferFunction( const std::string& filename );
    virtual ~KVSMLTransferFunction();

    const kvs::kvsml::KVSMLTag& KVSMLTag() const;
    size_t resolution() const;
    float minValue() const;
    float maxValue() const;
    const OpacityPointList& opacityPointList() const;
    const ColorPointList& colorPointList() const;
    const kvs::ValueArray<kvs::Real32>& opacities() const;
    const kvs::ValueArray<kvs::UInt8>& colors() const;

    void addOpacityPoint( const float value, const float opacity );
    void addColorPoint( const float value, const kvs::RGBColor color );
    void setResolution( const size_t resolution );
    void setRange( const float min_value, const float max_value );
    void setWritingDataType( const WritingDataType writing_type );
    void setOpacities( const kvs::ValueArray<kvs::Real32>& opacities );
    void setColors( const kvs::ValueArray<kvs::UInt8>& colors );

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( const std::string& filename );
    bool write( const std::string& filename );
};

} // end of namespace kvs

#endif // KVS__KVSML__KVSML_TRANSFER_FUNCTION_H_INCLUDE
