/****************************************************************************/
/**
 *  @file ScreenBase.h
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
#ifndef KVS__SCREEN_BASE_H_INCLUDE
#define KVS__SCREEN_BASE_H_INCLUDE

#include <string>
#include <kvs/DisplayFormat>

#if 1 // KVS_ENABLE_DEPRECATED
#include <kvs/EventHandler>
#include <kvs/InitializeEventListener>
#include <kvs/PaintEventListener>
#include <kvs/ResizeEventListener>
#include <kvs/MousePressEventListener>
#include <kvs/MouseMoveEventListener>
#include <kvs/MouseReleaseEventListener>
#include <kvs/MouseDoubleClickEventListener>
#include <kvs/WheelEventListener>
#include <kvs/KeyPressEventListener>
#endif


namespace kvs
{

class EventHandler;

class ScreenBase
{
private:

    int m_x; ///< window position (y position)
    int m_y; ///< window position (x position)
    int m_width; ///< window size (width)
    int m_height; ///< window size (height)
    std::string m_title; ///< window title
    kvs::DisplayFormat m_display_format; ///< display format
    kvs::EventHandler* m_event_handler; ///< event handler

public:

    ScreenBase();
    virtual ~ScreenBase();

    int x() const;
    int y() const;
    int width() const;
    int height() const;
    const std::string& title() const;
    const kvs::DisplayFormat& displayFormat() const;
    kvs::EventHandler* eventHandler();

    void setPosition( const int x, const int y );
    void setSize( const int width, const int height );
    void setGeometry( const int x, const int y, const int width, const int height );
    void setTitle( const std::string& title );
    void setDisplayFormat( const kvs::DisplayFormat& display_format );

    void addEvent( kvs::EventListener* event, const std::string& name = "" );
    void removeEvent( const kvs::EventListener* event );
    void removeEvent( const std::string& name );

    virtual void create();
    virtual void show();
    virtual void hide();
    virtual void showFullScreen();
    virtual void showNormal();
    virtual void popUp();
    virtual void pushDown();
    virtual void redraw();
    virtual void resize( int width, int height );
    virtual bool isFullScreen() const;
    virtual void enable();
    virtual void disable();
    virtual void reset();

#if 1 // KVS_ENABLE_DEPRECATED
    void addInitializeEvent( kvs::InitializeEventListener* event )
    {
        event->setScreen( this );
        m_event_handler->attach( event );
    }

    void addPaintEvent( kvs::PaintEventListener* event )
    {
        event->setScreen( this );
        m_event_handler->attach( event );
    }

    void addResizeEvent( kvs::ResizeEventListener* event )
    {
        event->setScreen( this );
        m_event_handler->attach( event );
    }

    void addMousePressEvent( kvs::MousePressEventListener* event )
    {
        event->setScreen( this );
        m_event_handler->attach( event );
    }

    void addMouseMoveEvent( kvs::MouseMoveEventListener* event )
    {
        event->setScreen( this );
        m_event_handler->attach( event );
    }

    void addMouseReleaseEvent( kvs::MouseReleaseEventListener* event )
    {
        event->setScreen( this );
        m_event_handler->attach( event );
    }

    void addMouseDoubleClickEvent( kvs::MouseDoubleClickEventListener* event )
    {
        event->setScreen( this );
        m_event_handler->attach( event );
    }

    void addWheelEvent( kvs::WheelEventListener* event )
    {
        event->setScreen( this );
        m_event_handler->attach( event );
    }

    void addKeyPressEvent( kvs::KeyPressEventListener* event )
    {
        event->setScreen( this );
        m_event_handler->attach( event );
    }
#endif
};

} // end of namespace kvs

#endif // KVS__SCREEN_BASE_H_INCLUDE
