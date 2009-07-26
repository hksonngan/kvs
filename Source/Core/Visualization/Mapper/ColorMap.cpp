/****************************************************************************/
/**
 *  @file ColorMap.cpp
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
#include "ColorMap.h"

#include <kvs/Assert>
#include <kvs/RGBColor>
#include <kvs/HSVColor>


namespace
{

const size_t NumberOfChannels = 3;

}

namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
ColorMap::ColorMap( void )
    : m_points()
    , m_table()
{
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param resolution [in] resolution
 */
/*==========================================================================*/
ColorMap::ColorMap( const size_t resolution )
    : m_points()
    , m_table()
{
    this->create( resolution );
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param table [in] opacity value table
 */
/*==========================================================================*/
ColorMap::ColorMap( const ColorMap::Table& table )
    : m_points()
    , m_table( table )
{
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param color_map [in] color map
 */
/*==========================================================================*/
ColorMap::ColorMap( const ColorMap& other )
    : m_points( other.m_points )
    , m_table( other.m_table )
{
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
ColorMap::~ColorMap( void )
{
}

/*==========================================================================*/
/**
 *  Returns the resolution of the color map.
 *  @return resolusion
 */
/*==========================================================================*/
const size_t ColorMap::resolution( void ) const
{
    return( m_table.size() / ::NumberOfChannels );
}

/*==========================================================================*/
/**
 *  Returns the color map table.
 *  @return color map table
 */
/*==========================================================================*/
const ColorMap::Table& ColorMap::table( void ) const
{
    return( m_table );
}

/*==========================================================================*/
/**
 *  Creates the color map.
 *  @param resolution [in] resolution of the color map
 */
/*==========================================================================*/
void ColorMap::create( const size_t resolution )
{
    m_points.clear();
    m_table.allocate( ::NumberOfChannels * resolution );

    const float min_hue = 0.0f;   // blue
    const float max_hue = 240.0f; // red

    const float increment = ( max_hue - min_hue ) / static_cast<float>( resolution - 1 );

    kvs::UInt8* color = m_table.pointer();

    for ( size_t i = 0; i < resolution; ++i )
    {
        // HSV to RGB
        const kvs::HSVColor hsv(
            ( max_hue - increment * static_cast<float>( i ) ) / 360.0f,
            1.0f,
            1.0f );
        const kvs::RGBColor rgb( hsv );

        *( color++ ) = rgb.red();
        *( color++ ) = rgb.green();
        *( color++ ) = rgb.blue();
    }
}

/*==========================================================================*/
/**
 *  Access operator [].
 *  @param index [in] index of the color map.
 *  @retval RGB color value
 */
/*==========================================================================*/
const kvs::RGBColor ColorMap::operator []( const size_t index ) const
{
    KVS_ASSERT( index < this->resolution() );

    const size_t offset = ::NumberOfChannels * index;
    return( kvs::RGBColor( m_table.pointer() + offset ) );
}

/*===========================================================================*/
/**
 *  @brief  Returns interpolated RGB color value by assuming piecewise linear map.
 *  @param  index [in] index of the color map as a floating point number
 *  @return interpolated RGB color value
 */
/*===========================================================================*/
const kvs::RGBColor ColorMap::at( const float index ) const
{
    KVS_ASSERT( 0.0f <= index && index <= static_cast<float>(this->resolution()-1) );

    const size_t s0 = static_cast<size_t>( index );
    const size_t s1 = s0 + 1;

    const kvs::RGBColor c0( m_table.pointer() + ::NumberOfChannels * s0 );
    const kvs::RGBColor c1( m_table.pointer() + ::NumberOfChannels * s1 );

    const kvs::UInt8 r = static_cast<kvs::UInt8>( ( c1.r() - c0.r() ) * index + c0.r() * s1 - c1.r() * s0 );
    const kvs::UInt8 g = static_cast<kvs::UInt8>( ( c1.g() - c0.g() ) * index + c0.g() * s1 - c1.g() * s0 );
    const kvs::UInt8 b = static_cast<kvs::UInt8>( ( c1.b() - c0.b() ) * index + c0.b() * s1 - c1.b() * s0 );

    return( kvs::RGBColor( r, g, b ) );
}

/*==========================================================================*/
/**
 *  Substitution operator =.
 *  @param opacity_map [in] color map
 *  @retval opacity map
 */
/*==========================================================================*/
ColorMap& ColorMap::operator =( const ColorMap& rhs )
{
    m_points = rhs.m_points;
    m_table  = rhs.m_table;

    return( *this );
}

} // end of namespace kvs
