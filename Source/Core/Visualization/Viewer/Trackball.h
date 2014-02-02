/****************************************************************************/
/**
 *  @file   Trackball.h
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
#ifndef KVS__TRACKBALL_H_INCLUDE
#define KVS__TRACKBALL_H_INCLUDE

#include <kvs/Vector2>
#include <kvs/Vector3>
#include <kvs/Quaternion>


namespace kvs
{

class Camera;

/*==========================================================================*/
/**
 *  Trackball class
 */
/*==========================================================================*/
class Trackball
{
public:

    enum ScalingType
    {
        ScalingXYZ = 0,
        ScalingX,
        ScalingY,
        ScalingZ,
        ScalingXY,
        ScalingYZ,
        ScalingZX,
        ScalingNot,
        ScalingTypeSize
    };

//protected:
private:

    float m_size; ///< trackball size
    float m_depth; ///< how near from center
    kvs::Vec2 m_rotation_center; ///< center of rotation in the devise coordinate system
    kvs::Vec3 m_scaling; ///< current scaling value
    kvs::Vec3 m_translation; ///< current translation vector
    kvs::Quaternion m_rotation; ///< current rotation quaternion
    int m_window_width; ///< window width
    int m_window_height; ///< window height
    kvs::Camera* m_ref_camera; ///< pointer to camera (reference only)

public:

    Trackball();
    virtual ~Trackball();

    void attachCamera( kvs::Camera* camera ) { m_ref_camera = camera; }
    void resetRotationCenter() { m_rotation_center = kvs::Vec2::Zero(); }

    void setTrackballSize( const float size ) { m_size = size; }
    void setDepthValue( const float depth ) { m_depth = depth; }
    void setRotationCenter( const kvs::Vec2& center ) { m_rotation_center = center; }
    void setScaling( const kvs::Vec3& scaling ) { m_scaling = scaling; }
    void setTranslation( const kvs::Vec3& translation ) { m_translation = translation; }
    void setRotation( const kvs::Quaternion& rotation ) { m_rotation = rotation; }
    void setWindowSize( const int w, const int h ) { m_window_width = w; m_window_height = h; }

    float size() const { return m_size; }
    float depthValue() const { return m_depth; }
    const kvs::Vec2& rotationCenter() const { return m_rotation_center; }
    const kvs::Vec3& scaling() const { return m_scaling; }
    const kvs::Vec3& translation() const { return m_translation; }
    const kvs::Quaternion& rotation() const { return m_rotation; }
    int windowWidth() const { return m_window_width; }
    int windowHeight() const { return m_window_height; }

    void scale( const kvs::Vec2i& start, const kvs::Vec2i& end, ScalingType type = ScalingXYZ );
    void rotate( const kvs::Vec2i& start, const kvs::Vec2i& end );
    void translate( const kvs::Vec2i& start, const kvs::Vec2i& end );
    void reset();

private:

    float depth_on_sphere( const kvs::Vec2& dir ) const;
    kvs::Vec2 get_norm_position( const kvs::Vec2i& pos ) const;
};

} // end of namespace kvs

#endif // KVS__TRACKBALL_H_INCLUDE
