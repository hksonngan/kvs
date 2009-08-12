/*****************************************************************************/
/**
 *  @file   Isosurface.cpp
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
#include "Isosurface.h"
#include "CommandName.h"
#include "ObjectInformation.h"
#include "FileChecker.h"
#include <kvs/File>
#include <kvs/KVSMLObjectStructuredVolume>
#include <kvs/KVSMLObjectUnstructuredVolume>
#include <kvs/AVSField>
#include <kvs/AVSUcd>
#include <kvs/PipelineModule>
#include <kvs/VisualizationPipeline>
#include <kvs/Isosurface>
#include <kvs/glut/Screen>
#include <kvs/glut/Application>


namespace kvsview
{

namespace Isosurface
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new Argument class for a point renderer.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Argument::Argument( int argc, char** argv ):
    kvsview::Argument::Common( argc, argv, "Isosurface")
{
    // Parameters for the isosurface class.
    add_option( kvsview::Isosurface::CommandName, kvsview::Isosurface::Description, 0 );
    add_option( "l", "Isosurface level. (default: 0)", 1, false );
    add_option( "n", "Normal vector type; 'poly[gon]' 'vert[ex]'. (default: poly)", 1, false );
    add_option( "t", "Transfer function file. (optional: <filename>)", 1, false );
}

/*===========================================================================*/
/**
 *  @brief  Returns a isolevel.
 *  @return subpixel level
 */
/*===========================================================================*/
const kvs::Real64 Argument::isolevel( void )
{
    const kvs::Real64 default_value = 0.0;

    if ( this->hasOption("l") ) return( this->optionValue<kvs::Real64>("l") );
    else return( default_value );
}

/*===========================================================================*/
/**
 *  @brief  Returns a polygon normal vector type.
 *  @return normal vector type
 */
/*===========================================================================*/
const kvs::PolygonObject::NormalType Argument::normalType( void )
{
    const kvs::PolygonObject::NormalType default_value = kvs::PolygonObject::PolygonNormal;

    kvs::PolygonObject::NormalType normal_type = default_value;
    if ( this->hasOption("n") )
    {
        const std::string option_value = this->optionValue<std::string>("n");
        if ( option_value == "poly" ||
             option_value == "polygon" )
        {
            normal_type = kvs::PolygonObject::PolygonNormal;
        }
        else if ( option_value == "vert" ||
                  option_value == "vertex" )
        {
            normal_type = kvs::PolygonObject::VertexNormal;
        }
        else
        {
            kvsMessageError("Unknown normal type '%s'.",option_value.c_str());
        }
    }

    return( normal_type );
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
    Isosurface::Argument arg( m_argc, m_argv );
    if( !arg.parse() ) return( false );

    // Create a global and screen class.
    kvs::glut::Screen screen;
    screen.setSize( 512, 512 );
    screen.setTitle( kvsview::CommandName + " - " + kvsview::Isosurface::CommandName );
    arg.applyTo( screen );

    // Check the input point data.
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
    kvs::PipelineModule mapper( new kvs::Isosurface );
    const kvs::Real64 level = arg.isolevel();
    const kvs::PolygonObject::NormalType normal = arg.normalType();
    const kvs::TransferFunction function = arg.transferFunction();
    mapper.get<kvs::Isosurface>()->setIsolevel( level );
    mapper.get<kvs::Isosurface>()->setNormalType( normal );
    mapper.get<kvs::Isosurface>()->setTransferFunction( function );

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

    app.attach( &screen );

    return( app.run() );
}

} // end of namespace Default

} // end of namespace kvsview
