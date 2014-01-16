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
#include <kvs/VisualizationPipeline>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new Scene class.
 */
/*===========================================================================*/
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

/*===========================================================================*/
/**
 *  @brief  Destroys the Scene class.
 */
/*===========================================================================*/
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
 *  @brief  Registers an object with a renderer.
 *  @param  object [in] pointer to the object
 *  @param  renderer [in] pointer to the renderer
 *  @return Pair of IDs (object ID and renderer ID)
 */
/*===========================================================================*/
const std::pair<int,int> Scene::registerObject( kvs::ObjectBase* object, kvs::RendererBase* renderer )
{
    // If the given pointer to the renderer is null, a renderer for the given
    // object is automatically created by using visualization pipeline class.
    if ( !renderer )
    {
        kvs::VisualizationPipeline pipeline( object );
        if ( !pipeline.exec() )
        {
            kvsMessageError("Cannot create a renderer for the given object.");
            return std::pair<int,int>( -1, -1 );
        }

        renderer = const_cast<kvs::RendererBase*>( pipeline.renderer() );
    }

    if ( !object->hasMinMaxObjectCoords() )
    {
        object->updateMinMaxCoords();
    }

    // If the object has not been registered in the object managet,
    // the object is registered and then its ID is returned.
    int object_id = m_object_manager->objectID( object );
    if ( object_id == -1 ) object_id = m_object_manager->insert( object );

    // If the renderer has not been registered in the renderer managet,
    // the renderer is registered and then its ID is returned.
    int renderer_id = m_renderer_manager->rendererID( renderer );
    if ( renderer_id == -1 ) renderer_id = m_renderer_manager->insert( renderer );

    // Insert the IDs into the ID manager.
    m_id_manager->insert( object_id, renderer_id );

    return std::pair<int,int>( object_id, renderer_id );
}

/*===========================================================================*/
/**
 *  @brief  Removes the object specified by the given object ID.
 *  @param  object_id [in] object ID
 *  @param  delete_object [in] if true, the object will be deleted
 *  @param  delete_renderer [in] if true, the renderers for the object will be deleted
 */
/*===========================================================================*/
void Scene::removeObject( int object_id, bool delete_object, bool delete_renderer )
{
    // Remove the object specified by the given object ID for the object manager.
    m_object_manager->erase( object_id, delete_object );

    // Remove the all of renderers assigned for the specified object from
    // the renderer manager.
    const std::vector<int> renderer_ids = m_id_manager->rendererID( object_id );
    for ( size_t i = 0; i < renderer_ids.size(); i++ )
    {
        m_renderer_manager->erase( renderer_ids[i], delete_renderer );
    }

    // Remove IDs specified by the given object ID from the ID manager.
    m_id_manager->eraseByObjectID( object_id );
}

/*===========================================================================*/
/**
 *  @brief  Removes the object specified by the given object name.
 *  @param  object_name [in] object name
 *  @param  delete_object [in] if true, the registered object will be deleted
 *  @param  delete_renderer [in] if true, the registered renderers for the object will be deleted
 */
/*===========================================================================*/
void Scene::removeObject( std::string object_name, bool delete_object, bool delete_renderer )
{
    const kvs::ObjectBase* object = m_object_manager->object( object_name );
    const int object_id = m_object_manager->objectID( object );
    this->removeObject( object_id, delete_object, delete_renderer );
}

/*===========================================================================*/
/**
 *  @brief  Replaces the object specified by the given object ID with the input object.
 *  @param  object_id [in] object ID
 *  @param  object [in] pointer to the object will be registered
 *  @param  delete_object [in] if true, the registered object will be deleted
 */
/*===========================================================================*/
void Scene::replaceObject( int object_id, kvs::ObjectBase* object, bool delete_object )
{
    m_object_manager->change( object_id, object, delete_object );
}

/*===========================================================================*/
/**
 *  @brief  Replaces the object specified by the given object name with the input object.
 *  @param  object_id [in] object name
 *  @param  object [in] pointer to the object will be registered
 *  @param  delete_object [in] if true, the registered object will be deleted
 */
/*===========================================================================*/
void Scene::replaceObject( std::string object_name, kvs::ObjectBase* object, bool delete_object )
{
    m_object_manager->change( object_name, object, delete_object );
}

/*===========================================================================*/
/**
 *  @brief  Replaces the renderer specified by the given renderer ID with the input renderer.
 *  @param  renderer_id [in] renderer ID
 *  @param  renderer [in] pointer to the renderer will be registered
 *  @param  delete_renderer [in] if true, the registered renderer will be deleted
 */
/*===========================================================================*/
void Scene::replaceRenderer( int renderer_id, kvs::RendererBase* renderer, bool delete_renderer )
{
    m_renderer_manager->change( renderer_id, renderer, delete_renderer );
}

/*===========================================================================*/
/**
 *  @brief  Replaces the renderer specified by the given renderer name with the input renderer.
 *  @param  renderer_name [in] renderer name
 *  @param  renderer [in] pointer to the renderer will be registered
 *  @param  delete_renderer [in] if true, the registered renderer will be deleted
 */
/*===========================================================================*/
void Scene::replaceRenderer( std::string renderer_name, kvs::RendererBase* renderer, bool delete_renderer )
{
    m_renderer_manager->change( renderer_name, renderer, delete_renderer );
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
    if ( m_object_manager->hasActiveObject() )
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
    if ( !m_object_manager->hasObject() ) return true;

    if ( m_target == TargetObject )
    {
        if ( !m_enable_move_all && m_enable_collision_detection )
        {
            const float px = static_cast<float>(x);
            const float py = static_cast<float>(y);
            const kvs::Vector2f p = kvs::Vector2f( px, py );
            return m_object_manager->detectCollision( p, m_camera );
        }
    }

    return true;
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
    if ( m_target == TargetObject )
    {
        if ( m_enable_move_all )
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
    kvs::Vec2 center( 0.0, 0.0 );

    switch ( m_target )
    {
    case TargetCamera:
    case TargetLight:
        // Get an at-point of the camera, which is the center of rotation,
        // in the device coord.
        center = m_camera->lookAtInDevice();
        break;
    case TargetObject:
        if ( m_enable_move_all || !m_object_manager->hasObject() )
        {
            center = m_object_manager->positionInDevice( m_camera );
        }
        else
        {
            // If the object manager has no active object, the center
            // of rotation is not updated.
            if ( !m_object_manager->hasActiveObject() ) return;

            kvs::ObjectBase* object = m_object_manager->activeObject();
            const kvs::Vec3& t = m_object_manager->objectCenter();
            const kvs::Vec3& s = m_object_manager->normalize();
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
    switch ( m_target )
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
    switch ( m_mouse->mode() )
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
    switch ( m_mouse->mode() )
    {
    case kvs::Mouse::Rotation:
        camera->rotate( m_mouse->rotation().toMatrix().transposed() );
        break;
    case kvs::Mouse::Translation:
        camera->translate( -m_mouse->translation() );
        break;
    case kvs::Mouse::Scaling:
    {
        const kvs::Vec3 s = m_mouse->scaling();
        camera->scale( kvs::Vec3( 1 / s.x(), 1 / s.y(), 1 / s.z() ) );
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
    switch ( m_mouse->mode() )
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
        const kvs::Vec3 center = m_object_manager->objectCenter();
        const kvs::Vec3 scale = m_object_manager->normalize();
        const int size = m_id_manager->size();
        for ( int index = 0; index < size; index++ )
        {
            kvs::IDManager::IDPair id = m_id_manager->id( index );
            kvs::ObjectBase* object = m_object_manager->object( id.first );
            kvs::RendererBase* renderer = m_renderer_manager->renderer( id.second );
            if ( object->isShown() )
            {
                kvs::OpenGL::PushMatrix();
                object->transform( center, scale );
                renderer->exec( object, m_camera, m_light );
                kvs::OpenGL::PopMatrix();
            }
        }
    }
    else
    {
        float array[16];
        m_object_manager->xform().toArray( array );
        kvs::OpenGL::MultMatrix( array );
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
    kvs::OpenGL::SetViewport( 0, 0, width, height );

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

    if ( !( m_mouse->isUseAuto() && m_mouse->isAuto() ) )
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

} // end of namespace kvs
