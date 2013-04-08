/*****************************************************************************/
/**
 *  @file   WindowCoordinate.cpp
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
#include "WindowCoordinate.h"
#include "NormalizedDeviceCoordinate.h"


namespace kvs
{

float WindowCoordinate::m_front = 0.0f;
float WindowCoordinate::m_back = 1.0f;

/*===========================================================================*/
/**
 *  @brief  Sets depth range.
 *  @param  front [in] depth value of the front clipping plane
 *  @param  back [in] depth value of the back clipping plane
 */
/*===========================================================================*/
void WindowCoordinate::SetDepthRange( const float front, const float back )
{
    m_front = front;
    m_back = back;
}

/*===========================================================================*/
/**
 *  @brief  Calculates the depth value.
 *  @param  nd_depth [in] depth value
 *  @return depth value
 */
/*===========================================================================*/
float WindowCoordinate::CalculateDepth( const float nd_depth )
{
    return m_front + ( m_back - m_front ) * nd_depth;
}

/*===========================================================================*/
/**
 *  @brief  Inverts the depth value.
 *  @param  depth [in] depth value
 *  @return depth value
 */
/*===========================================================================*/
float WindowCoordinate::InvertDepth( const float depth )
{
    return ( depth - m_front ) / ( m_back - m_front );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new WindowCoordinate class.
 *  @param  position [in] position in the window coordinates
 *  @param  x [in] window position x
 *  @param  y [in] winodw position y
 *  @param  width [in] window width
 *  @param  height [in] window height
 */
/*===========================================================================*/
WindowCoordinate::WindowCoordinate(
    const kvs::Vector3f& position,
    const int x,
    const int y,
    const size_t width,
    const size_t height ):
    m_position( position ),
    m_x( x ),
    m_y( y ),
    m_width( width ),
    m_height( height )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns the position in the widnow coordinates.
 *  @return position in the winodw coordinates
 */
/*===========================================================================*/
const kvs::Vector3f& WindowCoordinate::position() const
{
    return m_position;
}

/*===========================================================================*/
/**
 *  @brief  Transforms the widnow coordinates to the normalized device coordinates.
 *  @return transformed position in the normalized device coordinates
 */
/*===========================================================================*/
const NormalizedDeviceCoordinate WindowCoordinate::toNormalizedDeviceCoordinate() const
{
    const float x = ( m_position[0] - m_x ) / m_width * 2.0f - 1.0f;
    const float y = ( m_position[1] - m_y ) / m_height * 2.0f - 1.0f;
    const float z = WindowCoordinate::InvertDepth( m_position[2] ) * 2.0f - 1.0f;
    const kvs::Vector3f position( x, y, z );
    return NormalizedDeviceCoordinate( position );
}

} // end of namespace kvs
