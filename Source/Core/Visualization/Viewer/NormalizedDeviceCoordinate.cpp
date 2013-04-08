/*****************************************************************************/
/**
 *  @file   NormalizedDeviceCoordinate.cpp
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
#include "NormalizedDeviceCoordinate.h"
#include "WindowCoordinate.h"
#include "CameraCoordinate.h"
#include <kvs/Camera>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new NormalizedDeviceCoordinate class.
 *  @param  position [in] position in normalized device coordinates
 */
/*===========================================================================*/
NormalizedDeviceCoordinate::NormalizedDeviceCoordinate( const kvs::Vector3f& position ):
    m_position( position )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns the position in normalized device coordinates.
 *  @return position in normalized device coordinates
 */
/*===========================================================================*/
const kvs::Vector3f& NormalizedDeviceCoordinate::position() const
{
    return m_position;
}

/*===========================================================================*/
/**
 *  @brief  Transforms normalized device coordinates to world coordinates.
 *  @return world coordinates
 */
/*===========================================================================*/
const WindowCoordinate NormalizedDeviceCoordinate::toWindowCoordinate(
    const int x,
    const int y,
    const size_t width,
    const size_t height ) const
{
    const float px = ( m_position[0] + 1.0f ) / 2.0f * width + x;
    const float py = ( m_position[1] + 1.0f ) / 2.0f * height + y;
    const float pz = WindowCoordinate::CalculateDepth( ( m_position[2] + 1.0f ) / 2.0f );
    const kvs::Vector3f position( px, py, pz );
    return WindowCoordinate( position, x, y, width, height );
}

/*===========================================================================*/
/**
 *  @brief  Transforms normalized device coordinates to camera coordinates.
 *  @param  camera [in] pointer to a camera defines camera coordinates
 *  @return camera coordinates
 */
/*===========================================================================*/
const CameraCoordinate NormalizedDeviceCoordinate::toCameraCoordinate( const kvs::Camera* camera ) const
{
    const kvs::Xform xform( camera->projectionMatrix() * camera->viewingMatrix() );
    const kvs::Vector3f position = xform.inverse().project( m_position );
    return CameraCoordinate( position, camera );
}

} // end of namespace kvs
