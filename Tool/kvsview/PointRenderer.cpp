/*****************************************************************************/
/**
 *  @file   PointRenderer.cpp
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
#include "PointRenderer.h"
#include "CommandName.h"
#include "ObjectInformation.h"
#include <kvs/File>
#include <kvs/KVSMLObjectPoint>
#include <kvs/PipelineModule>
#include <kvs/VisualizationPipeline>
#include <kvs/PointRenderer>
#include <kvs/glut/Global>
#include <kvs/glut/Screen>


namespace
{

inline const bool CheckPointData( const std::string& filename )
{
    if ( kvs::KVSMLObjectPoint::CheckFileExtension( filename ) )
    {
        if ( kvs::KVSMLObjectPoint::CheckFileFormat( filename ) )
        {
            return( true );
        }
    }

    return( false );
}

} // end of namespace


namespace kvsview
{

namespace PointRenderer
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new Argument class for a point renderer.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Argument::Argument( int argc, char** argv ):
    kvsview::Argument::Common( argc, argv, kvsview::PointRenderer::CommandName )
{
    // Parameters for the point renderer class.
    add_option( kvsview::PointRenderer::CommandName, kvsview::PointRenderer::Description, 0 );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new Main class for a point renderer.
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
    PointRenderer::Argument arg( m_argc, m_argv );
    if( !arg.parse() ) return( false );

    // Create a global and screen class.
    kvs::glut::Global global( m_argc, m_argv );
    kvs::glut::Screen screen( 512, 512 );
    screen.setTitle( kvsview::CommandName + " - " + kvsview::PointRenderer::CommandName );
    arg.applyTo( screen );

    // Check the input data.
    m_input_name = arg.value<std::string>();
    if ( !::CheckPointData( m_input_name ) )
    {
        kvsMessageError("%s is not point data.", m_input_name.c_str());
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

    // Set a point renderer.
    kvs::PipelineModule renderer( new kvs::PointRenderer );
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

} // end of namespace PointRenderer

} // end of namespace kvsview
