/*****************************************************************************/
/**
 *  @file   WheelEventListener.cpp
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
#include "WheelEventListener.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new WheelEventListener class.
 */
/*===========================================================================*/
WheelEventListener::WheelEventListener( void ):
    m_screen( NULL ),
    m_window( NULL )
{
    kvs::EventListener::setEventType( kvs::EventBase::WheelEvent );
}

/*===========================================================================*/
/**
 *  @brief  Destructs the WheelEventListener class.
 */
/*===========================================================================*/
WheelEventListener::~WheelEventListener( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the screen.
 *  @return pointer to the screen
 */
/*===========================================================================*/
kvs::ScreenBase* WheelEventListener::screen( void )
{
    return( m_screen );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the window.
 *  @return pointer to the window
 */
/*===========================================================================*/
kvs::WindowBase* WheelEventListener::window( void )
{
    return( m_window );
}

/*===========================================================================*/
/**
 *  @brief  Sets a pointer to the screen.
 *  @param  screen [in] pointer to the screen
 */
/*===========================================================================*/
void WheelEventListener::setScreen( kvs::ScreenBase* screen )
{
    m_screen = screen;
}

/*===========================================================================*/
/**
 *  @brief  Sets a pointer to the window.
 *  @param  window [in] pointer to the window
 */
/*===========================================================================*/
void WheelEventListener::setWindow( kvs::WindowBase* window )
{
    m_window = window;
}

/*===========================================================================*/
/**
 *  @brief  Executes the event function.
 *  @param  event [in] pointer to the event
 */
/*===========================================================================*/
void WheelEventListener::onEvent( kvs::EventBase* event )
{
    this->update( static_cast<kvs::WheelEvent*>(event) );
}

} // end of namespace kvs
