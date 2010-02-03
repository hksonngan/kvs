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
#include <kvs/glut/Application>
#include <kvs/glut/Screen>
#if defined( KVS_SUPPORT_GLEW )
#include <kvs/glew/RayCastingRenderer>
#endif


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
    // GLUT application.
    kvs::glut::Application app( m_argc, m_argv );

    // Parse specified arguments.
    kvsview::Default::Argument arg( m_argc, m_argv );
    if( !arg.parse() ) return( false );

    /* Transfer function data is checked here, since default visualization
     * method for the transfer function data hasn't yet been implemented in
     * the visualization pipeline class.
     */
    if ( kvsview::TransferFunction::Check( arg.value<std::string>() ) )
    {
        return( kvsview::TransferFunction::Main( m_argc, m_argv ).exec() );
    }

    // Create a global and screen class.
    kvs::glut::Screen screen( &app );
    screen.setSize( 512, 512 );
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

#if defined( KVS_SUPPORT_GLEW )
    if ( pipe.object()->objectType() == kvs::ObjectBase::Volume )
    {
        const kvs::VolumeObjectBase* volume = kvs::VolumeObjectBase::DownCast( pipe.object() );
        if ( volume->volumeType() == kvs::VolumeObjectBase::Structured )
        {
            kvs::PipelineModule renderer( new kvs::glew::RayCastingRenderer );
            pipe.connect( renderer );
        }
    }
#endif

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

    // In case of the image object, the screen size is equal to the image size.
    if ( pipe.object()->objectType() == kvs::ObjectBase::Image )
    {
        const kvs::ImageObject* image = reinterpret_cast<const kvs::ImageObject*>( pipe.object() );
        const size_t width = image->width();
        const size_t height = image->height();
        screen.setSize( width, height );
    }

    // Show the screen.
    screen.show();

    return( app.run() );
}

} // end of namespace Default

} // end of namespace kvsview
