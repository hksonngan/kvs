/****************************************************************************/
/**
 *  @file KVSMLObjectUnstructuredVolume.h
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
#ifndef KVS__KVSML_OBJECT_UNSTRUCTURED_VOLUME_H_INCLUDE
#define KVS__KVSML_OBJECT_UNSTRUCTURED_VOLUME_H_INCLUDE

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
 *  @brief  KVSML unstructured volume object format.
 */
/*===========================================================================*/
class KVSMLObjectUnstructuredVolume : public kvs::FileFormatBase
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
    std::string m_cell_type; ///< cell type
    bool m_has_label; ///< data label is specified or not
    std::string m_label; ///< data label
    size_t m_veclen; ///< vector length
    size_t m_nnodes; ///< number of nodes
    size_t m_ncells; ///< number of cells
    bool m_has_min_value; ///< min. value is specified or not
    bool m_has_max_value; ///< max. value is specified or not
    double m_min_value; ///< min. value
    double m_max_value; ///< max. value
    kvs::AnyValueArray m_values; ///< field value array
    kvs::ValueArray<kvs::Real32> m_coords; ///< coordinate value array
    kvs::ValueArray<kvs::UInt32> m_connections; ///< connection id array

public:

    static bool CheckExtension( const std::string& filename );
    static bool CheckFormat( const std::string& filename );

public:

    KVSMLObjectUnstructuredVolume();
    KVSMLObjectUnstructuredVolume( const std::string& filename );
    virtual ~KVSMLObjectUnstructuredVolume();

    const kvs::kvsml::KVSMLTag& KVSMLTag() const;
    const kvs::kvsml::ObjectTag& objectTag() const;
    const std::string& cellType() const;
    bool hasLabel() const;
    const std::string& label() const;
    size_t veclen() const;
    size_t nnodes() const;
    size_t ncells() const;
    bool hasMinValue() const;
    bool hasMaxValue() const;
    double minValue() const;
    double maxValue() const;
    const kvs::AnyValueArray& values() const;
    const kvs::ValueArray<kvs::Real32>& coords() const;
    const kvs::ValueArray<kvs::UInt32>& connections() const;

    void setWritingDataType( const WritingDataType writing_type );
    void setCellType( const std::string& cell_type );
    void setLabel( const std::string& label );
    void setVeclen( const size_t veclen );
    void setNNodes( const size_t nnodes );
    void setNCells( const size_t ncells );
    void setMinValue( const double min_value );
    void setMaxValue( const double max_value );
    void setValues( const kvs::AnyValueArray& values );
    void setCoords( const kvs::ValueArray<kvs::Real32>& coords );
    void setConnections( const kvs::ValueArray<kvs::UInt32>& connections );

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( const std::string& filename );
    bool write( const std::string& filename );
};

} // end of namespace kvs

#endif // KVS__KVSML_OBJECT_UNSTRUCTURED_VOLUME_H_INCLUDE
