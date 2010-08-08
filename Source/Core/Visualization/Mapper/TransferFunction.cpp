/****************************************************************************/
/**
 *  @file TransferFunction.cpp
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
#include "TransferFunction.h"

#include <kvs/Assert>
#include <kvs/KVSMLTransferFunction>


namespace { const size_t DefaultResolution = 256; }

namespace kvs
{

/*==========================================================================*/
/**
 *  @brief  Constructs a new TransferFunction.
 *  @param  resolution [in] Resolution.
 */
/*==========================================================================*/
TransferFunction::TransferFunction( const size_t resolution )
    : m_color_map( resolution )
    , m_opacity_map( resolution )
{
    m_color_map.create();
    m_opacity_map.create();
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new TransferFunction.
 *  @param  filename [in] filename
 */
/*===========================================================================*/
TransferFunction::TransferFunction( const std::string& filename )
{
    this->read( filename );
}

/*==========================================================================*/
/**
 *  @brief  Constructs a new TransferFunction.
 *  @param  color_map [in] Color map.
 */
/*==========================================================================*/
TransferFunction::TransferFunction( const kvs::ColorMap& color_map )
    : m_color_map( color_map )
    , m_opacity_map( color_map.resolution() )
{
}

/*==========================================================================*/
/**
 *  @brief  Constructs a new TransferFunction.
 *  @param  opacity_map [in] Opacity map.
 */
/*==========================================================================*/
TransferFunction::TransferFunction( const kvs::OpacityMap& opacity_map )
    : m_color_map( opacity_map.resolution() )
    , m_opacity_map( opacity_map )
{
}

/*==========================================================================*/
/**
 *  @brief  Constructs a new TransferFunction.
 *  @param  color_map [in] Color map.
 *  @param  opacity_map [in] Opacity map.
 */
/*==========================================================================*/
TransferFunction::TransferFunction(
    const kvs::ColorMap&   color_map,
    const kvs::OpacityMap& opacity_map )
    : m_color_map( color_map )
    , m_opacity_map( opacity_map )
{
}

/*==========================================================================*/
/**
 *  @brief  Constructs a copy of other.
 *  @param  other [in] Transfer function.
 */
/*==========================================================================*/
TransferFunction::TransferFunction( const TransferFunction& other )
    : m_color_map( other.m_color_map )
    , m_opacity_map( other.m_opacity_map )
{
}

/*==========================================================================*/
/**
 *  @brief  Destroys TransferFunction.
 */
/*==========================================================================*/
TransferFunction::~TransferFunction( void )
{
}

/*==========================================================================*/
/**
 *  @brief  Set color map.
 *  @param  color_map [in] color map
 */
/*==========================================================================*/
void TransferFunction::setColorMap( const kvs::ColorMap& color_map )
{
    m_color_map = color_map;
}

/*==========================================================================*/
/**
 *  @brief  Set opacity map.
 *  @param  opacity_map [in] opacity map
 */
/*==========================================================================*/
void TransferFunction::setOpacityMap( const kvs::OpacityMap& opacity_map )
{
    m_opacity_map = opacity_map;
}

/*===========================================================================*/
/**
 *  @brief  Sets min and max values.
 *  @param  min_value [in] min. value
 *  @param  max_value [in] max. value
 */
/*===========================================================================*/
void TransferFunction::setRange( const float min_value, const float max_value )
{
    m_color_map.setRange( min_value, max_value );
    m_opacity_map.setRange( min_value, max_value );
}

const bool TransferFunction::hasRange( void ) const
{
    return( m_color_map.hasRange() && m_opacity_map.hasRange() );
}

const bool TransferFunction::minValue( void ) const
{
    KVS_ASSERT( m_color_map.minValue() == m_opacity_map.minValue() );
    return( m_color_map.minValue() );
}

const bool TransferFunction::maxValue( void ) const
{
    KVS_ASSERT( m_color_map.maxValue() == m_opacity_map.maxValue() );
    return( m_color_map.maxValue() );
}

/*==========================================================================*/
/**
 *  @brief  Returns the color map.
 */
/*==========================================================================*/
const kvs::ColorMap& TransferFunction::colorMap( void ) const
{
    return( m_color_map );
}

/*==========================================================================*/
/**
 *  @brief  Returns the opacity map.
 */
/*==========================================================================*/
const kvs::OpacityMap& TransferFunction::opacityMap( void ) const
{
    return( m_opacity_map );
}

/*==========================================================================*/
/**
 *  @brief  Returns the resolution.
 */
/*==========================================================================*/
const size_t TransferFunction::resolution( void ) const
{
    KVS_ASSERT( m_opacity_map.resolution() == m_color_map.resolution() );
    return( m_opacity_map.resolution() );
}

/*==========================================================================*/
/**
 *  @brief  Create the alpha map.
 *  @param  resolution [in] resolution
 */
/*==========================================================================*/
void TransferFunction::create( const size_t resolution )
{
    m_opacity_map.setResolution( resolution );
    m_opacity_map.create();

    m_color_map.setResolution( resolution );
    m_color_map.create();
}

/*==========================================================================*/
/**
 *  @brief  Read a trasfer function data from the given file.
 *  @param  filename [in] filename
 *  @return true, if the reading process is done successfully
 */
/*==========================================================================*/
const bool TransferFunction::read( const std::string& filename )
{
    kvs::KVSMLTransferFunction transfer_function( filename );
    if ( transfer_function.isFailure() ) return( false );

    const float min_value = transfer_function.minValue();
    const float max_value = transfer_function.maxValue();
    const bool has_range = !( kvs::Math::Equal( min_value, max_value ) );
    if ( has_range )
    {
        m_color_map.setRange( min_value, max_value );
        m_opacity_map.setRange( min_value, max_value );
    }

    m_color_map.setResolution( transfer_function.resolution() );
    if ( transfer_function.colorPointList().size() > 0 )
    {
        kvs::KVSMLTransferFunction::ColorPointList::const_iterator point =
            transfer_function.colorPointList().begin();
        kvs::KVSMLTransferFunction::ColorPointList::const_iterator last =
            transfer_function.colorPointList().end();
        while ( point != last )
        {
            const float value = point->first;
            const kvs::RGBColor color = point->second;
            m_color_map.addPoint( value, color );
            point++;
        }

        m_color_map.create();
    }
    else
    {
        m_color_map = kvs::ColorMap( transfer_function.colors() );
    }

    m_opacity_map.setResolution( transfer_function.resolution() );
    if ( transfer_function.opacityPointList().size() > 0 )
    {
        kvs::KVSMLTransferFunction::OpacityPointList::const_iterator point =
            transfer_function.opacityPointList().begin();
        kvs::KVSMLTransferFunction::OpacityPointList::const_iterator last =
            transfer_function.opacityPointList().end();
        while ( point != last )
        {
            const float value = point->first;
            const kvs::Real32 opacity = point->second;
            m_opacity_map.addPoint( value, opacity );
            point++;
        }

        m_opacity_map.create();
    }
    else
    {
        m_opacity_map = kvs::OpacityMap( transfer_function.opacities() );
    }

    return( true );
}

/*==========================================================================*/
/**
 *  @brief  Writes the trasfer function data.
 *  @param  filename [in] filename
 *  @return true, if the reading process is done successfully
 */
/*==========================================================================*/
const bool TransferFunction::write( const std::string& filename )
{
    kvs::KVSMLTransferFunction transfer_function;
    transfer_function.setResolution( this->resolution() );
    transfer_function.setWritingDataType( kvs::KVSMLTransferFunction::Ascii );

    if ( m_color_map.points().size() > 0 )
    {
        kvs::ColorMap::Points::const_iterator point = m_color_map.points().begin();
        kvs::ColorMap::Points::const_iterator last = m_color_map.points().end();
        while ( point != last )
        {
            transfer_function.addColorPoint( point->first, point->second );
            point++;
        }
    }
    else
    {
        transfer_function.setColors( m_color_map.table() );
    }

    if ( m_opacity_map.points().size() > 0 )
    {
        kvs::OpacityMap::Points::const_iterator point = m_opacity_map.points().begin();
        kvs::OpacityMap::Points::const_iterator last = m_opacity_map.points().end();
        while ( point != last )
        {
            transfer_function.addOpacityPoint( point->first, point->second );
            point++;
        }
    }
    else
    {
        transfer_function.setOpacities( m_opacity_map.table() );
    }

    return( transfer_function.write( filename ) );
}

/*==========================================================================*/
/**
 *  @brief  Substitution operator =.
 *  @param  trunsfer_function [in] transfer function
 *  @retval transfer function
 */
/*==========================================================================*/
TransferFunction& TransferFunction::operator =( const TransferFunction& rhs )
{
    m_color_map   = rhs.m_color_map;
    m_opacity_map = rhs.m_opacity_map;

    return( *this );
}

} // end of namespace kvs
