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
#include <kvs/File>
#include <kvs/KVSMLObjectLine>
#include <kvs/PipelineModule>
#include <kvs/VisualizationPipeline>
#include <kvs/LineRenderer>
#include <kvs/glut/Global>
#include <kvs/glut/Screen>


namespace
{

inline const bool CheckLineData( const std::string& filename )
{
    if ( kvs::KVSMLObjectLine::CheckFileExtension( filename ) )
    {
        if ( kvs::KVSMLObjectLine::CheckFileFormat( filename ) )
        {
            return( true );
        }
    }

    return( false );
}

} // end of namespace


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
    // Parse specified arguments.
    LineRenderer::Argument arg( m_argc, m_argv );
    if( !arg.parse() ) return( false );

    // Create a global and screen class.
    kvs::glut::Global global( m_argc, m_argv );
    kvs::glut::Screen screen( 512, 512 );
    screen.setTitle( kvsview::CommandName + " - " + kvsview::LineRenderer::CommandName );
    arg.applyTo( screen );

    // Check the input data.
    m_input_name = arg.value<std::string>();
    if ( !::CheckLineData( m_input_name ) )
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
    global.insert( pipe );

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
    arg.applyTo( global, pipe );

    // Show the screen.
    return( screen.show() != 0 );
}

} // end of namespace LineRenderer

} // end of namespace kvsview
