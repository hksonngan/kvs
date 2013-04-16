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

    kvs::Vector3f m_transform_center;
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
    void setPosition( const kvs::Vector3f& position, const kvs::Vector3f& look_at );
    void setPosition( const kvs::Vector3f& position, const kvs::Vector3f& look_at, const kvs::Vector3f& up );
    void setPosition( const kvs::Vector3f& position );
    void setUpVector( const kvs::Vector3f& up_vector );
    void setLookAt( const kvs::Vector3f& look_at );
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
    const kvs::Vector3f position() const;
    const kvs::Vector3f upVector() const;
    const kvs::Vector3f lookAt() const;
    const kvs::Matrix44f viewingMatrix() const;
    const kvs::Vector2f lookAtInDevice() const;
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

    const kvs::Matrix44f projectionMatrix() const;
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
    const kvs::Vector2f projectObjectToWindow(
        float  p_obj_x,
        float  p_obj_y,
        float  p_obj_z,
        float* depth = NULL ) const;
//deprecated used at ObjectBase.cpp and ObjectManager.cpp
    const kvs::Vector2f projectObjectToWindow(
        const kvs::Vector3f& p_obj,
        float*               depth = NULL ) const;

public:
//deprecated unused
    const kvs::Vector3f projectWindowToObject(
        const kvs::Vector2f& p_win,
        float                depth = 0.0 ) const;
//deprecated unused
    const kvs::Vector3f projectWindowToCamera(
        const kvs::Vector2f& p_win,
        float                depth = 0.0 ) const;
//deprecated unused
    const kvs::Vector3f projectWindowToWorld(
        const kvs::Vector2f& p_win,
        float                depth = 0.0 ) const;
//deprecated unused
    const kvs::Vector3f projectObjectToCamera( const kvs::Vector3f& p_obj ) const;
//deprecated unused
    const kvs::Vector3f projectCameraToObject( const kvs::Vector3f& p_cam ) const;
//deprecated used at Light.cpp
    const kvs::Vector3f projectWorldToCamera( const kvs::Vector3f& p_wld ) const;
//deprecated unused
    const kvs::Vector3f projectCameraToWorld( const kvs::Vector3f& p_cam ) const;
//deprecated used at Shader.cpp, HAVSVolumeRenderer and RayCastingRenderer.cpp
    const kvs::Vector3f projectWorldToObject( const kvs::Vector3f& p_wld ) const;
//deprecated unused
    const kvs::Vector3f projectObjectToWorld( const kvs::Vector3f& p_obj ) const;

public:

    void resetXform();
    void rotate( const kvs::Matrix33f& rotation );
    void translate( const kvs::Vector3f& translation );
    void scale( const kvs::Vector3f& scaling );
};

} // end of namespace kvs

#endif // KVS__CAMERA_H_INCLUDE
