/*****************************************************************************/
/**
 *  @file   ExternalFaces.cpp
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
#include "ExternalFaces.h"
#include "CommandName.h"
#include "ObjectInformation.h"
#include "FileChecker.h"
#include <kvs/File>
#include <kvs/PipelineModule>
#include <kvs/VisualizationPipeline>
#include <kvs/ExternalFaces>
#include <kvs/glut/Application>
#include <kvs/glut/Screen>
#include <kvs/glut/LegendBar>
#include <kvs/glut/OrientationAxis>


namespace kvsview
{

namespace ExternalFaces
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
    kvsview::Argument::Common( argc, argv, "ExternalFaces")
{
    // Parameters for the isosurface class.
    add_option( kvsview::ExternalFaces::CommandName, kvsview::ExternalFaces::Description, 0 );
    add_option( "a", "Opacity (alpha value). (default: 255)", 1, false );
    add_option( "t", "Transfer function file. (optional: <filename>)", 1, false );
}

/*===========================================================================*/
/**
 *  @brief  Returns a opacity value.
 *  @return opacity value
 */
/*===========================================================================*/
const kvs::UInt8 Argument::opacity( void )
{
    const kvs::UInt8 default_value = 255;

    if ( this->hasOption("a") ) return( this->optionValue<kvs::UInt8>("a") );
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
    kvsview::ExternalFaces::Argument arg( m_argc, m_argv );
    if( !arg.parse() ) return( false );

    // Create a global and screen class.
    kvs::glut::Screen screen( &app );
    screen.setSize( 512, 512 );
    screen.setTitle( kvsview::CommandName + " - " + kvsview::ExternalFaces::CommandName );
    arg.applyTo( screen );

    // Check the input volume data.
    m_input_name = arg.value<std::string>();
    if ( !( kvsview::FileChecker::ImportableStructuredVolume( m_input_name ) ||
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

    // Legend bar.
    ExternalFaces::LegendBar legend_bar( &screen );
    const double min_value = kvs::VolumeObjectBase::DownCast( pipe.object() )->minValue();
    const double max_value = kvs::VolumeObjectBase::DownCast( pipe.object() )->maxValue();
    legend_bar.setColorMap( arg.transferFunction().colorMap() );
    legend_bar.setRange( min_value, max_value );
    legend_bar.show();

    // Orientation axis.
    ExternalFaces::OrientationAxis orientation_axis( &screen );
    orientation_axis.show();

    // Setup an isosurface class.
    kvs::PipelineModule mapper( new kvs::ExternalFaces );
    const kvs::UInt8 opacity = arg.opacity();
    const kvs::TransferFunction function = arg.transferFunction();
    mapper.get<kvs::ExternalFaces>()->setOpacity( opacity );
    mapper.get<kvs::ExternalFaces>()->setTransferFunction( function );

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

    // Apply the specified parameters to the global and the visualization pipeline.
    arg.applyTo( screen, pipe );

    // Show the screen.
    screen.show();

    return( app.run() );
}

} // end of namespace ExternalFaces

} // end of namespace kvsview
