/****************************************************************************/
/**
 *  @file Camera.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#ifndef KVS_CORE_CAMERA_H_INCLUDE
#define KVS_CORE_CAMERA_H_INCLUDE

#include "XformControl.h"
#include <kvs/ClassName>
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
class Camera : public XformControl
{
    kvsClassName( Camera );

public:

    enum ProjectionType
    {
        Perspective = 0,
        Orthogonal
    };

protected:

    ProjectionType m_projection_type; ///< projection type
    kvs::Vector3f m_init_position; ///< initial position in the world coordinate system
    kvs::Vector3f m_init_up_vector; ///< initial up vector in the world coordinate system
    kvs::Vector3f m_init_look_at; ///< initial look-at point in the world coordinate system
    kvs::Vector3f m_position; ///< position in the world coordinate system
    kvs::Vector3f m_up_vector; ///< up vector in the world coordinate system
    kvs::Vector3f m_look_at; ///< look-at point in the world coordinate system
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

    Camera( const bool collision = true );

    virtual ~Camera( void );

public:

    void initialize( void );

public:

    void setProjectionType( const ProjectionType projection_type );

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

public:

    const bool isPerspective( void ) const;

    const ProjectionType projectionType( void ) const;

    const kvs::Vector3f& position( void ) const;

    const kvs::Vector3f& upVector( void ) const;

    const kvs::Vector3f& lookAt( void ) const;

    const kvs::Vector2f lookAtInDevice( void ) const;

    const float fieldOfView( void ) const;

    const float back( void ) const;

    const float front( void ) const;

    const float left( void ) const;

    const float right( void ) const;

    const float bottom( void ) const;

    const float top( void ) const;

    const size_t windowWidth( void ) const;

    const size_t windowHeight( void ) const;

public:

    void update( void );

    kvs::ColorImage snapshot( void );

public:

    void getProjectionMatrix( float (*projection)[16] ) const;

    void getModelviewMatrix( float (*modelview)[16] ) const;

    void getCombinedMatrix( float (*combined)[16] ) const;

    void getCombinedMatrix(
        float projection[16],
        float modelview[16],
        float (*combined)[16] ) const;

    const kvs::Vector2f projectObjectToWindow(
        float  p_obj_x,
        float  p_obj_y,
        float  p_obj_z,
        float* depth = NULL ) const;

    const kvs::Vector2f projectObjectToWindow(
        const kvs::Vector3f& p_obj,
        float*               depth = NULL ) const;

public:

    const kvs::Vector3f projectWindowToObject(
        const kvs::Vector2f& p_win,
        float                depth = 0.0 ) const;

    const kvs::Vector3f projectWindowToCamera(
        const kvs::Vector2f& p_win,
        float                depth = 0.0 ) const;

    const kvs::Vector3f projectWindowToWorld(
        const kvs::Vector2f& p_win,
        float                depth = 0.0 ) const;

    const kvs::Vector3f projectObjectToCamera( const kvs::Vector3f& p_obj ) const;

    const kvs::Vector3f projectCameraToObject( const kvs::Vector3f& p_cam ) const;

    const kvs::Vector3f projectWorldToCamera( const kvs::Vector3f& p_wld ) const;

    const kvs::Vector3f projectCameraToWorld( const kvs::Vector3f& p_cam ) const;

    const kvs::Vector3f projectWorldToObject( const kvs::Vector3f& p_wld ) const;

    const kvs::Vector3f projectObjectToWorld( const kvs::Vector3f& p_obj ) const;

public:

    void rotate( const kvs::Matrix33f& rotation );

    void translate( const kvs::Vector3f& translation );

    void scale( const kvs::Vector3f& scaling );

private:

    void update_up_at_from( void );
};

} // end of namespace kvs

#endif // KVS_CORE_CAMERA_H_INCLUDE
