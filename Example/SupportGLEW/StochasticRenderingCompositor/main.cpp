/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @author Naohisa Sakamoto
 *  @brief  Example program for kvs::glew::StochasticTetrahedraRenderer class.
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
#include <kvs/PolygonImporter>
#include <kvs/UnstructuredVolumeObject>
#include <kvs/UnstructuredVolumeImporter>
#include <kvs/glew/StochasticPolygonEngine>
#include <kvs/glew/StochasticTetrahedraEngine>
#include <kvs/glew/StochasticRenderingCompositor>
#include <kvs/ObjectManager>
#include <kvs/RendererManager>
#include <kvs/IDManager>

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

    kvs::PolygonObject* polygon_object = new kvs::PolygonImporter( argv[1] );
    kvs::glew::StochasticPolygonEngine* polygon_engine = new kvs::glew::StochasticPolygonEngine();
    polygon_object->setOpacity( 128 );

    kvs::UnstructuredVolumeObject* volume_object = new kvs::UnstructuredVolumeImporter( argv[2] );
    kvs::glew::StochasticTetrahedraEngine* volume_engine = new kvs::glew::StochasticTetrahedraEngine();

    kvs::glut::Screen screen( &app );
    screen.show();

    // Enable two-side (frontface and backface) lighting
    screen.light()->setModelTwoSide( true );

    kvs::ObjectManager* object_manager = screen.objectManager();
    kvs::RendererManager* renderer_manager = screen.rendererManager();
    kvs::IDManager* id_manager = screen.IDManager();
    kvs::glew::StochasticRenderingCompositor compositor( object_manager, renderer_manager, id_manager );
    compositor.setRepetitionLevel( 50 );
    compositor.enableLODControl( 1 );
    compositor.registerObject( polygon_object, polygon_engine );
    compositor.registerObject( volume_object, volume_engine );

    return app.run();
}
