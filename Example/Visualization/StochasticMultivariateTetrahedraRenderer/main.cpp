/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @author Naohisa Sakamoto
 *  @brief  Example program for kvs::StochasticMultivariateTetrahedraRenderer class.
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
#include <kvs/RGBFormulae>
#include <kvs/TransferFunction>
#include <kvs/StochasticMultivariateTetrahedraRenderer>


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

    kvs::StochasticMultivariateTetrahedraRenderer* renderer = new kvs::StochasticMultivariateTetrahedraRenderer();
    renderer->setRepetitionLevel( 50 );
    renderer->enableLODControl( 1 );

    kvs::TransferFunction tfunc;
    tfunc.setColorMap( kvs::RGBFormulae::PM3D( 256 ) );
    renderer->setTransferFunction( tfunc, 1 );

    kvs::glut::Screen screen( &app );
    screen.registerObject( object, renderer );
    screen.show();

    // Enable two-side (frontface and backface) lighting
    screen.light()->setModelTwoSide( true );

    return app.run();
}
