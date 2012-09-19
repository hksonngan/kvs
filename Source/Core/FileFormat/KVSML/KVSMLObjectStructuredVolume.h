/****************************************************************************/
/**
 *  @file KVSMLObjectStructuredVolume.h
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
#ifndef KVS__KVSML_OBJECT_STRUCTURED_VOLUME_H_INCLUDE
#define KVS__KVSML_OBJECT_STRUCTURED_VOLUME_H_INCLUDE

#include <kvs/FileFormatBase>
#include <kvs/AnyValueArray>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/Vector3>
#include <kvs/Indent>
#include <string>
#include "KVSMLTag.h"
#include "ObjectTag.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  KVSML structured volume object format.
 */
/*===========================================================================*/
class KVSMLObjectStructuredVolume : public kvs::FileFormatBase
{
public:

    typedef kvs::FileFormatBase BaseClass;

    enum WritingDataType
    {
        Ascii = 0,
        ExternalAscii,
        ExternalBinary
    };

private:

    kvs::kvsml::KVSMLTag m_kvsml_tag; ///< KVSML tag information
    kvs::kvsml::ObjectTag m_object_tag; ///< Object tag information
    WritingDataType m_writing_type; ///< writing data type
    std::string m_grid_type; ///< grid type
    bool m_has_label; ///< data label is specified or not
    std::string m_label; ///< data label
    size_t m_veclen; ///< vector length
    kvs::Vector3ui m_resolution; ///< grid resolution
    bool m_has_min_value; ///< min. value is specified or not
    bool m_has_max_value; ///< max. value is specified or not
    double m_min_value; ///< min. value
    double m_max_value; ///< max. value
    kvs::AnyValueArray m_values; ///< field value array
    kvs::ValueArray<float> m_coords; ///< coordinate array

public:

    static bool CheckExtension( const std::string& filename );
    static bool CheckFormat( const std::string& filename );

public:

    KVSMLObjectStructuredVolume();
    KVSMLObjectStructuredVolume( const std::string& filename );
    virtual ~KVSMLObjectStructuredVolume();

    const kvs::kvsml::KVSMLTag& KVSMLTag() const;
    const kvs::kvsml::ObjectTag& objectTag() const;
    const std::string& gridType() const;
    bool hasLabel() const;
    const std::string& label() const;
    size_t veclen() const;
    const kvs::Vector3ui& resolution() const;
    bool hasMinValue() const;
    bool hasMaxValue() const;
    double minValue() const;
    double maxValue() const;
    const kvs::AnyValueArray& values() const;
    const kvs::ValueArray<float>& coords() const;

    void setWritingDataType( const WritingDataType writing_type );
    void setGridType( const std::string& grid_type );
    void setLabel( const std::string& label );
    void setVeclen( const size_t veclen );
    void setResolution( const kvs::Vector3ui& resolution );
    void setMinValue( const double min_value );
    void setMaxValue( const double max_value );
    void setValues( const kvs::AnyValueArray& values );
    void setCoords( const kvs::ValueArray<float>& coords );

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( const std::string& filename );
    bool write( const std::string& filename );
};

} // end of namespace kvs

#endif // KVS__KVSML_OBJECT_STRUCTURED_VOLUME_H_INCLUDE
