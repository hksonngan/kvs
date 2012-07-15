/****************************************************************************/
/**
 *  @file Camera.h
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
class Camera
{
    kvsClassName( kvs::Camera );

public:

    enum ProjectionType
    {
        Perspective = 0,
        Orthogonal = 1,
        Frustum
    };

private:
#if KVS_ENABLE_DEPRECATED
protected:
#endif
    kvs::XformControl m_xform_control;
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

    virtual void initialize( void );

    virtual void update( void );

    virtual kvs::ColorImage snapshot( void );

public:

    const kvs::Matrix44f projectionMatrix( void ) const;

    const kvs::Matrix44f modelViewMatrix( void ) const;

    const kvs::Matrix44f projectionModelViewMatrix( void ) const;

    void getProjectionMatrix( float (*projection)[16] ) const;

    void getModelViewMatrix( float (*modelview)[16] ) const;

    void getProjectionModelViewMatrix( float (*projection_modelview)[16] ) const;

    void getProjectionModelViewMatrix(
        float projection[16],
        float modelview[16],
        float (*projection_modelview)[16] ) const;

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

    void resetXform( void );

    void rotate( const kvs::Matrix33f& rotation );

    void translate( const kvs::Vector3f& translation );

    void scale( const kvs::Vector3f& scaling );

private:

    void update_up_at_from( void );

#if KVS_ENABLE_DEPRECATED
public:

    operator kvs::XformControl() const
    {
        return m_xform_control;
    }

public:

    void clear()
    {
        m_xform_control.clear();
    }

    void set(
        const kvs::Vector3f&  translation,
        const kvs::Vector3f&  scaling,
        const kvs::Matrix33f& rotation )
    {
        m_xform_control.set( translation, scaling, rotation );
    }

    void set( const Xform& xform )
    {
        m_xform_control.set( xform );
    }

    void updateRotation( const kvs::Matrix33f& rotation )
    {
        m_xform_control.updateRotation( rotation );
    }

    void updateTranslation( const kvs::Vector3f& translation )
    {
        m_xform_control.updateTranslation( translation );
    }

    void updateScaling( const kvs::Vector3f& scaling )
    {
        m_xform_control.updateScaling( scaling );
    }

    void updateScaling( float scaling )
    {
        m_xform_control.updateScaling( scaling );
    }

    const kvs::Vector3f translation() const
    {
        return m_xform_control.translation();
    }

    const kvs::Matrix33f& rotation() const
    {
        return m_xform_control.rotation();
    }

    const kvs::Matrix33f scaledRotation() const
    {
        return m_xform_control.scaledRotation();
    }

    const kvs::Vector3f& scaling() const
    {
        return m_xform_control.scaling();
    }

    Xform get() const
    {
        return m_xform_control.get();
    }

    void get( float (*array)[16] ) const
    {
        m_xform_control.get( array );
    }

public:

    void enableCollision()
    {
        m_xform_control.enableCollision();
    }

    void disableCollision()
    {
        m_xform_control.disableCollision();
    }

    bool canCollision()
    {
        return m_xform_control.canCollision();
    }

    void setInitialXform(
        const kvs::Vector3f&  translation = kvs::Vector3f(0,0,0),
        const kvs::Vector3f&  scaling     = kvs::Vector3f(1,1,1),
        const kvs::Matrix33f& rotation    = kvs::Matrix33f(1,0,0,0,1,0,0,0,1) )
    {
        m_xform_control.setInitialXform( translation, scaling, rotation );
    }

    void saveXform()
    {
        m_xform_control.saveXform();
    }

    void setXform( const kvs::Xform& xform )
    {
        m_xform_control.setXform( xform );
    }

    void applyXform() const
    {
        m_xform_control.applyXform();
    }

    const kvs::Xform xform() const
    {
        return m_xform_control.xform();
    }
#endif
};

} // end of namespace kvs

#endif // KVS__CAMERA_H_INCLUDE
