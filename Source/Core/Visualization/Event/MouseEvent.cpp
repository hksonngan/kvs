/****************************************************************************/
/**
 *  @file MouseEvent.cpp
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
#include "MouseEvent.h"
#include <kvs/MouseButton>


namespace kvs
{

MouseEvent::MouseEvent()
{
}

MouseEvent::MouseEvent( const MouseEvent& event ):
    m_button( event.m_button ),
    m_state( event.m_state ),
    m_x( event.m_x ),
    m_y( event.m_y ),
    m_modifiers( event.m_modifiers ),
    m_action( event.m_action )
{
}

MouseEvent::MouseEvent(
    int button,
    int state,
    int x,
    int y,
    int modifiers ):
    m_button( button ),
    m_state( state ),
    m_x( x ),
    m_y( y ),
    m_modifiers( modifiers ),
    m_action( kvs::MouseButton::NoAction )
{
}

MouseEvent::~MouseEvent()
{
}

int MouseEvent::button() const
{
    return( m_button );
}

int MouseEvent::state() const
{
    return( m_state );
}

int MouseEvent::x() const
{
    return( m_x );
}

int MouseEvent::y() const
{
    return( m_y );
}

int MouseEvent::modifiers() const
{
    return( m_modifiers );
}

int MouseEvent::action() const
{
    return( m_action );
}

int MouseEvent::type() const
{
    return(
        m_action == kvs::MouseButton::Pressed ? EventBase::MousePressEvent :
        m_action == kvs::MouseButton::Moved ? EventBase::MouseMoveEvent :
        m_action == kvs::MouseButton::Released ? EventBase::MouseReleaseEvent :
        m_action == kvs::MouseButton::DoubleClicked ? EventBase::MouseDoubleClickEvent :
        m_action == kvs::MouseButton::Wheeled ? EventBase::WheelEvent : 0 );
}

void MouseEvent::setButton( int button )
{
    m_button = button;
}

void MouseEvent::setState( int state )
{
    m_state = state;
}

void MouseEvent::setPosition( int x, int y )
{
    m_x = x;
    m_y = y;
}

void MouseEvent::setModifiers( int modifiers )
{
    m_modifiers = modifiers;
}

void MouseEvent::setAction( int action )
{
    m_action = action;
}

} // end of namespace kvs
