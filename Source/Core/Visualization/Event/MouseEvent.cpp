/****************************************************************************/
/**
 *  @file MouseEvent.cpp
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
#include "MouseEvent.h"


namespace kvs
{

MouseEvent::MouseEvent( void )
{
}

MouseEvent::MouseEvent( const MouseEvent& event ):
    m_button( event.m_button ),
    m_state( event.m_state ),
    m_x( event.m_x ),
    m_y( event.m_y ),
    m_modifiers( event.m_modifiers )
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
    m_modifiers( modifiers )
{
}

MouseEvent::~MouseEvent( void )
{
}

void MouseEvent::set( int button, int state, int x, int y, int modifiers )
{
    m_button    = button;
    m_state     = state;
    m_x         = x;
    m_y         = y;
    m_modifiers = modifiers;
}

void MouseEvent::set( int x, int y )
{
    m_x = x;
    m_y = y;
}

const int MouseEvent::button( void ) const
{
    return( m_button );
}

const int MouseEvent::state( void ) const
{
    return( m_state );
}

const int MouseEvent::x( void ) const
{
    return( m_x );
}

const int MouseEvent::y( void ) const
{
    return( m_y );
}

const int MouseEvent::modifiers( void ) const
{
    return( m_modifiers );
}

} // end of namespace kvs
