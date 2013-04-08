/*****************************************************************************/
/**
 *  @file   ObjectCoordinate.cpp
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
#include "ObjectCoordinate.h"
#include "WorldCoordinate.h"
#include <kvs/ObjectBase>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new ObjectCoordinate class.
 *  @param  position [in] position in object coordinates
 *  @param  object [in] pointer to an object defines object coordinates
 */
/*===========================================================================*/
ObjectCoordinate::ObjectCoordinate( const kvs::Vector3f& position, const kvs::ObjectBase* object ):
    m_position( position ),
    m_object( object )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns the position in object coordinates.
 *  @return position in object coordinates
 */
/*===========================================================================*/
const kvs::Vector3f& ObjectCoordinate::position() const
{
    return m_position;
}

/*===========================================================================*/
/**
 *  @brief  Transforms object coordinates to camera coordinates.
 *  @return world coordinates
 */
/*===========================================================================*/
const WorldCoordinate ObjectCoordinate::toWorldCoordinate() const
{
    const kvs::Vector3f position = m_object->xform().transform( m_position );
    return WorldCoordinate( position );
}

} // end of namespace kvs
