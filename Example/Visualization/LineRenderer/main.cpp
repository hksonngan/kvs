/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::LineRenderer.
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
#include <kvs/KVSMLObjectLine>
#include <kvs/LineImporter>
#include <kvs/LineObject>
#include <kvs/LineRenderer>
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
    kvs::LineObject* object = new kvs::LineImporter( filename );
    if ( !object )
    {
        kvsMessageError( "Cannot creat a line object.");
        return( false );
    }

    kvs::LineRenderer* renderer = new kvs::LineRenderer();
    if ( !renderer )
    {
        kvsMessageError( "Cannot creat a line renderer.");
    }

    kvs::glut::Screen screen;
    screen.registerObject( object, renderer );
    screen.setGeometry( 0, 0, 512, 512 );
    screen.setTitle( "kvs::LineRenderer" );
    screen.show();

    app.attach( &screen );

    return( app.run() );
}
