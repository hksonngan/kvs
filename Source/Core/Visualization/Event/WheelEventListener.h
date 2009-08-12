/*****************************************************************************/
/**
 *  @file   WheelEventListener.h
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
#ifndef KVS__WHEEL_EVENT_LISTENER_H_INCLUDE
#define KVS__WHEEL_EVENT_LISTENER_H_INCLUDE

#include <kvs/ScreenBase>
#include <kvs/WindowBase>
#include <kvs/EventListener>
#include <kvs/WheelEvent>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  WheelEventListener class.
 */
/*===========================================================================*/
class WheelEventListener : public kvs::EventListener
{
private:

    kvs::ScreenBase* m_screen; ///< pointer to the screen
    kvs::WindowBase* m_window; ///< pointer to the window

public:

    WheelEventListener( void );

    virtual ~WheelEventListener( void );

public:

    virtual void update( kvs::WheelEvent* event ) = 0;

    kvs::ScreenBase* screen( void );

    kvs::WindowBase* window( void );

    void setScreen( kvs::ScreenBase* screen );

    void setWindow( kvs::WindowBase* window );

private:

    void onEvent( kvs::EventBase* event );
};

} // end of namespace kvs

#endif // KVS__WHEEL_EVENT_LISTENER_H_INCLUDE
