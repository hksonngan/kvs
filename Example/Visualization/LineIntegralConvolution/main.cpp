/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::LineIntegralConvolution class.
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
#include <kvs/LineIntegralConvolution>
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
    kvs::StructuredVolumeObject* volume = new kvs::StructuredVolumeImporter( filename );
    if ( !volume )
    {
        kvsMessageError( "Cannot creat a structured volume object.");
    }

    kvs::StructuredVolumeObject* object = new kvs::LineIntegralConvolution( volume , 0.2 );
    if ( !object )
    {
        kvsMessageError( "Cannot create LIC structured volume object.");
        delete volume;
        return( false );
    }

    delete volume;

    kvs::RayCastingRenderer* renderer = new kvs::RayCastingRenderer();
    if ( !renderer )
    {
        kvsMessageError( "Cannot create a ray-casting renderer." );
        delete object;
        return( false );
    }

    kvs::glut::Screen screen( &app );
    screen.registerObject( object, renderer );
    screen.setGeometry( 0, 0, 512, 512 );
    screen.setTitle( "kvs::LineIntegralConvolution" );
    screen.show();

    return( app.run() );
}
