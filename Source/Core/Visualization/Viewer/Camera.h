/****************************************************************************/
/**
 *  @file   Camera.h
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
#ifndef KVS__CAMERA_H_INCLUDE
#define KVS__CAMERA_H_INCLUDE

#include <kvs/XformControl>
#include <kvs/Vector2>
#include <kvs/Vector3>
#include <kvs/Matrix33>
#include <kvs/ColorImage>


namespace kvs
{

/*==========================================================================*/
/**
 *  Camera class
 */
/*==========================================================================*/
class Camera : public kvs::XformControl
{
public:

    enum ProjectionType
    {
        Perspective = 0,
        Orthogonal = 1,
        Frustum
    };

private:

    kvs::Vec3 m_transform_center;
    ProjectionType m_projection_type; ///< projection type
    float m_field_of_view; ///< field of view [deg]
    float m_front; ///< front plane position
    float m_back; ///< back plane position
    float m_left; ///< left plane position
    float m_right; ///< right plane position
    float m_bottom; ///< bottom plane position
    float m_top; ///< top plane position
    size_t m_window_width; ///< window width
    size_t m_window_height; ///< window height

public:

    Camera();
    virtual ~Camera();

    void setProjectionType( const ProjectionType projection_type );
    void setPosition( const kvs::Vec3& position, const kvs::Vec3& look_at );
    void setPosition( const kvs::Vec3& position, const kvs::Vec3& look_at, const kvs::Vec3& up );
    void setPosition( const kvs::Vec3& position );
    void setUpVector( const kvs::Vec3& up_vector );
    void setLookAt( const kvs::Vec3& look_at );
    void setFieldOfView( const float fov );
    void setBack( const float back );
    void setFront( const float front );
    void setLeft( const float left );
    void setRight( const float right );
    void setBottom( const float bottom );
    void setTop( const float top );
    void setWindowSize( const size_t width, const size_t height );

    bool isPerspective() const;
    ProjectionType projectionType() const;
    const kvs::Vec3 position() const;
    const kvs::Vec3 upVector() const;
    const kvs::Vec3 lookAt() const;
    const kvs::Matrix44f projectionMatrix() const;
    const kvs::Matrix44f viewingMatrix() const;
    const kvs::Vec2 lookAtInDevice() const;
    float fieldOfView() const;
    float back() const;
    float front() const;
    float left() const;
    float right() const;
    float bottom() const;
    float top() const;
    size_t windowWidth() const;
    size_t windowHeight() const;

    virtual void initialize();
    virtual void update();
    virtual kvs::ColorImage snapshot();

public:

//deprecated unused
    const kvs::Matrix44f modelViewMatrix() const;
//deprecated unused
    const kvs::Matrix44f projectionModelViewMatrix() const;
//deprecated unused
    void getProjectionMatrix( float (*projection)[16] ) const;
//deprecated unused
    void getModelViewMatrix( float (*modelview)[16] ) const;
//deprecated unused
    void getProjectionModelViewMatrix( float (*projection_modelview)[16] ) const;
//deprecated unused
    void getProjectionModelViewMatrix(
        const float projection[16],
        const float modelview[16],
        float (*projection_modelview)[16] ) const;
public:
    void getCombinedMatrix( float (*combined)[16] ) const;
//deprecated unused
    void getCombinedMatrix(
        const float projection[16],
        const float modelview[16],
        float (*combined)[16] ) const;
//deprecated unused
    const kvs::Vec2 projectObjectToWindow(
        float  p_obj_x,
        float  p_obj_y,
        float  p_obj_z,
        float* depth = NULL ) const;
//deprecated used at ObjectBase.cpp and ObjectManager.cpp
    const kvs::Vec2 projectObjectToWindow(
        const kvs::Vec3& p_obj,
        float*               depth = NULL ) const;

public:
//deprecated unused
    const kvs::Vec3 projectWindowToObject(
        const kvs::Vec2& p_win,
        float                depth = 0.0 ) const;
//deprecated unused
    const kvs::Vec3 projectWindowToCamera(
        const kvs::Vec2& p_win,
        float                depth = 0.0 ) const;
//deprecated unused
    const kvs::Vec3 projectWindowToWorld(
        const kvs::Vec2& p_win,
        float                depth = 0.0 ) const;
//deprecated unused
    const kvs::Vec3 projectObjectToCamera( const kvs::Vec3& p_obj ) const;
//deprecated unused
    const kvs::Vec3 projectCameraToObject( const kvs::Vec3& p_cam ) const;
//deprecated used at Light.cpp
    const kvs::Vec3 projectWorldToCamera( const kvs::Vec3& p_wld ) const;
//deprecated unused
    const kvs::Vec3 projectCameraToWorld( const kvs::Vec3& p_cam ) const;
//deprecated used at Shader.cpp, HAVSVolumeRenderer and RayCastingRenderer.cpp
    const kvs::Vec3 projectWorldToObject( const kvs::Vec3& p_wld ) const;
//deprecated unused
    const kvs::Vec3 projectObjectToWorld( const kvs::Vec3& p_obj ) const;

public:

    void resetXform();
    void rotate( const kvs::Mat3& rotation );
    void translate( const kvs::Vec3& translation );
    void scale( const kvs::Vec3& scaling );
};

} // end of namespace kvs

#endif // KVS__CAMERA_H_INCLUDE
