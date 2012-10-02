/****************************************************************************/
/**
 *  @file Screen.h
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
#ifndef KVS__GLUT__SCREEN_H_INCLUDE
#define KVS__GLUT__SCREEN_H_INCLUDE

#include "ScreenBase.h"
#include <kvs/Scene>
#include <kvs/Mouse>
#include <list>


namespace kvs
{

class Scene;
class ObjectBase;
class RendererBase;
class VisualizationPipeline;
class EventHandler;
class TimerEventListener;
class PaintEventListener;
class ResizeEventListener;
class MousePressEventListener;
class MouseMoveEventListener;
class MouseReleaseEventListener;
class MouseDoubleClickEventListener;
class WheelEventListener;
class KeyPressEventListener;

namespace glut
{

class Application;
class Timer;

class Screen : public kvs::glut::ScreenBase
{
public:

    typedef kvs::glut::ScreenBase BaseClass;
    typedef kvs::Scene::ControlTarget ControlTarget;

private:

    bool m_enable_default_paint_event;
    bool m_enable_default_resize_event;
    bool m_enable_default_mouse_press_event;
    bool m_enable_default_mouse_move_event;
    bool m_enable_default_mouse_release_event;
    bool m_enable_default_wheel_event;
    bool m_enable_default_key_press_event;
    kvs::Scene* m_scene; ///< default scene
    kvs::glut::Timer* m_idle_mouse_timer; ///< timer for idle mouse event
    kvs::TimerEventListener* m_idle_mouse_event_listener; ///< idle mouse event listener

public:

    Screen( kvs::glut::Application* application = 0 );
    virtual ~Screen();

    kvs::Camera* camera();
    kvs::Light* light();
    kvs::Mouse* mouse();
    kvs::Background* background();
    kvs::ObjectManager* objectManager();
    kvs::RendererManager* rendererManager();
    kvs::IDManager* IDManager();
    ControlTarget& controlTarget();

    void setPosition( const int x, const int y );
    void setSize( const int width, const int height );
    void setGeometry( const int x, const int y, const int width, const int height );

    void setPaintEvent( kvs::PaintEventListener* event );
    void setResizeEvent( kvs::ResizeEventListener* event );
    void setMousePressEvent( kvs::MousePressEventListener* event );
    void setMouseMoveEvent( kvs::MouseMoveEventListener* event );
    void setMouseReleaseEvent( kvs::MouseReleaseEventListener* event );
    void setMouseDoubleClickEvent( kvs::MouseDoubleClickEventListener* event );
    void setWheelEvent( kvs::WheelEventListener* event );
    void setKeyPressEvent( kvs::KeyPressEventListener* event );

    const std::pair<int,int> registerObject( kvs::ObjectBase* object, kvs::RendererBase* renderer = 0 );
    const std::pair<int,int> registerObject( kvs::VisualizationPipeline* pipeline );

    virtual void enable();
    virtual void disable();
    virtual void reset();

    virtual void initializeEvent();
    virtual void paintEvent();
    virtual void resizeEvent( int width, int height );
    virtual void mousePressEvent( kvs::MouseEvent* event );
    virtual void mouseMoveEvent( kvs::MouseEvent* event );
    virtual void mouseReleaseEvent( kvs::MouseEvent* event );
    virtual void mouseDoubleClickEvent( kvs::MouseEvent* event );
    virtual void wheelEvent( kvs::WheelEvent* event );
    virtual void keyPressEvent( kvs::KeyEvent* event );
    virtual void idleMouseEvent();

protected:

    virtual void defaultPaintEvent();
    virtual void defaultResizeEvent( int width, int height );
    virtual void defaultMousePressEvent( kvs::MouseEvent* event );
    virtual void defaultMouseMoveEvent( kvs::MouseEvent* event );
    virtual void defaultMouseReleaseEvent( kvs::MouseEvent* event );
    virtual void defaultWheelEvent( kvs::WheelEvent* event );
    virtual void defaultKeyPressEvent( kvs::KeyEvent* event );
};

} // end of namespace glut

} // end of namespace kvs

#endif // KVS__GLUT__SCREEN_H_INCLUDE
