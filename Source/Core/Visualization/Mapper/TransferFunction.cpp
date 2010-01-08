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


namespace
{

const size_t DefaultResolution = 256;

}

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
    m_opacity_map.create( resolution );
    m_color_map.create( resolution );
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

    m_opacity_map = kvs::OpacityMap( transfer_function.opacities() );
    m_color_map   = kvs::ColorMap( transfer_function.colors() );

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
    transfer_function.setColors( m_color_map.table() );
    transfer_function.setOpacities( m_opacity_map.table() );

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
