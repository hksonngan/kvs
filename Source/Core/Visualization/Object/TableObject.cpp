/*****************************************************************************/
/**
 *  @file   TableObject.cpp
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
#include "TableObject.h"
#include <kvs/Value>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Downcasts to the table object from the object base.
 *  @param  object [in] point to the object base
 *  @return pointer to the table object
 */
/*===========================================================================*/
kvs::TableObject* TableObject::DownCast( kvs::ObjectBase* object )
{
    const kvs::ObjectBase::ObjectType type = object->objectType();
    if ( type != kvs::ObjectBase::Table )
    {
        kvsMessageError("Input object is not table object.");
        return NULL;
    }

    kvs::TableObject* table = static_cast<kvs::TableObject*>( object );

    return table;
}

/*===========================================================================*/
/**
 *  @brief  Downcasts to the table object from the object base with 'const'.
 *  @param  object [in] point to the object base
 *  @return pointer to the table object
 */
/*===========================================================================*/
const kvs::TableObject* TableObject::DownCast( const kvs::ObjectBase* object )
{
    return TableObject::DownCast( const_cast<kvs::ObjectBase*>( object ) );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new TableObject class.
 */
/*===========================================================================*/
TableObject::TableObject()
{
//    BaseClass::setMinMaxObjectCoords( kvs::Vector3f::Zero(), kvs::Vector3f::Zero() );
//    BaseClass::setMinMaxExternalCoords( kvs::Vector3f::Zero(), kvs::Vector3f::Zero() );
    m_nrows = 0;
    m_ncolumns = 0;
}

/*===========================================================================*/
/**
 *  @brief  Shallow copys.
 *  @param  other [in] table object
 */
/*===========================================================================*/
void TableObject::shallowCopy( const TableObject& other )
{
    BaseClass::operator=( other );
    this->m_nrows = other.numberOfRows();
    this->m_ncolumns = other.numberOfColumns();
    this->m_labels = other.labelList();
    this->m_columns = other.columnList();
    this->m_min_values = other.minValueList();
    this->m_max_values = other.maxValueList();
    this->m_min_ranges = other.minRangeList();
    this->m_max_ranges = other.maxRangeList();
    this->m_inside_range_list = other.insideRangeList();
}

/*===========================================================================*/
/**
 *  @brief  Deep copys.
 *  @param  other [in] table object
 */
/*===========================================================================*/
void TableObject::deepCopy( const TableObject& other )
{
    { m_labels.clear(); LabelList().swap( m_labels ); }
    { m_columns.clear(); ColumnList().swap( m_columns ); }
    { m_min_values.clear(); ValueList().swap( m_min_values ); }
    { m_max_values.clear(); ValueList().swap( m_max_values ); }
    { m_min_ranges.clear(); ValueList().swap( m_min_ranges ); }
    { m_max_ranges.clear(); ValueList().swap( m_max_ranges ); }
    { m_inside_range_list.clear(); RangeList().swap( m_inside_range_list ); }

    BaseClass::operator=( other );
    this->m_nrows = other.numberOfRows();
    this->m_ncolumns = other.numberOfColumns();
    for ( size_t i = 0; i < m_labels.size(); i++ ) this->m_labels.push_back( other.label(i) );
    for ( size_t i = 0; i < m_columns.size(); i++ ) this->m_columns.push_back( other.column(i).clone() );
    for ( size_t i = 0; i < m_min_values.size(); i++ ) this->m_min_values.push_back( other.minValue(i) );
    for ( size_t i = 0; i < m_max_values.size(); i++ ) this->m_max_values.push_back( other.maxValue(i) );
    for ( size_t i = 0; i < m_min_ranges.size(); i++ ) this->m_min_ranges.push_back( other.minRange(i) );
    for ( size_t i = 0; i < m_max_ranges.size(); i++ ) this->m_max_ranges.push_back( other.maxRange(i) );
    for ( size_t i = 0; i < m_inside_range_list.size(); i++ ) this->m_inside_range_list.push_back( other.insideRange(i) );
}

/*===========================================================================*/
/**
 *  @brief  Prints information of the table object.
 *  @param  os [in] output stream
 *  @param  indent [in] indent
 */
/*===========================================================================*/
void TableObject::print( std::ostream& os, const kvs::Indent& indent ) const
{
    os << indent << "Object type : " << "table object" << std::endl;
    os << indent << "Number of columns : " << this->numberOfColumns() << std::endl;
    os << indent << "Number of rows : " << this->numberOfRows() << std::endl;
    os << indent << "Labels for each column : ";
    for ( size_t i = 0; i < this->labelList().size(); i++ ) os << "\"" << this->labelList()[i] << "\", "; os << std::endl;
    os << indent << "Min. values for each column : ";
    for ( size_t i = 0; i < this->minValueList().size(); i++ ) os << this->minValueList()[i] << ", "; os << std::endl;
    os << indent << "Max. values for each column : ";
    for ( size_t i = 0; i < this->maxValueList().size(); i++ ) os << this->maxValueList()[i] << ", "; os << std::endl;
    os << indent << "Min. ranges for each column : ";
    for ( size_t i = 0; i < this->minRangeList().size(); i++ ) os << this->minRangeList()[i] << ", "; os << std::endl;
    os << indent << "Max. ranges for each column : ";
    for ( size_t i = 0; i < this->maxRangeList().size(); i++ ) os << this->maxRangeList()[i] << ", "; os << std::endl;
}

/*===========================================================================*/
/**
 *  @brief  Adds a column.
 *  @param  array [in] column array
 *  @param  label [in] column label
 */
/*===========================================================================*/
void TableObject::addColumn( const kvs::AnyValueArray& array, const std::string& label )
{
    m_ncolumns++;
    m_nrows = kvs::Math::Max( m_nrows, array.size() );

    m_columns.push_back( array );
    m_labels.push_back( label );

    kvs::Real64 min_value = kvs::Value<kvs::Real64>::Max();
    kvs::Real64 max_value = kvs::Value<kvs::Real64>::Min();
    const std::type_info& type = array.typeInfo()->type();
    if ( type == typeid( kvs::Int8 ) )
    {
        const kvs::Int8* value = static_cast<const kvs::Int8*>( array.data() );
        for( size_t i = 0; i < array.size(); i++ )
        {
            min_value = kvs::Math::Min( min_value, kvs::Real64( value[i] ) );
            max_value = kvs::Math::Max( max_value, kvs::Real64( value[i] ) );
        }
    }
    else if ( type == typeid( kvs::UInt8 ) )
    {
        const kvs::UInt8* value = static_cast<const kvs::UInt8*>( array.data() );
        for( size_t i = 0; i < array.size(); i++ )
        {
            min_value = kvs::Math::Min( min_value, kvs::Real64( value[i] ) );
            max_value = kvs::Math::Max( max_value, kvs::Real64( value[i] ) );
        }
    }
    else if ( type == typeid( kvs::Int16 ) )
    {
        const kvs::Int16* value = static_cast<const kvs::Int16*>( array.data() );
        for( size_t i = 0; i < array.size(); i++ )
        {
            min_value = kvs::Math::Min( min_value, kvs::Real64( value[i] ) );
            max_value = kvs::Math::Max( max_value, kvs::Real64( value[i] ) );
        }
    }
    else if ( type == typeid( kvs::UInt16 ) )
    {
        const kvs::UInt16* value = static_cast<const kvs::UInt16*>( array.data() );
        for( size_t i = 0; i < array.size(); i++ )
        {
            min_value = kvs::Math::Min( min_value, kvs::Real64( value[i] ) );
            max_value = kvs::Math::Max( max_value, kvs::Real64( value[i] ) );
        }
    }
    else if ( type == typeid( kvs::Int32 ) )
    {
        const kvs::Int32* value = static_cast<const kvs::Int32*>( array.data() );
        for( size_t i = 0; i < array.size(); i++ )
        {
            min_value = kvs::Math::Min( min_value, kvs::Real64( value[i] ) );
            max_value = kvs::Math::Max( max_value, kvs::Real64( value[i] ) );
        }
    }
    else if ( type == typeid( kvs::UInt32 ) )
    {
        const kvs::UInt32* value = static_cast<const kvs::UInt32*>( array.data() );
        for( size_t i = 0; i < array.size(); i++ )
        {
            min_value = kvs::Math::Min( min_value, kvs::Real64( value[i] ) );
            max_value = kvs::Math::Max( max_value, kvs::Real64( value[i] ) );
        }
    }
    else if ( type == typeid( kvs::Int64 ) )
    {
        const kvs::Int64* value = static_cast<const kvs::Int64*>( array.data() );
        for( size_t i = 0; i < array.size(); i++ )
        {
            min_value = kvs::Math::Min( min_value, kvs::Real64( value[i] ) );
            max_value = kvs::Math::Max( max_value, kvs::Real64( value[i] ) );
        }
    }
    else if ( type == typeid( kvs::UInt64 ) )
    {
        const kvs::UInt64* value = static_cast<const kvs::UInt64*>( array.data() );
        for( size_t i = 0; i < array.size(); i++ )
        {
            min_value = kvs::Math::Min( min_value, kvs::Real64( value[i] ) );
            max_value = kvs::Math::Max( max_value, kvs::Real64( value[i] ) );
        }
    }
    else if ( type == typeid( kvs::Real32 ) )
    {
        const kvs::Real32* value = static_cast<const kvs::Real32*>( array.data() );
        for( size_t i = 0; i < array.size(); i++ )
        {
            min_value = kvs::Math::Min( min_value, kvs::Real64( value[i] ) );
            max_value = kvs::Math::Max( max_value, kvs::Real64( value[i] ) );
        }
    }
    else if ( type == typeid( kvs::Real64 ) )
    {
        const kvs::Real64* value = static_cast<const kvs::Real64*>( array.data() );
        for( size_t i = 0; i < array.size(); i++ )
        {
            min_value = kvs::Math::Min( min_value, kvs::Real64( value[i] ) );
            max_value = kvs::Math::Max( max_value, kvs::Real64( value[i] ) );
        }
    }
    else if ( type == typeid( std::string ) )
    {
        min_value = 0.0;
        max_value = 0.0;
    }

    m_min_values.push_back( min_value );
    m_max_values.push_back( max_value );
    m_min_ranges.push_back( min_value );
    m_max_ranges.push_back( max_value );

    m_inside_range_list.resize( m_nrows, 1 );
}

/*===========================================================================*/
/**
 *  @brief  Returns number of columns.
 *  @return number of columns
 */
/*===========================================================================*/
size_t TableObject::numberOfColumns() const
{
    return m_ncolumns;
}

/*===========================================================================*/
/**
 *  @brief  Returns number of rows.
 *  @return number of rows
 */
/*===========================================================================*/
size_t TableObject::numberOfRows() const
{
    return m_nrows;
}

/*===========================================================================*/
/**
 *  @brief  Returns label list.
 *  @return label list
 */
/*===========================================================================*/
const TableObject::LabelList TableObject::labelList() const
{
    return m_labels;
}

/*===========================================================================*/
/**
 *  @brief  Returns label of the column specified by the index.
 *  @param  index [in] column index
 *  @return label
 */
/*===========================================================================*/
const std::string TableObject::label( const size_t index ) const
{
    return m_labels[index];
}

/*===========================================================================*/
/**
 *  @brief  Returns column list.
 *  @return column list
 */
/*===========================================================================*/
const TableObject::ColumnList TableObject::columnList() const
{
    return m_columns;
}

/*===========================================================================*/
/**
 *  @brief  Returns column array specified by the index.
 *  @param  index [in] column index
 *  @return column array
 */
/*===========================================================================*/
const kvs::AnyValueArray& TableObject::column( const size_t index ) const
{
    return m_columns[index];
}

/*===========================================================================*/
/**
 *  @brief  Returns minimum value list.
 *  @return minimum value list
 */
/*===========================================================================*/
const TableObject::ValueList TableObject::minValueList() const
{
    return m_min_values;
}

/*===========================================================================*/
/**
 *  @brief  Returns minimum value of the column specified by the index.
 *  @param  index [in] column index
 *  @return minimum value
 */
/*===========================================================================*/
kvs::Real64 TableObject::minValue( const size_t index ) const
{
    return m_min_values[index];
}

/*===========================================================================*/
/**
 *  @brief  Returns maximum value list.
 *  @return maximum value list
 */
/*===========================================================================*/
const TableObject::ValueList TableObject::maxValueList() const
{
    return m_max_values;
}

/*===========================================================================*/
/**
 *  @brief  Returns maximum value of the column specified by the index.
 *  @param  index [in] column index
 *  @return maximum value
 */
/*===========================================================================*/
kvs::Real64 TableObject::maxValue( const size_t index ) const
{
    return m_max_values[index];
}

/*===========================================================================*/
/**
 *  @brief  Sets minimum value to the specified column.
 *  @param  column_index [in] column index
 *  @param  value [in] minimum value
 */
/*===========================================================================*/
void TableObject::setMinValue( const size_t column_index, const kvs::Real64 value )
{
    if ( value > m_min_ranges[column_index] ) { this->setMinRange( column_index, value ); }
    m_min_values[column_index] = value;
}

/*===========================================================================*/
/**
 *  @brief  Sets maximum value to the specified column.
 *  @param  column_index [in] column index
 *  @param  value [in] maximum value
 */
/*===========================================================================*/
void TableObject::setMaxValue( const size_t column_index, const kvs::Real64 value )
{
    if ( value < m_max_ranges[column_index] ) { this->setMaxRange( column_index, value ); }
    m_max_values[column_index] = value;
}

/*===========================================================================*/
/**
 *  @brief  Sets minimum range value to the specified column.
 *  @param  column_index [in] column index
 *  @param  range [in] range value
 */
/*===========================================================================*/
void TableObject::setMinRange( const size_t column_index, const kvs::Real64 range )
{
    const kvs::Real64 min_value = this->minValue(column_index);
    const kvs::Real64 max_range = m_max_ranges[column_index];

    const kvs::Real64 min_range_old = m_min_ranges[column_index];
    const kvs::Real64 min_range_new = kvs::Math::Clamp( range, min_value, max_range );

    if ( kvs::Math::Equal( min_range_old, min_range_new ) ) return;
    m_min_ranges[column_index] = min_range_new;

    const size_t nrows = this->numberOfRows();
    const size_t ncolumns = this->numberOfColumns();
    if ( min_range_new > min_range_old )
    {
        /* In case of flags turned off, you just have to check whether the value
         * in the specified column is included in the range.
         *
         *  (before) |xxx+oooooooo*xxxxxx|  o: on, x: off, +: min_range, *: max_range
         *  (after)  |xxxAxxxxBooo*xxxxxx|  A: min_range_old, B: min_range_new
         */
        const kvs::AnyValueArray& column = this->column( column_index );
        for ( size_t i = 0; i < nrows; i++ )
        {
            const kvs::Real64 value = column[i].to<kvs::Real64>();
            if (  min_range_old <= value && value <= min_range_new )
            {
                m_inside_range_list[i] = 0;
            }
        }
    }
    else
    {
        /* In case of flags turned on, you have to check the all of colums.
         *
         *  (before) |xxxxxxxx+ooo*xxxxxx|  o: on, x: off, +: min_range, *: max_range
         *  (after)  |xxxAooooBooo*xxxxxx|  A: min_range, B: min_range_old
         */
        for ( size_t i = 0; i < nrows; i++ )
        {
            m_inside_range_list[i] = 1;
            for ( size_t j = 0; j < ncolumns; j++ )
            {
                const kvs::AnyValueArray& column = this->column( j );
                const kvs::Real64 value = column[i].to<kvs::Real64>();
                if (  !( m_min_ranges[j] <= value && value <= m_max_ranges[j] ) )
                {
                    m_inside_range_list[i] = 0;
                    break;
                }
            }
        }
    }
}

/*===========================================================================*/
/**
 *  @brief  Sets maximum range value to the specified column.
 *  @param  column_index [in] column index
 *  @param  range [in] range value
 */
/*===========================================================================*/
void TableObject::setMaxRange( const size_t column_index, const kvs::Real64 range )
{
    const kvs::Real64 min_range = m_min_ranges[column_index];
    const kvs::Real64 max_value = this->maxValue(column_index);

    const kvs::Real64 max_range_old = m_max_ranges[column_index];
    const kvs::Real64 max_range_new = kvs::Math::Clamp( range, min_range, max_value );

    if ( kvs::Math::Equal( max_range_old, max_range_new ) ) return;
    m_max_ranges[column_index] = max_range_new;

    const size_t nrows = this->numberOfRows();
    const size_t ncolumns = this->numberOfColumns();
    if ( max_range_new > max_range_old )
    {
        /* In case of flags turned on, you have to check the all of colums.
         *
         *  (before) |xxx*oooooooo+xxxxxx|  o: on, x: off, *: min_range, +: max_range
         *  (after)  |xxx*ooooooooAoooBxx|  A: max_range_old, B: max_range_new
         */
        for ( size_t i = 0; i < nrows; i++ )
        {
            m_inside_range_list[i] = 1;
            for ( size_t j = 0; j < ncolumns; j++ )
            {
                const kvs::AnyValueArray& column = this->column( j );
                const kvs::Real64 value = column[i].to<kvs::Real64>();
                if (  !( m_min_ranges[j] <= value && value <= m_max_ranges[j] ) )
                {
                    m_inside_range_list[i] = 0;
                    break;
                }
            }
        }
    }
    else
    {
        /* In case of flags turned off, you just have to check whether the value
         * in the specified column is included in the range.
         *
         *  (before) |xxx*oooooooo+xxxxxx|  o: on, x: off, *: min_range, +: max_range
         *  (after)  |xxx*ooooBxxxAxxxxxx|  A: max_range_old, B: max_range_new
         */
        const kvs::AnyValueArray& column = this->column( column_index );
        for ( size_t i = 0; i < nrows; i++ )
        {
            const kvs::Real64 value = column[i].to<kvs::Real64>();
            if (  max_range_new <= value && value <= max_range_old )
            {
                m_inside_range_list[i] = 0;
            }
        }
    }
}

/*===========================================================================*/
/**
 *  @brief  Sets minimum and maximum range values to the specified column.
 *  @param  column_index [in] column index
 *  @param  min_range [in] minimum range value
 *  @param  max_range [in] maximum range value
 */
/*===========================================================================*/
void TableObject::setRange( const size_t column_index, const kvs::Real64 min_range, const kvs::Real64 max_range )
{
    this->setMinRange( column_index, min_range );
    this->setMaxRange( column_index, max_range );
}

/*===========================================================================*/
/**
 *  @brief  Moves minimum range value to the specified column.
 *  @param  column_index [in] column index
 *  @param  drange [in] distance of range value
 */
/*===========================================================================*/
void TableObject::moveMinRange( const size_t column_index, const kvs::Real64 drange )
{
    const kvs::Real64 min_range = this->minRange( column_index );
    this->setMinRange( column_index, min_range + drange );
}

/*===========================================================================*/
/**
 *  @brief  Moves maximum range value to the specified column.
 *  @param  column_index [in] column index
 *  @param  drange [in] distance of range value
 */
/*===========================================================================*/
void TableObject::moveMaxRange( const size_t column_index, const kvs::Real64 drange )
{
    const kvs::Real64 max_range = this->maxRange( column_index );
    this->setMaxRange( column_index, max_range + drange );
}

/*===========================================================================*/
/**
 *  @brief  Moves maximum range value to the specified column.
 *  @param  column_index [in] column index
 *  @param  drange [in] distance of range value
 */
/*===========================================================================*/
void TableObject::moveRange( const size_t column_index, const kvs::Real64 drange )
{
    const kvs::Real64 min_range = this->minRange( column_index );
    const kvs::Real64 max_range = this->maxRange( column_index );
    const kvs::Real64 min_value = this->minValue( column_index );
    const kvs::Real64 max_value = this->maxValue( column_index );
    const kvs::Real64 range_width = max_range - min_range;

    if ( max_range + drange > max_value )
    {
        this->setMinRange( column_index, max_value - range_width );
        this->setMaxRange( column_index, max_value );
    }
    else if ( min_range + drange < min_value )
    {
        this->setMinRange( column_index, min_value );
        this->setMaxRange( column_index, min_value + range_width );
    }
    else
    {
        this->setMinRange( column_index, min_range + drange );
        this->setMaxRange( column_index, max_range + drange );
    }
}

/*===========================================================================*/
/**
 *  @brief  Resets range specified by column_index.
 *  @param  column_index [in] column index
 */
/*===========================================================================*/
void TableObject::resetRange( const size_t column_index )
{
    this->setMinRange( column_index, this->minValue(column_index) );
    this->setMaxRange( column_index, this->maxValue(column_index) );
}

/*===========================================================================*/
/**
 *  @brief  Resets ranges.
 */
/*===========================================================================*/
void TableObject::resetRange()
{
    const size_t ncolumns = this->numberOfColumns();
    for ( size_t i = 0; i < ncolumns; i++ )
    {
        m_max_ranges[i] = this->maxValue(i);
        m_min_ranges[i] = this->minValue(i);
    }

    std::fill( m_inside_range_list.begin(), m_inside_range_list.end(), 1 );
}

/*===========================================================================*/
/**
 *  @brief  Returns minimum range list.
 *  @return minimum range list
 */
/*===========================================================================*/
const kvs::TableObject::ValueList& TableObject::minRangeList() const
{
    return m_min_ranges;
}

/*===========================================================================*/
/**
 *  @brief  Returns maximum range list.
 *  @return maximum range list
 */
/*===========================================================================*/
const kvs::TableObject::ValueList& TableObject::maxRangeList() const
{
    return m_max_ranges;
}

/*===========================================================================*/
/**
 *  @brief  Returns inside range list.
 *  @return inside range list
 */
/*===========================================================================*/
const kvs::TableObject::RangeList& TableObject::insideRangeList() const
{
    return m_inside_range_list;
}

/*===========================================================================*/
/**
 *  @brief  Returns minimum range value of the column specified by the index.
 *  @param  column_index [in] column index
 *  @return minimum range value
 */
/*===========================================================================*/
kvs::Real64 TableObject::minRange( const size_t column_index ) const
{
    return m_min_ranges[column_index];
}

/*===========================================================================*/
/**
 *  @brief  Returns maximum range value of the column specified by the index.
 *  @param  column_index [in] column index
 *  @return maximum range value
 */
/*===========================================================================*/
kvs::Real64 TableObject::maxRange( const size_t column_index ) const
{
    return m_max_ranges[column_index];
}

/*===========================================================================*/
/**
 *  @brief  Returns true if the value of the row specified by the index is inside the range.
 *  @param  row_index [in] row index
 *  @return true, if the value is inside the range
 */
/*===========================================================================*/
bool TableObject::insideRange( const size_t row_index ) const
{
    return m_inside_range_list[row_index] == 1;
}

/*===========================================================================*/
/**
 *  @brief  Returns object type.
 *  @return object type
 */
/*===========================================================================*/
kvs::ObjectBase::ObjectType TableObject::objectType() const
{
    return kvs::ObjectBase::Table;
}

template<> void TableObject::addColumn<kvs::Int8>( const kvs::ValueArray<kvs::Int8>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::UInt8>( const kvs::ValueArray<kvs::UInt8>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::Int16>( const kvs::ValueArray<kvs::Int16>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::UInt16>( const kvs::ValueArray<kvs::UInt16>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::Int32>( const kvs::ValueArray<kvs::Int32>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::UInt32>( const kvs::ValueArray<kvs::UInt32>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::Int64>( const kvs::ValueArray<kvs::Int64>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::UInt64>( const kvs::ValueArray<kvs::UInt64>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::Real32>( const kvs::ValueArray<kvs::Real32>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::Real64>( const kvs::ValueArray<kvs::Real64>& array, const std::string& label );
template<> void TableObject::addColumn<std::string>( const kvs::ValueArray<std::string>& array, const std::string& label );

template<> void TableObject::addColumn<kvs::Int8>( const std::vector<kvs::Int8>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::UInt8>( const std::vector<kvs::UInt8>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::Int16>( const std::vector<kvs::Int16>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::UInt16>( const std::vector<kvs::UInt16>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::Int32>( const std::vector<kvs::Int32>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::UInt32>( const std::vector<kvs::UInt32>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::Int64>( const std::vector<kvs::Int64>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::UInt64>( const std::vector<kvs::UInt64>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::Real32>( const std::vector<kvs::Real32>& array, const std::string& label );
template<> void TableObject::addColumn<kvs::Real64>( const std::vector<kvs::Real64>& array, const std::string& label );
template<> void TableObject::addColumn<std::string>( const std::vector<std::string>& array, const std::string& label );

template<> const kvs::Int8& TableObject::at<kvs::Int8>( const size_t row, const size_t column ) const;
template<> const kvs::UInt8& TableObject::at<kvs::UInt8>( const size_t row, const size_t column ) const;
template<> const kvs::Int16& TableObject::at<kvs::Int16>( const size_t row, const size_t column ) const;
template<> const kvs::UInt16& TableObject::at<kvs::UInt16>( const size_t row, const size_t column ) const;
template<> const kvs::Int32& TableObject::at<kvs::Int32>( const size_t row, const size_t column ) const;
template<> const kvs::UInt32& TableObject::at<kvs::UInt32>( const size_t row, const size_t column ) const;
template<> const kvs::Int64& TableObject::at<kvs::Int64>( const size_t row, const size_t column ) const;
template<> const kvs::UInt64& TableObject::at<kvs::UInt64>( const size_t row, const size_t column ) const;
template<> const kvs::Real32& TableObject::at<kvs::Real32>( const size_t row, const size_t column ) const;
template<> const kvs::Real64& TableObject::at<kvs::Real64>( const size_t row, const size_t column ) const;
template<> const std::string& TableObject::at<std::string>( const size_t row, const size_t column ) const;

} // end of namespace kvs
