/*****************************************************************************/
/**
 *  @file   MouseMoveEventListener.h
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
#ifndef KVS__MOUSE_MOVE_EVENT_LISTENER_H_INCLUDE
#define KVS__MOUSE_MOVE_EVENT_LISTENER_H_INCLUDE

#include <kvs/EventListener>
#include <kvs/MouseEvent>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  MouseMoveEventListener class.
 */
/*===========================================================================*/
class MouseMoveEventListener : public kvs::EventListener
{
public:

    MouseMoveEventListener( void );

    virtual ~MouseMoveEventListener( void );

public:

    virtual void update( kvs::MouseEvent* event ) = 0;

private:

    void onEvent( kvs::EventBase* event );
};

} // end of namespace kvs

#endif // KVS__MOUSE_MOVE_EVENT_LISTENER_H_INCLUDE
