/*****************************************************************************/
/**
 *  @file   ExtractVertices.cpp
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
#include "ExtractVertices.h"
#include "CommandName.h"
#include "ObjectInformation.h"
#include "FileChecker.h"
#include <kvs/File>
#include <kvs/PipelineModule>
#include <kvs/VisualizationPipeline>
#include <kvs/ExtractVertices>
#include <kvs/glut/Application>
#include <kvs/glut/Screen>


namespace kvsview
{

namespace ExtractVertices
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new Argument class.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Argument::Argument( int argc, char** argv ):
    kvsview::Argument::Common( argc, argv, "ExtractVertices")
{
    // Parameters for the isosurface class.
    add_option( kvsview::ExtractVertices::CommandName, kvsview::ExtractVertices::Description, 0 );
    add_option( "s", "Point size. (default: 1)", 1, false );
    add_option( "t", "Transfer function file. (optional: <filename>)", 1, false );
}

/*===========================================================================*/
/**
 *  @brief  Returns a point size.
 *  @return point size
 */
/*===========================================================================*/
const kvs::Real32 Argument::size( void )
{
    const kvs::Real32 default_value = 0.0;

    if ( this->hasOption("s") ) return( this->optionValue<kvs::Real32>("s") );
    else return( default_value );
}

/*===========================================================================*/
/**
 *  @brief  Returns a transfer function.
 *  @return transfer function
 */
/*===========================================================================*/
const kvs::TransferFunction Argument::transferFunction( void )
{
    if ( this->hasOption("t") )
    {
        const std::string filename = this->optionValue<std::string>("t");
        return( kvs::TransferFunction( filename ) );
    }
    else
    {
        const size_t resolution = 256;
        return( kvs::TransferFunction( resolution ) );
    }
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new Main class.
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
    // GLUT viewer application.
    kvs::glut::Application app( m_argc, m_argv );

    // Parse specified arguments.
    kvsview::ExtractVertices::Argument arg( m_argc, m_argv );
    if( !arg.parse() ) return( false );

    // Create a global and screen class.
    kvs::glut::Screen screen;
    screen.setSize( 512, 512 );
    screen.setTitle( kvsview::CommandName + " - " + kvsview::ExtractVertices::CommandName );
    arg.applyTo( screen );

    // Check the input volume data.
    m_input_name = arg.value<std::string>();
    if ( !(kvsview::FileChecker::ImportableStructuredVolume( m_input_name ) ||
           kvsview::FileChecker::ImportableUnstructuredVolume( m_input_name ) ) )
    {
        kvsMessageError("%s is not volume data.", m_input_name.c_str());
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

    // Set up the isosurface class.
    kvs::PipelineModule mapper( new kvs::ExtractVertices );
    const kvs::Real32 size = arg.size();
    const kvs::TransferFunction function = arg.transferFunction();
    mapper.get<kvs::ExtractVertices>()->setSize( size );
    mapper.get<kvs::ExtractVertices>()->setTransferFunction( function );

    // Construct the visualization pipeline.
    pipe.connect( mapper );
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

} // end of namespace ExtractVertices

} // end of namespace kvsview
