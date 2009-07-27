/****************************************************************************/
/**
 *  @file FrequencyTable.cpp
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
#include "FrequencyTable.h"
#include <kvs/Type>
#include <kvs/Value>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
FrequencyTable::FrequencyTable( void ):
    m_min_range( 0 ),
    m_max_range( 0 ),
    m_max_count( 0 ),
    m_nbins( 0 )
{
}

FrequencyTable::~FrequencyTable( void )
{
}

/*==========================================================================*/
/**
 *  Returns the min. range.
 *  @return min. range
 */
/*==========================================================================*/
const kvs::Real64 FrequencyTable::minRange( void ) const
{
    return( m_min_range );
}

/*==========================================================================*/
/**
 *  Returns the max. range.
 *  @return max. range
 */
/*==========================================================================*/
const kvs::Real64 FrequencyTable::maxRange( void ) const
{
    return( m_max_range );
}

/*==========================================================================*/
/**
 *  Returns the max. counts of the bins.
 *  @return max. counts
 */
/*==========================================================================*/
const size_t FrequencyTable::maxCount( void ) const
{
    return( m_max_count );
}

/*==========================================================================*/
/**
 *  Returns the number of bins.
 *  @return number of bins
 */
/*==========================================================================*/
const kvs::UInt64 FrequencyTable::nbins( void ) const
{
    return( m_nbins );
}

/*==========================================================================*/
/**
 *  Returns the bin.
 *  @return bin
 */
/*==========================================================================*/
const kvs::ValueArray<size_t>& FrequencyTable::bin( void ) const
{
    return( m_bin );
}

/*==========================================================================*/
/**
 *  Set the ignore value.
 */
/*==========================================================================*/
void FrequencyTable::setIgnoreValue( const kvs::Real64 value )
{
    m_ignore_values.push_back( value );
}

/*==========================================================================*/
/**
 *  Create a frequency distribution table for a structured volume object.
 *  @param volume [in] pointer to the structured volume object
 */
/*==========================================================================*/
void FrequencyTable::create( const kvs::StructuredVolumeObject* volume )
{
    // Calculate the min/max range value and the number of bins.
    this->calculate_range( volume );

    // Allocate and initialize the bin array.
    m_bin.allocate( static_cast<size_t>( m_nbins ) );
    m_bin.fill( 0x00 );

    // Count the bin.
    this->count_bin( volume );
}

/*==========================================================================*/
/**
 *  Create a frequency distribution table for a image object.
 *  @param image [in] pointer to the image object
 *  @param channel [in] color element channel (0, 1, 2, 3)
 */
/*==========================================================================*/
void FrequencyTable::create( const kvs::ImageObject* image, const size_t channel )
{
    // Calculate the min/max range value and the number of bins.
    this->calculate_range( image );

    // Allocate and initialize the bin array.
    m_bin.allocate( static_cast<size_t>( m_nbins ) );
    m_bin.fill( 0x00 );

    // Count the bin.
    this->count_bin( image, channel );
}

/*==========================================================================*/
/**
 *  Returns counts of the bin which is specified by the index.
 *  @param index [in] index
 *  @return counts
 */
/*==========================================================================*/
const kvs::UInt64 FrequencyTable::operator [] ( const size_t index ) const
{
    return( m_bin[ index ] );
}

/*==========================================================================*/
/**
 *  Returns counts of the bin which is specified by the index.
 *  @param index [in] index
 *  @return counts
 */
/*==========================================================================*/
const kvs::UInt64 FrequencyTable::at( const size_t index ) const
{
    return( m_bin.at( index ) );
}

/*==========================================================================*/
/**
 *  Calculate the bin range.
 *  @param volume [in] pointer to the structured volume object
 */
/*==========================================================================*/
void FrequencyTable::calculate_range( const kvs::StructuredVolumeObject* volume )
{
    const std::type_info& type = volume->values().typeInfo()->type();
    if (      type == typeid( kvs::Int8   ) )
    {
        m_min_range = kvs::Value<kvs::Int8>::Min();
        m_max_range = kvs::Value<kvs::Int8>::Max();
        m_nbins     = kvs::UInt64(1) << 8;
    }
    else if ( type == typeid( kvs::UInt8  ) )
    {
        m_min_range = kvs::Value<kvs::UInt8>::Min();
        m_max_range = kvs::Value<kvs::UInt8>::Max();
        m_nbins     = kvs::UInt64(1) << 8;
    }
    else if ( type == typeid( kvs::Int16  ) )
    {
        m_min_range = kvs::Value<kvs::Int16>::Min();
        m_max_range = kvs::Value<kvs::Int16>::Max();
        m_nbins     = kvs::UInt64(1) << 16;
    }
    else if ( type == typeid( kvs::UInt16 ) )
    {
        m_min_range = kvs::Value<kvs::UInt16>::Min();
        m_max_range = kvs::Value<kvs::UInt16>::Max();
        m_nbins     = kvs::UInt64(1) << 16;
    }
    else if ( type == typeid( kvs::Int32  ) )
    {
        m_min_range = kvs::Value<kvs::Int32>::Min();
        m_max_range = kvs::Value<kvs::Int32>::Max();
        m_nbins     = kvs::UInt64(1) << 32;
    }
    else if ( type == typeid( kvs::UInt32 ) )
    {
        m_min_range = kvs::Value<kvs::UInt32>::Min();
        m_max_range = kvs::Value<kvs::UInt32>::Max();
        m_nbins     = kvs::UInt64(1) << 32;
    }
/*
    else if ( type == typeid( kvs::Int64  ) || type == typeid( kvs::UInt64 ) )
    {
        m_min_range = kvs::Value<kvs::UInt64>::Min();
        m_max_range = kvs::Value<kvs::UInt64>::Max();
        m_nbins = kvs::UInt64(1) << 64;
    }
*/
    else if ( type == typeid( kvs::Real32 ) || type == typeid( kvs::Real64 ) )
    {
        m_min_range = volume->minValue();
        m_max_range = volume->maxValue();
        // It is neccessary to estimate the number of bins by binning process.
        m_nbins = 100;
    }
}

/*==========================================================================*/
/**
 *  Calculate a bin range.
 *  @param image [in] pointer to the image object
 */
/*==========================================================================*/
void FrequencyTable::calculate_range( const kvs::ImageObject* image )
{
    switch ( image->type() )
    {
    case kvs::ImageObject::Gray8:
    case kvs::ImageObject::Color24: // RGB
    case kvs::ImageObject::Color32: // RGBA
    {
        m_min_range = kvs::Value<kvs::UInt8>::Min();
        m_max_range = kvs::Value<kvs::UInt8>::Max();
        m_nbins     = kvs::UInt64(1) << 8;
        break;
    }
    case kvs::ImageObject::Gray16:
    {
        m_min_range = kvs::Value<kvs::UInt16>::Min();
        m_max_range = kvs::Value<kvs::UInt16>::Max();
        m_nbins     = kvs::UInt64(1) << 16;
        break;
    }
    default: break;
    }
}

/*==========================================================================*/
/**
 *  Count the bin.
 *  @param volume [in] pointer to the structured volume object
 */
/*==========================================================================*/
void FrequencyTable::count_bin( const kvs::StructuredVolumeObject* volume )
{
    const std::type_info& type = volume->values().typeInfo()->type();
    if (      type == typeid( kvs::Int8 )   ) this->binning<kvs::Int8>( volume );
    else if ( type == typeid( kvs::UInt8 )  ) this->binning<kvs::UInt8>( volume );
    else if ( type == typeid( kvs::Int16 )  ) this->binning<kvs::Int16>( volume );
    else if ( type == typeid( kvs::UInt16 ) ) this->binning<kvs::UInt16>( volume );
    else if ( type == typeid( kvs::Int32 )  ) this->binning<kvs::Int32>( volume );
    else if ( type == typeid( kvs::UInt32 ) ) this->binning<kvs::UInt32>( volume );
    else if ( type == typeid( kvs::Real32 ) ) this->binning<kvs::Real32>( volume );
    else if ( type == typeid( kvs::Real64 ) ) this->binning<kvs::Real64>( volume );
}

/*==========================================================================*/
/**
 *  Count the bin.
 *  @param image [in] pointer to the image object
 *  @param channel [in] color element channel (0, 1, 2, 3)
 */
/*==========================================================================*/
void FrequencyTable::count_bin( const kvs::ImageObject* image, const size_t channel )
{
    switch ( image->type() )
    {
    case kvs::ImageObject::Gray8:
    case kvs::ImageObject::Color24: // RGB
    case kvs::ImageObject::Color32: // RGBA
        this->binning<kvs::UInt8>( image, channel );
        break;
    case kvs::ImageObject::Gray16:
        this->binning<kvs::UInt16>( image, channel );
        break;
    default: break;
    }
}

/*==========================================================================*/
/**
 *  Test which a value is the ignore value or not.
 *  @param value [in] value
 *  @return true, if the value is the ignore value.
 */
/*==========================================================================*/
bool FrequencyTable::is_ignore_value( const kvs::Real64 value )
{
    std::list<kvs::Real64>::const_iterator ignore_value = m_ignore_values.begin();
    std::list<kvs::Real64>::const_iterator end = m_ignore_values.end();
    while ( ignore_value != end )
    {
        if ( kvs::Math::Equal( value, *ignore_value ) ) return( true );

        ++ignore_value;
    }

    return( false );
}

} // end of namespace kvs
