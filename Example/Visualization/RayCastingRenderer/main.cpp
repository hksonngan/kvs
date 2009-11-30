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
 *  $Id$
 */
/*****************************************************************************/
#include <kvs/Message>
#include <kvs/StructuredVolumeObject>
#include <kvs/StructuredVolumeImporter>
#include <kvs/RayCastingRenderer>
#include <kvs/glut/Application>
#include <kvs/glut/Screen>


/*===========================================================================*/
/**
 *  @brief  Main function.
 *  @param  argc [i] argument counter
 *  @param  argv [i] argument values
 */
/*===========================================================================*/
int main( int argc, char** argv )
{
    kvs::glut::Application app( argc, argv );

    const std::string filename( argc > 1 ? argv[1] : "" );
    kvs::StructuredVolumeObject* object = new kvs::StructuredVolumeImporter( filename );
    if ( !object )
    {
        kvsMessageError( "Cannot create a structured volume object." );
        return( false );
    }

    kvs::RayCastingRenderer* renderer = new kvs::RayCastingRenderer();
    if ( !renderer )
    {
        kvsMessageError( "Cannot create a ray casting renderer." );
        delete object;
        return( false );
    }

    kvs::glut::Screen screen( &app );
    screen.registerObject( object, renderer );
    screen.setGeometry( 0, 0, 512, 512 );
    screen.setTitle( "kvs::RayCastingRenderer" );
    screen.show();

    return( app.run() );
}
