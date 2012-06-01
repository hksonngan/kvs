/*****************************************************************************/
/**
 *  @file   EventHandler.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#ifndef KVS__EVENT_HANDLER_H_INCLUDE
#define KVS__EVENT_HANDLER_H_INCLUDE

#include <vector>
#include <cstddef>
#if KVS_ENABLE_DEPRECATED
#include "EventListener.h"
#endif
#include <kvs/ClassName>


namespace kvs
{

class EventListener;
class EventBase;

/*===========================================================================*/
/**
 *  @brief  Event handler class.
 */
/*===========================================================================*/
class EventHandler
{
    kvsClassName( kvs::EventHandler );

protected:

    std::vector<kvs::EventListener*> m_listeners; ///< list of the event listener

public:

    EventHandler( void );

    virtual ~EventHandler( void );

public:

    void attach( kvs::EventListener* listener );

    void detach( kvs::EventListener* listener );

    void clear( void );

    void notify( kvs::EventBase* event = NULL );
};

} // end of namespace kvs

#endif // KVS__EVENT_HANDLER_H_INCLUDE
