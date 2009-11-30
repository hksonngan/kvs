/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::Isosurface class.
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
#include <kvs/Isosurface>
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

    /* Extract surfaces by using the Isosurface class.
     *    i: isolevel
     *    n: NormalType (PolygonNormal/VertexNormal)
     *    d: check flag whether the duplicate vertices are deleted (false) or not
     *    t: transfer function
     */
    volume->updateMinMaxValues();
    const double i = ( volume->maxValue() + volume->minValue() ) * 0.5;
    const kvs::PolygonObject::NormalType n = kvs::PolygonObject::VertexNormal;
    const bool d = false;
    const kvs::TransferFunction t( 256 );
    kvs::PolygonObject* object = new kvs::Isosurface( volume, i, n, d, t );
    if ( !object )
    {
        kvsMessageError( "Cannot create a polygon object." );
        delete volume;
        return( false );
    }

    delete volume;

    // Screen.
    kvs::glut::Screen screen( &app );
    screen.registerObject( object );
    screen.setGeometry( 0, 0, 512, 512 );
    screen.setTitle( "kvs::Isosurface" );
    screen.show();

    return( app.run() );
}
