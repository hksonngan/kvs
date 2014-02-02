/****************************************************************************/
/**
 *  @file   Trackball.cpp
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
/****************************************************************************/
#include "Trackball.h"
#include <kvs/Camera>
#include <kvs/Matrix33>
#include <kvs/Quaternion>



namespace kvs
{

/*==========================================================================*/
/**
 *  @brief  Constructs a new Trackball class.
 */
/*==========================================================================*/
Trackball::Trackball()
{
    this->reset();
}

/*==========================================================================*/
/**
 *  @brief  Destroys the Trackball class.
 */
/*==========================================================================*/
Trackball::~Trackball()
{
    this->reset();
}

/*==========================================================================*/
/**
 *  @brief  Scaling operation.
 *  @param  start [in] start dragging point
 *  @param  end [in] end dragging point
 */
/*==========================================================================*/
void Trackball::scale( const kvs::Vec2i& start, const kvs::Vec2i& end, ScalingType type )
{
    const float ScalingFactor = 100.0f;

    m_scaling = kvs::Vec3( 1.0, 1.0, 1.0 );

    const kvs::Vector2f n_old = this->get_norm_position( start );
    const kvs::Vector2f n_new = this->get_norm_position( end );

    const float h = static_cast<float>( m_window_height );
    const float s = 1.0f + ScalingFactor * ( n_old.y() - n_new.y() ) / h;
    switch ( type )
    {
    case ScalingXYZ: m_scaling.set( s, s, s ); break;
    case ScalingX:   m_scaling.set( s, 1, 1 ); break;
    case ScalingY:   m_scaling.set( 1, s, 1 ); break;
    case ScalingZ:   m_scaling.set( 1, 1, s ); break;
    case ScalingXY:  m_scaling.set( s, s, 1 ); break;
    case ScalingYZ:  m_scaling.set( 1, s, s ); break;
    case ScalingZX:  m_scaling.set( s, 1, s ); break;
    default:         m_scaling.set( 1, 1, 1 ); break;
    }
}

/*==========================================================================*/
/**
 *  @brief  Translation operation.
 *  @param  start [in] start dragging point in the window coordinate system
 *  @param  end [in] end dragging point in the widnow coordinate system
 */
/*==========================================================================*/
void Trackball::translate( const kvs::Vec2i& start, const kvs::Vec2i& end )
{
    kvs::Vec2i diff = end - start;
    kvs::Vec3 trans;
    trans.x() = (float)diff.x() * 10.0f / m_window_width;
    trans.y() = -(float)diff.y() * 10.0f / m_window_height;
    trans.z() = 0;

    // Transform camera to world.
    m_translation = m_ref_camera->xform().transformNormal( trans );
}

/*==========================================================================*/
/**
 *  @brief  Rotation operation.
 *  @param  start [in] start dragging point in the window coordinate system
 *  @param  end [in] end dragging point in the window coordinate system
 */
/*==========================================================================*/
void Trackball::rotate( const kvs::Vec2i& start, const kvs::Vec2i& end )
{
    if ( start == end )
    {
        m_rotation.set( 0.0, 0.0, 0.0, 1.0 );
        return;
    }

    kvs::Vec2 n_old( this->get_norm_position( start ) );
    kvs::Vec2 n_new( this->get_norm_position( end   ) );

    kvs::Vec3 p1( n_old, this->depth_on_sphere( n_old ) );
    kvs::Vec3 p2( n_new, this->depth_on_sphere( n_new ) );

    // Transform to world coordinate.
    kvs::Vec3 p1w = m_ref_camera->xform().transformNormal( p1 );
    kvs::Vec3 p2w = m_ref_camera->xform().transformNormal( p2 );

    m_rotation = kvs::Quaternion::rotationQuaternion( p1w, p2w );
}

/*==========================================================================*/
/**
 *  Reset.
 */
/*==========================================================================*/
void Trackball::reset()
{
    m_size = 0.6f;
    m_depth = 1.0f;
    m_rotation_center = kvs::Vec2( 0.0f, 0.0f );
    m_scaling = kvs::Vec3( 1.0f, 1.0f, 1.0f );
    m_translation = kvs::Vec3( 0.0f, 0.0f, 0.0f );
    m_rotation = kvs::Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );
}

/*==========================================================================*/
/**
 *  Calculate a distance between 'dir' and the virtual sphere.
 *  @param dir [in] position
 *  @return distance
 */
/*==========================================================================*/
float Trackball::depth_on_sphere( const kvs::Vec2& dir ) const
{
    const float Sqrt2 = 1.4142135623730950488f;
    const float HalfOfSqrt2 = 0.7071067811865475244f;

    const double r = m_size;
    const double d = dir.length();

    float z;
    if ( d < r * HalfOfSqrt2 )
    {
        // inside sphere
        z = static_cast<float>( std::sqrt( r * r - d * d ) );
    }
    else
    {
        // on hyperbola
        const double t = r / Sqrt2;
        z = static_cast<float>( t * t / d );
    }

    return z;
}

/*==========================================================================*/
/**
 *  Get the mouse position.
 *  @return mouse position (on the normal device coordinate system)
 *
 *  Get the mouse position on the normal device coordinate system.
 *  A center of the normal device coordinate system is a center of the image
 *  and the rage is [-1,-1].
 */
/*==========================================================================*/
kvs::Vec2 Trackball::get_norm_position( const kvs::Vec2i& pos ) const
{
    const float x =  2.0f * ( pos.x() - m_rotation_center.x() ) / m_window_width;
    const float y = -2.0f * ( pos.y() - m_rotation_center.y() ) / m_window_height;

    return kvs::Vec2( x, y );
}

} // end of namespace kvs
