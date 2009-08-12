/*****************************************************************************/
/**
 *  @file   KeyPressEventListener.h
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
#ifndef KVS__KEY_PRESS_EVENT_LISTENER_H_INCLUDE
#define KVS__KEY_PRESS_EVENT_LISTENER_H_INCLUDE

#include <kvs/ScreenBase>
#include <kvs/WindowBase>
#include <kvs/EventListener>
#include <kvs/KeyEvent>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  KeyPressEventListener class.
 */
/*===========================================================================*/
class KeyPressEventListener : public kvs::EventListener
{
private:

    kvs::ScreenBase* m_screen; ///< pointer to the screen
    kvs::WindowBase* m_window; ///< pointer to the window

public:

    KeyPressEventListener( void );

    virtual ~KeyPressEventListener( void );

public:

    virtual void update( kvs::KeyEvent* event ) = 0;

    kvs::ScreenBase* screen( void );

    kvs::WindowBase* window( void );

    void setScreen( kvs::ScreenBase* screen );

    void setWindow( kvs::WindowBase* window );

private:

    void onEvent( kvs::EventBase* event );
};

} // end of namespace kvs

#endif // KVS__KEY_PRESS_EVENT_LISTENER_H_INCLUDE
