/*****************************************************************************/
/**
 *  @file   KVSMLObjectTable.h
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
#ifndef KVS__KVSML_OBJECT_TABLE_H_INCLUDE
#define KVS__KVSML_OBJECT_TABLE_H_INCLUDE

#include <kvs/FileFormatBase>
#include <kvs/AnyValueArray>
#include <kvs/Type>
#include <kvs/Vector3>
#include <kvs/Indent>
#include <string>
#include <vector>
#include <Core/FileFormat/KVSML/KVSMLTag.h>
#include <Core/FileFormat/KVSML/ObjectTag.h>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  KVSML table object format.
 */
/*===========================================================================*/
class KVSMLObjectTable : public kvs::FileFormatBase
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
    size_t m_nrows; ///< number of rows
    size_t m_ncolumns; ///< number of columns
    std::vector<std::string> m_labels; ///< column label list
    std::vector<kvs::AnyValueArray> m_columns; ///< column list
    std::vector<bool> m_has_min_values; ///< min. value flag list
    std::vector<bool> m_has_max_values; ///< max. value flag list
    std::vector<bool> m_has_min_ranges; ///< min. range flag list
    std::vector<bool> m_has_max_ranges; ///< max. range flag list
    std::vector<double> m_min_values; ///< min. value list
    std::vector<double> m_max_values; ///< max. value list
    std::vector<double> m_min_ranges; ///< min. range list
    std::vector<double> m_max_ranges; ///< max. range list

public:

    static bool CheckExtension( const std::string& filename );
    static bool CheckFormat( const std::string& filename );

public:

    KVSMLObjectTable();
    KVSMLObjectTable( const std::string& filename );
    virtual ~KVSMLObjectTable();

    const kvs::kvsml::KVSMLTag& KVSMLTag() const;
    const kvs::kvsml::ObjectTag& objectTag() const;
    size_t nrows() const;
    size_t ncolumns() const;
    const std::vector<std::string>& labelList() const;
    const std::vector<kvs::AnyValueArray>& columnList() const;
    const std::vector<bool>& hasMinValueList() const;
    const std::vector<bool>& hasMaxValueList() const;
    const std::vector<bool>& hasMinRangeList() const;
    const std::vector<bool>& hasMaxRangeList() const;
    const std::vector<double>& minValueList() const;
    const std::vector<double>& maxValueList() const;
    const std::vector<double>& minRangeList() const;
    const std::vector<double>& maxRangeList() const;

    void setWritingDataType( const WritingDataType writing_type );
    void setMinValue( const size_t column_index, const double value );
    void setMaxValue( const size_t column_index, const double value );
    void setMinRange( const size_t column_index, const double range );
    void setMaxRange( const size_t column_index, const double range );
    void addColumn( const kvs::AnyValueArray& column, const std::string& label );

    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;
    bool read( const std::string& filename );
    bool write( const std::string& filename );
};

} // end of namespace kvs

#endif // KVS__KVSML_OBJECT_TABLE_H_INCLUDE
