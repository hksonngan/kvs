/*****************************************************************************/
/**
 *  @file   LineRenderer.cpp
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
#include "LineRenderer.h"
#include "CommandName.h"
#include "ObjectInformation.h"
#include "FileChecker.h"
#include <kvs/File>
#include <kvs/PipelineModule>
#include <kvs/VisualizationPipeline>
#include <kvs/LineRenderer>
#include <kvs/glut/Screen>
#include <kvs/glut/Application>


namespace kvsview
{

namespace LineRenderer
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new Argument class for a line renderer.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Argument::Argument( int argc, char** argv ):
    kvsview::Argument::Common( argc, argv, kvsview::LineRenderer::CommandName )
{
    // Parameters for the line renderer class.
    add_option( kvsview::LineRenderer::CommandName, kvsview::LineRenderer::Description, 0 );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new Main class for a line renderer.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Main::Main( int argc, char** argv )
{
    m_argc = argc;
    m_argv = argv;
}

/*===========================================================================*/
/**
 *  @brief  Executes main process.
 */
/*===========================================================================*/
const bool Main::exec( void )
{
    kvs::glut::Application app( m_argc, m_argv );

    // Parse specified arguments.
    kvsview::LineRenderer::Argument arg( m_argc, m_argv );
    if( !arg.parse() ) return( false );

    // Create a global and screen class.
    kvs::glut::Screen screen;
    screen.setSize( 512, 512 );
    screen.setTitle( kvsview::CommandName + " - " + kvsview::LineRenderer::CommandName );
    arg.applyTo( screen );

    // Check the input data.
    m_input_name = arg.value<std::string>();
    if ( !kvsview::FileChecker::ImportableLine( m_input_name ) )
    {
        kvsMessageError("%s is not line data.", m_input_name.c_str());
        return( false );
    }

    // Visualization pipeline.
    kvs::VisualizationPipeline pipe( m_input_name );
    pipe.import();

    // Verbose information.
    if ( arg.verboseMode() )
    {
        std::cout << "IMPORTED OBJECT" << std::endl;
        std::cout << kvsview::ObjectInformation( pipe.object() ) << std::endl;
        std::cout << std::endl;
    }

    // Set a line renderer.
    kvs::PipelineModule renderer( new kvs::LineRenderer );
    pipe.connect( renderer );
    if ( !pipe.exec() )
    {
        kvsMessageError("Cannot execute the visulization pipeline.");
        return( false );
    }
    screen.setPipeline( &pipe );

    // Verbose information.
    if ( arg.verboseMode() )
    {
        std::cout << "RENDERERED OBJECT" << std::endl;
        std::cout << kvsview::ObjectInformation( pipe.object() ) << std::endl;
        std::cout << std::endl;
        std::cout << "VISUALIZATION PIPELINE" << std::endl;
        std::cout << pipe << std::endl;
    }

    // Apply the specified parameters to the global and the visualization pipeline.
    arg.applyTo( screen, pipe );

    // Show the screen.
    screen.show();

    app.attach( &screen );

    return( app.run() );
}

} // end of namespace LineRenderer

} // end of namespace kvsview
