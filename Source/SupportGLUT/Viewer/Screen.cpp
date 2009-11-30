/****************************************************************************/
/**
 *  @file Screen.cpp
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
#include "Screen.h"
#include <kvs/Key>
#include <kvs/Mouse>
#include <kvs/MouseButton>
#include <kvs/ResizeEvent>
#include <kvs/glut/GLUT>


namespace
{

/*===========================================================================*/
/**
 *  @brief  Listener class for idle mouse event.
 */
/*===========================================================================*/
class IdleMouseEvent : public kvs::TimerEventListener
{
public:

    IdleMouseEvent( kvs::ScreenBase* screen )
    {
        kvs::TimerEventListener::setScreen( screen );
    }

    void update( kvs::TimeEvent* event )
    {
        static_cast<kvs::glut::Screen*>(screen())->idleMouseEvent();
    }
};

} // end of namespace


namespace kvs
{

namespace glut
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new Screen class.
 */
/*===========================================================================*/
Screen::Screen( kvs::glut::Application* application ):
    kvs::glut::Window(),
    kvs::ScreenBase()
{
    if ( application ) application->attach( this );

    m_paint_event_func = &Screen::default_paint_event;
    m_resize_event_func = &Screen::default_resize_event;
    m_mouse_press_event_func = &Screen::default_mouse_press_event;
    m_mouse_move_event_func = &Screen::default_mouse_move_event;
    m_mouse_release_event_func = &Screen::default_mouse_release_event;
    m_wheel_event_func = &Screen::default_wheel_event;
    m_key_press_event_func = &Screen::default_key_press_event;

    m_idle_mouse_event_listener = new ::IdleMouseEvent( this );
    m_idle_mouse_timer = new kvs::glut::Timer( m_idle_mouse_event_listener );

    m_initialize_event_handler = new kvs::EventHandler();
    m_event_handler = new kvs::EventHandler();
}

/*===========================================================================*/
/**
 *  @brief  Destructs the Screen class.
 */
/*===========================================================================*/
Screen::~Screen( void )
{
    if ( m_idle_mouse_timer ) { delete m_idle_mouse_timer; }
    if ( m_idle_mouse_event_listener ) { delete m_idle_mouse_event_listener; }
    if ( m_initialize_event_handler ) { delete m_initialize_event_handler; }
    if ( m_event_handler ) { delete m_event_handler; }

    std::list<kvs::glut::Timer*>::iterator timer = m_timer_event_handler.begin();
    std::list<kvs::glut::Timer*>::iterator end = m_timer_event_handler.end();
    while ( timer != end )
    {
        if ( *timer ) delete *timer;
        ++timer;
    }
    m_timer_event_handler.clear();
}

/*===========================================================================*/
/**
 *  @brief  Sets a screen position.
 *  @param  x [in] x coordinate value of the screen position
 *  @param  y [in] y coordinate value of the screen position
 */
/*===========================================================================*/
void Screen::setPosition( const int x, const int y )
{
    Window::setPosition( x, y );
}

/*===========================================================================*/
/**
 *  @brief  Sets a screen size.
 *  @param  width [in] screen width
 *  @param  height [in] screen height
 */
/*===========================================================================*/
void Screen::setSize( const int width, const int height )
{
    Window::setSize( width, height );

    if ( ScreenBase::camera() ) ScreenBase::camera()->setWindowSize( width, height );
    if ( ScreenBase::mouse()  ) ScreenBase::mouse()->setWindowSize( width, height );
}

/*===========================================================================*/
/**
 *  @brief  Sets a screen geometry (position and size).
 *  @param  x [in] x coordinate value of the screen position
 *  @param  y [in] y coordinate value of the screen position
 *  @param  width [in] screen width
 *  @param  height [in] screen height
 */
/*===========================================================================*/
void Screen::setGeometry( const int x, const int y, const int width, const int height )
{
    this->setPosition( x, y );
    this->setSize( width, height );
}

/*===========================================================================*/
/**
 *  @brief  Initialization event.
 */
/*===========================================================================*/
void Screen::initializeEvent( void )
{
    m_idle_mouse_timer->start( kvs::Mouse::SpinTime );

    ScreenBase::initializeFunction();
    m_initialize_event_handler->notify();
}

/*===========================================================================*/
/**
 *  @brief  Paint event.
 */
/*===========================================================================*/
void Screen::paintEvent( void )
{
    if ( m_paint_event_func ) (this->*m_paint_event_func)();
    else m_event_handler->notify();
}

/*===========================================================================*/
/**
 *  @brief  Resize event.
 *  @param  width [in] resized screen width
 *  @param  height [in] resized screen height
 */
/*===========================================================================*/
void Screen::resizeEvent( int width, int height )
{
    if ( m_resize_event_func ) (this->*m_resize_event_func)( width, height );
    else
    {
        kvs::ResizeEvent event( width, height );
        m_event_handler->notify( &event );
    }
}

/*===========================================================================*/
/**
 *  @brief  Mouse press event.
 *  @param  event [in] pointer to the mouse event information
 */
/*===========================================================================*/
void Screen::mousePressEvent( kvs::MouseEvent* event )
{
    if ( m_mouse_press_event_func ) (this->*m_mouse_press_event_func)( event );
    else m_event_handler->notify( event );
}

/*===========================================================================*/
/**
 *  @brief  Mouse move event.
 *  @param  event [in] pointer to the mouse event information
 */
/*===========================================================================*/
void Screen::mouseMoveEvent( kvs::MouseEvent* event )
{
    if ( m_mouse_move_event_func ) (this->*m_mouse_move_event_func)( event );
    else m_event_handler->notify( event );
}

/*===========================================================================*/
/**
 *  @brief  Mouse release event.
 *  @param  event [in] pointer to the mouse event information
 */
/*===========================================================================*/
void Screen::mouseReleaseEvent( kvs::MouseEvent* event )
{
    if ( m_mouse_release_event_func ) (this->*m_mouse_release_event_func)( event );
    else m_event_handler->notify( event );
}

/*===========================================================================*/
/**
 *  @brief  Mouse double-click event.
 *  @param  event [in] pointer to the mouse event information
 */
/*===========================================================================*/
void Screen::mouseDoubleClickEvent( kvs::MouseEvent* event )
{
    m_event_handler->notify( event );
}

/*===========================================================================*/
/**
 *  @brief  Wheel event.
 *  @param  event [in] pointer to the wheel event information
 */
/*===========================================================================*/
void Screen::wheelEvent( kvs::WheelEvent* event )
{
    if ( m_wheel_event_func ) (this->*m_wheel_event_func)( event );
    else m_event_handler->notify( event );
}

/*===========================================================================*/
/**
 *  @brief  Key press event.
 *  @param  event [in] pointer to the key event information
 */
/*===========================================================================*/
void Screen::keyPressEvent( kvs::KeyEvent* event )
{
    if ( m_key_press_event_func ) (this->*m_key_press_event_func)( event );
    else m_event_handler->notify( event );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the event handler.
 *  @return pointer to the event handler
 */
/*===========================================================================*/
kvs::EventHandler* Screen::eventHandler( void ) const
{
    return( m_event_handler );
}

/*===========================================================================*/
/**
 *  @brief  Sets a paint event listener.
 *  @param  event [in] pointer to a paint event listener
 */
/*===========================================================================*/
void Screen::setPaintEvent( kvs::PaintEventListener* event )
{
    m_paint_event_func = NULL;
    this->addPaintEvent( event );
}

/*===========================================================================*/
/**
 *  @brief  Sets a resize event listener.
 *  @param  event [in] pointer to a resize event listener
 */
/*===========================================================================*/
void Screen::setResizeEvent( kvs::ResizeEventListener* event )
{
    m_resize_event_func = NULL;
    this->addResizeEvent( event );
}

/*===========================================================================*/
/**
 *  @brief  Sets a mouse press event listener.
 *  @param  event [in] pointer to a mouse press event listener
 */
/*===========================================================================*/
void Screen::setMousePressEvent( kvs::MousePressEventListener* event )
{
    m_mouse_press_event_func = NULL;
    this->addMousePressEvent( event );
}

/*===========================================================================*/
/**
 *  @brief  Sets a mouse move event listener.
 *  @param  event [in] pointer to a mouse move event listener
 */
/*===========================================================================*/
void Screen::setMouseMoveEvent( kvs::MouseMoveEventListener* event )
{
    m_mouse_move_event_func = NULL;
    this->addMouseMoveEvent( event );
}

/*===========================================================================*/
/**
 *  @brief  Sets a mouse release event listener.
 *  @param  event [in] pointer to a mouse release event listener
 */
/*===========================================================================*/
void Screen::setMouseReleaseEvent( kvs::MouseReleaseEventListener* event )
{
    m_mouse_release_event_func = NULL;
    this->addMouseReleaseEvent( event );
}

/*===========================================================================*/
/**
 *  @brief  Sets a mouse double-click event listener.
 *  @param  event [in] pointer to a mouse double-click event listener
 */
/*===========================================================================*/
void Screen::setMouseDoubleClickEvent( kvs::MouseDoubleClickEventListener* event )
{
    this->addMouseDoubleClickEvent( event );
}

/*===========================================================================*/
/**
 *  @brief  Sets a wheel event listener.
 *  @param  event [in] pointer to a wheel event listener
 */
/*===========================================================================*/
void Screen::setWheelEvent( kvs::WheelEventListener* event )
{
    m_wheel_event_func = NULL;
    this->addWheelEvent( event );
}

/*===========================================================================*/
/**
 *  @brief  Sets a key press event listener.
 *  @param  event [in] pointer to a key press event listener
 */
/*===========================================================================*/
void Screen::setKeyPressEvent( kvs::KeyPressEventListener* event )
{
    m_key_press_event_func = NULL;
    this->addKeyPressEvent( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds an intialize event listener.
 *  @param  event [in] pointer to an initialize event listener
 */
/*===========================================================================*/
void Screen::addInitializeEvent( kvs::InitializeEventListener* event )
{
    event->setScreen( this );
    event->setWindow( this );
    m_initialize_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds a paint event listener.
 *  @param  event [in] pointer to a paint event listener
 */
/*===========================================================================*/
void Screen::addPaintEvent( kvs::PaintEventListener* event )
{
    event->setScreen( this );
    event->setWindow( this );
    m_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds a resize event listener.
 *  @param  event [in] pointer to a resize event listener
 */
/*===========================================================================*/
void Screen::addResizeEvent( kvs::ResizeEventListener* event )
{
    event->setScreen( this );
    event->setWindow( this );
    m_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds a mouse press event listener.
 *  @param  event [in] pointer to a mous press event listener
 */
/*===========================================================================*/
void Screen::addMousePressEvent( kvs::MousePressEventListener* event )
{
    event->setScreen( this );
    event->setWindow( this );
    m_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds a mouse move event listener.
 *  @param  event [in] pointer to a mouse move event listener
 */
/*===========================================================================*/
void Screen::addMouseMoveEvent( kvs::MouseMoveEventListener* event )
{
    event->setScreen( this );
    event->setWindow( this );
    m_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds a mouse release event listener.
 *  @param  event [in] pointer to a mouse release event listener
 */
/*===========================================================================*/
void Screen::addMouseReleaseEvent( kvs::MouseReleaseEventListener* event )
{
    event->setScreen( this );
    event->setWindow( this );
    m_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds a mouse double-click event listener.
 *  @param  event [in] pointer to a mouse double-click event listener
 */
/*===========================================================================*/
void Screen::addMouseDoubleClickEvent( kvs::MouseDoubleClickEventListener* event )
{
    event->setScreen( this );
    event->setWindow( this );
    m_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds a wheel event listener.
 *  @param  event [in] pointer to a wheel event listener
 */
/*===========================================================================*/
void Screen::addWheelEvent( kvs::WheelEventListener* event )
{
    event->setScreen( this );
    event->setWindow( this );
    m_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds a key press event listener.
 *  @param  event [in] pointer to a key press event listener
 */
/*===========================================================================*/
void Screen::addKeyPressEvent( kvs::KeyPressEventListener* event )
{
    event->setScreen( this );
    event->setWindow( this );
    m_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds a timer event listener.
 *  @param  event [in] pointer to a timer event listener
 *  @param  msec [in] interval time in milliseconds
 */
/*===========================================================================*/
void Screen::addTimerEvent( kvs::TimerEventListener* event, int msec )
{
    event->setScreen( this );
    event->setWindow( this );
    m_timer_event_handler.push_back( new kvs::glut::Timer( event, msec ) );
}

/*===========================================================================*/
/**
 *  @brief  Shows the screen.
 *  @return window ID
 */
/*===========================================================================*/
int Screen::show( void )
{
    // Initialize display mode.
    unsigned int mode = 0;
    if ( displayFormat().doubleBuffer() ) mode |= GLUT_DOUBLE; else mode |= GLUT_SINGLE;
    if ( displayFormat().colorBuffer() ) mode |= GLUT_RGBA; else mode |= GLUT_INDEX;
    if ( displayFormat().depthBuffer() ) mode |= GLUT_DEPTH;
    if ( displayFormat().accumulationBuffer() ) mode |= GLUT_ACCUM;
    if ( displayFormat().stencilBuffer() ) mode |= GLUT_STENCIL;
    if ( displayFormat().stereoBuffer() ) mode |= GLUT_STEREO;
    if ( displayFormat().multisampleBuffer() ) mode |= GLUT_MULTISAMPLE;
    if ( displayFormat().alphaChannel() ) mode |= GLUT_ALPHA;
    glutInitDisplayMode( mode );

    // Set screen geometry.
    glutInitWindowPosition( m_x, m_y );
    glutInitWindowSize( m_width, m_height );

    // Create window.
    Window::create();

    return( Window::id() );
}

/*===========================================================================*/
/**
 *  @brief  Default paint event.
 */
/*===========================================================================*/
void Screen::default_paint_event( void )
{
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glPushMatrix();

    ScreenBase::paintFunction();
    m_event_handler->notify();

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

/*===========================================================================*/
/**
 *  @brief  Default resize event.
 *  @param  width [in] screen width
 *  @param  height [in] screen height
 */
/*===========================================================================*/
void Screen::default_resize_event( int width, int height )
{
    if ( !Window::isFullScreen() )
    {
        m_width = width;
        m_height = height;
    }

    kvs::ResizeEvent event( width, height );

    ScreenBase::resizeFunction( width, height );
    m_event_handler->notify( &event );
}

/*===========================================================================*/
/**
 *  @brief  Default mouse press event.
 *  @param  event [in] pointer to the mouse event
 */
/*===========================================================================*/
void Screen::default_mouse_press_event( kvs::MouseEvent* event )
{
    if ( event->button() == kvs::MouseButton::Left )
    {
        m_event_handler->notify( event );
        if ( !ScreenBase::isActiveMove( event->x(), event->y() ) ) return;

        kvs::Mouse::TransMode mode;
        switch ( event->modifiers() )
        {
        case kvs::Key::ShiftModifier:
            mode = kvs::Mouse::Scaling;
            break;
        case kvs::Key::ControlModifier:
            mode = kvs::Mouse::Translation;
            break;
        default:
            mode = kvs::Mouse::Rotation;
            ScreenBase::updateCenterOfRotation();
            break;
        }

        ScreenBase::mousePressFunction( event->x(), event->y(), mode );
    }

    else if ( event->button() == kvs::MouseButton::Middle )
    {
        m_event_handler->notify( event );
        if ( !ScreenBase::isActiveMove( event->x(), event->y() ) ) return;

        ScreenBase::mousePressFunction( event->x(), event->y(), kvs::Mouse::Scaling );
    }

    else if ( event->button() == kvs::MouseButton::Right )
    {
        m_event_handler->notify( event );
        if ( !ScreenBase::isActiveMove( event->x(), event->y() ) ) return;

        ScreenBase::mousePressFunction( event->x(), event->y(), kvs::Mouse::Translation );
    }
}

/*===========================================================================*/
/**
 *  @brief  Default mouse move event.
 *  @param  event [in] pointer to the mouse event
 */
/*===========================================================================*/
void Screen::default_mouse_move_event( kvs::MouseEvent* event )
{
    m_event_handler->notify( event );
    if( ScreenBase::m_target == ScreenBase::TargetObject )
    {
        if( !ScreenBase::m_object_manager->isEnableAllMove() )
        {
            if( !ScreenBase::m_object_manager->hasActiveObject() )
            {
                return;
            }
        }
    }

    ScreenBase::m_mouse->move( event->x(), event->y() );
    ScreenBase::updateXform();
    Window::redraw();
}

/*===========================================================================*/
/**
 *  @brief  Default mouse release event.
 *  @param  event [in] pointer to the mouse event
 */
/*===========================================================================*/
void Screen::default_mouse_release_event( kvs::MouseEvent* event )
{
    m_event_handler->notify( event );
    ScreenBase::mouseReleaseFunction( event->x(), event->y() );
}

/*===========================================================================*/
/**
 *  @brief  Default wheel event.
 *  @param  event [in] pointer to the wheel event
 */
/*===========================================================================*/
void Screen::default_wheel_event( kvs::WheelEvent* event )
{
    m_event_handler->notify( event );
    if ( !ScreenBase::isActiveMove( event->x(), event->y() ) ) return;

    if ( event->direction() > 0 )
    {
//        ScreenBase::wheelFunction( kvs::Mouse::WheelUpValue );
        ScreenBase::wheelFunction( 10 );
    }
    else
    {
//        ScreenBase::wheelFunction( kvs::Mouse::WheelDownValue );
        ScreenBase::wheelFunction( -10 );
    }

    ScreenBase::updateXform();
    Window::redraw();
}

/*===========================================================================*/
/**
 *  @brief  Default key press event.
 *  @param  event [in] pointer to the key event
 */
/*===========================================================================*/
void Screen::default_key_press_event( kvs::KeyEvent* event )
{
    switch( event->key() )
    {
    case kvs::Key::Escape:
    case kvs::Key::q:
        ScreenBase::clear();
        exit( 0 );
        break;
    case kvs::Key::Home:
        ScreenBase::reset();
        break;
    case kvs::Key::Tab:
        ScreenBase::disableAllMove();
        break;
    default:
        break;
    }

    m_event_handler->notify( event );

    Window::redraw();
}

/*===========================================================================*/
/**
 *  @brief  Default idle mouse event.
 */
/*===========================================================================*/
void Screen::idleMouseEvent( void )
{
    if ( ScreenBase::mouse()->idle() )
    {
        if ( !( ScreenBase::controlTarget() == ScreenBase::TargetObject &&
                !ScreenBase::objectManager()->isEnableAllMove()   &&
                !ScreenBase::objectManager()->hasActiveObject() ) )
        {
            ScreenBase::updateXform();
            Window::redraw();
        }
    }
}

} // end of namespace glut

} // end of namespace kvs
