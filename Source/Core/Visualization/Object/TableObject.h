/*****************************************************************************/
/**
 *  @file   TableObject.h
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
#ifndef KVS__TABLE_OBJECT_H_INCLUDE
#define KVS__TABLE_OBJECT_H_INCLUDE

#include <vector>
#include <ostream>
#include <kvs/Module>
#include <kvs/ObjectBase>
#include <kvs/Type>
#include <kvs/AnyValueArray>
#include <kvs/Indent>
#include <kvs/Deprecated>


namespace kvs
{

/*===========================================================================*/
/**
 *  TableObject class.
 */
/*===========================================================================*/
class TableObject : public kvs::ObjectBase
{
    kvsModuleName( kvs::TableObject );
    kvsModuleCategory( Object );
    kvsModuleBaseClass( kvs::ObjectBase );

public:

    typedef std::vector<std::string> Labels;
    typedef std::vector<kvs::AnyValueArray> Columns;
    typedef std::vector<kvs::Real64> Values;
    typedef std::vector<kvs::UInt8> InsideRangeFlags;

private:

    size_t m_nrows; ///< number of rows
    size_t m_ncolumns; ///< number of columns
    Labels m_labels; ///< label list
    Columns m_columns; ///< column list
    Values m_min_values; ///< min. values for each column
    Values m_max_values; ///< max. values for each column
    Values m_min_ranges; ///< min. value range
    Values m_max_ranges; ///< max. value range
    InsideRangeFlags m_inside_range_flags; ///< check flags for value range

public:

    static kvs::TableObject* DownCast( kvs::ObjectBase* object );
    static const kvs::TableObject* DownCast( const kvs::ObjectBase* object );

public:

    TableObject();

    ObjectType objectType() const;
    void shallowCopy( const TableObject& other );
    void deepCopy( const TableObject& other );
    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;

    void addColumn( const kvs::AnyValueArray& array, const std::string& label = "" );
    template <typename T> void addColumn( const kvs::ValueArray<T>& array, const std::string& label = "" );
    template <typename T> void addColumn( const std::vector<T>& array, const std::string& label = "" );

    size_t numberOfColumns() const;
    size_t numberOfRows() const;
    const Labels& labels() const;
    const Columns& columns() const;
    const Values& minValues() const;
    const Values& maxValues() const;
    const Values& minRanges() const;
    const Values& maxRanges() const;
    const InsideRangeFlags& insideRangeFlags() const;
    const std::string& label( const size_t index ) const;
    const kvs::AnyValueArray& column( const size_t index ) const;
    kvs::Real64 minValue( const size_t index ) const;
    kvs::Real64 maxValue( const size_t index ) const;
    kvs::Real64 minRange( const size_t column_index ) const;
    kvs::Real64 maxRange( const size_t column_index ) const;
    bool insideRange( const size_t row_index ) const;
    template <typename T> const T& at( const size_t row, const size_t column ) const;

    void setMinValue( const size_t column_index, const kvs::Real64 value );
    void setMaxValue( const size_t column_index, const kvs::Real64 value );
    void setMinRange( const size_t column_index, const kvs::Real64 range );
    void setMaxRange( const size_t column_index, const kvs::Real64 range );
    void setRange( const size_t column_index, const kvs::Real64 min_range, const kvs::Real64 max_range );

    void moveMinRange( const size_t column_index, const kvs::Real64 drange );
    void moveMaxRange( const size_t column_index, const kvs::Real64 drange );
    void moveRange( const size_t column_index, const kvs::Real64 drange );
    void resetRange( const size_t column_index );
    void resetRange();

protected:

    void setNumberOfRows( const size_t nrows );
    void setNumberOfColumns( const size_t ncolumns );
    void setLabels( const Labels& labels );
    void setColumns( const Columns& columns );
    void setMinValues( const Values& min_values );
    void setMaxValues( const Values& max_values );
    void setMinRanges( const Values& min_ranges );
    void setMaxRanges( const Values& max_ranges );
    void setInsideRangeFlags( const InsideRangeFlags& inside_range_flags );

public:
    typedef KVS_DEPRECATED( std::vector<std::string> LabelList );
    typedef KVS_DEPRECATED( std::vector<kvs::AnyValueArray> ColumnList );
    typedef KVS_DEPRECATED( std::vector<kvs::Real64> ValueList );
    typedef KVS_DEPRECATED( std::vector<kvs::UInt8> RangeList );
    KVS_DEPRECATED( size_t ncolumns() const ) { return this->numberOfColumns(); }
    KVS_DEPRECATED( size_t nrows() const ) { return this->numberOfRows(); }
    KVS_DEPRECATED( const Labels labelList() const ) { return this->labels(); }
    KVS_DEPRECATED( const Columns columnList() const ) { return this->columns(); }
    KVS_DEPRECATED( const Values minValueList() const ) { return this->minValues(); }
    KVS_DEPRECATED( const Values maxValueList() const ) { return this->maxValues(); }
    KVS_DEPRECATED( const Values& minRangeList() const ) { return this->minRanges(); }
    KVS_DEPRECATED( const Values& maxRangeList() const ) { return this->maxRanges(); }
    KVS_DEPRECATED( const InsideRangeFlags& insideRangeList() const ) { return this->insideRangeFlags(); }
};

/*===========================================================================*/
/**
 *  @brief  Adds a column.
 *  @param  array [in] column array
 *  @param  label [in] column label
 */
/*===========================================================================*/
template <typename T>
inline void TableObject::addColumn( const kvs::ValueArray<T>& array, const std::string& label )
{
    this->addColumn( kvs::AnyValueArray( array ), label ); // Shallow copy.
}

/*===========================================================================*/
/**
 *  @brief  Adds a column.
 *  @param  array [in] column array
 *  @param  label [in] column label
 */
/*===========================================================================*/
template <typename T>
inline void TableObject::addColumn( const std::vector<T>& array, const std::string& label )
{
    this->addColumn( kvs::AnyValueArray( array ), label ); // Deep copy.
}

/*===========================================================================*/
/**
 *  @brief  Returns value specified by indices.
 *  @param  row [in] row index
 *  @param  column [in] column index
 */
/*===========================================================================*/
template <typename T>
inline const T& TableObject::at( const size_t row, const size_t column ) const
{
    return( this->column( column ).template at<T>( row ) );
}

} // end of namespace kvs

#endif // KVS__TABLE_OBJECT_H_INCLUDE
