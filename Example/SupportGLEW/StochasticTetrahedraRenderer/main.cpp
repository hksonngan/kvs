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
#include <kvs/UnstructuredVolumeObject>
#include <kvs/UnstructuredVolumeImporter>
#include <kvs/glew/StochasticTetrahedraRenderer>


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

    kvs::UnstructuredVolumeObject* object = new kvs::UnstructuredVolumeImporter( argv[1] );

    kvs::glew::StochasticTetrahedraRenderer* renderer = new kvs::glew::StochasticTetrahedraRenderer();
    renderer->setRepetitionLevel( 50 );
    renderer->enableLODControl();

    kvs::glut::Screen screen( &app );
    screen.registerObject( object, renderer );
    screen.show();

    // Enable two-side (frontface and backface) lighting
    screen.light()->setModelTwoSide( true );

    return app.run();
}
