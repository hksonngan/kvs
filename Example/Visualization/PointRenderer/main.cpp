/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::PointRenderer class.
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
#include <kvs/PointImporter>
#include <kvs/PointObject>
#include <kvs/PointRenderer>
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
    kvs::PointObject* object = new kvs::PointImporter( filename );
    if ( !object )
    {
        kvsMessageError( "Cannot creat a point object.");
        return( false );
    }

    kvs::PointRenderer* renderer = new kvs::PointRenderer();
    if ( !renderer )
    {
        kvsMessageError( "Cannot creat a point renderer.");
    }

    kvs::glut::Screen screen( &app );
    screen.registerObject( object, renderer );
    screen.setGeometry( 0, 0, 512, 512 );
    screen.setTitle( "kvs::PointRenderer" );
    screen.show();

    return( app.run() );
}
