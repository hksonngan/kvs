/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::RayCastingRenderer class.
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: main.cpp 502 2010-04-27 10:59:39Z naohisa.sakamoto $
 */
/*****************************************************************************/
#include <kvs/Message>
#include <kvs/StructuredVolumeObject>
#include <kvs/StructuredVolumeImporter>
#include <kvs/RayCastingRenderer>
#include <kvs/HydrogenVolumeData>
#include <kvs/opencabin/Application>
#include <kvs/opencabin/Screen>

#define ENABLE_GPU_RENDERING 1

#ifdef ENABLE_GPU_RENDERING
#include <kvs/glew/RayCastingRenderer>
#endif

/*===========================================================================*/
/**
 *  @brief  Main function.
 *  @param  argc [i] argument counter
 *  @param  argv [i] argument values
 */
/*===========================================================================*/
int main( int argc, char** argv )
{
    kvs::opencabin::Application app( argc, argv );

    /* Read volume data from the specified data file. If the data file is not
     * specified, scalar hydrogen volume data is created by using
     * kvs::HydrogenVolumeData class.
     */
    kvs::StructuredVolumeObject* object = NULL;
    if ( argc > 1 ) object = new kvs::StructuredVolumeImporter( std::string( argv[1] ) );
    else            object = new kvs::HydrogenVolumeData( kvs::Vector3ui( 32, 32, 32 ) );

    if ( !object )
    {
        kvsMessageError( "Cannot create a structured volume object." );
        return( false );
    }

#ifdef ENABLE_GPU_RENDERING
    kvs::glew::RayCastingRenderer* renderer = new kvs::glew::RayCastingRenderer();
#else
    kvs::RayCastingRenderer* renderer = new kvs::RayCastingRenderer();
#endif
    if ( !renderer )
    {
        kvsMessageError( "Cannot create a ray casting renderer." );
        delete object;
        return( false );
    }

    const kvs::TransferFunction t = argc > 2 ? kvs::TransferFunction( argv[2] ) : kvs::TransferFunction( 256 );
    renderer->setTransferFunction( t );

    kvs::opencabin::Screen screen( &app );
    screen.registerObject( object, renderer );
    //screen.setGeometry( 0, 0, 512, 512 );
    screen.setTitle( "kvs::RayCastingRenderer" );
    screen.show();

    return( app.run() );
}
