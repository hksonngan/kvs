/*****************************************************************************/
/**
 *  @file   ResizeEventListener.cpp
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
#include "ResizeEventListener.h"
#include <kvs/ResizeEvent>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new ResizeEventListener class.
 */
/*===========================================================================*/
ResizeEventListener::ResizeEventListener( void ):
    m_screen( NULL ),
    m_window( NULL )
{
    kvs::EventListener::setEventType( kvs::EventBase::ResizeEvent );
}

/*===========================================================================*/
/**
 *  @brief  Destructs the ResizeEventListener class.
 */
/*===========================================================================*/
ResizeEventListener::~ResizeEventListener( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the screen.
 *  @return pointer to the screen
 */
/*===========================================================================*/
kvs::ScreenBase* ResizeEventListener::screen( void )
{
    return( m_screen );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the window.
 *  @return pointer to the window
 */
/*===========================================================================*/
kvs::WindowBase* ResizeEventListener::window( void )
{
    return( m_window );
}

/*===========================================================================*/
/**
 *  @brief  Sets a pointer to the screen.
 *  @param  screen [in] pointer to the screen
 */
/*===========================================================================*/
void ResizeEventListener::setScreen( kvs::ScreenBase* screen )
{
    m_screen = screen;
}

/*===========================================================================*/
/**
 *  @brief  Sets a pointer to the window.
 *  @param  window [in] pointer to the window
 */
/*===========================================================================*/
void ResizeEventListener::setWindow( kvs::WindowBase* window )
{
    m_window = window;
}

/*===========================================================================*/
/**
 *  @brief  Executes the event function.
 *  @param  event [in] pointer to the event
 */
/*===========================================================================*/
void ResizeEventListener::onEvent( kvs::EventBase* event )
{
    this->update(
        static_cast<kvs::ResizeEvent*>(event)->width(),
        static_cast<kvs::ResizeEvent*>(event)->height() );
}

} // end of namespace kvs
