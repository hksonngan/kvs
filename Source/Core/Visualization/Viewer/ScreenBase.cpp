/****************************************************************************/
/**
 *  @file ScreenBase.cpp
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
#include "ScreenBase.h"
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


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new ScreenBase class.
 */
/*===========================================================================*/
ScreenBase::ScreenBase():
    m_x( 0 ),
    m_y( 0 ),
    m_width( 512 ),
    m_height( 512 ),
    m_title("")
{
    m_initialize_event_handler = new kvs::EventHandler();
    m_event_handler = new kvs::EventHandler();
}

/*===========================================================================*/
/**
 *  @brief  Destructs the ScreenBase class.
 */
/*===========================================================================*/
ScreenBase::~ScreenBase()
{
    delete m_initialize_event_handler;
    delete m_event_handler;
}

/*===========================================================================*/
/**
 *  @brief  Returns the x coordinate value of the window position.
 *  @return x coordinate value of the window position
 */
/*===========================================================================*/
int ScreenBase::x( void ) const
{
    return( m_x );
}

/*===========================================================================*/
/**
 *  @brief  Returns the y coordinate value of the window position.
 *  @return y coordinate value of the window position
 */
/*===========================================================================*/
int ScreenBase::y( void ) const
{
    return( m_y );
}

/*===========================================================================*/
/**
 *  @brief  Returns the window width.
 *  @return window width
 */
/*===========================================================================*/
int ScreenBase::width( void ) const
{
    return( m_width );
}

/*===========================================================================*/
/**
 *  @brief  Returns the window height.
 *  @return window height
 */
/*===========================================================================*/
int ScreenBase::height( void ) const
{
    return( m_height );
}

/*===========================================================================*/
/**
 *  @brief  Returns the window title.
 *  @return window title
 */
/*===========================================================================*/
const std::string& ScreenBase::title( void ) const
{
    return( m_title );
}

/*===========================================================================*/
/**
 *  @brief  Returns the display format.
 */
/*===========================================================================*/
const kvs::DisplayFormat& ScreenBase::displayFormat( void ) const
{
    return( m_display_format );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the initialize event handler.
 *  @return pointer to the event handler
 */
/*===========================================================================*/
kvs::EventHandler* ScreenBase::initializeEventHandler()
{
    return( m_initialize_event_handler );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the event handler.
 *  @return pointer to the event handler
 */
/*===========================================================================*/
kvs::EventHandler* ScreenBase::eventHandler()
{
    return( m_event_handler );
}

/*===========================================================================*/
/**
 *  @brief  Sets a window position.
 *  @param  x [in] x coordinate value of the window
 *  @param  y [in] y coordinate value of the window
 */
/*===========================================================================*/
void ScreenBase::setPosition( const int x, const int y )
{
    m_x = x;
    m_y = y;
}

/*===========================================================================*/
/**
 *  @brief  Sets a window size.
 *  @param  width [in] window width
 *  @param  height [in] window height
 */
/*===========================================================================*/
void ScreenBase::setSize( const int width, const int height )
{
    m_width  = width;
    m_height = height;
}

/*===========================================================================*/
/**
 *  @brief  Sets a window geometry (position and size).
 *  @param  x [in] x coordinate value of the window
 *  @param  y [in] y coordinate value of the window
 *  @param  width [in] window width
 *  @param  height [in] window height
 */
/*===========================================================================*/
void ScreenBase::setGeometry( const int x, const int y, const int width, const int height )
{
    this->setPosition( x, y );
    this->setSize( width, height );
}

/*===========================================================================*/
/**
 *  @brief  Sets a window title.
 *  @param  title [in] window title
 */
/*===========================================================================*/
void ScreenBase::setTitle( const std::string& title )
{
    m_title = title;
}

/*===========================================================================*/
/**
 *  @brief  Sets a display format.
 *  @param  display_format [in] display format
 */
/*===========================================================================*/
void ScreenBase::setDisplayFormat( const kvs::DisplayFormat& display_format )
{
    m_display_format = display_format;
}

/*===========================================================================*/
/**
 *  @brief  Adds an intialize event listener.
 *  @param  event [in] pointer to an initialize event listener
 */
/*===========================================================================*/
void ScreenBase::addInitializeEvent( kvs::InitializeEventListener* event )
{
    event->setScreen( this );
    m_initialize_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds a paint event listener.
 *  @param  event [in] pointer to a paint event listener
 */
/*===========================================================================*/
void ScreenBase::addPaintEvent( kvs::PaintEventListener* event )
{
    event->setScreen( this );
    m_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds a resize event listener.
 *  @param  event [in] pointer to a resize event listener
 */
/*===========================================================================*/
void ScreenBase::addResizeEvent( kvs::ResizeEventListener* event )
{
    event->setScreen( this );
    m_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds a mouse press event listener.
 *  @param  event [in] pointer to a mous press event listener
 */
/*===========================================================================*/
void ScreenBase::addMousePressEvent( kvs::MousePressEventListener* event )
{
    event->setScreen( this );
    m_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds a mouse move event listener.
 *  @param  event [in] pointer to a mouse move event listener
 */
/*===========================================================================*/
void ScreenBase::addMouseMoveEvent( kvs::MouseMoveEventListener* event )
{
    event->setScreen( this );
    m_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds a mouse release event listener.
 *  @param  event [in] pointer to a mouse release event listener
 */
/*===========================================================================*/
void ScreenBase::addMouseReleaseEvent( kvs::MouseReleaseEventListener* event )
{
    event->setScreen( this );
    m_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds a mouse double-click event listener.
 *  @param  event [in] pointer to a mouse double-click event listener
 */
/*===========================================================================*/
void ScreenBase::addMouseDoubleClickEvent( kvs::MouseDoubleClickEventListener* event )
{
    event->setScreen( this );
    m_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds a wheel event listener.
 *  @param  event [in] pointer to a wheel event listener
 */
/*===========================================================================*/
void ScreenBase::addWheelEvent( kvs::WheelEventListener* event )
{
    event->setScreen( this );
    m_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds a key press event listener.
 *  @param  event [in] pointer to a key press event listener
 */
/*===========================================================================*/
void ScreenBase::addKeyPressEvent( kvs::KeyPressEventListener* event )
{
    event->setScreen( this );
    m_event_handler->attach( event );
}

void ScreenBase::create(){}
void ScreenBase::show(){}
void ScreenBase::showFullScreen(){}
void ScreenBase::showNormal(){}
void ScreenBase::hide(){}
void ScreenBase::popUp(){}
void ScreenBase::pushDown(){}
void ScreenBase::redraw(){}
void ScreenBase::resize( int, int ){}
bool ScreenBase::isFullScreen() const { return false; }
void ScreenBase::enable(){}
void ScreenBase::disable(){}
void ScreenBase::reset(){}

} // end of namespace kvs
