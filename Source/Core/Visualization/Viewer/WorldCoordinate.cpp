/*****************************************************************************/
/**
 *  @file   WorldCoordinate.cpp
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
#include "WorldCoordinate.h"
#include "CameraCoordinate.h"
#include "ObjectCoordinate.h"
#include <kvs/Camera>
#include <kvs/ObjectBase>
#include <kvs/Xform>
#include <kvs/OpenGL>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new WorldCoordinate class.
 *  @param  position [in] position in world coordinates
 */
/*===========================================================================*/
WorldCoordinate::WorldCoordinate( const kvs::Vector3f& position ):
    m_position( position )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns the position in world coordinates.
 *  @return position in world coordinates
 */
/*===========================================================================*/
const kvs::Vector3f& WorldCoordinate::position() const
{
    return m_position;
}

/*===========================================================================*/
/**
 *  @brief  Transforms world coordinates to camera coordinates.
 *  @param  camera [in] pointer to a camera defines camera coordiantes
 *  @return transformed position in camera coordinates
 */
/*===========================================================================*/
const CameraCoordinate WorldCoordinate::toCameraCoordinate( const kvs::Camera* camera ) const
{
    const kvs::Vector3f position = kvs::Xform( camera->viewingMatrix() ).transform( m_position );
    return CameraCoordinate( position, camera );
}

/*===========================================================================*/
/**
 *  @brief  Transforms the world coordinates to the object coordinates.
 *  @param  object [in] pointer to an object defines object coordiantes
 *  @return transformed position in object coordinates
 */
/*===========================================================================*/
const ObjectCoordinate WorldCoordinate::toObjectCoordinate( const kvs::ObjectBase* object ) const
{
    const kvs::Vector3f position = object->xform().inverse().transform( m_position );
    return ObjectCoordinate( position, object );
}

/*===========================================================================*/
/**
 *  @brief  Transforms the world coordinates to the object coordinates.
 *  @param  camera [in] pointer to the camera
 *  @return transformed position in object coordinates
 *
 *  The modeling matrix can be calculated from the modelview matrix stored in
 *  the OpenGL matrix stack and the given viewing matrix.
 */
/*===========================================================================*/
const ObjectCoordinate WorldCoordinate::toObjectCoordinate( const kvs::Camera* camera ) const
{
    const kvs::Xform inv_modeling( camera->modelViewMatrix().inverted() * camera->viewingMatrix() );
    const kvs::Vector3f position = inv_modeling.transform( m_position );
    return ObjectCoordinate( position, NULL );
}

} // end of namespace kvs
