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
#include <kvs/File>
#include <kvs/KVSMLObjectStructuredVolume>
#include <kvs/KVSMLObjectUnstructuredVolume>
#include <kvs/AVSField>
#include <kvs/AVSUcd>
#include <kvs/PipelineModule>
#include <kvs/VisualizationPipeline>
#include <kvs/ExternalFaces>
#include <kvs/glut/Global>
#include <kvs/glut/Screen>


namespace
{

inline const bool CheckVolumeData( const std::string& filename )
{
    if ( kvs::KVSMLObjectStructuredVolume::CheckFileExtension( filename ) )
    {
        if ( kvs::KVSMLObjectStructuredVolume::CheckFileFormat( filename ) )
        {
            return( true );
        }
    }

    if ( kvs::KVSMLObjectUnstructuredVolume::CheckFileExtension( filename ) )
    {
        if ( kvs::KVSMLObjectUnstructuredVolume::CheckFileFormat( filename ) )
        {
            return( true );
        }
    }

    if ( kvs::AVSField::CheckFileExtension( filename ) ||
         kvs::AVSUcd::CheckFileExtension( filename ) )
    {
        return( true );
    }

    return( false );
}

} // end of namespace


namespace kvsview
{

namespace ExternalFaces
{

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
    // Parse specified arguments.
    ExternalFaces::Argument arg( m_argc, m_argv );
    if( !arg.parse() ) return( false );

    // Create a global and screen class.
    kvs::glut::Global global( m_argc, m_argv );
    kvs::glut::Screen screen( 512, 512 );
    screen.setTitle( kvsview::CommandName + " - " + kvsview::ExternalFaces::CommandName );
    arg.applyTo( screen );

    // Check the input volume data.
    m_input_name = arg.value<std::string>();
    if ( !::CheckVolumeData( m_input_name ) )
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

} // end of namespace ExternalFaces

} // end of namespace kvsview
