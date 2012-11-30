/*****************************************************************************/
/**
 *  @file   TimerEventListener.cpp
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
#include "TimerEventListener.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new TimerEventListener class.
 */
/*===========================================================================*/
TimerEventListener::TimerEventListener()
{
    kvs::EventListener::setEventType( kvs::EventBase::TimerEvent );
}

/*===========================================================================*/
/**
 *  @brief  Destroys the TimerEventListener class.
 */
/*===========================================================================*/
TimerEventListener::~TimerEventListener()
{
}

/*===========================================================================*/
/**
 *  @brief  Executes the event function.
 *  @param  event [in] pointer to the event
 */
/*===========================================================================*/
void TimerEventListener::onEvent( kvs::EventBase* event )
{
    this->update( static_cast<kvs::TimeEvent*>(event) );
}

} // end of namespace kvs
