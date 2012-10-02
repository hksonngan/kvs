/*****************************************************************************/
/**
 *  @file   Scene.cpp
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
#include "Scene.h"
#include <kvs/OpenGL>
#include <kvs/Camera>
#include <kvs/Light>
#include <kvs/Mouse>
#include <kvs/Background>
#include <kvs/ObjectManager>
#include <kvs/RendererManager>
#include <kvs/IDManager>
#include <kvs/ObjectBase>
#include <kvs/RendererBase>


namespace kvs
{

Scene::Scene():
    m_target( Scene::TargetObject ),
    m_enable_move_all( true ),
    m_enable_collision_detection( false )
{
    m_camera = new kvs::Camera();
    m_light = new kvs::Light();
    m_mouse = new kvs::Mouse();
    m_background = new kvs::Background( kvs::RGBColor( 212, 221, 229 ) );
    m_object_manager = new kvs::ObjectManager();
    m_renderer_manager = new kvs::RendererManager();
    m_id_manager = new kvs::IDManager();
}

Scene::~Scene()
{
    delete m_camera;
    delete m_light;
    delete m_mouse;
    delete m_background;
    delete m_object_manager;
    delete m_renderer_manager;
    delete m_id_manager;
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the camera.
 *  @return pointer to the camera
 */
/*===========================================================================*/
kvs::Camera* Scene::camera()
{
    return( m_camera );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the light.
 *  @return pointer to the light
 */
/*===========================================================================*/
kvs::Light* Scene::light()
{
    return( m_light );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the mouse.
 *  @return pointer to the mouse
 */
/*===========================================================================*/
kvs::Mouse* Scene::mouse()
{
    return( m_mouse );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the background class.
 *  @return pointer to the background class
 */
/*===========================================================================*/
kvs::Background* Scene::background()
{
    return( m_background );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the object manager.
 *  @return pointer to the object manager
 */
/*===========================================================================*/
kvs::ObjectManager* Scene::objectManager()
{
    return( m_object_manager );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the renderer manager.
 *  @return pointer to the renderer manager
 */
/*===========================================================================*/
kvs::RendererManager* Scene::rendererManager()
{
    return( m_renderer_manager );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the ID manager.
 *  @return pointer to the ID manager
 */
/*===========================================================================*/
kvs::IDManager* Scene::IDManager()
{
    return( m_id_manager );
}

/*===========================================================================*/
/**
 *  @brief  Returns the control target.
 *  @return control target
 */
/*===========================================================================*/
Scene::ControlTarget& Scene::controlTarget()
{
    return( m_target );
}

/*==========================================================================*/
/**
 *  @brief  Initalizes the screen.
 */
/*==========================================================================*/
void Scene::initializeFunction()
{
    // Set the lighting parameters.
    m_light->on();

    // Attach the Camera to the Mouse
    m_mouse->attachCamera( m_camera );
}

/*==========================================================================*/
/**
 *  @brief  Core paint event function.
 */
/*==========================================================================*/
void Scene::paintFunction()
{
    // Update the camera and light.
    m_camera->update();
    m_light->update( m_camera );

    // Set the background color or image.
    m_background->apply();

    // Rendering the resistered object by using the corresponding renderer.
    if ( m_object_manager->hasObject() )
    {
        const int size = m_id_manager->size();
        for ( int index = 0; index < size; index++ )
        {
            kvs::IDManager::IDPair id_pair = (*m_id_manager)[index];
            kvs::ObjectBase* object = m_object_manager->object( id_pair.first );
            kvs::RendererBase* renderer = m_renderer_manager->renderer( id_pair.second );

            if ( object->isShown() )
            {
                glPushMatrix();
                object->transform( m_object_manager->objectCenter(), m_object_manager->normalize() );
                renderer->exec( object, m_camera, m_light );
                glPopMatrix();
            }
        }
    }
    else
    {
        float array[16];
        m_object_manager->xform().toArray( array );
        glMultMatrixf( array );
    }
}

/*==========================================================================*/
/**
 *  @brief  Core resize event function.
 *  @param  width [in] screen width
 *  @param  height [in] screen height
 */
/*==========================================================================*/
void Scene::resizeFunction( int width, int height )
{
    // Update the viewport for OpenGL.
    glViewport( 0 , 0 , width , height );

    // Update the window size for camera and mouse.
    m_camera->setWindowSize( width, height );
    m_mouse->setWindowSize( width, height );
}

/*==========================================================================*/
/**
 *  @brief  Function which is called when the mouse button is released.
 *  @param  x [in] x coordinate value of the mouse cursor position
 *  @param  y [in] y coordinate value of the mouse cursor position
 */
/*==========================================================================*/
void Scene::mouseReleaseFunction( int x, int y )
{
    m_enable_move_all = true;
    m_enable_collision_detection = false;
    m_mouse->release( x, y );

    if( !( m_mouse->isUseAuto() && m_mouse->isAuto() ) )
    {
        m_object_manager->releaseActiveObject();
    }
}

/*==========================================================================*/
/**
 *  @brief  Function which is called when the mouse button is released.
 *  @param  x [in] x coordinate value of the mouse cursor position
 *  @param  y [in] y coordinate value of the mouse cursor position
 *  @param  mode [in] mouse translation mode
 */
/*==========================================================================*/
void Scene::mousePressFunction( int x, int y, kvs::Mouse::TransMode mode )
{
    if ( m_enable_move_all || m_object_manager->hasActiveObject() )
    {
        this->updateControllingObject();
        m_mouse->setMode( mode );
        m_mouse->press( x, y );
    }
}

/*==========================================================================*/
/**
 *  @brief  Function which is called when the mouse cursor is moved.
 *  @param  x [in] x coordinate value of the mouse cursor position
 *  @param  y [in] y coordinate value of the mouse cursor position
 */
/*==========================================================================*/
void Scene::mouseMoveFunction( int x, int y )
{
    if ( m_enable_move_all || m_object_manager->hasActiveObject() )
    {
        m_mouse->move( x, y );
        this->updateXform();
    }
}

/*===========================================================================*/
/**
 *  @brief  Function which is called when the mouse wheel is scrolled.
 *  @param  value [in] incremental value
 */
/*===========================================================================*/
void Scene::wheelFunction( int value )
{
    if ( m_enable_move_all || m_object_manager->hasActiveObject() )
    {
        this->updateControllingObject();
        m_mouse->setMode( kvs::Mouse::Scaling );
        m_mouse->press( 0, 0 );
        m_mouse->move( 0, value );
    }
}

/*===========================================================================*/
/**
 *  @brief  Resets the x-form matrix of the basic screen components.
 */
/*===========================================================================*/
void Scene::reset()
{
    // Reset viewpoint to the initial position.
    m_mouse->reset();

    // Reset the xform of the object.
    if( m_object_manager->hasActiveObject() )
    {
        m_object_manager->resetActiveObjectXform();
    }
    else
    {
        m_object_manager->resetXform();
    }

    // Reset the xform of the camera.
    m_camera->resetXform();

    // Reset the xform of the light.
    m_light->resetXform();
}

/*==========================================================================*/
/**
 *  @brief  Test whether the screen is the active move mode.
 *  @param  x [in] x coordinate value of the mouse cursor position
 *  @param  y [in] y coordinate value of the mouse cursor position
 *  @return true, if the screen is the active move mode
 */
/*==========================================================================*/
bool Scene::isActiveMove( int x, int y )
{
    if( !m_object_manager->hasObject() ) return( true );

    if( m_target == TargetObject )
    {
        if( !m_enable_move_all && m_enable_collision_detection )
        {
            const float px = static_cast<float>(x);
            const float py = static_cast<float>(y);
            const kvs::Vector2f p = kvs::Vector2f( px, py );
            return( m_object_manager->detectCollision( p, m_camera ) );
        }
    }

    return( true );
}

/*==========================================================================*/
/**
 *  @brief  Disable move-all mode.
 */
/*==========================================================================*/
void Scene::disableAllMove()
{
    m_enable_move_all = false;
}

/*==========================================================================*/
/**
 *  @brief  Enable move-all mode.
 */
/*==========================================================================*/
void Scene::enableAllMove()
{
    m_enable_move_all = true;
}

/*===========================================================================*/
/**
 *  @brief  Disable collision detection mode.
 */
/*===========================================================================*/
void Scene::disableCollisionDetection()
{
    m_enable_collision_detection = false;
}

/*===========================================================================*/
/**
 *  @brief  Enable collision detection mode.
 */
/*===========================================================================*/
void Scene::enableCollisionDetection()
{
    m_enable_move_all = false;
    m_enable_collision_detection = true;
}

/*==========================================================================*/
/**
 *  @brief  Updates the controlling object.
 */
/*==========================================================================*/
void Scene::updateControllingObject()
{
    if( m_target == TargetObject )
    {
        if( m_enable_move_all )
        {
            m_object_manager->enableAllMove();
            m_object_manager->releaseActiveObject();
        }
        else
        {
            m_object_manager->disableAllMove();
        }
    }
}

/*==========================================================================*/
/**
 *  @brief  Updates the center of rotation.
 */
/*==========================================================================*/
void Scene::updateCenterOfRotation()
{
    // Center of rotation in the device coordinate system.
    kvs::Vector2f center( 0.0, 0.0 );

    switch( m_target )
    {
    case TargetCamera:
    case TargetLight:
        /* Get an at-point of the camera, which is the center of rotation,
         * in the device coord.
         */
        center = m_camera->lookAtInDevice();
        break;
    case TargetObject:
        if( m_enable_move_all || !m_object_manager->hasObject() )
        {
            center = m_object_manager->positionInDevice( m_camera );
        }
        else
        {
            /* If the object manager has no active object, the center
             * of rotation is not updated.
             */
            if ( !m_object_manager->hasActiveObject() ) return;

            kvs::ObjectBase* object = m_object_manager->activeObject();
            const kvs::Vector3f& t = m_object_manager->objectCenter();
            const kvs::Vector3f& s = m_object_manager->normalize();
            center = object->positionInDevice( m_camera, t, s );
        }
        break;
    default:
        break;
    }

    m_mouse->setRotationCenter( center );
}

/*==========================================================================*/
/**
 *  @brief  Updates the xform of the control target.
 */
/*==========================================================================*/
void Scene::updateXform()
{
    switch( m_target )
    {
    case TargetCamera:
        this->updateXform( m_camera );
        break;
    case TargetLight:
        this->updateXform( m_light );
        break;
    case TargetObject:
        this->updateXform( m_object_manager );
        break;
    default:
        break;
    }
}

/*==========================================================================*/
/**
 *  @brief  Updates the xform of the object manager.
 *  @param  manager [in] pointer to the object manager
 */
/*==========================================================================*/
void Scene::updateXform( kvs::ObjectManager* manager )
{
    switch( m_mouse->mode() )
    {
    case kvs::Mouse::Rotation:
        manager->rotate( m_mouse->rotation().toMatrix() );
        break;
    case kvs::Mouse::Translation:
        manager->translate( m_mouse->translation() );
        break;
    case kvs::Mouse::Scaling:
        manager->scale( m_mouse->scaling() );
        break;
    default:
        break;
    }
}

/*==========================================================================*/
/**
 *  @brief  Updates the xform of the camera.
 *  @param  camera [in] pointer to the camera
 */
/*==========================================================================*/
void Scene::updateXform( kvs::Camera* camera )
{
    switch( m_mouse->mode() )
    {
    case kvs::Mouse::Rotation:
        camera->rotate( m_mouse->rotation().toMatrix().transpose() );
        break;
    case kvs::Mouse::Translation:
        camera->translate( -m_mouse->translation() );
        break;
    case kvs::Mouse::Scaling:
    {
        const kvs::Vector3f s = m_mouse->scaling();
        camera->scale( kvs::Vector3f( 1 / s.x(), 1 / s.y(), 1 / s.z() ) );
        break;
    }
    default:
        break;
    }
}

/*==========================================================================*/
/**
 *  @brief  Updates the xform of the light.
 *  @param  light [in] pointer to the light
 */
/*==========================================================================*/
void Scene::updateXform( kvs::Light* light )
{
    switch( m_mouse->mode() )
    {
    case kvs::Mouse::Rotation:
        light->rotate( m_mouse->rotation().toMatrix() );
        break;
    case kvs::Mouse::Translation:
        light->translate( m_mouse->translation() );
        break;
    case kvs::Mouse::Scaling:
        light->scale( m_mouse->scaling() );
        break;
    default:
        break;
    }
}

} // end of namespace kvs
