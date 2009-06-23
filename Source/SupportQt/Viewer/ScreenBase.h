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
#ifndef KVS_SUPPORT_QT_SCREEN_BASE_H_INCLUDE
#define KVS_SUPPORT_QT_SCREEN_BASE_H_INCLUDE

#include "../Qt.h"
#include "QtScreenSupport.h"
#include <vector>
#include <string>
#include <kvs/ScreenCore>
#include <kvs/RGBColor>


namespace kvs
{

namespace qt
{

typedef void (*InitializeFuncBase)( void );
typedef void (*PaintEventBase)( void );
typedef void (*ResizeEventBase)( int, int );
typedef void (*MousePressEventBase)( QMouseEvent* );
typedef void (*MouseMoveEventBase)( QMouseEvent* );
typedef void (*MouseReleaseEventBase)( QMouseEvent* );
typedef void (*MouseDoubleClickEventBase)( QMouseEvent* );
typedef void (*WheelEventBase)( QWheelEvent* );
typedef void (*KeyPressEventBase)( QKeyEvent* );

typedef void (*MouseDoubleClickEvent)( MouseEvent* );
typedef void (*WheelEvent)( MouseEvent* );

/*==========================================================================*/
/**
 *  Screen base class for Qt.
 */
/*==========================================================================*/
class ScreenBase : public QGLWidget, public kvs::ScreenCore
{
    Q_OBJECT

protected:

    static QTimer*               m_mouse_timer; ///< timer for mouse event
    static kvs::QtScreenSupport* m_support;     ///< screen support class

protected:

    static PaintEventBase            m_pfunc_paint_event;
    static ResizeEventBase           m_pfunc_resize_event;
    static MousePressEventBase       m_pfunc_mouse_press_event;
    static MouseMoveEventBase        m_pfunc_mouse_move_event;
    static MouseReleaseEventBase     m_pfunc_mouse_release_event;
    static MouseDoubleClickEventBase m_pfunc_mouse_double_click_event;
    static WheelEventBase            m_pfunc_wheel_event;
    static KeyPressEventBase         m_pfunc_key_press_event;

    static MouseDoubleClickEvent     m_pfunc_add_mouse_double_click_event;
    static WheelEvent                m_pfunc_add_wheel_event;

    static MouseDoubleClickEvent     m_pfunc_set_mouse_double_click_event;
    static WheelEvent                m_pfunc_set_wheel_event;

protected:

    static void default_paint_event( void );
    static void default_resize_event( int width, int height );
    static void default_mouse_press_event( QMouseEvent* event );
    static void default_mouse_move_event( QMouseEvent* event );
    static void default_mouse_release_event( QMouseEvent* event );
    static void default_mouse_double_click_event( QMouseEvent* event );
    static void default_wheel_event( QWheelEvent* event );
    static void default_key_press_event( QKeyEvent* event );

    static void replaced_mouse_press_event( QMouseEvent* event );
    static void replaced_mouse_move_event( QMouseEvent* event );
    static void replaced_mouse_release_event( QMouseEvent* event );
    static void replaced_mouse_double_click_event( QMouseEvent* event );
    static void replaced_wheel_event( QWheelEvent* event );
    static void replaced_key_press_event( QKeyEvent * event );

    static void add_mouse_double_click_event( MouseEvent* ){};
    static void add_wheel_event( MouseEvent* ){};

    static void set_mouse_double_click_event( MouseEvent* ){};
    static void set_wheel_event( MouseEvent* ){};

public:

    ScreenBase( QWidget* parent = 0 );

    virtual ~ScreenBase( void );

protected:

    virtual void initializeGL( void );

    virtual void paintGL( void );

    virtual void resizeGL( int width, int height );

    virtual void mousePressEvent( QMouseEvent* event );

    virtual void mouseMoveEvent( QMouseEvent* event );

    virtual void mouseReleaseEvent( QMouseEvent* event );

    virtual void mouseDoubleClickEvent( QMouseEvent* event );

    virtual void wheelEvent( QWheelEvent* event );

    virtual void keyPressEvent( QKeyEvent* event );

public:

    void addMouseDoubleClickEvent( MouseDoubleClickEvent event );

    void addWheelEvent( WheelEvent event );

    void setPaintEvent( PaintEvent event );

    void setResizeEvent( ResizeEvent event );

    void setMousePressEvent( MousePressEvent event );

    void setMouseMoveEvent( MouseMoveEvent event );

    void setMouseReleaseEvent( MouseReleaseEvent event );

    void setMouseDoubleClickEvent( MouseDoubleClickEvent event );

    void setWheelEvent( WheelEvent event );

    void setKeyPressEvent( KeyPressEvent event );

public:

    void setPosition( int x, int y );

    void setSize( int width, int height );

    void setGeometry( int x, int y, int width, int height );

    void setTitle( const std::string& title );

public:

    int show( bool last = true );

    void showFullScreen( void );

    void showNormal( void );

    void popUp( void );

    void pushDown( void );

    void hide( void );

    void showWindow( void );

    void redraw( void );

    void resize( int width, int height );

protected:

    static void mouse_wheel_up( int value );

    static void mouse_wheel_down( int value );

public slots:

    void slotTimerMouseEvent( void );

public:

    static QGLWidget* device( void );
};

} // end of namesapce qt

} // end of namespace kvs

#endif // KVS_SUPPORT_QT_SCREEN_BASE_H_INCLUDE
