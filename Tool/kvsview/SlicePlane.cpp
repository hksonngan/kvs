/*****************************************************************************/
/**
 *  @file   SlicePlane.cpp
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
#include "SlicePlane.h"
#include "CommandName.h"
#include "ObjectInformation.h"
#include "FileChecker.h"
#include <kvs/File>
#include <kvs/PipelineModule>
#include <kvs/VisualizationPipeline>
#include <kvs/SlicePlane>
#include <kvs/glut/Screen>
#include <kvs/glut/Application>
#include <kvs/glut/LegendBar>
#include <kvs/glut/OrientationAxis>


namespace kvsview
{

namespace SlicePlane
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
 *  @brief  Constructs a new Argument class for a slice plane mapper.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Argument::Argument( int argc, char** argv ):
    kvsview::Argument::Common( argc, argv, "SlicePlane")
{
    // Parameters for the isosurface class.
    add_option( kvsview::SlicePlane::CommandName, kvsview::SlicePlane::Description, 0 );
    add_option( "p", "Position of any point in the plane. (optional: <x y z>)", 3, false );
    add_option( "n", "Normal vector. (optional: <nx ny nz>)", 3, false );
    add_option( "c", "Coefficients of the plane c1 x + c2 y + c3 z + c4 = 0. (optional: <c1 c2 c3 c4>)", 4, false );
    add_option( "t", "Transfer function file. (optional: <filename>)", 1, false );
}

/*===========================================================================*/
/**
 *  @brief  Returns coefficients of the plane.
 *  @return coefficients
 */
/*===========================================================================*/
const kvs::Vector4f Argument::coefficients( void )
{
    const kvs::Vector4f default_value( 0.0f, 0.0f, 0.0f, 0.0f );

    if ( this->hasOption("c") )
    {
        const kvs::Vector4f coefficients(
            this->optionValue<float>("c",0),
            this->optionValue<float>("c",1),
            this->optionValue<float>("c",2),
            this->optionValue<float>("c",3) );

        return( coefficients );
    }
    else return( default_value );
}

/*===========================================================================*/
/**
 *  @brief  Returns a position of any point in the plane.
 *  @return position of the point
 */
/*===========================================================================*/
const kvs::Vector3f Argument::point( void )
{
    const kvs::Vector3f default_value( 0.0f, 0.0f, 0.0f );

    if ( this->hasOption("p") )
    {
        const kvs::Vector3f point(
            this->optionValue<float>("p",0),
            this->optionValue<float>("p",1),
            this->optionValue<float>("p",2) );

        return( point );
    }
    else return( default_value );
}

/*===========================================================================*/
/**
 *  @brief  Returns a normal vector.
 *  @return normal vector
 */
/*===========================================================================*/
const kvs::Vector3f Argument::normal( void )
{
    const kvs::Vector3f default_value( 0.0f, 0.0f, 0.0f );

    if ( this->hasOption("n") )
    {
        const kvs::Vector3f point(
            this->optionValue<float>("n",0),
            this->optionValue<float>("n",1),
            this->optionValue<float>("n",2) );

        return( point );
    }
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
    SlicePlane::Argument arg( m_argc, m_argv );
    if( !arg.parse() ) return( false );

    // Create a global and screen class.
    kvs::glut::Screen screen( &app );
    screen.setSize( 512, 512 );
    screen.setTitle( kvsview::CommandName + " - " + kvsview::SlicePlane::CommandName );
    arg.applyTo( screen );

    // Check the input point data.
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
    SlicePlane::LegendBar legend_bar( &screen );
    legend_bar.setColorMap( arg.transferFunction().colorMap() );
    legend_bar.show();

    // Orientation axis.
    SlicePlane::OrientationAxis orientation_axis( &screen );
    orientation_axis.show();

    // Set up the slice plane class.
    kvs::PipelineModule mapper( new kvs::SlicePlane );
    if ( arg.hasOption("c") )
    {
        const kvs::Vector4f coefficients( arg.coefficients() );
        mapper.get<kvs::SlicePlane>()->setPlane( coefficients );
    }
    else if ( arg.hasOption("p") && arg.hasOption("n") )
    {
        const kvs::Vector3f point( arg.point() );
        const kvs::Vector3f normal( arg.normal() );
        mapper.get<kvs::SlicePlane>()->setPlane( point, normal );
    }
    else
    {
        const kvs::Vector3f point( pipe.object()->objectCenter() );
        const kvs::Vector3f normal( 0.0f, 0.0f, 1.0f );
        mapper.get<kvs::SlicePlane>()->setPlane( point, normal );
    }

    const kvs::TransferFunction function = arg.transferFunction();
    mapper.get<kvs::SlicePlane>()->setTransferFunction( function );

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

    return( app.run() );
}

} // end of namespace SlicePlane

} // end of namespace kvsview
