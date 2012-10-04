/****************************************************************************/
/**
 *  @file KeyEvent.cpp
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
#include "KeyEvent.h"


namespace kvs
{

KeyEvent::KeyEvent()
{
}

KeyEvent::KeyEvent( const KeyEvent& event ):
    m_key( event.m_key ),
    m_x( event.m_x ),
    m_y( event.m_y )
{
}

KeyEvent::KeyEvent( int key, int x, int y ):
    m_key( key ),
    m_x( x ),
    m_y( y )
{
}

KeyEvent::~KeyEvent()
{
}

int KeyEvent::key() const
{
    return( m_key );
}

int KeyEvent::x() const
{
    return( m_x );
}

int KeyEvent::y() const
{
    return( m_y );
}

int KeyEvent::type() const
{
    return( EventBase::KeyPressEvent );
}

void KeyEvent::setKey( int key )
{
    m_key = key;
}

void KeyEvent::setPosition( int x, int y )
{
    m_x = x;
    m_y = y;
}

} // end of namespace kvs
