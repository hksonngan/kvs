/****************************************************************************/
/**
 *  @file ScreenBase.h
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
#ifndef KVS__SCREEN_BASE_H_INCLUDE
#define KVS__SCREEN_BASE_H_INCLUDE

#include <string>
#include <kvs/Camera>
#include <kvs/Light>
#include <kvs/Mouse>
#include <kvs/Background>
#include <kvs/ObjectManager>
#include <kvs/RendererManager>
#include <kvs/IDManager>
#include <kvs/MouseEvent>
#include <kvs/KeyEvent>
#include <kvs/DisplayFormat>
#include <kvs/VisualizationPipeline>
#include <kvs/ClassName>
#include <kvs/IgnoreUnusedVariable>


namespace kvs
{

class EventHandler;

/*==========================================================================*/
/**
 *  Screen base class.
 */
/*==========================================================================*/
class ScreenBase
{
    kvsClassName( ScreenBase );

public:

    enum ControlTarget
    {
        TargetObject = 0, ///< controlling object
        TargetCamera,     ///< controlling camera
        TargetLight,      ///< controlling light
        NumberOfTargets   ///< number of control targets
    };

protected:

    // Basic components in the viewer.
    kvs::Camera*          m_camera;     ///< camera
    kvs::Light*           m_light;      ///< light
    kvs::Mouse*           m_mouse;      ///< mouse
    kvs::Background*      m_background; ///< background

    // Parameters for controlling the viewer.
    ControlTarget         m_target;           ///< control target
    kvs::ObjectManager*   m_object_manager;   ///< object manager
    kvs::RendererManager* m_renderer_manager; ///< renderer manager
    kvs::IDManager*       m_id_manager;       ///< ID manager ( object_id, renderer_id )

    bool m_enable_move_all;  ///< flag for object movement
    bool m_enable_collision_detection; ///< flag for collision detection

    kvs::EventHandler* m_event_handler; ///< event handler

public:

    ScreenBase( void );

    virtual ~ScreenBase( void );

public:

    virtual int show( void ) = 0;

public:

    void registerObject( kvs::ObjectBase* object, kvs::RendererBase* renderer = 0 );

    void registerObject( kvs::VisualizationPipeline* pipeline );

public:

    void initializeFunction( void );

    void paintFunction( void );

    void resizeFunction( int width, int height );

    void mouseReleaseFunction( int x, int y );

    void mousePressFunction( int x, int y, kvs::Mouse::TransMode mode );

    void mouseMoveFunction( int x, int y );

    void wheelFunction( int value );

public:

    kvs::Camera* camera( void );

    kvs::Light* light( void );

    kvs::Mouse* mouse( void );

    kvs::Background* background( void );

    kvs::ScreenBase::ControlTarget& controlTarget( void );

    kvs::ObjectManager* objectManager( void );

    kvs::RendererManager* rendererManager( void );

    kvs::IDManager* IDManager( void );

    kvs::EventHandler* eventHandler( void );

public:

    void create( void );

    void clear( void );

    void reset( void );

public:

    void disableAllMove( void );

    void enableAllMove( void );

    void disableCollisionDetection( void );

    void enableCollisionDetection( void );

    bool isActiveMove( int x, int y );

    void updateControllingObject( void );

    void updateCenterOfRotation( void );

    void updateXform( void );

    void updateXform( kvs::ObjectManager* manager );

    void updateXform( kvs::Camera* camera );

    void updateXform( kvs::Light* light );
};

} // end of namespace kvs

#endif // KVS__SCREEN_BASE_H_INCLUDE
