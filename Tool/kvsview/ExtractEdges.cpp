/*****************************************************************************/
/**
 *  @file   ExtractEdges.cpp
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
#include "ExtractEdges.h"
#include "CommandName.h"
#include "ObjectInformation.h"
#include "FileChecker.h"
#include <kvs/File>
#include <kvs/PipelineModule>
#include <kvs/VisualizationPipeline>
#include <kvs/ExtractEdges>
#include <kvs/glut/Application>
#include <kvs/glut/Screen>
#include <kvs/glut/LegendBar>
#include <kvs/glut/OrientationAxis>


namespace kvsview
{

namespace ExtractEdges
{

class LegendBar : public kvs::glut::LegendBar
{
public:

    LegendBar( kvs::ScreenBase* screen ):
        kvs::glut::LegendBar( screen )
    {
        setWidth( 200 );
        setHeight( 50 );
    }

    void screenResized( void )
    {
        setX( screen()->width() - width() );
        setY( screen()->height() - height() );
    }
};

class OrientationAxis : public kvs::glut::OrientationAxis
{
public:

    OrientationAxis( kvs::ScreenBase* screen ):
        kvs::glut::OrientationAxis( screen )
    {
        setMargin( 10 );
        setSize( 90 );
        setBoxType( kvs::glut::OrientationAxis::SolidBox );
        enableAntiAliasing();
    }

    void screenResized( void )
    {
        setY( screen()->height() - height() );
    }
};

/*===========================================================================*/
/**
 *  @brief  Constructs a new Argument class.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Argument::Argument( int argc, char** argv ):
    kvsview::Argument::Common( argc, argv, "ExtractEdges")
{
    // Parameters for the isosurface class.
    add_option( kvsview::ExtractEdges::CommandName, kvsview::ExtractEdges::Description, 0 );
    add_option( "s", "Line size. (default: 1)", 1, false );
    add_option( "t", "Transfer function file. (optional: <filename>)", 1, false );
}

/*===========================================================================*/
/**
 *  @brief  Returns a line size.
 *  @return line size
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
    ExtractEdges::Argument arg( m_argc, m_argv );
    if( !arg.parse() ) return( false );

    // Create a global and screen class.
    kvs::glut::Screen screen( &app );
    screen.setSize( 512, 512 );
    screen.setTitle( kvsview::CommandName + " - " + kvsview::ExtractEdges::CommandName );
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
    kvs::PipelineModule mapper( new kvs::ExtractEdges );
    const kvs::Real32 size = arg.size();
    const kvs::TransferFunction function = arg.transferFunction();
    mapper.get<kvs::ExtractEdges>()->setSize( size );
    mapper.get<kvs::ExtractEdges>()->setTransferFunction( function );

    // Construct the visualization pipeline.
    pipe.connect( mapper );
    if ( !pipe.exec() )
    {
        kvsMessageError("Cannot execute the visulization pipeline.");
        return( false );
    }
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

    // Legend bar.
    ExtractEdges::LegendBar legend_bar( &screen );
    legend_bar.setColorMap( arg.transferFunction().colorMap() );
    legend_bar.show();

    // Orientation axis.
    ExtractEdges::OrientationAxis orientation_axis( &screen );
    orientation_axis.show();

    // Apply the specified parameters to the global and the visualization pipeline.
    arg.applyTo( screen, pipe );

    // Show the screen.
    screen.show();

    return( app.run() );
}

} // end of namespace ExtractEdges

} // end of namespace kvsview