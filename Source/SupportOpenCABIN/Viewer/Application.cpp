/*****************************************************************************/
/**
 *  @file   Application.cpp
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
#include "Application.h"

#include <iostream>
#include <string>
#include <kvs/File>

// Static parameters.
namespace { bool QuitFlag = false; }
namespace { bool DoneFlag = false; }
namespace { bool MasterFlag = false; }
namespace { std::string Name = "unknown"; }

namespace
{

void SetApplicationName( int argc, char** argv )
{
    for ( int i = 0; i < argc; i++ )
    {
        kvs::File file( argv[i] );
        if ( file.extension() == "so" )
        {
            ::Name = file.baseName();
            break;
        }
    }
}

void ExitFunction( void )
{
    ::QuitFlag = true;
}

}


namespace kvs
{

namespace opencabin
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new Application class.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Application::Application( int argc, char** argv ):
    kvs::ApplicationBase( argc, argv )
{
    static bool flag = true;
    if ( flag )
    {
        ::SetApplicationName( argc, argv );
        atexit( ::ExitFunction );
        flag = false;
    }
}

/*===========================================================================*/
/**
 *  @brief  Destructs the Application class.
 */
/*===========================================================================*/
Application::~Application( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Runs the GLUT application.
 *  @return true, if the process is done successfully
 */
/*===========================================================================*/
int Application::run( void )
{
    /* All processes in the main function renamed as kvsOpenCABINMainFunction
     * have been done here.
     */
    ::DoneFlag = true;

    // Infinite loop.
    for ( ; ; ) if ( ::QuitFlag ) break;

    return( true );
}

/*===========================================================================*/
/**
 *  @brief  Quits the application.
 */
/*===========================================================================*/
void Application::quit( void )
{
    exit(0);
}

const std::string Application::Name( void )
{
    return( ::Name );
}

const bool Application::IsDone( void )
{
    return( ::DoneFlag );
}

const bool Application::IsMaster( void )
{
    return( ::MasterFlag );
}

const bool Application::IsRenderer( void )
{
    return( !::MasterFlag );
}

void Application::SetAsMaster( void )
{
    ::MasterFlag = true;
}

void Application::SetAsRenderer( void )
{
    ::MasterFlag = false;
}

} // end of namespace opencabin

} // end of namespace kvs
