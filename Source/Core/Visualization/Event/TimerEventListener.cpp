/*****************************************************************************/
/**
 *  @file   TimerEventListener.cpp
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
#include "TimerEventListener.h"


namespace kvs
{

TimerEventListener::TimerEventListener( void )
{
    kvs::EventListener::setEventType( kvs::EventBase::TimerEvent );
}

TimerEventListener::~TimerEventListener( void )
{
}

void TimerEventListener::onEvent( kvs::EventBase* event )
{
    this->update( static_cast<kvs::TimeEvent*>(event) );
}

} // end of namespace kvs