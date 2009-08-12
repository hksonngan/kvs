/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::SlicePlane class.
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
#include <kvs/PolygonObject>
#include <kvs/SlicePlane>
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
    kvs::StructuredVolumeObject* volume = new kvs::StructuredVolumeImporter( filename );
    if ( !volume )
    {
        kvsMessageError( "Cannot create a structured volume object." );
        return( false );
    }

    /* Extract planes by using SlicePlane class.
     *    c: center of gravity of the volume object.
     *    p: point located on the plane.
     *    n: normal vector of the plane.
     *    t: transfer function.
     */
    const kvs::Vector3f c( ( volume->maxObjectCoord() + volume->minObjectCoord() ) * 0.5f );
    const kvs::Vector3f p( c );
    const kvs::Vector3f n( 1.5, 0.8, 2.0 );
    const kvs::TransferFunction t( 256 );
    kvs::PolygonObject* object = new kvs::SlicePlane( volume, p, n, t );
    if ( !object )
    {
        kvsMessageError( "Cannot create a polygon object by Slice plane." );
        delete volume;
        return( false );
    }

    delete volume;

    kvs::glut::Screen screen;
    screen.registerObject( object );
    screen.setGeometry( 0, 0, 512, 512 );
    screen.setTitle( "kvs::SlicePlane" );
    screen.show();

    app.attach( &screen );

    return( app.run() );
}
