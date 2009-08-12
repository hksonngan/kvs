/*****************************************************************************/
/**
 *  @file   TimerEventListener.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include "TimerEventListener.h"


namespace kvs
{

TimerEventListener::TimerEventListener( void ):
    m_screen( NULL ),
    m_window( NULL )
{
    kvs::EventListener::setEventType( kvs::EventBase::TimerEvent );
}

TimerEventListener::~TimerEventListener( void )
{
}

kvs::ScreenBase* TimerEventListener::screen( void )
{
    return( m_screen );
}

kvs::WindowBase* TimerEventListener::window( void )
{
    return( m_window );
}

void TimerEventListener::setScreen( kvs::ScreenBase* screen )
{
    m_screen = screen;
}

void TimerEventListener::setWindow( kvs::WindowBase* window )
{
    m_window = window;
}

void TimerEventListener::onEvent( kvs::EventBase* event )
{
    this->update( static_cast<kvs::TimeEvent*>(event) );
}

} // end of namespace kvs
