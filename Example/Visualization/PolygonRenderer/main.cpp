/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::PolygonRenderer class.
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
#include <kvs/PolygonImporter>
#include <kvs/PolygonObject>
#include <kvs/PolygonRenderer>
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
    kvs::PolygonObject* object = new kvs::PolygonImporter( filename );
    if ( !object )
    {
        kvsMessageError( "Cannot creat a polygon object.");
        return( false );
    }

    kvs::PolygonRenderer* renderer = new kvs::PolygonRenderer();
    if ( !renderer )
    {
        kvsMessageError( "Cannot creat a polygon renderer.");
    }

    kvs::glut::Screen screen( &app );
    screen.registerObject( object, renderer );
    screen.setGeometry( 0, 0, 512, 512 );
    screen.setTitle( "kvs::PolygonRenderer" );
    screen.show();

    return( app.run() );
}
