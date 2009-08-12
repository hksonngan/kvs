/*****************************************************************************/
/**
 *  @file   OrthoSlice.cpp
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
#include "OrthoSlice.h"
#include "CommandName.h"
#include "ObjectInformation.h"
#include "FileChecker.h"
#include <kvs/File>
#include <kvs/PipelineModule>
#include <kvs/VisualizationPipeline>
#include <kvs/OrthoSlice>
#include <kvs/glut/Screen>
#include <kvs/glut/Application>


namespace kvsview
{

namespace OrthoSlice
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new Argument class for a orthogonal slice plane mapper.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Argument::Argument( int argc, char** argv ):
    kvsview::Argument::Common( argc, argv, "OrthoSlice")
{
    // Parameters for the isosurface class.
    add_option( kvsview::OrthoSlice::CommandName, kvsview::OrthoSlice::Description, 0 );
    add_option( "p", "Position of the point on the spefied axis. (default: 0)", 1, false );
    add_option( "a", "Axis (x:0, y:1, z:2). (default: 0)", 1, false );
    add_option( "t", "Transfer function file. (optional: <filename>)", 1, false );
}

/*===========================================================================*/
/**
 *  @brief  Returns a position of any point in the plane.
 *  @return position of the point
 */
/*===========================================================================*/
const float Argument::position( void )
{
    const float default_value( 0.0f );

    if ( this->hasOption("p") )
    {
        const float position( this->optionValue<float>("p") );

        return( position );
    }
    else return( default_value );
}

/*===========================================================================*/
/**
 *  @brief  Returns a normal vector.
 *  @return normal vector
 */
/*===========================================================================*/
const kvs::OrthoSlice::AlignedAxis Argument::axis( void )
{
    const kvs::OrthoSlice::AlignedAxis default_value( kvs::OrthoSlice::ZAxis );

    if ( this->hasOption("a") )
    {
        const int axis( this->optionValue<int>("a") );
        switch ( axis )
        {
        case 0: return( kvs::OrthoSlice::XAxis );
        case 1: return( kvs::OrthoSlice::YAxis );
        case 2: return( kvs::OrthoSlice::ZAxis );
        default:
            kvsMessageError("Cannot specify 0, 1, or 2 for the option 'a'.");
            break;
        }
    }

    return( default_value );
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
    kvs::glut::Application app( m_argc, m_argv );

    // Parse specified arguments.
    kvsview::OrthoSlice::Argument arg( m_argc, m_argv );
    if( !arg.parse() ) return( false );

    // Create a global and screen class.
    kvs::glut::Screen screen;
    screen.setSize( 512, 512 );
    screen.setTitle( kvsview::CommandName + " - " + kvsview::OrthoSlice::CommandName );
    arg.applyTo( screen );

    // Check the input point data.
    m_input_name = arg.value<std::string>();
    if ( !kvsview::FileChecker::ImportableStructuredVolume( m_input_name ) )
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

    // Set up the slice plane class.
    kvs::PipelineModule mapper( new kvs::OrthoSlice );
    const float position = arg.hasOption("p") ? arg.position() : pipe.object()->objectCenter().z();
    const kvs::OrthoSlice::AlignedAxis axis( arg.axis() );
    const kvs::TransferFunction function = arg.transferFunction();
    mapper.get<kvs::OrthoSlice>()->setPlane( position, axis );
    mapper.get<kvs::OrthoSlice>()->setTransferFunction( function );

    // Construct the visualization pipeline.
    pipe.connect( mapper );
    if ( !pipe.exec() )
    {
        kvsMessageError("Cannot execute the visulization pipeline.");
        return( false );
    }
    pipe.renderer()->disableShading();
    screen.registerObject( &pipe );

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

} // end of namespace OrthoSlice

} // end of namespace kvsview
