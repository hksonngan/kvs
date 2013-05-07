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
#include <kvs/UnstructuredVolumeObject>
#include <kvs/UnstructuredVolumeImporter>
#include <kvs/TransferFunction>
#include <kvs/StochasticTetrahedraRenderer>
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

    kvs::UnstructuredVolumeObject* object = new kvs::UnstructuredVolumeImporter( argv[1] );
    object->print( std::cout );

    kvs::TransferFunction tfunc( 256 );
    kvs::StochasticTetrahedraRenderer* renderer = new kvs::StochasticTetrahedraRenderer();
    renderer->setTransferFunction( tfunc );
    renderer->setRepetitionLevel( 50 );
    renderer->enableLODControl();

    kvs::glut::Screen screen( &app );
    screen.setTitle(" Example program for kvs::StochasticTetrahedraRenderer");
    screen.registerObject( object, renderer );
    screen.show();

    return app.run();
}
