/*****************************************************************************/
/**
 *  @file   CameraCoordinate.h
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
#ifndef KVS__CAMERA_COORDINATE_H_INCLUDE
#define KVS__CAMERA_COORDINATE_H_INCLUDE

#include <kvs/Vector3>


namespace kvs
{

class Camera;
class NormalizedDeviceCoordinate;
class WorldCoordinate;

/*===========================================================================*/
/**
 *  @brief  Camera coordinate class.
 */
/*===========================================================================*/
class CameraCoordinate
{
private:

    kvs::Vector3f m_position; ///< position in camera coordinates
    const kvs::Camera* m_camera; ///< camera defines camera coordinates

public:

    CameraCoordinate( const kvs::Vector3f& position, const kvs::Camera* camera );

    const kvs::Vector3f& position() const;

    const NormalizedDeviceCoordinate toNormalizedDeviceCoordinate() const;
    const WorldCoordinate toWorldCoordinate() const;
};

} // end of namespace kvs

#endif // KVS__CAMERA_COORDINATE_H_INCLUDE
