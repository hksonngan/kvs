/*****************************************************************************/
/**
 *  @file   Screen.h
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
#ifndef KVS__QT__SCREEN_H_INCLUDE
#define KVS__QT__SCREEN_H_INCLUDE

#include "ScreenBase.h"
#include <kvs/Scene>
#include <kvs/Mouse>
#include <kvs/qt/Timer>
#include <list>


namespace kvs
{

class Scene;
class ObjectBase;
class RendererBase;
class VisualizationPipeline;
class InitializeEventListener;
class PaintEventListener;
class ResizeEventListener;
class MousePressEventListener;
class MouseMoveEventListener;
class MouseReleaseEventListener;
class MouseDoubleClickEventListener;
class WheelEventListener;
class KeyPressEventListener;

namespace qt
{

class Application;

class Screen : public kvs::qt::ScreenBase
{
    Q_OBJECT

public:

    typedef kvs::qt::ScreenBase BaseClass;
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
    QTimer* m_idle_mouse_timer; ///< timer for idle mouse event

public:

    Screen( kvs::qt::Application* application = 0, QWidget* parent = 0 );
    virtual ~Screen();

    kvs::Camera* camera();
    kvs::Light* light();
    kvs::Mouse* mouse();
    kvs::Background* background();
    kvs::ObjectManager* objectManager();
    kvs::RendererManager* rendererManager();
    kvs::IDManager* IDManager();
    ControlTarget& controlTarget();

    void setTitle( const std::string& title );
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

    virtual void initializeEvent( void );
    virtual void paintEvent( void );
    virtual void resizeEvent( int width, int height );
    virtual void mousePressEvent( kvs::MouseEvent* event );
    virtual void mouseMoveEvent( kvs::MouseEvent* event );
    virtual void mouseReleaseEvent( kvs::MouseEvent* event );
    virtual void mouseDoubleClickEvent( kvs::MouseEvent* event );
    virtual void wheelEvent( kvs::WheelEvent* event );
    virtual void keyPressEvent( kvs::KeyEvent* event );

public slots:

    virtual void idleMouseEvent( void );

protected:

    virtual void defaultPaintEvent( void );
    virtual void defaultResizeEvent( int width, int height );
    virtual void defaultMousePressEvent( kvs::MouseEvent* event );
    virtual void defaultMouseMoveEvent( kvs::MouseEvent* event );
    virtual void defaultMouseReleaseEvent( kvs::MouseEvent* event );
    virtual void defaultWheelEvent( kvs::WheelEvent* event );
    virtual void defaultKeyPressEvent( kvs::KeyEvent* event );
};

} // end of namespace qt

} // end of namespace kvs

#endif // KVS__QT__SCREEN_H_INCLUDE
