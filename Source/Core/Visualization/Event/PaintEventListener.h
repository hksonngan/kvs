/*****************************************************************************/
/**
 *  @file   PaintEventListener.h
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
#ifndef KVS__PAINT_EVENT_LISTENER_H_INCLUDE
#define KVS__PAINT_EVENT_LISTENER_H_INCLUDE

#include <kvs/ScreenBase>
#include <kvs/WindowBase>
#include <kvs/EventListener>
#include <kvs/EventBase>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  PaintEventListener class.
 */
/*===========================================================================*/
class PaintEventListener : public kvs::EventListener
{
private:

    kvs::ScreenBase* m_screen; ///< pointer to the screen
    kvs::WindowBase* m_window; ///< pointer to the window

public:

    PaintEventListener( void );

    virtual ~PaintEventListener( void );

public:

    virtual void update( void ) = 0;

    kvs::ScreenBase* screen( void );

    kvs::WindowBase* window( void );

    void setScreen( kvs::ScreenBase* screen );

    void setWindow( kvs::WindowBase* window );

private:

    void onEvent( kvs::EventBase* event = 0 );
};

} // end of namespace kvs

#endif // KVS__PAINT_EVENT_LISTENER_H_INCLUDE
