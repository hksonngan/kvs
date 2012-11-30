/*****************************************************************************/
/**
 *  @file   TimeEvent.cpp
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
#include "TimeEvent.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new TimeEvent class.
 */
/*===========================================================================*/
TimeEvent::TimeEvent()
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the TimerEvent class.
 */
/*===========================================================================*/
TimeEvent::~TimeEvent()
{
}

/*===========================================================================*/
/**
 *  @brief  Returns the event type.
 *  @return event type
 */
/*===========================================================================*/
int TimeEvent::type() const
{
    return kvs::EventBase::TimerEvent;
}

} // end of namespace kvs
