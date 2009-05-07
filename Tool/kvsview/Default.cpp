/*****************************************************************************/
/**
 *  @file   Default.cpp
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
#include "Default.h"
#include "ObjectInformation.h"
#include "TransferFunction.h"
#include <kvs/VisualizationPipeline>
#include <kvs/ImageObject>
#include <kvs/glut/Global>
#include <kvs/glut/Screen>


namespace kvsview
{

namespace Default
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new Argument class for a default viewer.
 *  @param  argc [in] argument count
 *  @param  argv [in] argument values
 */
/*===========================================================================*/
Argument::Argument( int argc, char** argv ):
    kvsview::Argument::Common( argc, argv )
{
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new Main class for a default viewer.
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
    Default::Argument arg( m_argc, m_argv );
    if( !arg.parse() ) return( false );

    // In case of transfer function data file.
    if ( kvsview::TransferFunction::Check( arg.value<std::string>() ) )
    {
        return( kvsview::TransferFunction::Main( m_argc, m_argv ).exec() );
    }

    // Create a global and screen class.
    kvs::glut::Global global( m_argc, m_argv );
    kvs::glut::Screen screen( 512, 512 );
    screen.setTitle("kvsview - Default");
    arg.applyTo( screen );

    // Visualization pipeline.
    m_input_name = arg.value<std::string>();
    kvs::VisualizationPipeline pipe( m_input_name );
    pipe.import();

    // Verbose information.
    if ( arg.verboseMode() )
    {
        std::cout << "IMPORTED OBJECT" << std::endl;
        std::cout << kvsview::ObjectInformation( pipe.object() ) << std::endl;
        std::cout << std::endl;
    }

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

    // In case of the image object, the screen size is equal to the image size.
    if ( pipe.object()->objectType() == kvs::ObjectBase::Image )
    {
        const kvs::ImageObject* image = reinterpret_cast<const kvs::ImageObject*>( pipe.object() );
        const size_t width = image->width();
        const size_t height = image->height();
        screen.setSize( width, height );
    }

    // Show the screen.
    return( screen.show() != 0 );
}

} // end of namespace Default

} // end of namespace kvsview
