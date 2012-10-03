/****************************************************************************/
/**
 *  @file Camera.cpp
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
#include "Camera.h"
#include <utility>
#include <kvs/OpenGL>
#include <kvs/ColorImage>
#include <kvs/Matrix44>
#include <kvs/ViewingMatrix44>
#include <kvs/FrustumMatrix44>
#include <kvs/PerspectiveMatrix44>
#include <kvs/OrthogonalMatrix44>


namespace
{

const kvs::Xform MakeCameraXform( const kvs::Vector3f& eye, 
                                  const kvs::Vector3f& center, 
                                  const kvs::Vector3f& up )
{
    const kvs::Vector3f y = up.normalized();
    const kvs::Vector3f z = ( eye - center ).normalized();
    const kvs::Vector3f x = y.cross( z ).normalized();
    const kvs::Vector3f t = eye;

    const kvs::Matrix44f m( x[0], y[0], z[0], t[0], 
                            x[1], y[1], z[1], t[1], 
                            x[2], y[2], z[2], t[2], 
                            0, 0, 0, 1 );
    return kvs::Xform( m );
}

}

namespace kvs
{

/*==========================================================================*/
/**
 *  Default constructor.
 *  @param collision [in] collision dectection flag
 */
/*==========================================================================*/
Camera::Camera()
{
    this->initialize();
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
Camera::~Camera( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Sets the projection type of the camera.
 *  @param  projection_type [in] projection type
 */
/*===========================================================================*/
void Camera::setProjectionType( const Camera::ProjectionType projection_type )
{
    m_projection_type = projection_type;
}

void Camera::setPosition( const kvs::Vector3f& position, const kvs::Vector3f& look_at )
{
    this->setPosition( position, look_at, this->upVector() );
}

void Camera::setPosition( const kvs::Vector3f& position, const kvs::Vector3f& look_at, const kvs::Vector3f& up )
{
    m_transform_center = look_at;
    this->setXform( ::MakeCameraXform( position, look_at, up ) );
}

/*==========================================================================*/
/**
 *  Set a camera position in the world coordinate system.
 *  @param position [in] camera position
 */
/*==========================================================================*/
void Camera::setPosition( const kvs::Vector3f& position )
{
    this->setPosition( position, this->lookAt(), this->upVector() );
}

/*==========================================================================*/
/**
 *  Set a up vector in the world coordinate system.
 *  @param up [in] up vector
 */
/*==========================================================================*/
void Camera::setUpVector( const kvs::Vector3f& up_vector )
{
    this->setPosition( this->position(), this->lookAt(), up_vector );
}

/*==========================================================================*/
/**
 *  Set a look-at point in the world coordinate system.
 *  @param at [in] look-at point
 */
/*==========================================================================*/
void Camera::setLookAt( const kvs::Vector3f& look_at )
{
    this->setPosition( this->position(), look_at, this->upVector() );
}

/*==========================================================================*/
/**
 *  Set a field of view (FOV) parameter.
 *  @param fov [in] FOV parameter [deg]
 */
/*==========================================================================*/
void Camera::setFieldOfView( const float fov )
{
    m_field_of_view = fov;
}

/*==========================================================================*/
/**
 *  Set a back parameter.
 *  @param back [in] back parameter
 */
/*==========================================================================*/
void Camera::setBack( const float back )
{
    m_back = back;
}

/*==========================================================================*/
/**
 *  Set a front parameter.
 *  @param front [in] front parameter
 */
/*==========================================================================*/
void Camera::setFront( const float front )
{
    m_front = front;
}

/*==========================================================================*/
/**
 *  Set a left parameter.
 *  @param left [in] left parameter
 */
/*==========================================================================*/
void Camera::setLeft( const float left )
{
    m_left = left;
}

/*==========================================================================*/
/**
 *  Set a right parameter.
 *  @param right [in] right parameter
 */
/*==========================================================================*/
void Camera::setRight( const float right )
{
    m_right = right;
}

/*==========================================================================*/
/**
 *  Set a bottom parameter.
 *  @param bottom [in] bottom parameter
 */
/*==========================================================================*/
void Camera::setBottom( const float bottom )
{
    m_bottom = bottom;
}

/*==========================================================================*/
/**
 *  Set a top parameter.
 *  @param top [in] top parameter
 */
/*==========================================================================*/
void Camera::setTop( const float top )
{
    m_top = top;
}

/*==========================================================================*/
/**
 *  Set a window size.
 *  @param width [in] window width
 *  @param height [in] window height
 */
/*==========================================================================*/
void Camera::setWindowSize( const size_t width, const size_t height )
{
    m_window_width  = width;
    m_window_height = height;
}

/*==========================================================================*/
/**
 *  Determine if this camera is perspective camera.
 *  @retval true  : persepctive camera
 *  @retval false : orthogonal camera
 */
/*==========================================================================*/
const bool Camera::isPerspective( void ) const
{
    return( m_projection_type == Camera::Perspective );
}

/*===========================================================================*/
/**
 *  @brief  Returns the projection type of the camera.
 *  @return projection type
 */
/*===========================================================================*/
const Camera::ProjectionType Camera::projectionType( void ) const
{
    return( m_projection_type );
}

/*==========================================================================*/
/**
 *  Get the camera position.
 */
/*==========================================================================*/
const kvs::Vector3f Camera::position( void ) const
{
    return this->xform().translation();
}

/*==========================================================================*/
/**
 *  Get the up vector.
 */
/*==========================================================================*/
const kvs::Vector3f Camera::upVector( void ) const
{
    kvs::Matrix44f m = this->xform().toMatrix();
    return kvs::Vector3f( m[0][1], m[1][1], m[2][1] ).normalized();
}

/*==========================================================================*/
/**
 *  Get the look-at point.
 */
/*==========================================================================*/
const kvs::Vector3f Camera::lookAt( void ) const
{
    return m_transform_center;
}

const kvs::Matrix44f Camera::viewingMatrix() const
{
    return this->xform().inverse().toMatrix();
}

/*==========================================================================*/
/**
 *  Get a look-at point in device coordinate system.
 *  @return look-at point in the device coordinate system
 */
/*==========================================================================*/
const kvs::Vector2f Camera::lookAtInDevice( void ) const
{
    return( kvs::Vector2f( m_window_width / 2.0f, m_window_height / 2.0f ) );
}

/*==========================================================================*/
/**
 *  Get a field of view (FOV) parameter.
 *  @return FOV parameter
 */
/*==========================================================================*/
const float Camera::fieldOfView( void ) const
{
    return( m_field_of_view );
}

/*==========================================================================*/
/**
 *  Get a back parameter.
 *  @return back parameter
 */
/*==========================================================================*/
const float Camera::back( void ) const
{
    return( m_back );
}

/*==========================================================================*/
/**
 *  Get a front parameter.
 *  @return front parameter
 */
/*==========================================================================*/
const float Camera::front( void ) const
{
    return( m_front );
}

/*==========================================================================*/
/**
 *  Get a left parameter.
 *  @return left parameter
 */
/*==========================================================================*/
const float Camera::left( void ) const
{
    return( m_left );
}

/*==========================================================================*/
/**
 *  Get a right parameter.
 *  @return right parameter
 */
/*==========================================================================*/
const float Camera::right( void ) const
{
    return( m_right );
}

/*==========================================================================*/
/**
 *  Get a bottom parameter.
 *  @return bottom parameter
 */
/*==========================================================================*/
const float Camera::bottom( void ) const
{
    return( m_bottom );
}

/*==========================================================================*/
/**
 *  Get a top parameter.
 *  @return top parameter
 */
/*==========================================================================*/
const float Camera::top( void ) const
{
    return( m_top );
}

/*==========================================================================*/
/**
 *  Get the window width.
 */
/*==========================================================================*/
const size_t Camera::windowWidth( void ) const
{
    return( m_window_width );
}

/*==========================================================================*/
/**
 *  Get the window height.
 */
/*==========================================================================*/
const size_t Camera::windowHeight( void ) const
{
    return( m_window_height );
}

/*==========================================================================*/
/**
 *  Initialize the member parameters.
 */
/*==========================================================================*/
void Camera::initialize( void )
{
    m_projection_type = Camera::Perspective;

    const kvs::Vector3f init_pos( 0, 0, 12 );
    const kvs::Vector3f init_look_at( 0, 0, 0 );
    const kvs::Vector3f init_up( 0, 1, 0 );

    this->setPosition( init_pos, init_look_at, init_up );
    this->saveXform();
    m_transform_center = init_look_at;

    m_field_of_view = 45.0;
    m_front = 1.0;
    m_back = 2000.0;
    m_left = -5.0;
    m_right = 5.0;
    m_bottom = -5.0;
    m_top = 5.0;
    m_window_width = 512;
    m_window_height = 512;
}

/*==========================================================================*/
/**
 *  Update the camera.
 */
/*==========================================================================*/
void Camera::update( void )
{
    float ary[16];

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    kvs::Xform p( this->projectionMatrix() );
    p.toArray( ary );
    glMultMatrixf( ary );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    kvs::Xform v( this->viewingMatrix() );
    v.toArray( ary );
    glMultMatrixf( ary );
}

/*==========================================================================*/
/**
 *  Get a snapshot image.
 *  @return snapshot image
 */
/*==========================================================================*/
kvs::ColorImage Camera::snapshot( void )
{
    GLint viewport[4];
    glGetIntegerv( GL_VIEWPORT, viewport );

    const int width  = viewport[2];
    const int height = viewport[3];
//    const int size   = height * ( ( ( ( width * 3 ) + 3 ) >> 2 ) << 2 );
    const int size   = height * width * 3;
    kvs::ValueArray<kvs::UInt8> buffer( size );

    glPixelStorei( GL_PACK_ALIGNMENT, 1 );
    glReadPixels( 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data() );

    kvs::ColorImage ret( width, height, buffer );
    ret.flip();
    return ret;
}

const kvs::Matrix44f Camera::projectionMatrix( void ) const
{
    const float aspect = static_cast<float>( m_window_width ) / m_window_height;

    if ( m_projection_type == Camera::Perspective )
    {
        return kvs::PerspectiveMatrix44<float>( m_field_of_view, aspect, m_front, m_back );
    }
    else if ( m_projection_type == Camera::Orthogonal )
    {
        // Orthogonal camera mode
        if ( aspect >= 1.0f )
        {
            return kvs::OrthogonalMatrix44<float>( 
                m_left * aspect, 
                m_right * aspect, 
                m_bottom, m_top, 
                m_front, m_back );
        }
        else
        {
            return kvs::OrthogonalMatrix44<float>( 
                m_left, m_right, 
                m_bottom / aspect, m_top / aspect, 
                m_front, m_back );
        }
    }
    else
    {
        // Frustum camera mode
        if ( aspect >= 1.0f )
        {
            return kvs::FrustumMatrix44<float>( 
                m_left * aspect, m_right * aspect, 
                m_bottom, m_top, 
                m_front, m_back );
        }
        else
        {
            return kvs::FrustumMatrix44<float>( 
                m_left, m_right, 
                m_bottom / aspect, m_top / aspect, 
                m_front, m_back );
        }
    }
}

const kvs::Matrix44f Camera::modelViewMatrix( void ) const
{
    float m[16];
    this->getModelViewMatrix( &m );
    return kvs::Xform::FromArray( m ).toMatrix();
}

const kvs::Matrix44f Camera::projectionModelViewMatrix( void ) const
{
    return this->projectionMatrix() * this->modelViewMatrix();
}

void Camera::getProjectionModelViewMatrix( float (*projection_modelview)[16] ) const
{
    kvs::Matrix44f M = this->modelViewMatrix();
    kvs::Matrix44f P = this->projectionMatrix();
    kvs::Xform x( P * M );
    x.toArray( *projection_modelview );
}

void Camera::getProjectionModelViewMatrix(
    const float projection[16],
    const float modelview[16],
    float (*projection_modelview)[16] ) const
{
    kvs::Xform M = kvs::Xform::FromArray( modelview );
    kvs::Xform P = kvs::Xform::FromArray( projection );
    kvs::Xform x = P * M;
    x.toArray( *projection_modelview );
}

/*==========================================================================*/
/**
 *  Get a projection matrix.
 *  @param  projection [out] projection matrix
 */
/*==========================================================================*/
void Camera::getProjectionMatrix( float (*projection)[16] ) const
{
    glGetFloatv( GL_PROJECTION_MATRIX, (GLfloat*)*projection );
}

/*==========================================================================*/
/**
 *  Get a modelview matrix.
 *  @param  modelview [out] modelview matrix
 */
/*==========================================================================*/
void Camera::getModelViewMatrix( float (*modelview)[16] ) const
{
    glGetFloatv( GL_MODELVIEW_MATRIX, (GLfloat*)*modelview );
}

/*==========================================================================*/
/**
 *  Get a combined matrix (<projection matrix> x <modelview matrix>).
 *  @param  combined [out] combined matrix
 */
/*==========================================================================*/
void Camera::getCombinedMatrix( float (*combined)[16] ) const
{
    this->getProjectionModelViewMatrix( combined );
}

/*==========================================================================*/
/**
 *  Get a combined matrix (<projection matrix> x <modelview matrix>).
 *  @param projection [in] projection matrix
 *  @param modelview [in] modelview matrix
 *  @param  combined   [out] combined matrix
 */
/*==========================================================================*/
void Camera::getCombinedMatrix(
    const float projection[16],
    const float modelview[16],
    float (*combined)[16] ) const
{
    this->getProjectionModelViewMatrix( projection, modelview, combined );
}

/*==========================================================================*/
/**
 *  Get a coordinate value in the window coordinate system.
 *  @param p_obj_x [in] x coordinate value in the object coordinate system
 *  @param p_obj_y [in] y coordinate value in the object coordinate system
 *  @param p_obj_z [in] z coordinate value in the object coordinate system
 *  @param  depth   [out] depth value of projected point
 *  @return projected coordinate value in the window coordinate system
 *
 *  Same as gluProject() in OpenGL.
 */
/*==========================================================================*/
const kvs::Vector2f Camera::projectObjectToWindow(
    float  p_obj_x,
    float  p_obj_y,
    float  p_obj_z,
    float* depth ) const
{
    return this->projectObjectToWindow( kvs::Vector3f( p_obj_x, p_obj_y, p_obj_z ), depth );
}

/*==========================================================================*/
/**
 *  Get a coordinate value in the window coordinate system.
 *  @param p_obj [in] coordinate value in the object coordinate system
 *  @param  depth [out] depth value of projected point
 *  @return projected coordinate value in the window coordinate system
 *
 *  Same as gluProject() in OpenGL.
 */
/*==========================================================================*/
const kvs::Vector2f Camera::projectObjectToWindow(
    const kvs::Vector3f& p_obj,
    float*               depth ) const
{
    const kvs::Xform pvm( this->projectionModelViewMatrix() );
    const kvs::Vector3f p = pvm.project( p_obj );

    if ( depth ) *depth = ( 1.0f + p[2] ) * 0.5f;

    return kvs::Vector2f( ( 1.0f + p[0] ) * m_window_width * 0.5f,
                          ( 1.0f + p[1] ) * m_window_height * 0.5f );
}

/*==========================================================================*/
/**
 *  Get a coordinate value in the object coordinate system.
 *  @param p_win [in] point in the window coordinate system
 *  @param depth [in] depth value
 *  @return point in the object coordinate system
 */
/*==========================================================================*/
const kvs::Vector3f Camera::projectWindowToObject(
    const kvs::Vector2f& p_win,
    float                depth ) const
{
    return this->projectCameraToObject( this->projectWindowToCamera( p_win, depth ) );
}

/*==========================================================================*/
/**
 *  Get a point in the camera coordinate system.
 *  @param p_win [in] a point in the window coordinate system.
 *  @param depth [in] depth value
 *  @return point in the object coordinate system.
 */
/*==========================================================================*/
const kvs::Vector3f Camera::projectWindowToCamera(
    const kvs::Vector2f& p_win,
    float                depth ) const
{
    GLdouble m[16] = { 1.0, 0.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0,
                       0.0, 0.0, 1.0, 0.0,
                       0.0, 0.0, 0.0, 1.0 };

    GLdouble p[16]; glGetDoublev(  GL_PROJECTION_MATRIX, p );
    GLint    v[4];  glGetIntegerv( GL_VIEWPORT,          v );

    double x = 0;
    double y = 0;
    double z = 0;
    gluUnProject( p_win.x(), p_win.y(), depth,
                  m,
                  p,
                  v,
                  &x, &y, &z );

    return( kvs::Vector3f( (float)x, (float)y, (float)z ) );
}

/*==========================================================================*/
/**
 *  Get a point in the world coordinate system.
 *  @param win [in] point in the window coordinate system
 *  @param depth [in] depth value
 *  @return a point in the world coordinate system
 */
/*==========================================================================*/
const kvs::Vector3f Camera::projectWindowToWorld(
    const kvs::Vector2f& p_win,
    float                depth ) const
{
    return this->projectCameraToWorld( this->projectWindowToCamera( p_win, depth ) );
}

/*==========================================================================*/
/**
 *  Get a point in the camera coodinate system.
 *  @param p_obj [in] point in the object coordinate system
 *  @return point in the object coordinate system
 */
/*==========================================================================*/
const kvs::Vector3f Camera::projectObjectToCamera(
    const kvs::Vector3f& p_obj ) const
{
    const kvs::Xform modelview( this->modelViewMatrix() );
    return modelview.transform( p_obj );
}

/*==========================================================================*/
/**
 *  Get a point in the object coordinate system.
 *  @param p_cam [in] point in the camera coordinate system
 *  @return point in the object coordinate system
 */
/*==========================================================================*/
const kvs::Vector3f Camera::projectCameraToObject(
    const kvs::Vector3f& p_cam ) const
{
    const kvs::Xform modelview( this->modelViewMatrix() );
    return modelview.inverse().transform( p_cam );
}

/*==========================================================================*/
/**
 *  Get a point in the camera coordinate system.
 *  @param p_wld [in] point in the world coordinate system
 *  @return point in the camera coordinate system
 */
/*==========================================================================*/
const kvs::Vector3f Camera::projectWorldToCamera( const kvs::Vector3f& p_wld ) const
{
    const kvs::Xform viewing( this->viewingMatrix() );
    return viewing.transform( p_wld );
}

/*==========================================================================*/
/**
 *  Get a point in the world coordinate system.
 *  @param p_cam [in] point in the camera coordinate system
 *  @return point in the world coordinate system
 */
/*==========================================================================*/
const kvs::Vector3f Camera::projectCameraToWorld( const kvs::Vector3f& p_cam ) const
{
    const kvs::Xform inv_viewing( this->xform() );
    return inv_viewing.transform( p_cam );
}

/*==========================================================================*/
/**
 *  Get a point in the object coordinate system.
 *  @param p_wld [in] point in the world coordinate system
 *  @return point in the object coordinate system
 */
/*==========================================================================*/
const kvs::Vector3f Camera::projectWorldToObject( const kvs::Vector3f& p_wld ) const
{
    const kvs::Xform inv_modeling( this->modelViewMatrix().inverted() * this->viewingMatrix() );
    return inv_modeling.transform( p_wld );
}

/*==========================================================================*/
/**
 *  Get a point in the world coordinate system.
 *  @param p_obj [in] point in the object coordinate system
 *  @return point in the world coordinate system
 */
/*==========================================================================*/
const kvs::Vector3f Camera::projectObjectToWorld( const kvs::Vector3f& p_obj ) const
{
    const kvs::Xform modeling( this->xform().toMatrix() * this->modelViewMatrix() );
    return modeling.transform( p_obj );
}

/*===========================================================================*/
/**
 *  @brief  Resets the xform of the camera.
 */
/*===========================================================================*/
void Camera::resetXform( void )
{
    kvs::XformControl::resetXform();
    m_transform_center.set( 0, 0, 0 );
}

/*==========================================================================*/
/**
 *  Rotate the camera.
 *  @param rot [in] rotation matrix.
 */
/*==========================================================================*/
void Camera::rotate( const kvs::Matrix33f& rotation )
{
    const kvs::Vector3f t = m_transform_center;
    const kvs::Xform x = kvs::Xform::Translation( t )
                       * kvs::Xform::Rotation( rotation )
                       * kvs::Xform::Translation( -t );
    this->multiplyXform( x );
}

/*==========================================================================*/
/**
 *  Translate the camera.
 *  @param translation [in] translation vector
 */
/*==========================================================================*/
void Camera::translate( const kvs::Vector3f& translation )
{
    this->multiplyXform( kvs::Xform::Translation( translation ) );
    m_transform_center += translation;
}

/*==========================================================================*/
/**
 *  Scale the camera.
 *  @param scaling [in] scaling vector
 */
/*==========================================================================*/
void Camera::scale( const kvs::Vector3f& scaling )
{
    this->multiplyXform( kvs::Xform::Scaling( scaling ) );
}

} // end of namespace kvs
