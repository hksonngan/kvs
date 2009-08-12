/****************************************************************************/
/**
 *  @file ScreenBase.cpp
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
#include "ScreenBase.h"
#include <kvs/PointRenderer>
#include <kvs/LineRenderer>
#include <kvs/PolygonRenderer>
#include <kvs/RayCastingRenderer>
#include <kvs/ImageRenderer>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new ScreenBase class.
 */
/*===========================================================================*/
ScreenBase::ScreenBase( void ):
    m_target( ScreenBase::TargetObject ),
    m_can_move_all( true )
{
    this->create();
}

/*===========================================================================*/
/**
 *  @brief  Destructs the ScreenBase class.
 */
/*===========================================================================*/
ScreenBase::~ScreenBase( void )
{
    this->clear();
}

/*===========================================================================*/
/**
 *  @brief  Registers an object with a renderer.
 *  @param  object [in] pointer to the object
 *  @param  renderer [in] pointer to the renderer
 */
/*===========================================================================*/
void ScreenBase::registerObject( kvs::ObjectBase* object, kvs::RendererBase* renderer )
{
    /* If the given pointer to the renderer is null, a renderer for the given
     * object is automatically created by using visualization pipeline class.
     */
    if ( !renderer )
    {
        kvs::VisualizationPipeline pipeline( object );
        if ( !pipeline.exec() )
        {
            kvsMessageError("Cannot create a renderer for the given object.");
            return;
        }

        renderer = const_cast<kvs::RendererBase*>( pipeline.renderer() );
    }

    const size_t renderer_id = m_renderer_manager->insert( renderer );
    const size_t object_id = m_object_manager->insert( object );
    m_id_manager->insert( object_id, renderer_id );
}

/*===========================================================================*/
/**
 *  @brief  Registers an object that is processed through the visualization pipeline.
 *  @param  pipeline [in] pointer to the visualization pipeline
 */
/*===========================================================================*/
void ScreenBase::registerObject( kvs::VisualizationPipeline* pipeline )
{
    /* WARNING: It is necessary to increment the reference counter of the
     * pipeline.object() and the pipeline.renderer().
     */
    kvs::ObjectBase* object = const_cast<kvs::ObjectBase*>( pipeline->object() );
    kvs::RendererBase* renderer = const_cast<kvs::RendererBase*>( pipeline->renderer() );

    const size_t object_id = m_object_manager->insert( object );
    const size_t renderer_id = m_renderer_manager->insert( renderer );
    m_id_manager->insert( object_id, renderer_id );
}

/*==========================================================================*/
/**
 *  @brief  Disable all-move mode.
 */
/*==========================================================================*/
void ScreenBase::disableAllMove( void )
{
    m_can_move_all = false;
}

/*==========================================================================*/
/**
 *  @brief  Initalizes the screen.
 */
/*==========================================================================*/
void ScreenBase::initializeFunction( void )
{
    // Set the lighting parameters.
    m_light->setID( GL_LIGHT0 );
    m_light->setPosition( 0.0, 0.0, 12.0 );
    m_light->setColor( 1.0, 1.0, 1.0 );
    m_light->on();

    // Attach the Camera to the Mouse
    m_mouse->attachCamera( m_camera );
}

/*==========================================================================*/
/**
 *  @brief  Core paint event function.
 */
/*==========================================================================*/
void ScreenBase::paintFunction( void )
{
    // Update the camera and light.
    m_camera->update();
    m_light->update();

    // Set the background color or image.
    m_background->apply();

    // Rendering the resistered object by using the corresponding renderer.
    if ( m_object_manager->hasObject() )
    {
        const int size = m_id_manager->size();
        for ( int index = 0; index < size; index++ )
        {
            kvs::IDPair id_pair = (*m_id_manager)[index];
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
    else m_object_manager->applyXform();
}

/*==========================================================================*/
/**
 *  @brief  Core resize event function.
 *  @param  width [in] screen width
 *  @param  height [in] screen height
 */
/*==========================================================================*/
void ScreenBase::resizeFunction( int width, int height )
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
void ScreenBase::mouseReleaseFunction( int x, int y )
{
    m_can_move_all = true;
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
void ScreenBase::mousePressFunction( int x, int y, kvs::Mouse::TransMode mode )
{
    this->updateControllingObject();

    m_mouse->setMode( mode );
    m_mouse->press( x, y );
}

/*===========================================================================*/
/**
 *  @brief  Function which is called when the mouse wheel is scrolled.
 *  @param  value [in] incremental value
 */
/*===========================================================================*/
void ScreenBase::wheelFunction( int value )
{
    this->updateControllingObject();

    m_mouse->setScalingType( kvs::Mouse::ScalingXYZ );
    m_mouse->wheel( value );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the camera.
 *  @return pointer to the camera
 */
/*===========================================================================*/
kvs::Camera* ScreenBase::camera( void )
{
    return( m_camera );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the light.
 *  @return pointer to the light
 */
/*===========================================================================*/
kvs::Light* ScreenBase::light( void )
{
    return( m_light );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the mouse.
 *  @return pointer to the mouse
 */
/*===========================================================================*/
kvs::Mouse* ScreenBase::mouse( void )
{
    return( m_mouse );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the background class.
 *  @return pointer to the background class
 */
/*===========================================================================*/
kvs::Background* ScreenBase::background( void )
{
    return( m_background );
}

/*===========================================================================*/
/**
 *  @brief  Returns the control target.
 *  @return control target
 */
/*===========================================================================*/
kvs::ScreenBase::ControlTarget& ScreenBase::controlTarget( void )
{
    return( m_target );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the object manager.
 *  @return pointer to the object manager
 */
/*===========================================================================*/
kvs::ObjectManager* ScreenBase::objectManager( void )
{
    return( m_object_manager );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the renderer manager.
 *  @return pointer to the renderer manager
 */
/*===========================================================================*/
kvs::RendererManager* ScreenBase::rendererManager( void )
{
    return( m_renderer_manager );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the ID manager.
 *  @return pointer to the ID manager
 */
/*===========================================================================*/
kvs::IDManager* ScreenBase::IDManager( void )
{
    return( m_id_manager );
}

/*===========================================================================*/
/**
 *  @brief  Creates basic screen components.
 */
/*===========================================================================*/
void ScreenBase::create( void )
{
    m_camera = new kvs::Camera();
    if ( !m_camera )
    {
        kvsMessageError("Cannot allocate memory for the camera.");
        return;
    }

    m_light = new kvs::Light();
    if ( !m_light )
    {
        kvsMessageError("Cannot allocate memory for the light.");
        return;
    }

    m_mouse = new kvs::Mouse();
    if ( !m_mouse )
    {
        kvsMessageError("Cannot allocate memory for the mouse.");
        return;
    }

    m_background = new kvs::Background( kvs::RGBColor( 212, 221, 229 ) );
    if ( !m_background )
    {
        kvsMessageError("Cannot allocate memory for the background.");
        return;
    }

    m_object_manager = new kvs::ObjectManager();
    if ( !m_object_manager )
    {
        kvsMessageError("Cannot allocate memory for the object manager.");
        return;
    }

    m_renderer_manager = new kvs::RendererManager();
    if( !m_renderer_manager )
    {
        kvsMessageError("Cannot allocate memory for the renderer manager.");
        return;
    }

    m_id_manager = new kvs::IDManager();
    if( !m_id_manager )
    {
        kvsMessageError("Cannot allocate memory for the ID manager.");
        return;
    }
}

/*===========================================================================*/
/**
 *  @brief  Clears the basic screen components.
 */
/*===========================================================================*/
void ScreenBase::clear( void )
{
    if ( m_camera           ) { delete m_camera;           m_camera           = NULL; }
    if ( m_light            ) { delete m_light;            m_light            = NULL; }
    if ( m_mouse            ) { delete m_mouse;            m_mouse            = NULL; }
    if ( m_background       ) { delete m_background;       m_background       = NULL; }
    if ( m_object_manager   ) { delete m_object_manager;   m_object_manager   = NULL; }
    if ( m_renderer_manager ) { delete m_renderer_manager; m_renderer_manager = NULL; }
    if ( m_id_manager       ) { delete m_id_manager;       m_id_manager       = NULL; }
}

/*===========================================================================*/
/**
 *  @brief  Resets the x-form matrix of the basic screen components.
 */
/*===========================================================================*/
void ScreenBase::reset( void )
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
    m_camera->initialize();

    // Reset the xform of the light.
    m_light->resetXform();
    m_light->initialize();
}

/*==========================================================================*/
/**
 *  @brief  Test whether the screen is the active move mode.
 *  @param  x [in] x coordinate value of the mouse cursor position
 *  @param  y [in] y coordinate value of the mouse cursor position
 *  @return true, if the screen is the active move mode
 */
/*==========================================================================*/
bool ScreenBase::isActiveMove( int x, int y )
{
    if( !m_object_manager->hasObject() ) return( true );

    if( m_target == TargetObject )
    {
        if( !m_can_move_all )
        {
            // Collision detection.
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
 *  @brief  Updates the controlling object.
 */
/*==========================================================================*/
void ScreenBase::updateControllingObject( void )
{
    if( m_target == TargetObject )
    {
        if( m_can_move_all )
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
void ScreenBase::updateCenterOfRotation( void )
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
        if( m_can_move_all || !m_object_manager->hasObject() )
        {
            center = m_object_manager->positionInDevice( m_camera );
        }
        else
        {
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
void ScreenBase::updateXform( void )
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
void ScreenBase::updateXform( kvs::ObjectManager* manager )
{
    switch( m_mouse->mode() )
    {
    case kvs::Mouse::Rotation:
        manager->rotate( m_mouse->rotation() );
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
void ScreenBase::updateXform( kvs::Camera* camera )
{
    switch( m_mouse->mode() )
    {
    case kvs::Mouse::Rotation:
        camera->rotate( m_mouse->rotation() );
        break;
    case kvs::Mouse::Translation:
        camera->translate( m_mouse->translation() );
        break;
    case kvs::Mouse::Scaling:
        camera->scale( m_mouse->scaling() );
        break;
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
void ScreenBase::updateXform( kvs::Light* light )
{
    switch( m_mouse->mode() )
    {
    case kvs::Mouse::Rotation:
        light->rotate( m_mouse->rotation() );
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
