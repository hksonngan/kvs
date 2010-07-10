/*****************************************************************************/
/**
 *  @file   IdleEventListener.cpp
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
#include "IdleEventListener.h"
#include <kvs/IgnoreUnusedVariable>
#include <kvs/Binary>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new IdleEventListener class.
 */
/*===========================================================================*/
IdleEventListener::IdleEventListener( void )
{
    kvs::EventListener::setEventType( kvsBinary12(1111,1111,1111) );
}

/*===========================================================================*/
/**
 *  @brief  Destructs the IdleEventListener class.
 */
/*===========================================================================*/
IdleEventListener::~IdleEventListener( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Executes the event function.
 *  @param  event [in] pointer to the event
 */
/*===========================================================================*/
void IdleEventListener::onEvent( kvs::EventBase* event )
{
    kvs::IgnoreUnusedVariable( event );

    this->update();
}

} // end of namespace kvs
