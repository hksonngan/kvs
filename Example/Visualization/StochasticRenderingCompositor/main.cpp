/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @author Naohisa Sakamoto
 *  @brief  Example program for kvs::StochasticTetrahedraRenderer class.
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include <kvs/glut/Application>
#include <kvs/glut/Screen>
#include <kvs/PolygonObject>
#include <kvs/ExternalFaces>
#include <kvs/UnstructuredVolumeObject>
#include <kvs/UnstructuredVolumeImporter>
#include <kvs/StochasticPolygonRenderer>
#include <kvs/StochasticTetrahedraRenderer>
#include <kvs/StochasticRenderingCompositor>
#include <kvs/Scene>
#include <iostream>


/*===========================================================================*/
/**
 *  @brief  Main function.
 *  @param  argc [i] argument count
 *  @param  argv [i] argument values
 */
/*===========================================================================*/
int main( int argc, char** argv )
{
    kvs::glut::Application app( argc, argv );

    kvs::UnstructuredVolumeObject* volume_object = new kvs::UnstructuredVolumeImporter( argv[1] );
    volume_object->print( std::cout );

    kvs::PolygonObject* polygon_object = new kvs::ExternalFaces( volume_object );
    polygon_object->setColor( kvs::RGBColor::White() );
    polygon_object->setOpacity( 100 );
    polygon_object->print( std::cout << std::endl );

    kvs::StochasticTetrahedraRenderer* volume_renderer = new kvs::StochasticTetrahedraRenderer();
    kvs::StochasticPolygonRenderer* polygon_renderer = new kvs::StochasticPolygonRenderer();

    kvs::glut::Screen screen( &app );
    screen.setTitle("Example program for kvs::StochasticRenderingCompositor");
    screen.registerObject( polygon_object, polygon_renderer );
    screen.registerObject( volume_object, volume_renderer );
    screen.show();

    kvs::StochasticRenderingCompositor compositor( screen.scene() );
    compositor.setRepetitionLevel( 50 );
    compositor.enableLODControl();
    screen.setEvent( &compositor );

    return app.run();
}
