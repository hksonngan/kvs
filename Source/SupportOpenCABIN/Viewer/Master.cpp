/*****************************************************************************/
/**
 *  @file   Master.cpp
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
#include "OpenCABIN.h"
#include "Master.h"
#include "Application.h"
#include "Configuration.h"
#include <kvs/Thread>
#include <iostream>


// Static parameters.
namespace { kvs::opencabin::Master* context = 0; }

/* The 'kvsOpenCABINMainFunction' function is defined in the user program.
 * The main function defined in the user program is renamed to
 * 'kvsOpenCABINMainFunction' by including the '<kvs/opencabin/Application>'.
 */
extern int kvsOpenCABINMainFunction( int argc, char** argv );

/*===========================================================================*/
/**
 *  @brief  Infinite loop thread class.
 */
/*===========================================================================*/
class InfiniteLoopThread : public kvs::Thread
{
protected:

    int m_argc;    ///< argument count
    char** m_argv; ///< argument values

public:

    InfiniteLoopThread( int argc, char** argv )
    {
        m_argc = argc;
        m_argv = argv;
    }

    void run( void )
    {
        kvsOpenCABINMainFunction( m_argc, m_argv );
    }
};

/*===========================================================================*/
/**
 *  @brief  Initialization function for master program (OpenCABIN predefined function).
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 *  @return pointer to the user defined data
 */
/*===========================================================================*/
void* minit( int argc, char** argv )
{
    kvs::opencabin::Application::SetAsMaster();

    static ::InfiniteLoopThread thread( argc, argv ); thread.start();
    if ( ::context ) ::context->initializeEvent();
    for ( ; ; ) if ( kvs::opencabin::Application::IsDone() ) break;

    return( 0 );
}

/*===========================================================================*/
/**
 *  @brief  Idle function for master program (OpenCABIN predefined function).
 *  @param  pdata [in] pointer to the user defined data returned from minit
 */
/*===========================================================================*/
void midle( void*pdata )
{
    if ( ::context ) ::context->idleEvent();
}

/*===========================================================================*/
/**
 *  @brief  Repeat function for master program (OpenCABIN predefined function).
 *  @param  pdata [in] pointer to the user defined data returned from minit
 */
/*===========================================================================*/
void mrepeat( void* pdata )
{
    // This function is never called from the master program in OpenCABIN???
}

/*===========================================================================*/
/**
 *  @brief  Cleanup function for master program (OpenCABIN predefined function).
 *  @param  pdata [in] pointer to the user defined data returned from minit
 */
/*===========================================================================*/
void mcleanup( void* pdata )
{
    // Do nothing.
}


namespace kvs
{

namespace opencabin
{

/*===========================================================================*/
/**
 *  @brief  Construct a new Master class.
 *  @param  application [in] pointer to the applicataion
 */
/*===========================================================================*/
Master::Master( kvs::opencabin::Application* application )
{
    m_initialize_event_handler = new kvs::EventHandler();
    m_idle_event_handler = new kvs::EventHandler();

    ::context = this;
}

/*===========================================================================*/
/**
 *  @brief  Destruct the Master class.
 */
/*===========================================================================*/
Master::~Master( void )
{
    if ( m_initialize_event_handler ) { delete m_initialize_event_handler; }
    if ( m_idle_event_handler ) { delete m_idle_event_handler; }
}

/*===========================================================================*/
/**
 *  @brief  Initialize event.
 */
/*===========================================================================*/
void Master::initializeEvent( void )
{
    if ( kvs::opencabin::Application::IsMaster() )
    {
        m_initialize_event_handler->notify();
    }
}

/*===========================================================================*/
/**
 *  @brief  Idle event.
 */
/*===========================================================================*/
void Master::idleEvent( void )
{
    if ( kvs::opencabin::Application::IsMaster() )
    {
        m_idle_event_handler->notify();
    }
}

/*===========================================================================*/
/**
 *  @brief  Adds an intialize event listener.
 *  @param  event [in] pointer to an initialize event listener
 */
/*===========================================================================*/
void Master::addInitializeEvent( kvs::InitializeEventListener* event )
{
    event->setScreen( 0 );
    m_initialize_event_handler->attach( event );
}

/*===========================================================================*/
/**
 *  @brief  Adds an idle event listener.
 *  @param  event [in] pointer to an idle event listener
 */
/*===========================================================================*/
void Master::addIdleEvent( kvs::IdleEventListener* event )
{
    event->setScreen( 0 );
    m_idle_event_handler->attach( event );
}

} // end of namespace opencabin

} // end of namespace kvs
