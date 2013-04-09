/****************************************************************************/
/**
 *  @file Trackball.h
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

protected:

    float m_size; ///< trackball size
    float m_depth; ///< how near from center
    kvs::Vector2f m_rotation_center; ///< center of rotation in the devise coordinate system
    kvs::Vector3f m_scaling; ///< current scaling value
    kvs::Vector3f m_translation; ///< current translation vector
    kvs::Quaternion m_rotation; ///< current rotation quaternion
    int m_window_width; ///< window width
    int m_window_height; ///< window height
    kvs::Camera* m_ref_camera; ///< pointer to camera (reference only)

public:

    Trackball();
    virtual ~Trackball();

    void attachCamera( kvs::Camera* camera );
    void resetRotationCenter();
    void setTrackballSize( const float size );
    void setDepthValue( const float depth );
    void setRotationCenter( const kvs::Vector2f& center );
    void setScaling( const kvs::Vector3f& scaling );
    void setTranslation( const kvs::Vector3f& translation );
    void setRotation( const kvs::Quaternion& rotation );
    void setWindowSize( const int w, const int h );
    float size() const;
    float depthValue() const;
    const kvs::Vector2f& rotationCenter() const;
    const kvs::Vector3f& scaling() const;
    const kvs::Vector3f& translation() const;
    const kvs::Quaternion& rotation() const;
    int windowWidth() const;
    int windowHeight() const;

    void scale( const kvs::Vector2i& start, const kvs::Vector2i& end, ScalingType type = ScalingXYZ );
    void rotate( const kvs::Vector2i& start, const kvs::Vector2i& end );
    void translate( const kvs::Vector2i& start, const kvs::Vector2i& end );

protected:

    void reset();
    float depth_on_sphere( const kvs::Vector2f& dir ) const;
    kvs::Vector2f get_norm_position( const kvs::Vector2i& pos ) const;
};

} // end of namespace kvs

#endif // KVS__TRACKBALL_H_INCLUDE
