/****************************************************************************/
/**
 *  @file ScreenCore.h
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
#ifndef KVS_CORE_SCREEN_CORE_H_INCLUDE
#define KVS_CORE_SCREEN_CORE_H_INCLUDE

#include <string>
#include "Camera.h"
#include "Light.h"
#include "Mouse.h"
#include "ObjectManager.h"
#include "RendererManager.h"
#include "MouseEvent.h"
#include "KeyEvent.h"
#include "DisplayFormat.h"
#include <kvs/ClassName>
#include <kvs/IgnoreUnusedVariable>


namespace kvs
{

typedef void (*InitializeFunc)( void );
typedef void (*PaintEvent)( void );
typedef void (*ResizeEvent)( int, int );
typedef void (*MousePressEvent)( MouseEvent* );
typedef void (*MouseMoveEvent)( MouseEvent* );
typedef void (*MouseReleaseEvent)( MouseEvent* );
typedef void (*KeyPressEvent)( KeyEvent* );

/*==========================================================================*/
/**
 *  Screen core class.
 */
/*==========================================================================*/
class ScreenCore
{
    kvsClassName( ScreenCore );

protected:

    static kvs::DisplayFormat m_display_format;///< display format
    static std::string        m_title;         ///< window title
    static int                m_x;             ///< window position (y position)
    static int                m_y;             ///< window position (x position)
    static int                m_width;         ///< window size (width)
    static int                m_height;        ///< window size (height)
    static int                m_id;            ///< window ID
    static bool               m_is_fullscreen; ///< flag for statement of fullscreen.
    static bool               m_can_move_all;  ///< flag for object movement
    static kvs::MouseEvent*   m_mouse_event;   ///< mouse event
    static kvs::KeyEvent*     m_key_event;     ///< key event

protected:

    static InitializeFunc    m_pfunc_add_initialize_func;
    static PaintEvent        m_pfunc_add_paint_event;
    static ResizeEvent       m_pfunc_add_resize_event;
    static MousePressEvent   m_pfunc_add_mouse_press_event;
    static MouseMoveEvent    m_pfunc_add_mouse_move_event;
    static MouseReleaseEvent m_pfunc_add_mouse_release_event;
    static KeyPressEvent     m_pfunc_add_key_press_event;

    static MousePressEvent   m_pfunc_set_mouse_press_event;
    static MouseMoveEvent    m_pfunc_set_mouse_move_event;
    static MouseReleaseEvent m_pfunc_set_mouse_release_event;
    static KeyPressEvent     m_pfunc_set_key_press_event;

protected:

    static void paint_event_core( void );
    static void resize_event_core( int width, int height );

    static void add_initialize_func( void ){};
    static void add_paint_event( void ){};
    static void add_resize_event( int, int ){};
    static void add_mouse_press_event( MouseEvent* ){};
    static void add_mouse_move_event( MouseEvent* ){};
    static void add_mouse_release_event( MouseEvent* ){};
    static void add_key_press_event( KeyEvent* ){};

    static void set_mouse_press_event( MouseEvent* ){};
    static void set_mouse_move_event( MouseEvent* ){};
    static void set_mouse_release_event( MouseEvent* ){};
    static void set_key_press_event( KeyEvent* ){};

public:

    ScreenCore( void );

    virtual ~ScreenCore( void );

public:

    void setDisplayFormat( const kvs::DisplayFormat& display_format );

    void setPosition( int x, int y );

    void setSize( int width, int height );

    void setGeometry( int x, int y, int width, int height );

    void setTitle( const std::string& title );

public:

    const kvs::DisplayFormat& displayFormat( void ) const;

    const int x( void ) const;

    const int y( void ) const;

    const int width( void ) const;

    const int height( void ) const;

    const int id( void ) const;

    const std::string& title( void ) const;

public:

    void addInitializeFunc( InitializeFunc pfunc );

    void addPaintEvent( PaintEvent event );

    void addResizeEvent( ResizeEvent event );

    void addMousePressEvent( MousePressEvent event );

    void addMouseMoveEvent( MouseMoveEvent event );

    void addMouseReleaseEvent( MouseReleaseEvent event );

    void addKeyPressEvent( KeyPressEvent event );

public:

    virtual void setPaintEvent( PaintEvent event ) = 0;

    virtual void setResizeEvent( ResizeEvent event ) = 0;

    virtual void setMousePressEvent( MousePressEvent event ) = 0;

    virtual void setMouseMoveEvent( MouseMoveEvent event ) = 0;

    virtual void setKeyPressEvent( KeyPressEvent event ) = 0;

public:

    virtual int show( bool last = true ) = 0;

public:

    static void showFullScreen( void ){};

    static void showNormal( void ){};

    static void popUp( void ){};

    static void pushDown( void ){};

    static void hide( void ){};

    static void showWindow( void ){};

    static void redraw( void ){};

    static void resize( int width, int height )
    {
        kvs::IgnoreUnusedVariable( width );
        kvs::IgnoreUnusedVariable( height );
    };

public:

    static bool isFullScreen( void );

    static void disableAllMove( void );

protected:

    static void initialize( void );

protected:

    static void mouse_button_release( int x, int y );

    static void mouse_button_press( int x, int y, kvs::Mouse::TransMode mode );

    static bool is_active_move( int x, int y );

    static void set_object_manager_params( void );

    static void set_center_of_rotation( void );

    static void update_xform( void );

    static void update_object_manager_xform( kvs::ObjectManager* manager );

    static void update_camera_xform( kvs::Camera* camera );

    static void update_light_xform( kvs::Light* light );
};

} // end of namespace kvs

#endif // KVS_CORE_SCREEN_CORE_H_INCLUDE
