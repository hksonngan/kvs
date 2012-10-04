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
#include <string>


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
protected:

    std::vector<kvs::EventListener*> m_listeners; ///< list of the event listener

public:

    EventHandler();
    virtual ~EventHandler();

    void attach( kvs::EventListener* listener );
    void detach( const kvs::EventListener* listener );
    void detach( const std::string& name );
    void notify( kvs::EventBase* event );
    void clear();
};

} // end of namespace kvs

#endif // KVS__EVENT_HANDLER_H_INCLUDE
