/*****************************************************************************/
/**
 *  @file   PaintEventListener.cpp
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
#include "PaintEventListener.h"
#include <kvs/IgnoreUnusedVariable>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new PaintEventListener class.
 */
/*===========================================================================*/
PaintEventListener::PaintEventListener( void ):
    m_screen( NULL ),
    m_window( NULL )
{
    kvs::EventListener::setEventType( kvs::EventBase::PaintEvent );
}

/*===========================================================================*/
/**
 *  @brief  Destructs the PaintEventListener class.
 */
/*===========================================================================*/
PaintEventListener::~PaintEventListener( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the screen.
 *  @return pointer to the screen
 */
/*===========================================================================*/
kvs::ScreenBase* PaintEventListener::screen( void )
{
    return( m_screen );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the window.
 *  @return pointer to the window
 */
/*===========================================================================*/
kvs::WindowBase* PaintEventListener::window( void )
{
    return( m_window );
}

/*===========================================================================*/
/**
 *  @brief  Sets a pointer to the screen.
 *  @param  screen [in] pointer to the screen
 */
/*===========================================================================*/
void PaintEventListener::setScreen( kvs::ScreenBase* screen )
{
    m_screen = screen;
}

/*===========================================================================*/
/**
 *  @brief  Sets a pointer to the window.
 *  @param  window [in] pointer to the window
 */
/*===========================================================================*/
void PaintEventListener::setWindow( kvs::WindowBase* window )
{
    m_window = window;
}

/*===========================================================================*/
/**
 *  @brief  Executes the event function.
 *  @param  event [in] pointer to the event
 */
/*===========================================================================*/
void PaintEventListener::onEvent( kvs::EventBase* event )
{
    this->update();
}

} // end of namespace kvs
