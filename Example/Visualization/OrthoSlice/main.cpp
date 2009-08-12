/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::OrthoSlice class.
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
#include <kvs/OrthoSlice>
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
        return;
    }

    /* Extract orthogonal planes by using OrthoSlice class.
     *    p: plane position.
     *    a: axis of the orthogonal plane.
     *    t: transfer function.
     */
    const float p = volume->resolution().z() * 0.5f;
    const kvs::OrthoSlice::AlignedAxis a = kvs::OrthoSlice::ZAxis;
    const kvs::TransferFunction t( 256 );
    kvs::PolygonObject* object = new kvs::OrthoSlice( volume, p, a, t );
    if ( !object )
    {
        kvsMessageError( "Cannot create a polygon object." );
        delete volume;
        return;
    }

    delete volume;

    kvs::glut::Screen screen;
    screen.registerObject( object, renderer );
    screen.setGeometry( 0, 0, 512, 512 );
    screen.setTitle( "kvs::OrthoSlice" );
    screen.show();
    app.attach( &screen );

    return( app.run() );
}
