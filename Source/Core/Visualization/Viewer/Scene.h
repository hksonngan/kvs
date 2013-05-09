/*****************************************************************************/
/**
 *  @file   Scene.h
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
#ifndef KVS__SCENE_H_INCLUDE
#define KVS__SCENE_H_INCLUDE

#include <kvs/Mouse>


namespace kvs
{

class Camera;
class Light;
class Mouse;
class Background;
class ObjectManager;
class RendererManager;
class IDManager;

/*===========================================================================*/
/**
 *  @brief  Default scene class.
 */
/*===========================================================================*/
class Scene
{
public:

    enum ControlTarget
    {
        TargetObject = 0, ///< controlling object
        TargetCamera, ///< controlling camera
        TargetLight, ///< controlling light
        NumberOfTargets ///< number of control targets
    };

private:

    kvs::Camera* m_camera; ///< camera
    kvs::Light* m_light; ///< light
    kvs::Mouse* m_mouse; ///< mouse
    kvs::Background* m_background; ///< background
    kvs::ObjectManager* m_object_manager; ///< object manager
    kvs::RendererManager* m_renderer_manager; ///< renderer manager
    kvs::IDManager* m_id_manager; ///< ID manager ( object_id, renderer_id )
    ControlTarget m_target; ///< control target
    bool m_enable_move_all;  ///< flag for object movement
    bool m_enable_collision_detection; ///< flag for collision detection

public:

    Scene();
    virtual ~Scene();

    kvs::Camera* camera() { return m_camera; }
    kvs::Light* light() { return m_light; }
    kvs::Mouse* mouse() { return m_mouse; }
    kvs::Background* background() { return m_background; }
    kvs::ObjectManager* objectManager() { return m_object_manager; }
    kvs::RendererManager* rendererManager() { return m_renderer_manager; }
    kvs::IDManager* IDManager() { return m_id_manager; }
    ControlTarget& controlTarget() { return m_target; }

    void initializeFunction();
    void paintFunction();
    void resizeFunction( int width, int height );
    void mouseReleaseFunction( int x, int y );
    void mousePressFunction( int x, int y, kvs::Mouse::TransMode mode );
    void mouseMoveFunction( int x, int y );
    void wheelFunction( int value );

    void reset();
    bool isActiveMove( int x, int y );
    void disableAllMove();
    void enableAllMove();
    void disableCollisionDetection();
    void enableCollisionDetection();
    void updateControllingObject();
    void updateCenterOfRotation();
    void updateXform();
    void updateXform( kvs::ObjectManager* manager );
    void updateXform( kvs::Camera* camera );
    void updateXform( kvs::Light* light );
};

} // end of namespace kvs

#endif // KVS__SCENE_H_INCLUDE
