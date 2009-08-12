/*****************************************************************************/
/**
 *  @file   MousePressEventListener.cpp
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
#include "MousePressEventListener.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new MousePressEventListener class.
 */
/*===========================================================================*/
MousePressEventListener::MousePressEventListener( void ):
    m_screen( NULL ),
    m_window( NULL )
{
    kvs::EventListener::setEventType( kvs::EventBase::MousePressEvent );
}

/*===========================================================================*/
/**
 *  @brief  Destructs the MousePressEventListener class.
 */
/*===========================================================================*/
MousePressEventListener::~MousePressEventListener( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the screen.
 *  @return pointer to the screen
 */
/*===========================================================================*/
kvs::ScreenBase* MousePressEventListener::screen( void )
{
    return( m_screen );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the window.
 *  @return pointer to the window
 */
/*===========================================================================*/
kvs::WindowBase* MousePressEventListener::window( void )
{
    return( m_window );
}

/*===========================================================================*/
/**
 *  @brief  Sets a pointer to the screen.
 *  @param  screen [in] pointer to the screen
 */
/*===========================================================================*/
void MousePressEventListener::setScreen( kvs::ScreenBase* screen )
{
    m_screen = screen;
}

/*===========================================================================*/
/**
 *  @brief  Sets a pointer to the window.
 *  @param  window [in] pointer to the window
 */
/*===========================================================================*/
void MousePressEventListener::setWindow( kvs::WindowBase* window )
{
    m_window = window;
}

/*===========================================================================*/
/**
 *  @brief  Executes the event function.
 *  @param  event [in] pointer to the event
 */
/*===========================================================================*/
void MousePressEventListener::onEvent( kvs::EventBase* event )
{
    this->update( static_cast<kvs::MouseEvent*>(event) );
}

} // end of namespace kvs
